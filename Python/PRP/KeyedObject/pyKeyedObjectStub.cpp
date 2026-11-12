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

PY_PLASMA_INIT_DECL(KeyedObjectStub)
{
    pyCreatableStub* stubObj;
    const char* name = "";
    if (!PyArg_ParseTuple(args, "O|s", &stubObj, &name)) {
        PyErr_SetString(PyExc_TypeError, "__init__ expects a plCreatableStub and an optional string");
        return -1;
    }

    if (stubObj == nullptr || !pyCreatableStub_Check((PyObject*)stubObj)) {
        PyErr_SetString(PyExc_TypeError, "__init__ expects a plCreatableStub and an optional string");
        return -1;
    }

    // A stub object must be passed in because the hsKeyedObjectStub dereferences
    // it in `init()` to set the key's class type.
    stubObj->fPyOwned = false;
    self->fThis->setStub(stubObj->fThis);
    self->fThis->init(name);
    return 0;
}

PY_PLASMA_NEW(KeyedObjectStub, hsKeyedObjectStub)

PY_PROPERTY_CREATABLE_RO(KeyedObjectStub, stub, getStub)

static PyGetSetDef pyKeyedObjectStub_GetSet[] = {
    pyKeyedObjectStub_stub_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(KeyedObjectStub, hsKeyedObjectStub, "hsKeyedObjectStub wrapper")

PY_PLASMA_TYPE_INIT(KeyedObjectStub)
{
    pyKeyedObjectStub_Type.tp_init = pyKeyedObjectStub___init__;
    pyKeyedObjectStub_Type.tp_new = pyKeyedObjectStub_new;
    pyKeyedObjectStub_Type.tp_getset = pyKeyedObjectStub_GetSet;
    pyKeyedObjectStub_Type.tp_base = &pyKeyedObject_Type;
    if (PyType_CheckAndReady(&pyKeyedObjectStub_Type) < 0)
        return nullptr;

    Py_INCREF(&pyKeyedObjectStub_Type);
    return (PyObject*)&pyKeyedObjectStub_Type;
}

PY_PLASMA_IFC_METHODS(KeyedObjectStub, hsKeyedObjectStub)
