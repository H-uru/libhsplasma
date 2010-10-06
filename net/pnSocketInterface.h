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

class pnSocket;

class pnDispatcher {
public:
    virtual bool dispatch(pnSocket* sock) = 0;
};

class pnSocketInterface {
public:
    pnSocketInterface(pnDispatcher* dispatch, pnSocket* sock);
    virtual ~pnSocketInterface();
    virtual void run() = 0;

protected:
    pnDispatcher* fDispatch;
    pnSocket* fSock;
};

class pnThreadHelper;

class pnThreadedSocket : public pnSocketInterface {
public:
    pnThreadedSocket(pnDispatcher* dispatch, pnSocket* sock);
    virtual ~pnThreadedSocket();
    virtual void run();

protected:
    pnThreadHelper* fHelper;
};

class pnPolledSocket : public pnSocketInterface {
public:
    pnPolledSocket(pnDispatcher* dispatch, pnSocket* sock);
    virtual ~pnPolledSocket();
    virtual void run();
};

#endif
