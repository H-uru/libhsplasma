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

PY_PLASMA_EMPTY_INIT(CompressedQuatKey32)
PY_PLASMA_NEW(CompressedQuatKey32, hsCompressedQuatKey32)

PY_METHOD_VA(CompressedQuatKey32, setValue,
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

static PyMethodDef pyCompressedQuatKey32_Methods[] = {
    pyCompressedQuatKey32_setValue_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY_READ(CompressedQuatKey32, value, getQuat)
PY_PROPERTY_SETTER_MSG(CompressedQuatKey32, value,
                       "To set the compressed quat, use setValue()")
PY_PROPERTY_GETSET_DECL(CompressedQuatKey32, value)

static PyGetSetDef pyCompressedQuatKey32_GetSet[] = {
    pyCompressedQuatKey32_value_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(CompressedQuatKey32, hsCompressedQuatKey32,
               "hsCompressedQuatKey32 wrapper")

PY_PLASMA_TYPE_INIT(CompressedQuatKey32)
{
    pyCompressedQuatKey32_Type.tp_init = pyCompressedQuatKey32___init__;
    pyCompressedQuatKey32_Type.tp_new = pyCompressedQuatKey32_new;
    pyCompressedQuatKey32_Type.tp_methods = pyCompressedQuatKey32_Methods;
    pyCompressedQuatKey32_Type.tp_getset = pyCompressedQuatKey32_GetSet;
    pyCompressedQuatKey32_Type.tp_base = &pyKeyFrame_Type;
    if (PyType_CheckAndReady(&pyCompressedQuatKey32_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(CompressedQuatKey32, "kCompQuatNukeX", hsCompressedQuatKey32::kCompQuatNukeX);
    PY_TYPE_ADD_CONST(CompressedQuatKey32, "kCompQuatNukeY", hsCompressedQuatKey32::kCompQuatNukeY);
    PY_TYPE_ADD_CONST(CompressedQuatKey32, "kCompQuatNukeZ", hsCompressedQuatKey32::kCompQuatNukeZ);
    PY_TYPE_ADD_CONST(CompressedQuatKey32, "kCompQuatNukeW", hsCompressedQuatKey32::kCompQuatNukeW);

    Py_INCREF(&pyCompressedQuatKey32_Type);
    return (PyObject*)&pyCompressedQuatKey32_Type;
}

PY_PLASMA_IFC_METHODS(CompressedQuatKey32, hsCompressedQuatKey32)
