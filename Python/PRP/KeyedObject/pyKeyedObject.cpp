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

#include "pyKeyedObject.h"

#include <PRP/KeyedObject/hsKeyedObject.h>
#include "pyKey.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_INIT_DECL(KeyedObject)
{
    const char* name = "";
    if (!PyArg_ParseTuple(args, "|s", &name)) {
        PyErr_SetString(PyExc_TypeError, "__init__ expects an optional string");
        return -1;
    }

    self->fThis->init(name);
    return 0;
}

PY_PLASMA_NEW_MSG(KeyedObject, "hsKeyedObject is abstract")

PY_METHOD_VA(KeyedObject, orderAfter,
    "Params: otherObj\n"
    "Returns True if this object be ordered after otherObj")
{
    pyKeyedObject* other;
    if (!PyArg_ParseTuple(args, "O", &other)) {
        PyErr_SetString(PyExc_TypeError, "orderAfter expects a hsKeyedObject");
        return nullptr;
    }
    if (!pyKeyedObject_Check((PyObject*)other)) {
        PyErr_SetString(PyExc_TypeError, "orderAfter expects a hsKeyedObject");
        return nullptr;
    }
    return pyPlasma_convert(self->fThis->orderAfter(other->fThis));
}

static PyMethodDef pyKeyedObject_Methods[] = {
    pyKeyedObject_orderAfter_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(KeyedObject, key)
{
    if (self->fThis->getKey().Exists()) {
        return pyKey_FromKey(self->fThis->getKey());
    } else {
        Py_RETURN_NONE;
    }
}

PY_PROPERTY_GETSET_RO_DECL(KeyedObject, key)

static PyGetSetDef pyKeyedObject_GetSet[] = {
    pyKeyedObject_key_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(KeyedObject, hsKeyedObject, "hsKeyedObject wrapper")

PY_PLASMA_TYPE_INIT(KeyedObject)
{
    pyKeyedObject_Type.tp_init = pyKeyedObject___init__;
    pyKeyedObject_Type.tp_new = pyKeyedObject_new;
    pyKeyedObject_Type.tp_methods = pyKeyedObject_Methods;
    pyKeyedObject_Type.tp_getset = pyKeyedObject_GetSet;
    pyKeyedObject_Type.tp_base = &pyCreatable_Type;
    if (PyType_CheckAndReady(&pyKeyedObject_Type) < 0)
        return nullptr;

    Py_INCREF(&pyKeyedObject_Type);
    return (PyObject*)&pyKeyedObject_Type;
}

PY_PLASMA_IFC_METHODS(KeyedObject, hsKeyedObject)
