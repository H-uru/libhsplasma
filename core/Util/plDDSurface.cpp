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

#include "plDDSurface.h"
#include "Debug/hsExceptions.hpp"
#include "Debug/plDebug.h"
#include "PRP/Surface/plMipmap.h"
#include <cstring>

#define DDSD1_SIZE  0x6C
#define DDSD2_SIZE  0x7C
#define DDPF_SIZE   0x20

/* plDDColorKey */
void plDDSurface::plDDColorKey::read(hsStream* S)
{
    fColorSpaceLow = S->readInt();
    fColorSpaceHigh = S->readInt();
}

void plDDSurface::plDDColorKey::write(hsStream* S)
{
    S->writeInt(fColorSpaceLow);
    S->writeInt(fColorSpaceHigh);
}


/* plDDPixelFormat */
void plDDSurface::plDDPixelFormat::read(hsStream* S)
{
    if (S->readInt() != DDPF_SIZE)
        throw hsBadParamException(__FILE__, __LINE__, "Invalid DDPIXELFORMAT size");

    fFlags = S->readInt();
    fFourCC = S->readInt();
    fBitDepth = S->readInt();
    fRBitMask = S->readInt();
    fGBitMask = S->readInt();
    fBBitMask = S->readInt();
    fAlphaBitMask = S->readInt();

    if (((fFlags & DDPF_FOURCC) != 0) && (fFourCC != FOURCC_DXT1
        && fFourCC != FOURCC_DXT3 && fFourCC != FOURCC_DXT5))
        throw hsBadParamException(__FILE__, __LINE__, "Unsupported DXT compression type");
}

void plDDSurface::plDDPixelFormat::write(hsStream* S)
{
    if (((fFlags & DDPF_FOURCC) != 0) && (fFourCC != FOURCC_DXT1
        && fFourCC != FOURCC_DXT3 && fFourCC != FOURCC_DXT5))
        throw hsBadParamException(__FILE__, __LINE__, "Unsupported DXT compression type");

    S->writeInt(DDPF_SIZE);
    S->writeInt(fFlags);
    S->writeInt(fFourCC);
    S->writeInt(fBitDepth);
    S->writeInt(fRBitMask);
    S->writeInt(fGBitMask);
    S->writeInt(fBBitMask);
    S->writeInt(fAlphaBitMask);
}


/* plDDSurface */
plDDSurface::~plDDSurface()
{
    delete[] fDataBuffer;
    delete[] fLevelSizes;
}

void plDDSurface::read(hsStream* S)
{
    char dwbuf[4];
    S->read(4, dwbuf);
    if (memcmp(dwbuf, "DDS ", 4) != 0)
        throw hsBadParamException(__FILE__, __LINE__, "Invalid DDS magic");

    unsigned int size = S->readInt();
    if (size != DDSD1_SIZE && size != DDSD2_SIZE)
        throw hsBadParamException(__FILE__, __LINE__, "Invalid DDSURFACEDESC size");

    fFlags = S->readInt();
    fHeight = S->readInt();
    fWidth = S->readInt();
    fLinearSize = S->readInt();
    fBackBufferCount = S->readInt();
    fMipmapCount = S->readInt();
    fAlphaDepth = S->readInt();
    S->readInt();                       // Reserved
    S->readInt();                       // lpSurface
    fCKDestOverlay.read(S);
    fCKDestBlt.read(S);
    fCKSrcOverlay.read(S);
    fCKSrcBlt.read(S);

    switch (fFlags & (DDSD_FVF | DDSD_PIXELFORMAT)) {
    case 0:
    case DDSD_PIXELFORMAT:
        fPixelFormat.read(S);
        break;
    case DDSD_FVF:
        fFVF = S->readInt();
        S->readInt();   // Ignored
        S->readInt();
        S->readInt();
        S->readInt();
        S->readInt();
        S->readInt();
        S->readInt();
        break;
    default:
        throw hsBadParamException(__FILE__, __LINE__, "DDSURFACEDESC may not have both DDSD_PIXELFORMAT and DDSD_FVF");
    }

    fCaps = S->readInt();
    if (size == DDSD2_SIZE) {
        fCaps2 = S->readInt();
        fCaps3 = S->readInt();
        fCaps4 = S->readInt();
        fTextureStage = S->readInt();
    } else {
        fCaps2 = 0;
        fCaps3 = 0;
        fCaps4 = 0;
        fTextureStage = 0;
    }

    fDataSize = calcTotalBufferSize();
    if (fDataSize != 0) {
        fDataBuffer = new unsigned char[fDataSize];
        S->read(fDataSize, fDataBuffer);
    }
    if (S->pos() != fDataSize + size + 4) {
        plDebug::Debug("DDS CalcSize-Read difference: {} bytes",
                       (fDataSize + size + 4) - S->pos());
    }
    if (S->pos() != S->size()) {
        plDebug::Debug("DDS RealSize-Read difference: {} bytes",
                       S->size() - S->pos());
    }
}

