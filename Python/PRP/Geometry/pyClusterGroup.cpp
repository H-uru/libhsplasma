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

#include "pyClusterGroup.h"

#include <PRP/Geometry/plClusterGroup.h>
#include "pyCluster.h"
#include "pySpanTemplate.h"
#include "PRP/KeyedObject/pyKeyedObject.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/pyCreatable.h"

extern "C" {

PY_PLASMA_NEW(ClusterGroup, plClusterGroup)

PY_METHOD_VA(ClusterGroup, addCluster,
    "Params: region\n"
    "Add a plCluster object to the group")
{
    pyCluster* cluster;
    if (!PyArg_ParseTuple(args, "O", &cluster)) {
        PyErr_SetString(PyExc_TypeError, "addCluster expects a plCluster");
        return NULL;
    }
    if (!pyCluster_Check((PyObject*)cluster)) {
        PyErr_SetString(PyExc_TypeError, "addCluster expects a plCluster");
        return NULL;
    }
    self->fThis->addCluster(cluster->fThis);
    cluster->fPyOwned = false;
    Py_RETURN_NONE;
}

PY_METHOD_VA(ClusterGroup, delCluster,
    "Params: idx\n"
    "Remove a plCluster object from the group")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delCluster expects an int");
        return NULL;
    }
    self->fThis->delCluster(idx);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(ClusterGroup, clearClusters, "Remove all clusters from the group") {
    self->fThis->clearClusters();
    Py_RETURN_NONE;
}

PY_METHOD_VA(ClusterGroup, addRegion,
    "Params: key\n"
    "Add a region reference to the group")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addRegion expects a plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addRegion expects a plKey");
        return NULL;
    }
    self->fThis->addRegion(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(ClusterGroup, delRegion,
    "Params: idx\n"
    "Remove a region reference from the group")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delRegion expects an int");
        return NULL;
    }
    self->fThis->delRegion(idx);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(ClusterGroup, clearRegions, "Remove all regions from the group") {
    self->fThis->clearRegions();
    Py_RETURN_NONE;
}

PY_METHOD_VA(ClusterGroup, addLight,
    "Params: key\n"
    "Add a light reference to the group")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addLight expects a plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addLight expects a plKey");
        return NULL;
    }
    self->fThis->addLight(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(ClusterGroup, delLight,
    "Params: idx\n"
    "Remove a light reference from the group")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delLight expects an int");
        return NULL;
    }
    self->fThis->delLight(idx);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(ClusterGroup, clearLights, "Remove all lights from the group") {
    self->fThis->clearLights();
    Py_RETURN_NONE;
}

static PyObject* pyClusterGroup_getClusters(pyClusterGroup* self, void*) {
    PyObject* list = PyList_New(self->fThis->getClusters().size());
    for (size_t i=0; i<self->fThis->getClusters().size(); i++)
        PyList_SET_ITEM(list, i, pyCluster_FromCluster(self->fThis->getClusters()[i]));
    return list;
}

static PyObject* pyClusterGroup_getRegions(pyClusterGroup* self, void*) {
    PyObject* list = PyList_New(self->fThis->getRegions().size());
    for (size_t i=0; i<self->fThis->getRegions().size(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getRegions()[i]));
    return list;
}

static PyObject* pyClusterGroup_getLights(pyClusterGroup* self, void*) {
    PyObject* list = PyList_New(self->fThis->getLights().size());
    for (size_t i=0; i<self->fThis->getLights().size(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getLights()[i]));
    return list;
}

static int pyClusterGroup_setClusters(pyClusterGroup* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add clusters, use addCluster");
    return -1;
}

static int pyClusterGroup_setRegions(pyClusterGroup* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add regions, use addRegion");
    return -1;
}

static int pyClusterGroup_setLights(pyClusterGroup* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add lights, use addLight");
    return -1;
}

static PyMethodDef pyClusterGroup_Methods[] = {
    pyClusterGroup_addCluster_method,
    pyClusterGroup_delCluster_method,
    pyClusterGroup_clearClusters_method,
    pyClusterGroup_addRegion_method,
    pyClusterGroup_delRegion_method,
    pyClusterGroup_clearRegions_method,
    pyClusterGroup_addLight_method,
    pyClusterGroup_delLight_method,
    pyClusterGroup_clearLights_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY_PROXY_RO(plLODDist, ClusterGroup, LOD, getLOD)
PY_PROPERTY_PROXY_RO(plSpanTemplate, ClusterGroup, template, getTemplate)
PY_PROPERTY(plKey, ClusterGroup, material, getMaterial, setMaterial)
PY_PROPERTY(plKey, ClusterGroup, sceneNode, getSceneNode, setSceneNode)
PY_PROPERTY(plKey, ClusterGroup, drawable, getDrawable, setDrawable)
PY_PROPERTY(unsigned int, ClusterGroup, renderLevel, getRenderLevel, setRenderLevel)

static PyGetSetDef pyClusterGroup_GetSet[] = {
    pyClusterGroup_LOD_getset,
    pyClusterGroup_template_getset,
    pyClusterGroup_material_getset,
    pyClusterGroup_sceneNode_getset,
    pyClusterGroup_drawable_getset,
    pyClusterGroup_renderLevel_getset,
    { _pycs("clusters"), (getter)pyClusterGroup_getClusters,
        (setter)pyClusterGroup_setClusters, NULL, NULL },
    { _pycs("regions"), (getter)pyClusterGroup_getRegions,
        (setter)pyClusterGroup_setRegions, NULL, NULL },
    { _pycs("lights"), (getter)pyClusterGroup_getLights,
        (setter)pyClusterGroup_setLights, NULL, NULL },
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ClusterGroup, plClusterGroup, "pyClusterGroup wrapper")

PY_PLASMA_TYPE_INIT(ClusterGroup) {
    pyClusterGroup_Type.tp_new = pyClusterGroup_new;
    pyClusterGroup_Type.tp_methods = pyClusterGroup_Methods;
    pyClusterGroup_Type.tp_getset = pyClusterGroup_GetSet;
    pyClusterGroup_Type.tp_base = &pyKeyedObject_Type;
    if (PyType_Ready(&pyClusterGroup_Type) < 0)
        return NULL;

    Py_INCREF(&pyClusterGroup_Type);
    return (PyObject*)&pyClusterGroup_Type;
}

PY_PLASMA_IFC_METHODS(ClusterGroup, plClusterGroup)

}
