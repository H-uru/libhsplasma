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

#include "pyClothingItem.h"

#include <PRP/Avatar/plClothingItem.h>
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/KeyedObject/pyKeyedObject.h"
#include "PRP/pyCreatable.h"

extern "C" {

PY_PLASMA_NEW(ClothingItem, plClothingItem)

PY_METHOD_VA(ClothingItem, getMesh,
    "Params: lod\n"
    "Gets the Key of the mesh for the specified LOD")
{
    int lod = plClothingItem::kLODHigh;
    if (!PyArg_ParseTuple(args, "i", &lod)) {
        PyErr_SetString(PyExc_TypeError, "getMesh expects int");
        return NULL;
    }

    return pyKey_FromKey(self->fThis->getMesh(lod));
}

PY_METHOD_VA(ClothingItem, setMesh,
    "Params: lod, mesh\n"
    "Sets the Key of the mesh for the specified LOD")
{
    int lod = plClothingItem::kLODHigh;
    pyKey* key;

    if (!PyArg_ParseTuple(args, "iO", &lod, &key)) {
        PyErr_SetString(PyExc_TypeError, "read expects int, plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "read expects hsStream, plResManager");
        return NULL;
    }

    self->fThis->setMesh(lod, *(key->fThis));
    Py_RETURN_NONE;
}

PyMethodDef pyClothingItem_Methods[] = {
    pyClothingItem_getMesh_method,
    pyClothingItem_setMesh_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY(plString, ClothingItem, description, getDescription, setDescription)
PY_PROPERTY(plString, ClothingItem, itemName, getItemName, setItemName)

PyGetSetDef pyClothingItem_GetSet[] = {
    pyClothingItem_description_getset,
    pyClothingItem_itemName_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ClothingItem, plClothingItem, "plClothingItem wrapper")

PY_PLASMA_TYPE_INIT(ClothingItem) {
    pyClothingItem_Type.tp_new = pyClothingItem_new;
    pyClothingItem_Type.tp_methods = pyClothingItem_Methods;
    pyClothingItem_Type.tp_getset = pyClothingItem_GetSet;
    pyClothingItem_Type.tp_base = &pyKeyedObject_Type;
    if (PyType_Ready(&pyClothingItem_Type) < 0)
        return NULL;

    PY_TYPE_ADD_CONST(ClothingItem, "kLODHigh", plClothingItem::kLODHigh);
    PY_TYPE_ADD_CONST(ClothingItem, "kLODMedium", plClothingItem::kLODMedium);
    PY_TYPE_ADD_CONST(ClothingItem, "kLODLow", plClothingItem::kLODLow);

    Py_INCREF(&pyClothingItem_Type);
    return (PyObject*)&pyClothingItem_Type;
}

PY_PLASMA_IFC_METHODS(ClothingItem, plClothingItem)

}
