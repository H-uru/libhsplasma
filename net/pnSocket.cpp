#include "pnSocket.h"
#include "Debug/plDebug.h"

static const char* getSockErrorStr();
static int sockError();

#ifdef WIN32
#  include <winsock2.h>
#  include <ws2tcpip.h>

   typedef char* sockbuf_t;

   static WSADATA s_wsadata;

   static void closeWinsock()
   { WSACleanup(); }

   static int sockError()
   { return WSAGetLastError(); }

#  define ECONNRESET WSAECONNRESET
#else
#  include <sys/types.h>
#  include <sys/socket.h>
#  include <sys/ioctl.h>
#  include <netinet/in.h>
#  include <netinet/tcp.h>
#  include <arpa/inet.h>
#  include <netdb.h>
#  include <poll.h>
#  include <unistd.h>
#  include <errno.h>
#  include <signal.h>

#  define closesocket ::close
#  define ioctlsocket ::ioctl
   typedef void* sockbuf_t;

   static int sockError()
   { return errno; }

#  define INVALID_SOCKET (-1)
#endif

static const char* getSockErrorStr()
{
#ifdef WIN32
    static char msgbuf[4096];

    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, WSAGetLastError(),
                  0, msgbuf, 4096, NULL);
    return msgbuf;
#else
    return strerror(errno);
#endif
}

static void initSockets()
{
    static bool s_firstInit = true;
    if (s_firstInit) {
#ifdef WIN32
        WSAStartup(MAKEWORD(2, 0), &s_wsadata);
        atexit(closeWinsock);
#endif
        s_firstInit = false;
    }
}

/* pnSocket */
pnSocket::pnSocket()
        : fSockHandle(-1)
{
    initSockets();
}

pnSocket::pnSocket(int handle)
        : fSockHandle(handle)
{
    initSockets();
}

pnSocket::~pnSocket()
{
    close();
}

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

int pnSocket::getHandle() const
{
    return fSockHandle;
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
        if (fSockHandle != INVALID_SOCKET) {
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
        if (fSockHandle != INVALID_SOCKET) {
            if (::bind(fSockHandle, ap->ai_addr, ap->ai_addrlen) == 0)
                break;
        }
        closesocket(fSockHandle);
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
            plDebug::Error("Listen failed: %s", getSockErrorStr());
        return NULL;
    }

    int client = accept(fSockHandle, NULL, NULL);
    if (client == -1) {
        if (fSockHandle != -1)
            plDebug::Error("Listen failed: %s", getSockErrorStr());
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
            closesocket(fSockHandle);
    }
    fSockHandle = -1;
}

void pnSocket::unlink()
{
    fSockHandle = -1;
    delete this;
}

void pnSocket::link(int handle)
{
    fSockHandle = handle;
}

long pnSocket::send(const void* buffer, size_t size)
{
    long count = ::send(fSockHandle, (const sockbuf_t)buffer, size, 0);
    if (count == -1)
        plDebug::Error("Send failed: %s", getSockErrorStr());
    else if ((size_t)count < size)
        plDebug::Warning("Send truncated");
    return count;
}

long pnSocket::recv(void* buffer, size_t size)
{
    long count = ::recv(fSockHandle, (sockbuf_t)buffer, size, 0);
    if (count == -1 && sockError() != ECONNRESET)
        plDebug::Error("Recv failed: %s", getSockErrorStr());
    return count;
}

long pnSocket::peek(void* buffer, size_t size)
{
    long count = ::recv(fSockHandle, (sockbuf_t)buffer, size, MSG_PEEK);
    if (count == -1 && sockError() != ECONNRESET)
        plDebug::Error("Peek failed: %s", getSockErrorStr());
    return count;
}

