/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "plMipmap.h"
#include <cstring>
#include <cstdlib>

#include "Debug/plDebug.h"
#include "Util/plJPEG.h"
#include "Util/plPNG.h"
#include "Util/plDDSurface.h"
#include "Stream/hsRAMStream.h"
#include "3rdPartyLibs/squish/squish.h"

static uint8_t* alloc_aligned(size_t bytes)
{
    // Ensure the block is aligned to the processor's likely max access size
    size_t blocks = bytes / sizeof(size_t);
    if (bytes % sizeof(size_t) != 0)
        ++blocks;

    return reinterpret_cast<uint8_t*>(new size_t[blocks]);
}

static void free_aligned(uint8_t*& ptr)
{
    delete[] reinterpret_cast<size_t*>(ptr);
    ptr = nullptr;
}

/* plMipmap */
plMipmap::plMipmap() : fImageData(), fTotalSize()
{
    Create(0, 0, 0, kUncompressed, kRGB8888);
}

plMipmap::plMipmap(uint32_t width, uint32_t height, uint8_t numLevels,
                   uint8_t compType, ColorFormat format, uint8_t dxtLevel)
    : fImageData(), fTotalSize()
{
    Create(width, height, numLevels, compType, format, dxtLevel);
}

plMipmap::~plMipmap()
{
    free_aligned(fImageData);
}

void plMipmap::Create(uint32_t width, uint32_t height, uint8_t numLevels,
                      uint8_t compType, ColorFormat format, uint8_t dxtLevel)
{
    free_aligned(fImageData);
    fJPEGCache.clear();
    fJAlphaCache.clear();
    fLevelData.clear();
    fTotalSize = 0;

    if (compType == kDirectXCompression && dxtLevel == kDXTError)
        throw hsBadParamException(__FILE__, __LINE__, "DXT Type must be set for DirectX textures");

    fCompressionType = compType;
    if (compType == kDirectXCompression) {
        fPixelSize = 32;
        fSpace = kDirectSpace;
        fDXInfo.fCompressionType = dxtLevel;
        if (dxtLevel == kDXT1) {
            fDXInfo.fBlockSize = 8;
            fFlags = kAlphaBitFlag;
        } else {
            fDXInfo.fBlockSize = 16;
            fFlags = kAlphaChannelFlag;
        }
    } else {
        setConfig(format);
        fUncompressedInfo.fType = format;
    }

    fWidth = width;
    fHeight = height;
    fStride = (fPixelSize * fWidth) / 8;

    if (fWidth == 0 || fHeight == 0)
        return;

    if (numLevels == 0) {
        numLevels = 1;
        while (width > 1 || height > 1) {
            width = (width > 1) ? width >> 1 : 1;
            height = (height > 1) ? height >> 1 : 1;
            numLevels++;
        }
    }

    fLevelData.resize(numLevels);
    fTotalSize = IBuildLevelSizes();
    fImageData = alloc_aligned(fTotalSize);
    memset(fImageData, 0, fTotalSize);
}

void plMipmap::CopyFrom(plMipmap* src)
{
    free_aligned(fImageData);
    fJPEGCache.clear();
    fJAlphaCache.clear();

    fPixelSize = src->fPixelSize;
    fSpace = src->fSpace;
    fFlags = src->fFlags;
    fCompressionType = src->fCompressionType;
    fLowModTime = src->fLowModTime;
    fHighModTime = src->fHighModTime;
    if (fCompressionType == kDirectXCompression) {
        fDXInfo.fCompressionType = src->fDXInfo.fCompressionType;
        fDXInfo.fBlockSize = src->fDXInfo.fBlockSize;
    } else {
        fUncompressedInfo.fType = src->fUncompressedInfo.fType;
    }

    fWidth = src->fWidth;
    fHeight = src->fHeight;
    fStride = src->fStride;
    fTotalSize = src->fTotalSize;
    fImageData = alloc_aligned(fTotalSize);
    memcpy(fImageData, src->fImageData, fTotalSize);
    fLevelData = src->fLevelData;

    fJPEGCache = src->fJPEGCache;
    fJAlphaCache = src->fJAlphaCache;
}

void plMipmap::read(hsStream* S, plResManager* mgr)
{
    plBitmap::read(S, mgr);
    IReadMipmap(S);
}

void plMipmap::write(hsStream* S, plResManager* mgr)
{
    plBitmap::write(S, mgr);
    IWriteMipmap(S);
}

void plMipmap::readData(hsStream* S)
{
    IReadBitmap(S);
    IReadMipmap(S);
}

void plMipmap::writeData(hsStream* S)
{
    IWriteBitmap(S);
    IWriteMipmap(S);
}

void plMipmap::IReadMipmap(hsStream* S)
{
    fWidth = S->readInt();
    fHeight = S->readInt();
    fStride = S->readInt();
    fTotalSize = S->readInt();
    fLevelData.resize(S->readByte());

    free_aligned(fImageData);
    fJPEGCache.clear();
    fJAlphaCache.clear();

    if (fTotalSize == 0)
        return;

    size_t realSize = IBuildLevelSizes();
    if (realSize != fTotalSize)
        plDebug::Warning("{}: Incorrect image buffer storage size", getKey().toString());
    fImageData = alloc_aligned(realSize);

    switch (fCompressionType) {
    case kJPEGCompression:
        IReadJPEGImage(S);
        DecompressImage(0, fImageData, fLevelData[0].fSize);
        break;
    case kDirectXCompression:
        S->read(fTotalSize, fImageData);
        break;
    case kPNGCompression:
        plPNG::DecompressPNG(S, fImageData, fLevelData[0].fSize);
        break;
    case kUncompressed:
        IReadRawImage(S);
        break;
    default:
        throw hsBadParamException(__FILE__, __LINE__, "Unsupported compression type");
    }
}

void plMipmap::IWriteMipmap(hsStream* S)
{
    S->writeInt(fWidth);
    S->writeInt(fHeight);
    S->writeInt(fStride);
    S->writeInt(fTotalSize);
    S->writeByte(fLevelData.size());

    if (fTotalSize == 0)
        return;

    switch (fCompressionType) {
    case kJPEGCompression:
        IWriteJPEGImage(S);
        break;
    case kDirectXCompression:
        S->write(fTotalSize, fImageData);
        break;
    case kPNGCompression:
        plPNG::CompressPNG(S, fImageData, fLevelData[0].fSize,
                           fWidth, fHeight, fPixelSize);
        break;
    case kUncompressed:
        IWriteRawImage(S);
        break;
    default:
        throw hsBadParamException(__FILE__, __LINE__, "Unsupported compression type");
    }
}

void plMipmap::IPrcWrite(pfPrcHelper* prc)
{
    plBitmap::IPrcWrite(prc);

    prc->startTag("Metrics");
    prc->writeParam("Width", fWidth);
    prc->writeParam("Height", fHeight);
    prc->writeParam("Stride", fStride);
    prc->writeParam("TotalSize", (unsigned int)fTotalSize);
    prc->writeParam("MipLevels", (unsigned int)fLevelData.size());
    prc->endTag(true);

    if (fCompressionType == kJPEGCompression) {
        prc->startTag("JPEG");
        prc->writeParam("ImageRLE", !isImageJPEG());
        prc->writeParam("AlphaRLE", !isAlphaJPEG());
        prc->endTag();

        prc->writeSimpleTag("ImageData");
        if (!prc->isExcluded(pfPrcHelper::kExcludeTextureData)) {
            prc->writeHexStream(fTotalSize, fImageData);
        } else {
            prc->writeComment("Texture data excluded");
        }
        prc->closeTag();    // Image

        if (isImageJPEG()) {
            prc->writeSimpleTag("JpegData");
            if (!prc->isExcluded(pfPrcHelper::kExcludeTextureData))
                prc->writeHexStream(fJPEGCache.size(), fJPEGCache.data());
            else
                prc->writeComment("Texture data excluded");
            prc->closeTag();    // JpegData
        }

        if (isAlphaJPEG()) {
            prc->writeSimpleTag("AlphaData");
            if (!prc->isExcluded(pfPrcHelper::kExcludeTextureData))
                prc->writeHexStream(fJAlphaCache.size(), fJAlphaCache.data());
            else
                prc->writeComment("Texture data excluded");
            prc->closeTag();    // AlphaData
        }

        prc->closeTag();    // JPEG
    } else {
        prc->writeSimpleTag("DDS");
        prc->writeHexStream(fTotalSize, fImageData);
        prc->closeTag();
    }
}

