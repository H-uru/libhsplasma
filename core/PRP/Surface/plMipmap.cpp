#include "plMipmap.h"
#include <cstring>
#include <cstdlib>

plMipmap::plMipmap()
        : fImageData(NULL), fTotalSize(0), fJPEGData(NULL), fJPEGSize(0),
          fAlphaData(NULL), fAlphaSize(0), fJPEGDataRLE(NULL),
          fAlphaDataRLE(NULL), fNumLevels(0), fLevelSizes(NULL) {
    fPixelSize = 32;
    fSpace = kDirectSpace;
    fFlags = kAlphaChannelFlag;
}

plMipmap::plMipmap(unsigned int width, unsigned int height, unsigned int cfg,
                   unsigned char numLevels, unsigned char compType,
                   unsigned char format)
        : fImageData(NULL), fTotalSize(0), fJPEGData(NULL), fJPEGSize(0),
          fAlphaData(NULL), fAlphaSize(0), fJPEGDataRLE(NULL),
          fAlphaDataRLE(NULL), fNumLevels(0), fLevelSizes(NULL) {
    fPixelSize = 32;
    fSpace = kDirectSpace;
    fFlags = kAlphaChannelFlag;
    Create(width, height, cfg, numLevels, compType, format);
}

plMipmap::~plMipmap() {
    if (fImageData != NULL) delete[] fImageData;
    if (fJPEGData != NULL) delete[] fJPEGData;
    if (fAlphaData != NULL) delete[] fAlphaData;
    if (fLevelSizes != NULL) delete[] fLevelSizes;
    if (fJPEGDataRLE != NULL) delete fJPEGDataRLE;
    if (fAlphaDataRLE != NULL) delete fAlphaDataRLE;
}

IMPLEMENT_CREATABLE(plMipmap, kMipmap, plBitmap)

void plMipmap::Create(unsigned int width, unsigned int height, unsigned int cfg,
                      unsigned char numLevels, unsigned char compType,
                      unsigned char format) {
    setConfig(cfg);
    fStride = (fPixelSize * width) / 8;
    fWidth = width;
    fHeight = height;
    
    if (numLevels > 0) {
        fNumLevels = numLevels;
    } else {
        fNumLevels = 1;
        while (width > 1 && height > 1) {
            if (width > 1)
                width /= 2;
            if (height > 1)
                height /= 2;
            numLevels++;
        }
    }

    fCompressionType = compType;
    if (compType == kUncompressed || compType == kJPEGCompression) {
        fUncompressedInfo.fType = format;
    } else {
        fDXInfo.fCompressionType = format;
        fDXInfo.fBlockSize = (format != kDXT1 ? 1 : 0);
        if (format == kDXT1) {
            fFlags &= ~kAlphaChannelFlag;
            fFlags |= kAlphaBitFlag;
        } else {
            fFlags &= ~kAlphaBitFlag;
            fFlags |= kAlphaChannelFlag;
        }
    }

    if (fLevelSizes != NULL)
        delete[] fLevelSizes;
    fLevelSizes = NULL;
    IBuildLevelSizes();
    fTotalSize = 0;
    for (size_t i=0; i<fNumLevels; i++)
        fTotalSize += fLevelSizes[i];
    fImageData = new unsigned char[fTotalSize];
    memset(fImageData, 0, fTotalSize);
}

void plMipmap::setConfig(unsigned int cfg) {
    switch (cfg) {
    case kColor8Config:
        fPixelSize = 8;
        fSpace = 3;
        fFlags = kNoFlag;
        break;
    case kGray44Config:
        fPixelSize = 8;
        fSpace = 2;
        fFlags = kAlphaChannelFlag;
        break;
    case kGray4Config:
        fPixelSize = 4;
        fSpace = 2;
        fFlags = kNoFlag;
        break;
    case kGray8Config:
        fPixelSize = 8;
        fSpace = 1;
        fFlags = kNoFlag;
        break;
    case kRGB16Config:
        fPixelSize = 16;
        fSpace = 1;
        fFlags = kAlphaBitFlag;
        break;
    case kRGB32Config:
        fPixelSize = 32;
        fSpace = 1;
        fFlags = kNoFlag;
    case kARGB32Config:
        fPixelSize = 32;
        fSpace = 1;
        fFlags = kAlphaChannelFlag;
        break;
    }
}

