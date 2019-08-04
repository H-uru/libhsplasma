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

#ifndef _PLDDSURFACE_H
#define _PLDDSURFACE_H

#include "Stream/hsStream.h"

class PLASMA_DLL plDDSurface
{
public:
    enum Flags
    {
        DDSD_CAPS = 0x1,
        DDSD_HEIGHT = 0x2,
        DDSD_WIDTH = 0x4,
        DDSD_PITCH = 0x8,
        DDSD_BACKBUFFERCOUNT = 0x20,
        DDSD_ZBUFFERBITDEPTH = 0x40,
        DDSD_ALPHABITDEPTH = 0x80,
        DDSD_LPSURFACE = 0x800,
        DDSD_PIXELFORMAT = 0x1000,
        DDSD_CKDESTOVERLAY = 0x2000,
        DDSD_CKDESTBLT = 0x4000,
        DDSD_CKSRCOVERLAY = 0x8000,
        DDSD_CKSRCBLT = 0x10000,
        DDSD_MIPMAPCOUNT = 0x20000,
        DDSD_REFRESHRATE = 0x40000,
        DDSD_LINEARSIZE = 0x80000,
        DDSD_TEXTURESTAGE = 0x100000,
        DDSD_FVF = 0x200000,
        DDSD_SRCVBHANDLE = 0x400000,
        DDSD_DEPTH = 0x800000,
        DDSD_ALL = 0xFFF9EE1,
    };

    enum PixelFormatFlags
    {
        DDPF_ALPHAPIXELS = 0x1,
        DDPF_ALPHA = 0x2,
        DDPF_FOURCC = 0x4,
        DDPF_PALETTEINDEXED4 = 0x8,
        DDPF_PALETTEINDEXEDTO8 = 0x10,
        DDPF_PALETTEINDEXED8 = 0x20,
        DDPF_RGB = 0x40,
        DDPF_COMPRESSED = 0x80,
        DDPF_RGBTOYUV = 0x100,
        DDPF_YUV = 0x200,
        DDPF_ZBUFFER = 0x400,
        DDPF_PALETTEINDEXED1 = 0x800,
        DDPF_PALETTEINDEXED2 = 0x1000,
        DDPF_ZPIXELS = 0x2000,
        DDPF_STENCILBUFFER = 0x4000,
        DDPF_ALPHAPREMULT = 0x8000,
        DDPF_LUMINANCE = 0x20000,
        DDPF_BUMPLUMINANCE = 0x40000,
        DDPF_BUMPDUDV = 0x80000,
    };

    enum DDSCaps
    {
        DDSCAPS_RESERVED1 = 0x1,                // RESERVED
        DDSCAPS_ALPHA = 0x2,
        DDSCAPS_BACKBUFFER = 0x4,
        DDSCAPS_COMPLEX = 0x8,
        DDSCAPS_FLIP = 0x10,
        DDSCAPS_FRONTBUFFER = 0x20,
        DDSCAPS_OFFSCREENPLAIN = 0x40,
        DDSCAPS_OVERLAY = 0x80,
        DDSCAPS_PALETTE = 0x100,
        DDSCAPS_PRIMARYSURFACE = 0x200,
        DDSCAPS_PRIMARYSURFACELEFT = 0x400,     // OBSOLETE
        DDSCAPS_SYSTEMMEMORY = 0x800,
        DDSCAPS_TEXTURE = 0x1000,
        DDSCAPS_3DDEVICE = 0x2000,
        DDSCAPS_VIDEOMEMORY = 0x4000,
        DDSCAPS_VISIBLE = 0x8000,
        DDSCAPS_WRITEONLY = 0x10000,
        DDSCAPS_ZBUFFER = 0x20000,
        DDSCAPS_OWNDC = 0x40000,
        DDSCAPS_LIVEVIDEO = 0x80000,
        DDSCAPS_HWCODEC = 0x100000,
        DDSCAPS_MODEX = 0x200000,
        DDSCAPS_MIPMAP = 0x400000,
        DDSCAPS_RESERVED2 = 0x800000,           // RESERVED
        DDSCAPS_ALLOCONLOAD = 0x4000000,
        DDSCAPS_VIDEOPORT = 0x8000000,
        DDSCAPS_LOCALVIDMEM = 0x10000000,
        DDSCAPS_NONLOCALVIDMEM = 0x20000000,
        DDSCAPS_STANDARDVGAMODE = 0x40000000,
        DDSCAPS_OPTIMIZED = 0x80000000,

