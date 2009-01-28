#include "plMipmap.h"
#include <cstring>
#include <cstdlib>

#include "Util/plJPEG.h"
#include "Stream/hsRAMStream.h"
#include "3rdPartyLibs/squish/squish.h"

plMipmap::plMipmap()
        : fImageData(NULL), fTotalSize(0), fAlphaData(NULL), fAlphaSize(0),
          fJPEGData(NULL), fJPEGSize(0), fJAlphaData(NULL), fJAlphaSize(0) {
    Create(0, 0, kARGB32Config, 0, kUncompressed, kRGB8888);
}

plMipmap::plMipmap(unsigned int width, unsigned int height, unsigned int cfg,
                   unsigned char numLevels, unsigned char compType,
                   unsigned char format)
        : fImageData(NULL), fTotalSize(0), fAlphaData(NULL), fAlphaSize(0),
          fJPEGData(NULL), fJPEGSize(0), fJAlphaData(NULL), fJAlphaSize(0) {
    Create(width, height, cfg, numLevels, compType, format);
}

plMipmap::~plMipmap() {
    if (fImageData != NULL) delete[] fImageData;
    if (fAlphaData != NULL) delete[] fAlphaData;
    if (fJPEGData != NULL) delete[] fJPEGData;
    if (fJAlphaData != NULL) delete[] fJAlphaData;
}

IMPLEMENT_CREATABLE(plMipmap, kMipmap, plBitmap)

void plMipmap::Create(unsigned int width, unsigned int height, unsigned int cfg,
                      unsigned char numLevels, unsigned char compType,
                      unsigned char format) {
    if (fImageData != NULL) delete[] fImageData;
    if (fAlphaData != NULL) delete[] fAlphaData;
    if (fJPEGData != NULL) delete[] fJPEGData;
    if (fJAlphaData != NULL) delete[] fJAlphaData;
                          
    setConfig(cfg);
    fStride = (fPixelSize * width) / 8;
    fWidth = width;
    fHeight = height;

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

    if (fWidth == 0 || fHeight == 0) {
        fLevelData.setSize(0);
        fTotalSize = 0;
        fImageData = NULL;
        fAlphaData = NULL;
        fJPEGData = NULL;
        fJAlphaData = NULL;
        return;
    }

    if (numLevels == 0) {
        numLevels = 1;
        while (width > 1 && height > 1) {
            if (width > 1)
                width /= 2;
            if (height > 1)
                height /= 2;
            numLevels++;
        }
    }
    fLevelData.setSize(numLevels);

    fLevelData.clear();
    IBuildLevelSizes();
    fTotalSize = 0;
    for (size_t i=0; i<fLevelData.getSize(); i++)
        fTotalSize += fLevelData[i].fSize;
    fImageData = new unsigned char[fTotalSize];
    memset(fImageData, 0, fTotalSize);
}

void plMipmap::setConfig(unsigned int cfg) {
    switch (cfg) {
    case kColor8Config:
        fPixelSize = 8;
        fSpace = kIndexSpace;
        fFlags = kNoFlag;
        break;
    case kGray44Config:
        fPixelSize = 8;
        fSpace = kGraySpace;
        fFlags = kAlphaChannelFlag;
        break;
    case kGray4Config:
        fPixelSize = 4;
        fSpace = kGraySpace;
        fFlags = kNoFlag;
        break;
    case kGray8Config:
        fPixelSize = 8;
        fSpace = kDirectSpace;
        fFlags = kNoFlag;
        break;
    case kRGB16Config:
        fPixelSize = 16;
        fSpace = kDirectSpace;
        fFlags = kAlphaBitFlag;
        break;
    case kRGB32Config:
        fPixelSize = 32;
        fSpace = kDirectSpace;
        fFlags = kNoFlag;
    case kARGB32Config:
        fPixelSize = 32;
        fSpace = kDirectSpace;
        fFlags = kAlphaChannelFlag;
        break;
    }
}

void plMipmap::read(hsStream* S, plResManager* mgr) {
    plBitmap::read(S, mgr);
    IRead(S);
}

void plMipmap::write(hsStream* S, plResManager* mgr) {
    plBitmap::write(S, mgr);
    IWrite(S);
}

void plMipmap::readData(hsStream* S) {
    plBitmap::IRead(S);
    IRead(S);
}

void plMipmap::writeData(hsStream* S) {
    plBitmap::IWrite(S);
    IWrite(S);
}