void plMipmap::readData(hsStream* S) {
    plBitmap::readData(S);
    
    fWidth = S->readInt();
    fHeight = S->readInt();
    fStride = S->readInt();
    fTotalSize = S->readInt();
    fNumLevels = S->readByte();

    if (fImageData != NULL) {
        delete[] fImageData;
        fImageData = NULL;
    }
    if (fTotalSize == 0)
        return;

    IBuildLevelSizes();
    fImageData = new unsigned char[fTotalSize];
    switch (fCompressionType) {
    case kJPEGCompression:
        IReadJPEGImage(S);
        break;
    case kDirectXCompression:
        S->read(fTotalSize, fImageData);
        break;
    case kUncompressed:
        IReadRawImage(S);
        break;
    }
}

void plMipmap::writeData(hsStream* S) {
    plBitmap::writeData(S);

    S->writeInt(fWidth);
    S->writeInt(fHeight);
    S->writeInt(fStride);
    S->writeInt(fTotalSize);
    S->writeByte(fNumLevels);

    if (fTotalSize == 0)
        return;

    switch (fCompressionType) {
    case kJPEGCompression:
        IWriteJPEGImage(S);
        break;
    case kDirectXCompression:
        S->write(fTotalSize, fImageData);
        break;
    case kUncompressed:
        IWriteRawImage(S);
        break;
    }
}

void plMipmap::IPrcWrite(pfPrcHelper* prc) {
    plBitmap::IPrcWrite(prc);

    prc->startTag("Metrics");
    prc->writeParam("Width", fWidth);
    prc->writeParam("Height", fHeight);
    prc->writeParam("Stride", fStride);
    prc->writeParam("TotalSize", fTotalSize);
    prc->writeParam("MipLevels", fNumLevels);
    prc->endTag(true);

    if (fCompressionType == kJPEGCompression) {
        prc->startTag("JPEG");
        prc->writeParam("ImageRLE", fJPEGData == NULL);
        prc->writeParam("AlphaRLE", fAlphaData == NULL);
        prc->endTag();
        
        prc->writeSimpleTag("Image");
        if (!prc->isExcluded(pfPrcHelper::kExcludeTextureData)) {
            if (fJPEGData == NULL)
                prc->writeHexStream(fJPEGDataRLE->fTotalSize, fJPEGDataRLE->fImageData);
            else
                prc->writeHexStream(fJPEGSize, fJPEGData);
        } else {
            prc->writeComment("Texture data excluded");
        }
        prc->closeTag();    // Image
        prc->writeSimpleTag("Alpha");
        if (!prc->isExcluded(pfPrcHelper::kExcludeTextureData)) {
            if (fAlphaData == NULL)
                prc->writeHexStream(fAlphaDataRLE->fTotalSize, fAlphaDataRLE->fImageData);
            else
                prc->writeHexStream(fAlphaSize, fAlphaData);
        } else {
            prc->writeComment("Texture data excluded");
        }
        prc->closeTag();    // Alpha
        
        prc->closeTag();    // JPEG
    } else {
        prc->writeSimpleTag("DDS");
        prc->writeHexStream(fTotalSize, fImageData);
        prc->closeTag();
    }
}

