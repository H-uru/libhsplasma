#include "pnSha1.h"
#include "pnNetMsg.h"
#include "Debug/hsExceptions.h"
#include <openssl/sha.h>

void pnSha1Hash::fromString(const plString& src)
{
    if (src.len() != 40)
        throw hsBadParamException(__FILE__, __LINE__, "Invalid SHA1 string");

    fData[0] = src.mid(0, 8).toUint(16);
    fData[1] = src.mid(8, 8).toUint(16);
    fData[2] = src.mid(16, 8).toUint(16);
    fData[3] = src.mid(24, 8).toUint(16);
    fData[4] = src.mid(32, 8).toUint(16);
}

plString pnSha1Hash::toString() const
{
    return plString::Format("%08x%08x%08x%08x%08x",
                            fData[0], fData[1], fData[2], fData[3], fData[4]);
}

pnSha1Hash pnSha1Hash::Sha0(const void* src, size_t len)
{
    pnSha1Hash hash;
    SHA((const unsigned char*)src, len, (unsigned char*)hash.fData);
    return hash;
}

pnSha1Hash pnSha1Hash::Sha1(const void* src, size_t len)
{
    pnSha1Hash hash;
    SHA1((const unsigned char*)src, len, (unsigned char*)hash.fData);
    return hash;
}

pnSha1Hash NCHashPassword(const plString& userName, const plString& password)
{
    NCchar_t* userBuf = StringToNCstr(userName);
    NCchar_t* passBuf = StringToNCstr(password);
    NCstrlower(userBuf);
    size_t userLen = NCstrlen(userBuf);
    size_t passLen = NCstrlen(passBuf);
    NCchar_t* hashBuf = new NCchar_t[userLen + passLen];
    memcpy(hashBuf, passBuf, passLen * sizeof(NCchar_t));
    memcpy(hashBuf + passLen, userBuf, userLen * sizeof(NCchar_t));
    hashBuf[passLen - 1] = 0;
    hashBuf[(passLen + userLen) - 1] = 0;
    pnSha1Hash result = pnSha1Hash::Sha0(hashBuf, (userLen + passLen) * sizeof(NCchar_t));
    delete[] hashBuf;
    delete[] userBuf;
    delete[] passBuf;
    return result;
}

struct NCChallengeBuffer {
    hsUint32 fClientChallenge, fServerChallenge;
    pnSha1Hash fNamePassHash;
};

pnSha1Hash NCHashLoginInfo(const plString& userName, const plString& password,
                           hsUint32 serverChallenge, hsUint32 clientChallenge)
{
    NCChallengeBuffer buffer;
    buffer.fClientChallenge = clientChallenge;
    buffer.fServerChallenge = serverChallenge;
    buffer.fNamePassHash = NCHashPassword(userName, password);
    pnSha1Hash result = pnSha1Hash::Sha0(&buffer, sizeof(buffer));
    return result;
}
