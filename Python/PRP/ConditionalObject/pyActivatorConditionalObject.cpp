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

#include "pyActivatorConditionalObject.h"

#include <PRP/ConditionalObject/plActivatorConditionalObject.h>
#include "pyConditionalObject.h"
#include "PRP/pyCreatable.h"
#include "PRP/KeyedObject/pyKey.h"

PY_PLASMA_NEW(ActivatorConditionalObject, plActivatorConditionalObject)

PY_METHOD_VA(ActivatorConditionalObject, addActivator,
    "Params: key\n"
    "Adds an activator key")
{
    PyObject* key;
    if (!(PyArg_ParseTuple(args, "O", &key) && pyKey_Check(key))) {
        PyErr_SetString(PyExc_TypeError, "addActivator expects a plKey");
        return nullptr;
    }
    self->fThis->addActivator(*((pyKey*)key)->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(ActivatorConditionalObject, clearActivators,
    "Removes all activator keys")
{
    self->fThis->clearActivators();
    Py_RETURN_NONE;
}

PY_METHOD_VA(ActivatorConditionalObject, delActivator,
    "Params: idx\n"
    "Removes an activator key")
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delActivator expects an int");
        return nullptr;
    }
    self->fThis->delActivator((size_t)idx);
    Py_RETURN_NONE;
}

static PyMethodDef pyActivatorConditionalObject_Methods[] = {
    pyActivatorConditionalObject_addActivator_method,
    pyActivatorConditionalObject_clearActivators_method,
    pyActivatorConditionalObject_delActivator_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(ActivatorConditionalObject, activators)
{
    plActivatorConditionalObject* act = self->fThis;
    PyObject* activators = PyTuple_New(act->getActivators().size());
    for (size_t i = 0; i < act->getActivators().size(); ++i)
        PyTuple_SET_ITEM(activators, i, pyKey_FromKey(act->getActivators()[i]));
    return activators;
}

PY_PROPERTY_SETTER_MSG(ActivatorConditionalObject, activators,
                       "To add activators, use addActivator()")
PY_PROPERTY_GETSET_DECL(ActivatorConditionalObject, activators)

static PyGetSetDef pyActivatorConditionalObject_GetSet[] = {
    pyActivatorConditionalObject_activators_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ActivatorConditionalObject, plActivatorConditionalObject,
               "plActivatorConditionalObject wrapper")

PY_PLASMA_TYPE_INIT(ActivatorConditionalObject)
{
    pyActivatorConditionalObject_Type.tp_new = pyActivatorConditionalObject_new;
    pyActivatorConditionalObject_Type.tp_methods = pyActivatorConditionalObject_Methods;
    pyActivatorConditionalObject_Type.tp_getset = pyActivatorConditionalObject_GetSet;
    pyActivatorConditionalObject_Type.tp_base = &pyConditionalObject_Type;
    if (PyType_CheckAndReady(&pyActivatorConditionalObject_Type) < 0)
        return nullptr;

    Py_INCREF(&pyActivatorConditionalObject_Type);
    return (PyObject*)&pyActivatorConditionalObject_Type;
}

PY_PLASMA_IFC_METHODS(ActivatorConditionalObject, plActivatorConditionalObject)
