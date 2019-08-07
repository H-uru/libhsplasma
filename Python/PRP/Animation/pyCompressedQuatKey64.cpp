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

#include "pyKeys.h"

#include <PRP/Animation/hsKeys.h>
#include "Math/pyGeometry3.h"

PY_PLASMA_EMPTY_INIT(CompressedQuatKey64)
PY_PLASMA_NEW(CompressedQuatKey64, hsCompressedQuatKey64)

PY_METHOD_VA(CompressedQuatKey64, setValue,
    "Params: quat, type\n"
    "Set the hsQuat data.  Type is the compression nuking to use")
{
    pyQuat* value;
    int type;
    if (!PyArg_ParseTuple(args, "Oi", &value, &type)) {
        PyErr_SetString(PyExc_TypeError, "setValue expects hsQuat, int");
        return nullptr;
    }
    if (!pyQuat_Check((PyObject*)value)) {
        PyErr_SetString(PyExc_TypeError, "setValue expects hsQuat, int");
        return nullptr;
    }
    self->fThis->setQuat(*value->fThis, type);
    Py_RETURN_NONE;
}

static PyMethodDef pyCompressedQuatKey64_Methods[] = {
    pyCompressedQuatKey64_setValue_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY_READ(CompressedQuatKey64, value, getQuat)
PY_PROPERTY_SETTER_MSG(CompressedQuatKey64, value,
                       "To set the compressed quat, use setValue()")
PY_PROPERTY_GETSET_DECL(CompressedQuatKey64, value)

static PyGetSetDef pyCompressedQuatKey64_GetSet[] = {
    pyCompressedQuatKey64_value_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(CompressedQuatKey64, hsCompressedQuatKey64,
               "hsCompressedQuatKey64 wrapper")

PY_PLASMA_TYPE_INIT(CompressedQuatKey64)
{
    pyCompressedQuatKey64_Type.tp_init = pyCompressedQuatKey64___init__;
    pyCompressedQuatKey64_Type.tp_new = pyCompressedQuatKey64_new;
    pyCompressedQuatKey64_Type.tp_methods = pyCompressedQuatKey64_Methods;
    pyCompressedQuatKey64_Type.tp_getset = pyCompressedQuatKey64_GetSet;
    pyCompressedQuatKey64_Type.tp_base = &pyKeyFrame_Type;
    if (PyType_CheckAndReady(&pyCompressedQuatKey64_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(CompressedQuatKey64, "kCompQuatNukeX", hsCompressedQuatKey64::kCompQuatNukeX);
    PY_TYPE_ADD_CONST(CompressedQuatKey64, "kCompQuatNukeY", hsCompressedQuatKey64::kCompQuatNukeY);
    PY_TYPE_ADD_CONST(CompressedQuatKey64, "kCompQuatNukeZ", hsCompressedQuatKey64::kCompQuatNukeZ);
    PY_TYPE_ADD_CONST(CompressedQuatKey64, "kCompQuatNukeW", hsCompressedQuatKey64::kCompQuatNukeW);

    Py_INCREF(&pyCompressedQuatKey64_Type);
    return (PyObject*)&pyCompressedQuatKey64_Type;
}

PY_PLASMA_IFC_METHODS(CompressedQuatKey64, hsCompressedQuatKey64)
