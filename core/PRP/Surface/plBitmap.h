#ifndef _PLBITMAP_H
#define _PLBITMAP_H

#include "PRP/KeyedObject/hsKeyedObject.h"

DllClass plBitmap : public hsKeyedObject {
public:
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
    enum { kNoSpace, kDirectSpace, kGraySpace, kIndexSpace };

    // DX Compression Type
    enum { kDXTError, kDXT1, kDXT2, kDXT3, kDXT4, kDXT5 };
    // Uncompressed Type
    enum { kRGB8888, kRGB4444, kRGB1555, kInten8, kAInten88 };

    static const char* kCompressionTypeNames[];
    static const char* kSpaceNames[];
    static const char* kUncompressedTypeNames[];
    static const char* kCompressedTypeNames[];

protected:
    struct DirectXInfo {
        unsigned char fCompressionType;
        unsigned char fBlockSize;
    };

    struct UncompressedInfo {
        unsigned char fType;
    };

    unsigned char fPixelSize, fSpace;
    unsigned short fFlags;
    unsigned char fCompressionType;
    union {
        DirectXInfo fDXInfo;
        UncompressedInfo fUncompressedInfo;
    };
    unsigned int fLowModTime, fHighModTime;

public:
    plBitmap();
    virtual ~plBitmap();

    DECLARE_CREATABLE(plBitmap)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    void IRead(hsStream* S);
    void IWrite(hsStream* S);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    unsigned char getBPP() const;
    unsigned char getSpace() const;
    unsigned short getFlags() const;
    unsigned char getCompressionType() const;
    unsigned char getDXCompression() const;
    unsigned char getDXBlockSize() const;
    unsigned char getARGBType() const;
    unsigned int getLowModTime() const;
    unsigned int getHighModTime() const;

    void setBPP(unsigned char bpp);
    void setSpace(unsigned char space);
    void setFlags(unsigned short flags);
    void setCompressionType(unsigned char type);
    void setDXCompression(unsigned char type);
    void setDXBlockSize(unsigned char size);
    void setARGBType(unsigned char type);
    void setModTime(unsigned int low, unsigned int high);
};

#endif