void plMipmap::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Metrics") {
        fWidth = tag->getParam("Width", "0").to_uint();
        fHeight = tag->getParam("Height", "0").to_uint();
        fStride = tag->getParam("Stride", "0").to_uint();
        fTotalSize = tag->getParam("TotalSize", "0").to_uint();
        fLevelData.resize(tag->getParam("MipLevels", "0").to_uint());
        IBuildLevelSizes();
    } else if (tag->getName() == "JPEG") {
        IBuildLevelSizes();
        free_aligned(fImageData);
        fJPEGCache.clear();
        fJAlphaCache.clear();
        fImageData = alloc_aligned(fTotalSize);

        const pfPrcTag* child = tag->getFirstChild();
        while (child) {
            if (child->getName() == "ImageData") {
                if (child->getContents().size() != fTotalSize)
                    throw pfPrcParseException(__FILE__, __LINE__, "Image Data is not of the correct length");
                child->readHexStream(fTotalSize, fImageData);
            } else if (child->getName() == "JpegData") {
                fJPEGCache.resize(tag->getContents().size());
                tag->readHexStream(fJPEGCache.size(), fJPEGCache.data());
            } else if (child->getName() == "AlphaData") {
                fJAlphaCache.resize(tag->getContents().size());
                tag->readHexStream(fJAlphaCache.size(), fJAlphaCache.data());
            } else {
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            }
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "DDS") {
        if (tag->getContents().size() != fTotalSize)
            throw pfPrcParseException(__FILE__, __LINE__, "DDS Data is not of the correct length");
        IBuildLevelSizes();
        free_aligned(fImageData);
        fJPEGCache.clear();
        fJAlphaCache.clear();
        if (fTotalSize > 0) {
            fImageData = alloc_aligned(fTotalSize);
            tag->readHexStream(fTotalSize, fImageData);
        }
    } else {
        plBitmap::IPrcParse(tag, mgr);
    }
}

size_t plMipmap::IBuildLevelSizes()
{
    unsigned int curWidth = fWidth;
    unsigned int curStride = fStride;
    unsigned int curHeight = fHeight;
    size_t curOffs = 0;

    for (size_t i=0; i<fLevelData.size(); i++) {
        if (fCompressionType == kDirectXCompression) {
            if ((curHeight | curWidth) & 3)
                fLevelData[i].fSize = curStride * curHeight;
            else
                fLevelData[i].fSize = (fDXInfo.fBlockSize * curHeight * curWidth) / 16;
        } else {
            fLevelData[i].fSize = curStride * curHeight;
        }

        fLevelData[i].fWidth = curWidth;
        fLevelData[i].fHeight = curHeight;
        fLevelData[i].fOffset = curOffs;
        curOffs += fLevelData[i].fSize;
        if (curWidth > 1) {
            curWidth >>= 1;
            curStride >>= 1;
        }
        if (curHeight > 1)
            curHeight >>= 1;
    }

    return curOffs;
}

void plMipmap::IReadRLEImage(hsStream* S, bool alpha)
{
    unsigned int* dataPtr = (unsigned int*)fImageData;
    size_t count;
    if (alpha) {
        do {
            count = S->readInt();
            unsigned int data = S->readInt();
            for (size_t i=0; i<count; i++) {
                *dataPtr = (*dataPtr & 0x00FFFFFF) | ((data << 8) & 0xFF000000);
                dataPtr++;
            }
        } while (count != 0);
    } else {
        do {
            count = S->readInt();
            unsigned int data = S->readInt();
            for (size_t i=0; i<count; i++) {
                *dataPtr = (*dataPtr & 0xFF000000) | (data & 0x00FFFFFF);
                dataPtr++;
            }
        } while (count != 0);
    }
}

