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
#include "Stream/pyStream.h"
#include "PRP/Surface/pyBitmap.h"

extern "C" {

static void pyDDSurface_dealloc(pyDDSurface* self) {
    if (self->fPyOwned)
        delete self->fThis;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static int pyDDSurface___init__(pyDDSurface* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}


static PyObject* pyDDSurface_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyDDSurface* self = (pyDDSurface*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plDDSurface();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyDDSurface_read(pyDDSurface* self, PyObject* args) {
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
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyDDSurface_write(pyDDSurface* self, PyObject* args) {
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
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyDDSurface_setFromMipmap(pyDDSurface* self, PyObject* args) {
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
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyDDSurface_createMipmap(pyDDSurface* self) {
    plMipmap* tex = self->fThis->createMipmap();
    return pyMipmap_FromMipmap(tex);
}

static PyObject* pyDDSurface_calcBufferSize(pyDDSurface* self, PyObject* args) {
    int width, height;
    if (!PyArg_ParseTuple(args, "ii", &width, &height)) {
        PyErr_SetString(PyExc_TypeError, "calcBufferSize expects int, int");
        return NULL;
    }
    size_t bufSize = self->fThis->calcBufferSize(width, height);
    return PyInt_FromLong((long)bufSize);
}

static PyObject* pyDDSurface_calcNumLevels(pyDDSurface* self) {
    size_t levels = self->fThis->calcNumLevels();
    return PyInt_FromLong((long)levels);
}

static PyObject* pyDDSurface_calcTotalSize(pyDDSurface* self) {
    size_t totSize = self->fThis->calcTotalBufferSize();
    return PyInt_FromLong((long)totSize);
}

static PyObject* pyDDSurface_getFlags(pyDDSurface* self, void*) {
    return PyInt_FromLong(self->fThis->fFlags);
}

static PyObject* pyDDSurface_getHeight(pyDDSurface* self, void*) {
    return PyInt_FromLong(self->fThis->fHeight);
}

static PyObject* pyDDSurface_getWidth(pyDDSurface* self, void*) {
    return PyInt_FromLong(self->fThis->fWidth);
}

static PyObject* pyDDSurface_getPitch(pyDDSurface* self, void*) {
    return PyInt_FromLong(self->fThis->fPitch);
}

static PyObject* pyDDSurface_getDepth(pyDDSurface* self, void*) {
    return PyInt_FromLong(self->fThis->fDepth);
}

static PyObject* pyDDSurface_getMipCount(pyDDSurface* self, void*) {
    return PyInt_FromLong(self->fThis->fMipmapCount);
}

static PyObject* pyDDSurface_getAlphaDepth(pyDDSurface* self, void*) {
    return PyInt_FromLong(self->fThis->fAlphaDepth);
}

static PyObject* pyDDSurface_getCKDestOverlay(pyDDSurface* self, void*) {
    return Py_BuildValue("ii", self->fThis->fCKDestOverlay.fColorSpaceLow,
                               self->fThis->fCKDestOverlay.fColorSpaceHigh);
}

static PyObject* pyDDSurface_getCKDestBlt(pyDDSurface* self, void*) {
    return Py_BuildValue("ii", self->fThis->fCKDestBlt.fColorSpaceLow,
                               self->fThis->fCKDestBlt.fColorSpaceHigh);
}

static PyObject* pyDDSurface_getCKSrcOverlay(pyDDSurface* self, void*) {
    return Py_BuildValue("ii", self->fThis->fCKSrcOverlay.fColorSpaceLow,
                               self->fThis->fCKSrcOverlay.fColorSpaceHigh);
}

static PyObject* pyDDSurface_getCKSrcBlt(pyDDSurface* self, void*) {
    return Py_BuildValue("ii", self->fThis->fCKSrcBlt.fColorSpaceLow,
                               self->fThis->fCKSrcBlt.fColorSpaceHigh);
}

static PyObject* pyDDSurface_getFVF(pyDDSurface* self, void*) {
    return PyInt_FromLong(self->fThis->fFVF);
}

static PyObject* pyDDSurface_getCaps(pyDDSurface* self, void*) {
    return PyInt_FromLong(self->fThis->fCaps);
}

static PyObject* pyDDSurface_getCaps2(pyDDSurface* self, void*) {
    return PyInt_FromLong(self->fThis->fCaps2);
}

static PyObject* pyDDSurface_getCaps3(pyDDSurface* self, void*) {
    return PyInt_FromLong(self->fThis->fCaps3);
}

static PyObject* pyDDSurface_getCaps4(pyDDSurface* self, void*) {
    return PyInt_FromLong(self->fThis->fCaps4);
}

static PyObject* pyDDSurface_getTextureStage(pyDDSurface* self, void*) {
    return PyInt_FromLong(self->fThis->fTextureStage);
}

static PyObject* pyDDSurface_getPF_Flags(pyDDSurface* self, void*) {
    return PyInt_FromLong(self->fThis->fPixelFormat.fFlags);
}

static PyObject* pyDDSurface_getPF_FourCC(pyDDSurface* self, void*) {
    return PyInt_FromLong(self->fThis->fPixelFormat.fFourCC);
}

static PyObject* pyDDSurface_getPF_BitDepth(pyDDSurface* self, void*) {
    return PyInt_FromLong(self->fThis->fPixelFormat.fBitDepth);
}

static PyObject* pyDDSurface_getPF_RBitMask(pyDDSurface* self, void*) {
    return PyInt_FromLong(self->fThis->fPixelFormat.fRBitMask);
}

static PyObject* pyDDSurface_getPF_GBitMask(pyDDSurface* self, void*) {
    return PyInt_FromLong(self->fThis->fPixelFormat.fGBitMask);
}

static PyObject* pyDDSurface_getPF_MSCaps(pyDDSurface* self, void*) {
    return Py_BuildValue("ii", self->fThis->fPixelFormat.fMultiSampleCaps.fFlipMSTypes,
                               self->fThis->fPixelFormat.fMultiSampleCaps.fBltMSTypes);
}

static PyObject* pyDDSurface_getPF_BBitMask(pyDDSurface* self, void*) {
    return PyInt_FromLong(self->fThis->fPixelFormat.fBBitMask);
}

static PyObject* pyDDSurface_getPF_ABitMask(pyDDSurface* self, void*) {
    return PyInt_FromLong(self->fThis->fPixelFormat.fAlphaBitMask);
}

static PyObject* pyDDSurface_getData(pyDDSurface* self, void*) {
    PyObject* data = PyBytes_FromStringAndSize((const char*)self->fThis->getData(),
                                               self->fThis->getDataSize());
    return data;
}

static int pyDDSurface_setFlags(pyDDSurface* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "flags must be an int");
        return -1;
    }
    self->fThis->fFlags = PyInt_AsLong(value);
    return 0;
}

static int pyDDSurface_setHeight(pyDDSurface* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "height must be an int");
        return -1;
    }
    self->fThis->fHeight = PyInt_AsLong(value);
    return 0;
}

static int pyDDSurface_setWidth(pyDDSurface* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "width must be an int");
        return -1;
    }
    self->fThis->fWidth = PyInt_AsLong(value);
    return 0;
}

