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

#include "plMD5.h"
#include <cstring>

/* plMD5Hash */
typedef union
{
    unsigned int hash32[4];
    unsigned char hash8[16];
} HashConvert;

static const char kHexTable[16] = {
    '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', 'a', 'b', 'c', 'd', 'e', 'f',
};

static int charToHex(char ch)
{
    switch (ch) {
        case '0':   return 0;   case '1':   return 1;
        case '2':   return 2;   case '3':   return 3;
        case '4':   return 4;   case '5':   return 5;
        case '6':   return 6;   case '7':   return 7;
        case '8':   return 8;   case '9':   return 9;
        case 'a':   return 10;  case 'A':   return 10;
        case 'b':   return 11;  case 'B':   return 11;
        case 'c':   return 12;  case 'C':   return 12;
        case 'd':   return 13;  case 'D':   return 13;
        case 'e':   return 14;  case 'E':   return 14;
        case 'f':   return 15;  case 'F':   return 15;
        default:    return -1;
    }
}

plMD5Hash::plMD5Hash()
{
    // Empty hash
    fHash[0] = 0xd98c1dd4;
    fHash[1] = 0x04b2008f;
    fHash[2] = 0x980980e9;
    fHash[3] = 0x7e42f8ec;
}

bool plMD5Hash::operator==(const plMD5Hash& cmp) const
{
    return memcmp(fHash, cmp.fHash, sizeof(fHash)) == 0;
}

bool plMD5Hash::operator!=(const plMD5Hash& cmp) const
{
    return memcmp(fHash, cmp.fHash, sizeof(fHash)) != 0;
}

ST::string plMD5Hash::toHex() const
{
    // Little-endian byte order
    HashConvert hc;
    hc.hash32[0] = LESWAP32(fHash[0]);
    hc.hash32[1] = LESWAP32(fHash[1]);
    hc.hash32[2] = LESWAP32(fHash[2]);
    hc.hash32[3] = LESWAP32(fHash[3]);

    ST::char_buffer result;
    result.allocate(32);
    for (size_t i=0; i<16; i++) {
        result[(2*i)    ] = kHexTable[(hc.hash8[i] & 0xF0) >> 4];
        result[(2*i) + 1] = kHexTable[(hc.hash8[i] & 0x0F)     ];
    }
    return result;
}

void plMD5Hash::fromHex(const char* hex)
{
    HashConvert hc;

    if (strlen(hex) != 32)
        throw hsBadParamException(__FILE__, __LINE__, "Invalid hex string");
    for (size_t i=0; i<16; i++) {
        int ch1 = charToHex(hex[(2*i)    ]);
        int ch2 = charToHex(hex[(2*i) + 1]);
        if (ch1 == -1 || ch2 == -1)
            throw hsBadParamException(__FILE__, __LINE__, "Invalid hex string");
        hc.hash8[i] = ((ch1 << 4) & 0xF0) | (ch2 & 0x0F);
    }

    fHash[0] = LESWAP32(hc.hash32[0]);
    fHash[1] = LESWAP32(hc.hash32[1]);
    fHash[2] = LESWAP32(hc.hash32[2]);
    fHash[3] = LESWAP32(hc.hash32[3]);
}

void plMD5Hash::read(hsStream* S)
{
    fHash[0] = S->readInt();
    fHash[1] = S->readInt();
    fHash[2] = S->readInt();
    fHash[3] = S->readInt();
}

void plMD5Hash::write(hsStream* S) const
{
    S->writeInt(fHash[0]);
    S->writeInt(fHash[1]);
    S->writeInt(fHash[2]);
    S->writeInt(fHash[3]);
}


/* plMD5 */
const unsigned int plMD5::kShiftArray[4][4] = {
     { 7, 12, 17, 22 },
     { 5,  9, 14, 20 },
     { 4, 11, 16, 23 },
     { 6, 10, 15, 21 },
};

const unsigned int plMD5::kBaseArray[64] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
};

