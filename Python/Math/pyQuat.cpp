#include <PyPlasma.h>
#include <Math/hsGeometry3.h>
#include <Math/hsQuat.h>
#include "pyGeometry3.h"
#include "Stream/pyStream.h"

extern "C" {

static void pyQuat_dealloc(pyQuat* self) {
    delete self->fThis;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static int pyQuat___init__(pyQuat* self, PyObject* args, PyObject* kwds) {
    float x = 0.0f, y = 0.0f, z = 0.0f, w = 0.0f;
    PyObject* init = NULL;
    static char* kwlist[] = { "X", "Y", "Z", "W", NULL };
    static char* kwlist2[] = { "quat", NULL };
    static char* kwlist3[] = { "angle", "axis", NULL };

    if (PyArg_ParseTupleAndKeywords(args, kwds, "ffff", kwlist, &x, &y, &z, &w)) {
        (*self->fThis) = hsQuat(x, y, z, w);
    } else if (PyErr_Clear(), PyArg_ParseTupleAndKeywords(args, kwds, "fO", kwlist3, &w, &init)) {
        if (pyVector3_Check(init)) {
            (*self->fThis) = hsQuat(w, *((pyVector3*)init)->fThis);
            return 0;
        } else {
            PyErr_SetString(PyExc_TypeError, "__init__ expects a quaternion or an angle and axis");
            return -1;
        }
    } else if (PyErr_Clear(), PyArg_ParseTupleAndKeywords(args, kwds, "|O", kwlist2, &init)) {
        if (init == NULL) {
            (*self->fThis) = hsQuat();
            return 0;
        }
        if (pyQuat_Check(init)) {
            (*self->fThis) = (*((pyQuat*)init)->fThis);
        } else {
            PyErr_SetString(PyExc_TypeError, "__init__ expects a quaternion or an angle and axis");
            return -1;
        }
    } else {
        return -1;
    }

    return 0;
}

static PyObject* pyQuat_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyQuat* self = (pyQuat*)type->tp_alloc(type, 0);
    if (self != NULL)
        self->fThis = new hsQuat();
    return (PyObject*)self;
}

static PyObject* pyQuat_Repr(pyQuat* self) {
    plString repr = plString::Format("hsQuat(%f, %f, %f, %f)",
             self->fThis->X, self->fThis->Y, self->fThis->Z, self->fThis->W);
    return PyString_FromString(repr.cstr());
}

static PyObject* pyQuat_add(PyObject* left, PyObject* right) {
    if (!pyQuat_Check(left) || !pyQuat_Check(right)) {
        PyErr_SetString(PyExc_TypeError, "Incompatible Types");
        return NULL;
    }
    return pyQuat_FromQuat(*((pyQuat*)left)->fThis + *((pyQuat*)right)->fThis);
}

static PyObject* pyQuat_subtract(PyObject* left, PyObject* right) {
    if (!pyQuat_Check(left) || !pyQuat_Check(right)) {
        PyErr_SetString(PyExc_TypeError, "Incompatible Types");
        return NULL;
    }
    return pyQuat_FromQuat(*((pyQuat*)left)->fThis - *((pyQuat*)right)->fThis);
}

static PyObject* pyQuat_multiply(PyObject* left, PyObject* right) {
    if (pyQuat_Check(left)) {
        if (pyQuat_Check(right)) {
            return pyQuat_FromQuat(*((pyQuat*)left)->fThis * *((pyQuat*)right)->fThis);
        } else if (PyFloat_Check(right)) {
            return pyQuat_FromQuat(*((pyQuat*)left)->fThis * PyFloat_AsDouble(right));
        } else {
            PyErr_SetString(PyExc_TypeError, "Incompatible Types");
            return NULL;
        }
    } else if (pyQuat_Check(right)) {
        if (PyFloat_Check(left)) {
            return pyQuat_FromQuat(*((pyQuat*)right)->fThis * PyFloat_AsDouble(left));
        } else {
            PyErr_SetString(PyExc_TypeError, "Incompatible Types");
            return NULL;
        }
    } else {
        PyErr_SetString(PyExc_TypeError, "This should not happen");
        return NULL;
    }
}

static PyObject* pyQuat_negative(pyQuat* self) {
    return pyQuat_FromQuat(hsQuat(-(self->fThis->X), -(self->fThis->Y),
                                  -(self->fThis->Z), -(self->fThis->W)));
}

static PyObject* pyQuat_positive(pyQuat* self) {
    return pyQuat_FromQuat(hsQuat(+(self->fThis->X), +(self->fThis->Y),
                                  +(self->fThis->Z), +(self->fThis->W)));
}

static PyObject* pyQuat_absolute(pyQuat* self) {
    return pyQuat_FromQuat(hsQuat(fabs(self->fThis->X),
                                  fabs(self->fThis->Y),
                                  fabs(self->fThis->Z),
                                  fabs(self->fThis->W)));
}

static int pyQuat_nonzero(pyQuat* self) {
    return (self->fThis->X != 0.0f) || (self->fThis->Y != 0.0f)
        || (self->fThis->Z != 0.0f) || (self->fThis->W != 0.0f);
}

static PyObject* pyQuat_Identity(PyObject*) {
    return pyQuat_FromQuat(hsQuat::Identity());
}

static PyObject* pyQuat_conjugate(pyQuat* self) {
    return pyQuat_FromQuat(self->fThis->conjugate());
}

static PyObject* pyQuat_read(pyQuat* self, PyObject* args) {
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

static PyObject* pyQuat_write(pyQuat* self, PyObject* args) {
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

static PyObject* pyQuat_getX(pyQuat* self, void*) {
    return PyFloat_FromDouble(self->fThis->X);
}

static PyObject* pyQuat_getY(pyQuat* self, void*) {
    return PyFloat_FromDouble(self->fThis->Y);
}

static PyObject* pyQuat_getZ(pyQuat* self, void*) {
    return PyFloat_FromDouble(self->fThis->Z);
}

static PyObject* pyQuat_getW(pyQuat* self, void*) {
    return PyFloat_FromDouble(self->fThis->W);
}

static int pyQuat_setX(pyQuat* self, PyObject* value, void*) {
    if (!PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "X needs to be a float");
        return -1;
    }
    self->fThis->X = PyFloat_AsDouble(value);
    return 0;
}

static int pyQuat_setY(pyQuat* self, PyObject* value, void*) {
    if (!PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "Y needs to be a float");
        return -1;
    }
    self->fThis->Y = PyFloat_AsDouble(value);
    return 0;
}

static int pyQuat_setZ(pyQuat* self, PyObject* value, void*) {
    if (!PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "Z needs to be a float");
        return -1;
    }
    self->fThis->Z = PyFloat_AsDouble(value);
    return 0;
}

