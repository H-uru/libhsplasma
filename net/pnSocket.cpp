#include "pnSocket.h"
#include "Debug/plDebug.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <poll.h>
#include <fcntl.h>

#ifdef WIN32
  #include <winsock.h>
#else
  #include <unistd.h>
  #define closesocket ::close
#endif

/* pnSocket */
plString pnSocket::getRemoteIpStr() const
{
    static hsMutex ipStrMutex;

    sockaddr_in addr;
    socklen_t slen = sizeof(addr);
    ipStrMutex.lock();
    const char* str = "???.???.???.???";
    if (getpeername(fSockHandle, (sockaddr*)&addr, &slen) >= 0)
        str = inet_ntoa(addr.sin_addr);
    plString result(str);
    ipStrMutex.unlock();
    return result;
}

bool pnSocket::connect(const char* address, unsigned short port)
{
    addrinfo conn;
    memset(&conn, 0, sizeof(conn));
    conn.ai_flags = AI_ADDRCONFIG;
    conn.ai_family = AF_UNSPEC;
    conn.ai_socktype = SOCK_STREAM;
    conn.ai_protocol = 0;

    addrinfo* addr;
    int res = getaddrinfo(address, plString::Format("%hu", port).cstr(),
                          &conn, &addr);
    if (res != 0) {
        plString msg = gai_strerror(res);
        plDebug::Error("Failed to connect to %s:%hu", address, port);
        plDebug::Error("    Error message was %s", msg.cstr());
        return false;
    }

    for (addrinfo* ap = addr; ap != NULL; ap = ap->ai_next) {
        fSockHandle = socket(ap->ai_family, ap->ai_socktype, ap->ai_protocol);
        if (fSockHandle != -1) {
            if (::connect(fSockHandle, ap->ai_addr, ap->ai_addrlen) != -1)
                break;
        }
        closesocket(fSockHandle);
        fSockHandle = -1;
    }

    if (fSockHandle == -1) {
        plDebug::Error("Failed to connect to %s:%hu", address, port);
        return false;
    }

    freeaddrinfo(addr);
    return true;
}

bool pnSocket::bind(unsigned short port)
{
    addrinfo conn;
    memset(&conn, 0, sizeof(conn));
    conn.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;
    conn.ai_family = AF_UNSPEC;
    conn.ai_socktype = SOCK_STREAM;
    conn.ai_protocol = 0;

    addrinfo* addr;
    int res = getaddrinfo(NULL, plString::Format("%hu", port).cstr(),
                          &conn, &addr);
    if (res != 0) {
        plString msg = gai_strerror(res);
        plDebug::Error("Failed to bind to port %hu", port);
        plDebug::Error("    Error message was %s", msg.cstr());
        return false;
    }

    for (addrinfo* ap = addr; ap != NULL; ap = ap->ai_next) {
        fSockHandle = socket(ap->ai_family, ap->ai_socktype, ap->ai_protocol);
        if (fSockHandle != -1) {
            if (::bind(fSockHandle, ap->ai_addr, ap->ai_addrlen) == 0)
                break;
        }
        ::close(fSockHandle);
        fSockHandle = -1;
    }

    if (fSockHandle == -1) {
        plDebug::Error("Failed to bind to port %hu", port);
        return false;
    }

    freeaddrinfo(addr);
    return true;
}

pnSocket* pnSocket::listen(int backlog)
{
    if (::listen(fSockHandle, backlog) == -1) {
        if (fSockHandle != -1)
            plDebug::Error("Listen failed: %s", strerror(errno));
        return NULL;
    }

    int client = accept(fSockHandle, NULL, NULL);
    if (client == -1) {
        if (fSockHandle != -1)
            plDebug::Error("Listen failed: %s", strerror(errno));
        return NULL;
    }
    return new pnSocket(client);
}

void pnSocket::close(bool force)
{
    if (fSockHandle != -1) {
        if (force)
            ::shutdown(fSockHandle, 2);
        else
            ::close(fSockHandle);
    }
    fSockHandle = -1;
}

ssize_t pnSocket::send(const void* buffer, size_t size)
{
    ssize_t count = ::send(fSockHandle, buffer, size, 0);
    if (count == -1)
        plDebug::Error("Send failed: %s", strerror(errno));
    else if ((size_t)count < size)
        plDebug::Warning("Send truncated");
    return count;
}

ssize_t pnSocket::recv(void* buffer, size_t size)
{
    ssize_t count = ::recv(fSockHandle, buffer, size, 0);
    if (count == -1 && errno != ECONNRESET)
        plDebug::Error("Recv failed: %s", strerror(errno));
    return count;
}

ssize_t pnSocket::peek(void* buffer, size_t size)
{
    ssize_t count = ::recv(fSockHandle, buffer, size, MSG_PEEK);
    if (count == -1 && errno != ECONNRESET)
        plDebug::Error("Peek failed: %s", strerror(errno));
    return count;
}

