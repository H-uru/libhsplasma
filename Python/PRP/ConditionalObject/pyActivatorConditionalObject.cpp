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
#include <PRP/ConditionalObject/plActivatorConditionalObject.h>
#include "pyActivatorConditionalObject.h"
#include "pyConditionalObject.h"
#include "PRP/pyCreatable.h"
#include "PRP/KeyedObject/pyKey.h"

extern "C" {

static PyObject* pyActivatorConditionalObject_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyActivatorConditionalObject* self = (pyActivatorConditionalObject*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plActivatorConditionalObject();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyActivatorConditionalObject_addActivator(pyActivatorConditionalObject* self, PyObject* args) {
    PyObject* key;
    if (!(PyArg_ParseTuple(args, "O", &key) && pyKey_Check(key))) {
        PyErr_SetString(PyExc_TypeError, "addActivator expects a plKey");
        return NULL;
    }
    self->fThis->addActivator(*((pyKey*)key)->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyActivatorConditionalObject_clearActivators(pyActivatorConditionalObject* self) {
    self->fThis->clearActivators();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyActivatorConditionalObject_delActivator(pyActivatorConditionalObject* self, PyObject* args) {
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delActivator expects an int");
        return NULL;
    }
    self->fThis->delActivator((size_t)idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef pyActivatorConditionalObject_Methods[] = {
    { "addActivator", (PyCFunction)pyActivatorConditionalObject_addActivator, METH_VARARGS,
      "Params: key\n"
      "Adds an activator key" },
    { "clearActivators", (PyCFunction)pyActivatorConditionalObject_clearActivators, METH_NOARGS,
      "Removes all activator keys" },
    { "delActivator", (PyCFunction)pyActivatorConditionalObject_delActivator, METH_VARARGS,
      "Params: idx\n"
      "Removes an activator key" },
    { NULL, NULL, 0, NULL }
};

static PyObject* pyActivatorConditionalObject_getActivators(pyActivatorConditionalObject* self, void*) {
    plActivatorConditionalObject* act = self->fThis;
    PyObject* activators = PyTuple_New(act->getActivators().size());
    for (size_t i = 0; i < act->getActivators().size(); ++i)
        PyTuple_SET_ITEM(activators, i, pyKey_FromKey(act->getActivators()[i]));
    return activators;
}

static int pyActivatorConditionalObject_setActivators(pyActivatorConditionalObject* self, PyObject*, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add activators, use addActivator()");
    return -1;
}

static PyGetSetDef pyActivatorConditionalObject_GetSet[] = {
    { _pycs("activators"), (getter)pyActivatorConditionalObject_getActivators,
       (setter)pyActivatorConditionalObject_setActivators, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyActivatorConditionalObject_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plActivatorConditionalObject", /* tp_name */
    sizeof(pyActivatorConditionalObject),      /* tp_basicsize */
    0,                                         /* tp_itemsize */

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

    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,  /* tp_flags */
    "plActivatorConditionalObject wrapper", /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyActivatorConditionalObject_Methods,/* tp_methods */
    NULL,                               /* tp_members */
    pyActivatorConditionalObject_GetSet,/* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyActivatorConditionalObject_new,   /* tp_new */
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

PyObject* Init_pyActivatorConditionalObject_Type() {
    pyActivatorConditionalObject_Type.tp_base = &pyConditionalObject_Type;
    if (PyType_Ready(&pyActivatorConditionalObject_Type) < 0)
        return NULL;

    Py_INCREF(&pyActivatorConditionalObject_Type);
    return (PyObject*)&pyActivatorConditionalObject_Type;
}

int pyActivatorConditionalObject_Check(PyObject* obj) {
    if (obj->ob_type == &pyActivatorConditionalObject_Type
        || PyType_IsSubtype(obj->ob_type, &pyActivatorConditionalObject_Type))
        return 1;
    return 0;
}

PyObject* pyActivatorConditionalObject_FromActivatorConditionalObject(class plActivatorConditionalObject* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyActivatorConditionalObject* py = PyObject_New(pyActivatorConditionalObject, &pyActivatorConditionalObject_Type);
    py->fThis = obj;
    py->fPyOwned = false;
    return (PyObject*)py;
}

};
