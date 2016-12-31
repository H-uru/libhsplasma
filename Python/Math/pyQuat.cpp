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

#include "pyGeometry3.h"

#include <Math/hsQuat.h>
#include "Stream/pyStream.h"

extern "C" {

PY_PLASMA_VALUE_DEALLOC(Quat)

PY_PLASMA_INIT_DECL(Quat) {
    float x = 0.0f, y = 0.0f, z = 0.0f, w = 0.0f;
    PyObject* init = NULL;
    static char* kwlist[] = { _pycs("X"), _pycs("Y"), _pycs("Z"), _pycs("W"), NULL };
    static char* kwlist2[] = { _pycs("quat"), NULL };
    static char* kwlist3[] = { _pycs("angle"), _pycs("axis"), NULL };

    if (PyArg_ParseTupleAndKeywords(args, kwds, "ffff", kwlist, &x, &y, &z, &w)) {
        (*self->fThis) = hsQuat(x, y, z, w);
    } else if (PyErr_Clear(), PyArg_ParseTupleAndKeywords(args, kwds, "fO", kwlist3, &w, &init)) {
        if (pyPlasma_check<hsVector3>(init)) {
            (*self->fThis) = hsQuat(w, pyPlasma_get<hsVector3>(init));
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
            (*self->fThis) = pyPlasma_get<hsQuat>(init);
        } else {
            PyErr_SetString(PyExc_TypeError, "__init__ expects a quaternion or an angle and axis");
            return -1;
        }
    } else {
        return -1;
    }

    return 0;
}

PY_PLASMA_VALUE_NEW(Quat, hsQuat)

static PyObject* pyQuat_Repr(pyQuat* self) {
    plString repr = plString::Format("hsQuat(%f, %f, %f, %f)",
             self->fThis->X, self->fThis->Y, self->fThis->Z, self->fThis->W);
    return pyPlasma_convert(repr);
}

static PyObject* pyQuat_add(PyObject* left, PyObject* right) {
    if (!pyQuat_Check(left) || !pyQuat_Check(right)) {
        PyErr_SetString(PyExc_TypeError, "Incompatible Types");
        return NULL;
    }
    return pyPlasma_convert(*((pyQuat*)left)->fThis + *((pyQuat*)right)->fThis);
}

static PyObject* pyQuat_subtract(PyObject* left, PyObject* right) {
    if (!pyQuat_Check(left) || !pyQuat_Check(right)) {
        PyErr_SetString(PyExc_TypeError, "Incompatible Types");
        return NULL;
    }
    return pyPlasma_convert(*((pyQuat*)left)->fThis - *((pyQuat*)right)->fThis);
}

static PyObject* pyQuat_multiply(PyObject* left, PyObject* right) {
    if (pyQuat_Check(left)) {
        if (pyQuat_Check(right)) {
            return pyPlasma_convert(*((pyQuat*)left)->fThis * *((pyQuat*)right)->fThis);
        } else if (PyFloat_Check(right)) {
            return pyPlasma_convert(*((pyQuat*)left)->fThis * PyFloat_AsDouble(right));
        } else {
            PyErr_SetString(PyExc_TypeError, "Incompatible Types");
            return NULL;
        }
    } else if (pyQuat_Check(right)) {
        if (PyFloat_Check(left)) {
            return pyPlasma_convert(*((pyQuat*)right)->fThis * PyFloat_AsDouble(left));
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
    return pyPlasma_convert(hsQuat(-(self->fThis->X), -(self->fThis->Y),
                                   -(self->fThis->Z), -(self->fThis->W)));
}

static PyObject* pyQuat_positive(pyQuat* self) {
    return pyPlasma_convert(hsQuat(+(self->fThis->X), +(self->fThis->Y),
                                   +(self->fThis->Z), +(self->fThis->W)));
}

static PyObject* pyQuat_absolute(pyQuat* self) {
    return pyPlasma_convert(hsQuat(fabs(self->fThis->X),
                                   fabs(self->fThis->Y),
                                   fabs(self->fThis->Z),
                                   fabs(self->fThis->W)));
}

static int pyQuat_nonzero(pyQuat* self) {
    return (self->fThis->X != 0.0f) || (self->fThis->Y != 0.0f)
        || (self->fThis->Z != 0.0f) || (self->fThis->W != 0.0f);
}

static PyObject* pyQuat_Identity(PyObject*) {
    return pyPlasma_convert(hsQuat::Identity());
}

static PyObject* pyQuat_conjugate(pyQuat* self) {
    return pyPlasma_convert(self->fThis->conjugate());
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
    Py_RETURN_NONE;
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
    Py_RETURN_NONE;
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
#if ((PY_MAJOR_VERSION > 3) || (PY_MAJOR_VERSION == 3 && PY_MINOR_VERSION >= 5))
    NULL,                               /* nb_matrix_multiply */
    NULL,                               /* nb_inplace_matrix_multiply */
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

PY_PROPERTY_MEMBER(float, Quat, X, X)
PY_PROPERTY_MEMBER(float, Quat, Y, Y)
PY_PROPERTY_MEMBER(float, Quat, Z, Z)
PY_PROPERTY_MEMBER(float, Quat, W, W)

PyGetSetDef pyQuat_GetSet[] = {
    pyQuat_X_getset,
    pyQuat_Y_getset,
    pyQuat_Z_getset,
    pyQuat_W_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyQuat_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.hsQuat",                /* tp_name */
    sizeof(pyQuat),                     /* tp_basicsize */
    0,                                  /* tp_itemsize */

    pyQuat_dealloc,                     /* tp_dealloc */
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

    pyQuat___init__,                    /* tp_init */
    NULL,                               /* tp_alloc */
    pyQuat_new,                         /* tp_new */
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

PyObject* Init_pyQuat_Type() {
    if (PyType_Ready(&pyQuat_Type) < 0)
        return NULL;

    Py_INCREF(&pyQuat_Type);
    return (PyObject*)&pyQuat_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(Quat, hsQuat)

}
