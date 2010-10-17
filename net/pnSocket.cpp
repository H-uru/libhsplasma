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

static const char* getSockErrorStr();
static int sockError();

#ifdef WIN32
#   include <winsock2.h>
#   include <ws2tcpip.h>
#   include <wspiapi.h>

    typedef char* sockbuf_t;

    static WSADATA s_wsadata;

    static void closeWinsock()
    { WSACleanup(); }

    static int sockError()
    { return WSAGetLastError(); }

#   ifndef AI_ADDRCONFIG
#       define AI_ADDRCONFIG 0x0020
#   endif

#   define ECONNRESET WSAECONNRESET
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

    static int sockError()
    { return errno; }

#   define INVALID_SOCKET (-1)
#endif

// For Solaris
#ifdef NEED_FILIO
#   include <sys/filio.h>
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
        : fSockHandle(-1), fConnected(false)
{
    initSockets();
}

pnSocket::pnSocket(int handle)
        : fSockHandle(handle), fConnected(true)
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

bool pnSocket::connect(const char* address, unsigned short port)
{
    addrinfo conn;
    memset(&conn, 0, sizeof(conn));
    conn.ai_flags = 0;
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
    fConnected = false;
}

void pnSocket::unlink()
{
    fSockHandle = -1;
    delete this;
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
    int si = select(fSockHandle+1, &sread, NULL, NULL, &stimeout);
    if (si < 0)
        close();
    return si > 0;
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

plString pnSocket::recvString(size_t maxlen)
{
    hsUint16 size;
    if (recv(&size, sizeof(hsUint16)) <= 0)
        size = 0;
    if (size >= maxlen)
        size = maxlen-1;

    if (size > 0) {
        pl_wchar_t* buf = new pl_wchar_t[size];
        recv(buf, size * sizeof(pl_wchar_t));
        plString str(buf, size);
        delete[] buf;
        return str;
    } else {
        return plString();
    }
}

static void RecvBasic(pnSocket* sock, msgparm_t& data,
                      unsigned int size, unsigned int count)
{
    // Also works for floats
    if (count == 0) {
        if (size == 1) {
            hsUbyte v;
            sock->recv(&v, sizeof(hsUbyte));
            data.fUint = v;
        } else if (size == 2) {
            hsUint16 v;
            sock->recv(&v, sizeof(hsUint16));
            data.fUint = v;
        } else if (size == 4) {
            hsUint32 v;
            sock->recv(&v, sizeof(hsUint32));
            data.fUint = v;
        }

#ifdef COMMDEBUG
        plDebug::Debug("     <- Int%d: %lu", size * 8, data.fUint);
#endif
    } else {
        if (size == 1)
            sock->recv(data.fData, count * sizeof(hsUbyte));
        else if (size == 2)
            sock->recv(data.fData, count * sizeof(hsUint16));
        else if (size == 4)
            sock->recv(data.fData, count * sizeof(hsUint32));

#ifdef COMMDEBUG
        plString ln = plString::Format("     <- Int%d[%d]: ", size * 8, count);
        size_t lnbufSize = count * ((size * 2) + 1);
        char* lnbuf = new char[lnbufSize + 1];
        for (size_t i=0; i<count; i++) {
            if (size == 1)
                sprintf(lnbuf + (i * 3), "%02X ", ((hsUbyte*)data.fData)[i]);
            else if (size == 2)
                sprintf(lnbuf + (i * 5), "%04X ", ((hsUint16*)data.fData)[i]);
            else if (size == 4)
                sprintf(lnbuf + (i * 9), "%08X ", ((hsUint32*)data.fData)[i]);
        }
        lnbuf[lnbufSize] = 0;
        ln += lnbuf;
        delete[] lnbuf;
        plDebug::Debug(ln.cstr());
#endif
    }
}

static void SendBasic(unsigned char*& buf, const msgparm_t& data,
                      unsigned int size, unsigned int count)
{
    // Also works for floats and doubles
    if (count == 0) {
        if (size == 1) {
            *(hsUbyte*)buf = (hsUbyte)data.fUint;
            buf += sizeof(hsUbyte);
        } else if (size == 2) {
            *(hsUint16*)buf = (hsUint16)data.fUint;
            buf += sizeof(hsUint16);
        } else if (size == 4) {
            *(hsUint32*)buf = data.fUint;
            buf += sizeof(hsUint32);
        }

#ifdef COMMDEBUG
        plDebug::Debug("     -> Int%d: %lu", size * 8, data.fUint);
#endif
    } else {
        if (size == 1) {
            memcpy(buf, data.fData, count * sizeof(hsUbyte));
            buf += count * sizeof(hsUbyte);
        } else if (size == 2) {
            memcpy(buf, data.fData, count * sizeof(hsUint16));
            buf += count * sizeof(hsUint16);
        } else if (size == 4) {
            memcpy(buf, data.fData, count * sizeof(hsUint32));
            buf += count * sizeof(hsUint32);
        }

#ifdef COMMDEBUG
        plString ln = plString::Format("     -> Int%d[%d]: ", size * 8, count);
        size_t lnbufSize = count * ((size * 2) + 1);
        char* lnbuf = new char[lnbufSize + 1];
        for (size_t i=0; i<count; i++) {
            if (size == 1)
                sprintf(lnbuf + (i * 3), "%02X ", ((hsUbyte*)data.fData)[i]);
            else if (size == 2)
                sprintf(lnbuf + (i * 5), "%04X ", ((hsUint16*)data.fData)[i]);
            else if (size == 4)
                sprintf(lnbuf + (i * 9), "%08X ", ((hsUint32*)data.fData)[i]);
        }
        lnbuf[lnbufSize] = 0;
        ln += lnbuf;
        delete[] lnbuf;
        plDebug::Debug(ln.cstr());
#endif
    }
}

bool pnSocket::sendMsg(const msgparm_t* data, const pnNetMsg* msg)
{
    if (msg == NULL)
        return false;

#ifdef COMMDEBUG
    plDebug::Debug("<SEND> %s", msg->fMsgName);
#endif

    size_t bufSize = sizeof(hsUint16) + NCMessageSize(data, msg);
    unsigned char* buffer = new unsigned char[bufSize];
    unsigned char* bp = buffer;
    *(hsUint16*)bp = msg->fMsgId;
    bp += sizeof(hsUint16);

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
                hsUint16 len = plwcslen(data[i].fString);
                *(hsUint16*)bp = len;
                bp += sizeof(hsUint16);
                memcpy(bp, data[i].fString, len * sizeof(pl_wchar_t));
                bp += len * sizeof(pl_wchar_t);
#ifdef COMMDEBUG
                plDebug::Debug("     -> Str: %s", plString(data[i].fString, len).cstr());
#endif
            }
            break;
        case kFieldVarCount:
            size = field->fSize;
            count = data[i].fUint;
            *(hsUint32*)bp = count;
            bp += sizeof(hsUint32);
#ifdef COMMDEBUG
            plDebug::Debug("     -> Count: %d", count);
#endif
            break;
        case kFieldVarPtr:
        case kFieldRawVarPtr:
            memcpy(bp, data[i].fData, size * count);
            bp += size * count;
#ifdef COMMDEBUG
            {
                plString ln = "     -> VarData: ";
                char* sBuf = new char[(3 * (size * count)) + 1];
                for (size_t j=0; j<(size * count); j++)
                    sprintf(sBuf + (3*j), "%02X ", data[i].fData[j]);
                sBuf[3 * (size * count)] = 0;
                ln += sBuf;
                delete[] sBuf;
                plDebug::Debug(ln.cstr());
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
                plString ln = "     -> Data: ";
                char* sBuf = new char[(3 * (field->fSize * field->fCount)) + 1];
                for (size_t j=0; j<(field->fSize * field->fCount); j++)
                    sprintf(sBuf + (3*j), "%02X ", data[i].fData[j]);
                sBuf[3 * (field->fSize * field->fCount)] = 0;
                ln += sBuf;
                delete[] sBuf;
                plDebug::Debug(ln.cstr());
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
    if (msg == NULL)
        return NULL;

#ifdef COMMDEBUG
    plDebug::Debug("<RECV> %s", msg->fMsgName);
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
                hsUint16 len;
                recv(&len, sizeof(hsUint16));
                pl_wchar_t* str = new pl_wchar_t[len + 1];
                recv(str, len * sizeof(pl_wchar_t));
                str[len] = 0;
                data[i].fString = str;
#ifdef COMMDEBUG
                plDebug::Debug("     <- Str: %s", plString(data[i].fString, len).cstr());
#endif
            }
            break;
        case kFieldVarCount:
            size = field->fSize;
            recv(&count, sizeof(hsUint32));
            data[i].fUint = count;
#ifdef COMMDEBUG
            plDebug::Debug("     <- Count: %d", count);
#endif
            break;
        case kFieldVarPtr:
        case kFieldRawVarPtr:
            delete[] data[i].fData;
            data[i].fData = new hsUbyte[size * count];
            recv(data[i].fData, size * count);
#ifdef COMMDEBUG
            {
                plString ln = "     <- VarData: ";
                char* sBuf = new char[(3 * (size * count)) + 1];
                for (size_t j=0; j<(size * count); j++)
                    sprintf(sBuf + (3*j), "%02X ", data[i].fData[j]);
                sBuf[3 * (size * count)] = 0;
                ln += sBuf;
                delete[] sBuf;
                plDebug::Debug(ln.cstr());
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
                plString ln = "     <- Data: ";
                char* sBuf = new char[(3 * (field->fSize * field->fCount)) + 1];
                for (size_t j=0; j<(field->fSize * field->fCount); j++)
                    sprintf(sBuf + (3*j), "%02X ", data[i].fData[j]);
                sBuf[3 * (field->fSize * field->fCount)] = 0;
                ln += sBuf;
                delete[] sBuf;
                plDebug::Debug(ln.cstr());
            }
#endif
            break;
        }
    }
    return data;
}
