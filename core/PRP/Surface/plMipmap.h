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

#ifndef _PLMIPMAP_H
#define _PLMIPMAP_H

#include "plBitmap.h"

class PLASMA_DLL plMipmap : public virtual plBitmap {
    CREATABLE(plMipmap, kMipmap, plBitmap)

public:
    enum { kColorDataRLE = 0x1, kAlphaDataRLE = 0x2 };

protected:
    struct PLASMA_DLL LevelData {
        unsigned int fSize, fOffset;
        unsigned int fWidth, fHeight;
    };

    unsigned char* fImageData;
    size_t fTotalSize;
    unsigned char* fJPEGData;
    size_t fJPEGSize;
    unsigned char* fJAlphaData;
    size_t fJAlphaSize;

    unsigned int fWidth, fHeight, fStride;
    std::vector<LevelData> fLevelData;

public:
    plMipmap();
    plMipmap(unsigned int width, unsigned int height, unsigned char numLevels,
             unsigned char compType, ColorFormat format, unsigned char dxtLevel = kDXTError);
    virtual ~plMipmap();

    void Create(unsigned int width, unsigned int height, unsigned char numLevels,
                unsigned char compType, ColorFormat format, unsigned char dxtLevel = kDXTError);
    void CopyFrom(plMipmap* src);

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void readData(hsStream* S);
    void writeData(hsStream* S);

protected:
    void IReadMipmap(hsStream* S);
    void IWriteMipmap(hsStream* S);
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

    size_t IBuildLevelSizes();
    void IReadJPEGImage(hsStream* S);
    void IReadRawImage(hsStream* S);
    void IReadRLEImage(hsStream* S, bool alpha);
    void IWriteJPEGImage(hsStream* S);
    void IWriteRawImage(hsStream* S);
    void IWriteRLEImage(hsStream* S, bool alpha);

public:
    unsigned int getWidth() const { return fWidth; }
    unsigned int getHeight() const { return fHeight; }
    const void* getImageData() const { return fImageData; }
    size_t getTotalSize() const { return fTotalSize; }
    size_t getNumLevels() const { return fLevelData.size(); }
    unsigned int getLevelSize(size_t idx) const { return fLevelData[idx].fSize; }
    unsigned int getLevelWidth(size_t idx) const { return fLevelData[idx].fWidth; }
    unsigned int getLevelHeight(size_t idx) const { return fLevelData[idx].fHeight; }
    const void* getLevelData(size_t idx) const;

    size_t getJpegSize() const { return fJPEGSize; }
    size_t getJpegAlphaSize() const { return fJAlphaSize; }
    const void* getJpegImage() const { return fJPEGData; }
    const void* getJpegAlpha() const { return fJAlphaData; }

    void setImageData(const void* data, size_t size);
    void setLevelData(size_t idx, const void* data, size_t size);
    void setImageJPEG(const void* data, size_t size);
    void setAlphaJPEG(const void* data, size_t size);

    // Separate color and alpha for JPEG images
    void setColorData(const void* data, size_t size);
    void setAlphaData(const void* alpha, size_t size);
    void extractColorData(void* buffer, size_t size) const;
    void extractAlphaData(void* buffer, size_t size) const;

    bool isImageJPEG() const { return fJPEGData != NULL; }
    bool isAlphaJPEG() const { return fJAlphaData != NULL; }

    size_t GetUncompressedSize(size_t level) const;
    void DecompressImage(size_t level, void* dest, size_t size);
    void CompressImage(size_t level, void* src, size_t size);
};


class PLASMA_DLL plLODMipmap : public virtual plMipmap {
    CREATABLE(plLODMipmap, kLODMipmap, plMipmap)

private:
    plKey fBase;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plKey getBase() const { return fBase; }
    void setBase(plKey base) { fBase = base; }
};

#endif