void plDDSurface::write(hsStream* S)
{
    if (fDataSize != calcTotalBufferSize()) {
        plDebug::Debug("Data format does not match buffer size: {}, {}",
                       fDataSize, calcTotalBufferSize());
    }

    S->write(4, "DDS ");
    S->writeInt(DDSD2_SIZE);

    S->writeInt(fFlags);
    S->writeInt(fHeight);
    S->writeInt(fWidth);
    S->writeInt(fLinearSize);
    S->writeInt(fBackBufferCount);
    S->writeInt(fMipmapCount);
    S->writeInt(fAlphaDepth);
    S->writeInt(0);                 // Reserved
    S->writeInt(0);                 // lpSurface
    fCKDestOverlay.write(S);
    fCKDestBlt.write(S);
    fCKSrcOverlay.write(S);
    fCKSrcBlt.write(S);

    switch (fFlags & (DDSD_FVF | DDSD_PIXELFORMAT)) {
    case 0:
    case DDSD_PIXELFORMAT:
        fPixelFormat.write(S);
        break;
    case DDSD_FVF:
        S->writeInt(fFVF);
        S->writeInt(0);     // Ignored
        S->writeInt(0);
        S->writeInt(0);
        S->writeInt(0);
        S->writeInt(0);
        S->writeInt(0);
        S->writeInt(0);
        break;
    default:
        throw hsBadParamException(__FILE__, __LINE__, "DDSURFACEDESC may not have both DDSD_PIXELFORMAT and DDSD_FVF");
    }

    S->writeInt(fCaps);
    S->writeInt(fCaps2);
    S->writeInt(fCaps3);
    S->writeInt(fCaps4);
    S->writeInt(fTextureStage);

    if (fDataBuffer)
        S->write(fDataSize, fDataBuffer);
}

void plDDSurface::setFromMipmap(const plMipmap* img)
{
    fFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT
           | DDSD_LINEARSIZE;
    fCaps = DDSCAPS_TEXTURE;

    fHeight = img->getHeight();
    fWidth = img->getWidth();
    fLinearSize = (fHeight * fWidth * img->getBPP()) / 8;
    if (img->getCompressionType() == plBitmap::kDirectXCompression
        && img->getDXCompression() == plBitmap::kDXT1)
        fLinearSize /= 2;

    if (img->getCompressionType() != plBitmap::kJPEGCompression) {
        fFlags |= DDSD_MIPMAPCOUNT;
        fCaps |= DDSCAPS_MIPMAP | DDSCAPS_COMPLEX;
        fMipmapCount = img->getNumLevels();
    }

    if (img->getCompressionType() == plBitmap::kDirectXCompression) {
        fPixelFormat.fFlags = DDPF_FOURCC;
        switch (img->getDXCompression()) {
        case plBitmap::kDXT1:
            fPixelFormat.fFourCC = FOURCC_DXT1;
            break;
        case plBitmap::kDXT3:
            fPixelFormat.fFourCC = FOURCC_DXT3;
            break;
        case plBitmap::kDXT5:
            fPixelFormat.fFourCC = FOURCC_DXT5;
            break;
        default:
            throw hsBadParamException(__FILE__, __LINE__, "Unsupported DXT format");
        }
    } else {
        switch (img->getARGBType()) {
        case plBitmap::kRGB8888:
            fPixelFormat.fFlags = DDPF_ALPHAPIXELS | DDPF_RGB;
            fPixelFormat.fBitDepth      = 32;
            fPixelFormat.fRBitMask      = 0x00FF0000;
            fPixelFormat.fGBitMask      = 0x0000FF00;
            fPixelFormat.fBBitMask      = 0x000000FF;
            fPixelFormat.fAlphaBitMask  = 0xFF000000;
            break;
        case plBitmap::kRGB4444:
            fPixelFormat.fFlags = DDPF_ALPHAPIXELS | DDPF_RGB;
            fPixelFormat.fBitDepth      = 16;
            fPixelFormat.fRBitMask      = 0x0F00;
            fPixelFormat.fGBitMask      = 0x00F0;
            fPixelFormat.fBBitMask      = 0x000F;
            fPixelFormat.fAlphaBitMask  = 0xF000;
            break;
        case plBitmap::kRGB1555:
            fPixelFormat.fFlags = DDPF_ALPHAPIXELS | DDPF_RGB;
            fPixelFormat.fBitDepth      = 16;
            fPixelFormat.fRBitMask      = 0x7C00;
            fPixelFormat.fGBitMask      = 0x03E0;
            fPixelFormat.fBBitMask      = 0x001F;
            fPixelFormat.fAlphaBitMask  = 0x8000;
            break;
        case plBitmap::kInten8:
            fPixelFormat.fFlags = DDPF_LUMINANCE;
            fPixelFormat.fBitDepth          = 8;
            fPixelFormat.fLuminanceBitMask  = 0xFF;
            break;
        case plBitmap::kAInten88:
            fPixelFormat.fFlags = DDPF_ALPHAPIXELS | DDPF_LUMINANCE;
            fPixelFormat.fBitDepth          = 16;
            fPixelFormat.fLuminanceBitMask  = 0x00FF;
            fPixelFormat.fAlphaBitMask      = 0xFF00;
            break;
        }
    }

    setData(img->getTotalSize(), (const unsigned char*)img->getImageData());
}

