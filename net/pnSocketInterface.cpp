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

#include "pnSocketInterface.h"

#include <Sys/hsThread.h>
#include "pnSocket.h"

pnDispatcher::pnDispatcher()
{ }

pnDispatcher::~pnDispatcher()
{ }

bool pnDispatcher::dispatch(pnSocket* /*sock*/)
{
    return false;
}


pnSocketInterface::pnSocketInterface(pnDispatcher* dispatch, pnSocket* sock)
                 : fDispatch(dispatch), fSock(sock)
{ }

pnSocketInterface::~pnSocketInterface()
{ }

class pnThreadHelper : public hsThread {
public:
    pnThreadHelper(pnSocket* sock, pnDispatcher* dispatch);
    virtual ~pnThreadHelper();
    void stop();

private:
    virtual void run();

    pnDispatcher* fReceiver;
    pnSocket* fSock;
    volatile bool fRunning;
};

pnThreadHelper::pnThreadHelper(pnSocket* sock, pnDispatcher* dispatch)
              : fReceiver(dispatch), fSock(sock)
{ }

pnThreadHelper::~pnThreadHelper()
{ }

void pnThreadHelper::run()
{
    fRunning = true;
    while (fRunning && fSock->isConnected()) {
        if (!fSock->waitForData())
            continue;
        // close the socket if anything fails
        if (!fReceiver->dispatch(fSock))
            fSock->close();
    }
}

void pnThreadHelper::stop()
{ 
    if (!isFinished()) {
        fRunning = false; 
        wait(); 
    }
}

pnThreadedSocket::pnThreadedSocket(pnDispatcher* dispatch, pnSocket* sock)
                : pnSocketInterface(dispatch, sock), fHelper(NULL)
{ }

pnThreadedSocket::~pnThreadedSocket()
{
    fHelper->stop();
    delete fHelper;
}


void pnThreadedSocket::run()
{
    if (!fHelper) {
        fHelper = new pnThreadHelper(fSock, fDispatch);
        fHelper->start();
    }
}

pnPolledSocket::pnPolledSocket(pnDispatcher* dispatch, pnSocket* sock)
              : pnSocketInterface(dispatch, sock)
{ }

pnPolledSocket::~pnPolledSocket()
{ }

void pnPolledSocket::run()
{
    if (fSock->isConnected()) {
        while (fSock->waitForData(0)) {
            if (!fDispatch->dispatch(fSock)) {
                // close the socket if anything fails
                fSock->close();
            }
        }
    }
}
