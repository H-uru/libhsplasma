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

#include "pyLogicModifier.h"

#include <PRP/Modifier/plLogicModifier.h>
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW(LogicModifier, plLogicModifier)

PY_METHOD_NOARGS(LogicModifier, clearConditions, "Remove all condition keys")
{
    self->fThis->clearConditions();
    Py_RETURN_NONE;
}

PY_METHOD_VA(LogicModifier, addCondition,
    "Params: key\n"
    "Add a condition key")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addCondition expects a plKey");
        return nullptr;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addCondition expects a plKey");
        return nullptr;
    }
    self->fThis->addCondition(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(LogicModifier, delCondition,
    "Params: idx\n"
    "Remove a condition key")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delCondition expects an int");
        return nullptr;
    }
    self->fThis->delCondition(idx);
    Py_RETURN_NONE;
}

static PyMethodDef pyLogicModifier_Methods[] = {
    pyLogicModifier_clearConditions_method,
    pyLogicModifier_addCondition_method,
    pyLogicModifier_delCondition_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(LogicModifier, conditions)
{
    PyObject* list = PyTuple_New(self->fThis->getConditions().size());
    for (size_t i=0; i<self->fThis->getConditions().size(); i++)
        PyTuple_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getConditions()[i]));
    return list;
}

PY_PROPERTY_SETTER_MSG(LogicModifier, conditions, "To add conditions, use addCondition")
PY_PROPERTY_GETSET_DECL(LogicModifier, conditions)

PY_PROPERTY(unsigned int, LogicModifier, cursor, getCursor, setCursor)
PY_PROPERTY(plKey, LogicModifier, parent, getParent, setParent)

static PyGetSetDef pyLogicModifier_GetSet[] = {
    pyLogicModifier_conditions_getset,
    pyLogicModifier_cursor_getset,
    pyLogicModifier_parent_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(LogicModifier, plLogicModifier, "plLogicModifier wrapper")

PY_PLASMA_TYPE_INIT(LogicModifier)
{
    pyLogicModifier_Type.tp_new = pyLogicModifier_new;
    pyLogicModifier_Type.tp_methods = pyLogicModifier_Methods;
    pyLogicModifier_Type.tp_getset = pyLogicModifier_GetSet;
    pyLogicModifier_Type.tp_base = &pyLogicModBase_Type;
    if (PyType_CheckAndReady(&pyLogicModifier_Type) < 0)
        return nullptr;

    Py_INCREF(&pyLogicModifier_Type);
    return (PyObject*)&pyLogicModifier_Type;
}

PY_PLASMA_IFC_METHODS(LogicModifier, plLogicModifier)