void plMipmap::IRead(hsStream* S) {
    fWidth = S->readInt();
    fHeight = S->readInt();
    fStride = S->readInt();
    fTotalSize = S->readInt();
    fLevelData.setSize(S->readByte());

    if (fImageData != NULL) {
        delete[] fImageData;
        fImageData = NULL;
    }
    if (fAlphaData != NULL) {
        delete[] fAlphaData;
        fAlphaData = NULL;
    }
    if (fTotalSize == 0)
        return;

    IBuildLevelSizes();
    fImageData = new unsigned char[fTotalSize];
    fAlphaData = new unsigned char[fTotalSize];
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

void plMipmap::IWrite(hsStream* S) {
    S->writeInt(fWidth);
    S->writeInt(fHeight);
    S->writeInt(fStride);
    S->writeInt(fTotalSize);
    S->writeByte(fLevelData.getSize());

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
    prc->writeParam("MipLevels", fLevelData.getSize());
    prc->endTag(true);

    if (fCompressionType == kJPEGCompression) {
        prc->startTag("JPEG");
        prc->writeParam("ImageRLE", !isImageJPEG());
        prc->writeParam("AlphaRLE", !isAlphaJPEG());
        prc->endTag();

        prc->writeSimpleTag("Image");
        if (!prc->isExcluded(pfPrcHelper::kExcludeTextureData)) {
            if (isImageJPEG())
                prc->writeHexStream(fJPEGSize, fJPEGData);
            else
                prc->writeHexStream(fLevelData[0].fSize, fImageData);
        } else {
            prc->writeComment("Texture data excluded");
        }
        prc->closeTag();    // Image
        prc->writeSimpleTag("Alpha");
        if (!prc->isExcluded(pfPrcHelper::kExcludeTextureData)) {
            if (isAlphaJPEG())
                prc->writeHexStream(fJAlphaSize, fJAlphaData);
            else
                prc->writeHexStream(fLevelData[0].fSize, fAlphaData);
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
        fLevelData.setSize(tag->getParam("MipLevels", "0").toUint());
        IBuildLevelSizes();
    } else if (tag->getName() == "JPEG") {
        IBuildLevelSizes();
        if (tag->getParam("ImageRLE", "false").toBool()) {
            fImageData = new unsigned char[fTotalSize];
            tag->readHexStream(fLevelData[0].fSize, fImageData);
        } else {
            fJPEGSize = tag->getContents().getSize();
            fJPEGData = new unsigned char[fJPEGSize];
            tag->readHexStream(fJPEGSize, fJPEGData);
        }
        if (tag->getParam("AlphaRLE", "false").toBool()) {
            fAlphaData = new unsigned char[fTotalSize];
            tag->readHexStream(fLevelData[0].fSize, fAlphaData);
        } else {
            fJAlphaSize = tag->getContents().getSize();
            fJAlphaData = new unsigned char[fJAlphaSize];
            tag->readHexStream(fJAlphaSize, fJAlphaData);
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

void ExportDDS(hsStream* S, bool isDXT, plMipmap* img, bool isAlpha) {
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
        else if (img->getDXCompression() == plBitmap::kDXT3)
            S->write(4, "DXT3");
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
    S->write((isAlpha ? img->getAlphaSize() : img->getImageSize()),
             (isAlpha ? img->getAlphaData() : img->getImageData()));
}

void plMipmap::readFromStream(hsStream* S) {
    throw hsNotImplementedException(__FILE__, __LINE__);
}

void plMipmap::writeToStream(hsStream* S) {
    if (isImageJPEG()) {
        S->write(fJPEGSize, fJPEGData);
    } else if (fCompressionType == kJPEGCompression) {
        ExportDDS(S, false, this, false);
    } else {
        ExportDDS(S, fCompressionType != kUncompressed, this, false);
    }
}

void plMipmap::readAlphaFromStream(hsStream* S) {
    throw hsNotImplementedException(__FILE__, __LINE__);
}

void plMipmap::writeAlphaToStream(hsStream* S) {
    if (isAlphaJPEG()) {
        S->write(fJAlphaSize, fJAlphaData);
    } else if (fCompressionType == kJPEGCompression) {
        ExportDDS(S, false, this, true);
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
    unsigned int curWidth = fWidth;
    unsigned int curStride = fStride;
    unsigned int curHeight = fHeight;
    size_t curOffs = 0;

    for (size_t i=0; i<fLevelData.getSize(); i++) {
        if (fCompressionType == kDirectXCompression) {
            if ((curHeight | curWidth) & 3)
                fLevelData[i].fSize = curStride * curHeight;
            else
                fLevelData[i].fSize = (fDXInfo.fBlockSize * curHeight * curWidth) / 16;
        } else if (fCompressionType == kUncompressed) {
            fLevelData[i].fSize = curStride * curHeight;
        } else {
            fLevelData[i].fSize = curStride * curHeight;
        }

        fLevelData[i].fWidth = curWidth;
        fLevelData[i].fHeight = curHeight;
        fLevelData[i].fOffset = curOffs;
        curOffs += fLevelData[i].fSize;
        if (curWidth > 1) {
            curWidth /= 2;
            curStride /= 2;
        }
        if (curHeight > 1)
            curHeight /= 2;
    }
}

void plMipmap::IReadRLEImage(hsStream* S, bool alpha) {
    unsigned int* dataPtr = (unsigned int*)(alpha ? fAlphaData : fImageData);
    size_t count;
    do {
        count = S->readInt();
        unsigned int data = S->readInt();
        for (size_t i=0; i<count; i++) {
            *dataPtr = data;
            dataPtr++;
        }
    } while (count != 0);
}

void plMipmap::IWriteRLEImage(hsStream* S, bool alpha) {
    unsigned int* dataPtr = (unsigned int*)(alpha ? fAlphaData : fImageData);
    unsigned int data = *dataPtr;
    size_t count = 0;
    for (size_t i=0; i<(fLevelData[0].fSize / 4); i++) {
        if (count == 0xFFFFFFFF || (*dataPtr & 0x00FFFFFF) != data) {
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
    unsigned char rleFlag = S->readByte();

    if (rleFlag & kColorDataRLE) {
        fJPEGData = NULL;
        IReadRLEImage(S, false);
    } else {
        fImageData = NULL;
        fJPEGSize = S->readInt();
        fJPEGData = new unsigned char[fJPEGSize];
        S->read(fJPEGSize, fJPEGData);
    }

    if (rleFlag & kAlphaDataRLE) {
        fJAlphaData = NULL;
        IReadRLEImage(S, true);
    } else {
        fAlphaData = NULL;
        fJAlphaSize = S->readInt();
        fJAlphaData = new unsigned char[fJAlphaSize];
        S->read(fJAlphaSize, fJAlphaData);
    }
}

void plMipmap::IWriteJPEGImage(hsStream* S) {
    unsigned char rleFlag = 0;
    if (!isImageJPEG())
        rleFlag |= kColorDataRLE;
    if (!isAlphaJPEG())
        rleFlag |= kAlphaDataRLE;
    S->writeByte(rleFlag);

    if (rleFlag & kColorDataRLE) {
        IWriteRLEImage(S, false);
    } else {
        S->writeInt(fJPEGSize);
        S->write(fJPEGSize, fJPEGData);
    }

    if (rleFlag & kAlphaDataRLE) {
        IWriteRLEImage(S, true);
    } else {
        S->writeInt(fJAlphaSize);
        S->write(fJAlphaSize, fJAlphaData);
    }
}

void plMipmap::IReadRawImage(hsStream* S) {
    unsigned char* dataPtr = fImageData;
    if (fPixelSize == 32) {
        for (size_t i=0; i<fLevelData.getSize(); i++) {
            S->readInts(fLevelData[i].fSize / 4, (hsUint32*)dataPtr);
            dataPtr += fLevelData[i].fSize;
        }
    } else if (fPixelSize == 16) {
        for (size_t i=0; i<fLevelData.getSize(); i++) {
            S->readShorts(fLevelData[i].fSize / 2, (hsUint16*)dataPtr);
            dataPtr += fLevelData[i].fSize;
        }
    } else {
        throw hsBadParamException(__FILE__, __LINE__);
    }
}

void plMipmap::IWriteRawImage(hsStream* S) {
    unsigned char* dataPtr = fImageData;
    if (fPixelSize == 32) {
        for (size_t i=0; i<fLevelData.getSize(); i++) {
            S->writeInts(fLevelData[i].fSize / 4, (hsUint32*)dataPtr);
            dataPtr += fLevelData[i].fSize;
        }
    } else if (fPixelSize == 16) {
        for (size_t i=0; i<fLevelData.getSize(); i++) {
            S->writeShorts(fLevelData[i].fSize / 2, (hsUint16*)dataPtr);
            dataPtr += fLevelData[i].fSize;
        }
    } else {
        throw hsBadParamException(__FILE__, __LINE__);
    }
}

/*
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
*/

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
    fLevelData = src->fLevelData;
    if (fCompressionType == kUncompressed || fCompressionType == kJPEGCompression)
        fUncompressedInfo.fType = src->fUncompressedInfo.fType;
    else if (fCompressionType == kDirectXCompression) {
        fDXInfo.fCompressionType = src->fDXInfo.fCompressionType;
        fDXInfo.fBlockSize = src->fDXInfo.fCompressionType;
    }
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
    fLevelData = src->fLevelData;
}

unsigned int plMipmap::getWidth() const { return fWidth; }
unsigned int plMipmap::getHeight() const { return fHeight; }

const void* plMipmap::getImageData() const {
    if (fCompressionType == kJPEGCompression)
        return isImageJPEG() ? fJPEGData : fImageData ;
    return fImageData;
}

unsigned int plMipmap::getImageSize() const {
    if (fCompressionType == kJPEGCompression)
        return isImageJPEG() ? fJPEGSize : fTotalSize;
    return fTotalSize;
}

const void* plMipmap::getAlphaData() const {
    if (fCompressionType == kJPEGCompression)
        return isAlphaJPEG() ? fJAlphaData : fAlphaData;
    return NULL;
}

unsigned int plMipmap::getAlphaSize() const {
    if (fCompressionType == kJPEGCompression)
        return isAlphaJPEG() ? fJAlphaSize : fTotalSize;
    return 0;
}

size_t plMipmap::getNumLevels() const { return fLevelData.getSize(); }
unsigned int plMipmap::getLevelWidth(size_t idx) const { return fLevelData[idx].fWidth; }
unsigned int plMipmap::getLevelHeight(size_t idx) const { return fLevelData[idx].fHeight; }
unsigned int plMipmap::getLevelSize(size_t idx) const { return fLevelData[idx].fSize; }

const void* plMipmap::getLevelData(size_t idx) const {
    return fImageData + fLevelData[idx].fOffset;
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
    memcpy(fImageData + fLevelData[idx].fOffset,
           data, fLevelData[idx].fSize);
}

void plMipmap::setImageJPEG(const void* data, unsigned int size) {
    if (fJPEGData != NULL)
        delete[] fJPEGData;
    fJPEGSize = size;
    fJPEGData = new unsigned char[size];
    memcpy(fJPEGData, data, size);
}

void plMipmap::setAlphaJPEG(const void* data, unsigned int size) {
    if (fJAlphaData != NULL)
        delete[] fJAlphaData;
    fJAlphaSize = size;
    fJAlphaData = new unsigned char[size];
    memcpy(fJAlphaData, data, size);
}

bool plMipmap::isImageJPEG() const { return fJPEGData != NULL; }
bool plMipmap::isAlphaJPEG() const { return fJAlphaData != NULL; }

size_t plMipmap::GetUncompressedSize(size_t level) const {
    const LevelData& lvl = fLevelData[level];
    return lvl.fHeight * lvl.fWidth * 4;
}

size_t plMipmap::GetCompressedSize(size_t level) const {
    const LevelData& lvl = fLevelData[level];
    if (fCompressionType == kDirectXCompression) {
        if (fDXInfo.fCompressionType == kDXT1) {
            return (size_t)squish::GetStorageRequirements(lvl.fWidth, lvl.fHeight, squish::kDxt1);
        } else if (fDXInfo.fCompressionType == kDXT3) {
            return (size_t)squish::GetStorageRequirements(lvl.fWidth, lvl.fHeight, squish::kDxt3);
        } else if (fDXInfo.fCompressionType == kDXT5) {
            return (size_t)squish::GetStorageRequirements(lvl.fWidth, lvl.fHeight, squish::kDxt5);
        } else {
            throw hsBadParamException(__FILE__, __LINE__);
        }
    } else {
        return lvl.fSize;
    }
}

void plMipmap::DecompressImage(size_t level, void* dest, size_t size) {
    const LevelData& lvl = fLevelData[level];

    if (fCompressionType == kJPEGCompression) {
        unsigned char* jAlpha = new unsigned char[size];

        if (isImageJPEG()) {
            hsRAMStream S;
            S.copyFrom(fJPEGData, fJPEGSize);
            plJPEG::DecompressJPEG(&S, dest, size);
        } else {
            memcpy(dest, fImageData, size);
        }

        if (isAlphaJPEG()) {
            hsRAMStream S;
            S.copyFrom(fJAlphaData, fJAlphaSize);
            plJPEG::DecompressJPEG(&S, jAlpha, size);
        } else {
            memcpy(jAlpha, fAlphaData, size);
        }

        size_t alphaOffset = isAlphaJPEG() ? 0 : 2;
        for (size_t i=0; i<size; i+=4)
            ((unsigned char*)dest)[i+3] = jAlpha[i + alphaOffset];
        delete[] jAlpha;
    } else if (fCompressionType == kDirectXCompression) {
        unsigned char* imgPtr = fImageData + fLevelData[level].fOffset;
        if (fDXInfo.fCompressionType == kDXT1) {
            squish::DecompressImage((squish::u8*)dest, lvl.fWidth, lvl.fHeight,
                                    imgPtr, squish::kDxt1);
        } else if (fDXInfo.fCompressionType == kDXT3) {
            squish::DecompressImage((squish::u8*)dest, lvl.fWidth, lvl.fHeight,
                                    imgPtr, squish::kDxt3);
        } else if (fDXInfo.fCompressionType == kDXT5) {
            squish::DecompressImage((squish::u8*)dest, lvl.fWidth, lvl.fHeight,
                                    imgPtr, squish::kDxt5);
        } else {
            throw hsBadParamException(__FILE__, __LINE__);
        }
    } else {
        unsigned char* imgPtr = fImageData + fLevelData[level].fOffset;
        memcpy(dest, imgPtr, size);
    }
}