static int pyDDSurface_setPitch(pyDDSurface* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "value must be an int");
        return -1;
    }
    self->fThis->fWidth = PyInt_AsLong(value);
    return 0;
}

static int pyDDSurface_setDepth(pyDDSurface* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "value must be an int");
        return -1;
    }
    self->fThis->fDepth = PyInt_AsLong(value);
    return 0;
}

static int pyDDSurface_setMipCount(pyDDSurface* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "value must be an int");
        return -1;
    }
    self->fThis->fMipmapCount = PyInt_AsLong(value);
    return 0;
}

static int pyDDSurface_setAlphaDepth(pyDDSurface* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "alphaDepth must be an int");
        return -1;
    }
    self->fThis->fAlphaDepth = PyInt_AsLong(value);
    return 0;
}

static int pyDDSurface_setCKDestOverlay(pyDDSurface* self, PyObject* value, void*) {
    if (value == NULL || !PyTuple_Check(value) || PyTuple_GET_SIZE(value) != 2) {
        PyErr_SetString(PyExc_TypeError, "ckDestOverlay should be a tuple (int, int)");
        return -1;
    }
    PyObject* low = PyTuple_GET_ITEM(value, 0);
    PyObject* hi = PyTuple_GET_ITEM(value, 1);
    if (!PyInt_Check(low) || !PyInt_Check(hi)) {
        PyErr_SetString(PyExc_TypeError, "ckDestOverlay should be a tuple (int, int)");
        return -1;
    }
    self->fThis->fCKDestOverlay.fColorSpaceLow = PyInt_AsLong(low);
    self->fThis->fCKDestOverlay.fColorSpaceHigh = PyInt_AsLong(hi);
    return 0;
}

