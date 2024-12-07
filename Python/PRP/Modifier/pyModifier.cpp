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

#include "pyModifier.h"

#include <PRP/Modifier/plModifier.h>
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/Object/pySynchedObject.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW_MSG(Modifier, "plModifier is abstract")

PY_METHOD_VA(Modifier, addTarget,
    "Params: key\n"
    "Add referenced scene object")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addTarget expects a plKey");
        return nullptr;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addTarget expects a plKey");
        return nullptr;
    }
    self->fThis->addTarget(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(Modifier, removeTarget,
    "Params: key\n"
    "Remove scene object from target list")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "removeTarget expects a plKey");
        return nullptr;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "removeTarget expects a plKey");
        return nullptr;
    }
    self->fThis->removeTarget(*key->fThis);
    Py_RETURN_NONE;
}

static PyMethodDef pyModifier_Methods[] = {
    pyModifier_addTarget_method,
    pyModifier_removeTarget_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(Modifier, targets)
{
    PyObject* tup = PyTuple_New(self->fThis->getTargetsCount());
    for (size_t i = 0; i < self->fThis->getTargetsCount(); ++i)
        PyTuple_SET_ITEM(tup, i, pyPlasma_convert(self->fThis->getTarget(i)));
    return tup;
}

PY_PROPERTY_SETTER_MSG(Modifier, targets, "To add targets, use addTarget()")
PY_PROPERTY_GETSET_DECL(Modifier, targets)

static PyGetSetDef pyModifier_GetSet[] = {
    pyModifier_targets_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(Modifier, plModifier, "plModifier wrapper")

PY_PLASMA_TYPE_INIT(Modifier)
{
    pyModifier_Type.tp_new = pyModifier_new;
    pyModifier_Type.tp_methods = pyModifier_Methods;
    pyModifier_Type.tp_getset = pyModifier_GetSet;
    pyModifier_Type.tp_base = &pySynchedObject_Type;
    if (PyType_CheckAndReady(&pyModifier_Type) < 0)
        return nullptr;

    Py_INCREF(&pyModifier_Type);
    return (PyObject*)&pyModifier_Type;
}

PY_PLASMA_IFC_METHODS(Modifier, plModifier)
