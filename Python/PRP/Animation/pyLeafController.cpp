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
#include <PRP/Animation/plLeafController.h>
#include "pyLeafController.h"
#include "pyController.h"
#include "pyKeys.h"
#include "PRP/pyCreatable.h"

extern "C" {

static int pyLeafController___init__(pyLeafController* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pyLeafController_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyLeafController* self = (pyLeafController*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plLeafController();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyLeafController_hasKeys(pyLeafController* self) {
    return PyBool_FromLong(self->fThis->hasKeys() ? 1 : 0);
}

static PyObject* pyLeafController_hasEaseControllers(pyLeafController* self) {
    return PyBool_FromLong(self->fThis->hasEaseControllers() ? 1 : 0);
}

static PyObject* pyLeafController_setKeys(pyLeafController* self, PyObject* args) {
    PyObject* list;
    int type;
    if (!PyArg_ParseTuple(args, "Oi", &list, &type)) {
        PyErr_SetString(PyExc_TypeError, "setKeys expects a list of hsKeyFrames and an int");
        return NULL;
    }
    if (!PyList_Check(list)) {
        PyErr_SetString(PyExc_TypeError, "setKeys expects a list of hsKeyFrames and an int");
        return NULL;
    }
    hsTArray<hsKeyFrame*> keys;
    keys.setSizeNull(PyList_Size(list));
    for (size_t i=0; i<keys.getSize(); i++) {
        PyObject* itm = PyList_GetItem(list, i);
        if (!pyKeyFrame_Check(itm)) {
            PyErr_SetString(PyExc_TypeError, "setKeys expects a list of hsKeyFrames and an int");
            return NULL;
        }
        ((pyKeyFrame*)itm)->fPyOwned = false;
        keys[i] = ((pyKeyFrame*)itm)->fThis;
    }
    self->fThis->setKeys(keys, type);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyLeafController_ExpandToKeyController(pyLeafController* self) {
    return pyLeafController_FromLeafController(self->fThis->ExpandToKeyController());
}

static PyObject* pyLeafController_CompactToLeafController(pyLeafController* self) {
    return pyLeafController_FromLeafController(self->fThis->CompactToLeafController());
}

static PyObject* pyLeafController_getType(pyLeafController* self, void*) {
    return PyInt_FromLong(self->fThis->getType());
}

static PyObject* pyLeafController_getKeys(pyLeafController* self, void*) {
    const hsTArray<hsKeyFrame*>& keys = self->fThis->getKeys();
    PyObject* list = PyList_New(keys.getSize());
    for (size_t i=0; i<keys.getSize(); i++)
        PyList_SET_ITEM(list, i, pyKeyFrame_FromKeyFrame(keys[i]));
    return list;
}

static PyObject* pyLeafController_getEaseControllers(pyLeafController* self, void*) {
    const hsTArray<plEaseController*>& controllers = self->fThis->getEaseControllers();
    PyObject* list = PyList_New(controllers.getSize());
    for (size_t i=0; i<controllers.getSize(); i++)
        PyList_SET_ITEM(list, i, pyEaseController_FromEaseController(controllers[i]));
    return list;
}

static int pyLeafController_setType(pyLeafController* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To set the key type, use setKeys");
    return -1;
}

static int pyLeafController_setKeysErr(pyLeafController* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "Use setKeys to set the keys list");
    return -1;
}

static int pyLeafController_setEaseControllers(pyLeafController* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setEaseControllers(hsTArray<plEaseController*>());
        return 0;
    }
    if (!PyList_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "easeControllers should be a list of plEaseControllers");
        return -1;
    }
    hsTArray<plEaseController*> controllers;
    controllers.setSizeNull(PyList_Size(value));
    for (size_t i=0; i<controllers.getSize(); i++) {
        PyObject* itm = PyList_GetItem(value, i);
        if (!pyEaseController_Check(itm)) {
            PyErr_SetString(PyExc_TypeError, "easeControllers should be a list of plEaseControllers");
            return -1;
        }
        ((pyEaseController*)itm)->fPyOwned = false;
        controllers[i] = ((pyEaseController*)itm)->fThis;
    }
    self->fThis->setEaseControllers(controllers);
    return 0;
}

static PyMethodDef pyLeafController_Methods[] = {
    { "hasKeys", (PyCFunction)pyLeafController_hasKeys, METH_NOARGS, NULL },
    { "hasEaseControllers", (PyCFunction)pyLeafController_hasEaseControllers, METH_NOARGS, NULL },
    { "setKeys", (PyCFunction)pyLeafController_setKeys, METH_VARARGS,
      "Params: keys, type\n"
      "Set a list of keys of type `type` for the controller\n" },
    { "ExpandToKeyController", (PyCFunction)pyLeafController_ExpandToKeyController, METH_NOARGS, NULL },
    { "CompactToLeafController", (PyCFunction)pyLeafController_CompactToLeafController, METH_NOARGS, NULL },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyLeafController_GetSet[] = {
    { "type", (getter)pyLeafController_getType, (setter)pyLeafController_setType, NULL, NULL },
    { "keys", (getter)pyLeafController_getKeys, (setter)pyLeafController_setKeysErr, NULL, NULL },
    { "easeControllers", (getter)pyLeafController_getEaseControllers, (setter)pyLeafController_setEaseControllers, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyLeafController_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plLeafController",        /* tp_name */
    sizeof(pyLeafController),           /* tp_basicsize */
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
    "plLeafController wrapper",         /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyLeafController_Methods,           /* tp_methods */
    NULL,                               /* tp_members */
    pyLeafController_GetSet,            /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyLeafController___init__, /* tp_init */
    NULL,                               /* tp_alloc */
    pyLeafController_new,               /* tp_new */
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

PyObject* Init_pyLeafController_Type() {
    pyLeafController_Type.tp_base = &pyController_Type;
    if (PyType_Ready(&pyLeafController_Type) < 0)
        return NULL;

    Py_INCREF(&pyLeafController_Type);
    return (PyObject*)&pyLeafController_Type;
}

int pyLeafController_Check(PyObject* obj) {
    if (obj->ob_type == &pyLeafController_Type
        || PyType_IsSubtype(obj->ob_type, &pyLeafController_Type))
        return 1;
    return 0;
}

PyObject* pyLeafController_FromLeafController(class plLeafController* controller) {
    if (controller == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyLeafController* pyobj = PyObject_New(pyLeafController, &pyLeafController_Type);
    delete pyobj->fThis;
    pyobj->fThis = controller;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