ssize_t pnSocket::rsize()
{
    unsigned char buf;
    ssize_t count = ::recv(fSockHandle, &buf, 1, MSG_PEEK | MSG_DONTWAIT | MSG_TRUNC);
    if (count < 1)
        return 0;
    return count;
}

unsigned long pnSocket::GetAddress(const char* addrName)
{
    static hsMutex addrMutex;
    addrMutex.lock();
    hostent* host = gethostbyname(addrName);
    unsigned long numAddr = 0;
    if (host != NULL && host->h_addr_list != NULL)
        numAddr = ntohl(*(unsigned long*)host->h_addr_list[0]);
    addrMutex.unlock();
    return numAddr;
}


/* pnAsyncSocket */
pnAsyncSocket::_async::~_async()
{
    if (fSock != NULL) {
        fSock->close(true);
        delete fSock;
    }
    fSockMutex.lock();
    while (!fSendQueue.empty()) {
        delete[] fSendQueue.front().fData;
        fSendQueue.pop_front();
    }
    while (!fRecvQueue.empty()) {
        delete[] fRecvQueue.front().fData;
        fRecvQueue.pop_front();
    }
    fSockMutex.unlock();
}

void pnAsyncSocket::_async::run()
{
    if (fSock == NULL)
        return;

    struct pollfd pinfo;
    pinfo.fd = fSock->getHandle();
    pinfo.events = POLLIN | POLLOUT;

    while (!isFinished()) {
        int id = poll(&pinfo, 1, -1);
        if (id <= 0) {
            plDebug::Error("Error reading from socket: %s", strerror(errno));
            // TODO: Reconnect socket instead of dumping it
            return;
        }

        if ((pinfo.revents & (POLLHUP | POLLNVAL)) != 0)
            return;

        if ((pinfo.revents & POLLERR) != 0) {
            plDebug::Error("Socket error: %s", strerror(errno));
            return;
        }

        fSockMutex.lock();
        if ((pinfo.revents & POLLOUT) != 0 && !fSendQueue.empty()) {
            // Dump the next queued message to the socket
            _datum msg = *fSendQueue.begin();
            fSendQueue.pop_front();
            fSock->send(msg.fData, msg.fSize);
            delete[] msg.fData;
        }

        if ((pinfo.revents & POLLIN) != 0) {
            _datum msg;
            msg.fSize = (size_t)fSock->rsize();
            msg.fData = new unsigned char[msg.fSize];
            fSock->recv(msg.fData, msg.fSize);
            fRecvQueue.push_back(msg);
        }
        fSockMutex.unlock();
    }
}

ssize_t pnAsyncSocket::send(const void* buffer, size_t size)
{
    _async::_datum msg;
    msg.fSize = size;
    msg.fData = new unsigned char[size];
    memcpy(msg.fData, buffer, size);

    if (!fAsyncIO.isFinished()) {
        fAsyncIO.fSockMutex.lock();
        fAsyncIO.fSendQueue.push_back(msg);
        fAsyncIO.fSockMutex.unlock();
        return size;
    } else {
        return -1;
    }
}

ssize_t pnAsyncSocket::recv(void* buffer, size_t size)
{
    ssize_t rSize = 0;
    while (size > 0) {
        if (!waitForData())
            return -1;

        fAsyncIO.fSockMutex.lock();
        _async::_datum msg = fAsyncIO.fRecvQueue.front();
        size_t cpySize = size;
        if (size + fAsyncIO.fReadPos >= msg.fSize)
            cpySize = msg.fSize - fAsyncIO.fReadPos;
        memcpy(buffer, msg.fData + fAsyncIO.fReadPos, cpySize);
        if (size + fAsyncIO.fReadPos >= msg.fSize) {
            delete[] msg.fData;
            fAsyncIO.fRecvQueue.pop_front();
            fAsyncIO.fReadPos = 0;
        } else {
            fAsyncIO.fReadPos += cpySize;
        }
        fAsyncIO.fSockMutex.unlock();
        buffer = (void*)((unsigned char*)buffer + cpySize);
        size -= cpySize;
        rSize += cpySize;
    }
    return rSize;
}

ssize_t pnAsyncSocket::peek(void* buffer, size_t size)
{
    if (!waitForData())
        return -1;

    fAsyncIO.fSockMutex.lock();
    std::list<_async::_datum>::iterator it = fAsyncIO.fRecvQueue.begin();
    ssize_t rSize = 0;
    size_t readPos = fAsyncIO.fReadPos;
    while (size > 0 && it != fAsyncIO.fRecvQueue.end()) {
        _async::_datum msg = *it;
        size_t cpySize = size;
        if (size + readPos >= msg.fSize)
            cpySize = msg.fSize - readPos;
        memcpy(buffer, msg.fData + readPos, cpySize);
        if (size + readPos >= msg.fSize) {
            it++;
            readPos = 0;
        } else {
            readPos += cpySize;
        }
        buffer = (void*)((unsigned char*)buffer + cpySize);
        size -= cpySize;
        rSize += cpySize;
    }
    fAsyncIO.fSockMutex.unlock();
    return (ssize_t)rSize;
}
