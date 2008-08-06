#include <Python.h>
#include <Util/hsBitVector.h>
#include "pyUtil.h"
#include "../Stream/pyStream.h"

extern "C" {

static void pyBitVector_dealloc(pyBitVector* self) {
    if (self->fPyOwned)
        delete self->fThis;
    self->ob_type->tp_free((PyObject*)self);
}

static int pyBitVector___init__(pyBitVector* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    
    return 0;
}

static PyObject* pyBitVector_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyBitVector* self = (pyBitVector*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new hsBitVector();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyBitVector_Subscript(pyBitVector* self, PyObject* key) {
    if (PyString_Check(key)) {
        Py_INCREF(key);
        char* name = PyString_AsString(key);
        int idx = (int)self->fThis->getValue(name);
        Py_DECREF(key);
        bool v = self->fThis->get(idx);
        return PyBool_FromLong(v ? 1 : 0);
    } else if (PyInt_Check(key)) {
        int idx = PyInt_AsLong(key);
        bool v = self->fThis->get(idx);
        return PyBool_FromLong(v ? 1 : 0);
    } else {
        PyErr_SetString(PyExc_TypeError, "Invalid subscript");
        return NULL;
    }
}

static int pyBitVector_AssSubscript(pyBitVector* self, PyObject* key, PyObject* value) {
    if (!PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "BitVector bits should be bools");
        return -1;
    }
    bool b = (PyInt_AsLong(value) != 0);

    if (PyString_Check(key)) {
        Py_INCREF(key);
        char* name = PyString_AsString(key);
        int idx = (int)self->fThis->getValue(name);
        Py_DECREF(key);
        self->fThis->set(idx, b);
        return 0;
    } else if (PyInt_Check(key)) {
        int idx = PyInt_AsLong(key);
        self->fThis->set(idx, b);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "Invalid subscript");
        return -1;
    }
}

static PyObject* pyBitVector_isEmpty(pyBitVector* self) {
    return PyBool_FromLong(self->fThis->isEmpty() ? 1 : 0);
}

static PyObject* pyBitVector_clear(pyBitVector* self) {
    self->fThis->clear();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyBitVector_compact(pyBitVector* self) {
    self->fThis->compact();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyBitVector_getName(pyBitVector* self, PyObject* args) {
    int index;
    if (!PyArg_ParseTuple(args, "i", &index)) {
        PyErr_SetString(PyExc_TypeError, "getName expects an int");
        return NULL;
    }
    return PyString_FromString(self->fThis->getName((size_t)index));
}

static PyObject* pyBitVector_getValue(pyBitVector* self, PyObject* args) {
    const char* name;
    if (!PyArg_ParseTuple(args, "s", &name)) {
        PyErr_SetString(PyExc_TypeError, "getValue expects a string");
        return NULL;
    }
    return PyInt_FromLong(self->fThis->getValue(name));
}

static PyObject* pyBitVector_setName(pyBitVector* self, PyObject* args) {
    int index;
    const char* name;
    if (!PyArg_ParseTuple(args, "is", &index, &name)) {
        PyErr_SetString(PyExc_TypeError, "setName expects int, string");
        return NULL;
    }
    self->fThis->setName(index, name);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyBitVector_read(pyBitVector* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects a hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects a hsStream");
        return NULL;
    }
    self->fThis->read(stream->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyBitVector_write(pyBitVector* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects a hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects a hsStream");
        return NULL;
    }
    self->fThis->write(stream->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMappingMethods pyBitVector_AsMapping = {
    NULL,                                   /* mp_length */
    (binaryfunc)pyBitVector_Subscript,      /* mp_subscript */
    (objobjargproc)pyBitVector_AssSubscript /* mp_ass_subscript */
};

static PyMethodDef pyBitVector_Methods[] = {
    { "isEmpty", (PyCFunction)pyBitVector_isEmpty, METH_NOARGS,
      "Returns whether the vector is empty" },
    { "clear", (PyCFunction)pyBitVector_clear, METH_NOARGS,
      "Clears the vector of all bits" },
    { "compact", (PyCFunction)pyBitVector_compact, METH_NOARGS,
      "Compacts the vector to the smallest size necessary to\n"
      "store all of the contained bits" },
    { "getName", (PyCFunction)pyBitVector_getName, METH_VARARGS,
      "Params: index\n"
      "Returns the name of the bit at `index`" },
    { "getValue", (PyCFunction)pyBitVector_getValue, METH_VARARGS,
      "Params: name\n"
      "Returns the index of the bit named `name`" },
    { "setName", (PyCFunction)pyBitVector_setName, METH_VARARGS,
      "Params: index, name\n"
      "Names the bit at `index` to `name`" },
    { "read", (PyCFunction)pyBitVector_read, METH_VARARGS,
      "Params: stream\n"
      "Read this BitVector from `stream`" },
    { "write", (PyCFunction)pyBitVector_write, METH_VARARGS,
      "Params: stream\n"
      "Write this BitVector to `stream`" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyBitVector_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.hsBitVector",             /* tp_name */
    sizeof(pyBitVector),                /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pyBitVector_dealloc,    /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_compare */
    NULL,                               /* tp_repr */
    NULL,                               /* tp_as_number */
    NULL,                               /* tp_as_sequence */
    &pyBitVector_AsMapping,             /* tp_as_mapping */
    NULL,                               /* tp_hash */
    NULL,                               /* tp_call */
    NULL,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */

    Py_TPFLAGS_DEFAULT,                 /* tp_flags */
    "hsBitVector wrapper",              /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyBitVector_Methods,                /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyBitVector___init__,     /* tp_init */
    NULL,                               /* tp_alloc */
    pyBitVector_new,                    /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyBitVector_Type() {
    if (PyType_Ready(&pyBitVector_Type) < 0)
        return NULL;

    Py_INCREF(&pyBitVector_Type);
    return (PyObject*)&pyBitVector_Type;
}

int pyBitVector_Check(PyObject* obj) {
    if (obj->ob_type == &pyBitVector_Type
        || PyType_IsSubtype(obj->ob_type, &pyBitVector_Type))
        return 1;
    return 0;
}

PyObject* pyBitVector_FromBitVector(class hsBitVector& vec) {
    pyBitVector* bv = PyObject_New(pyBitVector, &pyBitVector_Type);
    bv->fThis = &vec;
    bv->fPyOwned = false;
    return (PyObject*)bv;
}

}
