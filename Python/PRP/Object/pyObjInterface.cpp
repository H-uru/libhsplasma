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

#include "pyObjInterface.h"

#include <PRP/Object/plObjInterface.h>
#include "pySynchedObject.h"
#include "PRP/pyCreatable.h"
#include "PRP/KeyedObject/pyKey.h"
#include "Util/pyBitVector.h"

PY_PLASMA_NEW_MSG(ObjInterface, "plObjInterface is abstract")

PY_METHOD_VA(ObjInterface, getProperty,
    "Params: flag\n"
    "Returns whether the specified property is set")
{
    int prop;
    if (!PyArg_ParseTuple(args, "i", &prop)) {
        PyErr_SetString(PyExc_TypeError, "getProperty expects an int");
        return nullptr;
    }
    return pyPlasma_convert(self->fThis->getProperty(prop));
}

PY_METHOD_VA(ObjInterface, setProperty,
    "Params: flag, value\n"
    "Sets the specified property")
{
    int prop, value;
    if (!PyArg_ParseTuple(args, "ii", &prop, &value)) {
        PyErr_SetString(PyExc_TypeError, "setProperty expects int, bool");
        return nullptr;
    }
    self->fThis->setProperty(prop, value != 0);
    Py_RETURN_NONE;
}

PyMethodDef pyObjInterface_Methods[] = {
    pyObjInterface_getProperty_method,
    pyObjInterface_setProperty_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY(plKey, ObjInterface, owner, getOwner, setOwner)

PyGetSetDef pyObjInterface_GetSet[] = {
    pyObjInterface_owner_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ObjInterface, plObjInterface, "plObjInterface wrapper")

PY_PLASMA_TYPE_INIT(ObjInterface)
{
    pyObjInterface_Type.tp_new = pyObjInterface_new;
    pyObjInterface_Type.tp_methods = pyObjInterface_Methods;
    pyObjInterface_Type.tp_getset = pyObjInterface_GetSet;
    pyObjInterface_Type.tp_base = &pySynchedObject_Type;
    if (PyType_CheckAndReady(&pyObjInterface_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(ObjInterface, "kDisable", plObjInterface::kDisable);

    Py_INCREF(&pyObjInterface_Type);
    return (PyObject*)&pyObjInterface_Type;
}

PY_PLASMA_IFC_METHODS(ObjInterface, plObjInterface)