        DDSCAPS2_HARDWAREDEINTERLACE = 0x2,     // RESERVED
        DDSCAPS2_HINTDYNAMIC = 0x4,
        DDSCAPS2_HINTSTATIC = 0x8,
        DDSCAPS2_TEXTUREMANAGE = 0x10,
        DDSCAPS2_RESERVED1 = 0x20,              // RESERVED
        DDSCAPS2_RESERVED2 = 0x40,              // RESERVED
        DDSCAPS2_OPAQUE = 0x80,
        DDSCAPS2_HINTALIASING = 0x100,
        DDSCAPS2_CUBEMAP = 0x200,
        DDSCAPS2_CUBEMAP_POSITIVEX = 0x400,
        DDSCAPS2_CUBEMAP_NEGATIVEX = 0x800,
        DDSCAPS2_CUBEMAP_POSITIVEY = 0x1000,
        DDSCAPS2_CUBEMAP_NEGATIVEY = 0x2000,
        DDSCAPS2_CUBEMAP_POSITIVEZ = 0x4000,
        DDSCAPS2_CUBEMAP_NEGATIVEZ = 0x8000,
        DDSCAPS2_CUBEMAP_ALLFACES = 0xFC00,
        DDSCAPS2_MIPMAPSUBLEVEL = 0x10000,
        DDSCAPS2_D3DTEXTUREMANAGE = 0x20000,
        DDSCAPS2_DONOTPERSIST = 0x40000,
        DDSCAPS2_STEREOSURFACELEFT = 0x80000,
        DDSCAPS2_VOLUME = 0x200000,
        DDSCAPS2_NOTUSERLOCKABLE = 0x400000,
        DDSCAPS2_POINTS = 0x800000,
        DDSCAPS2_RTPATCHES = 0x1000000,
        DDSCAPS2_NPATCHES = 0x2000000,
        DDSCAPS2_RESERVED3 = 0x4000000,             // RESERVED
        DDSCAPS2_DISCARDBACKBUFFER = 0x10000000,
        DDSCAPS2_ENABLEALPHACHANNEL = 0x20000000,
        DDSCAPS2_EXTENDEDFORMATPRIMARY = 0x40000000,
        DDSCAPS2_ADDITIONALPRIMARY = 0x80000000,

        DDSCAPS3_MULTISAMPLE_MASK = 0x1F,
        DDSCAPS3_MULTISAMPLE_QUALITY_MASK = 0xE0,
        DDSCAPS3_MULTISAMPLE_QUALITY_SHIFT = 5,
        DDSCAPS3_RESERVED1 = 0x100,                 // RESERVED
        DDSCAPS3_RESERVED2 = 0x200,                 // RESERVED
        DDSCAPS3_LIGHTWEIGHTMIPMAP = 0x400,
        DDSCAPS3_AUTOGENMIPMAP = 0x800,
        DDSCAPS3_DMAP = 0x1000,
        DDSCAPS3_CREATESHAREDRESOURCE = 0x2000,
        DDSCAPS3_READONLYRESOURCE = 0x4000,
        DDSCAPS3_OPENSHAREDRESOURCE = 0x8000,
    };

    enum FourCC
    {
        FOURCC_DXT1 = 0x31545844,
        FOURCC_DXT3 = 0x33545844,
        FOURCC_DXT5 = 0x35545844,
    };

    struct PLASMA_DLL plDDColorKey
    {
        unsigned int fColorSpaceLow, fColorSpaceHigh;

        plDDColorKey() : fColorSpaceLow(), fColorSpaceHigh() { }

        void read(hsStream* S);
        void write(hsStream* S);
    };

    struct PLASMA_DLL plDDPixelFormat
    {
        unsigned int fFlags;
        unsigned int fFourCC;
        union
        {
            unsigned int fBitDepth;
            unsigned int fBitCount;
        };
        union
        {
            unsigned int fRBitMask;
            unsigned int fYBitMask;
            unsigned int fStencilBitDepth;
            unsigned int fLuminanceBitMask;
            unsigned int fBumpDuBitMask;
            unsigned int fOperations;
        };
        union
        {
            unsigned int fGBitMask;
            unsigned int fUBitMask;
            unsigned int fZBitMask;
            unsigned int fBumpDvBitMask;
            struct
            {
                unsigned short fFlipMSTypes;
                unsigned short fBltMSTypes;
            } fMultiSampleCaps;
        };
        union
        {
            unsigned int fBBitMask;
            unsigned int fVBitMask;
            unsigned int fStencilBitMask;
            unsigned int fBumpLuminanceBitMask;
        };
        union
        {
            unsigned int fAlphaBitMask;
            unsigned int fColorZBitMask;
        };

        plDDPixelFormat()
            : fFlags(), fFourCC(), fBitDepth(), fRBitMask(), fGBitMask(),
              fBBitMask(), fAlphaBitMask() { }

        void read(hsStream* S);
        void write(hsStream* S);
    };

public:
    unsigned int fFlags;
    unsigned int fHeight, fWidth;
    union
    {
        unsigned int fPitch;
        unsigned int fLinearSize;
    };
    union
    {
        unsigned int fBackBufferCount;
        unsigned int fDepth;
    };
    union
    {
        unsigned int fMipmapCount;
        unsigned int fZBufferBitDepth;
        unsigned int fRefreshRate;
        unsigned int fSrcVBHandle;
    };
    unsigned int fAlphaDepth;
    plDDColorKey fCKDestOverlay, fCKDestBlt, fCKSrcOverlay, fCKSrcBlt;
    plDDPixelFormat fPixelFormat;
    unsigned int fFVF;
    unsigned int fCaps, fCaps2, fCaps3, fCaps4;
    unsigned int fTextureStage;

private:
    size_t fDataSize;
    unsigned char* fDataBuffer;
    size_t* fLevelSizes;

public:
    plDDSurface()
        : fFlags(), fHeight(), fWidth(), fLinearSize(), fBackBufferCount(),
          fMipmapCount(), fAlphaDepth(), fCaps(), fCaps2(), fCaps3(), fCaps4(),
          fTextureStage(), fDataSize(), fDataBuffer(), fLevelSizes() { }
    ~plDDSurface();

    void read(hsStream* S);
    void write(hsStream* S);

    void setFromMipmap(const class plMipmap* img);
    class plMipmap* createMipmap() const;

    size_t getDataSize() const { return fDataSize; }
    const unsigned char* getData() const { return fDataBuffer; }
    void setData(size_t size, const unsigned char* data);

    size_t calcBufferSize(unsigned int width, unsigned int height) const;
    size_t calcNumLevels() const;
    size_t calcTotalBufferSize() const;
};

#endif
