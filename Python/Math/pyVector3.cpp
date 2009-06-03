#include <PyPlasma.h>
#include <Math/hsGeometry3.h>
#include "pyGeometry3.h"
#include "Stream/pyStream.h"

extern "C" {

static void pyVector3_dealloc(pyVector3* self) {
    delete self->fThis;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static int pyVector3___init__(pyVector3* self, PyObject* args, PyObject* kwds) {
    float x = 0.0f, y = 0.0f, z = 0.0f;
    PyObject* init = NULL;
    static char* kwlist[] = { "X", "Y", "Z", NULL };
    static char* kwlist2[] = { "vector", NULL };

    if (PyArg_ParseTupleAndKeywords(args, kwds, "fff", kwlist, &x, &y, &z)) {
        (*self->fThis) = hsVector3(x, y, z);
    } else if (PyErr_Clear(), PyArg_ParseTupleAndKeywords(args, kwds, "|O", kwlist2, &init)) {
        if (init == NULL) {
            (*self->fThis) = hsVector3();
            return 0;
        }
        if (pyVector3_Check(init)) {
            (*self->fThis) = (*((pyVector3*)init)->fThis);
        } else {
            PyErr_SetString(PyExc_TypeError, "__init__ expects a vector");
            return -1;
        }
    } else {
        return -1;
    }

    return 0;
}

static PyObject* pyVector3_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyVector3* self = (pyVector3*)type->tp_alloc(type, 0);
    if (self != NULL)
        self->fThis = new hsVector3();
    return (PyObject*)self;
}

static PyObject* pyVector3_Repr(pyVector3* self) {
    plString repr = plString::Format("hsVector3(%f, %f, %f)",
             self->fThis->X, self->fThis->Y, self->fThis->Z);
    return PyString_FromString(repr.cstr());
}

static PyObject* pyVector3_add(PyObject* left, PyObject* right) {
    if (!pyVector3_Check(left) || !pyVector3_Check(right)) {
        PyErr_SetString(PyExc_TypeError, "Incompatible Types");
        return NULL;
    }
    return pyVector3_FromVector3(*((pyVector3*)left)->fThis + *((pyVector3*)right)->fThis);
}

static PyObject* pyVector3_subtract(PyObject* left, PyObject* right) {
    if (!pyVector3_Check(left) || !pyVector3_Check(right)) {
        PyErr_SetString(PyExc_TypeError, "Incompatible Types");
        return NULL;
    }
    return pyVector3_FromVector3(*((pyVector3*)left)->fThis - *((pyVector3*)right)->fThis);
}

static PyObject* pyVector3_multiply(PyObject* left, PyObject* right) {
    if (pyVector3_Check(left)) {
        if (pyVector3_Check(right)) {
            PyErr_SetString(PyExc_TypeError, "Vector Multiplication should use dotP and crossP");
            return NULL;
        } else if (PyFloat_Check(right)) {
            return pyVector3_FromVector3(*((pyVector3*)left)->fThis * PyFloat_AsDouble(right));
        } else {
            PyErr_SetString(PyExc_TypeError, "Incompatible Types");
            return NULL;
        }
    } else if (pyVector3_Check(right)) {
        if (PyFloat_Check(left)) {
            return pyVector3_FromVector3(*((pyVector3*)right)->fThis * PyFloat_AsDouble(left));
        } else {
            PyErr_SetString(PyExc_TypeError, "Incompatible Types");
            return NULL;
        }
    } else {
        PyErr_SetString(PyExc_TypeError, "This should not happen");
        return NULL;
    }
}

static PyObject* pyVector3_negative(pyVector3* self) {
    return pyVector3_FromVector3(hsVector3(-(self->fThis->X), -(self->fThis->Y),
                                           -(self->fThis->Z)));
}

static PyObject* pyVector3_positive(pyVector3* self) {
    return pyVector3_FromVector3(hsVector3(+(self->fThis->X), +(self->fThis->Y),
                                           +(self->fThis->Z)));
}

static PyObject* pyVector3_absolute(pyVector3* self) {
    return pyVector3_FromVector3(hsVector3(fabs(self->fThis->X),
                                           fabs(self->fThis->Y),
                                           fabs(self->fThis->Z)));
}

static int pyVector3_nonzero(pyVector3* self) {
    return (self->fThis->X != 0.0f) || (self->fThis->Y != 0.0f)
        || (self->fThis->Z != 0.0f);
}

static PyObject* pyVector3_magnitude(pyVector3* self) {
    return PyFloat_FromDouble(self->fThis->magnitude());
}

static PyObject* pyVector3_dotP(pyVector3* self, PyObject* args) {
    pyVector3* vec;
    if (!PyArg_ParseTuple(args, "O", &vec)) {
        PyErr_SetString(PyExc_TypeError, "dotP expects an hsVector3");
        return NULL;
    }
    if (!pyVector3_Check((PyObject*)vec)) {
        PyErr_SetString(PyExc_TypeError, "dotP expects an hsVector3");
        return NULL;
    }
    return PyFloat_FromDouble(self->fThis->dotP(*vec->fThis));
}

static PyObject* pyVector3_crossP(pyVector3* self, PyObject* args) {
    pyVector3* vec;
    if (!PyArg_ParseTuple(args, "O", &vec)) {
        PyErr_SetString(PyExc_TypeError, "crossP expects an hsVector3");
        return NULL;
    }
    if (!pyVector3_Check((PyObject*)vec)) {
        PyErr_SetString(PyExc_TypeError, "crossP expects an hsVector3");
        return NULL;
    }
    return pyVector3_FromVector3(self->fThis->crossP(*vec->fThis));
}

static PyObject* pyVector3_read(pyVector3* self, PyObject* args) {
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

static PyObject* pyVector3_write(pyVector3* self, PyObject* args) {
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

static PyObject* pyVector3_getX(pyVector3* self, void*) {
    return PyFloat_FromDouble(self->fThis->X);
}

static PyObject* pyVector3_getY(pyVector3* self, void*) {
    return PyFloat_FromDouble(self->fThis->Y);
}

static PyObject* pyVector3_getZ(pyVector3* self, void*) {
    return PyFloat_FromDouble(self->fThis->Z);
}

static int pyVector3_setX(pyVector3* self, PyObject* value, void*) {
    if (!PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "X needs to be a float");
        return -1;
    }
    self->fThis->X = PyFloat_AsDouble(value);
    return 0;
}

static int pyVector3_setY(pyVector3* self, PyObject* value, void*) {
    if (!PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "Y needs to be a float");
        return -1;
    }
    self->fThis->Y = PyFloat_AsDouble(value);
    return 0;
}

static int pyVector3_setZ(pyVector3* self, PyObject* value, void*) {
    if (!PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "Z needs to be a float");
        return -1;
    }
    self->fThis->Z = PyFloat_AsDouble(value);
    return 0;
}

