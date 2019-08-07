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
#include <string_theory/format>

PY_PLASMA_VALUE_DEALLOC(Vector3)

PY_PLASMA_INIT_DECL(Vector3)
{
    float x = 0.0f, y = 0.0f, z = 0.0f;
    PyObject* init = nullptr;
    static char* kwlist[] = { _pycs("X"), _pycs("Y"), _pycs("Z"), nullptr };
    static char* kwlist2[] = { _pycs("vector"), nullptr };

    if (PyArg_ParseTupleAndKeywords(args, kwds, "fff", kwlist, &x, &y, &z)) {
        (*self->fThis) = hsVector3(x, y, z);
    } else if (PyErr_Clear(), PyArg_ParseTupleAndKeywords(args, kwds, "|O", kwlist2, &init)) {
        if (init == nullptr) {
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

PY_PLASMA_REPR_DECL(Vector3)
{
    ST::string repr = ST::format("hsVector3({f}, {f}, {f})",
             self->fThis->X, self->fThis->Y, self->fThis->Z);
    return pyPlasma_convert(repr);
}

PY_PLASMA_NB_BINARYFUNC_DECL(Vector3, add)
{
    if (!pyVector3_Check(left) || !pyVector3_Check(right)) {
        PyErr_SetString(PyExc_TypeError, "Incompatible Types");
        return nullptr;
    }
    return pyPlasma_convert(pyPlasma_get<hsVector3>(left) + pyPlasma_get<hsVector3>(right));
}

PY_PLASMA_NB_BINARYFUNC_DECL(Vector3, subtract)
{
    if (!pyVector3_Check(left) || !pyVector3_Check(right)) {
        PyErr_SetString(PyExc_TypeError, "Incompatible Types");
        return nullptr;
    }
    return pyPlasma_convert(pyPlasma_get<hsVector3>(left) - pyPlasma_get<hsVector3>(right));
}

PY_PLASMA_NB_BINARYFUNC_DECL(Vector3, multiply)
{
    if (pyVector3_Check(left)) {
        if (pyVector3_Check(right)) {
            PyErr_SetString(PyExc_TypeError, "Vector Multiplication should use dotP and crossP");
            return nullptr;
        } else if (pyPlasma_check<float>(right)) {
            return pyPlasma_convert(pyPlasma_get<hsVector3>(left) * pyPlasma_get<float>(right));
        } else {
            PyErr_SetString(PyExc_TypeError, "Incompatible Types");
            return nullptr;
        }
    } else if (pyVector3_Check(right)) {
        if (pyPlasma_check<float>(left)) {
            return pyPlasma_convert(pyPlasma_get<hsVector3>(right) * pyPlasma_get<float>(left));
        } else {
            PyErr_SetString(PyExc_TypeError, "Incompatible Types");
            return nullptr;
        }
    } else {
        PyErr_SetString(PyExc_TypeError, "This should not happen");
        return nullptr;
    }
}

PY_PLASMA_NB_UNARYFUNC_DECL(Vector3, negative)
{
    return pyPlasma_convert(hsVector3(-(self->fThis->X), -(self->fThis->Y),
                                      -(self->fThis->Z)));
}

PY_PLASMA_NB_UNARYFUNC_DECL(Vector3, positive)
{
    return pyPlasma_convert(hsVector3(+(self->fThis->X), +(self->fThis->Y),
                                      +(self->fThis->Z)));
}

PY_PLASMA_NB_UNARYFUNC_DECL(Vector3, absolute)
{
    return pyPlasma_convert(hsVector3(fabs(self->fThis->X),
                                      fabs(self->fThis->Y),
                                      fabs(self->fThis->Z)));
}

PY_PLASMA_NB_INQUIRY_DECL(Vector3, nonzero)
{
    return (self->fThis->X != 0.0f) || (self->fThis->Y != 0.0f)
        || (self->fThis->Z != 0.0f);
}

PY_METHOD_NOARGS(Vector3, magnitude, "Returns the magnitude of the vector")
{
    return pyPlasma_convert(self->fThis->magnitude());
}

PY_METHOD_NOARGS(Vector3, normalize, "Normalizes the vector")
{
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
        return nullptr;
    }
    if (!pyVector3_Check((PyObject*)vec)) {
        PyErr_SetString(PyExc_TypeError, "dotP expects an hsVector3");
        return nullptr;
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
        return nullptr;
    }
    if (!pyVector3_Check((PyObject*)vec)) {
        PyErr_SetString(PyExc_TypeError, "crossP expects an hsVector3");
        return nullptr;
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
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects a hsStream");
        return nullptr;
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
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects a hsStream");
        return nullptr;
    }
    self->fThis->write(stream->fThis);
    Py_RETURN_NONE;
}

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

PY_PLASMA_TYPE(Vector3, hsVector3, "hsVector3/hsPoint3 wrapper")
PY_PLASMA_TYPE_AS_NUMBER(Vector3)

PY_PLASMA_TYPE_INIT(Vector3)
{
    pyVector3_As_Number.nb_add = pyVector3_nb_add;
    pyVector3_As_Number.nb_subtract = pyVector3_nb_subtract;
    pyVector3_As_Number.nb_multiply = pyVector3_nb_multiply;
    pyVector3_As_Number.nb_negative = pyVector3_nb_negative;
    pyVector3_As_Number.nb_positive = pyVector3_nb_positive;
    pyVector3_As_Number.nb_absolute = pyVector3_nb_absolute;
    pyVector3_As_Number.nb_bool = pyVector3_nb_nonzero;
    pyVector3_Type.tp_dealloc = pyVector3_dealloc;
    pyVector3_Type.tp_init = pyVector3___init__;
    pyVector3_Type.tp_new = pyVector3_new;
    pyVector3_Type.tp_repr = pyVector3_repr;
    pyVector3_Type.tp_as_number = &pyVector3_As_Number;
    pyVector3_Type.tp_methods = pyVector3_Methods;
    pyVector3_Type.tp_getset = pyVector3_GetSet;
    pyVector3_Type.tp_flags |= Py_TPFLAGS_CHECKTYPES;
    if (PyType_CheckAndReady(&pyVector3_Type) < 0)
        return nullptr;

    Py_INCREF(&pyVector3_Type);
    return (PyObject*)&pyVector3_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(Vector3, hsVector3)
