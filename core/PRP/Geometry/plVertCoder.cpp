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

#include <cstring>
#include <cmath>
#include "plVertCoder.h"
#include "plGBufferGroup.h"

float plVertCoder::FieldScales[] = {
   1024.0f, 32768.0f, 65536.0f, 65536.0f, 65536.0f,
   65536.0f, 65536.0f, 65536.0f, 65536.0f, 65536.0f
};

void plVertCoder::clear()
{
    memset(fFloats, 0, sizeof(fFloats));
    memset(fColors, 0, sizeof(fColors));
}

void plVertCoder::read(hsStream* S, unsigned char* dest, unsigned char format,
                       unsigned short numVerts)
{
    clear();
    for (unsigned short i=0; i<numVerts; i++)
        IDecode(S, dest, format);
}

void plVertCoder::write(hsStream* S, const unsigned char* src,
                        unsigned char format, unsigned int stride,
                        unsigned short numVerts)
{
    clear();
    for (unsigned short i=0; i<numVerts; i++)
        IEncode(S, numVerts - i, src, stride, format);
}

void plVertCoder::IDecode(hsStream* S, unsigned char*& dest, unsigned char format)
{
    int i;

    // The X, Y, Z coordinates of this vertex
    IDecodeFloat(S, kPosition, 0, dest);
    IDecodeFloat(S, kPosition, 1, dest);
    IDecodeFloat(S, kPosition, 2, dest);

    // Weights
    int count = (format & plGBufferGroup::kSkinWeightMask) >> 4;
    if (count > 0) {
        for (i=0; i<count; i++)
            IDecodeFloat(S, kWeight, i, dest);

        // Skin index
        if (format & kSkinIndices) {
            *(int*)dest = S->readInt();
            dest += sizeof(int);
        }
    }

    // Normal
    IDecodeNormal(S, dest);
    IDecodeColor(S, dest);
    *(int*)dest = 0;
    dest += sizeof(int);

    // UVW Coordinates
    for (i=0; i<(format & kUVCountMask); i++) {
        IDecodeFloat(S, kUVW+i, 0, dest);
        IDecodeFloat(S, kUVW+i, 1, dest);
        IDecodeFloat(S, kUVW+i, 2, dest);
    }
}

void plVertCoder::IDecodeByte(hsStream* S, int chan, unsigned char* dest)
{
    if (fColors[chan].fCount == 0) {
        unsigned short count = S->readShort();
        if (count & 0x8000) {
            fColors[chan].fSame = true;
            fColors[chan].fVal = S->readByte();
            count &= 0x7FFF;
        } else {
            fColors[chan].fSame = false;
        }
        fColors[chan].fCount = count;
    }
    if (fColors[chan].fSame)
        dest[chan] = fColors[chan].fVal;
    else
        dest[chan] = S->readByte();
    fColors[chan].fCount--;
}

void plVertCoder::IDecodeFloat(hsStream* S, int field, int chan,
                               unsigned char*& dest)
{
    if (fFloats[chan][field].fCount == 0) {
        fFloats[chan][field].fOffset = S->readFloat();
        if (S->getVer().isLive())
            fFloats[chan][field].fAllSame = S->readBool();
        else
            fFloats[chan][field].fAllSame = false;
        fFloats[chan][field].fCount = S->readShort();
    }
    *(float*)dest = fFloats[chan][field].fOffset;
    if (!fFloats[chan][field].fAllSame)
        *(float*)dest += ((uint16_t)S->readShort() / FieldScales[field]);
    dest += sizeof(float);
    fFloats[chan][field].fCount--;
}

void plVertCoder::IDecodeNormal(hsStream* S, unsigned char*& dest)
{
    if (S->getVer().isLive()) {
        ((float*)dest)[0] = ((S->readByte() / 256.0f) - 0.5f) * 2.0f;
        ((float*)dest)[1] = ((S->readByte() / 256.0f) - 0.5f) * 2.0f;
        ((float*)dest)[2] = ((S->readByte() / 256.0f) - 0.5f) * 2.0f;
    } else {
        ((float*)dest)[0] = (int16_t)S->readShort() / 32767.0f;
        ((float*)dest)[1] = (int16_t)S->readShort() / 32767.0f;
        ((float*)dest)[2] = (int16_t)S->readShort() / 32767.0f;
    }
    dest += sizeof(float) * 3;
}

void plVertCoder::IDecodeColor(hsStream* S, unsigned char*& dest)
{
    IDecodeByte(S, 0, dest);
    IDecodeByte(S, 1, dest);
    IDecodeByte(S, 2, dest);
    IDecodeByte(S, 3, dest);
    dest += sizeof(unsigned int);
}

void plVertCoder::IEncode(hsStream* S, unsigned int vertsLeft,
                          const unsigned char*& src, unsigned int stride,
                          unsigned char format)
{
    int i;

    // The X, Y, Z coordinates of this vertex
    IEncodeFloat(S, vertsLeft, kPosition, 0, src, stride);
    IEncodeFloat(S, vertsLeft, kPosition, 1, src, stride);
    IEncodeFloat(S, vertsLeft, kPosition, 2, src, stride);

    // Weights
    int count = (format & plGBufferGroup::kSkinWeightMask) >> 4;
    if (count > 0) {
        for (i=0; i<count; i++)
            IEncodeFloat(S, vertsLeft, kWeight, i, src, stride);

        if (format & kSkinIndices) {
            S->writeInt(*(int*)src);
            src += sizeof(int);
        }
    }

    // Normal
    IEncodeNormal(S, src);
    IEncodeColor(S, vertsLeft, src, stride);
    src += sizeof(int);

    // UVW Coordinates
    for (i=0; i<(format & kUVCountMask); i++) {
        IEncodeFloat(S, vertsLeft, kUVW+i, 0, src, stride);
        IEncodeFloat(S, vertsLeft, kUVW+i, 1, src, stride);
        IEncodeFloat(S, vertsLeft, kUVW+i, 2, src, stride);
    }
}

