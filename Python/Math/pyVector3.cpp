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

#include <Math/hsGeometry3.h>
#include "Stream/pyStream.h"

extern "C" {

PY_PLASMA_VALUE_DEALLOC(Vector3)

PY_PLASMA_INIT_DECL(Vector3) {
    float x = 0.0f, y = 0.0f, z = 0.0f;
    PyObject* init = NULL;
    static char* kwlist[] = { _pycs("X"), _pycs("Y"), _pycs("Z"), NULL };
    static char* kwlist2[] = { _pycs("vector"), NULL };

    if (PyArg_ParseTupleAndKeywords(args, kwds, "fff", kwlist, &x, &y, &z)) {
        (*self->fThis) = hsVector3(x, y, z);
    } else if (PyErr_Clear(), PyArg_ParseTupleAndKeywords(args, kwds, "|O", kwlist2, &init)) {
        if (init == NULL) {
            (*self->fThis) = hsVector3();
            return 0;
        }
        if (pyVector3_Check(init)) {
            (*self->fThis) = pyPlasma_get<hsVector3>(init);
        } else {
            PyErr_SetString(PyExc_TypeError, "__init__ expects a vector");
            return -1;
        }
    } else {
        return -1;
    }

    return 0;
}

PY_PLASMA_VALUE_NEW(Vector3, hsVector3)

static PyObject* pyVector3_Repr(pyVector3* self) {
    plString repr = plString::Format("hsVector3(%f, %f, %f)",
             self->fThis->X, self->fThis->Y, self->fThis->Z);
    return pyPlasma_convert(repr);
}

static PyObject* pyVector3_add(PyObject* left, PyObject* right) {
    if (!pyVector3_Check(left) || !pyVector3_Check(right)) {
        PyErr_SetString(PyExc_TypeError, "Incompatible Types");
        return NULL;
    }
    return pyPlasma_convert(*((pyVector3*)left)->fThis + *((pyVector3*)right)->fThis);
}

static PyObject* pyVector3_subtract(PyObject* left, PyObject* right) {
    if (!pyVector3_Check(left) || !pyVector3_Check(right)) {
        PyErr_SetString(PyExc_TypeError, "Incompatible Types");
        return NULL;
    }
    return pyPlasma_convert(*((pyVector3*)left)->fThis - *((pyVector3*)right)->fThis);
}

static PyObject* pyVector3_multiply(PyObject* left, PyObject* right) {
    if (pyVector3_Check(left)) {
        if (pyVector3_Check(right)) {
            PyErr_SetString(PyExc_TypeError, "Vector Multiplication should use dotP and crossP");
            return NULL;
        } else if (PyFloat_Check(right)) {
            return pyPlasma_convert(*((pyVector3*)left)->fThis * PyFloat_AsDouble(right));
        } else {
            PyErr_SetString(PyExc_TypeError, "Incompatible Types");
            return NULL;
        }
    } else if (pyVector3_Check(right)) {
        if (PyFloat_Check(left)) {
            return pyPlasma_convert(*((pyVector3*)right)->fThis * PyFloat_AsDouble(left));
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
    return pyPlasma_convert(hsVector3(-(self->fThis->X), -(self->fThis->Y),
                                      -(self->fThis->Z)));
}

static PyObject* pyVector3_positive(pyVector3* self) {
    return pyPlasma_convert(hsVector3(+(self->fThis->X), +(self->fThis->Y),
                                      +(self->fThis->Z)));
}

static PyObject* pyVector3_absolute(pyVector3* self) {
    return pyPlasma_convert(hsVector3(fabs(self->fThis->X),
                                      fabs(self->fThis->Y),
                                      fabs(self->fThis->Z)));
}

static int pyVector3_nonzero(pyVector3* self) {
    return (self->fThis->X != 0.0f) || (self->fThis->Y != 0.0f)
        || (self->fThis->Z != 0.0f);
}

PY_METHOD_NOARGS(Vector3, magnitude, "Returns the magnitude of the vector") {
    return pyPlasma_convert(self->fThis->magnitude());
}

PY_METHOD_NOARGS(Vector3, normalize, "Normalizes the vector") {
    self->fThis->normalize();
    Py_RETURN_NONE;
}

PY_METHOD_VA(Vector3, dotP,
    "Params: vec\n"
    "Returns the dot product of this vector and `vec`")
{
    pyVector3* vec;
    if (!PyArg_ParseTuple(args, "O", &vec)) {
        PyErr_SetString(PyExc_TypeError, "dotP expects an hsVector3");
        return NULL;
    }
    if (!pyVector3_Check((PyObject*)vec)) {
        PyErr_SetString(PyExc_TypeError, "dotP expects an hsVector3");
        return NULL;
    }
    return pyPlasma_convert(self->fThis->dotP(*vec->fThis));
}

PY_METHOD_VA(Vector3, crossP,
    "Params: vec\n"
    "Returns the cross product of this vector and `vec`")
{
    pyVector3* vec;
    if (!PyArg_ParseTuple(args, "O", &vec)) {
        PyErr_SetString(PyExc_TypeError, "crossP expects an hsVector3");
        return NULL;
    }
    if (!pyVector3_Check((PyObject*)vec)) {
        PyErr_SetString(PyExc_TypeError, "crossP expects an hsVector3");
        return NULL;
    }
    return pyPlasma_convert(self->fThis->crossP(*vec->fThis));
}

PY_METHOD_VA(Vector3, read,
    "Params: stream\n"
    "Reads this vector from `stream`")
{
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

PY_METHOD_VA(Vector3, write,
    "Params: stream\n"
    "Writes this vector to `stream`")
{
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
#if ((PY_MAJOR_VERSION > 3) || (PY_MAJOR_VERSION == 3 && PY_MINOR_VERSION >= 5))
    NULL,                               /* nb_matrix_multiply */
    NULL,                               /* nb_inplace_matrix_multiply */
#endif
};

PyMethodDef pyVector3_Methods[] = {
    pyVector3_magnitude_method,
    pyVector3_normalize_method,
    pyVector3_dotP_method,
    pyVector3_crossP_method,
    pyVector3_read_method,
    pyVector3_write_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY_MEMBER(float, Vector3, X, X)
PY_PROPERTY_MEMBER(float, Vector3, Y, Y)
PY_PROPERTY_MEMBER(float, Vector3, Z, Z)

PyGetSetDef pyVector3_GetSet[] = {
    pyVector3_X_getset,
    pyVector3_Y_getset,
    pyVector3_Z_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyVector3_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.hsVector3",             /* tp_name */
    sizeof(pyVector3),                  /* tp_basicsize */
    0,                                  /* tp_itemsize */

    pyVector3_dealloc,                  /* tp_dealloc */
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

    pyVector3___init__,                 /* tp_init */
    NULL,                               /* tp_alloc */
    pyVector3_new,                      /* tp_new */
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

PyObject* Init_pyVector3_Type() {
    if (PyType_Ready(&pyVector3_Type) < 0)
        return NULL;

    Py_INCREF(&pyVector3_Type);
    return (PyObject*)&pyVector3_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(Vector3, hsVector3)

}
