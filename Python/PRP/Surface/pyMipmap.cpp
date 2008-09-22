#include <Python.h>
#include <PRP/Surface/plMipmap.h>
#include "pyBitmap.h"
#include "../pyCreatable.h"
#include "../../Stream/pyStream.h"

extern "C" {

static int pyMipmap___init__(pyMipmap* self, PyObject* args, PyObject* kwds) {
    const char* name = "";
    int width, height, cfg, numLevels, compType, format;
    static char* kwlist[] = { "name", "width", "height", "cfg", "numLevels",
                              "compType", "format", NULL };

    if (PyArg_ParseTupleAndKeywords(args, kwds, "siiiiii", kwlist,
                                    &name, &width, &height, &cfg, &numLevels,
                                    &compType, &format)) {
        self->fThis->init(name);
        self->fThis->Create(width, height, cfg, numLevels, compType, format);
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

static PyObject* pyMipmap_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyMipmap_FromMipmap(plMipmap::Convert(cre->fThis));
}

static PyObject* pyMipmap_setConfig(pyMipmap* self, PyObject* args) {
    int cfg;
    if (!PyArg_ParseTuple(args, "i", &cfg)) {
        PyErr_SetString(PyExc_TypeError, "setConfig expects an int");
        return NULL;
    }
    self->fThis->setConfig(cfg);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyMipmap_readFrom(pyMipmap* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "readFromStream expects an hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "readFromStream expects an hsStream");
        return NULL;
    }
    self->fThis->readFromStream(stream->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyMipmap_writeTo(pyMipmap* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "writeToStream expects an hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "writeToStream expects an hsStream");
        return NULL;
    }
    self->fThis->writeToStream(stream->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyMipmap_readFromA(pyMipmap* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "readAlphaFromStream expects an hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "readAlphaFromStream expects an hsStream");
        return NULL;
    }
    self->fThis->readAlphaFromStream(stream->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyMipmap_writeToA(pyMipmap* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "writeAlphaToStream expects an hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "writeAlphaToStream expects an hsStream");
        return NULL;
    }
    self->fThis->writeAlphaToStream(stream->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyMipmap_getExt(pyMipmap* self) {
    return PyString_FromString(self->fThis->getSuggestedExt().cstr());
}

static PyObject* pyMipmap_getAExt(pyMipmap* self) {
    return PyString_FromString(self->fThis->getSuggestedAlphaExt().cstr());
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
    PyObject* data = PyString_FromStringAndSize((const char*)self->fThis->getLevelData(level),
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
    self->fThis->setImageData((const void*)data);
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
    self->fThis->setLevelData(level, (const void*)data);
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

static PyObject* pyMipmap_isImageJPEG(pyMipmap* self) {
    return PyBool_FromLong(self->fThis->isImageJPEG() ? 1 : 0);
}

static PyObject* pyMipmap_isAlphaJPEG(pyMipmap* self) {
    return PyBool_FromLong(self->fThis->isAlphaJPEG() ? 1 : 0);
}

static PyObject* pyMipmap_getWidth(pyMipmap* self, void*) {
    return PyInt_FromLong(self->fThis->getWidth());
}

static PyObject* pyMipmap_getHeight(pyMipmap* self, void*) {
    return PyInt_FromLong(self->fThis->getHeight());
}

static PyObject* pyMipmap_getImageData(pyMipmap* self, void*) {
    PyObject* data = PyString_FromStringAndSize((const char*)self->fThis->getImageData(),
                                                self->fThis->getImageSize());
    return data;
}

static PyObject* pyMipmap_getAlphaData(pyMipmap* self, void*) {
    if (self->fThis->getAlphaData() == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    PyObject* data = PyString_FromStringAndSize((const char*)self->fThis->getAlphaData(),
                                                self->fThis->getAlphaSize());
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

static int pyMipmap_setAlphaData(pyMipmap* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To set the image data, use the mipmap set methods");
    return -1;
}

static int pyMipmap_setNumLevels(pyMipmap* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To set the number of mip levels, you must re-create the mipmap object");
    return -1;
}

static PyMethodDef pyMipmap_Methods[] = {
    { "Convert", (PyCFunction)pyMipmap_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plMipmap" },
    { "setConfig", (PyCFunction)pyMipmap_setConfig, METH_VARARGS,
      "Params: config\n"
      "Set the configuration of the image data" },
    { "readFromStream", (PyCFunction)pyMipmap_readFrom, METH_VARARGS,
      "Params: stream\n"
      "Reads the mipmap from a file stream" },
    { "writeToStream", (PyCFunction)pyMipmap_writeTo, METH_VARARGS,
      "Params: stream\n"
      "Writes the mipmap to a file stream" },
    { "readAlphaFromStream\n", (PyCFunction)pyMipmap_readFromA, METH_VARARGS,
      "Params: stream\n"
      "Reads the mipmap's alpha data from a file stream" },
    { "writeAlphaToStream\n", (PyCFunction)pyMipmap_writeToA, METH_VARARGS,
      "Params: stream\n"
      "Writes the mipmap's alpha data to a file stream" },
    { "getSuggestedExt\n", (PyCFunction)pyMipmap_getExt, METH_NOARGS,
      "Returns the suggested file extension for exporting the image" },
    { "getSuggestedAlphaExt\n", (PyCFunction)pyMipmap_getAExt, METH_NOARGS,
      "Returns the suggested file extension for exporting the alpha data" },
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
    { "isImageJPEG", (PyCFunction)pyMipmap_isImageJPEG, METH_NOARGS,
      "Returns whether the imageData member is a JPEG stream" },
    { "isAlphaJPEG", (PyCFunction)pyMipmap_isAlphaJPEG, METH_NOARGS,
      "Returns whether the alphaData member is a JPEG stream" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyMipmap_GetSet[] = {
    { "width", (getter)pyMipmap_getWidth, (setter)pyMipmap_setWidth, NULL, NULL },
    { "height", (getter)pyMipmap_getHeight, (setter)pyMipmap_setHeight, NULL, NULL },
    { "imageData", (getter)pyMipmap_getImageData, (setter)pyMipmap_setImageData, NULL, NULL },
    { "alphaData", (getter)pyMipmap_getAlphaData, (setter)pyMipmap_setAlphaData, NULL, NULL },
    { "numLevels", (getter)pyMipmap_getNumLevels, (setter)pyMipmap_setNumLevels, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyMipmap_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
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
};

PyObject* Init_pyMipmap_Type() {
    pyMipmap_Type.tp_base = &pyBitmap_Type;
    if (PyType_Ready(&pyMipmap_Type) < 0)
        return NULL;

    // Config
    PyDict_SetItemString(pyMipmap_Type.tp_dict, "kColor8Config",
                         PyInt_FromLong(plMipmap::kColor8Config));
    PyDict_SetItemString(pyMipmap_Type.tp_dict, "kGray44Config",
                         PyInt_FromLong(plMipmap::kGray44Config));
    PyDict_SetItemString(pyMipmap_Type.tp_dict, "kGray4Config",
                         PyInt_FromLong(plMipmap::kGray4Config));
    PyDict_SetItemString(pyMipmap_Type.tp_dict, "kGray8Config",
                         PyInt_FromLong(plMipmap::kGray8Config));
    PyDict_SetItemString(pyMipmap_Type.tp_dict, "kRGB16Config",
                         PyInt_FromLong(plMipmap::kRGB16Config));
    PyDict_SetItemString(pyMipmap_Type.tp_dict, "kRGB32Config",
                         PyInt_FromLong(plMipmap::kRGB32Config));
    PyDict_SetItemString(pyMipmap_Type.tp_dict, "kARGB32Config",
                         PyInt_FromLong(plMipmap::kARGB32Config));

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
