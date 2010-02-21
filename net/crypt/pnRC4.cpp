#include "pnRC4.h"
#include "Debug/plDebug.h"

pnRC4Socket::pnRC4Socket(pnSocket* sock)
           : pnAsyncSocket(sock), fEncrypted(false)
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
        sSize = pnAsyncSocket::send(buf, size);
    } else {
        unsigned char* cBuf = new unsigned char[size];
        fSendLock.lock();
        RC4(&fSend, size, (const unsigned char*)buf, cBuf);
        sSize = pnAsyncSocket::send(cBuf, size);
        fSendLock.unlock();
        delete[] cBuf;
    }
    return sSize;
}

long pnRC4Socket::recv(void* buf, size_t size)
{
    long rSize;
    if (!fEncrypted) {
        rSize = pnAsyncSocket::recv(buf, size);
    } else {
        fRecvLock.lock();
        rSize = pnAsyncSocket::recv(buf, size);
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
        return pnAsyncSocket::peek(buf, size);

    throw hsBadParamException(__FILE__, __LINE__, "Cannot peek on an encrypted socket");
}

NCchar_t* pnRC4Socket::recvString(size_t maxlen)
{
    NCchar_t* str = new NCchar_t[maxlen];
    memset(str, 0, maxlen * sizeof(NCchar_t));

    hsUint16 size;
    if (recv(&size, sizeof(hsUint16)) <= 0)
        size = 0;

    if (size > 0) {
        NCchar_t* buf = new NCchar_t[size];
        recv(buf, size * sizeof(NCchar_t));
        memcpy(str, buf, (size >= maxlen ? maxlen-1 : size) * sizeof(NCchar_t));
        delete[] buf;
    }

    return str;
}

static void RecvBasic(pnRC4Socket* sock, msgparm_t& data,
                      unsigned int size, unsigned int count)
{
    // Also works for floats
    if (count == 0) {
        if (size == 1) {
            hsUbyte v;
            sock->recv(&v, sizeof(hsUbyte));
            data.fUint = v;
        } else if (size == 2) {
            hsUint16 v;
            sock->recv(&v, sizeof(hsUint16));
            data.fUint = v;
        } else if (size == 4) {
            hsUint32 v;
            sock->recv(&v, sizeof(hsUint32));
            data.fUint = v;
        }

#ifdef COMMDEBUG
        plDebug::Debug("     <- Int%d: %lu", size * 8, data);
#endif
    } else {
        if (size == 1)
            sock->recv(data.fData, count * sizeof(hsUbyte));
        else if (size == 2)
            sock->recv(data.fData, count * sizeof(hsUint16));
        else if (size == 4)
            sock->recv(data.fData, count * sizeof(hsUint32));

#ifdef COMMDEBUG
        plString ln = plString::Format("     <- Int%d[%d]: ", size * 8, count);
        size_t lnbufSize = count * ((size * 2) + 1);
        char* lnbuf = new char[lnbufSize + 1];
        for (size_t i=0; i<count; i++) {
            if (size == 1)
                sprintf(lnbuf + (i * 3), "%02X ", ((hsUbyte*)data.fData)[i]);
            else if (size == 2)
                sprintf(lnbuf + (i * 5), "%04X ", ((hsUint16*)data.fData)[i]);
            else if (size == 4)
                sprintf(lnbuf + (i * 9), "%08X ", ((hsUint32*)data.fData)[i]);
        }
        lnbuf[lnbufSize] = 0;
        ln += lnbuf;
        delete[] lnbuf;
        plDebug::Debug(ln.cstr());
#endif
    }
}

static void SendBasic(unsigned char*& buf, const msgparm_t& data,
                      unsigned int size, unsigned int count)
{
    // Also works for floats and doubles
    if (count == 0) {
        if (size == 1) {
            *(hsUbyte*)buf = (hsUbyte)data.fUint;
            buf += sizeof(hsUbyte);
        } else if (size == 2) {
            *(hsUint16*)buf = (hsUint16)data.fUint;
            buf += sizeof(hsUint16);
        } else if (size == 4) {
            *(hsUint32*)buf = data.fUint;
            buf += sizeof(hsUint32);
        }

#ifdef COMMDEBUG
        plDebug::Debug("     -> Int%d: %lu", size * 8, data);
#endif
    } else {
        if (size == 1) {
            memcpy(buf, data.fData, count * sizeof(hsUbyte));
            buf += count * sizeof(hsUbyte);
        } else if (size == 2) {
            memcpy(buf, data.fData, count * sizeof(hsUint16));
            buf += count * sizeof(hsUint16);
        } else if (size == 4) {
            memcpy(buf, data.fData, count * sizeof(hsUint32));
            buf += count * sizeof(hsUint32);
        }

#ifdef COMMDEBUG
        plString ln = plString::Format("     <- Int%d[%d]: ", size * 8, count);
        size_t lnbufSize = count * ((size * 2) + 1);
        char* lnbuf = new char[lnbufSize + 1];
        for (size_t i=0; i<count; i++) {
            if (size == 1)
                sprintf(lnbuf + (i * 3), "%02X ", ((hsUbyte*)data.fData)[i]);
            else if (size == 2)
                sprintf(lnbuf + (i * 5), "%04X ", ((hsUint16*)data.fData)[i]);
            else if (size == 4)
                sprintf(lnbuf + (i * 9), "%08X ", ((hsUint32*)data.fData)[i]);
        }
        lnbuf[lnbufSize] = 0;
        ln += lnbuf;
        delete[] lnbuf;
        plDebug::Debug(ln.cstr());
#endif
    }
}

bool pnRC4Socket::sendMsg(const msgparm_t* data, const pnNetMsg* msg)
{
    if (msg == NULL)
        return false;

#ifdef COMMDEBUG
    plDebug::Debug("<SEND> %s", msg->fMsgName);
#endif

    size_t bufSize = sizeof(hsUint16) + NCMessageSize(data, msg);
    unsigned char* buffer = new unsigned char[bufSize];
    unsigned char* bp = buffer;
    *(hsUint16*)bp = msg->fMsgId;
    bp += sizeof(hsUint16);

    unsigned int size = 0;
    unsigned int count = 0;
    for (size_t i=0; i<msg->fFieldCount; i++) {
        const pnNetMsgField* field = &msg->fFields[i];
        switch (field->fType) {
        case kFieldInteger:
        case kFieldFloat:
            SendBasic(bp, data[i], field->fSize, field->fCount);
            break;
        case kFieldString:
            {
                hsUint16 len = NCstrlen(data[i].fString);
                *(hsUint16*)bp = len;
                bp += sizeof(hsUint16);
                memcpy(bp, data[i].fData, len * sizeof(NCchar_t));
                bp += len * sizeof(NCchar_t);
#ifdef COMMDEBUG
                plDebug::Debug("     -> Str: %s",
                               NCstrToString(data[i].fString).cstr());
#endif
            }
            break;
        case kFieldVarCount:
            size = field->fSize;
            count = data[i].fUint;
            *(hsUint32*)bp = count;
            bp += sizeof(hsUint32);
#ifdef COMMDEBUG
            plDebug::Debug("     -> Count: %d", count);
#endif
            break;
        case kFieldVarPtr:
        case kFieldRawVarPtr:
            memcpy(bp, data[i].fData, size * count);
            bp += size * count;
#ifdef COMMDEBUG
            {
                plString ln = "     -> VarData: ";
                char* sBuf = new char[(3 * (size * count)) + 1];
                for (size_t j=0; j<(size * count); j++)
                    sprintf(sBuf + (3*j), "%02X ", data[i].fData[j]);
                sBuf[3 * (size * count)] = 0;
                ln += sBuf;
                delete[] sBuf;
                plDebug::Debug(ln.cstr());
            }
#endif
            size = 0;
            count = 0;
            break;
        case kFieldData:
        case kFieldPtr:
        case kFieldRawData:
        case kFieldRawPtr:
            memcpy(bp, data[i].fData, field->fSize * field->fCount);
            bp += field->fSize * field->fCount;
#ifdef COMMDEBUG
            {
                plString ln = "     -> Data: ";
                char* sBuf = new char[(3 * (field->fSize * field->fCount)) + 1];
                for (size_t j=0; j<(field->fSize * field->fCount); j++)
                    sprintf(sBuf + (3*j), "%02X ", data[i].fData[j]);
                sBuf[3 * (field->fSize * field->fCount)] = 0;
                ln += sBuf;
                delete[] sBuf;
                plDebug::Debug(ln.cstr());
            }
#endif
            break;
        }
    }
    bool result = (send(buffer, bufSize) > 0);
    delete[] buffer;
    return result;
}

msgparm_t* pnRC4Socket::recvMsg(const pnNetMsg* msg)
{
    if (msg == NULL)
        return NULL;

#ifdef COMMDEBUG
    plDebug::Debug("<RECV> %s", msg->fMsgName);
#endif
    msgparm_t* data = NCAllocMessage(msg);

    unsigned int size = 0;
    unsigned int count = 0;
    for (size_t i=0; i<msg->fFieldCount; i++) {
        const pnNetMsgField* field = &msg->fFields[i];
        switch (field->fType) {
        case kFieldInteger:
        case kFieldFloat:
            RecvBasic(this, data[i], field->fSize, field->fCount);
            break;
        case kFieldString:
            {
                hsUint16 len;
                recv(&len, sizeof(hsUint16));
                NCchar_t* str = new NCchar_t[len + 1];
                recv(str, len * sizeof(NCchar_t));
                str[len] = 0;
                data[i].fString = str;
#ifdef COMMDEBUG
                plDebug::Debug("     <- Str: %s",
                               NCstrToString(data[i].fString).cstr());
#endif
            }
            break;
        case kFieldVarCount:
            size = field->fSize;
            recv(&count, sizeof(hsUint32));
            data[i].fUint = count;
#ifdef COMMDEBUG
            plDebug::Debug("     <- Count: %d", count);
#endif
            break;
        case kFieldVarPtr:
        case kFieldRawVarPtr:
            if (data[i].fData != NULL)
                delete[] data[i].fData;
            data[i].fData = new hsUbyte[size * count];
            recv(data[i].fData, size * count);
#ifdef COMMDEBUG
            {
                plString ln = "     <- VarData: ";
                char* sBuf = new char[(3 * (size * count)) + 1];
                for (size_t j=0; j<(size * count); j++)
                    sprintf(sBuf + (3*j), "%02X ", data[i].fData[j]);
                sBuf[3 * (size * count)] = 0;
                ln += sBuf;
                delete[] sBuf;
                plDebug::Debug(ln.cstr());
            }
#endif
            size = 0;
            count = 0;
            break;
        case kFieldData:
        case kFieldPtr:
        case kFieldRawData:
        case kFieldRawPtr:
            recv(data[i].fData, field->fSize * field->fCount);
#ifdef COMMDEBUG
            {
                plString ln = "     <- Data: ";
                char* sBuf = new char[(3 * (field->fSize * field->fCount)) + 1];
                for (size_t j=0; j<(field->fSize * field->fCount); j++)
                    sprintf(sBuf + (3*j), "%02X ", data[i].fData[j]);
                sBuf[3 * (field->fSize * field->fCount)] = 0;
                ln += sBuf;
                delete[] sBuf;
                plDebug::Debug(ln.cstr());
            }
#endif
            break;
        }
    }
    return data;
}
