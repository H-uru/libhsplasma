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

extern "C" {

PY_PLASMA_NEW(CoordinateInterface, plCoordinateInterface)

static PyObject* pyCoordinateInterface_clearChildren(pyCoordinateInterface* self) {
    self->fThis->clearChildren();
    Py_RETURN_NONE;
}

static PyObject* pyCoordinateInterface_addChild(pyCoordinateInterface* self, PyObject* args) {
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addChild expects a plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addChild expects a plKey");
        return NULL;
    }
    self->fThis->addChild(*key->fThis);
    Py_RETURN_NONE;
}

static PyObject* pyCoordinateInterface_delChild(pyCoordinateInterface* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delChild expects an int");
        return NULL;
    }
    self->fThis->delChild(idx);
    Py_RETURN_NONE;
}

static PyObject* pyCoordinateInterface_getChildren(pyCoordinateInterface* self, void*) {
    PyObject* list = PyList_New(self->fThis->getChildren().size());
    for (size_t i=0; i<self->fThis->getChildren().size(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getChildren()[i]));
    return list;
}

static int pyCoordinateInterface_setChildren(pyCoordinateInterface* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add Children, use addChild");
    return -1;
}

PyMethodDef pyCoordinateInterface_Methods[] = {
    { "clearChildren", (PyCFunction)pyCoordinateInterface_clearChildren, METH_NOARGS,
      "Removes all children from the Coordinate Interface" },
    { "addChild", (PyCFunction)pyCoordinateInterface_addChild, METH_VARARGS,
      "Params: key\n"
      "Adds a child object to this Coordinate Interface" },
    { "delChild", (PyCFunction)pyCoordinateInterface_delChild, METH_VARARGS,
      "Params: idx\n"
      "Removes a child object from this Coordinate Interface" },
    { NULL, NULL, 0, NULL }
};

PY_PROPERTY(hsMatrix44, CoordinateInterface, localToWorld, getLocalToWorld, setLocalToWorld)
PY_PROPERTY(hsMatrix44, CoordinateInterface, worldToLocal, getWorldToLocal, setWorldToLocal)
PY_PROPERTY(hsMatrix44, CoordinateInterface, localToParent, getLocalToParent, setLocalToParent)
PY_PROPERTY(hsMatrix44, CoordinateInterface, parentToLocal, getParentToLocal, setParentToLocal)

PyGetSetDef pyCoordinateInterface_GetSet[] = {
    pyCoordinateInterface_localToWorld_getset,
    pyCoordinateInterface_worldToLocal_getset,
    pyCoordinateInterface_localToParent_getset,
    pyCoordinateInterface_parentToLocal_getset,
    { _pycs("children"), (getter)pyCoordinateInterface_getChildren,
        (setter)pyCoordinateInterface_setChildren,
        _pycs("Child Objects"), NULL },
    PY_GETSET_TERMINATOR
};

PyTypeObject pyCoordinateInterface_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plCoordinateInterface", /* tp_name */
    sizeof(pyCoordinateInterface),      /* tp_basicsize */
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
    "plCoordinateInterface wrapper",    /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyCoordinateInterface_Methods,      /* tp_methods */
    NULL,                               /* tp_members */
    pyCoordinateInterface_GetSet,       /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyCoordinateInterface_new,          /* tp_new */
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

PyObject* Init_pyCoordinateInterface_Type() {
    pyCoordinateInterface_Type.tp_base = &pyObjInterface_Type;
    if (PyType_Ready(&pyCoordinateInterface_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyCoordinateInterface_Type.tp_dict, "kCanEverDelayTransform",
                         PyInt_FromLong(plCoordinateInterface::kCanEverDelayTransform));
    PyDict_SetItemString(pyCoordinateInterface_Type.tp_dict, "kDelayedTransformEval",
                         PyInt_FromLong(plCoordinateInterface::kDelayedTransformEval));

    Py_INCREF(&pyCoordinateInterface_Type);
    return (PyObject*)&pyCoordinateInterface_Type;
}

PY_PLASMA_IFC_METHODS(CoordinateInterface, plCoordinateInterface)

}
