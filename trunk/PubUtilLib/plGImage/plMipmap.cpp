#include "plMipmap.h"
#include <string.h>
#include <stdlib.h>

plMipmap::plMipmap(PlasmaVer pv) : ImageData(NULL), levelSizes(NULL) { }

plMipmap::plMipmap(int w, int h, int cfg, char nLevels, char compType,
                   char format, PlasmaVer pv) : plBitmap(pv) {
    create(w, h, cfg, nLevels, compType, format);
}

plMipmap::~plMipmap() {
    if (ImageData != NULL)
        free(ImageData);
    if (levelSizes != NULL)
        delete[] levelSizes;
}

unsigned short plMipmap::ClassIndex() { return 4; }

void plMipmap::create(int w, int h, int cfg, char nLevels, char compType,
                      char format) {
    setConfig(cfg);
    stride = (pixelSize * w) >> 3;
    width = w;
    height = h;
    if (nLevels > 0)
        numLevels = nLevels;
    throw "Incomplete";
}

void plMipmap::setConfig(int cfg) {
    switch (cfg) {
    case kColor8Config:
        pixelSize = 8;
        space = 3;
        flags = kNoFlag;
        break;
    case kGray44Config:
        pixelSize = 8;
        space = 2;
        flags = kAlphaChannelFlag;
        break;
    case kGray4Config:
        pixelSize = 4;
        space = 2;
        flags = kNoFlag;
        break;
    case kGray8Config:
        pixelSize = 8;
        space = 1;
        flags = kNoFlag;
        break;
    case kRGB16Config:
        pixelSize = 16;
        space = 1;
        flags = kAlphaBitFlag;
        break;
    case kRGB32Config:
        pixelSize = 32;
        space = 1;
        flags = kNoFlag;
    case kARGB32Config:
        pixelSize = 32;
        space = 1;
        flags = kAlphaChannelFlag;
        break;
    }
}

void plMipmap::readData(hsStream* S) {
    plBitmap::readData(S);
    
    width = S->readInt();
    height = S->readInt();
    stride = S->readInt();
    totalSize = S->readInt();
    numLevels = S->readByte();

    if (ImageData != NULL) {
        free(ImageData);
        ImageData = NULL;
    }
    if (totalSize == 0)
        return;

    IBuildLevelSizes();
    ImageData = malloc(totalSize);
    switch (compressionType) {
    case kJPEGCompression:
        IReadJPEGImage(S);
        break;
    case kDirectXCompression:
        S->read(totalSize, ImageData);
        break;
    case kUncompressed:
        IReadRawImage(S);
        break;
    }
}

void plMipmap::writeData(hsStream* S) {
    plBitmap::writeData(S);

    S->writeInt(width);
    S->writeInt(height);
    S->writeInt(stride);
    S->writeInt(totalSize);
    S->writeByte(numLevels);

    if (totalSize == 0)
        return;

    switch (compressionType) {
    case kJPEGCompression:
        IWriteJPEGImage(S);
        break;
    case kDirectXCompression:
        S->write(totalSize, ImageData);
        break;
    case kUncompressed:
        IWriteRawImage(S);
        break;
    }
}

void plMipmap::IBuildLevelSizes() {
    if (levelSizes != NULL)
        delete[] levelSizes;
    levelSizes = new unsigned int[numLevels];
    memset(levelSizes, 0, numLevels * sizeof(unsigned int));

    int curWidth = width;
    int curStride = stride;
    int curHeight = height;

    if (numLevels <= 0) return;
    for (int i=0; i<numLevels; i++) {
        if (compressionType > 2) return;
        if (compressionType == kDirectXCompression &&
            !((curHeight | curWidth) & 3))
            levelSizes[i] = (dxInfo.blockSize * curHeight * curWidth) >> 4;
        else
            levelSizes[i] = curStride * curHeight;
        if (curWidth > 1) {
            curWidth >>= 1;
            curStride >>= 1;
        }
        if (curHeight > 1)
            curHeight >>= 1;
    }
}

