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

#include "pyDDSurface.h"

#include <Util/plDDSurface.h>
#include <PRP/Surface/plMipmap.h>
#include "Stream/pyStream.h"
#include "PRP/pyCreatable.h"
#include "PRP/Surface/pyBitmap.h"

PY_PLASMA_DEALLOC(DDSurface)
PY_PLASMA_EMPTY_INIT(DDSurface)
PY_PLASMA_NEW(DDSurface, plDDSurface)

PY_METHOD_VA(DDSurface, read,
    "Params: stream\n"
    "Reads a DDS file from a stream")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects an hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects an hsStream");
        return NULL;
    }
    self->fThis->read(stream->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(DDSurface, write,
    "Params: stream\n"
    "Writes a DDS file to a stream")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects an hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects an hsStream");
        return NULL;
    }
    self->fThis->write(stream->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(DDSurface, setFromMipmap,
    "Params: mipmap\n"
    "Sets the fields of this plDDSurface from the supplied plMipmap")
{
    pyMipmap* tex;
    if (!PyArg_ParseTuple(args, "O", &tex)) {
        PyErr_SetString(PyExc_TypeError, "setFromMipmap expects a plMipmap");
        return NULL;
    }
    if (!pyMipmap_Check((PyObject*)tex)) {
        PyErr_SetString(PyExc_TypeError, "setFromMipmap expects a plMipmap");
        return NULL;
    }
    self->fThis->setFromMipmap(tex->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(DDSurface, createMipmap,
    "Params: Mipmap name\n"
    "Create a new plMipmap from this plDDSurface")
{
    const char* name = "";
    if (!PyArg_ParseTuple(args, "|s", &name)) {
        PyErr_SetString(PyExc_TypeError, "createMipmap expects a string");
        return NULL;
    }

    plMipmap* mm = self->fThis->createMipmap();
    mm->init(name);
    return ICreate(mm);
}

PY_METHOD_VA(DDSurface, calcBufferSize,
    "Params: width, height\n"
    "Calculates the size of an buffer within the surface")
{
    int width, height;
    if (!PyArg_ParseTuple(args, "ii", &width, &height)) {
        PyErr_SetString(PyExc_TypeError, "calcBufferSize expects int, int");
        return NULL;
    }
    size_t bufSize = self->fThis->calcBufferSize(width, height);
    return pyPlasma_convert(bufSize);
}

PY_METHOD_NOARGS(DDSurface, calcNumLevels,
    "Calculates the total number of mipmap levels for one surface buffer")
{
    return pyPlasma_convert(self->fThis->calcNumLevels());
}

PY_METHOD_NOARGS(DDSurface, calcTotalBufferSize,
    "Calculates the total size needed to store all buffers in this surface")
{
    return pyPlasma_convert(self->fThis->calcTotalBufferSize());
}

static PyMethodDef pyDDSurface_Methods[] = {
    pyDDSurface_read_method,
    pyDDSurface_write_method,
    pyDDSurface_setFromMipmap_method,
    pyDDSurface_createMipmap_method,
    pyDDSurface_calcBufferSize_method,
    pyDDSurface_calcNumLevels_method,
    pyDDSurface_calcTotalBufferSize_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY_MEMBER(unsigned int, DDSurface, flags, fFlags)
PY_PROPERTY_MEMBER(unsigned int, DDSurface, height, fHeight)
PY_PROPERTY_MEMBER(unsigned int, DDSurface, width, fWidth)
PY_PROPERTY_MEMBER(unsigned int, DDSurface, pitch, fPitch)
PY_PROPERTY_MEMBER(unsigned int, DDSurface, linearSize, fLinearSize)
PY_PROPERTY_MEMBER(unsigned int, DDSurface, depth, fDepth)
PY_PROPERTY_MEMBER(unsigned int, DDSurface, backBufferCount, fBackBufferCount)
PY_PROPERTY_MEMBER(unsigned int, DDSurface, mipmapCount, fMipmapCount)
PY_PROPERTY_MEMBER(unsigned int, DDSurface, zbufferBitDepth, fZBufferBitDepth)
PY_PROPERTY_MEMBER(unsigned int, DDSurface, refreshRate, fRefreshRate)
PY_PROPERTY_MEMBER(unsigned int, DDSurface, srcVBHandle, fSrcVBHandle)
PY_PROPERTY_MEMBER(unsigned int, DDSurface, alphaDepth, fAlphaDepth)

#define DDCK_PROPERTY(name, member)                                     \
    PY_GETSET_GETTER_DECL(DDSurface, name) {                            \
        return Py_BuildValue("ii", self->fThis->member.fColorSpaceLow,  \
                                   self->fThis->member.fColorSpaceHigh); \
    }                                                                   \
    PY_GETSET_SETTER_DECL(DDSurface, name) {                            \
        PY_PROPERTY_CHECK_NULL(name)                                    \
        if (!PyTuple_Check(value) || PyTuple_GET_SIZE(value) != 2) {    \
            PyErr_SetString(PyExc_TypeError, #name " should be a tuple (int, int)"); \
            return -1;                                                  \
        }                                                               \
        PyObject* low = PyTuple_GET_ITEM(value, 0);                     \
        PyObject* hi = PyTuple_GET_ITEM(value, 1);                      \
        if (!pyPlasma_check<unsigned int>(low) || !pyPlasma_check<unsigned int>(hi)) { \
            PyErr_SetString(PyExc_TypeError, #name " should be a tuple (int, int)"); \
            return -1;                                                  \
        }                                                               \
        self->fThis->member.fColorSpaceLow = pyPlasma_get<unsigned int>(low); \
        self->fThis->member.fColorSpaceHigh = pyPlasma_get<unsigned int>(hi); \
        return 0;                                                       \
    }                                                                   \
    PY_PROPERTY_GETSET_DECL(DDSurface, name)

DDCK_PROPERTY(ckDestOverlay, fCKDestOverlay)
DDCK_PROPERTY(ckDestBlt, fCKDestBlt)
DDCK_PROPERTY(ckSrcOverlay, fCKSrcOverlay)
DDCK_PROPERTY(ckSrcBlt, fCKSrcBlt)

PY_PROPERTY_MEMBER(unsigned int, DDSurface, fvf, fFVF)
PY_PROPERTY_MEMBER(unsigned int, DDSurface, caps, fCaps)
PY_PROPERTY_MEMBER(unsigned int, DDSurface, caps2, fCaps2)
PY_PROPERTY_MEMBER(unsigned int, DDSurface, caps3, fCaps3)
PY_PROPERTY_MEMBER(unsigned int, DDSurface, caps4, fCaps4)
PY_PROPERTY_MEMBER(unsigned int, DDSurface, textureStage, fTextureStage)
PY_PROPERTY_MEMBER(unsigned int, DDSurface, pf_flags, fPixelFormat.fFlags)
PY_PROPERTY_MEMBER(unsigned int, DDSurface, pf_fourCC, fPixelFormat.fFourCC)
PY_PROPERTY_MEMBER(unsigned int, DDSurface, pf_bitDepth, fPixelFormat.fBitDepth)
PY_PROPERTY_MEMBER(unsigned int, DDSurface, pf_bitCount, fPixelFormat.fBitCount)
PY_PROPERTY_MEMBER(unsigned int, DDSurface, pf_RBitMask, fPixelFormat.fRBitMask)
PY_PROPERTY_MEMBER(unsigned int, DDSurface, pf_YBitMask, fPixelFormat.fYBitMask)
PY_PROPERTY_MEMBER(unsigned int, DDSurface, pf_stencilBitDepth, fPixelFormat.fStencilBitDepth)
PY_PROPERTY_MEMBER(unsigned int, DDSurface, pf_luminanceBitMask, fPixelFormat.fLuminanceBitMask)
PY_PROPERTY_MEMBER(unsigned int, DDSurface, pf_bumpDuBitMask, fPixelFormat.fBumpDuBitMask)
PY_PROPERTY_MEMBER(unsigned int, DDSurface, pf_operations, fPixelFormat.fOperations)
PY_PROPERTY_MEMBER(unsigned int, DDSurface, pf_GBitMask, fPixelFormat.fGBitMask)
PY_PROPERTY_MEMBER(unsigned int, DDSurface, pf_UBitMask, fPixelFormat.fUBitMask)
PY_PROPERTY_MEMBER(unsigned int, DDSurface, pf_ZBitMask, fPixelFormat.fZBitMask)
PY_PROPERTY_MEMBER(unsigned int, DDSurface, pf_bumpDvBitMask, fPixelFormat.fBumpDvBitMask)

PY_GETSET_GETTER_DECL(DDSurface, pf_multiSampleCaps) {
    return Py_BuildValue("ii", self->fThis->fPixelFormat.fMultiSampleCaps.fFlipMSTypes,
                               self->fThis->fPixelFormat.fMultiSampleCaps.fBltMSTypes);
}

PY_GETSET_SETTER_DECL(DDSurface, pf_multiSampleCaps) {
    PY_PROPERTY_CHECK_NULL(pf_multiSampleCaps)
    if (!PyTuple_Check(value) || PyTuple_GET_SIZE(value) != 2) {
        PyErr_SetString(PyExc_TypeError, "pf_multiSampleCaps should be a tuple (int, int)");
        return -1;
    }
    PyObject* flip = PyTuple_GET_ITEM(value, 0);
    PyObject* blt = PyTuple_GET_ITEM(value, 1);
    if (!pyPlasma_check<unsigned short>(flip) || !pyPlasma_check<unsigned short>(blt)) {
        PyErr_SetString(PyExc_TypeError, "pf_multiSampleCaps should be a tuple (int, int)");
        return -1;
    }
    self->fThis->fPixelFormat.fMultiSampleCaps.fFlipMSTypes = pyPlasma_get<unsigned short>(flip);
    self->fThis->fPixelFormat.fMultiSampleCaps.fBltMSTypes = pyPlasma_get<unsigned short>(blt);
    return 0;
}

PY_PROPERTY_GETSET_DECL(DDSurface, pf_multiSampleCaps)

PY_PROPERTY_MEMBER(unsigned int, DDSurface, pf_BBitMask, fPixelFormat.fBBitMask)
PY_PROPERTY_MEMBER(unsigned int, DDSurface, pf_VBitMask, fPixelFormat.fVBitMask)
PY_PROPERTY_MEMBER(unsigned int, DDSurface, pf_stencilBitMask, fPixelFormat.fStencilBitMask)
PY_PROPERTY_MEMBER(unsigned int, DDSurface, pf_bumpLuminanceBitMask, fPixelFormat.fBumpLuminanceBitMask)
PY_PROPERTY_MEMBER(unsigned int, DDSurface, pf_alphaBitMask, fPixelFormat.fAlphaBitMask)
PY_PROPERTY_MEMBER(unsigned int, DDSurface, pf_colorZBitMask, fPixelFormat.fColorZBitMask)

PY_GETSET_GETTER_DECL(DDSurface, data) {
    return PyBytes_FromStringAndSize((const char*)self->fThis->getData(),
                                     self->fThis->getDataSize());
}

PY_GETSET_SETTER_DECL(DDSurface, data) {
    PY_PROPERTY_CHECK_NULL(data)
    if (value == Py_None) {
        self->fThis->setData(0, NULL);
    } else if (PyBytes_Check(value)) {
        char* data;
        Py_ssize_t size;
        PyBytes_AsStringAndSize(value, &data, &size);
        self->fThis->setData(size, (const unsigned char*)data);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "data must be a binary string");
        return -1;
    }
    return 0;
}

PY_PROPERTY_GETSET_DECL(DDSurface, data)

static PyGetSetDef pyDDSurface_GetSet[] = {
    pyDDSurface_flags_getset,
    pyDDSurface_height_getset,
    pyDDSurface_width_getset,
    pyDDSurface_pitch_getset,
    pyDDSurface_linearSize_getset,
    pyDDSurface_backBufferCount_getset,
    pyDDSurface_depth_getset,
    pyDDSurface_mipmapCount_getset,
    pyDDSurface_zbufferBitDepth_getset,
    pyDDSurface_refreshRate_getset,
    pyDDSurface_srcVBHandle_getset,
    pyDDSurface_alphaDepth_getset,
    pyDDSurface_ckDestOverlay_getset,
    pyDDSurface_ckDestBlt_getset,
    pyDDSurface_ckSrcOverlay_getset,
    pyDDSurface_ckSrcBlt_getset,
    pyDDSurface_fvf_getset,
    pyDDSurface_caps_getset,
    pyDDSurface_caps2_getset,
    pyDDSurface_caps3_getset,
    pyDDSurface_caps4_getset,
    pyDDSurface_textureStage_getset,
    pyDDSurface_pf_flags_getset,
    pyDDSurface_pf_fourCC_getset,
    pyDDSurface_pf_bitDepth_getset,
    pyDDSurface_pf_bitCount_getset,
    pyDDSurface_pf_RBitMask_getset,
    pyDDSurface_pf_YBitMask_getset,
    pyDDSurface_pf_stencilBitDepth_getset,
    pyDDSurface_pf_luminanceBitMask_getset,
    pyDDSurface_pf_bumpDuBitMask_getset,
    pyDDSurface_pf_operations_getset,
    pyDDSurface_pf_GBitMask_getset,
    pyDDSurface_pf_UBitMask_getset,
    pyDDSurface_pf_ZBitMask_getset,
    pyDDSurface_pf_bumpDvBitMask_getset,
    pyDDSurface_pf_multiSampleCaps_getset,
    pyDDSurface_pf_BBitMask_getset,
    pyDDSurface_pf_VBitMask_getset,
    pyDDSurface_pf_stencilBitMask_getset,
    pyDDSurface_pf_bumpLuminanceBitMask_getset,
    pyDDSurface_pf_alphaBitMask_getset,
    pyDDSurface_pf_colorZBitMask_getset,
    pyDDSurface_data_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(DDSurface, plDDSurface, "plDDSurface wrapper")

PY_PLASMA_TYPE_INIT(DDSurface) {
    pyDDSurface_Type.tp_dealloc = pyDDSurface_dealloc;
    pyDDSurface_Type.tp_init = pyDDSurface___init__;
    pyDDSurface_Type.tp_new = pyDDSurface_new;
    pyDDSurface_Type.tp_methods = pyDDSurface_Methods;
    pyDDSurface_Type.tp_getset = pyDDSurface_GetSet;
    if (PyType_CheckAndReady(&pyDDSurface_Type) < 0)
        return NULL;

    PY_TYPE_ADD_CONST(DDSurface, "DDSD_CAPS", plDDSurface::DDSD_CAPS);
    PY_TYPE_ADD_CONST(DDSurface, "DDSD_HEIGHT", plDDSurface::DDSD_HEIGHT);
    PY_TYPE_ADD_CONST(DDSurface, "DDSD_WIDTH", plDDSurface::DDSD_WIDTH);
    PY_TYPE_ADD_CONST(DDSurface, "DDSD_PITCH", plDDSurface::DDSD_PITCH);
    PY_TYPE_ADD_CONST(DDSurface, "DDSD_BACKBUFFERCOUNT", plDDSurface::DDSD_BACKBUFFERCOUNT);
    PY_TYPE_ADD_CONST(DDSurface, "DDSD_ZBUFFERBITDEPTH", plDDSurface::DDSD_ZBUFFERBITDEPTH);
    PY_TYPE_ADD_CONST(DDSurface, "DDSD_ALPHABITDEPTH", plDDSurface::DDSD_ALPHABITDEPTH);
    PY_TYPE_ADD_CONST(DDSurface, "DDSD_LPSURFACE", plDDSurface::DDSD_LPSURFACE);
    PY_TYPE_ADD_CONST(DDSurface, "DDSD_PIXELFORMAT", plDDSurface::DDSD_PIXELFORMAT);
    PY_TYPE_ADD_CONST(DDSurface, "DDSD_CKDESTOVERLAY", plDDSurface::DDSD_CKDESTOVERLAY);
    PY_TYPE_ADD_CONST(DDSurface, "DDSD_CKDESTBLT", plDDSurface::DDSD_CKDESTBLT);
    PY_TYPE_ADD_CONST(DDSurface, "DDSD_CKSRCOVERLAY", plDDSurface::DDSD_CKSRCOVERLAY);
    PY_TYPE_ADD_CONST(DDSurface, "DDSD_CKSRCBLT", plDDSurface::DDSD_CKSRCBLT);
    PY_TYPE_ADD_CONST(DDSurface, "DDSD_MIPMAPCOUNT", plDDSurface::DDSD_MIPMAPCOUNT);
    PY_TYPE_ADD_CONST(DDSurface, "DDSD_REFRESHRATE", plDDSurface::DDSD_REFRESHRATE);
    PY_TYPE_ADD_CONST(DDSurface, "DDSD_LINEARSIZE", plDDSurface::DDSD_LINEARSIZE);
    PY_TYPE_ADD_CONST(DDSurface, "DDSD_TEXTURESTAGE", plDDSurface::DDSD_TEXTURESTAGE);
    PY_TYPE_ADD_CONST(DDSurface, "DDSD_FVF", plDDSurface::DDSD_FVF);
    PY_TYPE_ADD_CONST(DDSurface, "DDSD_SRCVBHANDLE", plDDSurface::DDSD_SRCVBHANDLE);
    PY_TYPE_ADD_CONST(DDSurface, "DDSD_DEPTH", plDDSurface::DDSD_DEPTH);
    PY_TYPE_ADD_CONST(DDSurface, "DDSD_ALL", plDDSurface::DDSD_ALL);

    PY_TYPE_ADD_CONST(DDSurface, "DDPF_ALPHAPIXELS", plDDSurface::DDPF_ALPHAPIXELS);
    PY_TYPE_ADD_CONST(DDSurface, "DDPF_ALPHA", plDDSurface::DDPF_ALPHA);
    PY_TYPE_ADD_CONST(DDSurface, "DDPF_FOURCC", plDDSurface::DDPF_FOURCC);
    PY_TYPE_ADD_CONST(DDSurface, "DDPF_PALETTEINDEXED4", plDDSurface::DDPF_PALETTEINDEXED4);
    PY_TYPE_ADD_CONST(DDSurface, "DDPF_PALETTEINDEXEDTO8", plDDSurface::DDPF_PALETTEINDEXEDTO8);
    PY_TYPE_ADD_CONST(DDSurface, "DDPF_PALETTEINDEXED8", plDDSurface::DDPF_PALETTEINDEXED8);
    PY_TYPE_ADD_CONST(DDSurface, "DDPF_RGB", plDDSurface::DDPF_RGB);
    PY_TYPE_ADD_CONST(DDSurface, "DDPF_COMPRESSED", plDDSurface::DDPF_COMPRESSED);
    PY_TYPE_ADD_CONST(DDSurface, "DDPF_RGBTOYUV", plDDSurface::DDPF_RGBTOYUV);
    PY_TYPE_ADD_CONST(DDSurface, "DDPF_YUV", plDDSurface::DDPF_YUV);
    PY_TYPE_ADD_CONST(DDSurface, "DDPF_ZBUFFER", plDDSurface::DDPF_ZBUFFER);
    PY_TYPE_ADD_CONST(DDSurface, "DDPF_PALETTEINDEXED1", plDDSurface::DDPF_PALETTEINDEXED1);
    PY_TYPE_ADD_CONST(DDSurface, "DDPF_PALETTEINDEXED2", plDDSurface::DDPF_PALETTEINDEXED2);
    PY_TYPE_ADD_CONST(DDSurface, "DDPF_ZPIXELS", plDDSurface::DDPF_ZPIXELS);
    PY_TYPE_ADD_CONST(DDSurface, "DDPF_STENCILBUFFER", plDDSurface::DDPF_STENCILBUFFER);
    PY_TYPE_ADD_CONST(DDSurface, "DDPF_ALPHAPREMULT", plDDSurface::DDPF_ALPHAPREMULT);
    PY_TYPE_ADD_CONST(DDSurface, "DDPF_LUMINANCE", plDDSurface::DDPF_LUMINANCE);
    PY_TYPE_ADD_CONST(DDSurface, "DDPF_BUMPLUMINANCE", plDDSurface::DDPF_BUMPLUMINANCE);
    PY_TYPE_ADD_CONST(DDSurface, "DDPF_BUMPDUDV", plDDSurface::DDPF_BUMPDUDV);

    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS_RESERVED1",
                      plDDSurface::DDSCAPS_RESERVED1);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS_ALPHA",
                      plDDSurface::DDSCAPS_ALPHA);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS_BACKBUFFER",
                      plDDSurface::DDSCAPS_BACKBUFFER);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS_COMPLEX",
                      plDDSurface::DDSCAPS_COMPLEX);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS_FLIP",
                      plDDSurface::DDSCAPS_FLIP);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS_FRONTBUFFER",
                      plDDSurface::DDSCAPS_FRONTBUFFER);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS_OFFSCREENPLAIN",
                      plDDSurface::DDSCAPS_OFFSCREENPLAIN);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS_OVERLAY",
                      plDDSurface::DDSCAPS_OVERLAY);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS_PALETTE",
                      plDDSurface::DDSCAPS_PALETTE);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS_PRIMARYSURFACE",
                      plDDSurface::DDSCAPS_PRIMARYSURFACE);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS_PRIMARYSURFACELEFT",
                      plDDSurface::DDSCAPS_PRIMARYSURFACELEFT);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS_SYSTEMMEMORY",
                      plDDSurface::DDSCAPS_SYSTEMMEMORY);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS_TEXTURE",
                      plDDSurface::DDSCAPS_TEXTURE);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS_3DDEVICE",
                      plDDSurface::DDSCAPS_3DDEVICE);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS_VIDEOMEMORY",
                      plDDSurface::DDSCAPS_VIDEOMEMORY);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS_VISIBLE",
                      plDDSurface::DDSCAPS_VISIBLE);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS_WRITEONLY",
                      plDDSurface::DDSCAPS_WRITEONLY);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS_ZBUFFER",
                      plDDSurface::DDSCAPS_ZBUFFER);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS_OWNDC",
                      plDDSurface::DDSCAPS_OWNDC);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS_LIVEVIDEO",
                      plDDSurface::DDSCAPS_LIVEVIDEO);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS_HWCODEC",
                      plDDSurface::DDSCAPS_HWCODEC);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS_MODEX",
                      plDDSurface::DDSCAPS_MODEX);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS_MIPMAP",
                      plDDSurface::DDSCAPS_MIPMAP);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS_RESERVED2",
                      plDDSurface::DDSCAPS_RESERVED2);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS_ALLOCONLOAD",
                      plDDSurface::DDSCAPS_ALLOCONLOAD);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS_VIDEOPORT",
                      plDDSurface::DDSCAPS_VIDEOPORT);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS_LOCALVIDMEM",
                      plDDSurface::DDSCAPS_LOCALVIDMEM);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS_NONLOCALVIDMEM",
                      plDDSurface::DDSCAPS_NONLOCALVIDMEM);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS_STANDARDVGAMODE",
                      plDDSurface::DDSCAPS_STANDARDVGAMODE);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS_OPTIMIZED",
                      plDDSurface::DDSCAPS_OPTIMIZED);

    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS2_HARDWAREDEINTERLACE",
                      plDDSurface::DDSCAPS2_HARDWAREDEINTERLACE);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS2_HINTDYNAMIC",
                      plDDSurface::DDSCAPS2_HINTDYNAMIC);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS2_HINTSTATIC",
                      plDDSurface::DDSCAPS2_HINTSTATIC);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS2_TEXTUREMANAGE",
                      plDDSurface::DDSCAPS2_TEXTUREMANAGE);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS2_RESERVED1",
                      plDDSurface::DDSCAPS2_RESERVED1);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS2_RESERVED2",
                      plDDSurface::DDSCAPS2_RESERVED2);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS2_OPAQUE",
                      plDDSurface::DDSCAPS2_OPAQUE);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS2_HINTALIASING",
                      plDDSurface::DDSCAPS2_HINTALIASING);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS2_CUBEMAP",
                      plDDSurface::DDSCAPS2_CUBEMAP);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS2_CUBEMAP_POSITIVEX",
                      plDDSurface::DDSCAPS2_CUBEMAP_POSITIVEX);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS2_CUBEMAP_NEGATIVEX",
                      plDDSurface::DDSCAPS2_CUBEMAP_NEGATIVEX);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS2_CUBEMAP_POSITIVEY",
                      plDDSurface::DDSCAPS2_CUBEMAP_POSITIVEY);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS2_CUBEMAP_NEGATIVEY",
                      plDDSurface::DDSCAPS2_CUBEMAP_NEGATIVEY);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS2_CUBEMAP_POSITIVEZ",
                      plDDSurface::DDSCAPS2_CUBEMAP_POSITIVEZ);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS2_CUBEMAP_NEGATIVEZ",
                      plDDSurface::DDSCAPS2_CUBEMAP_NEGATIVEZ);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS2_CUBEMAP_ALLFACES",
                      plDDSurface::DDSCAPS2_CUBEMAP_ALLFACES);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS2_MIPMAPSUBLEVEL",
                      plDDSurface::DDSCAPS2_MIPMAPSUBLEVEL);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS2_D3DTEXTUREMANAGE",
                      plDDSurface::DDSCAPS2_D3DTEXTUREMANAGE);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS2_DONOTPERSIST",
                      plDDSurface::DDSCAPS2_DONOTPERSIST);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS2_STEREOSURFACELEFT",
                      plDDSurface::DDSCAPS2_STEREOSURFACELEFT);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS2_VOLUME",
                      plDDSurface::DDSCAPS2_VOLUME);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS2_NOTUSERLOCKABLE",
                      plDDSurface::DDSCAPS2_NOTUSERLOCKABLE);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS2_POINTS",
                      plDDSurface::DDSCAPS2_POINTS);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS2_RTPATCHES",
                      plDDSurface::DDSCAPS2_RTPATCHES);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS2_NPATCHES",
                      plDDSurface::DDSCAPS2_NPATCHES);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS2_RESERVED3",
                      plDDSurface::DDSCAPS2_RESERVED3);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS2_DISCARDBACKBUFFER",
                      plDDSurface::DDSCAPS2_DISCARDBACKBUFFER);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS2_ENABLEALPHACHANNEL",
                      plDDSurface::DDSCAPS2_ENABLEALPHACHANNEL);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS2_EXTENDEDFORMATPRIMARY",
                      plDDSurface::DDSCAPS2_EXTENDEDFORMATPRIMARY);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS2_ADDITIONALPRIMARY",
                      plDDSurface::DDSCAPS2_ADDITIONALPRIMARY);

    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS3_MULTISAMPLE_MASK",
                      plDDSurface::DDSCAPS3_MULTISAMPLE_MASK);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS3_MULTISAMPLE_QUALITY_MASK",
                      plDDSurface::DDSCAPS3_MULTISAMPLE_QUALITY_MASK);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS3_MULTISAMPLE_QUALITY_SHIFT",
                      plDDSurface::DDSCAPS3_MULTISAMPLE_QUALITY_SHIFT);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS3_RESERVED1",
                      plDDSurface::DDSCAPS3_RESERVED1);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS3_RESERVED2",
                      plDDSurface::DDSCAPS3_RESERVED2);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS3_LIGHTWEIGHTMIPMAP",
                      plDDSurface::DDSCAPS3_LIGHTWEIGHTMIPMAP);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS3_AUTOGENMIPMAP",
                      plDDSurface::DDSCAPS3_AUTOGENMIPMAP);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS3_DMAP",
                      plDDSurface::DDSCAPS3_DMAP);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS3_CREATESHAREDRESOURCE",
                      plDDSurface::DDSCAPS3_CREATESHAREDRESOURCE);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS3_READONLYRESOURCE",
                      plDDSurface::DDSCAPS3_READONLYRESOURCE);
    PY_TYPE_ADD_CONST(DDSurface, "DDSCAPS3_OPENSHAREDRESOURCE",
                      plDDSurface::DDSCAPS3_OPENSHAREDRESOURCE);

    PY_TYPE_ADD_CONST(DDSurface, "FOURCC_DXT1", plDDSurface::FOURCC_DXT1);
    PY_TYPE_ADD_CONST(DDSurface, "FOURCC_DXT3", plDDSurface::FOURCC_DXT3);
    PY_TYPE_ADD_CONST(DDSurface, "FOURCC_DXT5", plDDSurface::FOURCC_DXT5);

    Py_INCREF(&pyDDSurface_Type);
    return (PyObject*)&pyDDSurface_Type;
}

PY_PLASMA_IFC_METHODS(DDSurface, plDDSurface)
