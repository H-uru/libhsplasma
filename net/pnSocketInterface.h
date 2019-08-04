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

#ifndef _PNSOCKETINTERFACE_H
#define _PNSOCKETINTERFACE_H

#include "PlasmaDefs.h"

class pnSocket;

class pnDispatcher
{
public:
    pnDispatcher() { }
    virtual ~pnDispatcher() { }
    virtual bool dispatch(pnSocket* /*sock*/) { return false; }
};

class pnSocketInterface
{
public:
    pnSocketInterface(pnDispatcher* dispatch, pnSocket* sock)
        : fDispatch(dispatch), fSock(sock) { }
    virtual ~pnSocketInterface() { }
    virtual void run() = 0;

protected:
    pnDispatcher* fDispatch;
    pnSocket* fSock;
};

class pnThreadHelper;

class pnThreadedSocket : public pnSocketInterface
{
public:
    pnThreadedSocket(pnDispatcher* dispatch, pnSocket* sock)
        : pnSocketInterface(dispatch, sock), fHelper() { }
    ~pnThreadedSocket();
    void run() HS_OVERRIDE;

protected:
    pnThreadHelper* fHelper;
};

class pnPolledSocket : public pnSocketInterface
{
public:
    pnPolledSocket(pnDispatcher* dispatch, pnSocket* sock)
        : pnSocketInterface(dispatch, sock) { }
    ~pnPolledSocket() { }
    void run() HS_OVERRIDE;
};

#endif
