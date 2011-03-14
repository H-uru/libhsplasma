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

#include <PyPlasma.h>
#include <PRP/Avatar/plClothingItem.h>
#include "pyClothingItem.h"
#include "../KeyedObject/pyKey.h"
#include "../KeyedObject/pyKeyedObject.h"
#include "../pyCreatable.h"

extern "C" {

static PyObject* pyClothingItem_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyClothingItem* self = (pyClothingItem*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plClothingItem();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyClothingItem_getDescription(pyClothingItem* self, void* closure) {
    return PlStr_To_PyStr(self->fThis->getDescription());
}

static PyObject* pyClothingItem_getItemName(pyClothingItem* self, void* closure) {
    return PlStr_To_PyStr(self->fThis->getItemName());
}

static PyObject* pyClothingItem_getMesh(pyClothingItem* self, PyObject* args) {
    int lod = plClothingItem::kLODHigh;
    if (!PyArg_ParseTuple(args, "i", &lod)) {
        PyErr_SetString(PyExc_TypeError, "getMesh expects int");
        return NULL;
    }

    return pyKey_FromKey(self->fThis->getMesh(lod));
}

static int pyClothingItem_setDescription(pyClothingItem* self, PyObject* value, void* closure) {
    if (value == NULL) {
        self->fThis->setDescription("");
    } else {
        if (!PyAnyStr_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "description must be a string");
            return -1;
        }
        self->fThis->setDescription(PyStr_To_PlStr(value));
    }
    return 0;
}

static int pyClothingItem_setItemName(pyClothingItem* self, PyObject* value, void* closure) {
    if (value == NULL) {
        self->fThis->setItemName("");
    } else {
        if (!PyAnyStr_Check(value)) {
            PyErr_SetString(PyExc_TypeError, "itemName must be a string");
            return -1;
        }
        self->fThis->setItemName(PyStr_To_PlStr(value));
    }
    return 0;
}

static PyObject* pyClothingItem_setMesh(pyClothingItem* self, PyObject* args) {
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
    Py_INCREF(Py_None);
    return Py_None;
}

PyMethodDef pyClothingItem_Methods[] = {
    { "getMesh", (PyCFunction)pyClothingItem_getMesh, METH_VARARGS,
      "Params: lod\n"
      "Gets the Key of the mesh for the specified LOD" },
    { "setMesh", (PyCFunction)pyClothingItem_setMesh, METH_VARARGS,
      "Params: lod, mesh\n"
      "Sets the Key of the mesh for the specified LOD" },
    { NULL, NULL, 0, NULL }
};

PyGetSetDef pyClothingItem_GetSet[] = {
    { "description", (getter)pyClothingItem_getDescription,
      (setter)pyClothingItem_setDescription, NULL, NULL },
    { "itemName", (getter)pyClothingItem_getItemName,
      (setter)pyClothingItem_setItemName, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyClothingItem_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plClothingItem",          /* tp_name */
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

int pyClothingItem_Check(PyObject* obj) {
    if (obj->ob_type == &pyClothingItem_Type
        || PyType_IsSubtype(obj->ob_type, &pyClothingItem_Type))
        return 1;
    return 0;
}

PyObject* pyClothingItem_FromClothingItem(class plClothingItem* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyClothingItem* node = PyObject_New(pyClothingItem, &pyClothingItem_Type);
    node->fThis = obj;
    node->fPyOwned = false;
    return (PyObject*)node;
}

}