void plMipmap::IWriteRLEImage(hsStream* S, bool alpha)
{
    unsigned int* dataPtr = (unsigned int*)fImageData;
    unsigned int data;
    size_t count = 0;
    if (alpha) {
        data = *dataPtr & 0xFF000000;
        for (size_t i=0; i<(fLevelData[0].fSize / 4); i++) {
            if (count == 0xFFFFFFFF || (*dataPtr & 0xFF000000) != data) {
                S->writeInt(count);
                S->writeInt(data >> 8);
                count = 0;
                data = *dataPtr & 0xFF000000;
            }
            count++;
            dataPtr++;
        }
        // Final block
        S->writeInt(count);
        S->writeInt(data >> 8);
    } else {
        data = *dataPtr & 0x00FFFFFF;
        for (size_t i=0; i<(fLevelData[0].fSize / 4); i++) {
            if (count == 0xFFFFFFFF || (*dataPtr & 0x00FFFFFF) != data) {
                S->writeInt(count);
                S->writeInt(data);
                count = 0;
                data = *dataPtr & 0x00FFFFFF;
            }
            count++;
            dataPtr++;
        }
        // Final block
        S->writeInt(count);
        S->writeInt(data);
    }

    // Stop indicator
    S->writeInt(0);
    S->writeInt(0);
}

void plMipmap::IReadJPEGImage(hsStream* S)
{
    unsigned char rleFlag = S->readByte();

    if (rleFlag & kColorDataRLE) {
        IReadRLEImage(S, false);
    } else {
        fJPEGCache.resize(S->readInt());
        S->read(fJPEGCache.size(), fJPEGCache.data());
    }

    if (rleFlag & kAlphaDataRLE) {
        IReadRLEImage(S, true);
    } else {
        fJAlphaCache.resize(S->readInt());
        S->read(fJAlphaCache.size(), fJAlphaCache.data());
    }
}

void plMipmap::IWriteJPEGImage(hsStream* S)
{
    unsigned char rleFlag = 0;
    if (!isImageJPEG())
        rleFlag |= kColorDataRLE;
    if (!isAlphaJPEG())
        rleFlag |= kAlphaDataRLE;
    S->writeByte(rleFlag);

    if (rleFlag & kColorDataRLE) {
        IWriteRLEImage(S, false);
    } else {
        S->writeInt(fJPEGCache.size());
        S->write(fJPEGCache.size(), fJPEGCache.data());
    }

    if (rleFlag & kAlphaDataRLE) {
        IWriteRLEImage(S, true);
    } else {
        S->writeInt(fJAlphaCache.size());
        S->write(fJAlphaCache.size(), fJAlphaCache.data());
    }
}

void plMipmap::IReadRawImage(hsStream* S)
{
    uint8_t* dataPtr = fImageData;
    if (fPixelSize == 32) {
        for (size_t i=0; i<fLevelData.size(); i++) {
            S->readInts(fLevelData[i].fSize / 4, (uint32_t*)dataPtr);
            dataPtr += fLevelData[i].fSize;
        }
    } else if (fPixelSize == 16) {
        for (size_t i=0; i<fLevelData.size(); i++) {
            S->readShorts(fLevelData[i].fSize / 2, (uint16_t*)dataPtr);
            dataPtr += fLevelData[i].fSize;
        }
    } else if (fPixelSize == 8) {
        for (size_t i=0; i<fLevelData.size(); i++) {
            S->read(fLevelData[i].fSize, dataPtr);
            dataPtr += fLevelData[i].fSize;
        }
    } else {
        throw hsBadParamException(__FILE__, __LINE__);
    }
}

