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

#include "pyInterfaceInfoModifier.h"

#include <PRP/Modifier/plInterfaceInfoModifier.h>
#include "PRP/Modifier/pyModifier.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW(InterfaceInfoModifier, plInterfaceInfoModifier)

PY_METHOD_NOARGS(InterfaceInfoModifier, clearIntfKeys, "Remove all interface keys")
{
    self->fThis->clearIntfKeys();
    Py_RETURN_NONE;
}

PY_METHOD_VA(InterfaceInfoModifier, addIntfKey,
    "Params: key\n"
    "Add an interface key")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addIntfKey expects a plKey");
        return nullptr;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addIntfKey expects a plKey");
        return nullptr;
    }
    self->fThis->addIntfKey(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(InterfaceInfoModifier, delIntfKey,
    "Params: idx\n"
    "Remove an interface key" )
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delIntfKey expects an int");
        return nullptr;
    }
    self->fThis->delIntfKey(idx);
    Py_RETURN_NONE;
}

static PyMethodDef pyInterfaceInfoModifier_Methods[] = {
    pyInterfaceInfoModifier_clearIntfKeys_method,
    pyInterfaceInfoModifier_addIntfKey_method,
    pyInterfaceInfoModifier_delIntfKey_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(InterfaceInfoModifier, intfKeys)
{
    PyObject* list = PyTuple_New(self->fThis->getIntfKeys().size());
    for (size_t i=0; i<self->fThis->getIntfKeys().size(); i++)
        PyTuple_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getIntfKeys()[i]));
    return list;
}

PY_PROPERTY_SETTER_MSG(InterfaceInfoModifier, intfKeys, "To add interface keys, use addIntfKey")
PY_PROPERTY_GETSET_DECL(InterfaceInfoModifier, intfKeys)

static PyGetSetDef pyInterfaceInfoModifier_GetSet[] = {
    pyInterfaceInfoModifier_intfKeys_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(InterfaceInfoModifier, plInterfaceInfoModifier,
               "plInterfaceInfoModifier wrapper")

PY_PLASMA_TYPE_INIT(InterfaceInfoModifier)
{
    pyInterfaceInfoModifier_Type.tp_new = pyInterfaceInfoModifier_new;
    pyInterfaceInfoModifier_Type.tp_methods = pyInterfaceInfoModifier_Methods;
    pyInterfaceInfoModifier_Type.tp_getset = pyInterfaceInfoModifier_GetSet;
    pyInterfaceInfoModifier_Type.tp_base = &pySingleModifier_Type;
    if (PyType_CheckAndReady(&pyInterfaceInfoModifier_Type) < 0)
        return nullptr;

    Py_INCREF(&pyInterfaceInfoModifier_Type);
    return (PyObject*)&pyInterfaceInfoModifier_Type;
}

PY_PLASMA_IFC_METHODS(InterfaceInfoModifier, plInterfaceInfoModifier)
