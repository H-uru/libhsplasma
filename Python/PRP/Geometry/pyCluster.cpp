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

#include "pyCluster.h"

#include <PRP/Geometry/plCluster.h>
#include <PRP/Geometry/plClusterGroup.h>
#include "PRP/pyCreatable.h"
#include "pyClusterGroup.h"
#include "pySpanInstance.h"
#include "Stream/pyStream.h"

extern "C" {

PY_PLASMA_DEALLOC(Cluster)
PY_PLASMA_EMPTY_INIT(Cluster)
PY_PLASMA_NEW(Cluster, plCluster)

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
    Py_RETURN_NONE;
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
    Py_RETURN_NONE;
}

static PyObject* pyCluster_clearInstances(pyCluster* self) {
    self->fThis->clearInstances();
    Py_RETURN_NONE;
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
    Py_RETURN_NONE;
}

static PyObject* pyCluster_delInstance(pyCluster* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delInstance expects an int");
        return NULL;
    }
    self->fThis->delInstance(idx);
    Py_RETURN_NONE;
}

static PyObject* pyCluster_getInstances(pyCluster* self, void*) {
    PyObject* list = PyList_New(self->fThis->getInstances().size());
    for (size_t i=0; i<self->fThis->getInstances().size(); i++)
        PyList_SET_ITEM(list, i, pySpanInstance_FromSpanInstance(self->fThis->getInstances()[i]));
    return list;
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

PY_PROPERTY_PROXY_RO(plSpanEncoding, Cluster, encoding, getEncoding)
PY_PROPERTY_CREATABLE(plClusterGroup, ClusterGroup, Cluster, group, getGroup, setGroup)

static PyGetSetDef pyCluster_GetSet[] = {
    pyCluster_encoding_getset,
    pyCluster_group_getset,
    { _pycs("instances"), (getter)pyCluster_getInstances,
        (setter)pyCluster_setInstances, NULL, NULL },
    PY_GETSET_TERMINATOR
};

PyTypeObject pyCluster_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plCluster",             /* tp_name */
    sizeof(pyCluster),                  /* tp_basicsize */
    0,                                  /* tp_itemsize */

    pyCluster_dealloc,                  /* tp_dealloc */
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

    pyCluster___init__,                 /* tp_init */
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
    TP_FINALIZE_INIT                    /* tp_finalize */
};

PyObject* Init_pyCluster_Type() {
    if (PyType_Ready(&pyCluster_Type) < 0)
        return NULL;

    Py_INCREF(&pyCluster_Type);
    return (PyObject*)&pyCluster_Type;
}

PY_PLASMA_IFC_METHODS(Cluster, plCluster)

}
