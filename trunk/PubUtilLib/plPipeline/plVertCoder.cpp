#include <cstring>
#include <cmath>
#include "plVertCoder.h"
#include "plGBufferGroup.h"

float plVertCoder::FieldScales[] = {
   1024.0f, 32768.0f, 65536.0f, 65536.0f, 65536.0f,
   65536.0f, 65536.0f, 65536.0f, 65536.0f, 65536.0f
};

plVertCoder::plVertCoder() { }
plVertCoder::~plVertCoder() { }

void plVertCoder::clear() {
    memset(fFloats, 0, sizeof(fFloats));
    memset(fColors, 0, sizeof(fColors));
}

void plVertCoder::read(hsStream* S, unsigned char* dest, unsigned char format,
                       unsigned short numVerts) {
    clear();
    for (unsigned short i=0; i<numVerts; i++)
        IDecode(S, dest, format);
}

void plVertCoder::write(hsStream* S, const unsigned char* src,
                        unsigned char format, unsigned int stride,
                        unsigned short numVerts) {
    clear();
    for (unsigned short i=numVerts; i>0; i--)
        IEncode(S, i, src, stride, format);
}

void plVertCoder::IDecode(hsStream* S, unsigned char*& dest, unsigned char format) {
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

void plVertCoder::IDecodeByte(hsStream* S, int chan, unsigned char*& dest) {
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
        //plDebug::Debug("_VC_ fBytes[%d] = { count=%d, same=%d, val=0x%02X }\n",
        //               chan, fColors[chan].fCount, fColors[chan].fSame, fColors[chan].fVal);
    }
    if (fColors[chan].fSame)
        *dest = fColors[chan].fVal;
    else
        *dest = S->readByte();
    dest += sizeof(unsigned char);
    fColors[chan].fCount--;
}

void plVertCoder::IDecodeFloat(hsStream* S, int field, int chan,
                               unsigned char*& dest) {
    if (fFloats[chan][field].fCount == 0) {
        fFloats[chan][field].fOffset = S->readFloat();
        if (S->getVer() == pvLive)
            fFloats[chan][field].fAllSame = S->readBool();
        else
            fFloats[chan][field].fAllSame = false;
        fFloats[chan][field].fCount = S->readShort();
        //plDebug::Debug("_VC_ fFloats[%d][%d] = { count=%d, same=%d, offset=%f }\n",
        //               chan, field, fFloats[chan][field].fCount,
        //               fFloats[chan][field].fAllSame, fFloats[chan][field].fOffset);
    }
    *(float*)dest = fFloats[chan][field].fOffset;
    if (!fFloats[chan][field].fAllSame)
        *(float*)dest += ((hsInt16)S->readShort() / FieldScales[field]);
    dest += sizeof(float);
    fFloats[chan][field].fCount--;
}

void plVertCoder::IDecodeNormal(hsStream* S, unsigned char*& dest) {
    if (S->getVer() == pvLive) {
        ((float*)dest)[0] = ((S->readByte() / 256.0f) - 0.5f) * 2.0f;
        ((float*)dest)[1] = ((S->readByte() / 256.0f) - 0.5f) * 2.0f;
        ((float*)dest)[2] = ((S->readByte() / 256.0f) - 0.5f) * 2.0f;
    } else {
        ((float*)dest)[0] = (hsInt16)S->readShort() / 32767.0f;
        ((float*)dest)[1] = (hsInt16)S->readShort() / 32767.0f;
        ((float*)dest)[2] = (hsInt16)S->readShort() / 32767.0f;
    }
    dest += sizeof(float) * 3;
}

void plVertCoder::IDecodeColor(hsStream* S, unsigned char*& dest) {
    IDecodeByte(S, 0, dest);
    IDecodeByte(S, 1, dest);
    IDecodeByte(S, 2, dest);
    IDecodeByte(S, 3, dest);
}