static int pyDDSurface_setCKDestBlt(pyDDSurface* self, PyObject* value, void*) {
    if (value == NULL || !PyTuple_Check(value) || PyTuple_GET_SIZE(value) != 2) {
        PyErr_SetString(PyExc_TypeError, "ckDestBlt should be a tuple (int, int)");
        return -1;
    }
    PyObject* low = PyTuple_GET_ITEM(value, 0);
    PyObject* hi = PyTuple_GET_ITEM(value, 1);
    if (!PyInt_Check(low) || !PyInt_Check(hi)) {
        PyErr_SetString(PyExc_TypeError, "ckDestBlt should be a tuple (int, int)");
        return -1;
    }
    self->fThis->fCKDestBlt.fColorSpaceLow = PyInt_AsLong(low);
    self->fThis->fCKDestBlt.fColorSpaceHigh = PyInt_AsLong(hi);
    return 0;
}

static int pyDDSurface_setCKSrcOverlay(pyDDSurface* self, PyObject* value, void*) {
    if (value == NULL || !PyTuple_Check(value) || PyTuple_GET_SIZE(value) != 2) {
        PyErr_SetString(PyExc_TypeError, "ckSrcOverlay should be a tuple (int, int)");
        return -1;
    }
    PyObject* low = PyTuple_GET_ITEM(value, 0);
    PyObject* hi = PyTuple_GET_ITEM(value, 1);
    if (!PyInt_Check(low) || !PyInt_Check(hi)) {
        PyErr_SetString(PyExc_TypeError, "ckSrcOverlay should be a tuple (int, int)");
        return -1;
    }
    self->fThis->fCKSrcOverlay.fColorSpaceLow = PyInt_AsLong(low);
    self->fThis->fCKSrcOverlay.fColorSpaceHigh = PyInt_AsLong(hi);
    return 0;
}

static int pyDDSurface_setCKSrcBlt(pyDDSurface* self, PyObject* value, void*) {
    if (value == NULL || !PyTuple_Check(value) || PyTuple_GET_SIZE(value) != 2) {
        PyErr_SetString(PyExc_TypeError, "ckSrcBlt should be a tuple (int, int)");
        return -1;
    }
    PyObject* low = PyTuple_GET_ITEM(value, 0);
    PyObject* hi = PyTuple_GET_ITEM(value, 1);
    if (!PyInt_Check(low) || !PyInt_Check(hi)) {
        PyErr_SetString(PyExc_TypeError, "ckSrcBlt should be a tuple (int, int)");
        return -1;
    }
    self->fThis->fCKSrcBlt.fColorSpaceLow = PyInt_AsLong(low);
    self->fThis->fCKSrcBlt.fColorSpaceHigh = PyInt_AsLong(hi);
    return 0;
}

static int pyDDSurface_setFVF(pyDDSurface* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "fvf must be an int");
        return -1;
    }
    self->fThis->fFVF = PyInt_AsLong(value);
    return 0;
}

static int pyDDSurface_setCaps(pyDDSurface* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "caps must be an int");
        return -1;
    }
    self->fThis->fCaps = PyInt_AsLong(value);
    return 0;
}

static int pyDDSurface_setCaps2(pyDDSurface* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "caps2 must be an int");
        return -1;
    }
    self->fThis->fCaps2 = PyInt_AsLong(value);
    return 0;
}