plMipmap* plDDSurface::createMipmap() const
{
    if ((fFlags & DDSD_HEIGHT) == 0 || (fFlags & DDSD_WIDTH) == 0
        || (fFlags & DDSD_PIXELFORMAT) == 0)
        throw hsBadParamException(__FILE__, __LINE__, "DDSurface does not contain required fields");

    unsigned int mipCount = ((fFlags & DDSD_MIPMAPCOUNT) != 0) ? fMipmapCount : 1;
    plMipmap* tex = nullptr;

    if ((fPixelFormat.fFlags & DDPF_FOURCC) != 0) {
        unsigned int dxtLevel = 0;
        switch (fPixelFormat.fFourCC) {
        case FOURCC_DXT1:
            dxtLevel = plBitmap::kDXT1;
            break;
        case FOURCC_DXT3:
            dxtLevel = plBitmap::kDXT3;
            break;
        case FOURCC_DXT5:
            dxtLevel = plBitmap::kDXT5;
            break;
        default:
            throw hsBadParamException(__FILE__, __LINE__, "Invalid FourCC");
        }
        tex = new plMipmap(fWidth, fHeight, mipCount, plBitmap::kDirectXCompression,
                            plBitmap::kRGB8888, dxtLevel);
    } else if ((fPixelFormat.fFlags & DDPF_RGB) != 0) {
        plBitmap::ColorFormat colorConfig = (plBitmap::ColorFormat)0;
        if ((fPixelFormat.fFlags & DDPF_ALPHAPIXELS) != 0 && fPixelFormat.fBitDepth == 32
            && fPixelFormat.fRBitMask == 0x00FF0000 && fPixelFormat.fGBitMask == 0x0000FF00
            && fPixelFormat.fBBitMask == 0x000000FF && fPixelFormat.fAlphaBitMask == 0xFF000000)
            colorConfig = plBitmap::kRGB8888;
        else if ((fPixelFormat.fFlags & DDPF_ALPHAPIXELS) != 0 && fPixelFormat.fBitDepth == 16
            && fPixelFormat.fRBitMask == 0x0F00 && fPixelFormat.fGBitMask == 0x00F0
            && fPixelFormat.fBBitMask == 0x000F && fPixelFormat.fAlphaBitMask == 0xF000)
            colorConfig = plBitmap::kRGB4444;
        else if ((fPixelFormat.fFlags & DDPF_ALPHAPIXELS) != 0 && fPixelFormat.fBitDepth == 16
            && fPixelFormat.fRBitMask == 0x7C00 && fPixelFormat.fGBitMask == 0x03E0
            && fPixelFormat.fBBitMask == 0x001F && fPixelFormat.fAlphaBitMask == 0x8000)
            colorConfig = plBitmap::kRGB1555;
        else if ((fPixelFormat.fFlags & DDPF_ALPHAPIXELS) != 0 && fPixelFormat.fBitDepth == 16
            && fPixelFormat.fRBitMask == 0x7C00 && fPixelFormat.fGBitMask == 0x03E0
            && fPixelFormat.fBBitMask == 0x001F && fPixelFormat.fAlphaBitMask == 0x8000)
            colorConfig = plBitmap::kRGB1555;
        else
            throw hsBadParamException(__FILE__, __LINE__, "Unsupported RGB format");
        tex = new plMipmap(fWidth, fHeight, mipCount, plBitmap::kUncompressed, colorConfig);
    } else if ((fPixelFormat.fFlags & DDPF_LUMINANCE) != 0) {
        plBitmap::ColorFormat colorConfig = (plBitmap::ColorFormat)0;
        if ((fPixelFormat.fFlags & DDPF_ALPHAPIXELS) != 0 && fPixelFormat.fBitDepth == 16
            && fPixelFormat.fLuminanceBitMask == 0x00FF && fPixelFormat.fAlphaBitMask == 0xFF00)
            colorConfig = plBitmap::kAInten88;
        else if ((fPixelFormat.fFlags & DDPF_ALPHAPIXELS) == 0 && fPixelFormat.fBitDepth == 8
            && fPixelFormat.fLuminanceBitMask == 0xFF)
            colorConfig = plBitmap::kInten8;
        else
            throw hsBadParamException(__FILE__, __LINE__, "Unsupported Luminance format");
        tex = new plMipmap(fWidth, fHeight, mipCount, plBitmap::kUncompressed, colorConfig);
    } else {
        throw hsBadParamException(__FILE__, __LINE__, "Unsupported texture format");
    }

    tex->setImageData(fDataBuffer, fDataSize);
    return tex;
}

