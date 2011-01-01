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
#include <PRP/Geometry/plCluster.h>
#include "pyCluster.h"
#include "pyClusterGroup.h"
#include "pySpanInstance.h"
#include "Stream/pyStream.h"

extern "C" {

static void pyCluster_dealloc(pyCluster* self) {
    if (self->fPyOwned)
        delete self->fThis;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static int pyCluster___init__(pyCluster* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pyCluster_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyCluster* self = (pyCluster*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plCluster();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyCluster_read(pyCluster* self, PyObject* args) {
    pyStream* stream;
    pyClusterGroup* group;
    if (!PyArg_ParseTuple(args, "OO", &stream, &group)) {
        PyErr_SetString(PyExc_TypeError, "read expects hsStream, plClusterGroup");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream) || !pyClusterGroup_Check((PyObject*)group)) {
        PyErr_SetString(PyExc_TypeError, "read expects hsStream, plClusterGroup");
        return NULL;
    }
    self->fThis->read(stream->fThis, group->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyCluster_write(pyCluster* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects an hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects an hsStream");
        return NULL;
    }
    self->fThis->write(stream->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyCluster_clearInstances(pyCluster* self) {
    self->fThis->clearInstances();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyCluster_addInstance(pyCluster* self, PyObject* args) {
    pySpanInstance* instance;
    if (!PyArg_ParseTuple(args, "O", &instance)) {
        PyErr_SetString(PyExc_TypeError, "addInstance expects a plSpanInstance");
        return NULL;
    }
    if (!pySpanInstance_Check((PyObject*)instance)) {
        PyErr_SetString(PyExc_TypeError, "addInstance expects a plSpanInstance");
        return NULL;
    }
    self->fThis->addInstance(instance->fThis);
    instance->fPyOwned = false;
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyCluster_delInstance(pyCluster* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delInstance expects an int");
        return NULL;
    }
    self->fThis->delInstance(idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyCluster_getEncoding(pyCluster* self, void*) {
    return pySpanEncoding_FromSpanEncoding(&self->fThis->getEncoding());
}

static PyObject* pyCluster_getGroup(pyCluster* self, void*) {
    return pyClusterGroup_FromClusterGroup(self->fThis->getGroup());
}

static PyObject* pyCluster_getInstances(pyCluster* self, void*) {
    PyObject* list = PyList_New(self->fThis->getInstances().getSize());
    for (size_t i=0; i<self->fThis->getInstances().getSize(); i++)
        PyList_SET_ITEM(list, i, pySpanInstance_FromSpanInstance(self->fThis->getInstances()[i]));
    return list;
}

static int pyCluster_setEncoding(pyCluster* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "encoding cannot be assigned");
    return -1;
}

static int pyCluster_setGroup(pyCluster* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setGroup(NULL);
        return 0;
    }
    if (!pyClusterGroup_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "group should be a plClusterGroup");
        return -1;
    }
    self->fThis->setGroup(((pyClusterGroup*)value)->fThis);
    return 0;
}

static int pyCluster_setInstances(pyCluster* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add instances, use addInstance");
    return -1;
}

static PyMethodDef pyCluster_Methods[] = {
    { "read", (PyCFunction)pyCluster_read, METH_VARARGS,
      "Params: stream, group\n"
      "Read this object from the stream" },
    { "write", (PyCFunction)pyCluster_write, METH_VARARGS,
      "Params: stream\n"
      "Write this object to the stream" },
    { "clearInstances", (PyCFunction)pyCluster_clearInstances, METH_NOARGS,
      "Remove all plSpanInstance objects from the cluster" },
    { "addInstance", (PyCFunction)pyCluster_addInstance, METH_VARARGS,
      "Params: instance\n"
      "Add a plSpanInstance to the cluster" },
    { "delInstance", (PyCFunction)pyCluster_delInstance, METH_VARARGS,
      "Params: idx\n"
      "Remove a plSpanInstance from the cluster" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyCluster_GetSet[] = {
    { "encoding", (getter)pyCluster_getEncoding, (setter)pyCluster_setEncoding, NULL, NULL },
    { "group", (getter)pyCluster_getGroup, (setter)pyCluster_setGroup, NULL, NULL },
    { "instances", (getter)pyCluster_getInstances, (setter)pyCluster_setInstances, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyCluster_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plCluster",               /* tp_name */
    sizeof(pyCluster),                  /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pyCluster_dealloc,      /* tp_dealloc */
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
    "plCluster wrapper",                /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyCluster_Methods,                  /* tp_methods */
    NULL,                               /* tp_members */
    pyCluster_GetSet,                   /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyCluster___init__,       /* tp_init */
    NULL,                               /* tp_alloc */
    pyCluster_new,                      /* tp_new */
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

PyObject* Init_pyCluster_Type() {
    if (PyType_Ready(&pyCluster_Type) < 0)
        return NULL;

    Py_INCREF(&pyCluster_Type);
    return (PyObject*)&pyCluster_Type;
}

int pyCluster_Check(PyObject* obj) {
    if (obj->ob_type == &pyCluster_Type
        || PyType_IsSubtype(obj->ob_type, &pyCluster_Type))
        return 1;
    return 0;
}

PyObject* pyCluster_FromCluster(plCluster* cluster) {
    if (cluster == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyCluster* obj = PyObject_New(pyCluster, &pyCluster_Type);
    obj->fThis = cluster;
    obj->fPyOwned = false;
    return (PyObject*)obj;
}

}