void plMipmap::IWriteRawImage(hsStream* S)
{
    uint8_t* dataPtr = fImageData;
    if (fPixelSize == 32) {
        for (size_t i=0; i<fLevelData.size(); i++) {
            S->writeInts(fLevelData[i].fSize / 4, (uint32_t*)dataPtr);
            dataPtr += fLevelData[i].fSize;
        }
    } else if (fPixelSize == 16) {
        for (size_t i=0; i<fLevelData.size(); i++) {
            S->writeShorts(fLevelData[i].fSize / 2, (uint16_t*)dataPtr);
            dataPtr += fLevelData[i].fSize;
        }
    } else if (fPixelSize == 8) {
        for (size_t i=0; i<fLevelData.size(); i++) {
            S->write(fLevelData[i].fSize, dataPtr);
            dataPtr += fLevelData[i].fSize;
        }
    } else {
        throw hsBadParamException(__FILE__, __LINE__);
    }
}

const void* plMipmap::getLevelData(size_t idx) const
{
    return fImageData + fLevelData[idx].fOffset;
}

void plMipmap::setImageData(const void* data, size_t size)
{
    if (size != fTotalSize) {
        free_aligned(fImageData);
        fImageData = alloc_aligned(size);
        fTotalSize = size;
    }

    memcpy(fImageData, data, fTotalSize);
}

void plMipmap::setLevelData(size_t idx, const void* data, size_t size)
{
    if (size != fLevelData[idx].fSize)
        throw hsBadParamException(__FILE__, __LINE__, "Image data size mismatch");
    memcpy(fImageData + fLevelData[idx].fOffset, data, fLevelData[idx].fSize);
}

void plMipmap::setImageJPEG(const void* data, size_t size)
{
    fJPEGCache.resize(size);
    if (data)
        memcpy(fJPEGCache.data(), data, size);
    DecompressImage(0, fImageData, fLevelData[0].fSize);
}

void plMipmap::setAlphaJPEG(const void* data, size_t size)
{
    fJAlphaCache.resize(size);
    if (data)
        memcpy(fJAlphaCache.data(), data, size);
    DecompressImage(0, fImageData, fLevelData[0].fSize);
}

void plMipmap::setColorData(const void* data, size_t size)
{
    if (fCompressionType != kJPEGCompression)
        throw hsBadParamException(__FILE__, __LINE__, "Color/Alpha split only supported on JPEG textures");
    if (size != (fWidth * fHeight * 3))
        throw hsBadParamException(__FILE__, __LINE__, "Pixel configuration does not match buffer size");

    unsigned char* dp = (unsigned char*)fImageData;
    const unsigned char* sp = (const unsigned char*)data;
    for (size_t i=0; i<fLevelData[0].fSize; i += 4) {
        *dp++ = *sp++;  // Blue
        *dp++ = *sp++;  // Green
        *dp++ = *sp++;  // Red
        dp++;           // Skip alpha
    }
}

void plMipmap::setAlphaData(const void* alpha, size_t size)
{
    if (fCompressionType != kJPEGCompression)
        throw hsBadParamException(__FILE__, __LINE__, "Color/Alpha split only supported on JPEG textures");
    if (size != (fWidth * fHeight * 1))
        throw hsBadParamException(__FILE__, __LINE__, "Pixel configuration does not match buffer size");

    unsigned char* dp = (unsigned char*)fImageData;
    const unsigned char* sp = (const unsigned char*)alpha;
    for (size_t i=0; i<fLevelData[0].fSize; i += 4) {
        dp += 3;        // Skip RGB
        *dp++ = *sp++;  // Alpha
    }
}

void plMipmap::extractColorData(void* buffer, size_t size) const
{
    if (fCompressionType != kJPEGCompression)
        throw hsBadParamException(__FILE__, __LINE__, "Color/Alpha split only supported on JPEG textures");
    if (size != (fWidth * fHeight * 3))
        throw hsBadParamException(__FILE__, __LINE__, "Pixel configuration does not match buffer size");

    unsigned char* sp = (unsigned char*)fImageData;
    unsigned char* dp = (unsigned char*)buffer;
    for (size_t i=0; i<fLevelData[0].fSize; i += 4) {
        *dp++ = *sp++;  // Blue
        *dp++ = *sp++;  // Green
        *dp++ = *sp++;  // Red
        sp++;           // Skip alpha
    }
}

