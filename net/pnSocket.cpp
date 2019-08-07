/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "pnSocket.h"
#include "Debug/plDebug.h"
#include <cstring>

static const char* getSockErrorStr();
static int sockError();

#ifdef _WIN32
#   include <winsock2.h>
#   include <ws2tcpip.h>
#   include <wspiapi.h>

    typedef char* sockbuf_t;
    typedef const char* const_sockbuf_t;

    static WSADATA s_wsadata;

    static void closeWinsock() { WSACleanup(); }

    static int sockError() { return WSAGetLastError(); }

#   ifndef AI_ADDRCONFIG
#       define AI_ADDRCONFIG 0x0020
#   endif
#else
#   include <sys/types.h>
#   include <sys/socket.h>
#   include <sys/ioctl.h>
#   include <netinet/in.h>
#   include <netinet/tcp.h>
#   include <arpa/inet.h>
#   include <netdb.h>
#   include <poll.h>
#   include <unistd.h>
#   include <errno.h>
#   include <signal.h>

#   define closesocket ::close
#   define ioctlsocket ::ioctl
    typedef void* sockbuf_t;
    typedef const void* const_sockbuf_t;

    static int sockError() { return errno; }

#   define INVALID_SOCKET (-1)
#endif

#ifdef _MSC_VER
#   define ECONNRESET WSAECONNRESET
#endif

// For Solaris
#ifdef NEED_FILIO
#   include <sys/filio.h>
#endif

static const char* getSockErrorStr()
{
#ifdef _WIN32
    static char msgbuf[4096];

    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, nullptr, WSAGetLastError(),
                  0, msgbuf, 4096, nullptr);
    return msgbuf;
#else
    return strerror(errno);
#endif
}

static void initSockets()
{
#ifdef _WIN32
    static bool s_firstInit = true;
    if (s_firstInit) {
        WSAStartup(MAKEWORD(2, 0), &s_wsadata);
        atexit(closeWinsock);
        s_firstInit = false;
    }
#endif
}

/* pnSocket */
pnSocket::pnSocket() : fSockHandle(-1), fConnected()
{
    initSockets();
}

pnSocket::pnSocket(int handle) : fSockHandle(handle), fConnected(true)
{
    initSockets();
}

ST::string pnSocket::getRemoteIpStr() const
{
    static std::mutex ipStrMutex;

    sockaddr_in addr;
    socklen_t slen = sizeof(addr);
    std::lock_guard<std::mutex> lock(ipStrMutex);
    if (getpeername(fSockHandle, (sockaddr*)&addr, &slen) >= 0)
        return inet_ntoa(addr.sin_addr);
    return "???.???.???.???";
}

bool pnSocket::connect(const char* address, unsigned short port)
{
    addrinfo conn;
    memset(&conn, 0, sizeof(conn));
    conn.ai_flags = 0;
    conn.ai_family = AF_UNSPEC;
    conn.ai_socktype = SOCK_STREAM;
    conn.ai_protocol = 0;

    addrinfo* addr;
    int res = getaddrinfo(address, ST::format("{}", port).c_str(),
                          &conn, &addr);
    if (res != 0) {
        ST::string msg = gai_strerror(res);
        plDebug::Error("Failed to connect to {}:{}", address, port);
        plDebug::Error("    Error message was {}", msg);
        return false;
    }

    for (addrinfo* ap = addr; ap; ap = ap->ai_next) {
        fSockHandle = socket(ap->ai_family, ap->ai_socktype, ap->ai_protocol);
        if (fSockHandle != INVALID_SOCKET) {
            if (::connect(fSockHandle, ap->ai_addr, ap->ai_addrlen) != -1)
                break;
        }
        closesocket(fSockHandle);
        fSockHandle = -1;
    }

    if (fSockHandle == -1) {
        plDebug::Error("Failed to connect to {}:{}", address, port);
        return false;
    }

    freeaddrinfo(addr);
    fConnected = true;
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
    int res = getaddrinfo(nullptr, ST::format("{}", port).c_str(),
                          &conn, &addr);
    if (res != 0) {
        ST::string msg = gai_strerror(res);
        plDebug::Error("Failed to bind to port {}", port);
        plDebug::Error("    Error message was {}", msg);
        return false;
    }

    for (addrinfo* ap = addr; ap; ap = ap->ai_next) {
        fSockHandle = socket(ap->ai_family, ap->ai_socktype, ap->ai_protocol);
        if (fSockHandle != INVALID_SOCKET) {
            if (::bind(fSockHandle, ap->ai_addr, ap->ai_addrlen) == 0)
                break;
        }
        closesocket(fSockHandle);
        fSockHandle = -1;
    }

    if (fSockHandle == -1) {
        plDebug::Error("Failed to bind to port {}", port);
        return false;
    }

    freeaddrinfo(addr);
    return true;
}

