#include "plBitmap.h"

const char* plBitmap::compressionTypeNames[] = {
    "Uncompressed", "DDS", "JPEG"
};

const char* plBitmap::uncompressedTypeNames[] = {
    "RGB8888", "RGB4444", "RGB1555", "Inten8", "AInten88"
};

const char* plBitmap::compressedTypeNames[] = {
    "Error", "DXT1", "DXT2", "DXT3", "DXT4", "DXT5"
};


plBitmap::plBitmap() : pixelSize(0), space(0), flags(0), compressionType(0),
                       lowModTime(0), highModTime(0) { }
plBitmap::~plBitmap() { }

IMPLEMENT_CREATABLE(plBitmap, kBitmap, hsKeyedObject)

void plBitmap::read(hsStream* S) {
    hsKeyedObject::read(S);
    readData(S);
}

void plBitmap::write(hsStream* S) {
    hsKeyedObject::write(S);
    writeData(S);
}

void plBitmap::readData(hsStream* S) {
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

void plBitmap::writeData(hsStream* S) {
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

void plBitmap::prcWrite(pfPrcHelper* prc) {
    hsKeyedObject::prcWrite(prc);

    prc->startTag("BitmapFlags");
    prc->writeParam("PixelSize", pixelSize);
    prc->writeParam("Space", space);
    prc->writeParam("Flags", flags);
    prc->endTag(true);

    prc->startTag("Compression");
    prc->writeParam("Type", compressionTypeNames[compressionType]);
    if (compressionType == kUncompressed || compressionType == kJPEGCompression)
        prc->writeParam("SubType", uncompressedTypeNames[uncompressedInfo.type]);
    else {
        prc->writeParam("SubType", compressedTypeNames[dxInfo.compressionType]);
        prc->writeParam("BlockSize", dxInfo.blockSize);
    }
    prc->endTag(true);

    prc->startTag("ModTime");
    prc->writeParam("low", lowModTime);
    prc->writeParam("high", highModTime);
    prc->endTag(true);
}