static int pyDDSurface_setCaps3(pyDDSurface* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "caps3 must be an int");
        return -1;
    }
    self->fThis->fCaps3 = PyInt_AsLong(value);
    return 0;
}

static int pyDDSurface_setCaps4(pyDDSurface* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "caps4 must be an int");
        return -1;
    }
    self->fThis->fCaps4 = PyInt_AsLong(value);
    return 0;
}

static int pyDDSurface_setTextureStage(pyDDSurface* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "textureStage must be an int");
        return -1;
    }
    self->fThis->fTextureStage = PyInt_AsLong(value);
    return 0;
}

static int pyDDSurface_setPF_Flags(pyDDSurface* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "pf_flags must be an int");
        return -1;
    }
    self->fThis->fPixelFormat.fFlags = PyInt_AsLong(value);
    return 0;
}

static int pyDDSurface_setPF_FourCC(pyDDSurface* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "pf_fourCC must be an int");
        return -1;
    }
    self->fThis->fPixelFormat.fFourCC = PyInt_AsLong(value);
    return 0;
}

static int pyDDSurface_setPF_BitDepth(pyDDSurface* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "value must be an int");
        return -1;
    }
    self->fThis->fPixelFormat.fBitDepth = PyInt_AsLong(value);
    return 0;
}

static int pyDDSurface_setPF_RBitMask(pyDDSurface* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "value must be an int");
        return -1;
    }
    self->fThis->fPixelFormat.fRBitMask = PyInt_AsLong(value);
    return 0;
}

static int pyDDSurface_setPF_GBitMask(pyDDSurface* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "value must be an int");
        return -1;
    }
    self->fThis->fPixelFormat.fGBitMask = PyInt_AsLong(value);
    return 0;
}

static int pyDDSurface_setPF_MSCaps(pyDDSurface* self, PyObject* value, void*) {
    if (value == NULL || !PyTuple_Check(value) || PyTuple_GET_SIZE(value) != 2) {
        PyErr_SetString(PyExc_TypeError, "pf_multisampleCaps should be a tuple (int, int)");
        return -1;
    }
    PyObject* flip = PyTuple_GET_ITEM(value, 0);
    PyObject* blt = PyTuple_GET_ITEM(value, 1);
    if (!PyInt_Check(flip) || !PyInt_Check(blt)) {
        PyErr_SetString(PyExc_TypeError, "pf_multisampleCaps should be a tuple (int, int)");
        return -1;
    }
    self->fThis->fPixelFormat.fMultiSampleCaps.fFlipMSTypes = PyInt_AsLong(flip);
    self->fThis->fPixelFormat.fMultiSampleCaps.fBltMSTypes = PyInt_AsLong(blt);
    return 0;
}

static int pyDDSurface_setPF_BBitMask(pyDDSurface* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "value must be an int");
        return -1;
    }
    self->fThis->fPixelFormat.fBBitMask = PyInt_AsLong(value);
    return 0;
}

static int pyDDSurface_setPF_ABitMask(pyDDSurface* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "value must be an int");
        return -1;
    }
    self->fThis->fPixelFormat.fAlphaBitMask = PyInt_AsLong(value);
    return 0;
}

