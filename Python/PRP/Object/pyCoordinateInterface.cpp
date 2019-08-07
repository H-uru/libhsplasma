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

#include <PRP/Object/plCoordinateInterface.h>
#include "PRP/pyCreatable.h"
#include "PRP/KeyedObject/pyKey.h"
#include "Math/pyMatrix.h"

PY_PLASMA_NEW(CoordinateInterface, plCoordinateInterface)

PY_METHOD_NOARGS(CoordinateInterface, clearChildren,
    "Removes all children from the Coordinate Interface")
{
    self->fThis->clearChildren();
    Py_RETURN_NONE;
}

PY_METHOD_VA(CoordinateInterface, addChild,
    "Params: key\n"
    "Adds a child object to this Coordinate Interface")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addChild expects a plKey");
        return nullptr;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addChild expects a plKey");
        return nullptr;
    }
    self->fThis->addChild(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(CoordinateInterface, delChild,
    "Params: idx\n"
    "Removes a child object from this Coordinate Interface")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delChild expects an int");
        return nullptr;
    }
    self->fThis->delChild(idx);
    Py_RETURN_NONE;
}

PyMethodDef pyCoordinateInterface_Methods[] = {
    pyCoordinateInterface_clearChildren_method,
    pyCoordinateInterface_addChild_method,
    pyCoordinateInterface_delChild_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(CoordinateInterface, children)
{
    PyObject* list = PyTuple_New(self->fThis->getChildren().size());
    for (size_t i=0; i<self->fThis->getChildren().size(); i++)
        PyTuple_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getChildren()[i]));
    return list;
}

PY_PROPERTY_SETTER_MSG(CoordinateInterface, children, "To add Children, use addChild")
PY_PROPERTY_GETSET_DECL(CoordinateInterface, children)

PY_PROPERTY(hsMatrix44, CoordinateInterface, localToWorld, getLocalToWorld, setLocalToWorld)
PY_PROPERTY(hsMatrix44, CoordinateInterface, worldToLocal, getWorldToLocal, setWorldToLocal)
PY_PROPERTY(hsMatrix44, CoordinateInterface, localToParent, getLocalToParent, setLocalToParent)
PY_PROPERTY(hsMatrix44, CoordinateInterface, parentToLocal, getParentToLocal, setParentToLocal)

PyGetSetDef pyCoordinateInterface_GetSet[] = {
    pyCoordinateInterface_localToWorld_getset,
    pyCoordinateInterface_worldToLocal_getset,
    pyCoordinateInterface_localToParent_getset,
    pyCoordinateInterface_parentToLocal_getset,
    pyCoordinateInterface_children_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(CoordinateInterface, plCoordinateInterface,
               "plCoordinateInterface wrapper")

PY_PLASMA_TYPE_INIT(CoordinateInterface)
{
    pyCoordinateInterface_Type.tp_new = pyCoordinateInterface_new;
    pyCoordinateInterface_Type.tp_methods = pyCoordinateInterface_Methods;
    pyCoordinateInterface_Type.tp_getset = pyCoordinateInterface_GetSet;
    pyCoordinateInterface_Type.tp_base = &pyObjInterface_Type;
    if (PyType_CheckAndReady(&pyCoordinateInterface_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(CoordinateInterface, "kCanEverDelayTransform",
                      plCoordinateInterface::kCanEverDelayTransform);
    PY_TYPE_ADD_CONST(CoordinateInterface, "kDelayedTransformEval",
                      plCoordinateInterface::kDelayedTransformEval);

    Py_INCREF(&pyCoordinateInterface_Type);
    return (PyObject*)&pyCoordinateInterface_Type;
}

PY_PLASMA_IFC_METHODS(CoordinateInterface, plCoordinateInterface)
