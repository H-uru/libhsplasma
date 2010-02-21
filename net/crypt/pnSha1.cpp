#include "pnSha1.h"
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