static int pyDDSurface_setData(pyDDSurface* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
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

static PyMethodDef pyDDSurface_Methods[] = {
    { "read", (PyCFunction)pyDDSurface_read, METH_VARARGS,
      "Params: stream\n"
      "Reads a DDS file from a stream" },
    { "write", (PyCFunction)pyDDSurface_write, METH_VARARGS,
      "Params: stream\n"
      "Writes a DDS file to a stream" },
    { "setFromMipmap", (PyCFunction)pyDDSurface_setFromMipmap, METH_VARARGS,
      "Params: mipmap\n"
      "Sets the fields of this plDDSurface from the supplied plMipmap" },
    { "createMipmap", (PyCFunction)pyDDSurface_createMipmap, METH_NOARGS,
      "Create a new plMipmap from this plDDSurface" },
    { "calcBufferSize", (PyCFunction)pyDDSurface_calcBufferSize, METH_VARARGS,
      "Params: width, height\n"
      "Calculates the size of an buffer within the surface" },
    { "calcNumLevels", (PyCFunction)pyDDSurface_calcNumLevels, METH_NOARGS,
      "Calculates the total number of mipmap levels for one surface buffer" },
    { "calcTotalBufferSize", (PyCFunction)pyDDSurface_calcTotalSize, METH_NOARGS,
      "Calculates the total size needed to store all buffers in this surface" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyDDSurface_GetSet[] = {
    { _pycs("flags"), (getter)pyDDSurface_getFlags,
        (setter)pyDDSurface_setFlags, NULL, NULL },
    { _pycs("height"), (getter)pyDDSurface_getHeight,
        (setter)pyDDSurface_setHeight, NULL, NULL },
    { _pycs("width"), (getter)pyDDSurface_getWidth, (setter)pyDDSurface_setWidth,
        NULL, NULL },
    { _pycs("pitch"), (getter)pyDDSurface_getPitch, (setter)pyDDSurface_setPitch,
        NULL, NULL },
    { _pycs("linearSize"), (getter)pyDDSurface_getPitch,
        (setter)pyDDSurface_setPitch, NULL, NULL },
    { _pycs("backBufferCount"), (getter)pyDDSurface_getDepth,
        (setter)pyDDSurface_setDepth, NULL, NULL },
    { _pycs("depth"), (getter)pyDDSurface_getDepth, (setter)pyDDSurface_setDepth,
        NULL, NULL },
    { _pycs("mipmapCount"), (getter)pyDDSurface_getMipCount,
        (setter)pyDDSurface_setMipCount, NULL, NULL },
    { _pycs("zbufferBitDepth"), (getter)pyDDSurface_getMipCount,
        (setter)pyDDSurface_setMipCount, NULL, NULL },
    { _pycs("refreshRate"), (getter)pyDDSurface_getMipCount,
        (setter)pyDDSurface_setMipCount, NULL, NULL },
    { _pycs("srcVBHandle"), (getter)pyDDSurface_getMipCount,
        (setter)pyDDSurface_setMipCount, NULL, NULL },
    { _pycs("alphaDepth"), (getter)pyDDSurface_getAlphaDepth,
        (setter)pyDDSurface_setAlphaDepth, NULL, NULL },
    { _pycs("ckDestOverlay"), (getter)pyDDSurface_getCKDestOverlay,
        (setter)pyDDSurface_setCKDestOverlay, NULL, NULL },
    { _pycs("ckDestBlt"), (getter)pyDDSurface_getCKDestBlt,
        (setter)pyDDSurface_setCKDestBlt, NULL, NULL },
    { _pycs("ckSrcOverlay"), (getter)pyDDSurface_getCKSrcOverlay,
        (setter)pyDDSurface_setCKSrcOverlay, NULL, NULL },
    { _pycs("ckSrcBlt"), (getter)pyDDSurface_getCKSrcBlt,
        (setter)pyDDSurface_setCKSrcBlt, NULL, NULL },
    { _pycs("fvf"), (getter)pyDDSurface_getFVF, (setter)pyDDSurface_setFVF,
        NULL, NULL },
    { _pycs("caps"), (getter)pyDDSurface_getCaps, (setter)pyDDSurface_setCaps,
        NULL, NULL },
    { _pycs("caps2"), (getter)pyDDSurface_getCaps2, (setter)pyDDSurface_setCaps2,
        NULL, NULL },
    { _pycs("caps3"), (getter)pyDDSurface_getCaps3, (setter)pyDDSurface_setCaps3,
        NULL, NULL },
    { _pycs("caps4"), (getter)pyDDSurface_getCaps4, (setter)pyDDSurface_setCaps4,
        NULL, NULL },
    { _pycs("textureStage"), (getter)pyDDSurface_getTextureStage,
        (setter)pyDDSurface_setTextureStage, NULL, NULL },
    { _pycs("pf_flags"), (getter)pyDDSurface_getPF_Flags,
        (setter)pyDDSurface_setPF_Flags, NULL, NULL },
    { _pycs("pf_fourCC"), (getter)pyDDSurface_getPF_FourCC,
        (setter)pyDDSurface_setPF_FourCC, NULL, NULL },
    { _pycs("pf_bitDepth"), (getter)pyDDSurface_getPF_BitDepth,
        (setter)pyDDSurface_setPF_BitDepth, NULL, NULL },
    { _pycs("pf_bitCount"), (getter)pyDDSurface_getPF_BitDepth,
        (setter)pyDDSurface_setPF_BitDepth, NULL, NULL },
    { _pycs("pf_RBitMask"), (getter)pyDDSurface_getPF_RBitMask,
        (setter)pyDDSurface_setPF_RBitMask, NULL, NULL },
    { _pycs("pf_YBitMask"), (getter)pyDDSurface_getPF_RBitMask,
        (setter)pyDDSurface_setPF_RBitMask, NULL, NULL },
    { _pycs("pf_stencilBitDepth"), (getter)pyDDSurface_getPF_RBitMask,
        (setter)pyDDSurface_setPF_RBitMask, NULL, NULL },
    { _pycs("pf_luminanceBitMask"), (getter)pyDDSurface_getPF_RBitMask,
        (setter)pyDDSurface_setPF_RBitMask, NULL, NULL },
    { _pycs("pf_bumpDu"), (getter)pyDDSurface_getPF_RBitMask,
        (setter)pyDDSurface_setPF_RBitMask, NULL, NULL },
    { _pycs("pf_operations"), (getter)pyDDSurface_getPF_RBitMask,
        (setter)pyDDSurface_setPF_RBitMask, NULL, NULL },
    { _pycs("pf_GBitMask"), (getter)pyDDSurface_getPF_GBitMask,
        (setter)pyDDSurface_setPF_GBitMask, NULL, NULL },
    { _pycs("pf_UBitMask"), (getter)pyDDSurface_getPF_GBitMask,
        (setter)pyDDSurface_setPF_GBitMask, NULL, NULL },
    { _pycs("pf_ZBitMask"), (getter)pyDDSurface_getPF_GBitMask,
        (setter)pyDDSurface_setPF_GBitMask, NULL, NULL },
    { _pycs("pf_bumpDvBitMask"), (getter)pyDDSurface_getPF_GBitMask,
        (setter)pyDDSurface_setPF_GBitMask, NULL, NULL },
    { _pycs("pf_multiSampleCaps"), (getter)pyDDSurface_getPF_MSCaps,
        (setter)pyDDSurface_setPF_MSCaps, NULL, NULL },
    { _pycs("pf_BBitMask"), (getter)pyDDSurface_getPF_BBitMask,
        (setter)pyDDSurface_setPF_BBitMask, NULL, NULL },
    { _pycs("pf_VBitMask"), (getter)pyDDSurface_getPF_BBitMask,
        (setter)pyDDSurface_setPF_BBitMask, NULL, NULL },
    { _pycs("pf_stencilBitMask"), (getter)pyDDSurface_getPF_BBitMask,
        (setter)pyDDSurface_setPF_BBitMask, NULL, NULL },
    { _pycs("pf_bumpLuminanceBitMask"), (getter)pyDDSurface_getPF_BBitMask,
        (setter)pyDDSurface_setPF_BBitMask, NULL, NULL },
    { _pycs("pf_alphaBitMask"), (getter)pyDDSurface_getPF_ABitMask,
        (setter)pyDDSurface_setPF_ABitMask, NULL, NULL },
    { _pycs("pf_colorZBitMask"), (getter)pyDDSurface_getPF_ABitMask,
        (setter)pyDDSurface_setPF_ABitMask, NULL, NULL },
    { _pycs("data"), (getter)pyDDSurface_getData, (setter)pyDDSurface_setData,
        NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyDDSurface_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plDDSurface",           /* tp_name */
    sizeof(pyDDSurface),                /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pyDDSurface_dealloc,    /* tp_dealloc */
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

    (initproc)pyDDSurface___init__,     /* tp_init */
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
