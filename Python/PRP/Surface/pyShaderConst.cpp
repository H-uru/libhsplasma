#include <PyPlasma.h>
#include <PRP/Surface/plShader.h>
#include "pyShader.h"
#include "Stream/pyStream.h"

extern "C" {

static void pyShaderConst_dealloc(pyShaderConst* self) {
    delete self->fThis;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static int pyShaderConst___init__(pyShaderConst* self, PyObject* args, PyObject* kwds) {
    float sc[4];
    PyObject* init = NULL;

    if (PyArg_ParseTuple(args, "ffff", &sc[0], &sc[1], &sc[2], &sc[3])) {
        self->fThis->fArray[0] = sc[0];
        self->fThis->fArray[1] = sc[1];
        self->fThis->fArray[2] = sc[2];
        self->fThis->fArray[3] = sc[3];
    } else if (PyErr_Clear(), PyArg_ParseTuple(args, "|O", &init)) {
        if (init == NULL)
            return 0;
        if (pyShaderConst_Check(init)) {
            self->fThis->fArray[0] = ((pyShaderConst*)init)->fThis->fArray[0];
            self->fThis->fArray[1] = ((pyShaderConst*)init)->fThis->fArray[1];
            self->fThis->fArray[2] = ((pyShaderConst*)init)->fThis->fArray[2];
            self->fThis->fArray[3] = ((pyShaderConst*)init)->fThis->fArray[3];
        } else {
            return -1;
        }
    } else {
        return -1;
    }

    return 0;
}

static PyObject* pyShaderConst_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyShaderConst* self = (pyShaderConst*)type->tp_alloc(type, 0);
    if (self != NULL)
        self->fThis = new plShaderConst();
    return (PyObject*)self;
}

static PyObject* pyShaderConst_Subscript(pyShaderConst* self, PyObject* key) {
    if (!PyInt_Check(key)) {
        PyErr_SetString(PyExc_IndexError, "subscript should be an int");
        return NULL;
    }
    return PyFloat_FromDouble(self->fThis->fArray[PyInt_AsLong(key)]);
}

static int pyShaderConst_AssSubscript(pyShaderConst* self, PyObject* key, PyObject* value) {
    if (!PyInt_Check(key)) {
        PyErr_SetString(PyExc_IndexError, "subscript should be an int");
        return -1;
    }
    if (!PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "Shader Const values should be floats");
        return -1;
    }
    self->fThis->fArray[PyInt_AsLong(key)] = PyFloat_AsDouble(value);
    return 0;
}

static PyObject* pyShaderConst_Repr(pyShaderConst* self) {
    plString repr = plString::Format("plShaderConst(%f, %f, %f, %f)",
        self->fThis->fX, self->fThis->fY, self->fThis->fZ, self->fThis->fW);
    return PlStr_To_PyStr(repr);
}

static PyObject* pyShaderConst_read(pyShaderConst* self, PyObject* args) {
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

static PyObject* pyShaderConst_write(pyShaderConst* self, PyObject* args) {
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

static PyObject* pyShaderConst_getItem(pyShaderConst* self, void* which) {
    return PyFloat_FromDouble(self->fThis->fArray[(size_t)which]);
}

static int pyShaderConst_setItem(pyShaderConst* self, PyObject* value, void* which) {
    if (!PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "shader const values should be floats");
        return -1;
    }
    self->fThis->fArray[(size_t)which] = PyFloat_AsDouble(value);
    return 0;
}

static PyMappingMethods pyShaderConst_As_Mapping = {
    NULL,                                       /* mp_length */
    (binaryfunc)pyShaderConst_Subscript,        /* mp_subscript */
    (objobjargproc)pyShaderConst_AssSubscript   /* mp_ass_subscript */
};

static PyMethodDef pyShaderConst_Methods[] = {
    { "read", (PyCFunction)pyShaderConst_read, METH_VARARGS,
      "Params: stream\n"
      "Reads this object from `stream`" },
    { "write", (PyCFunction)pyShaderConst_write, METH_VARARGS,
      "Params: stream\n"
      "Writes this object to `stream`" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyShaderConst_GetSet[] = {
    { "X", (getter)pyShaderConst_getItem, (setter)pyShaderConst_setItem, NULL, (void*)0 },
    { "Y", (getter)pyShaderConst_getItem, (setter)pyShaderConst_setItem, NULL, (void*)1 },
    { "Z", (getter)pyShaderConst_getItem, (setter)pyShaderConst_setItem, NULL, (void*)2 },
    { "W", (getter)pyShaderConst_getItem, (setter)pyShaderConst_setItem, NULL, (void*)3 },
    { "red", (getter)pyShaderConst_getItem, (setter)pyShaderConst_setItem, NULL, (void*)0 },
    { "green", (getter)pyShaderConst_getItem, (setter)pyShaderConst_setItem, NULL, (void*)1 },
    { "blue", (getter)pyShaderConst_getItem, (setter)pyShaderConst_setItem, NULL, (void*)2 },
    { "alpha", (getter)pyShaderConst_getItem, (setter)pyShaderConst_setItem, NULL, (void*)3 },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyShaderConst_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plShaderConst",           /* tp_name */
    sizeof(pyShaderConst),              /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pyShaderConst_dealloc,  /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_compare */
    (reprfunc)pyShaderConst_Repr,       /* tp_repr */
    NULL,                               /* tp_as_number */
    NULL,                               /* tp_as_sequence */
    &pyShaderConst_As_Mapping,          /* tp_as_mapping */
    NULL,                               /* tp_hash */
    NULL,                               /* tp_call */
    NULL,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */

    Py_TPFLAGS_DEFAULT,                 /* tp_flags */
    "plShaderConst wrapper",            /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyShaderConst_Methods,              /* tp_methods */
    NULL,                               /* tp_members */
    pyShaderConst_GetSet,               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyShaderConst___init__,   /* tp_init */
    NULL,                               /* tp_alloc */
    pyShaderConst_new,                  /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyShaderConst_Type() {
    if (PyType_Ready(&pyShaderConst_Type) < 0)
        return NULL;

    Py_INCREF(&pyShaderConst_Type);
    return (PyObject*)&pyShaderConst_Type;
}

int pyShaderConst_Check(PyObject* obj) {
    if (obj->ob_type == &pyShaderConst_Type
        || PyType_IsSubtype(obj->ob_type, &pyShaderConst_Type))
        return 1;
    return 0;
}

PyObject* pyShaderConst_FromShaderConst(const plShaderConst& sc) {
    pyShaderConst* psc = PyObject_New(pyShaderConst, &pyShaderConst_Type);
    psc->fThis = new plShaderConst(sc);
    return (PyObject*)psc;
}

}
