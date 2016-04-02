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
#include <string_theory/format>
#include <cstring>

void pnSha1Hash::fromString(const ST::string& src)
{
    if (src.size() != 40)
        throw hsBadParamException(__FILE__, __LINE__, "Invalid SHA1 string");

    fData[0] = src.substr(0, 8).to_uint(16);
    fData[1] = src.substr(8, 8).to_uint(16);
    fData[2] = src.substr(16, 8).to_uint(16);
    fData[3] = src.substr(24, 8).to_uint(16);
    fData[4] = src.substr(32, 8).to_uint(16);
    for (size_t i=0; i<5; i++)
        fData[i] = BESWAP32(fData[i]);
}

ST::string pnSha1Hash::toString() const
{
    return ST::format("{_08x}{_08x}{_08x}{_08x}{_08x}",
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

pnSha1Hash NCHashPassword(const ST::string& userName, const ST::string& password)
{
    ST::utf16_buffer userBuf = userName.to_lower().to_utf16();
    ST::utf16_buffer passBuf = password.to_utf16();
    char16_t * hashBuf = new char16_t[userBuf.size() + passBuf.size()];
    memcpy(hashBuf, passBuf.data(), passBuf.size() * sizeof(char16_t));
    memcpy(hashBuf + passBuf.size(), userBuf.data(), userBuf.size() * sizeof(char16_t));
    hashBuf[passBuf.size() - 1] = 0;
    hashBuf[(passBuf.size() + userBuf.size()) - 1] = 0;
    pnSha1Hash result = pnSha1Hash::Sha0(hashBuf, (userBuf.size() + passBuf.size()) * sizeof(char16_t));
    delete[] hashBuf;
    return result;
}

struct NCChallengeBuffer {
    uint32_t fClientChallenge, fServerChallenge;
    pnSha1Hash fNamePassHash;
};

pnSha1Hash NCHashLoginInfo(const ST::string& userName, const ST::string& password,
                           uint32_t serverChallenge, uint32_t clientChallenge)
{
    NCChallengeBuffer buffer;
    buffer.fClientChallenge = clientChallenge;
    buffer.fServerChallenge = serverChallenge;
    buffer.fNamePassHash = NCHashPassword(userName, password);
    pnSha1Hash result = pnSha1Hash::Sha0(&buffer, sizeof(buffer));
    return result;
}
