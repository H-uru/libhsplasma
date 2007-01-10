#include "plBitmap.h"

plBitmap::plBitmap(PlasmaVer pv) : BPP(0), CPB(0), flags(0), imgType(0),
                       texelSize(0), texelType(0), Unk1(0), Unk2(0) { }

plBitmap::~plBitmap() { }

void plBitmap::read(hsStream * S) {
    hsKeyedObject::read(S);
    readData(S);
}

void plBitmap::readData(hsStream * S) {
    S->readByte();  // Version == 2
    BPP = S->readByte();
    CPB = S->readByte();
    flags = S->readShort();
    imgType = S->readByte();
    if ((imgType != IMG_ARGB) && (imgType != IMG_JPEG))
        texelSize = S->readByte();
    else texelSize = 0;
    texelType = S->readByte();
    Unk1 = S->readInt();
    Unk2 = S->readInt();
}

void plBitmap::write(hsStream * S) {
    hsKeyedObject::write(S);
    writeData(S);
}

void plBitmap::writeData(hsStream * S) {
    S->writeByte(BITMAPVER);
    S->writeByte(BPP);
    S->writeByte(CPB);
    S->writeShort(flags);
    S->writeByte(imgType);
    if ((imgType != IMG_ARGB) && (imgType != IMG_JPEG))
        S->writeByte(texelSize);
    S->writeByte(texelType);
    S->writeInt(Unk1);
    S->writeInt(Unk2);
}
