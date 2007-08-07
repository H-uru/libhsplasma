#ifndef _PLMIPMAP_H
#define _PLMIPMAP_H

#include "plBitmap.h"

class plMipmap : public plBitmap {
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

    enum {
        kCreateDetailAlpha = 0x1,
        kCreateDetailAdd = 0x2,
        kCreateDetailMult = 0x4,
        kCreateDetailMask = 0x7,
        kCreateCarryAlpha = 0x10,
        kCreateCarryBlack = 0x20,
        kCreateCarryMask = 0x38
    };

    enum hsGPixelType { kPixelARGB4444, kPixelARGB1555, kPixelAI88, kPixelI8 };
    enum hsGCopyOptions { kCopyLODMask };
    enum { kColorDataRLE = 0x1, kAlphaDataRLE = 0x2 };

    enum CompositeFlags {
        kForceOpaque = 0x1,
        kCopySrcAlpha = 0x2,
        kBlendSrcAlpha = 0x4,
        kMaskSrcAlpha = 0x8,
        kBlendWriteAlpha = 0x10
    };

    enum ScaleFilter { kBoxFilter = 0, kDefaultFilter = 0 };

    struct CompositeOptions {
        unsigned short flags;
        unsigned char srcLevelsToSkip;
        unsigned char opacity;
        float redTint, greenTint, blueTint;
        unsigned short srcClipX, srcClipY, srcClipWidth, srcClipHeight;
    };

protected:
    void* ImageData;
    void* JPEGData;
    unsigned int JPEGSize;
    void* AlphaData;
    unsigned int AlphaSize;
    
    unsigned int width, height, stride, totalSize;
    unsigned char numLevels;
    unsigned int* levelSizes;
    unsigned char* curLevelPtr;
    unsigned char curLevel;
    unsigned int curLvlWidth, curLevelHeight, curLevelStride;
    
    void CopyFrom(plMipmap* src);
    void ICopyImage(plMipmap* src);
    void IRecombineAlpha(plMipmap* alphaImg);
    plMipmap* ISplitAlpha();

public:
    plMipmap();
    plMipmap(int w, int h, int cfg, char nLevels, char compType, char format);
    virtual ~plMipmap();

    DECLARE_CREATABLE(plMipmap)

    void create(int w, int h, int cfg, char nLevels, char compType, char format);
    void setConfig(int cfg);

    const void* getJPEGData();
    unsigned int getJPEGSize();
    const void* getAlphaData();
    unsigned int getAlphaSize();

    virtual void readData(hsStream* S);
    virtual void writeData(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);

    void IBuildLevelSizes();
    void IReadJPEGImage(hsStream* S);
    void IReadRawImage(hsStream* S);
    plMipmap* IReadRLEImage(hsStream* S);
    void IWriteJPEGImage(hsStream* S);
    void IWriteRawImage(hsStream* S);
    void IWriteRLEImage(hsStream* S, plMipmap* img);
};

#endif

