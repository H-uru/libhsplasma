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
#include <openssl/evp.h>
#include <string_theory/format>
#include <memory>
#include <cstring>

static struct _pnSha1_Static_Initializer {
    // Ensure digest names are available to EVP APIs below
    _pnSha1_Static_Initializer() { OpenSSL_add_all_digests(); }
} _pnSha1_Static_Init;

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

uint32_t rol32(uint32_t value, unsigned int n)
{
    // Many compilers will optimize this to a single rol instruction on x86
    return (value << n) | (value >> (32 - n));
}

static pnSha1Hash _hs_internal_sha0(const void *data, size_t size)
{
    pnSha1Hash hash;
    hash.fData[0] = 0x67452301;
    hash.fData[1] = 0xefcdab89;
    hash.fData[2] = 0x98badcfe;
    hash.fData[3] = 0x10325476;
    hash.fData[4] = 0xc3d2e1f0;

    uint8_t stack_buffer[256];
    std::unique_ptr<uint8_t[]> heap_buffer;
    uint8_t* bufp;

    // Preprocess the message to pad it to a multiple of 512 bits,
    // with the (Big Endian) size in bits tacked onto the end.
    uint64_t buf_size = size + 1 + sizeof(uint64_t);
    if ((buf_size % 64) != 0)
        buf_size += 64 - (buf_size % 64);
    if (buf_size > sizeof(stack_buffer)) {
        heap_buffer = std::unique_ptr<uint8_t[]>(new uint8_t[buf_size]);
        bufp = heap_buffer.get();
    } else {
        bufp = stack_buffer;
    }

    memcpy(bufp, data, size);
    memset(bufp + size, 0, buf_size - size);
    bufp[size] = 0x80;  // Append '1' bit to the end of the message
    uint64_t msg_size_bits = static_cast<uint64_t>(size) * 8;
    msg_size_bits = BESWAP64(msg_size_bits);
    memcpy(bufp + buf_size - sizeof(msg_size_bits),
           &msg_size_bits, sizeof(msg_size_bits));

    uint8_t* end = bufp + buf_size;
    uint32_t work[80];
    while (bufp < end) {
        memcpy(work, bufp, 64);
        bufp += 64;

        for (size_t i = 0; i < 16; ++i)
            work[i] = BESWAP32(work[i]);

        for (size_t i = 16; i < 80; ++i) {
            // SHA-1 difference: no rol32(work[i], 1)
            work[i] = work[i-3] ^ work[i-8] ^ work[i-14] ^ work[i-16];
        }

        uint32_t hv[5];
        memcpy(hv, hash.fData, sizeof(hv));

        // Main SHA loop
        for (size_t i = 0; i < 20; ++i) {
            static const uint32_t K = 0x5a827999;
            const uint32_t f = (hv[1] & hv[2]) | (~hv[1] & hv[3]);
            const uint32_t temp = rol32(hv[0], 5) + f + hv[4] + K + work[i];
            hv[4] = hv[3];
            hv[3] = hv[2];
            hv[2] = rol32(hv[1], 30);
            hv[1] = hv[0];
            hv[0] = temp;
        }
        for (size_t i = 20; i < 40; ++i) {
            static const uint32_t K = 0x6ed9eba1;
            const uint32_t f = (hv[1] ^ hv[2] ^ hv[3]);
            const uint32_t temp = rol32(hv[0], 5) + f + hv[4] + K + work[i];
            hv[4] = hv[3];
            hv[3] = hv[2];
            hv[2] = rol32(hv[1], 30);
            hv[1] = hv[0];
            hv[0] = temp;
        }
        for (size_t i = 40; i < 60; ++i) {
            static const uint32_t K = 0x8f1bbcdc;
            const uint32_t f = (hv[1] & hv[2]) | (hv[1] & hv[3]) | (hv[2] & hv[3]);
            const uint32_t temp = rol32(hv[0], 5) + f + hv[4] + K + work[i];
            hv[4] = hv[3];
            hv[3] = hv[2];
            hv[2] = rol32(hv[1], 30);
            hv[1] = hv[0];
            hv[0] = temp;
        }
        for (size_t i = 60; i < 80; ++i) {
            static const uint32_t K = 0xca62c1d6;
            const uint32_t f = (hv[1] ^ hv[2] ^ hv[3]);
            const uint32_t temp = rol32(hv[0], 5) + f + hv[4] + K + work[i];
            hv[4] = hv[3];
            hv[3] = hv[2];
            hv[2] = rol32(hv[1], 30);
            hv[1] = hv[0];
            hv[0] = temp;
        }

        hash.fData[0] += hv[0];
        hash.fData[1] += hv[1];
        hash.fData[2] += hv[2];
        hash.fData[3] += hv[3];
        hash.fData[4] += hv[4];
    }

    // Bring the output back to host endian
    for (size_t i = 0; i < 5; ++i)
        hash.fData[i] = BESWAP32(hash.fData[i]);

    return hash;
}