static int pyQuat_setW(pyQuat* self, PyObject* value, void*) {
    if (!PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "W needs to be a float");
        return -1;
    }
    self->fThis->W = PyFloat_AsDouble(value);
    return 0;
}

PyNumberMethods pyQuat_As_Number = {
    (binaryfunc)pyQuat_add,             /* nb_add */
    (binaryfunc)pyQuat_subtract,        /* nb_subtract */
    (binaryfunc)pyQuat_multiply,        /* nb_multiply */
#if (PY_MAJOR_VERSION < 3)
    NULL,                               /* nb_divide */
#endif
    NULL,                               /* nb_remainder */
    NULL,                               /* nb_divmod */
    NULL,                               /* nb_power */
    (unaryfunc)pyQuat_negative,         /* nb_negative */
    (unaryfunc)pyQuat_positive,         /* nb_positive */
    (unaryfunc)pyQuat_absolute,         /* nb_absolute */
    (inquiry)pyQuat_nonzero,            /* nb_nonzero */
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

PyMethodDef pyQuat_Methods[] = {
    { "Identity", (PyCFunction)pyQuat_Identity, METH_NOARGS | METH_STATIC,
      "Returns an identity quaternion" },
    { "conjugate", (PyCFunction)pyQuat_conjugate, METH_NOARGS,
      "Returns the conjugate of the quaternion" },
    { "read", (PyCFunction)pyQuat_read, METH_VARARGS,
      "Params: stream\n"
      "Reads this vector from `stream`" },
    { "write", (PyCFunction)pyQuat_write, METH_VARARGS,
      "Params: stream\n"
      "Writes this vector to `stream`" },
    { NULL, NULL, 0, NULL }
};

PyGetSetDef pyQuat_GetSet[] = {
    { "X", (getter)pyQuat_getX, (setter)pyQuat_setX, NULL, NULL },
    { "Y", (getter)pyQuat_getY, (setter)pyQuat_setY, NULL, NULL },
    { "Z", (getter)pyQuat_getZ, (setter)pyQuat_setZ, NULL, NULL },
    { "W", (getter)pyQuat_getW, (setter)pyQuat_setW, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyQuat_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.hsQuat",                  /* tp_name */
    sizeof(pyQuat),                     /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pyQuat_dealloc,         /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_compare */
    (reprfunc)pyQuat_Repr,              /* tp_repr */
    &pyQuat_As_Number,                  /* tp_as_number */
    NULL,                               /* tp_as_sequence */
    NULL,                               /* tp_as_mapping */
    NULL,                               /* tp_hash */
    NULL,                               /* tp_call */
    NULL,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */

    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_CHECKTYPES, /* tp_flags */
    "Plasma Quaternion",                /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyQuat_Methods,                     /* tp_methods */
    NULL,                               /* tp_members */
    pyQuat_GetSet,                      /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyQuat___init__,          /* tp_init */
    NULL,                               /* tp_alloc */
    pyQuat_new,                         /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyQuat_Type() {
    if (PyType_Ready(&pyQuat_Type) < 0)
        return NULL;

    Py_INCREF(&pyQuat_Type);
    return (PyObject*)&pyQuat_Type;
}

int pyQuat_Check(PyObject* obj) {
    if (obj->ob_type == &pyQuat_Type
        || PyType_IsSubtype(obj->ob_type, &pyQuat_Type))
        return 1;
    return 0;
}

PyObject* pyQuat_FromQuat(const hsQuat& quat) {
    pyQuat* pq = PyObject_New(pyQuat, &pyQuat_Type);
    pq->fThis = new hsQuat(quat);
    return (PyObject*)pq;
}

}
