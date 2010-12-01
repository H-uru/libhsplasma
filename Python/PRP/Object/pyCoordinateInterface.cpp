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
#include <PRP/Object/plCoordinateInterface.h>
#include "pyObjInterface.h"
#include "PRP/pyCreatable.h"
#include "PRP/KeyedObject/pyKey.h"
#include "Math/pyMatrix.h"

extern "C" {

static PyObject* pyCoordinateInterface_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyCoordinateInterface* self = (pyCoordinateInterface*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plCoordinateInterface();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyCoordinateInterface_clearChildren(pyCoordinateInterface* self) {
    self->fThis->clearChildren();
    Py_INCREF(Py_None);
    return Py_None;
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
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyCoordinateInterface_delChild(pyCoordinateInterface* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delChild expects an int");
        return NULL;
    }
    self->fThis->delChild(idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyCoordinateInterface_getL2W(pyCoordinateInterface* self, void*) {
    return pyMatrix44_FromMatrix44(self->fThis->getLocalToWorld());
}

static PyObject* pyCoordinateInterface_getW2L(pyCoordinateInterface* self, void*) {
    return pyMatrix44_FromMatrix44(self->fThis->getWorldToLocal());
}

static PyObject* pyCoordinateInterface_getL2P(pyCoordinateInterface* self, void*) {
    return pyMatrix44_FromMatrix44(self->fThis->getLocalToParent());
}

static PyObject* pyCoordinateInterface_getP2L(pyCoordinateInterface* self, void*) {
    return pyMatrix44_FromMatrix44(self->fThis->getParentToLocal());
}

static PyObject* pyCoordinateInterface_getChildren(pyCoordinateInterface* self, void*) {
    PyObject* list = PyList_New(self->fThis->getChildren().getSize());
    for (size_t i=0; i<self->fThis->getChildren().getSize(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getChildren()[i]));
    return list;
}

static int pyCoordinateInterface_setL2W(pyCoordinateInterface* self, PyObject* value, void*) {
    if (value == NULL || (!pyMatrix44_Check(value))) {
        PyErr_SetString(PyExc_TypeError, "localToWorld should be an hsMatrix44");
        return -1;
    }
    self->fThis->setLocalToWorld(*((pyMatrix44*)value)->fThis);
    return 0;
}

static int pyCoordinateInterface_setW2L(pyCoordinateInterface* self, PyObject* value, void*) {
    if (value == NULL || (!pyMatrix44_Check(value))) {
        PyErr_SetString(PyExc_TypeError, "worldToLocal should be an hsMatrix44");
        return -1;
    }
    self->fThis->setWorldToLocal(*((pyMatrix44*)value)->fThis);
    return 0;
}

static int pyCoordinateInterface_setL2P(pyCoordinateInterface* self, PyObject* value, void*) {
    if (value == NULL || (!pyMatrix44_Check(value))) {
        PyErr_SetString(PyExc_TypeError, "local2Parent should be an hsMatrix44");
        return -1;
    }
    self->fThis->setLocalToParent(*((pyMatrix44*)value)->fThis);
    return 0;
}

static int pyCoordinateInterface_setP2L(pyCoordinateInterface* self, PyObject* value, void*) {
    if (value == NULL || (!pyMatrix44_Check(value))) {
        PyErr_SetString(PyExc_TypeError, "parentToLocal should be an hsMatrix44");
        return -1;
    }
    self->fThis->setParentToLocal(*((pyMatrix44*)value)->fThis);
    return 0;
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

PyGetSetDef pyCoordinateInterface_GetSet[] = {
    { "localToWorld", (getter)pyCoordinateInterface_getL2W, (setter)pyCoordinateInterface_setL2W,
      "Local -> World transform matrix", NULL },
    { "worldToLocal", (getter)pyCoordinateInterface_getW2L, (setter)pyCoordinateInterface_setW2L,
      "World -> Local transform matrix", NULL },
    { "localToParent", (getter)pyCoordinateInterface_getL2P, (setter)pyCoordinateInterface_setL2P,
      "Local -> Parent transform matrix", NULL },
    { "parentToLocal", (getter)pyCoordinateInterface_getP2L, (setter)pyCoordinateInterface_setP2L,
      "Parent -> Local transform matrix", NULL },
    { "children", (getter)pyCoordinateInterface_getChildren, (setter)pyCoordinateInterface_setChildren,
      "Child Objects", NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyCoordinateInterface_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plCoordinateInterface",   /* tp_name */
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

int pyCoordinateInterface_Check(PyObject* obj) {
    if (obj->ob_type == &pyCoordinateInterface_Type
        || PyType_IsSubtype(obj->ob_type, &pyCoordinateInterface_Type))
        return 1;
    return 0;
}

PyObject* pyCoordinateInterface_FromCoordinateInterface(class plCoordinateInterface* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyCoordinateInterface* intf = PyObject_New(pyCoordinateInterface, &pyCoordinateInterface_Type);
    intf->fThis = obj;
    intf->fPyOwned = false;
    return (PyObject*)intf;
}

}
