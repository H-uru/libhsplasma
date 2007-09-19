#ifndef _PLBITMAP_H
#define _PLBITMAP_H

#include "../../NucleusLib/pnKeyedObject/hsKeyedObject.h"
#include "../../CoreLib/hsStream.h"

#define BITMAPVER (char)2

class plBitmap : public hsKeyedObject {
public:
    struct DirectXInfo {
        enum { kError, kDXT1, kDXT2, kDXT3, kDXT4, kDXT5 };
        unsigned char compressionType;
        unsigned char blockSize;
    };
    
    struct UncompressedInfo {
        enum { kRGB8888, kRGB4444, kRGB1555, kInten8, kAInten88 };
        unsigned char type;
    };

    enum { kNoSpace, kDirectSpace, kGraySpace, kIndexSpace };

    enum Flags {
        kNoFlag = 0x0,
        kAlphaChannelFlag = 0x1,
        kAlphaBitFlag = 0x2,
        kBumpEnvMap = 0x4,
        kForce32Bit = 0x8,
        kDontThrowAwayImage = 0x10,
        kForceOneMipLevel = 0x20,
        kNoMaxSize = 0x40,
        kIntensityMap = 0x80,
        kHalfSize = 0x100,
        kUserOwnsBitmap = 0x200,
        kForceRewrite = 0x400,
        kForceNonCompressed = 0x800,
        kIsTexture = 0x1000,
        kIsOffscreen = 0x2000,
        kMainScreen = 0x0,
        kIsProjected = 0x4000,
        kIsOrtho = 0x8000
    };

    enum { kUncompressed, kDirectXCompression, kJPEGCompression };
    
    static const char* compressionTypeNames[];
    static const char* uncompressedTypeNames[];
    static const char* compressedTypeNames[];

protected:
    char pixelSize, space;
    short flags;
    char compressionType;
    union {
        DirectXInfo dxInfo;
        UncompressedInfo uncompressedInfo;
    };
    unsigned int lowModTime, highModTime;

public:
    plBitmap();
    virtual ~plBitmap();
    
    DECLARE_CREATABLE(plBitmap)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

    virtual void readData(hsStream* S);
    virtual void writeData(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif

