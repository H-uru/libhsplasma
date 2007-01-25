#include "plBitmap.h"

plBitmap::plBitmap(PlasmaVer pv) : pixelSize(0), space(0), flags(0),
                   compressionType(0), lowModTime(0), highModTime(0) { }

plBitmap::~plBitmap() { }

void plBitmap::read(hsStream * S) {
    hsKeyedObject::read(S);
    readData(S);
}

void plBitmap::write(hsStream * S) {
    hsKeyedObject::write(S);
    writeData(S);
}

void plBitmap::readData(hsStream * S) {
    S->readByte();  // Version == 2
    pixelSize = S->readByte();
    space = S->readByte();
    flags = S->readShort();
    compressionType = S->readByte();
    if (compressionType == kUncompressed || compressionType == kJPEGCompression)
        uncompressedInfo.type = S->readByte();
    else {
        dxInfo.blockSize = S->readByte();
        dxInfo.compressionType = S->readByte();
    }
    lowModTime = S->readInt();
    highModTime = S->readInt();
}

void plBitmap::writeData(hsStream * S) {
    S->writeByte(BITMAPVER);
    S->writeByte(pixelSize);
    S->writeByte(space);
    S->writeShort(flags);
    S->writeByte(compressionType);
    if (compressionType == kUncompressed || compressionType == kJPEGCompression)
        S->writeByte(uncompressedInfo.type);
    else {
        S->writeByte(dxInfo.blockSize);
        S->writeByte(dxInfo.compressionType);
    }
    S->writeInt(lowModTime);
    S->writeInt(highModTime);
}

