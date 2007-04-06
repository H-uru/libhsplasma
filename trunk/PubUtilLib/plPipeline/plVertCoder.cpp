#include <string.h>
#include "plVertCoder.h"

float plVertCoder::FieldScales[] = {
   1024.0, 32768.0, 65536.0, 65536.0, 65536.0,
   65536.0, 65536.0, 65536.0, 65536.0, 65536.0
};

plVertCoder::plVertCoder() { }
plVertCoder::~plVertCoder() { }

void plVertCoder::read(hsStream* S, unsigned char* dest, unsigned char format,
                       unsigned int stride, unsigned short numVerts) {
    memset(this, 0, sizeof(plVertCoder));
    for (unsigned short i=0; i<numVerts; i++)
        IDecode(S, dest, stride, format);
}

void plVertCoder::IDecode(hsStream* S, unsigned char* dest, unsigned int stride,
                          unsigned char format) {
    // The X, Y, Z coordinates of this vertex
    IDecodeFloat(S, kPosition, 0, dest, stride);
    IDecodeFloat(S, kPosition, 1, dest, stride);
    IDecodeFloat(S, kPosition, 2, dest, stride);

    // Weights
    int count = (format >> 4) & 3;
    for (int i=0; i<count; i++)
        IDecodeFloat(S, kWeight, i, dest, stride);

    // Skin index
    if (format & kSkinIndices) {
        *(int*)dest = S->readInt();
        dest += sizeof(int);
    }

    // Normal (polygon face)
    IDecodeNormal(S, dest, stride);
    IDecodeByte(S, 0, dest, stride);
    IDecodeByte(S, 1, dest, stride);
    IDecodeByte(S, 2, dest, stride);
    IDecodeByte(S, 3, dest, stride);

    // UVW maps
    for (int i=0; i<(format & kUVCountMask); i++) {
        IDecodeFloat(S, kUVW, 0, dest, stride);
        IDecodeFloat(S, kUVW, 1, dest, stride);
        IDecodeFloat(S, kUVW, 2, dest, stride);
    }
}

void plVertCoder::IDecodeFloat(hsStream* S, int field, int chan,
                               unsigned char* dest, unsigned int stride) {
    if (fFloats[chan][field].fCount != 0) {
        fFloats[chan][field].fOffset = S->readFloat();
        if (S->getVer() == pvLive)
            fFloats[chan][field].fAllSame = S->readBool();
        else
            fFloats[chan][field].fAllSame = false;
        fFloats[chan][field].fCount = S->readShort();
    }
    if (fFloats[chan][field].fAllSame)
        *(float*)dest = fFloats[chan][field].fOffset;
    else
        *(float*)dest = fFloats[chan][field].fOffset +
                       (S->readShort() / FieldScales[field]);
    dest += sizeof(float);
    fFloats[chan][field].fCount--;
}

void plVertCoder::IDecodeNormal(hsStream* S, unsigned char* dest,
                                unsigned int stride) {
    if (S->getVer() == pvLive) {
        ((float*)dest)[0] = ((S->readByte() / 256.0) - 0.5) * 2.0;
        ((float*)dest)[1] = ((S->readByte() / 256.0) - 0.5) * 2.0;
        ((float*)dest)[2] = ((S->readByte() / 256.0) - 0.5) * 2.0;
    } else {
        ((float*)dest)[0] = S->readShort() / 32767.0;
        ((float*)dest)[1] = S->readShort() / 32767.0;
        ((float*)dest)[2] = S->readShort() / 32767.0;
    }
    dest += sizeof(float) * 3;
}

void plVertCoder::IDecodeByte(hsStream* S, int chan, unsigned char* dest,
                              unsigned int stride) {
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
        *dest = fColors[chan].fVal;
    else
        *dest = S->readByte();
    dest += sizeof(unsigned char);
    fColors[chan].fCount--;
}