long pnSocket::rsize()
{
#ifdef WIN32
    unsigned long size;
#else
    int size;
#endif
    ioctlsocket(fSockHandle, FIONREAD, &size);
    return (long)size;
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
pnAsyncSocket::_async::_async()
             : fSock(NULL), fReadPos(0), fFinished(false)
{
    fSockMutex = new hsMutex();
    fStatusChange = new hsThreadCondition();
}

void pnAsyncSocket::_async::destroy()
{
    if (fSock != NULL) {
        fSock->close(true);
        delete fSock;
    }
    while (!fRecvQueue.empty()) {
        delete[] fRecvQueue.front().fData;
        fRecvQueue.pop_front();
    }
    delete fStatusChange;
    delete fSockMutex;
}

void pnAsyncSocket::_async::run()
{
    if (fSock == NULL)
        return;

    struct timeval stimeout;
    fd_set sread;
    FD_ZERO(&sread);

    int hSock = fSock->getHandle();
    fSockMutex->lock();
    while (!fFinished) {
        fSockMutex->unlock();
        FD_SET(hSock, &sread);

        /* 0.5 second poll timeout */
        stimeout.tv_sec  = 0;
        stimeout.tv_usec = 500000;

        int si = select(hSock + 1, &sread, NULL, NULL, &stimeout);
        if (si < 0) {
            plDebug::Error("Error reading from socket: %s", getSockErrorStr());
            // TODO: Reconnect socket instead of dumping it
            break;
        }

        if (FD_ISSET(hSock, &sread)) {
            _datum msg;
            fSockMutex->lock();
            msg.fSize = (size_t)fSock->rsize();
            if (msg.fSize < 0) {
                plDebug::Error("Error reading from socket: %s", getSockErrorStr());
                break;
            } else if (msg.fSize == 0) {
                // Disconnected
                break;
            }
            msg.fData = new unsigned char[msg.fSize];
            fSock->recv(msg.fData, msg.fSize);
            fRecvQueue.push_back(msg);
            fStatusChange->signal();
            fSockMutex->unlock();
        }
    }
    fSockMutex->lock();
    fSock->close();
    fFinished = true;
    fStatusChange->signal();
    fSockMutex->unlock();
}

pnAsyncSocket::pnAsyncSocket(pnSocket* sock)
{
    int yes = 1;
    fAsyncIO = new _async();
    fAsyncIO->fSock = sock;
    ioctlsocket(sock->getHandle(), FIOASYNC, &yes);
    fAsyncIO->start();
}

pnAsyncSocket::~pnAsyncSocket()
{
    fAsyncIO->fFinished = true;
    fAsyncIO->destroy();
}

long pnAsyncSocket::send(const void* buffer, size_t size)
{
    _async::_datum msg;
    msg.fSize = size;
    msg.fData = new unsigned char[size];
    memcpy(msg.fData, buffer, size);

    fAsyncIO->fSockMutex->lock();
    if (!fAsyncIO->fFinished) {
        fAsyncIO->fSock->send(msg.fData, msg.fSize);
        fAsyncIO->fSockMutex->unlock();
        return size;
    }
    fAsyncIO->fSockMutex->unlock();
    return -1;
}

long pnAsyncSocket::recv(void* buffer, size_t size)
{
    long rSize = 0;
    while (size > 0) {
        if (!waitForData())
            return -1;

        fAsyncIO->fSockMutex->lock();
        _async::_datum msg = fAsyncIO->fRecvQueue.front();
        size_t cpySize = size;
        if (size + fAsyncIO->fReadPos >= msg.fSize)
            cpySize = msg.fSize - fAsyncIO->fReadPos;
        memcpy(buffer, msg.fData + fAsyncIO->fReadPos, cpySize);
        if (size + fAsyncIO->fReadPos >= msg.fSize) {
            delete[] msg.fData;
            fAsyncIO->fRecvQueue.pop_front();
            fAsyncIO->fReadPos = 0;
        } else {
            fAsyncIO->fReadPos += cpySize;
        }
        fAsyncIO->fSockMutex->unlock();
        buffer = (void*)((unsigned char*)buffer + cpySize);
        size -= cpySize;
        rSize += cpySize;
    }
    return rSize;
}

long pnAsyncSocket::peek(void* buffer, size_t size)
{
    if (!waitForData())
        return -1;

    fAsyncIO->fSockMutex->lock();
    std::list<_async::_datum>::iterator it = fAsyncIO->fRecvQueue.begin();
    long rSize = 0;
    size_t readPos = fAsyncIO->fReadPos;
    while (size > 0 && it != fAsyncIO->fRecvQueue.end()) {
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
    fAsyncIO->fSockMutex->unlock();
    return rSize;
}

bool pnAsyncSocket::readAvailable() const
{
    fAsyncIO->fSockMutex->lock();
    bool hasData = !fAsyncIO->fRecvQueue.empty();
    fAsyncIO->fSockMutex->unlock();
    return hasData;
}

bool pnAsyncSocket::waitForData()
{
    while (isConnected() && !readAvailable())
        fAsyncIO->fStatusChange->wait();
    return isConnected();
}

size_t pnAsyncSocket::rsize() const
{
    fAsyncIO->fSockMutex->lock();
    size_t msgSize = 0;
    if (!fAsyncIO->fRecvQueue.empty())
        msgSize = fAsyncIO->fRecvQueue.front().fSize;
    fAsyncIO->fSockMutex->unlock();
    return msgSize;
}

bool pnAsyncSocket::isConnected() const
{
    fAsyncIO->fSockMutex->lock();
    bool done = fAsyncIO->fFinished && fAsyncIO->fRecvQueue.empty();
    fAsyncIO->fSockMutex->unlock();
    return !done;
}

void pnAsyncSocket::signalStatus() const
{
    fAsyncIO->fStatusChange->signal();
}

void pnAsyncSocket::waitForStatus() const
{
    fAsyncIO->fStatusChange->wait();
}

void pnAsyncSocket::close()
{
    fAsyncIO->fSockMutex->lock();
    fAsyncIO->fFinished = true;
    fAsyncIO->fSockMutex->unlock();
    fAsyncIO->wait();
}
