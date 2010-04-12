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

#ifndef _PNRC4_H
#define _PNRC4_H

#include "Util/plString.h"
#include "pnSocket.h"
#include "pnNetMsg.h"
#include <cstdlib>
#include <openssl/rc4.h>

enum ECryptAlgorithm {
    kCryptSha, kCryptSha1, kCryptMd5, kCryptRc4, kCryptRsa,
    kNumCryptAlgorithms
};

DllClass pnRC4Socket : public pnAsyncSocket {
protected:
    RC4_KEY fSend, fRecv;
    hsMutex fSendLock, fRecvLock;
    bool fEncrypted;

public:
    pnRC4Socket(pnSocket* sock);
    void init(size_t keySize, const unsigned char* keyData);

    long send(const void* buf, size_t size);
    long recv(void* buf, size_t size);
    long peek(void* buf, size_t size);

    NCchar_t* recvString(size_t maxlen);
    bool sendMsg(const msgparm_t* data, const pnNetMsg* msg);
    msgparm_t* recvMsg(const pnNetMsg* msg);
};

#endif
