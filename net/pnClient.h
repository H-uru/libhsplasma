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

#ifndef _PNCLIENT_H
#define _PNCLIENT_H

#include "PlasmaDefs.h"
#include "Protocol.h"
#include "Sys/hsThread.h"

class pnSocketInterface;

class PLASMANET_DLL pnClient
{
public:
    pnClient() : fIface() { }
    virtual ~pnClient();

    virtual ENetError connect(const char* host, short port = 14617) = 0;
    virtual ENetError connect(int sockFd) = 0;
    virtual void disconnect() = 0;
    virtual bool isConnected() const = 0;

    // The exact semantics of this depend on what the subclass has set
    // as the SocketInterface - normally it does nothing, or loops until
    // there's no more data available to read.
    void run();

    //virtual void signalStatus() = 0;
    //virtual void waitForStatus() = 0;

protected:
    uint32_t nextTransId();
    pnSocketInterface *fIface;
};

#endif
