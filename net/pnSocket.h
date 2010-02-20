#ifndef _PNSOCKET_H
#define _PNSOCKET_H

#include "Sys/hsThread.h"
#include "Util/plString.h"
#include <cstdlib>
#include <list>

class pnSocket {
protected:
    int fSockHandle;

public:
    pnSocket();
    pnSocket(int handle);
    ~pnSocket();

    plString getRemoteIpStr() const;
    int getHandle() const;

    bool connect(const char* address, unsigned short port);
    bool bind(unsigned short port);
    pnSocket* listen(int backlog);
    void close(bool force=false);
    void unlink();
    void link(int handle);

    ssize_t send(const void* buffer, size_t size);
    ssize_t recv(void* buffer, size_t size);
    ssize_t peek(void* buffer, size_t size);
    ssize_t rsize();

    static unsigned long GetAddress(const char* addrName);
};

class pnAsyncSocket {
private:
    class _async : public hsThread {
    public:
        struct _datum {
            unsigned char* fData;
            size_t fSize;
        };

        std::list<_datum> fSendQueue, fRecvQueue;
        hsMutex fSockMutex;
        pnSocket* fSock;
        size_t fReadPos;

    public:
        _async();
        ~_async();
        virtual void initialize();
        virtual void finalize();

        void flush();

    protected:
        virtual void run();
    } fAsyncIO;

public:
    pnAsyncSocket(pnSocket* sock);   // Steals the socket
    ~pnAsyncSocket();

    ssize_t send(const void* buffer, size_t size);
    ssize_t recv(void* buffer, size_t size);
    ssize_t peek(void* buffer, size_t size);
    void flush();
    bool readAvailable() const;
    bool waitForData();
    bool isConnected() const;

    void close(bool force=false);
};

#endif
