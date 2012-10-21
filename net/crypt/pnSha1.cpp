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

#include "pnSha1.h"
#include "pnNetMsg.h"
#include "Debug/hsExceptions.hpp"
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
    for (size_t i=0; i<5; i++)
        fData[i] = BESWAP32(fData[i]);
}

plString pnSha1Hash::toString() const
{
    return plString::Format("%08x%08x%08x%08x%08x",
                            BESWAP32(fData[0]), BESWAP32(fData[1]),
                            BESWAP32(fData[2]), BESWAP32(fData[3]),
                            BESWAP32(fData[4]));
}

void pnSha1Hash::swapBytes()
{
    fData[0] = ENDSWAP32(fData[0]);
    fData[1] = ENDSWAP32(fData[1]);
    fData[2] = ENDSWAP32(fData[2]);
    fData[3] = ENDSWAP32(fData[3]);
    fData[4] = ENDSWAP32(fData[4]);
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
    plString::Wide userBuf = userName.toLower().wstr();
    plString::Wide passBuf = password.wstr();
    pl_wchar_t* hashBuf = new pl_wchar_t[userBuf.len() + passBuf.len()];
    memcpy(hashBuf, passBuf.data(), passBuf.len() * sizeof(pl_wchar_t));
    memcpy(hashBuf + passBuf.len(), userBuf.data(), userBuf.len() * sizeof(pl_wchar_t));
    hashBuf[passBuf.len() - 1] = 0;
    hashBuf[(passBuf.len() + userBuf.len()) - 1] = 0;
    pnSha1Hash result = pnSha1Hash::Sha0(hashBuf, (userBuf.len() + passBuf.len()) * sizeof(pl_wchar_t));
    delete[] hashBuf;
    return result;
}

struct NCChallengeBuffer {
    uint32_t fClientChallenge, fServerChallenge;
    pnSha1Hash fNamePassHash;
};

pnSha1Hash NCHashLoginInfo(const plString& userName, const plString& password,
                           uint32_t serverChallenge, uint32_t clientChallenge)
{
    NCChallengeBuffer buffer;
    buffer.fClientChallenge = clientChallenge;
    buffer.fServerChallenge = serverChallenge;
    buffer.fNamePassHash = NCHashPassword(userName, password);
    pnSha1Hash result = pnSha1Hash::Sha0(&buffer, sizeof(buffer));
    return result;
}
