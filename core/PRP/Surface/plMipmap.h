#ifndef _PLMIPMAP_H
#define _PLMIPMAP_H

#include "plBitmap.h"

DllClass plMipmap : public plBitmap {
public:
    enum {
        kColor8Config = 0x0,
        kGray44Config = 0x1,
        kGray4Config = 0x2,
        kGray8Config = 0x8,
        kRGB16Config = 0x10,
        kRGB32Config = 0x18,
        kARGB32Config = 0x20
    };

    enum { kColorDataRLE = 0x1, kAlphaDataRLE = 0x2 };

protected:
    struct LevelData {
        unsigned int fSize, fOffset;
        unsigned int fWidth, fHeight;
    };

    unsigned char* fImageData;
    unsigned int fTotalSize;
    unsigned char* fAlphaData;
    unsigned int fAlphaSize;
    unsigned char* fJPEGData;
    unsigned int fJPEGSize;
    unsigned char* fJAlphaData;
    unsigned int fJAlphaSize;
    
    unsigned int fWidth, fHeight, fStride;
    hsTArray<LevelData> fLevelData;
    

public:
    plMipmap();
    plMipmap(unsigned int width, unsigned int height, unsigned int cfg,
             unsigned char numLevels, unsigned char compType,
             unsigned char format);
    virtual ~plMipmap();

    DECLARE_CREATABLE(plMipmap)

    void Create(unsigned int width, unsigned int height, unsigned int cfg,
                unsigned char numLevels, unsigned char compType,
                unsigned char format);
    void setConfig(unsigned int cfg);

    virtual void readData(hsStream* S);
    virtual void writeData(hsStream* S);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

    void CopyFrom(plMipmap* src);
    void ICopyImage(plMipmap* src);
    void IRecombineAlpha(plMipmap* alphaImg);
    plMipmap* ISplitAlpha();

    void IBuildLevelSizes();
    void IReadJPEGImage(hsStream* S);
    void IReadRawImage(hsStream* S);
    void IReadRLEImage(hsStream* S, bool alpha);
    void IWriteJPEGImage(hsStream* S);
    void IWriteRawImage(hsStream* S);
    void IWriteRLEImage(hsStream* S, bool alpha);

public:
    void readFromStream(hsStream* S);
    void writeToStream(hsStream* S);
    void readAlphaFromStream(hsStream* S);
    void writeAlphaToStream(hsStream* S);
    plString getSuggestedExt() const;
    plString getSuggestedAlphaExt() const;

    unsigned int getWidth() const;
    unsigned int getHeight() const;
    const void* getImageData() const;
    unsigned int getImageSize() const;
    const void* getAlphaData() const;
    unsigned int getAlphaSize() const;
    size_t getNumLevels() const;
    unsigned int getLevelSize(size_t idx) const;
    unsigned int getLevelWidth(size_t idx) const;
    unsigned int getLevelHeight(size_t idx) const;
    const void* getLevelData(size_t idx) const;

    void setImageData(const void* data);
    void setLevelData(size_t idx, const void* data);
    void setImageJPEG(const void* data, unsigned int size);
    void setAlphaJPEG(const void* data, unsigned int size);

    bool isImageJPEG() const;
    bool isAlphaJPEG() const;
};

#endif
