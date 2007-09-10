#include "plMipmap.h"
#include "../plJPEG/plJPEG.h"
#include <string.h>
#include <stdlib.h>

plMipmap::plMipmap() {
    ImageData = NULL;
    JPEGData = NULL;
    AlphaData = NULL;
    levelSizes = NULL;
    curLevelPtr = NULL;
    AlphaSize = JPEGSize = totalSize = 0;
    pixelSize = 32;
    space = 1;
    flags = kAlphaChannelFlag;
}

plMipmap::plMipmap(int w, int h, int cfg, char nLevels, char compType,
                   char format) {
    ImageData = NULL;
    JPEGData = NULL;
    AlphaData = NULL;
    levelSizes = NULL;
    curLevelPtr = NULL;
    AlphaSize = JPEGSize = totalSize = 0;
    pixelSize = 32;
    space = 1;
    flags = kAlphaChannelFlag;
    create(w, h, cfg, nLevels, compType, format);
}

plMipmap::~plMipmap() {
    if (ImageData != NULL) free(ImageData);
    if (JPEGData != NULL) free(JPEGData);
    if (AlphaData != NULL) free(AlphaData);
    if (levelSizes != NULL) delete[] levelSizes;
}

IMPLEMENT_CREATABLE(plMipmap, kMipmap, plBitmap)