void plMipmap::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Metrics") {
        fWidth = tag->getParam("Width", "0").toUint();
        fHeight = tag->getParam("Height", "0").toUint();
        fStride = tag->getParam("Stride", "0").toUint();
        fTotalSize = tag->getParam("TotalSize", "0").toUint();
        fNumLevels = tag->getParam("MipLevels", "0").toUint();
    } else if (tag->getName() == "JPEG") {
        IBuildLevelSizes();
        if (tag->getParam("ImageRLE", "false").toBool()) {
            fJPEGDataRLE = new plMipmap(fWidth, fHeight, kARGB32Config, 1, 0, 0);
            tag->readHexStream(fJPEGDataRLE->fTotalSize, fJPEGDataRLE->fImageData);
        } else {
            fJPEGSize = tag->getContents().getSize();
            fJPEGData = new unsigned char[fJPEGSize];
            tag->readHexStream(fJPEGSize, fJPEGData);
        }
        if (tag->getParam("AlphaRLE", "false").toBool()) {
            fAlphaDataRLE = new plMipmap(fWidth, fHeight, kARGB32Config, 1, 0, 0);
            tag->readHexStream(fAlphaDataRLE->fTotalSize, fAlphaDataRLE->fImageData);
        } else {
            fAlphaSize = tag->getContents().getSize();
            fAlphaData = new unsigned char[fAlphaSize];
            tag->readHexStream(fAlphaSize, fAlphaData);
        }
    } else if (tag->getName() == "DDS") {
        if (tag->getContents().getSize() != fTotalSize)
            throw pfPrcParseException(__FILE__, __LINE__, "DDS Data is not of the correct length");
        IBuildLevelSizes();
        if (fTotalSize > 0) {
            fImageData = new unsigned char[fTotalSize];
            tag->readHexStream(fTotalSize, fImageData);
        }
    } else {
        plBitmap::IPrcParse(tag, mgr);
    }
}

void ExportDDS(hsStream* S, bool isDXT, plMipmap* img) {
    S->write(4, "DDS ");

    // DDSURFACEDESC
    S->writeInt(124);   // sizeof(DDSURFACEDESC)
    S->writeInt(isDXT ? 0x000A1007  // DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH |
                                    // DDSD_PIXELFORMAT | DDSD_MIPMAPCOUNT |
                                    // DDSD_LINEARSIZE
                      : 0x0000100F);// DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH |
                                    // DDSD_PITCH | DDSD_PIXELFORMAT

    S->writeInt(img->getHeight());
    S->writeInt(img->getWidth());
    if (isDXT) {
        unsigned int size = img->getHeight() * img->getWidth();
        if (img->getDXCompression() == plBitmap::kDXT1)
            size /= 2;
        S->writeInt(size);
    } else {
        S->writeInt(img->getWidth() * 4);
    }
    S->writeInt(0); // Depth
    S->writeInt(img->getNumLevels());
    for (size_t i=0; i<11; i++)
        S->writeInt(0); // Unused

    // DDPIXELFORMAT
    S->writeInt(32);    // sizeof(DDPIXELFORMAT)
    if (isDXT) {
        S->writeInt(0x00000004);    // DDPF_FOURCC
        if (img->getDXCompression() == plBitmap::kDXT1)
            S->write(4, "DXT1");
        else if (img->getDXCompression() == plBitmap::kDXT5)
            S->write(4, "DXT5");
        S->writeInt(0); // RGBBitCount
        S->writeInt(0); // RBitMask
        S->writeInt(0); // GBitMask
        S->writeInt(0); // BBitMask
        S->writeInt(0); // ABitMask
    } else {
        S->writeInt(0x00000041);    // DDPF_ALPHAPIXELS | DDPF_RGB
        S->writeInt(0);             // FourCC
        S->writeInt(32);            // RGBBitCount
        S->writeInt(0x00FF0000);    // RBitMask
        S->writeInt(0x0000FF00);    // GBitMask
        S->writeInt(0x000000FF);    // BBitMask
        S->writeInt(0xFF000000);    // ABitMask
    }

    // DDSCAPS2
    S->writeInt(isDXT ? 0x00401008  // DDSCAPS_COMPLEX | DDSCAPS_TEXTURE |
                                    // DDSCAPS_MIPMAP
                      : 0x00001000);// DDSCAPS_TEXTURE
    S->writeInt(0); // Caps2
    S->writeInt(0); // Reserved
    S->writeInt(0); // Reserved

    S->writeInt(0); // Reserved

    // Full image data chunk
    S->write(img->getImageSize(), img->getImageData());
}

void plMipmap::readFromStream(hsStream* S) {
    throw hsNotImplementedException(__FILE__, __LINE__);
}