void plMipmap::extractAlphaData(void* buffer, size_t size) const
{
    if (fCompressionType != kJPEGCompression)
        throw hsBadParamException(__FILE__, __LINE__, "Color/Alpha split only supported on JPEG textures");
    if (size != (fWidth * fHeight * 1))
        throw hsBadParamException(__FILE__, __LINE__, "Pixel configuration does not match buffer size");

    unsigned char* sp = (unsigned char*)fImageData;
    unsigned char* dp = (unsigned char*)buffer;
    for (size_t i=0; i<fLevelData[0].fSize; i += 4) {
        sp += 3;        // Skip RGB
        *dp++ = *sp++;  // Alpha
    }
}

size_t plMipmap::GetUncompressedSize(size_t level) const
{
    const LevelData& lvl = fLevelData[level];
    return lvl.fHeight * lvl.fWidth * (fPixelSize / 8);
}

void plMipmap::DecompressImage(size_t level, void* dest, size_t size)
{
    const LevelData& lvl = fLevelData[level];

    if (fCompressionType == kJPEGCompression) {
        if ((size % 4) != 0)
            throw hsBadParamException(__FILE__, __LINE__, "Invalid dest buffer size");
        if (dest != fImageData)
            memcpy(dest, fImageData, size);

        uint8_t* jbuffer = alloc_aligned(size);
        if (isImageJPEG()) {
            hsRAMStream S;
            S.copyFrom(fJPEGCache.data(), fJPEGCache.size());
            plJPEG::DecompressJPEG(&S, jbuffer, size);

            unsigned int* dp = (unsigned int*)dest;
            unsigned int* sp = (unsigned int*)jbuffer;
            for (size_t i=0; i<(size/4); i++)
                dp[i] = (dp[i] & 0xFF000000) | (sp[i] & 0x00FFFFFF);
        }

        if (isAlphaJPEG()) {
            hsRAMStream S;
            S.copyFrom(fJAlphaCache.data(), fJAlphaCache.size());
            plJPEG::DecompressJPEG(&S, jbuffer, size);

            unsigned int* dp = (unsigned int*)dest;
            unsigned int* sp = (unsigned int*)jbuffer;
            for (size_t i=0; i<(size/4); i++)
                dp[i] = (dp[i] & 0x00FFFFFF) | ((sp[i] << 24) & 0xFF000000);
        }

        free_aligned(jbuffer);
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

void plMipmap::CompressImage(size_t level, void* src, size_t size)
{
    const LevelData& lvl = fLevelData[level];

    if (fCompressionType == kDirectXCompression) {
        unsigned char* imgPtr = fImageData + fLevelData[level].fOffset;
        if (fDXInfo.fCompressionType == kDXT1) {
            squish::CompressImage((squish::u8*)src, lvl.fWidth, lvl.fHeight,
                                  imgPtr, squish::kDxt1 | squish::kColourRangeFit);
        } else if (fDXInfo.fCompressionType == kDXT3) {
            squish::CompressImage((squish::u8*)src, lvl.fWidth, lvl.fHeight,
                                  imgPtr, squish::kDxt3 | squish::kColourRangeFit);
        } else if (fDXInfo.fCompressionType == kDXT5) {
            squish::CompressImage((squish::u8*)src, lvl.fWidth, lvl.fHeight,
                                  imgPtr, squish::kDxt5 | squish::kColourRangeFit);
        } else {
            throw hsBadParamException(__FILE__, __LINE__);
        }
    } else {
        throw hsNotImplementedException(__FILE__, __LINE__, "Compression not currently supported for format.");
    }
}

/* plLODMipmap */
void plLODMipmap::read(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::read(S, mgr);    // Not a typo
    fBase = mgr->readKey(S);
}

void plLODMipmap::write(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::write(S, mgr);   // Not a typo
    mgr->writeKey(S, fBase);
}

void plLODMipmap::IPrcWrite(pfPrcHelper* prc)
{
    hsKeyedObject::IPrcWrite(prc);

    prc->writeSimpleTag("Base");
    plResManager::PrcWriteKey(prc, fBase);
    prc->closeTag();
}

void plLODMipmap::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Base") {
        if (tag->hasChildren())
            fBase = mgr->prcParseKey(tag->getFirstChild());
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}