void plDDSurface::setData(size_t size, const unsigned char* data)
{
    delete[] fDataBuffer;
    fDataSize = size;
    fDataBuffer = new unsigned char[size];
    memcpy(fDataBuffer, data, size);
}

size_t plDDSurface::calcBufferSize(unsigned int width, unsigned int height) const
{
    if ((fFlags & DDSD_HEIGHT) == 0 || (fFlags & DDSD_WIDTH) == 0)
        return 0;
    if ((fFlags & DDSD_PIXELFORMAT) == 0)
        throw hsBadParamException(__FILE__, __LINE__, "Surface has no pixel format descriptor");

    size_t stride, blocks;
    if ((fPixelFormat.fFlags & DDPF_FOURCC) != 0) {
        stride = (fPixelFormat.fFourCC == FOURCC_DXT1) ? 8 : 16;
        blocks = ((width+3)/4) * ((height+3)/4);
    } else {
        stride = ((fPixelFormat.fBitCount * width) + 7) / 8;
        blocks = height;
    }

    return stride * blocks;
}

size_t plDDSurface::calcNumLevels() const
{
    if ((fFlags & DDSD_HEIGHT) == 0 || (fFlags & DDSD_WIDTH) == 0)
        return 0;
    if (fHeight == 0 || fWidth == 0)
        return 0;
    if ((fFlags & DDSD_MIPMAPCOUNT) == 0)
        return 1;

    size_t lvl = 1;
    unsigned int w = fWidth, h = fHeight;
    while (w > 1 || h > 1) {
        w = (w > 1) ? w >> 1 : 1;
        h = (h > 1) ? h >> 1 : 1;
        lvl++;
    }
    return lvl;
}

size_t plDDSurface::calcTotalBufferSize() const
{
    size_t oneBuffer = calcBufferSize(fWidth, fHeight);
    if ((fFlags & DDSD_MIPMAPCOUNT) != 0) {
        unsigned int w = fWidth, h = fHeight;
        for (unsigned int i=1; i<fMipmapCount; i++) {
            w = (w > 1) ? w >> 1 : 1;
            h = (h > 1) ? h >> 1 : 1;
            oneBuffer += calcBufferSize(w, h);
        }
    }

    if ((fFlags & DDSD_BACKBUFFERCOUNT) != 0)
        return oneBuffer * fBackBufferCount;
    return oneBuffer;
}