void plMipmap::writeToStream(hsStream* S) {
    if (isImageJPEG()) {
        S->write(fJPEGSize, fJPEGData);
    } else if (fCompressionType == kJPEGCompression) {
        ExportDDS(S, false, fJPEGDataRLE);
    } else {
        ExportDDS(S, fCompressionType != kUncompressed, this);
    }
}

void plMipmap::readAlphaFromStream(hsStream* S) {
    throw hsNotImplementedException(__FILE__, __LINE__);
}

void plMipmap::writeAlphaToStream(hsStream* S) {
    if (isAlphaJPEG()) {
        S->write(fAlphaSize, fAlphaData);
    } else if (fCompressionType == kJPEGCompression) {
        ExportDDS(S, false, fAlphaDataRLE);
    } else {
        throw hsBadParamException(__FILE__, __LINE__);
    }
}

plString plMipmap::getSuggestedExt() const {
    return isImageJPEG() ? ".jpg" : ".dds";
}

plString plMipmap::getSuggestedAlphaExt() const {
    return isAlphaJPEG() ? ".jpg" : ".dds";
}

void plMipmap::IBuildLevelSizes() {
    if (fLevelSizes != NULL)
        delete[] fLevelSizes;
    fLevelSizes = new unsigned int[fNumLevels];
    memset(fLevelSizes, 0, fNumLevels * sizeof(unsigned int));

    unsigned int curWidth = fWidth;
    unsigned int curStride = fStride;
    unsigned int curHeight = fHeight;

    if (fNumLevels <= 0) return;
    for (size_t i=0; i<fNumLevels; i++) {
        if (fCompressionType > 2) return;
        if (fCompressionType == kDirectXCompression &&
            !((curHeight | curWidth) & 3))
            fLevelSizes[i] = (fDXInfo.fBlockSize * curHeight * curWidth) / 16;
        else
            fLevelSizes[i] = curStride * curHeight;
        if (curWidth > 1) {
            curWidth /= 2;
            curStride /= 2;
        }
        if (curHeight > 1)
            curHeight /= 2;
    }
}

plMipmap* plMipmap::IReadRLEImage(hsStream* S) {
    plMipmap* img = new plMipmap(fWidth, fHeight, kARGB32Config, 1, 0, 0);
    int* dataPtr = (int*)img->fImageData;
    while (true) {
        size_t count = S->readInt();
        int data = S->readInt();
        if (count == 0) break;
        for (size_t i=0; i<count; i++) {
            *dataPtr = data;
            dataPtr++;
        }
    }
    return img;
}

