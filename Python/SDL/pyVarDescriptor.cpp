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

#include "pySDL.h"

#include <SDL/plStateDescriptor.h>

PY_PLASMA_DEALLOC(VarDescriptor)
PY_PLASMA_EMPTY_INIT(VarDescriptor)
PY_PLASMA_NEW(VarDescriptor, plVarDescriptor)

PY_PLASMA_REPR_DECL(VarDescriptor)
{
    return PyString_FromSTString(ST::format("<plVarDescriptor '{}'>", self->fThis->getName()));
}

PY_PLASMA_STR_DECL(VarDescriptor)
{
    return PyString_FromSTString(self->fThis->getName());
}

PY_PROPERTY(ST::string, VarDescriptor, name, getName, setName);
PY_PROPERTY(ST::string, VarDescriptor, default, getDefault, setDefault);
PY_PROPERTY(ST::string, VarDescriptor, display, getDisplay, setDisplay);
PY_PROPERTY(size_t, VarDescriptor, count, getCount, setCount);
PY_PROPERTY(plVarDescriptor::Type, VarDescriptor, type, getType, setType);
PY_PROPERTY(ST::string, VarDescriptor, stateDescType, getStateDescType, setStateDescType)

PY_GETSET_GETTER_DECL(VarDescriptor, stateDesc)
{
    return pyStateDescriptor_FromStateDescriptor(self->fThis->getStateDesc());
}

PY_GETSET_SETTER_DECL(VarDescriptor, stateDesc)
{
    PY_PROPERTY_CHECK_NULL(stateDesc);
    if (!pyStateDescriptor_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "stateDesc should be a plStateDescriptor");
        return -1;
    }

    ((pyStateDescriptor*)value)->fPyOwned = false;
    self->fThis->setStateDesc(((pyStateDescriptor*)value)->fThis);
    return 0;
}

PY_PROPERTY_GETSET_DECL(VarDescriptor, stateDesc);
PY_PROPERTY(bool, VarDescriptor, internal, isInternal, setInternal);
PY_PROPERTY(bool, VarDescriptor, alwaysNew, isAlwaysNew, setAlwaysNew);
PY_PROPERTY(bool, VarDescriptor, variableLength, isVariableLength, setVariableLength);
PY_PROPERTY_RO(VarDescriptor, valid, isValid);

static PyGetSetDef pyVarDescriptor_GetSet[] = {
    pyVarDescriptor_name_getset,
    pyVarDescriptor_default_getset,
    pyVarDescriptor_display_getset,
    pyVarDescriptor_count_getset,
    pyVarDescriptor_type_getset,
    pyVarDescriptor_stateDescType_getset,
    pyVarDescriptor_stateDesc_getset,
    pyVarDescriptor_internal_getset,
    pyVarDescriptor_alwaysNew_getset,
    pyVarDescriptor_variableLength_getset,
    pyVarDescriptor_valid_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(VarDescriptor, plVarDescriptor, "plVarDescriptor wrapper")

PY_PLASMA_TYPE_INIT(VarDescriptor)
{
    pyVarDescriptor_Type.tp_dealloc = pyVarDescriptor_dealloc;
    pyVarDescriptor_Type.tp_init = pyVarDescriptor___init__;
    pyVarDescriptor_Type.tp_new = pyVarDescriptor_new;
    pyVarDescriptor_Type.tp_repr = pyVarDescriptor_repr;
    pyVarDescriptor_Type.tp_str = pyVarDescriptor_str;
    pyVarDescriptor_Type.tp_getset = pyVarDescriptor_GetSet;
    if (PyType_CheckAndReady(&pyVarDescriptor_Type) < 0)
        return nullptr;

    /* Konstants */
    PY_TYPE_ADD_CONST(VarDescriptor, "kNone", plVarDescriptor::kNone);
    PY_TYPE_ADD_CONST(VarDescriptor, "kInt", plVarDescriptor::kInt);
    PY_TYPE_ADD_CONST(VarDescriptor, "kFloat", plVarDescriptor::kFloat);
    PY_TYPE_ADD_CONST(VarDescriptor, "kBool", plVarDescriptor::kBool);
    PY_TYPE_ADD_CONST(VarDescriptor, "kString", plVarDescriptor::kString);
    PY_TYPE_ADD_CONST(VarDescriptor, "kKey", plVarDescriptor::kKey);
    PY_TYPE_ADD_CONST(VarDescriptor, "kStateDescriptor", plVarDescriptor::kStateDescriptor);
    PY_TYPE_ADD_CONST(VarDescriptor, "kCreatable", plVarDescriptor::kCreatable);
    PY_TYPE_ADD_CONST(VarDescriptor, "kDouble", plVarDescriptor::kDouble);
    PY_TYPE_ADD_CONST(VarDescriptor, "kTime", plVarDescriptor::kTime);
    PY_TYPE_ADD_CONST(VarDescriptor, "kByte", plVarDescriptor::kByte);
    PY_TYPE_ADD_CONST(VarDescriptor, "kShort", plVarDescriptor::kShort);
    PY_TYPE_ADD_CONST(VarDescriptor, "kAgeTimeOfDay", plVarDescriptor::kAgeTimeOfDay);
    PY_TYPE_ADD_CONST(VarDescriptor, "kVector3", plVarDescriptor::kVector3);
    PY_TYPE_ADD_CONST(VarDescriptor, "kPoint3", plVarDescriptor::kPoint3);
    PY_TYPE_ADD_CONST(VarDescriptor, "kRGB", plVarDescriptor::kRGB);
    PY_TYPE_ADD_CONST(VarDescriptor, "kRGBA", plVarDescriptor::kRGBA);
    PY_TYPE_ADD_CONST(VarDescriptor, "kQuaternion", plVarDescriptor::kQuaternion);
    PY_TYPE_ADD_CONST(VarDescriptor, "kRGB8", plVarDescriptor::kRGB8);
    PY_TYPE_ADD_CONST(VarDescriptor, "kRGBA8", plVarDescriptor::kRGBA8);
    PY_TYPE_ADD_CONST(VarDescriptor, "kUint", plVarDescriptor::kUint);
    PY_TYPE_ADD_CONST(VarDescriptor, "kChar", plVarDescriptor::kChar);
    PY_TYPE_ADD_CONST(VarDescriptor, "kMatrix44", plVarDescriptor::kMatrix44);
    PY_TYPE_ADD_CONST(VarDescriptor, "kBuffer", plVarDescriptor::kBuffer);
    PY_TYPE_ADD_CONST(VarDescriptor, "kAgeTimeElapsed", plVarDescriptor::kAgeTimeElapsed);
    PY_TYPE_ADD_CONST(VarDescriptor, "kGameTimeElapsed", plVarDescriptor::kGameTimeElapsed);

    Py_INCREF(&pyVarDescriptor_Type);
    return (PyObject*)& pyVarDescriptor_Type;
}

PY_PLASMA_IFC_METHODS(VarDescriptor, plVarDescriptor)