plMipmap* plMipmap::IReadRLEImage(hsStream* S) {
    plMipmap* img = new plMipmap(width, height, kARGB32Config, 1, 0, 0, ver);
    int* dataPtr = (int*)img->ImageData;
    while (true) {
        int count = S->readInt();
        int data = S->readInt();
        if (count == 0) break;
        for (int i=0; i<count; i++) {
            *dataPtr = data;
            dataPtr += sizeof(data);
        }
    }
    return img;
}

void plMipmap::IReadJPEGImage(hsStream* S) {
    char rleFlag = S->readByte();
    plMipmap* img, * alpha;
    if (rleFlag & kColorDataRLE)
        img = IReadRLEImage(S);
    else {
        throw "JPEG not yet supported";
    }
    if (img == NULL) return;
    CopyFrom(img);

    if (rleFlag & kAlphaDataRLE)
        alpha = IReadRLEImage(S);
    else
        throw "JPEG not yet supported";
    if (alpha != NULL) {
        IRecombineAlpha(alpha);
        delete alpha;
    }
    delete img;
}

void plMipmap::IWriteJPEGImage(hsStream* S) {
    throw "JPEG not yet supported!";
}

void plMipmap::IReadRawImage(hsStream* S) {
    if (pixelSize == 32) {
        if (numLevels <= 0) return;
        int* dataPtr = (int*)ImageData;
        for (int i=0; i<numLevels; i++) {
            S->readInts(levelSizes[i] >> 2, dataPtr);
            dataPtr += levelSizes[i];
        }
    } else if (pixelSize == 16) {
        if (numLevels <= 0) return;
        short* dataPtr = (short*)ImageData;
        for (int i=0; i<numLevels; i++) {
            S->readShorts(levelSizes[i] >> 1, dataPtr);
            dataPtr += levelSizes[i];
        }
    } else
        throw "Bad Parameters";
}

void plMipmap::IWriteRawImage(hsStream* S) {
    if (pixelSize == 32) {
        if (numLevels <= 0) return;
        int* dataPtr = (int*)ImageData;
        for (int i=0; i<numLevels; i++) {
            S->writeInts(levelSizes[i] >> 2, dataPtr);
            dataPtr += levelSizes[i];
        }
    } else if (pixelSize == 16) {
        if (numLevels <= 0) return;
        short* dataPtr = (short*)ImageData;
        for (int i=0; i<numLevels; i++) {
            S->writeShorts(levelSizes[i] >> 1, dataPtr);
            dataPtr += levelSizes[i];
        }
    } else
        throw "Bad Parameters";
}

void plMipmap::IRecombineAlpha(plMipmap* alphaImg) {
    if (uncompressedInfo.type == UncompressedInfo::kRGB8888) {
        for (int i=((totalSize-1)/4)+1; i>0; i--)
            ((char*)ImageData)[(i*4)+3] = ((char*)alphaImg->ImageData)[(i*4)+2];
    }
    flags |= kAlphaChannelFlag;
}

void plMipmap::CopyFrom(plMipmap* src) {
    if (ImageData != NULL) free(ImageData);
    width = src->width;
    height = src->height;
    stride = src->stride;
    pixelSize = src->pixelSize;
    flags = src->flags;
    space = src->space;
    compressionType = src->compressionType;
    totalSize = src->totalSize;
    ImageData = malloc(totalSize);
    memcpy(ImageData, src->ImageData, totalSize);
    numLevels = src->numLevels;
    if (compressionType == kUncompressed ||
        compressionType == kJPEGCompression)
        uncompressedInfo.type = src->uncompressedInfo.type;
    else if (compressionType == kDirectXCompression) {
        dxInfo.compressionType = src->dxInfo.compressionType;
        dxInfo.blockSize = src->dxInfo.compressionType;
    }
    IBuildLevelSizes();
    // if (GetDeviceRef()) GetDeviceRef()->flags |= kDirty;
}

