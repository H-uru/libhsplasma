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
    int getHandle() const { return fSockHandle; }

    bool connect(const char* address, unsigned short port);
    bool bind(unsigned short port);
    pnSocket* listen(int backlog);
    void close(bool force=false);
    void unlink();
    void link(int handle) { fSockHandle = handle; }

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

        std::list<_datum> fRecvQueue;
        hsMutex* fSockMutex;
        hsThreadCondition* fStatusChange;
        pnSocket* fSock;
        size_t fReadPos;
        bool fFinished;

    public:
        _async();
        virtual void destroy();

    protected:
        virtual void run();
    } *fAsyncIO;

public:
    pnAsyncSocket(pnSocket* sock);   // Steals the socket
    ~pnAsyncSocket();

    long send(const void* buffer, size_t size);
    long recv(void* buffer, size_t size);
    long peek(void* buffer, size_t size);
    bool readAvailable() const;
    bool waitForData();
    size_t rsize() const;
    bool isConnected() const;
    void signalStatus() const { fAsyncIO->fStatusChange->signal(); }
    void waitForStatus() const { fAsyncIO->fStatusChange->wait(); }

    void close();
};

#endif
