#ifndef _PNSOCKET_H
#define _PNSOCKET_H

#include "Sys/hsThread.h"
#include "Util/plString.h"
#include <cstdlib>
#include <list>

DllClass pnSocket {
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

    long send(const void* buffer, size_t size);
    long recv(void* buffer, size_t size);
    long peek(void* buffer, size_t size);
    long rsize();

    static unsigned long GetAddress(const char* addrName);
};

DllClass pnAsyncSocket {
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
        bool fFinished;

    public:
        _async();
        ~_async();

        void flush();
        void finish();

    protected:
        virtual void run();
    } fAsyncIO;

public:
    pnAsyncSocket(pnSocket* sock);   // Steals the socket
    ~pnAsyncSocket();

    long send(const void* buffer, size_t size);
    long recv(void* buffer, size_t size);
    long peek(void* buffer, size_t size);
    void flush();
    bool readAvailable() const;
    bool waitForData();
    bool isConnected() const;

    void close(bool force=false);
};

#endif
