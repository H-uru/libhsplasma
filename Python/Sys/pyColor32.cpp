#include <Python.h>
#include <Sys/hsColor.h>
#include "pyColor.h"
#include "../Stream/pyStream.h"

extern "C" {

static void pyColor32_dealloc(pyColor32* self) {
    delete self->fThis;
    self->ob_type->tp_free((PyObject*)self);
}

static PyObject* pyColor32_set(pyColor32* self, PyObject* args, PyObject* kwds) {
    int red = 0, green = 0, blue = 0, alpha = 255, color = 0xFF000000;

    static char* kwlist1[] = { "red", "green", "blue", "alpha", NULL };
    static char* kwlist2[] = { "color", NULL };

    if (PyArg_ParseTupleAndKeywords(args, kwds, "I", kwlist2, &color)) {
        self->fThis->color = color;
    } else if (PyArg_ParseTupleAndKeywords(args, kwds, "|iiii", kwlist1,
                                           &red, &green, &blue, &alpha)) {
        PyErr_Clear();
        self->fThis->r = red;
        self->fThis->g = green;
        self->fThis->b = blue;
        self->fThis->a = alpha;
    } else {
        PyErr_SetString(PyExc_TypeError, "set expects 0-4 ints");
        return NULL;
    }

    Py_INCREF(Py_None);
    return Py_None;
}

static int pyColor32___init__(pyColor32* self, PyObject* args, PyObject* kwds) {
    PyObject* retn = pyColor32_set(self, args, kwds);
    if (retn == NULL)
        return -1;
    Py_DECREF(retn);
    return 0;
}

static PyObject* pyColor32_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyColor32* self = (pyColor32*)type->tp_alloc(type, 0);
    if (self != NULL)
        self->fThis = new hsColor32();
    return (PyObject*)self;
}

static PyObject* pyColor32_Repr(pyColor32* self) {
    plString repr = plString::Format("hsColor32(%u, %u, %u, %u)",
        self->fThis->r, self->fThis->g, self->fThis->b, self->fThis->a);
    return PyString_FromString(repr.cstr());
}

static PyObject* pyColor32_read32(pyColor32* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "read32 expects a hsStream");
        return NULL;
    }
    Py_INCREF(stream);
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "read32 expects a hsStream");
        return NULL;
    }
    self->fThis->read32(stream->fThis);
    Py_DECREF(stream);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyColor32_write32(pyColor32* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "write32 expects a hsStream");
        return NULL;
    }
    Py_INCREF(stream);
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "write32 expects a hsStream");
        return NULL;
    }
    self->fThis->write32(stream->fThis);
    Py_DECREF(stream);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyColor32_readRGBA8(pyColor32* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "readRGBA8 expects a hsStream");
        return NULL;
    }
    Py_INCREF(stream);
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "readRGBA8 expects a hsStream");
        return NULL;
    }
    self->fThis->readRGBA8(stream->fThis);
    Py_DECREF(stream);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyColor32_writeRGBA8(pyColor32* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "writeRGBA8 expects a hsStream");
        return NULL;
    }
    Py_INCREF(stream);
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "writeRGBA8 expects a hsStream");
        return NULL;
    }
    self->fThis->writeRGBA8(stream->fThis);
    Py_DECREF(stream);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyColor32_readRGB8(pyColor32* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "readRGB8 expects a hsStream");
        return NULL;
    }
    Py_INCREF(stream);
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "readRGB8 expects a hsStream");
        return NULL;
    }
    self->fThis->readRGB8(stream->fThis);
    Py_DECREF(stream);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyColor32_writeRGB8(pyColor32* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "writeRGB8 expects a hsStream");
        return NULL;
    }
    Py_INCREF(stream);
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "writeRGB8 expects a hsStream");
        return NULL;
    }
    self->fThis->writeRGB8(stream->fThis);
    Py_DECREF(stream);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyColor32_getRed(pyColor32* self, void* closure) {
    return PyInt_FromLong(self->fThis->r);
}

static PyObject* pyColor32_getGreen(pyColor32* self, void* closure) {
    return PyInt_FromLong(self->fThis->g);
}

static PyObject* pyColor32_getBlue(pyColor32* self, void* closure) {
    return PyInt_FromLong(self->fThis->b);
}

static PyObject* pyColor32_getAlpha(pyColor32* self, void* closure) {
    return PyInt_FromLong(self->fThis->a);
}