void plVertCoder::IEncodeByte(hsStream* S, unsigned int vertsLeft, int chan,
                              const unsigned char* src, unsigned int stride)
{
    if (fColors[chan].fCount == 0) {
        ICountBytes(vertsLeft, src + chan, stride, fColors[chan].fCount, fColors[chan].fSame);
        unsigned short count = fColors[chan].fCount;
        if (fColors[chan].fSame)
            count |= 0x8000;
        S->writeShort(count);
        count &= 0x7FFF;
        if (fColors[chan].fSame)
            S->writeByte(src[chan]);
    }
    if (!fColors[chan].fSame)
        S->writeByte(src[chan]);
    fColors[chan].fCount--;
}

#define FloatToShort(x) (int16_t)(x)
#define FloatToUShort(x) (uint16_t)(x)
#define FloatToByte(x) (uint8_t)(x)

void plVertCoder::IEncodeFloat(hsStream* S, unsigned int vertsLeft, int field,
                               int chan, const unsigned char*& src,
                               unsigned int stride)
{
    if (fFloats[chan][field].fCount == 0) {
        ICountFloats(vertsLeft, src, FieldScales[field], stride,
                     fFloats[chan][field].fOffset,
                     fFloats[chan][field].fAllSame,
                     fFloats[chan][field].fCount);
        S->writeFloat(fFloats[chan][field].fOffset);
        if (S->getVer().isLive())
            S->writeBool(fFloats[chan][field].fAllSame);
        S->writeShort(fFloats[chan][field].fCount);
    }

    if (!S->getVer().isLive() || (!fFloats[chan][field].fAllSame)) {
        float flt = *(float*)src;
        flt = (flt - fFloats[chan][field].fOffset) * FieldScales[field];
        S->writeShort((unsigned short)(flt + 0.5f));
    }
    src += sizeof(float);
    fFloats[chan][field].fCount--;
}

void plVertCoder::IEncodeNormal(hsStream* S, const unsigned char*& src)
{
    if (S->getVer().isLive()) {
        S->writeByte(FloatToByte(((((float*)src)[0] + 1.0f) / 2.0f) * 256.0f));
        S->writeByte(FloatToByte(((((float*)src)[1] + 1.0f) / 2.0f) * 256.0f));
        S->writeByte(FloatToByte(((((float*)src)[2] + 1.0f) / 2.0f) * 256.0f));
    } else {
        S->writeShort(FloatToShort(((float*)src)[0] * 32767.0f));
        S->writeShort(FloatToShort(((float*)src)[1] * 32767.0f));
        S->writeShort(FloatToShort(((float*)src)[2] * 32767.0f));
    }
    src += sizeof(float) * 3;
}

void plVertCoder::IEncodeColor(hsStream* S, unsigned int vertsLeft,
                               const unsigned char*& src, unsigned int stride)
{
    IEncodeByte(S, vertsLeft, 0, src, stride);
    IEncodeByte(S, vertsLeft, 1, src, stride);
    IEncodeByte(S, vertsLeft, 2, src, stride);
    IEncodeByte(S, vertsLeft, 3, src, stride);
    src += sizeof(unsigned int);
}

void plVertCoder::ICountBytes(unsigned int vertsLeft, const unsigned char* src,
                              unsigned int stride, unsigned short& len, bool& same)
{
    if (vertsLeft < 4) {
        len = vertsLeft;
        same = false;
        return;
    }

    unsigned int i = 0;
    if (vertsLeft > 0) {
        unsigned char rle = *src;
        while (i < vertsLeft && *src == rle && i <= 0x7FFF) {
            src += stride;
            i++;
        }
        if (i >= 4) {
            len = i;
            same = true;
            return;
        }
    }

    same = false;
    while (i < (vertsLeft - 4) && i <= 0x7FFF) {
        unsigned char b0 = *(src + (0*stride));
        unsigned char b1 = *(src + (1*stride));
        unsigned char b2 = *(src + (2*stride));
        unsigned char b3 = *(src + (3*stride));
        if (b0 == b1 && b0 == b2 && b0 == b3)
            break;
        i++;
        src += stride;
    }
    if (i < vertsLeft - 4)
        len = i;
    else if (vertsLeft <= 0x7FFF)
        len = vertsLeft;
    else
        len = 0x7FFF;
}

void plVertCoder::ICountFloats(unsigned int vertsLeft, const unsigned char* src,
                               float quant, unsigned int stride, float& lo,
                               bool& allSame, unsigned short& count)
{
    lo = floor(((*(float*)src) * quant) + 0.5f) / quant;
    float hi = lo;
    allSame = false;
    unsigned int len = 1;
    float maxRange = 65535.0f / quant;

    src += stride;
    while (--vertsLeft > 0 && len < 0xFFFF) {
        float cur = floor(((*(float*)src) * quant) + 0.5f) / quant;
        if (cur < lo) {
            if (hi - cur >= maxRange) {
                count = len;
                return;
            }
            lo = cur;
        } else if (cur > hi) {
            if (cur - lo >= maxRange) {
                count = len;
                return;
            }
            hi = cur;
        }
        len++;
        src += stride;
    }

    allSame = (hi == lo);
    count = len;
}