PyNumberMethods pyVector3_As_Number = {
    (binaryfunc)pyVector3_add,          /* nb_add */
    (binaryfunc)pyVector3_subtract,     /* nb_subtract */
    (binaryfunc)pyVector3_multiply,     /* nb_multiply */
#if (PY_MAJOR_VERSION < 3)
    NULL,                               /* nb_divide */
#endif
    NULL,                               /* nb_remainder */
    NULL,                               /* nb_divmod */
    NULL,                               /* nb_power */
    (unaryfunc)pyVector3_negative,      /* nb_negative */
    (unaryfunc)pyVector3_positive,      /* nb_positive */
    (unaryfunc)pyVector3_absolute,      /* nb_absolute */
    (inquiry)pyVector3_nonzero,         /* nb_nonzero */
    NULL,                               /* nb_invert */
    NULL,                               /* nb_lshift */
    NULL,                               /* nb_rshift */
    NULL,                               /* nb_and */
    NULL,                               /* nb_xor */
    NULL,                               /* nb_or */
#if (PY_MAJOR_VERSION < 3)
    NULL,                               /* nb_coerce */
#endif
    NULL,                               /* nb_int */
    NULL,                               /* nb_long */
    NULL,                               /* nb_float */
#if (PY_MAJOR_VERSION < 3)
    NULL,                               /* nb_oct */
    NULL,                               /* nb_hex */
#endif
    NULL,                               /* nb_inplace_add */
    NULL,                               /* nb_inplace_subtract */
    NULL,                               /* nb_inplace_multiply */
#if (PY_MAJOR_VERSION < 3)
    NULL,                               /* nb_inplace_divide */
#endif
    NULL,                               /* nb_inplace_remainder */
    NULL,                               /* nb_inplace_power */
    NULL,                               /* nb_inplace_lshift */
    NULL,                               /* nb_inplace_rshift */
    NULL,                               /* nb_inplace_and */
    NULL,                               /* nb_inplace_xor */
    NULL,                               /* nb_inplace_or */
    NULL,                               /* nb_floor_divide */
    NULL,                               /* nb_true_divide */
    NULL,                               /* nb_inplace_floor_divide */
    NULL,                               /* nb_inplace_true_divide */
#if ((PY_MAJOR_VERSION > 2) || (PY_MAJOR_VERSION == 2 && PY_MINOR_VERSION >= 5))
    NULL,                               /* nb_index */
#endif
};

