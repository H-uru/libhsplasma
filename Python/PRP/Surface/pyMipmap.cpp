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

#include <PyPlasma.h>
#include <PRP/Surface/plMipmap.h>
#include "pyBitmap.h"
#include "PRP/pyCreatable.h"
#include "Stream/pyStream.h"

extern "C" {

static int pyMipmap___init__(pyMipmap* self, PyObject* args, PyObject* kwds) {
    const char* name = "";
    int width, height, numLevels, compType, format, dxtLevel;
    static char* kwlist[] = { "name", "width", "height", "numLevels",
                              "compType", "format", "dxtLevel", NULL };

    if (PyArg_ParseTupleAndKeywords(args, kwds, "siiiiii", kwlist,
                                    &name, &width, &height, &numLevels,
                                    &compType, &format, &dxtLevel)) {
        self->fThis->init(name);
        self->fThis->Create(width, height, numLevels, compType,
                            (plBitmap::ColorFormat)format, dxtLevel);
        return 0;
    } else if (PyErr_Clear(), PyArg_ParseTuple(args, "|s", &name)) {
        self->fThis->init(name);
        return 0;
    }

    PyErr_SetString(PyExc_TypeError, "__init__ expects an optional string, or a set of creation parameters");
    return -1;
}

static PyObject* pyMipmap_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyMipmap* self = (pyMipmap*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plMipmap();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyMipmap_readData(pyMipmap* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "readData expects an hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "readData expects an hsStream");
        return NULL;
    }
    self->fThis->readData(stream->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyMipmap_writeData(pyMipmap* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "writeData expects an hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "writeData expects an hsStream");
        return NULL;
    }
    self->fThis->writeData(stream->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyMipmap_getLevelWidth(pyMipmap* self, PyObject* args) {
    int level;
    if (!PyArg_ParseTuple(args, "i", &level)) {
        PyErr_SetString(PyExc_TypeError, "getLevelWidth expects an int");
        return NULL;
    }
    return PyInt_FromLong(self->fThis->getLevelWidth(level));
}

static PyObject* pyMipmap_getLevelHeight(pyMipmap* self, PyObject* args) {
    int level;
    if (!PyArg_ParseTuple(args, "i", &level)) {
        PyErr_SetString(PyExc_TypeError, "getLevelHeight expects an int");
        return NULL;
    }
    return PyInt_FromLong(self->fThis->getLevelHeight(level));
}

static PyObject* pyMipmap_getLevel(pyMipmap* self, PyObject* args) {
    int level;
    if (!PyArg_ParseTuple(args, "i", &level)) {
        PyErr_SetString(PyExc_TypeError, "getLevel expects an int");
        return NULL;
    }
    PyObject* data = PyBytes_FromStringAndSize((const char*)self->fThis->getLevelData(level),
                                               self->fThis->getLevelSize(level));
    return data;
}

static PyObject* pyMipmap_setRawImage(pyMipmap* self, PyObject* args) {
    const char* data;
    int dataSize;
    if (!PyArg_ParseTuple(args, "s#", &data, &dataSize)) {
        PyErr_SetString(PyExc_TypeError, "setRawImage expects a binary string");
        return NULL;
    }
    self->fThis->setImageData((const void*)data, dataSize);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyMipmap_setLevel(pyMipmap* self, PyObject* args) {
    const char* data;
    int dataSize, level;
    if (!PyArg_ParseTuple(args, "is#", &level, &data, &dataSize)) {
        PyErr_SetString(PyExc_TypeError, "setLevel expects int, binary string");
        return NULL;
    }
    self->fThis->setLevelData(level, (const void*)data, dataSize);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyMipmap_setImageJPEG(pyMipmap* self, PyObject* args) {
    const char* data;
    int dataSize;
    if (!PyArg_ParseTuple(args, "s#", &data, &dataSize)) {
        PyErr_SetString(PyExc_TypeError, "setImageJPEG expects a binary string");
        return NULL;
    }
    self->fThis->setImageJPEG((const void*)data, dataSize);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyMipmap_setAlphaJPEG(pyMipmap* self, PyObject* args) {
    const char* data;
    int dataSize;
    if (!PyArg_ParseTuple(args, "s#", &data, &dataSize)) {
        PyErr_SetString(PyExc_TypeError, "setAlphaJPEG expects a binary string");
        return NULL;
    }
    self->fThis->setAlphaJPEG((const void*)data, dataSize);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyMipmap_setColorData(pyMipmap* self, PyObject* args) {
    const char* data;
    int dataSize;
    if (!PyArg_ParseTuple(args, "s#", &data, &dataSize)) {
        PyErr_SetString(PyExc_TypeError, "setColorData expects a binary string");
        return NULL;
    }
    try {
        self->fThis->setColorData((const void*)data, dataSize);
    } catch (hsBadParamException& ex) {
        PyErr_SetString(PyExc_RuntimeError, ex.what());
        return NULL;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyMipmap_setAlphaData(pyMipmap* self, PyObject* args) {
    const char* data;
    int dataSize;
    if (!PyArg_ParseTuple(args, "s#", &data, &dataSize)) {
        PyErr_SetString(PyExc_TypeError, "setAlphaData expects a binary string");
        return NULL;
    }
    try {
        self->fThis->setAlphaData((const void*)data, dataSize);
    } catch (hsBadParamException& ex) {
        PyErr_SetString(PyExc_RuntimeError, ex.what());
        return NULL;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyMipmap_extractColorData(pyMipmap* self) {
    size_t dataSize = self->fThis->getWidth() * self->fThis->getHeight() * 3;
    char* data = new char[dataSize];
    self->fThis->extractColorData(data, dataSize);
    PyObject* buf = PyBytes_FromStringAndSize(data, dataSize);
    delete[] data;
    return buf;
}

static PyObject* pyMipmap_extractAlphaData(pyMipmap* self) {
    size_t dataSize = self->fThis->getWidth() * self->fThis->getHeight() * 1;
    char* data = new char[dataSize];
    self->fThis->extractAlphaData(data, dataSize);
    PyObject* buf = PyBytes_FromStringAndSize(data, dataSize);
    delete[] data;
    return buf;
}

static PyObject* pyMipmap_isImageJPEG(pyMipmap* self) {
    return PyBool_FromLong(self->fThis->isImageJPEG() ? 1 : 0);
}

static PyObject* pyMipmap_isAlphaJPEG(pyMipmap* self) {
    return PyBool_FromLong(self->fThis->isAlphaJPEG() ? 1 : 0);
}

static PyObject* pyMipmap_DecompressImage(pyMipmap* self, PyObject* args) {
    int level;
    if (!PyArg_ParseTuple(args, "i", &level)) {
        PyErr_SetString(PyExc_TypeError, "DecompressImage expects an int");
        return NULL;
    }
    size_t size = self->fThis->GetUncompressedSize(level);
    unsigned char* buf = new unsigned char[size];
    self->fThis->DecompressImage(level, buf, size);
    PyObject* img = PyBytes_FromStringAndSize((char*)buf, size);
    delete[] buf;
    return img;
}

static PyObject* pyMipmap_getWidth(pyMipmap* self, void*) {
    return PyInt_FromLong(self->fThis->getWidth());
}

static PyObject* pyMipmap_getHeight(pyMipmap* self, void*) {
    return PyInt_FromLong(self->fThis->getHeight());
}

static PyObject* pyMipmap_getImageData(pyMipmap* self, void*) {
    PyObject* data = PyBytes_FromStringAndSize((const char*)self->fThis->getImageData(),
                                               self->fThis->getTotalSize());
    return data;
}

static PyObject* pyMipmap_getNumLevels(pyMipmap* self, void*) {
    return PyInt_FromLong(self->fThis->getNumLevels());
}

static int pyMipmap_setWidth(pyMipmap* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To set the width, you must re-create the mipmap object");
    return -1;
}

static int pyMipmap_setHeight(pyMipmap* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To set the height, you must re-create the mipmap object");
    return -1;
}

static int pyMipmap_setImageData(pyMipmap* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To set the image data, use the mipmap set methods");
    return -1;
}

static int pyMipmap_setNumLevels(pyMipmap* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To set the number of mip levels, you must re-create the mipmap object");
    return -1;
}

static PyMethodDef pyMipmap_Methods[] = {
    { "readData", (PyCFunction)pyMipmap_readData, METH_VARARGS,
      "Params: stream\n"
      "Reads a plMipmap from a stream, exluding the plKey" },
    { "writeData", (PyCFunction)pyMipmap_writeData, METH_VARARGS,
      "Params: stream\n"
      "Writes a plMipmap to a stream, exluding the plKey" },
    { "getLevelWidth", (PyCFunction)pyMipmap_getLevelWidth, METH_VARARGS,
      "Params: level\n"
      "Get the width of a specified mip level" },
    { "getLevelHeight", (PyCFunction)pyMipmap_getLevelHeight, METH_VARARGS,
      "Params: level\n"
      "Get the height of a specified mip level" },
    { "getLevel", (PyCFunction)pyMipmap_getLevel, METH_VARARGS,
      "Params: level\n"
      "Get the image data buffer for a specified mip level" },
    { "setRawImage", (PyCFunction)pyMipmap_setRawImage, METH_VARARGS,
      "Params: data\n"
      "Set the raw full image data (not for JPEG or RLE encoding)" },
    { "setLevel", (PyCFunction)pyMipmap_setLevel, METH_VARARGS,
      "Params: level, data\n"
      "Set the image data for a specified mip level" },
    { "setImageJPEG", (PyCFunction)pyMipmap_setImageJPEG, METH_VARARGS,
      "Params: jpegData\n"
      "Set the image data as a JPEG stream" },
    { "setAlphaJPEG", (PyCFunction)pyMipmap_setAlphaJPEG, METH_VARARGS,
      "Params: jpegData\n"
      "Set the alpha data as a JPEG stream" },
    { "setColorData", (PyCFunction)pyMipmap_setColorData, METH_VARARGS,
      "Params: buffer\n"
      "Set the RGB color data for a JPEG mipmap" },
    { "setAlphaData", (PyCFunction)pyMipmap_setAlphaData, METH_VARARGS,
      "Params: buffer\n"
      "Set the alpha data for a JPEG mipmap" },
    { "extractColorData", (PyCFunction)pyMipmap_extractColorData, METH_NOARGS,
      "Extract an RGB color buffer from a JPEG mipmap" },
    { "extractAlphaData", (PyCFunction)pyMipmap_extractAlphaData, METH_NOARGS,
      "Extract an alpha intensity buffer from a JPEG mipmap" },
    { "isImageJPEG", (PyCFunction)pyMipmap_isImageJPEG, METH_NOARGS,
      "Returns whether the imageData member is a JPEG stream" },
    { "isAlphaJPEG", (PyCFunction)pyMipmap_isAlphaJPEG, METH_NOARGS,
      "Returns whether the alphaData member is a JPEG stream" },
    { "DecompressImage", (PyCFunction)pyMipmap_DecompressImage, METH_VARARGS,
      "Params: level\n"
      "Deompresses the specified mip level and returns the uncompressed RGBA buffer" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyMipmap_GetSet[] = {
    { "width", (getter)pyMipmap_getWidth, (setter)pyMipmap_setWidth, NULL, NULL },
    { "height", (getter)pyMipmap_getHeight, (setter)pyMipmap_setHeight, NULL, NULL },
    { "imageData", (getter)pyMipmap_getImageData, (setter)pyMipmap_setImageData, NULL, NULL },
    { "numLevels", (getter)pyMipmap_getNumLevels, (setter)pyMipmap_setNumLevels, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyMipmap_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plMipmap",                /* tp_name */
    sizeof(pyMipmap),                   /* tp_basicsize */
    0,                                  /* tp_itemsize */

    NULL,                               /* tp_dealloc */
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
    "plMipmap wrapper",                 /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyMipmap_Methods,                   /* tp_methods */
    NULL,                               /* tp_members */
    pyMipmap_GetSet,                    /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyMipmap___init__,        /* tp_init */
    NULL,                               /* tp_alloc */
    pyMipmap_new,                       /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */

    NULL,                               /* tp_del */
    TP_VERSION_TAG_INIT                 /* tp_version_tag */
};

PyObject* Init_pyMipmap_Type() {
    pyMipmap_Type.tp_base = &pyBitmap_Type;
    if (PyType_Ready(&pyMipmap_Type) < 0)
        return NULL;

    Py_INCREF(&pyMipmap_Type);
    return (PyObject*)&pyMipmap_Type;
}

int pyMipmap_Check(PyObject* obj) {
    if (obj->ob_type == &pyMipmap_Type
        || PyType_IsSubtype(obj->ob_type, &pyMipmap_Type))
        return 1;
    return 0;
}

PyObject* pyMipmap_FromMipmap(class plMipmap* img) {
    if (img == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyMipmap* pybmp = PyObject_New(pyMipmap, &pyMipmap_Type);
    pybmp->fThis = img;
    pybmp->fPyOwned = false;
    return (PyObject*)pybmp;
}

}
