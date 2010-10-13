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

#include "pnRC4.h"
#include "Debug/plDebug.h"

pnRC4Socket::pnRC4Socket()
           : fEncrypted(false)
{ }

pnRC4Socket::pnRC4Socket(int handle)
           : pnSocket(handle), fEncrypted(false)
{ }


void pnRC4Socket::init(size_t keySize, const unsigned char* keyData)
{
    if (keyData != NULL) {
        RC4_set_key(&fSend, keySize, keyData);
        RC4_set_key(&fRecv, keySize, keyData);
        fEncrypted = true;
    } else {
        fEncrypted = false;
    }
}

long pnRC4Socket::send(const void* buf, size_t size)
{
    long sSize;
    if (!fEncrypted) {
        sSize = pnSocket::send(buf, size);
    } else {
        unsigned char* cBuf = new unsigned char[size];
        fSendLock.lock();
        RC4(&fSend, size, (const unsigned char*)buf, cBuf);
        sSize = pnSocket::send(cBuf, size);
        fSendLock.unlock();
        delete[] cBuf;
    }
    return sSize;
}

long pnRC4Socket::recv(void* buf, size_t size)
{
    size_t rSize = 0;
    if (!fEncrypted) {
        while(rSize < size)
            rSize += pnSocket::recv((hsByte*)buf+rSize, size-rSize);
    } else {
        fRecvLock.lock();
        while(rSize < size)
          rSize += pnSocket::recv((hsByte*)buf+rSize, size-rSize);
        if (rSize > 0) {
            unsigned char* cBuf = new unsigned char[rSize];
            RC4(&fRecv, rSize, (const unsigned char*)buf, cBuf);
            memcpy(buf, cBuf, rSize);
            delete[] cBuf;
        }
        fRecvLock.unlock();
    }

    return rSize;
}

long pnRC4Socket::peek(void* buf, size_t size)
{
    if (!fEncrypted)
        return pnSocket::peek(buf, size);

    throw hsBadParamException(__FILE__, __LINE__, "Cannot peek on an encrypted socket");
}