void plMipmap::create(int w, int h, int cfg, char nLevels, char compType,
                      char format) {
    setConfig(cfg);
    stride = (pixelSize * w) >> 3;
    width = w;
    height = h;
    
    if (nLevels > 0) {
        numLevels = nLevels;
    } else {
        numLevels = 1;
        while (w > 1 && h > 1) {
            if (w > 1) w >>= 1;
            if (h > 1) h >>= 1;
            numLevels++;
        }
    }

    compressionType = compType;
    if (compType == kUncompressed || compType == kJPEGCompression) {
        uncompressedInfo.type = format;
    } else {
        dxInfo.compressionType = format;
        dxInfo.blockSize = (format != DirectXInfo::kDXT1 ? 1 : 0);
        if (format == DirectXInfo::kDXT1) {
            flags &= ~kAlphaChannelFlag;
            flags |= kAlphaBitFlag;
        } else {
            flags &= ~kAlphaBitFlag;
            flags |= kAlphaChannelFlag;
        }
    }

    if (levelSizes != NULL) delete[] levelSizes;
    levelSizes = NULL;
    IBuildLevelSizes();
    totalSize = 0;
    for (int i=0; i<numLevels; i++)
        totalSize += levelSizes[i];
    ImageData = malloc(totalSize);
    memset(ImageData, 0, totalSize);
    //setCurrLevel(0);
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

const void* plMipmap::getJPEGData() { return JPEGData; }
unsigned int plMipmap::getJPEGSize() { return JPEGSize; }
const void* plMipmap::getAlphaData() { return AlphaData; }
unsigned int plMipmap::getAlphaSize() { return AlphaSize; }

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

void plMipmap::prcWrite(pfPrcHelper* prc) {
    plBitmap::prcWrite(prc);

    prc->startTag("Metrics");
    prc->writeParam("Width", width);
    prc->writeParam("Height", height);
    prc->writeParam("Stride", stride);
    prc->writeParam("TotalSize", totalSize);
    prc->writeParam("MipLevels", numLevels);
    prc->endTag(true);

    if (compressionType == kJPEGCompression) {
        prc->startTag("JPEG");
        prc->writeParam("src", "");
        prc->writeParam("ImageRLE", JPEGData == NULL);
        prc->writeParam("AlphaRLE", AlphaData == NULL);
        prc->endTag(true);
    } else {
        prc->startTag("DDS");
        prc->writeParam("src", "");
        prc->endTag(true);
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
    plMipmap* img = new plMipmap(width, height, kARGB32Config, 1, 0, 0);
    int* dataPtr = (int*)img->ImageData;
    while (true) {
        int count = S->readInt();
        int data = S->readInt();
        if (count == 0) break;
        for (int i=0; i<count; i++) {
            *dataPtr = data;
            dataPtr++;
        }
    }
    return img;
}

void plMipmap::IWriteRLEImage(hsStream* S, plMipmap* img) {
    int* dataPtr = (int*)img->ImageData;
    int data = *dataPtr;
    int count = 0;
    for (int i=(levelSizes[0] >> 2); i>0; i--) {
        if ((*dataPtr & 0x00FFFFFF) != data) {
            S->writeInt(count);
            S->writeInt(data);
            count = 0;
            data = *dataPtr;
        }
        count++;
        dataPtr++;
    }
    S->writeInt(count);
    S->writeInt(data);
    
    // Stop indicator
    S->writeInt(0);
    S->writeInt(0);
}

void plMipmap::IReadJPEGImage(hsStream* S) {
    char rleFlag = S->readByte();
    plMipmap* img;

    if (rleFlag & kColorDataRLE)
        img = IReadRLEImage(S);
    else {
        //img = plJPEG::inst->IRead(S);
        // Until plJPEG is fixed
        img = NULL;
        JPEGSize = S->readInt();
        JPEGData = malloc(JPEGSize);
        S->read(JPEGSize, JPEGData);
    }
    if (img != NULL) {
        ICopyImage(img);
        delete img;
    }

    if (rleFlag & kAlphaDataRLE)
        img = IReadRLEImage(S);
    else {
        //img = plJPEG::inst->IRead(S);
        img = NULL;
        AlphaSize = S->readInt();
        AlphaData = malloc(AlphaSize);
        S->read(AlphaSize, AlphaData);
    }
    if (img != NULL) {
        IRecombineAlpha(img);
        delete img;
    }
}

void plMipmap::IWriteJPEGImage(hsStream* S) {
    char rleFlag = 0;
    if (JPEGData == NULL)
        rleFlag |= kColorDataRLE;
    if (AlphaData == NULL)
        rleFlag |= kAlphaDataRLE;
    S->writeByte(rleFlag);

    if (rleFlag & kColorDataRLE)
        IWriteRLEImage(S, this);
    else {
        S->writeInt(JPEGSize);
        S->write(JPEGSize, JPEGData);
    }

    if (rleFlag & kAlphaDataRLE)
        IWriteRLEImage(S, ISplitAlpha());
    else {
        S->writeInt(AlphaSize);
        S->write(AlphaSize, AlphaData);
    }
}

void plMipmap::IReadRawImage(hsStream* S) {
    unsigned char* dataPtr = (unsigned char*)ImageData;
    if (pixelSize == 32) {
        if (numLevels <= 0) return;
        for (int i=0; i<numLevels; i++) {
            S->readInts(levelSizes[i] >> 2, (int32*)dataPtr);
            dataPtr += levelSizes[i];
        }
    } else if (pixelSize == 16) {
        if (numLevels <= 0) return;
        for (int i=0; i<numLevels; i++) {
            S->readShorts(levelSizes[i] >> 1, (int16*)dataPtr);
            dataPtr += levelSizes[i];
        }
    } else
        throw "Bad Parameters";
}

void plMipmap::IWriteRawImage(hsStream* S) {
    unsigned char* dataPtr = (unsigned char*)ImageData;
    if (pixelSize == 32) {
        if (numLevels <= 0) return;
        for (int i=0; i<numLevels; i++) {
            S->writeInts(levelSizes[i] >> 2, (int32*)dataPtr);
            dataPtr += levelSizes[i];
        }
    } else if (pixelSize == 16) {
        if (numLevels <= 0) return;
        for (int i=0; i<numLevels; i++) {
            S->writeShorts(levelSizes[i] >> 1, (int16*)dataPtr);
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

plMipmap* plMipmap::ISplitAlpha() {
    plMipmap* alpha = new plMipmap();
    alpha->CopyFrom(this);
    memset(alpha->ImageData, 0, alpha->totalSize);
    if (uncompressedInfo.type == UncompressedInfo::kRGB8888) {
        for (int i=((totalSize-1)/4)+1; i>0; i--)
            ((char*)alpha->ImageData)[(i*4)+2] = ((char*)ImageData)[(i*4)+3];
    }
    return alpha;
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

void plMipmap::ICopyImage(plMipmap* src) {
    if (ImageData != NULL) free(ImageData);
    width = src->width;
    height = src->height;
    stride = src->stride;
    pixelSize = src->pixelSize;
    totalSize = src->totalSize;
    ImageData = malloc(totalSize);
    memcpy(ImageData, src->ImageData, totalSize);
    IBuildLevelSizes();
}