pnSocket* pnSocket::listen(int backlog)
{
    if (::listen(fSockHandle, backlog) == -1) {
        if (fSockHandle != -1)
            plDebug::Error("Listen failed: {}", getSockErrorStr());
        return nullptr;
    }

    int client = accept(fSockHandle, nullptr, nullptr);
    if (client == -1) {
        if (fSockHandle != -1)
            plDebug::Error("Listen failed: {}", getSockErrorStr());
        return nullptr;
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
    fConnected = false;
}

void pnSocket::unlink()
{
    fSockHandle = -1;
    delete this;
}

long pnSocket::send(const void* buffer, size_t size)
{
    long count = ::send(fSockHandle, (const_sockbuf_t)buffer, size, 0);
    if (count == -1) {
        plDebug::Error("Send failed: {}", getSockErrorStr());
        close();
    }
    else if ((size_t)count < size)
        plDebug::Warning("Send truncated");
    return count;
}

long pnSocket::recv(void* buffer, size_t size)
{
    long count = ::recv(fSockHandle, (sockbuf_t)buffer, size, 0);
    if (count == -1 && sockError() != ECONNRESET) {
        plDebug::Error("Recv failed: {}", getSockErrorStr());
        close();
    }
    return count;
}

long pnSocket::peek(void* buffer, size_t size)
{
    long count = ::recv(fSockHandle, (sockbuf_t)buffer, size, MSG_PEEK);
    if (count == -1 && sockError() != ECONNRESET)
        plDebug::Error("Peek failed: {}", getSockErrorStr());
    return count;
}

long pnSocket::rsize()
{
#ifdef _WIN32
    unsigned long size;
#else
    int size;
#endif
    ioctlsocket(fSockHandle, FIONREAD, &size);
    return (long)size;
}

bool pnSocket::waitForData(unsigned int utimeout)
{
    if (!fConnected)
        return false;
    struct timeval stimeout;
    fd_set sread;
    FD_ZERO(&sread);
    FD_SET(fSockHandle, &sread);
    stimeout.tv_sec = 0;
    stimeout.tv_usec = utimeout;
    int si = select(fSockHandle+1, &sread, nullptr, nullptr, &stimeout);
    if (si < 0)
        close();
    return si > 0;
}

unsigned long pnSocket::GetAddress(const char* addrName)
{
    static std::mutex addrMutex;
    std::lock_guard<std::mutex> lock(addrMutex);
    hostent* host = gethostbyname(addrName);
    unsigned long numAddr = 0;
    if (host && host->h_addr_list)
        numAddr = ntohl(*(unsigned long*)host->h_addr_list[0]);
    return numAddr;
}

ST::string pnSocket::recvString(size_t maxlen)
{
    uint16_t size;
    if (recv(&size, sizeof(uint16_t)) <= 0)
        size = 0;
    if (size >= maxlen)
        size = maxlen-1;

    if (size > 0) {
        ST::utf16_buffer str;
        str.allocate(size);
        recv(str.data(), size * sizeof(char16_t));
        return ST::string::from_utf16(str);
    } else {
        return ST::string();
    }
}

static void RecvBasic(pnSocket* sock, msgparm_t& data,
                      unsigned int size, unsigned int count)
{
    // Also works for floats
    if (count == 0) {
        if (size == 1) {
            uint8_t v;
            sock->recv(&v, sizeof(uint8_t));
            data.fUint = v;
        } else if (size == 2) {
            uint16_t v;
            sock->recv(&v, sizeof(uint16_t));
            data.fUint = v;
        } else if (size == 4) {
            uint32_t v;
            sock->recv(&v, sizeof(uint32_t));
            data.fUint = v;
        }

#ifdef COMMDEBUG
        plDebug::Debug("     <- Int{}: {}", size * 8, data.fUint);
#endif
    } else {
        if (size == 1)
            sock->recv(data.fData, count * sizeof(uint8_t));
        else if (size == 2)
            sock->recv(data.fData, count * sizeof(uint16_t));
        else if (size == 4)
            sock->recv(data.fData, count * sizeof(uint32_t));

#ifdef COMMDEBUG
        ST::string ln = ST::format("     <- Int{}[{}]: ", size * 8, count);
        size_t lnbufSize = count * ((size * 2) + 1);
        char* lnbuf = new char[lnbufSize + 1];
        for (size_t i=0; i<count; i++) {
            if (size == 1)
                sprintf(lnbuf + (i * 3), "%02X ", ((uint8_t*)data.fData)[i]);
            else if (size == 2)
                sprintf(lnbuf + (i * 5), "%04X ", ((uint16_t*)data.fData)[i]);
            else if (size == 4)
                sprintf(lnbuf + (i * 9), "%08X ", ((uint32_t*)data.fData)[i]);
        }
        lnbuf[lnbufSize] = 0;
        ln += lnbuf;
        delete[] lnbuf;
        plDebug::Debug(ln.c_str());
#endif
    }
}

static void SendBasic(unsigned char*& buf, const msgparm_t& data,
                      unsigned int size, unsigned int count)
{
    // Also works for floats and doubles
    if (count == 0) {
        if (size == 1) {
            NCWriteBuffer<uint8_t>(buf, data.fUint);
        } else if (size == 2) {
            NCWriteBuffer<uint16_t>(buf, data.fUint);
        } else if (size == 4) {
            NCWriteBuffer<uint32_t>(buf, data.fUint);
        }

#ifdef COMMDEBUG
        plDebug::Debug("     -> Int{}: {}", size * 8, data.fUint);
#endif
    } else {
        if (size == 1) {
            memcpy(buf, data.fData, count * sizeof(uint8_t));
            buf += count * sizeof(uint8_t);
        } else if (size == 2) {
            memcpy(buf, data.fData, count * sizeof(uint16_t));
            buf += count * sizeof(uint16_t);
        } else if (size == 4) {
            memcpy(buf, data.fData, count * sizeof(uint32_t));
            buf += count * sizeof(uint32_t);
        }

#ifdef COMMDEBUG
        ST::string ln = ST::format("     -> Int{}[{}]: ", size * 8, count);
        size_t lnbufSize = count * ((size * 2) + 1);
        char* lnbuf = new char[lnbufSize + 1];
        for (size_t i=0; i<count; i++) {
            if (size == 1)
                sprintf(lnbuf + (i * 3), "%02X ", ((uint8_t*)data.fData)[i]);
            else if (size == 2)
                sprintf(lnbuf + (i * 5), "%04X ", ((uint16_t*)data.fData)[i]);
            else if (size == 4)
                sprintf(lnbuf + (i * 9), "%08X ", ((uint32_t*)data.fData)[i]);
        }
        lnbuf[lnbufSize] = 0;
        ln += lnbuf;
        delete[] lnbuf;
        plDebug::Debug(ln.c_str());
#endif
    }
}

bool pnSocket::sendMsg(const msgparm_t* data, const pnNetMsg* msg)
{
    if (msg == nullptr)
        return false;

#ifdef COMMDEBUG
    plDebug::Debug("<SEND> {}", msg->fMsgName);
#endif

    size_t bufSize = sizeof(uint16_t) + NCMessageSize(data, msg);
    unsigned char* buffer = new unsigned char[bufSize];
    unsigned char* bp = buffer;
    *(uint16_t*)bp = msg->fMsgId;
    bp += sizeof(uint16_t);

    unsigned int size = 0;
    unsigned int count = 0;
    for (size_t i=0; i<msg->fFieldCount; i++) {
        const pnNetMsgField* field = &msg->fFields[i];
        switch (field->fType) {
        case kFieldInteger:
        case kFieldFloat:
            SendBasic(bp, data[i], field->fSize, field->fCount);
            break;
        case kFieldString:
            {
                uint16_t len = ST::utf16_buffer::strlen(data[i].fString);
                *(uint16_t*)bp = len;
                bp += sizeof(uint16_t);
                memcpy(bp, data[i].fString, len * sizeof(char16_t));
                bp += len * sizeof(char16_t);
#ifdef COMMDEBUG
                plDebug::Debug("     -> Str: {}",
                               ST::string::from_utf16(data[i].fString, len));
#endif
            }
            break;
        case kFieldVarCount:
            size = field->fSize;
            count = data[i].fUint;
            *(uint32_t*)bp = count;
            bp += sizeof(uint32_t);
#ifdef COMMDEBUG
            plDebug::Debug("     -> Count: {}", count);
#endif
            break;
        case kFieldVarPtr:
        case kFieldRawVarPtr:
            memcpy(bp, data[i].fData, size * count);
            bp += size * count;
#ifdef COMMDEBUG
            {
                ST::string ln = "     -> VarData: ";
                char* sBuf = new char[(3 * (size * count)) + 1];
                for (size_t j=0; j<(size * count); j++)
                    sprintf(sBuf + (3*j), "%02X ", data[i].fData[j]);
                sBuf[3 * (size * count)] = 0;
                ln += sBuf;
                delete[] sBuf;
                plDebug::Debug(ln.c_str());
            }
#endif
            size = 0;
            count = 0;
            break;
        case kFieldData:
        case kFieldPtr:
        case kFieldRawData:
        case kFieldRawPtr:
            memcpy(bp, data[i].fData, field->fSize * field->fCount);
            bp += field->fSize * field->fCount;
#ifdef COMMDEBUG
            {
                ST::string ln = "     -> Data: ";
                char* sBuf = new char[(3 * (field->fSize * field->fCount)) + 1];
                for (size_t j=0; j<(field->fSize * field->fCount); j++)
                    sprintf(sBuf + (3*j), "%02X ", data[i].fData[j]);
                sBuf[3 * (field->fSize * field->fCount)] = 0;
                ln += sBuf;
                delete[] sBuf;
                plDebug::Debug(ln.c_str());
            }
#endif
            break;
        }
    }
    bool result = (send(buffer, bufSize) > 0);
    delete[] buffer;
    return result;
}

msgparm_t* pnSocket::recvMsg(const pnNetMsg* msg)
{
    if (msg == nullptr)
        return nullptr;

#ifdef COMMDEBUG
    plDebug::Debug("<RECV> {}", msg->fMsgName);
#endif
    msgparm_t* data = NCAllocMessage(msg);

    unsigned int size = 0;
    unsigned int count = 0;
    for (size_t i=0; i<msg->fFieldCount; i++) {
        const pnNetMsgField* field = &msg->fFields[i];
        switch (field->fType) {
        case kFieldInteger:
        case kFieldFloat:
            RecvBasic(this, data[i], field->fSize, field->fCount);
            break;
        case kFieldString:
            {
                uint16_t len;
                recv(&len, sizeof(uint16_t));
                char16_t* str = new char16_t[len + 1];
                recv(str, len * sizeof(char16_t));
                str[len] = 0;
                data[i].fString = str;
#ifdef COMMDEBUG
                plDebug::Debug("     <- Str: {}", ST::string::from_utf16(data[i].fString, len));
#endif
            }
            break;
        case kFieldVarCount:
            size = field->fSize;
            recv(&count, sizeof(uint32_t));
            data[i].fUint = count;
#ifdef COMMDEBUG
            plDebug::Debug("     <- Count: {}", count);
#endif
            break;
        case kFieldVarPtr:
        case kFieldRawVarPtr:
            delete[] data[i].fData;
            data[i].fData = new uint8_t[size * count];
            recv(data[i].fData, size * count);
#ifdef COMMDEBUG
            {
                ST::string ln = "     <- VarData: ";
                char* sBuf = new char[(3 * (size * count)) + 1];
                for (size_t j=0; j<(size * count); j++)
                    sprintf(sBuf + (3*j), "%02X ", data[i].fData[j]);
                sBuf[3 * (size * count)] = 0;
                ln += sBuf;
                delete[] sBuf;
                plDebug::Debug(ln.c_str());
            }
#endif
            size = 0;
            count = 0;
            break;
        case kFieldData:
        case kFieldPtr:
        case kFieldRawData:
        case kFieldRawPtr:
            recv(data[i].fData, field->fSize * field->fCount);
#ifdef COMMDEBUG
            {
                ST::string ln = "     <- Data: ";
                char* sBuf = new char[(3 * (field->fSize * field->fCount)) + 1];
                for (size_t j=0; j<(field->fSize * field->fCount); j++)
                    sprintf(sBuf + (3*j), "%02X ", data[i].fData[j]);
                sBuf[3 * (field->fSize * field->fCount)] = 0;
                ln += sBuf;
                delete[] sBuf;
                plDebug::Debug(ln.c_str());
            }
#endif
            break;
        }
    }
    return data;
}