static PyObject* pyColor32_getColor(pyColor32* self, void* closure) {
    return PyInt_FromLong(self->fThis->color);
}

static int pyColor32_setRed(pyColor32* self, PyObject* value, void* closure) {
    if (!PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "red should be an int");
        return -1;
    }
    self->fThis->r = PyInt_AsLong(value);
    return 0;
}

static int pyColor32_setGreen(pyColor32* self, PyObject* value, void* closure) {
    if (!PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "green should be an int");
        return -1;
    }
    self->fThis->g = PyInt_AsLong(value);
    return 0;
}

static int pyColor32_setBlue(pyColor32* self, PyObject* value, void* closure) {
    if (!PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "blue should be an int");
        return -1;
    }
    self->fThis->b = PyInt_AsLong(value);
    return 0;
}

static int pyColor32_setAlpha(pyColor32* self, PyObject* value, void* closure) {
    if (!PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "alpha should be an int");
        return -1;
    }
    self->fThis->a = PyInt_AsLong(value);
    return 0;
}

static int pyColor32_setColor(pyColor32* self, PyObject* value, void* closure) {
    if (!PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "color should be an int");
        return -1;
    }
    self->fThis->color = PyInt_AsLong(value);
    return 0;
}

static PyMethodDef pyColor32_Methods[] = {
    { "set", (PyCFunction)pyColor32_set, METH_VARARGS | METH_KEYWORDS,
      "Params: red, green, blue, alpha (all optional)\n"
      "Params: color (32-bit value)\n"
      "Sets the color" },
    { "read32", (PyCFunction)pyColor32_read32, METH_VARARGS,
      "Params: stream\n"
      "Reads this object from `stream`" },
    { "write32", (PyCFunction)pyColor32_write32, METH_VARARGS,
      "Params: stream\n"
      "Writes this object to `stream`" },
    { "readRGBA8", (PyCFunction)pyColor32_readRGBA8, METH_VARARGS,
      "Params: stream\n"
      "Reads this object from `stream`" },
    { "writeRGBA8", (PyCFunction)pyColor32_writeRGBA8, METH_VARARGS,
      "Params: stream\n"
      "Writes this object to `stream`" },
    { "readRGB8", (PyCFunction)pyColor32_readRGB8, METH_VARARGS,
      "Params: stream\n"
      "Same as readRGBA8(), but does not read alpha" },
    { "writeRGB8", (PyCFunction)pyColor32_writeRGB8, METH_VARARGS,
      "Params: stream\n"
      "Same as writeRGBA8(), but does not write alpha" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyColor32_GetSet[] = {
    { "red", (getter)pyColor32_getRed, (setter)pyColor32_setRed, NULL, NULL },
    { "green", (getter)pyColor32_getGreen, (setter)pyColor32_setGreen, NULL, NULL },
    { "blue", (getter)pyColor32_getBlue, (setter)pyColor32_setBlue, NULL, NULL },
    { "alpha", (getter)pyColor32_getAlpha, (setter)pyColor32_setAlpha, NULL, NULL },
    { "color", (getter)pyColor32_getColor, (setter)pyColor32_setColor, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyColor32_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.hsColor32",               /* tp_name */
    sizeof(pyColor32),                  /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pyColor32_dealloc,      /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_compare */
    (reprfunc)pyColor32_Repr,           /* tp_repr */
    NULL,                               /* tp_as_number */
    NULL,                               /* tp_as_sequence */
    NULL,                               /* tp_as_mapping */
    NULL,                               /* tp_hash */
    NULL,                               /* tp_call */
    NULL,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */

    Py_TPFLAGS_DEFAULT,                 /* tp_flags */
    "hsColor32 wrapper",                /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyColor32_Methods,                  /* tp_methods */
    NULL,                               /* tp_members */
    pyColor32_GetSet,                   /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyColor32___init__,       /* tp_init */
    NULL,                               /* tp_alloc */
    pyColor32_new,                      /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyColor32_Type() {
    if (PyType_Ready(&pyColor32_Type) < 0)
        return NULL;

    Py_INCREF(&pyColor32_Type);
    return (PyObject*)&pyColor32_Type;
}

int pyColor32_Check(PyObject* obj) {
    if (obj->ob_type == &pyColor32_Type
        || PyType_IsSubtype(obj->ob_type, &pyColor32_Type))
        return 1;
    return 0;
}

}
