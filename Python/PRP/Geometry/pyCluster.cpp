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

PY_PLASMA_DEALLOC(Cluster)
PY_PLASMA_EMPTY_INIT(Cluster)
PY_PLASMA_NEW(Cluster, plCluster)

PY_METHOD_VA(Cluster, read,
    "Params: stream, group\n"
    "Read this object from the stream")
{
    pyStream* stream;
    pyClusterGroup* group;
    if (!PyArg_ParseTuple(args, "OO", &stream, &group)) {
        PyErr_SetString(PyExc_TypeError, "read expects hsStream, plClusterGroup");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream) || !pyClusterGroup_Check((PyObject*)group)) {
        PyErr_SetString(PyExc_TypeError, "read expects hsStream, plClusterGroup");
        return nullptr;
    }
    self->fThis->read(stream->fThis, group->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(Cluster, write,
    "Params: stream\n"
    "Write this object to the stream")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects an hsStream");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects an hsStream");
        return nullptr;
    }
    self->fThis->write(stream->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(Cluster, clearInstances,
    "Remove all plSpanInstance objects from the cluster")
{
    self->fThis->clearInstances();
    Py_RETURN_NONE;
}

PY_METHOD_VA(Cluster, addInstance,
    "Params: instance\n"
    "Add a plSpanInstance to the cluster")
{
    pySpanInstance* instance;
    if (!PyArg_ParseTuple(args, "O", &instance)) {
        PyErr_SetString(PyExc_TypeError, "addInstance expects a plSpanInstance");
        return nullptr;
    }
    if (!pySpanInstance_Check((PyObject*)instance)) {
        PyErr_SetString(PyExc_TypeError, "addInstance expects a plSpanInstance");
        return nullptr;
    }
    self->fThis->addInstance(instance->fThis);
    instance->fPyOwned = false;
    Py_RETURN_NONE;
}

PY_METHOD_VA(Cluster, delInstance,
    "Params: idx\n"
    "Remove a plSpanInstance from the cluster")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delInstance expects an int");
        return nullptr;
    }
    self->fThis->delInstance(idx);
    Py_RETURN_NONE;
}

static PyMethodDef pyCluster_Methods[] = {
    pyCluster_read_method,
    pyCluster_write_method,
    pyCluster_clearInstances_method,
    pyCluster_addInstance_method,
    pyCluster_delInstance_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(Cluster, instances)
{
    PyObject* list = PyTuple_New(self->fThis->getInstances().size());
    for (size_t i=0; i<self->fThis->getInstances().size(); i++)
        PyTuple_SET_ITEM(list, i, pySpanInstance_FromSpanInstance(self->fThis->getInstances()[i]));
    return list;
}

PY_PROPERTY_SETTER_MSG(Cluster, instances, "To add instances, use addInstance")
PY_PROPERTY_GETSET_DECL(Cluster, instances)

PY_PROPERTY_PROXY_RO(plSpanEncoding, Cluster, encoding, getEncoding)
PY_PROPERTY_CREATABLE(plClusterGroup, ClusterGroup, Cluster, group, getGroup, setGroup)

static PyGetSetDef pyCluster_GetSet[] = {
    pyCluster_encoding_getset,
    pyCluster_group_getset,
    pyCluster_instances_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(Cluster, plCluster, "plCluster wrapper")

PY_PLASMA_TYPE_INIT(Cluster)
{
    pyCluster_Type.tp_dealloc = pyCluster_dealloc;
    pyCluster_Type.tp_init = pyCluster___init__;
    pyCluster_Type.tp_new = pyCluster_new;
    pyCluster_Type.tp_methods = pyCluster_Methods;
    pyCluster_Type.tp_getset = pyCluster_GetSet;
    if (PyType_CheckAndReady(&pyCluster_Type) < 0)
        return nullptr;

    Py_INCREF(&pyCluster_Type);
    return (PyObject*)&pyCluster_Type;
}

PY_PLASMA_IFC_METHODS(Cluster, plCluster)