pnSha1Hash pnSha1Hash::Sha0(const void* src, size_t len)
{
    const EVP_MD* sha0_md = EVP_get_digestbyname("sha");
    if (!sha0_md) {
        // Use our own implementation only if OpenSSL doesn't support it
        return _hs_internal_sha0(src, len);
    }

    pnSha1Hash hash;
    unsigned int out_len = EVP_MD_size(sha0_md);
    if (out_len != sizeof(hash.fData)) {
        throw hsBadParamException(__FILE__, __LINE__,
                        "SHA0 digest size doesn't match expected size");
    }

    EVP_MD_CTX* sha_ctx = EVP_MD_CTX_create();
    EVP_DigestInit_ex(sha_ctx, sha0_md, NULL);
    EVP_DigestUpdate(sha_ctx, src, len);
    EVP_DigestFinal_ex(sha_ctx, reinterpret_cast<unsigned char *>(hash.fData), &out_len);
    EVP_MD_CTX_destroy(sha_ctx);

    return hash;
}

pnSha1Hash pnSha1Hash::Sha1(const void* src, size_t len)
{
    pnSha1Hash hash;
    const EVP_MD* sha1_md = EVP_get_digestbyname("sha1");
    if (!sha1_md) {
        throw hsNotImplementedException(__FILE__, __LINE__,
                        "SHA1 support unavailable in OpenSSL");
    }

    unsigned int out_len = EVP_MD_size(sha1_md);
    if (out_len != sizeof(hash.fData)) {
        throw hsBadParamException(__FILE__, __LINE__,
                        "SHA1 digest size doesn't match expected size");
    }

    EVP_MD_CTX* sha1_ctx = EVP_MD_CTX_create();
    EVP_DigestInit_ex(sha1_ctx, sha1_md, NULL);
    EVP_DigestUpdate(sha1_ctx, src, len);
    EVP_DigestFinal_ex(sha1_ctx, reinterpret_cast<unsigned char *>(hash.fData), &out_len);
    EVP_MD_CTX_destroy(sha1_ctx);

    return hash;
}

pnSha1Hash NCHashPassword(const ST::string& userName, const ST::string& password)
{
    ST::utf16_buffer userBuf = userName.to_lower().to_utf16();
    ST::utf16_buffer passBuf = password.to_utf16();
    std::unique_ptr<char16_t[]> hashBuf(new char16_t[userBuf.size() + passBuf.size()]);
    memcpy(hashBuf.get(), passBuf.data(), passBuf.size() * sizeof(char16_t));
    memcpy(hashBuf.get() + passBuf.size(), userBuf.data(), userBuf.size() * sizeof(char16_t));
    hashBuf[passBuf.size() - 1] = 0;
    hashBuf[(passBuf.size() + userBuf.size()) - 1] = 0;
    pnSha1Hash result = pnSha1Hash::Sha0(hashBuf.get(), (userBuf.size() + passBuf.size()) * sizeof(char16_t));
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
