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

PyTypeObject pyClothingItem_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plClothingItem",        /* tp_name */
    sizeof(pyClothingItem),             /* tp_basicsize */
    0,                                  /* tp_itemsize */

    NULL,                               /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_compare */
    NULL,                               /* tp_repr */
    NULL,                               /* tp_as_number */
    NULL,                               /* tp_as_sequence */
    NULL,                               /* tp_as_mapping */
    NULL,                               /* tp_hash */
    NULL,                               /* tp_call */
    NULL,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */

    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
    "plClothingItem wrapper",                 /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyClothingItem_Methods,             /* tp_methods */
    NULL,                               /* tp_members */
    pyClothingItem_GetSet,              /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyClothingItem_new,                 /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */

    NULL,                               /* tp_del */
    TP_VERSION_TAG_INIT                 /* tp_version_tag */
    TP_FINALIZE_INIT                    /* tp_finalize */
};

PyObject* Init_pyClothingItem_Type() {
    pyClothingItem_Type.tp_base = &pyKeyedObject_Type;
    if (PyType_Ready(&pyClothingItem_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyClothingItem_Type.tp_dict, "kLODHigh",
        PyInt_FromLong(plClothingItem::kLODHigh));
    PyDict_SetItemString(pyClothingItem_Type.tp_dict, "kLODMedium",
        PyInt_FromLong(plClothingItem::kLODMedium));
    PyDict_SetItemString(pyClothingItem_Type.tp_dict, "kLODLow",
        PyInt_FromLong(plClothingItem::kLODLow));

    Py_INCREF(&pyClothingItem_Type);
    return (PyObject*)&pyClothingItem_Type;
}

PY_PLASMA_IFC_METHODS(ClothingItem, plClothingItem)

}
