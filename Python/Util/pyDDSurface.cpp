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

extern "C" {

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

PY_METHOD_NOARGS(DDSurface, createMipmap,
    "Create a new plMipmap from this plDDSurface")
{
    plMipmap* tex = self->fThis->createMipmap();
    return ICreate(tex);
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
    size_t levels = self->fThis->calcNumLevels();
    return pyPlasma_convert(levels);
}

PY_METHOD_NOARGS(DDSurface, calcTotalBufferSize,
    "Calculates the total size needed to store all buffers in this surface")
{
    size_t totSize = self->fThis->calcTotalBufferSize();
    return pyPlasma_convert(totSize);
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
        if (value == NULL) {                                            \
            PyErr_SetString(PyExc_RuntimeError, #name " cannot be deleted"); \
            return -1;                                                  \
        }                                                               \
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
    if (value == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "pf_multiSampleCaps cannot be deleted");
        return -1;
    }
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
    if (value == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "data cannot be deleted");
        return -1;
    } else if (value == Py_None) {
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

PyTypeObject pyDDSurface_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plDDSurface",           /* tp_name */
    sizeof(pyDDSurface),                /* tp_basicsize */
    0,                                  /* tp_itemsize */

    pyDDSurface_dealloc,                /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_compare */
    NULL,                               /* tp_repr */
    NULL,                               /* tp_as_number */
    NULL,                               /* tp_as_sequence */
    NULL,                               /* tp_as_mapping */
    NULL,                               /* tp_hash */
    NULL,                               /* tp_call */
    NULL,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */

    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
    "plDDSurface wrapper",              /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyDDSurface_Methods,                /* tp_methods */
    NULL,                               /* tp_members */
    pyDDSurface_GetSet,                 /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    pyDDSurface___init__,               /* tp_init */
    NULL,                               /* tp_alloc */
    pyDDSurface_new,                    /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */

    NULL,                               /* tp_del */
    TP_VERSION_TAG_INIT                 /* tp_version_tag */
    TP_FINALIZE_INIT                    /* tp_finalize */
};

PyObject* Init_pyDDSurface_Type() {
    if (PyType_Ready(&pyDDSurface_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSD_CAPS",
                         PyInt_FromLong(plDDSurface::DDSD_CAPS));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSD_HEIGHT",
                         PyInt_FromLong(plDDSurface::DDSD_HEIGHT));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSD_WIDTH",
                         PyInt_FromLong(plDDSurface::DDSD_WIDTH));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSD_PITCH",
                         PyInt_FromLong(plDDSurface::DDSD_PITCH));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSD_BACKBUFFERCOUNT",
                         PyInt_FromLong(plDDSurface::DDSD_BACKBUFFERCOUNT));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSD_ZBUFFERBITDEPTH",
                         PyInt_FromLong(plDDSurface::DDSD_ZBUFFERBITDEPTH));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSD_ALPHABITDEPTH",
                         PyInt_FromLong(plDDSurface::DDSD_ALPHABITDEPTH));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSD_LPSURFACE",
                         PyInt_FromLong(plDDSurface::DDSD_LPSURFACE));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSD_PIXELFORMAT",
                         PyInt_FromLong(plDDSurface::DDSD_PIXELFORMAT));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSD_CKDESTOVERLAY",
                         PyInt_FromLong(plDDSurface::DDSD_CKDESTOVERLAY));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSD_CKDESTBLT",
                         PyInt_FromLong(plDDSurface::DDSD_CKDESTBLT));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSD_CKSRCOVERLAY",
                         PyInt_FromLong(plDDSurface::DDSD_CKSRCOVERLAY));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSD_CKSRCBLT",
                         PyInt_FromLong(plDDSurface::DDSD_CKSRCBLT));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSD_MIPMAPCOUNT",
                         PyInt_FromLong(plDDSurface::DDSD_MIPMAPCOUNT));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSD_REFRESHRATE",
                         PyInt_FromLong(plDDSurface::DDSD_REFRESHRATE));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSD_LINEARSIZE",
                         PyInt_FromLong(plDDSurface::DDSD_LINEARSIZE));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSD_TEXTURESTAGE",
                         PyInt_FromLong(plDDSurface::DDSD_TEXTURESTAGE));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSD_FVF",
                         PyInt_FromLong(plDDSurface::DDSD_FVF));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSD_SRCVBHANDLE",
                         PyInt_FromLong(plDDSurface::DDSD_SRCVBHANDLE));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSD_DEPTH",
                         PyInt_FromLong(plDDSurface::DDSD_DEPTH));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSD_ALL",
                         PyInt_FromLong(plDDSurface::DDSD_ALL));

    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDPF_ALPHAPIXELS",
                         PyInt_FromLong(plDDSurface::DDPF_ALPHAPIXELS));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDPF_ALPHA",
                         PyInt_FromLong(plDDSurface::DDPF_ALPHA));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDPF_FOURCC",
                         PyInt_FromLong(plDDSurface::DDPF_FOURCC));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDPF_PALETTEINDEXED4",
                         PyInt_FromLong(plDDSurface::DDPF_PALETTEINDEXED4));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDPF_PALETTEINDEXEDTO8",
                         PyInt_FromLong(plDDSurface::DDPF_PALETTEINDEXEDTO8));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDPF_PALETTEINDEXED8",
                         PyInt_FromLong(plDDSurface::DDPF_PALETTEINDEXED8));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDPF_RGB",
                         PyInt_FromLong(plDDSurface::DDPF_RGB));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDPF_COMPRESSED",
                         PyInt_FromLong(plDDSurface::DDPF_COMPRESSED));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDPF_RGBTOYUV",
                         PyInt_FromLong(plDDSurface::DDPF_RGBTOYUV));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDPF_YUV",
                         PyInt_FromLong(plDDSurface::DDPF_YUV));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDPF_ZBUFFER",
                         PyInt_FromLong(plDDSurface::DDPF_ZBUFFER));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDPF_PALETTEINDEXED1",
                         PyInt_FromLong(plDDSurface::DDPF_PALETTEINDEXED1));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDPF_PALETTEINDEXED2",
                         PyInt_FromLong(plDDSurface::DDPF_PALETTEINDEXED2));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDPF_ZPIXELS",
                         PyInt_FromLong(plDDSurface::DDPF_ZPIXELS));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDPF_STENCILBUFFER",
                         PyInt_FromLong(plDDSurface::DDPF_STENCILBUFFER));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDPF_ALPHAPREMULT",
                         PyInt_FromLong(plDDSurface::DDPF_ALPHAPREMULT));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDPF_LUMINANCE",
                         PyInt_FromLong(plDDSurface::DDPF_LUMINANCE));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDPF_BUMPLUMINANCE",
                         PyInt_FromLong(plDDSurface::DDPF_BUMPLUMINANCE));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDPF_BUMPDUDV",
                         PyInt_FromLong(plDDSurface::DDPF_BUMPDUDV));

    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS_RESERVED1",
                         PyInt_FromLong(plDDSurface::DDSCAPS_RESERVED1));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS_ALPHA",
                         PyInt_FromLong(plDDSurface::DDSCAPS_ALPHA));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS_BACKBUFFER",
                         PyInt_FromLong(plDDSurface::DDSCAPS_BACKBUFFER));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS_COMPLEX",
                         PyInt_FromLong(plDDSurface::DDSCAPS_COMPLEX));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS_FLIP",
                         PyInt_FromLong(plDDSurface::DDSCAPS_FLIP));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS_FRONTBUFFER",
                         PyInt_FromLong(plDDSurface::DDSCAPS_FRONTBUFFER));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS_OFFSCREENPLAIN",
                         PyInt_FromLong(plDDSurface::DDSCAPS_OFFSCREENPLAIN));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS_OVERLAY",
                         PyInt_FromLong(plDDSurface::DDSCAPS_OVERLAY));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS_PALETTE",
                         PyInt_FromLong(plDDSurface::DDSCAPS_PALETTE));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS_PRIMARYSURFACE",
                         PyInt_FromLong(plDDSurface::DDSCAPS_PRIMARYSURFACE));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS_PRIMARYSURFACELEFT",
                         PyInt_FromLong(plDDSurface::DDSCAPS_PRIMARYSURFACELEFT));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS_SYSTEMMEMORY",
                         PyInt_FromLong(plDDSurface::DDSCAPS_SYSTEMMEMORY));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS_TEXTURE",
                         PyInt_FromLong(plDDSurface::DDSCAPS_TEXTURE));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS_3DDEVICE",
                         PyInt_FromLong(plDDSurface::DDSCAPS_3DDEVICE));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS_VIDEOMEMORY",
                         PyInt_FromLong(plDDSurface::DDSCAPS_VIDEOMEMORY));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS_VISIBLE",
                         PyInt_FromLong(plDDSurface::DDSCAPS_VISIBLE));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS_WRITEONLY",
                         PyInt_FromLong(plDDSurface::DDSCAPS_WRITEONLY));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS_ZBUFFER",
                         PyInt_FromLong(plDDSurface::DDSCAPS_ZBUFFER));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS_OWNDC",
                         PyInt_FromLong(plDDSurface::DDSCAPS_OWNDC));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS_LIVEVIDEO",
                         PyInt_FromLong(plDDSurface::DDSCAPS_LIVEVIDEO));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS_HWCODEC",
                         PyInt_FromLong(plDDSurface::DDSCAPS_HWCODEC));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS_MODEX",
                         PyInt_FromLong(plDDSurface::DDSCAPS_MODEX));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS_MIPMAP",
                         PyInt_FromLong(plDDSurface::DDSCAPS_MIPMAP));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS_RESERVED2",
                         PyInt_FromLong(plDDSurface::DDSCAPS_RESERVED2));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS_ALLOCONLOAD",
                         PyInt_FromLong(plDDSurface::DDSCAPS_ALLOCONLOAD));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS_VIDEOPORT",
                         PyInt_FromLong(plDDSurface::DDSCAPS_VIDEOPORT));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS_LOCALVIDMEM",
                         PyInt_FromLong(plDDSurface::DDSCAPS_LOCALVIDMEM));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS_NONLOCALVIDMEM",
                         PyInt_FromLong(plDDSurface::DDSCAPS_NONLOCALVIDMEM));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS_STANDARDVGAMODE",
                         PyInt_FromLong(plDDSurface::DDSCAPS_STANDARDVGAMODE));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS_OPTIMIZED",
                         PyInt_FromLong(plDDSurface::DDSCAPS_OPTIMIZED));

    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS2_HARDWAREDEINTERLACE",
                         PyInt_FromLong(plDDSurface::DDSCAPS2_HARDWAREDEINTERLACE));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS2_HINTDYNAMIC",
                         PyInt_FromLong(plDDSurface::DDSCAPS2_HINTDYNAMIC));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS2_HINTSTATIC",
                         PyInt_FromLong(plDDSurface::DDSCAPS2_HINTSTATIC));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS2_TEXTUREMANAGE",
                         PyInt_FromLong(plDDSurface::DDSCAPS2_TEXTUREMANAGE));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS2_RESERVED1",
                         PyInt_FromLong(plDDSurface::DDSCAPS2_RESERVED1));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS2_RESERVED2",
                         PyInt_FromLong(plDDSurface::DDSCAPS2_RESERVED2));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS2_OPAQUE",
                         PyInt_FromLong(plDDSurface::DDSCAPS2_OPAQUE));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS2_HINTALIASING",
                         PyInt_FromLong(plDDSurface::DDSCAPS2_HINTALIASING));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS2_CUBEMAP",
                         PyInt_FromLong(plDDSurface::DDSCAPS2_CUBEMAP));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS2_CUBEMAP_POSITIVEX",
                         PyInt_FromLong(plDDSurface::DDSCAPS2_CUBEMAP_POSITIVEX));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS2_CUBEMAP_NEGATIVEX",
                         PyInt_FromLong(plDDSurface::DDSCAPS2_CUBEMAP_NEGATIVEX));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS2_CUBEMAP_POSITIVEY",
                         PyInt_FromLong(plDDSurface::DDSCAPS2_CUBEMAP_POSITIVEY));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS2_CUBEMAP_NEGATIVEY",
                         PyInt_FromLong(plDDSurface::DDSCAPS2_CUBEMAP_NEGATIVEY));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS2_CUBEMAP_POSITIVEZ",
                         PyInt_FromLong(plDDSurface::DDSCAPS2_CUBEMAP_POSITIVEZ));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS2_CUBEMAP_NEGATIVEZ",
                         PyInt_FromLong(plDDSurface::DDSCAPS2_CUBEMAP_NEGATIVEZ));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS2_CUBEMAP_ALLFACES",
                         PyInt_FromLong(plDDSurface::DDSCAPS2_CUBEMAP_ALLFACES));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS2_MIPMAPSUBLEVEL",
                         PyInt_FromLong(plDDSurface::DDSCAPS2_MIPMAPSUBLEVEL));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS2_D3DTEXTUREMANAGE",
                         PyInt_FromLong(plDDSurface::DDSCAPS2_D3DTEXTUREMANAGE));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS2_DONOTPERSIST",
                         PyInt_FromLong(plDDSurface::DDSCAPS2_DONOTPERSIST));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS2_STEREOSURFACELEFT",
                         PyInt_FromLong(plDDSurface::DDSCAPS2_STEREOSURFACELEFT));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS2_VOLUME",
                         PyInt_FromLong(plDDSurface::DDSCAPS2_VOLUME));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS2_NOTUSERLOCKABLE",
                         PyInt_FromLong(plDDSurface::DDSCAPS2_NOTUSERLOCKABLE));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS2_POINTS",
                         PyInt_FromLong(plDDSurface::DDSCAPS2_POINTS));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS2_RTPATCHES",
                         PyInt_FromLong(plDDSurface::DDSCAPS2_RTPATCHES));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS2_NPATCHES",
                         PyInt_FromLong(plDDSurface::DDSCAPS2_NPATCHES));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS2_RESERVED3",
                         PyInt_FromLong(plDDSurface::DDSCAPS2_RESERVED3));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS2_DISCARDBACKBUFFER",
                         PyInt_FromLong(plDDSurface::DDSCAPS2_DISCARDBACKBUFFER));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS2_ENABLEALPHACHANNEL",
                         PyInt_FromLong(plDDSurface::DDSCAPS2_ENABLEALPHACHANNEL));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS2_EXTENDEDFORMATPRIMARY",
                         PyInt_FromLong(plDDSurface::DDSCAPS2_EXTENDEDFORMATPRIMARY));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS2_ADDITIONALPRIMARY",
                         PyInt_FromLong(plDDSurface::DDSCAPS2_ADDITIONALPRIMARY));

    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS3_MULTISAMPLE_MASK",
                         PyInt_FromLong(plDDSurface::DDSCAPS3_MULTISAMPLE_MASK));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS3_MULTISAMPLE_QUALITY_MASK",
                         PyInt_FromLong(plDDSurface::DDSCAPS3_MULTISAMPLE_QUALITY_MASK));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS3_MULTISAMPLE_QUALITY_SHIFT",
                         PyInt_FromLong(plDDSurface::DDSCAPS3_MULTISAMPLE_QUALITY_SHIFT));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS3_RESERVED1",
                         PyInt_FromLong(plDDSurface::DDSCAPS3_RESERVED1));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS3_RESERVED2",
                         PyInt_FromLong(plDDSurface::DDSCAPS3_RESERVED2));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS3_LIGHTWEIGHTMIPMAP",
                         PyInt_FromLong(plDDSurface::DDSCAPS3_LIGHTWEIGHTMIPMAP));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS3_AUTOGENMIPMAP",
                         PyInt_FromLong(plDDSurface::DDSCAPS3_AUTOGENMIPMAP));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS3_DMAP",
                         PyInt_FromLong(plDDSurface::DDSCAPS3_DMAP));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS3_CREATESHAREDRESOURCE",
                         PyInt_FromLong(plDDSurface::DDSCAPS3_CREATESHAREDRESOURCE));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS3_READONLYRESOURCE",
                         PyInt_FromLong(plDDSurface::DDSCAPS3_READONLYRESOURCE));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "DDSCAPS3_OPENSHAREDRESOURCE",
                         PyInt_FromLong(plDDSurface::DDSCAPS3_OPENSHAREDRESOURCE));

    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "FOURCC_DXT1",
                         PyInt_FromLong(plDDSurface::FOURCC_DXT1));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "FOURCC_DXT3",
                         PyInt_FromLong(plDDSurface::FOURCC_DXT3));
    PyDict_SetItemString(pyDDSurface_Type.tp_dict, "FOURCC_DXT5",
                         PyInt_FromLong(plDDSurface::FOURCC_DXT5));

    Py_INCREF(&pyDDSurface_Type);
    return (PyObject*)&pyDDSurface_Type;
}

PY_PLASMA_IFC_METHODS(DDSurface, plDDSurface)

}
