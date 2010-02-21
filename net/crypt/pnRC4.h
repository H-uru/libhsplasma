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
