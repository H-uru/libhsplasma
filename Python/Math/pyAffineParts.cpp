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

#include <Math/hsAffineParts.h>
#include "Stream/pyStream.h"

PY_PLASMA_VALUE_DEALLOC(AffineParts)
PY_PLASMA_EMPTY_INIT(AffineParts)
PY_PLASMA_VALUE_NEW(AffineParts, hsAffineParts)

PY_METHOD_VA(AffineParts, read,
    "Params: stream\n"
    "Reads this object from `stream`")
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

PY_METHOD_VA(AffineParts, write,
    "Params: stream\n"
    "Writes this object to `stream`")
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

PY_METHOD_NOARGS(AffineParts, reset, "Resets the transform to the identity")
{
    self->fThis->reset();
    Py_RETURN_NONE;
}

PyMethodDef pyAffineParts_Methods[] = {
    pyAffineParts_read_method,
    pyAffineParts_write_method,
    pyAffineParts_reset_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY_MEMBER(int, AffineParts, I, fI)
PY_PROPERTY_MEMBER(hsVector3, AffineParts, T, fT)
PY_PROPERTY_MEMBER(hsQuat, AffineParts, Q, fQ)
PY_PROPERTY_MEMBER(hsQuat, AffineParts, U, fU)
PY_PROPERTY_MEMBER(hsVector3, AffineParts, K, fK)
PY_PROPERTY_MEMBER(float, AffineParts, F, fF)

PyGetSetDef pyAffineParts_GetSet[] = {
    pyAffineParts_I_getset,
    pyAffineParts_T_getset,
    pyAffineParts_Q_getset,
    pyAffineParts_U_getset,
    pyAffineParts_K_getset,
    pyAffineParts_F_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(AffineParts, hsAffineParts, "Plasma 3DS Max AffineParts wrapper");

PY_PLASMA_TYPE_INIT(AffineParts)
{
    pyAffineParts_Type.tp_dealloc = pyAffineParts_dealloc;
    pyAffineParts_Type.tp_init = pyAffineParts___init__;
    pyAffineParts_Type.tp_new = pyAffineParts_new;
    pyAffineParts_Type.tp_methods = pyAffineParts_Methods;
    pyAffineParts_Type.tp_getset = pyAffineParts_GetSet;
    if (PyType_CheckAndReady(&pyAffineParts_Type) < 0)
        return nullptr;

    Py_INCREF(&pyAffineParts_Type);
    return (PyObject*)&pyAffineParts_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(AffineParts, hsAffineParts)