void plVertCoder::IEncode(hsStream* S, unsigned int vertsLeft,
                          const unsigned char*& src, unsigned int stride,
                          unsigned char format) {
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
                              const unsigned char*& src, unsigned int stride) {
    if (fColors[chan].fCount == 0) {
        ICountBytes(vertsLeft, src, stride, fColors[chan].fCount, fColors[chan].fSame);
        unsigned short count = fColors[chan].fCount;
        if (fColors[chan].fSame)
            count |= 0x8000;
        S->writeShort(count);
        count &= 0x7FFF;
        if (fColors[chan].fSame)
            S->writeByte(*src);
    }
    if (!fColors[chan].fSame)
        S->writeByte(*src);
    src += sizeof(unsigned char);
    fColors[chan].fCount--;
}

#define FloatToShort(x) (hsInt16)(signed short)(x)
#define FloatToByte(x) (hsUbyte)(unsigned char)(x)

void plVertCoder::IEncodeFloat(hsStream* S, unsigned int vertsLeft, int field,
                               int chan, const unsigned char*& src,
                               unsigned int stride) {
    if (fFloats[chan][field].fCount == 0) {
        ICountFloats(vertsLeft, src, FieldScales[field], stride,
                     fFloats[chan][field].fOffset,
                     fFloats[chan][field].fAllSame,
                     fFloats[chan][field].fCount);
        S->writeFloat(fFloats[chan][field].fOffset);
        if (S->getVer() == pvLive)
            S->writeBool(fFloats[chan][field].fAllSame);
        S->writeShort(fFloats[chan][field].fCount);
    }

    if (S->getVer() != pvLive || (!fFloats[chan][field].fAllSame)) {
        float flt = *(float*)src;
        flt = (flt - fFloats[chan][field].fOffset) * FieldScales[field];
        S->writeShort((signed short)(flt + 0.5f));
    }
    src += sizeof(float);
    fFloats[chan][field].fCount--;
}

void plVertCoder::IEncodeNormal(hsStream* S, const unsigned char*& src) {
    if (S->getVer() == pvLive) {
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
                               const unsigned char*& src, unsigned int stride) {
    IEncodeByte(S, vertsLeft, 0, src, stride);
    IEncodeByte(S, vertsLeft, 1, src, stride);
    IEncodeByte(S, vertsLeft, 2, src, stride);
    IEncodeByte(S, vertsLeft, 3, src, stride);
}

void plVertCoder::ICountBytes(unsigned int vertsLeft, const unsigned char* src,
                              unsigned int stride, unsigned short& len, bool& same) {
    if (vertsLeft < 4) {
        len = vertsLeft;
        same = false;
        return;
    }

    unsigned int i = 0;
    if (vertsLeft > 0) {
        unsigned char rle = *src;
        while (i < vertsLeft && *src == rle) {
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
    while (i < vertsLeft - 4) {
        unsigned char b0 = *(src + ((i+0)*stride));
        unsigned char b1 = *(src + ((i+1)*stride));
        unsigned char b2 = *(src + ((i+2)*stride));
        unsigned char b3 = *(src + ((i+3)*stride));
        if (b0 == b1 && b0 == b2 && b0 == b3)
            break;
        i++;
        src += stride;
    }
    if (i < vertsLeft - 4)
        len = i;
    else
        len = vertsLeft;
}

void plVertCoder::ICountFloats(unsigned int vertsLeft, const unsigned char* src,
                               float quant, unsigned int stride, float& lo,
                               bool& allSame, unsigned short& count) {
    lo = floor(((*(float*)src) * quant) + 0.5f) / quant;
    float hi = lo;
    allSame = false;
    count = 1;
    float maxRange = 32767.0f / quant;

    src += stride;
    while (--vertsLeft > 0) {
        float cur = floor(((*(float*)src) * quant) + 0.5f) / quant;
        if (cur < lo) {
            if (hi - cur >= maxRange)
                return;
            lo = cur;
        } else if (cur > hi) {
            if (cur - lo >= maxRange)
                return;
            hi = cur;
        }
        count++;
        src += stride;
    }

    allSame = (hi == lo) ? true : false;
}
