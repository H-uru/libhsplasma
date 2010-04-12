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

#ifndef _PLBITMAP_H
#define _PLBITMAP_H

#include "PRP/KeyedObject/hsKeyedObject.h"

DllClass plBitmap : public hsKeyedObject {
    CREATABLE(plBitmap, kBitmap, hsKeyedObject)

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
    DllStruct DirectXInfo {
        unsigned char fCompressionType;
        unsigned char fBlockSize;
    };

    DllStruct UncompressedInfo {
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

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    void IRead(hsStream* S);
    void IWrite(hsStream* S);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    unsigned char getBPP() const { return fPixelSize; }
    unsigned char getSpace() const { return fSpace; }
    unsigned short getFlags() const { return fFlags; }
    unsigned char getCompressionType() const { return fCompressionType; }
    unsigned char getDXCompression() const { return fDXInfo.fCompressionType; }
    unsigned char getDXBlockSize() const { return fDXInfo.fBlockSize; }
    unsigned char getARGBType() const { return fUncompressedInfo.fType; }
    unsigned int getLowModTime() const { return fLowModTime; }
    unsigned int getHighModTime() const { return fHighModTime; }

    void setBPP(unsigned char bpp) { fPixelSize = bpp; }
    void setSpace(unsigned char space) { fSpace = space; }
    void setFlags(unsigned short flags) { fFlags = flags; }
    void setCompressionType(unsigned char type) { fCompressionType = type; }
    void setDXCompression(unsigned char type) { fDXInfo.fCompressionType = type; }
    void setDXBlockSize(unsigned char size) { fDXInfo.fBlockSize = size; }
    void setARGBType(unsigned char type) { fUncompressedInfo.fType = type; }

    void setModTime(unsigned int low, unsigned int high)
    { fLowModTime = low; fHighModTime = high; }
};

#endif
