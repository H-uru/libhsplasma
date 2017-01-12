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

extern "C" {

PY_PLASMA_NEW(LogicModifier, plLogicModifier)

PY_METHOD_NOARGS(LogicModifier, clearConditions, "Remove all condition keys") {
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
        return NULL;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addCondition expects a plKey");
        return NULL;
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
        return NULL;
    }
    self->fThis->delCondition(idx);
    Py_RETURN_NONE;
}

static PyObject* pyLogicModifier_getConditions(pyLogicModifier* self, void*) {
    PyObject* list = PyList_New(self->fThis->getConditions().size());
    for (size_t i=0; i<self->fThis->getConditions().size(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getConditions()[i]));
    return list;
}

static int pyLogicModifier_setConditions(pyLogicModifier* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "to add conditions, use addCondition");
    return -1;
}

static PyMethodDef pyLogicModifier_Methods[] = {
    pyLogicModifier_clearConditions_method,
    pyLogicModifier_addCondition_method,
    pyLogicModifier_delCondition_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY(unsigned int, LogicModifier, cursor, getCursor, setCursor)
PY_PROPERTY(plKey, LogicModifier, parent, getParent, setParent)

static PyGetSetDef pyLogicModifier_GetSet[] = {
    { _pycs("conditions"), (getter)pyLogicModifier_getConditions,
        (setter)pyLogicModifier_setConditions, NULL, NULL },
    pyLogicModifier_cursor_getset,
    pyLogicModifier_parent_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(LogicModifier, plLogicModifier, "plLogicModifier wrapper")

PY_PLASMA_TYPE_INIT(LogicModifier) {
    pyLogicModifier_Type.tp_new = pyLogicModifier_new;
    pyLogicModifier_Type.tp_methods = pyLogicModifier_Methods;
    pyLogicModifier_Type.tp_getset = pyLogicModifier_GetSet;
    pyLogicModifier_Type.tp_base = &pyLogicModBase_Type;
    if (PyType_CheckAndReady(&pyLogicModifier_Type) < 0)
        return NULL;

    Py_INCREF(&pyLogicModifier_Type);
    return (PyObject*)&pyLogicModifier_Type;
}

PY_PLASMA_IFC_METHODS(LogicModifier, plLogicModifier)

}