void plMipmap::IWriteRLEImage(hsStream* S, plMipmap* img) {
    int* dataPtr = (int*)img->fImageData;
    int data = *dataPtr;
    size_t count = 0;
    for (size_t i=0; i<(fLevelSizes[0] / 4); i++) {
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

    if (rleFlag & kColorDataRLE) {
        fJPEGData = NULL;
        fJPEGDataRLE = IReadRLEImage(S);
    } else {
        fJPEGDataRLE = NULL;
        fJPEGSize = S->readInt();
        fJPEGData = new unsigned char[fJPEGSize];
        S->read(fJPEGSize, fJPEGData);
    }

    if (rleFlag & kAlphaDataRLE) {
        fAlphaData = NULL;
        fAlphaDataRLE = IReadRLEImage(S);
    } else {
        fAlphaDataRLE = NULL;
        fAlphaSize = S->readInt();
        fAlphaData = new unsigned char[fAlphaSize];
        S->read(fAlphaSize, fAlphaData);
    }
}

void plMipmap::IWriteJPEGImage(hsStream* S) {
    char rleFlag = 0;
    if (fJPEGData == NULL)
        rleFlag |= kColorDataRLE;
    if (fAlphaData == NULL)
        rleFlag |= kAlphaDataRLE;
    S->writeByte(rleFlag);

    if (rleFlag & kColorDataRLE) {
        IWriteRLEImage(S, fJPEGDataRLE);
    } else {
        S->writeInt(fJPEGSize);
        S->write(fJPEGSize, fJPEGData);
    }

    if (rleFlag & kAlphaDataRLE) {
        IWriteRLEImage(S, fAlphaDataRLE);
    } else {
        S->writeInt(fAlphaSize);
        S->write(fAlphaSize, fAlphaData);
    }
}

void plMipmap::IReadRawImage(hsStream* S) {
    unsigned char* dataPtr = fImageData;
    if (fPixelSize == 32) {
        if (fNumLevels <= 0) return;
        for (size_t i=0; i<fNumLevels; i++) {
            S->readInts(fLevelSizes[i] / 4, (hsUint32*)dataPtr);
            dataPtr += fLevelSizes[i];
        }
    } else if (fPixelSize == 16) {
        if (fNumLevels <= 0) return;
        for (size_t i=0; i<fNumLevels; i++) {
            S->readShorts(fLevelSizes[i] / 2, (hsUint16*)dataPtr);
            dataPtr += fLevelSizes[i];
        }
    } else {
        throw hsBadParamException(__FILE__, __LINE__);
    }
}

void plMipmap::IWriteRawImage(hsStream* S) {
    unsigned char* dataPtr = fImageData;
    if (fPixelSize == 32) {
        if (fNumLevels <= 0) return;
        for (size_t i=0; i<fNumLevels; i++) {
            S->writeInts(fLevelSizes[i] >> 2, (hsUint32*)dataPtr);
            dataPtr += fLevelSizes[i];
        }
    } else if (fPixelSize == 16) {
        if (fNumLevels <= 0) return;
        for (size_t i=0; i<fNumLevels; i++) {
            S->writeShorts(fLevelSizes[i] >> 1, (hsUint16*)dataPtr);
            dataPtr += fLevelSizes[i];
        }
    } else {
        throw hsBadParamException(__FILE__, __LINE__);
    }
}

void plMipmap::IRecombineAlpha(plMipmap* alphaImg) {
    if (fUncompressedInfo.fType == kRGB8888) {
        for (size_t i=0; i<((fTotalSize-1)/4)+1; i++)
            fImageData[(i*4)+3] = alphaImg->fImageData[(i*4)+2];
    }
    fFlags |= kAlphaChannelFlag;
}

plMipmap* plMipmap::ISplitAlpha() {
    plMipmap* alpha = new plMipmap();
    alpha->CopyFrom(this);
    memset(alpha->fImageData, 0, alpha->fTotalSize);
    if (fUncompressedInfo.fType == kRGB8888) {
        for (size_t i=((fTotalSize-1)/4)+1; i>0; i--)
            alpha->fImageData[(i*4)+2] = fImageData[(i*4)+3];
    }
    return alpha;
}

void plMipmap::CopyFrom(plMipmap* src) {
    if (fImageData != NULL)
        delete[] fImageData;
    
    fWidth = src->fWidth;
    fHeight = src->fHeight;
    fStride = src->fStride;
    fPixelSize = src->fPixelSize;
    fFlags = src->fFlags;
    fSpace = src->fSpace;
    fCompressionType = src->fCompressionType;
    fTotalSize = src->fTotalSize;
    fImageData = new unsigned char[fTotalSize];
    memcpy(fImageData, src->fImageData, fTotalSize);
    fNumLevels = src->fNumLevels;
    if (fCompressionType == kUncompressed || fCompressionType == kJPEGCompression)
        fUncompressedInfo.fType = src->fUncompressedInfo.fType;
    else if (fCompressionType == kDirectXCompression) {
        fDXInfo.fCompressionType = src->fDXInfo.fCompressionType;
        fDXInfo.fBlockSize = src->fDXInfo.fCompressionType;
    }
    IBuildLevelSizes();
}

void plMipmap::ICopyImage(plMipmap* src) {
    if (fImageData != NULL)
        delete[] fImageData;

    fWidth = src->fWidth;
    fHeight = src->fHeight;
    fStride = src->fStride;
    fPixelSize = src->fPixelSize;
    fTotalSize = src->fTotalSize;
    fImageData = new unsigned char[fTotalSize];
    memcpy(fImageData, src->fImageData, fTotalSize);
    IBuildLevelSizes();
}

unsigned int plMipmap::getWidth() const { return fWidth; }
unsigned int plMipmap::getHeight() const { return fHeight; }

const void* plMipmap::getImageData() const {
    if (fCompressionType == kJPEGCompression)
        return (fJPEGDataRLE != NULL) ? fJPEGDataRLE->fImageData : fJPEGData;
    return fImageData;
}

unsigned int plMipmap::getImageSize() const {
    if (fCompressionType == kJPEGCompression)
        return (fJPEGDataRLE != NULL) ? fJPEGDataRLE->fTotalSize : fJPEGSize;
    return fTotalSize;
}

const void* plMipmap::getAlphaData() const {
    if (fCompressionType == kJPEGCompression)
        return (fAlphaDataRLE != NULL) ? fAlphaDataRLE->fImageData : fAlphaData;
    return 0;
}

unsigned int plMipmap::getAlphaSize() const {
    if (fCompressionType == kJPEGCompression)
        return (fAlphaDataRLE != NULL) ? fAlphaDataRLE->fTotalSize : fAlphaSize;
    return 0;
}

size_t plMipmap::getNumLevels() const { return fNumLevels; }
unsigned int plMipmap::getLevelSize(size_t idx) const { return fLevelSizes[idx]; }
    
const void* plMipmap::getLevelData(size_t idx) const {
    unsigned int pos = 0;
    for (size_t i=0; i<idx; i++)
        pos += fLevelSizes[i];
    return &fImageData[pos];
}

void plMipmap::setImageData(const void* data) {
    if (data == NULL) {
        delete[] fImageData;
        fImageData = NULL;
    } else {
        memcpy(fImageData, data, fTotalSize);
    }
}

void plMipmap::setLevelData(size_t idx, const void* data) {
    unsigned int pos = 0;
    for (size_t i=0; i<idx; i++)
        pos += fLevelSizes[i];
    memcpy(fImageData + pos, data, fLevelSizes[idx]);
}

void plMipmap::setImageJPEG(const void* data, unsigned int size) {
    if (fJPEGDataRLE != NULL) {
        delete fJPEGDataRLE;
        fJPEGDataRLE = NULL;
    }
    if (fJPEGData != NULL)
        delete[] fJPEGData;
    fJPEGSize = size;
    fJPEGData = new unsigned char[size];
    memcpy(fJPEGData, data, size);
}

void plMipmap::setImageRLE(const void* data) {
    if (fJPEGData != NULL) {
        delete[] fJPEGData;
        fJPEGData = NULL;
    }
    if (fJPEGDataRLE != NULL)
        delete fJPEGDataRLE;
    fJPEGDataRLE = new plMipmap(fWidth, fHeight, kARGB32Config, 1, 0, 0);
    memcpy(fJPEGDataRLE->fImageData, data, fJPEGDataRLE->fTotalSize);
}

void plMipmap::setAlphaJPEG(const void* data, unsigned int size) {
    if (fAlphaDataRLE != NULL) {
        delete fAlphaDataRLE;
        fAlphaDataRLE = NULL;
    }
    if (fAlphaData != NULL)
        delete[] fAlphaData;
    fAlphaSize = size;
    fAlphaData = new unsigned char[size];
    memcpy(fAlphaData, data, size);
}

void plMipmap::setAlphaRLE(const void* data) {
    if (fAlphaData != NULL) {
        delete[] fAlphaData;
        fAlphaData = NULL;
    }
    if (fAlphaDataRLE != NULL)
        delete fAlphaDataRLE;
    fAlphaDataRLE = new plMipmap(fWidth, fHeight, kARGB32Config, 1, 0, 0);
    memcpy(fAlphaDataRLE->fImageData, data, fAlphaDataRLE->fTotalSize);
}

bool plMipmap::isImageJPEG() const { return fJPEGData != NULL; }
bool plMipmap::isAlphaJPEG() const { return fAlphaData != NULL; }
