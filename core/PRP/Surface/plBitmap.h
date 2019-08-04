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

/**
 * \brief Abstract base class for all renderable surface textures.
 *
 * This class provides the common base for all texture types, including
 * static mipmap and environmaps, dynamic text maps, and render targets for
 * animated layers.
 */
class PLASMA_DLL plBitmap : public hsKeyedObject
{
    CREATABLE(plBitmap, kBitmap, hsKeyedObject)

public:
    enum Flags
    {
        /** Texture contains a full alpha channel */
        kAlphaChannelFlag = 0x1,

        /** Texture contains an alpha (transparent) bit */
        kAlphaBitFlag = 0x2,

        /** Texture uses bump maps */
        kBumpEnvMap = 0x4,

        /** Unknown */
        kForce32Bit = 0x8,

        /** Unknown */
        kDontThrowAwayImage = 0x10,

        /** Don't generate smaller mipmaps -- only use top-level quality */
        kForceOneMipLevel = 0x20,

        /** Unknown */
        kNoMaxSize = 0x40,

        /** Unknown */
        kIntensityMap = 0x80,

        /** Unknown */
        kHalfSize = 0x100,

        /** Unknown */
        kUserOwnsBitmap = 0x200,

        /** Unknown */
        kForceRewrite = 0x400,

        /** Never compress this image */
        kForceNonCompressed = 0x800,

        /** Unknown */
        kIsTexture = 0x1000,

        /** Unknown */
        kIsOffscreen = 0x2000,

        /** Used for projection lights */
        kIsProjected = 0x4000,

        /** Unknown */
        kIsOrtho = 0x8000
    };

    enum CompressionType
    {
        /** Image data is stored as raw (A)RGB data */
        kUncompressed,

        /** Image is DXT compressed */
        kDirectXCompression,

        /** Image is JPEG compressed */
        kJPEGCompression,

        /** Image is PNG compressed */
        kPNGCompression,
    };

    enum ColorSpace
    {
        /** Image has no color space */
        kNoSpace,

        /** Image uses complete ARGB pixels */
        kDirectSpace,

        /** Image uses greyscale color space, 0-255 intensity */
        kGraySpace,

        /** Image data uses a lookup index into a color table */
        kIndexSpace
    };

    enum DxtType
    {
        /** Invalid DXT compression type */
        kDXTError,

        /** DXT1 compression */
        kDXT1,

        /** DXT2 compression (not used) */
        kDXT2_UNUSED,

        /** DXT3 compression */
        kDXT3,

        /** DXT4 compression (not used) */
        kDXT4_UNUSED,

        /** DXT5 compression */
        kDXT5
    };

    enum ColorFormat
    {
        /** 32-bit ARGB color pixels, 8 bits per channel */
        kRGB8888,

        /** 16-bit ARGB color pixels, 4 bits per channel */
        kRGB4444,

        /** 16-bit RGB color pixels, 5 bits per channel + 1 alpha bit */
        kRGB1555,

        /** 8-bit intensity pixels (e.g. grayscale) */
        kInten8,

        /** 8-bit intensity pixels + 8-bit alpha channel */
        kAInten88
    };

    /** Textual name lookup for compression types */
    static const char* kCompressionTypeNames[];

    /** Textual name lookup for color spaces */
    static const char* kSpaceNames[];

    /** Textual name lookup for color layouts */
    static const char* kUncompressedTypeNames[];

    /** Textual name lookup for DXT compression types */
    static const char* kCompressedTypeNames[];

protected:
    /** Stores information about a DXT compressed image */
    struct PLASMA_DLL DirectXInfo
    {
        unsigned char fCompressionType; /** DXT compression type */
        unsigned char fBlockSize;       /** DirectX block size */
    };

    /** Stores information about non-DXT compressed images */
    struct PLASMA_DLL UncompressedInfo
    {
        unsigned char fType;            /** Uncompressed image type */
    };

    unsigned char fPixelSize;
    unsigned char fSpace;
    unsigned short fFlags;
    unsigned char fCompressionType;
    union
    {
        DirectXInfo fDXInfo;
        UncompressedInfo fUncompressedInfo;
    };
    unsigned int fLowModTime, fHighModTime;

public:
    plBitmap()
        : fPixelSize(), fSpace(), fFlags(), fCompressionType(),
          fLowModTime(), fHighModTime() { }

    /** Set pixel configuration based on color type */
    void setConfig(ColorFormat format);

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

    /** Performs internal plBitmap header read */
    void IReadBitmap(hsStream* S);

    /** Performs internal plBitmap header write */
    void IWriteBitmap(hsStream* S);

public:
    /** Returns the texture's number of bits per pixel */
    unsigned char getBPP() const { return fPixelSize; }

    /** Returns the texture's color space */
    unsigned char getSpace() const { return fSpace; }

    /** Returns the texture's display flag set */
    unsigned short getFlags() const { return fFlags; }

    /** Returns the texture's top-level compression type */
    unsigned char getCompressionType() const { return fCompressionType; }

    /** Returns the DirectX texture's DXT compression level */
    unsigned char getDXCompression() const { return fDXInfo.fCompressionType; }

    /** Returns the DirectX texture's DXT Block size */
    unsigned char getDXBlockSize() const { return fDXInfo.fBlockSize; }

    /** Returns a non-DirectX texture's configuration type */
    unsigned char getARGBType() const { return fUncompressedInfo.fType; }

    /** Returns the low word of the texture's modification timestamp */
    unsigned int getLowModTime() const { return fLowModTime; }

    /** Returns the high word of the texture's modification timestamp */
    unsigned int getHighModTime() const { return fHighModTime; }

    /** Set the texture's number of bits per pixel */
    void setBPP(unsigned char bpp) { fPixelSize = bpp; }

    /** Set the texture's color space */
    void setSpace(unsigned char space) { fSpace = space; }

    /** Set the texture's display flags */
    void setFlags(unsigned short flags) { fFlags = flags; }

    /** Set the texture's top-level compression type */
    void setCompressionType(unsigned char type) { fCompressionType = type; }

    /** Set the texture's DXT compression level */
    void setDXCompression(unsigned char type) { fDXInfo.fCompressionType = type; }

    /** Set the texture's DXT block size */
    void setDXBlockSize(unsigned char size) { fDXInfo.fBlockSize = size; }

    /** Set the texture's non-DXT configuration type */
    void setARGBType(unsigned char type) { fUncompressedInfo.fType = type; }

    /** Set the texture's modification timestamp */
    void setModTime(unsigned int low, unsigned int high)
    {
        fLowModTime = low;
        fHighModTime = high;
    }
};

#endif
