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

#include "pySittingModifier.h"

#include <PRP/Avatar/plSittingModifier.h>
#include "PRP/Modifier/pyModifier.h"
#include "PRP/KeyedObject/pyKey.h"

PY_PLASMA_NEW(SittingModifier, plSittingModifier)

PY_METHOD_VA(SittingModifier, addNotifyKey,
    "Params: key\n"
    "Adds a LogicMod notify key")
{
    PyObject* key;
    if (!(PyArg_ParseTuple(args, "O", &key) && pyKey_Check(key))) {
        PyErr_SetString(PyExc_TypeError, "addNotifyKey expects a plKey");
        return nullptr;
    }
    self->fThis->addNotifyKey(*((pyKey*)key)->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(SittingModifier, clearNotifyKeys, "Removes all LogicMod notify keys")
{
    self->fThis->clearNotifyKeys();
    Py_RETURN_NONE;
}

PY_METHOD_VA(SittingModifier, delNotifyKey,
    "Params: idx\n"
    "Removes a LogicMod notify key")
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delNotifyKey expects an int");
        return nullptr;
    }
    self->fThis->delNotifyKey((size_t)idx);
    Py_RETURN_NONE;
}

static PyMethodDef pySittingModifier_Methods[] = {
    pySittingModifier_addNotifyKey_method,
    pySittingModifier_clearNotifyKeys_method,
    pySittingModifier_delNotifyKey_method,
    PY_METHOD_TERMINATOR
};


PY_PROPERTY(uint8_t, SittingModifier, miscFlags, getMiscFlags, setMiscFlags)
PY_PROPERTY_VECTOR(plKey, SittingModifier, notifyKeys, getNotifyKeys, setNotifyKeys)

static PyGetSetDef pySittingModifier_GetSet[] = {
    pySittingModifier_miscFlags_getset,
    pySittingModifier_notifyKeys_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(SittingModifier, plSittingModifier, "plSittingModifier wrapper")

PY_PLASMA_TYPE_INIT(SittingModifier)
{
    pySittingModifier_Type.tp_new = pySittingModifier_new;
    pySittingModifier_Type.tp_methods = pySittingModifier_Methods;
    pySittingModifier_Type.tp_getset = pySittingModifier_GetSet;
    pySittingModifier_Type.tp_base = &pySingleModifier_Type;
    if (PyType_CheckAndReady(&pySittingModifier_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(SittingModifier, "kApproachFront", plSittingModifier::kApproachFront);
    PY_TYPE_ADD_CONST(SittingModifier, "kApproachLeft", plSittingModifier::kApproachLeft);
    PY_TYPE_ADD_CONST(SittingModifier, "kApproachRight", plSittingModifier::kApproachRight);
    PY_TYPE_ADD_CONST(SittingModifier, "kApproachRear", plSittingModifier::kApproachRear);
    PY_TYPE_ADD_CONST(SittingModifier, "kApproachMask", plSittingModifier::kApproachMask);
    PY_TYPE_ADD_CONST(SittingModifier, "kDisableForward", plSittingModifier::kDisableForward);

    Py_INCREF(&pySittingModifier_Type);
    return (PyObject*)&pySittingModifier_Type;
}

PY_PLASMA_IFC_METHODS(SittingModifier, plSittingModifier)
