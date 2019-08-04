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

#ifndef _PLVERTCODER_H
#define _PLVERTCODER_H

#include "Stream/hsStream.h"

class PLASMA_DLL plVertCoder
{
public:
    enum { kPosition, kWeight, kUVW, kNumFloatFields = 10 };

    enum Formats
    {
        kUVCountMask = 0xF,
        kSkinNoWeights = 0x0,
        kSkin1Weight = 0x10,
        kSkin2Weights = 0x20,
        kSkin3Weights = 0x30,
        kSkinWeightMask = 0x30,
        kSkinIndices = 0x40,
        kEncoded = 0x80
    };

    static float FieldScales[kNumFloatFields];

private:
    struct FloatCode
    {
        float fOffset;
        bool fAllSame;
        unsigned short fCount;
    } fFloats[3][kNumFloatFields];

    struct ByteCode
    {
        unsigned short fCount;
        unsigned char fVal;
        bool fSame;
    } fColors[4];

    void IDecode(hsStream* S, unsigned char*& dest,unsigned char format);
    void IDecodeByte(hsStream* S, int chan, unsigned char* dest);
    void IDecodeFloat(hsStream* S, int field, int chan, unsigned char*& dest);
    void IDecodeNormal(hsStream* S, unsigned char*& dest);
    void IDecodeColor(hsStream* S, unsigned char*& dest);

    void IEncode(hsStream* S, unsigned int vertsLeft, const unsigned char*& src,
                 unsigned int stride, unsigned char format);
    void IEncodeByte(hsStream* S, unsigned int vertsLeft, int chan,
                     const unsigned char* src, unsigned int stride);
    void IEncodeFloat(hsStream* S, unsigned int vertsLeft, int field, int chan,
                      const unsigned char*& src, unsigned int stride);
    void IEncodeNormal(hsStream* S, const unsigned char*& src);
    void IEncodeColor(hsStream* S, unsigned int vertsLeft,
                      const unsigned char*& src, unsigned int stride);

    void ICountBytes(unsigned int vertsLeft, const unsigned char* src,
                     unsigned int stride, unsigned short& len, bool& same);
    void ICountFloats(unsigned int vertsLeft, const unsigned char* src,
                      float fieldScale, unsigned int stride, float& offset,
                      bool& same, unsigned short& count);

public:
    void clear();
    void read(hsStream* S, unsigned char* dest, unsigned char format,
              unsigned short numVerts);
    void write(hsStream* S, const unsigned char* src, unsigned char format,
               unsigned int stride, unsigned short numVerts);
};

#endif

