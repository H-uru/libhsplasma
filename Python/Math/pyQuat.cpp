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
#include <string_theory/format>

PY_PLASMA_VALUE_DEALLOC(Quat)

PY_PLASMA_INIT_DECL(Quat)
{
    float x = 0.0f, y = 0.0f, z = 0.0f, w = 0.0f;
    PyObject* init = nullptr;
    static char* kwlist[] = { _pycs("X"), _pycs("Y"), _pycs("Z"), _pycs("W"), nullptr };
    static char* kwlist2[] = { _pycs("quat"), nullptr };
    static char* kwlist3[] = { _pycs("angle"), _pycs("axis"), nullptr };

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
        if (init == nullptr) {
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

PY_PLASMA_REPR_DECL(Quat)
{
    ST::string repr = ST::format("hsQuat({f}, {f}, {f}, {f})",
             self->fThis->X, self->fThis->Y, self->fThis->Z, self->fThis->W);
    return pyPlasma_convert(repr);
}

PY_PLASMA_NB_BINARYFUNC_DECL(Quat, add)
{
    if (!pyQuat_Check(left) || !pyQuat_Check(right)) {
        PyErr_SetString(PyExc_TypeError, "Incompatible Types");
        return nullptr;
    }
    return pyPlasma_convert(pyPlasma_get<hsQuat>(left) + pyPlasma_get<hsQuat>(right));
}

PY_PLASMA_NB_BINARYFUNC_DECL(Quat, subtract)
{
    if (!pyQuat_Check(left) || !pyQuat_Check(right)) {
        PyErr_SetString(PyExc_TypeError, "Incompatible Types");
        return nullptr;
    }
    return pyPlasma_convert(pyPlasma_get<hsQuat>(left) - pyPlasma_get<hsQuat>(right));
}

PY_PLASMA_NB_BINARYFUNC_DECL(Quat, multiply)
{
    if (pyQuat_Check(left)) {
        if (pyQuat_Check(right)) {
            return pyPlasma_convert(pyPlasma_get<hsQuat>(left) * pyPlasma_get<hsQuat>(right));
        } else if (pyPlasma_check<float>(right)) {
            return pyPlasma_convert(pyPlasma_get<hsQuat>(left) * pyPlasma_get<float>(right));
        } else {
            PyErr_SetString(PyExc_TypeError, "Incompatible Types");
            return nullptr;
        }
    } else if (pyQuat_Check(right)) {
        if (pyPlasma_check<float>(left)) {
            return pyPlasma_convert(pyPlasma_get<hsQuat>(right) * pyPlasma_get<float>(left));
        } else {
            PyErr_SetString(PyExc_TypeError, "Incompatible Types");
            return nullptr;
        }
    } else {
        PyErr_SetString(PyExc_TypeError, "This should not happen");
        return nullptr;
    }
}

PY_PLASMA_NB_UNARYFUNC_DECL(Quat, negative)
{
    return pyPlasma_convert(hsQuat(-(self->fThis->X), -(self->fThis->Y),
                                   -(self->fThis->Z), -(self->fThis->W)));
}

PY_PLASMA_NB_UNARYFUNC_DECL(Quat, positive)
{
    return pyPlasma_convert(hsQuat(+(self->fThis->X), +(self->fThis->Y),
                                   +(self->fThis->Z), +(self->fThis->W)));
}

PY_PLASMA_NB_UNARYFUNC_DECL(Quat, absolute)
{
    return pyPlasma_convert(hsQuat(fabs(self->fThis->X),
                                   fabs(self->fThis->Y),
                                   fabs(self->fThis->Z),
                                   fabs(self->fThis->W)));
}

PY_PLASMA_NB_INQUIRY_DECL(Quat, nonzero)
{
    return (self->fThis->X != 0.0f) || (self->fThis->Y != 0.0f)
        || (self->fThis->Z != 0.0f) || (self->fThis->W != 0.0f);
}

PY_METHOD_STATIC_NOARGS(Quat, Identity, "Returns an identity quaternion")
{
    return pyPlasma_convert(hsQuat::Identity());
}

PY_METHOD_NOARGS(Quat, conjugate, "Returns the conjugate of the quaternion")
{
    return pyPlasma_convert(self->fThis->conjugate());
}

PY_METHOD_VA(Quat, read,
    "Params: stream\n"
    "Reads this quat from `stream`")
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

PY_METHOD_VA(Quat, write,
    "Params: stream\n"
    "Writes this quat to `stream`")
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

PyMethodDef pyQuat_Methods[] = {
    pyQuat_Identity_method,
    pyQuat_conjugate_method,
    pyQuat_read_method,
    pyQuat_write_method,
    PY_METHOD_TERMINATOR
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

PY_PLASMA_TYPE(Quat, hsQuat, "Plasma Quaternion")
PY_PLASMA_TYPE_AS_NUMBER(Quat)

PY_PLASMA_TYPE_INIT(Quat)
{
    pyQuat_As_Number.nb_add = pyQuat_nb_add;
    pyQuat_As_Number.nb_subtract = pyQuat_nb_subtract;
    pyQuat_As_Number.nb_multiply = pyQuat_nb_multiply;
    pyQuat_As_Number.nb_negative = pyQuat_nb_negative;
    pyQuat_As_Number.nb_positive = pyQuat_nb_positive;
    pyQuat_As_Number.nb_absolute = pyQuat_nb_absolute;
    pyQuat_As_Number.nb_bool = pyQuat_nb_nonzero;
    pyQuat_Type.tp_dealloc = pyQuat_dealloc;
    pyQuat_Type.tp_init = pyQuat___init__;
    pyQuat_Type.tp_new = pyQuat_new;
    pyQuat_Type.tp_repr = pyQuat_repr;
    pyQuat_Type.tp_as_number = &pyQuat_As_Number;
    pyQuat_Type.tp_methods = pyQuat_Methods;
    pyQuat_Type.tp_getset = pyQuat_GetSet;
    pyQuat_Type.tp_flags |= Py_TPFLAGS_CHECKTYPES;
    if (PyType_CheckAndReady(&pyQuat_Type) < 0)
        return nullptr;

    Py_INCREF(&pyQuat_Type);
    return (PyObject*)&pyQuat_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(Quat, hsQuat)