PyMethodDef pyVector3_Methods[] = {
    { "magnitude", (PyCFunction)pyVector3_magnitude, METH_NOARGS,
      "Returns the magnitude of the vector" },
    { "dotP", (PyCFunction)pyVector3_dotP, METH_VARARGS,
      "Params: vec\n"
      "Returns the dot product of this vector and `vec`" },
    { "crossP", (PyCFunction)pyVector3_crossP, METH_VARARGS,
      "Params: vec\n"
      "Returns the cross product of this vector and `vec`" },
    { "read", (PyCFunction)pyVector3_read, METH_VARARGS,
      "Params: stream\n"
      "Reads this vector from `stream`" },
    { "write", (PyCFunction)pyVector3_write, METH_VARARGS,
      "Params: stream\n"
      "Writes this vector to `stream`" },
    { NULL, NULL, 0, NULL }
};

PyGetSetDef pyVector3_GetSet[] = {
    { "X", (getter)pyVector3_getX, (setter)pyVector3_setX, NULL, NULL },
    { "Y", (getter)pyVector3_getY, (setter)pyVector3_setY, NULL, NULL },
    { "Z", (getter)pyVector3_getZ, (setter)pyVector3_setZ, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyVector3_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.hsVector3",               /* tp_name */
    sizeof(pyVector3),                  /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pyVector3_dealloc,      /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_compare */
    (reprfunc)pyVector3_Repr,           /* tp_repr */
    &pyVector3_As_Number,               /* tp_as_number */
    NULL,                               /* tp_as_sequence */
    NULL,                               /* tp_as_mapping */
    NULL,                               /* tp_hash */
    NULL,                               /* tp_call */
    NULL,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */

    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_CHECKTYPES, /* tp_flags */
    "hsVector3/hsPoint3 wrapper",       /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyVector3_Methods,                  /* tp_methods */
    NULL,                               /* tp_members */
    pyVector3_GetSet,                   /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyVector3___init__,       /* tp_init */
    NULL,                               /* tp_alloc */
    pyVector3_new,                      /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyVector3_Type() {
    if (PyType_Ready(&pyVector3_Type) < 0)
        return NULL;

    Py_INCREF(&pyVector3_Type);
    return (PyObject*)&pyVector3_Type;
}

int pyVector3_Check(PyObject* obj) {
    if (obj->ob_type == &pyVector3_Type
        || PyType_IsSubtype(obj->ob_type, &pyVector3_Type))
        return 1;
    return 0;
}

PyObject* pyVector3_FromVector3(const hsVector3& vec) {
    pyVector3* pv = PyObject_New(pyVector3, &pyVector3_Type);
    pv->fThis = new hsVector3(vec);
    return (PyObject*)pv;
}

}