const unsigned char plMD5::kPadArray[64] = {
    0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

#define ROTL(x, n) \
    ((x << n) | (x >> (32 - n)))

#define R1(a, b, c, d, x, s, k) \
    a += ((b & c) | (~b & d)) + x + k; \
    a = ROTL(a, s); \
    a += b;

#define R2(a, b, c, d, x, s, k) \
    a += ((b & d) | (c & ~d)) + x + k; \
    a = ROTL(a, s); \
    a += b;

#define R3(a, b, c, d, x, s, k) \
    a += (b ^ c ^ d) + x + k; \
    a = ROTL(a, s); \
    a += b;

#define R4(a, b, c, d, x, s, k) \
    a += (c ^ (b | ~d)) + x + k; \
    a = ROTL(a, s); \
    a += b;

plMD5::plMD5()
{
    // Initialize context state
    fA = 0x67452301;
    fB = 0xefcdab89;
    fC = 0x98badcfe;
    fD = 0x10325476;
}

void plMD5::processBlock(const unsigned char* block)
{
    // Expand 64-byte input into 16 little-endian DWords
    unsigned int x[16];
    for (size_t i=0; i<16; i++) {
        x[i] = (block[(4*i)    ]      )
             | (block[(4*i) + 1] <<  8)
             | (block[(4*i) + 2] << 16)
             | (block[(4*i) + 3] << 24);
    }

    unsigned int a = fA, b = fB, c = fC, d = fD;

    /* Round 1 */
    R1(a, b, c, d, x[ 0], kShiftArray[0][0], kBaseArray[ 0]);
    R1(d, a, b, c, x[ 1], kShiftArray[0][1], kBaseArray[ 1]);
    R1(c, d, a, b, x[ 2], kShiftArray[0][2], kBaseArray[ 2]);
    R1(b, c, d, a, x[ 3], kShiftArray[0][3], kBaseArray[ 3]);
    R1(a, b, c, d, x[ 4], kShiftArray[0][0], kBaseArray[ 4]);
    R1(d, a, b, c, x[ 5], kShiftArray[0][1], kBaseArray[ 5]);
    R1(c, d, a, b, x[ 6], kShiftArray[0][2], kBaseArray[ 6]);
    R1(b, c, d, a, x[ 7], kShiftArray[0][3], kBaseArray[ 7]);
    R1(a, b, c, d, x[ 8], kShiftArray[0][0], kBaseArray[ 8]);
    R1(d, a, b, c, x[ 9], kShiftArray[0][1], kBaseArray[ 9]);
    R1(c, d, a, b, x[10], kShiftArray[0][2], kBaseArray[10]);
    R1(b, c, d, a, x[11], kShiftArray[0][3], kBaseArray[11]);
    R1(a, b, c, d, x[12], kShiftArray[0][0], kBaseArray[12]);
    R1(d, a, b, c, x[13], kShiftArray[0][1], kBaseArray[13]);
    R1(c, d, a, b, x[14], kShiftArray[0][2], kBaseArray[14]);
    R1(b, c, d, a, x[15], kShiftArray[0][3], kBaseArray[15]);

    /* Round 2 */
    R2(a, b, c, d, x[ 1], kShiftArray[1][0], kBaseArray[16]);
    R2(d, a, b, c, x[ 6], kShiftArray[1][1], kBaseArray[17]);
    R2(c, d, a, b, x[11], kShiftArray[1][2], kBaseArray[18]);
    R2(b, c, d, a, x[ 0], kShiftArray[1][3], kBaseArray[19]);
    R2(a, b, c, d, x[ 5], kShiftArray[1][0], kBaseArray[20]);
    R2(d, a, b, c, x[10], kShiftArray[1][1], kBaseArray[21]);
    R2(c, d, a, b, x[15], kShiftArray[1][2], kBaseArray[22]);
    R2(b, c, d, a, x[ 4], kShiftArray[1][3], kBaseArray[23]);
    R2(a, b, c, d, x[ 9], kShiftArray[1][0], kBaseArray[24]);
    R2(d, a, b, c, x[14], kShiftArray[1][1], kBaseArray[25]);
    R2(c, d, a, b, x[ 3], kShiftArray[1][2], kBaseArray[26]);
    R2(b, c, d, a, x[ 8], kShiftArray[1][3], kBaseArray[27]);
    R2(a, b, c, d, x[13], kShiftArray[1][0], kBaseArray[28]);
    R2(d, a, b, c, x[ 2], kShiftArray[1][1], kBaseArray[29]);
    R2(c, d, a, b, x[ 7], kShiftArray[1][2], kBaseArray[30]);
    R2(b, c, d, a, x[12], kShiftArray[1][3], kBaseArray[31]);

    /* Round 3 */
    R3(a, b, c, d, x[ 5], kShiftArray[2][0], kBaseArray[32]);
    R3(d, a, b, c, x[ 8], kShiftArray[2][1], kBaseArray[33]);
    R3(c, d, a, b, x[11], kShiftArray[2][2], kBaseArray[34]);
    R3(b, c, d, a, x[14], kShiftArray[2][3], kBaseArray[35]);
    R3(a, b, c, d, x[ 1], kShiftArray[2][0], kBaseArray[36]);
    R3(d, a, b, c, x[ 4], kShiftArray[2][1], kBaseArray[37]);
    R3(c, d, a, b, x[ 7], kShiftArray[2][2], kBaseArray[38]);
    R3(b, c, d, a, x[10], kShiftArray[2][3], kBaseArray[39]);
    R3(a, b, c, d, x[13], kShiftArray[2][0], kBaseArray[40]);
    R3(d, a, b, c, x[ 0], kShiftArray[2][1], kBaseArray[41]);
    R3(c, d, a, b, x[ 3], kShiftArray[2][2], kBaseArray[42]);
    R3(b, c, d, a, x[ 6], kShiftArray[2][3], kBaseArray[43]);
    R3(a, b, c, d, x[ 9], kShiftArray[2][0], kBaseArray[44]);
    R3(d, a, b, c, x[12], kShiftArray[2][1], kBaseArray[45]);
    R3(c, d, a, b, x[15], kShiftArray[2][2], kBaseArray[46]);
    R3(b, c, d, a, x[ 2], kShiftArray[2][3], kBaseArray[47]);

    /* Round 4 */
    R4(a, b, c, d, x[ 0], kShiftArray[3][0], kBaseArray[48]);
    R4(d, a, b, c, x[ 7], kShiftArray[3][1], kBaseArray[49]);
    R4(c, d, a, b, x[14], kShiftArray[3][2], kBaseArray[50]);
    R4(b, c, d, a, x[ 5], kShiftArray[3][3], kBaseArray[51]);
    R4(a, b, c, d, x[12], kShiftArray[3][0], kBaseArray[52]);
    R4(d, a, b, c, x[ 3], kShiftArray[3][1], kBaseArray[53]);
    R4(c, d, a, b, x[10], kShiftArray[3][2], kBaseArray[54]);
    R4(b, c, d, a, x[ 1], kShiftArray[3][3], kBaseArray[55]);
    R4(a, b, c, d, x[ 8], kShiftArray[3][0], kBaseArray[56]);
    R4(d, a, b, c, x[15], kShiftArray[3][1], kBaseArray[57]);
    R4(c, d, a, b, x[ 6], kShiftArray[3][2], kBaseArray[58]);
    R4(b, c, d, a, x[13], kShiftArray[3][3], kBaseArray[59]);
    R4(a, b, c, d, x[ 4], kShiftArray[3][0], kBaseArray[60]);
    R4(d, a, b, c, x[11], kShiftArray[3][1], kBaseArray[61]);
    R4(c, d, a, b, x[ 2], kShiftArray[3][2], kBaseArray[62]);
    R4(b, c, d, a, x[ 9], kShiftArray[3][3], kBaseArray[63]);

    fA += a;
    fB += b;
    fC += c;
    fD += d;
}

plMD5Hash plMD5::hashStream(hsStream* S)
{
    plMD5 ctx;
    size_t size = S->size();
    unsigned char buf[64];

    size_t pos = 0;
    while (pos + 64 <= size) {
        S->read(64, buf);
        ctx.processBlock(buf);
        pos += 64;
    }

    // Final block
    size_t lastSize = size - pos;
    S->read(lastSize, buf);

    if (lastSize >= 56) {
        memcpy(buf + lastSize, kPadArray, 64 - lastSize);
        ctx.processBlock(buf);
        memset(buf, 0, sizeof(buf));
    } else {
        unsigned int padBytes = 56 - lastSize;
        memcpy(buf + lastSize, kPadArray, padBytes);
    }

    unsigned int bitSize[2];
    bitSize[0] = LESWAP32((size <<  3));
    bitSize[1] = LESWAP32((size >> 29));
    memcpy(buf + 56, bitSize, sizeof(bitSize));

    ctx.processBlock(buf);
    plMD5Hash hash;
    hash.fHash[0] = ctx.fA;
    hash.fHash[1] = ctx.fB;
    hash.fHash[2] = ctx.fC;
    hash.fHash[3] = ctx.fD;
    return hash;
}

plMD5Hash plMD5::hashFile(const char* filename)
{
    hsFileStream S;
    S.open(filename, fmRead);
    plMD5Hash hash = hashStream(&S);
    S.close();
    return hash;
}

plMD5Hash plMD5::hashString(const ST::string& str)
{
    plMD5 ctx;
    size_t size = str.size();
    unsigned char buf[64];

    size_t pos = 0;
    while (pos + 64 <= size) {
        memcpy(buf, str.c_str() + pos, 64);
        ctx.processBlock(buf);
        pos += 64;
    }

    // Final block
    size_t lastSize = size - pos;
    memcpy(buf, str.c_str() + pos, lastSize);

    if (lastSize >= 56) {
        memcpy(buf + lastSize, kPadArray, 64 - lastSize);
        ctx.processBlock(buf);
        memset(buf, 0, sizeof(buf));
    } else {
        unsigned int padBytes = 56 - lastSize;
        memcpy(buf + lastSize, kPadArray, padBytes);
    }

    unsigned int bitSize[2];
    bitSize[0] = LESWAP32((size <<  3));
    bitSize[1] = LESWAP32((size >> 29));
    memcpy(buf + 56, bitSize, sizeof(bitSize));

    ctx.processBlock(buf);
    plMD5Hash hash;
    hash.fHash[0] = ctx.fA;
    hash.fHash[1] = ctx.fB;
    hash.fHash[2] = ctx.fC;
    hash.fHash[3] = ctx.fD;
    return hash;
};
