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
#include "pnNetMsg.h"
#include <cstdlib>
#include <list>
#include <string_theory/string>

class PLASMANET_DLL pnSocket
{
protected:
    int fSockHandle;
    bool fConnected;

public:
    pnSocket();
    pnSocket(int handle);
    virtual ~pnSocket() { close(); }

    ST::string getRemoteIpStr() const;
    int getHandle() const { return fSockHandle; }

    bool connect(const char* address, unsigned short port);
    bool bind(unsigned short port);
    pnSocket* listen(int backlog);
    void close(bool force=false);
    void unlink();
    void link(int handle) { fSockHandle = handle; }

    virtual long send(const void* buffer, size_t size);
    virtual long recv(void* buffer, size_t size);
    virtual long peek(void* buffer, size_t size);
    long rsize();

    ST::string recvString(size_t maxlen);
    bool sendMsg(const msgparm_t* data, const pnNetMsg* msg);
    msgparm_t* recvMsg(const pnNetMsg* msg);

    bool isConnected() const { return fConnected; }
    bool waitForData(unsigned int utimeout = 500000);

    static unsigned long GetAddress(const char* addrName);
};

#endif
