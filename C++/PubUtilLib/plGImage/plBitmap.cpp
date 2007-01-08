#include "plBitmap.h"

plBitmap::plBitmap() : version(0), BPP(0), CPB(0), flags(0), imgType(0),
                       texelSize(0), texelType(0), Unk1(0), Unk2(0) { }

plBitmap::~plBitmap() { }

void plBitmap::read(hsStream * S) {
    hsKeyedObject::read(S);

    version = S->readByte();
    BPP = S->readByte();
    CPB = S->readByte();
    flags = S->readShort();
    imgType = S->readByte();
    if (imgType && (imgType != IMG_JPEG))
        texelSize = S->readByte();
    else texelSize = 0;
    texelType = S->readByte();
    Unk1 = S->readShort();
    Unk2 = S->readShort();
}

void plBitmap::write(hsStream * S) {
    hsKeyedObject::write(S);

    S->writeByte(version);
    S->writeByte(BPP);
    S->writeByte(CPB);
    S->writeShort(flags);
    S->writeByte(imgType);
    if (imgType && (imgType != IMG_JPEG))
        S->writeByte(texelSize);
    S->writeByte(texelType);
    S->writeShort(Unk1);
    S->writeShort(Unk2);
}

