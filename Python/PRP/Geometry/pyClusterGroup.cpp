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

PY_PLASMA_NEW(ClusterGroup, plClusterGroup)

PY_METHOD_VA(ClusterGroup, addCluster,
    "Params: region\n"
    "Add a plCluster object to the group")
{
    pyCluster* cluster;
    if (!PyArg_ParseTuple(args, "O", &cluster)) {
        PyErr_SetString(PyExc_TypeError, "addCluster expects a plCluster");
        return nullptr;
    }
    if (!pyCluster_Check((PyObject*)cluster)) {
        PyErr_SetString(PyExc_TypeError, "addCluster expects a plCluster");
        return nullptr;
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
        return nullptr;
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
        return nullptr;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addRegion expects a plKey");
        return nullptr;
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
        return nullptr;
    }
    self->fThis->delRegion(idx);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(ClusterGroup, clearRegions, "Remove all regions from the group")
{
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
        return nullptr;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addLight expects a plKey");
        return nullptr;
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
        return nullptr;
    }
    self->fThis->delLight(idx);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(ClusterGroup, clearLights, "Remove all lights from the group")
{
    self->fThis->clearLights();
    Py_RETURN_NONE;
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

PY_GETSET_GETTER_DECL(ClusterGroup, clusters)
{
    PyObject* list = PyTuple_New(self->fThis->getClusters().size());
    for (size_t i=0; i<self->fThis->getClusters().size(); i++)
        PyTuple_SET_ITEM(list, i, pyCluster_FromCluster(self->fThis->getClusters()[i]));
    return list;
}

PY_PROPERTY_SETTER_MSG(ClusterGroup, clusters, "To add clusters, use addCluster")
PY_PROPERTY_GETSET_DECL(ClusterGroup, clusters)

PY_GETSET_GETTER_DECL(ClusterGroup, regions)
{
    PyObject* list = PyTuple_New(self->fThis->getRegions().size());
    for (size_t i=0; i<self->fThis->getRegions().size(); i++)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(self->fThis->getRegions()[i]));
    return list;
}

PY_PROPERTY_SETTER_MSG(ClusterGroup, regions, "To add regions, use addRegion")
PY_PROPERTY_GETSET_DECL(ClusterGroup, regions)

PY_GETSET_GETTER_DECL(ClusterGroup, lights)
{
    PyObject* list = PyTuple_New(self->fThis->getLights().size());
    for (size_t i=0; i<self->fThis->getLights().size(); i++)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(self->fThis->getLights()[i]));
    return list;
}

PY_PROPERTY_SETTER_MSG(ClusterGroup, lights, "To add lights, use addLight")
PY_PROPERTY_GETSET_DECL(ClusterGroup, lights)

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
    pyClusterGroup_clusters_getset,
    pyClusterGroup_regions_getset,
    pyClusterGroup_lights_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ClusterGroup, plClusterGroup, "pyClusterGroup wrapper")

PY_PLASMA_TYPE_INIT(ClusterGroup)
{
    pyClusterGroup_Type.tp_new = pyClusterGroup_new;
    pyClusterGroup_Type.tp_methods = pyClusterGroup_Methods;
    pyClusterGroup_Type.tp_getset = pyClusterGroup_GetSet;
    pyClusterGroup_Type.tp_base = &pyKeyedObject_Type;
    if (PyType_CheckAndReady(&pyClusterGroup_Type) < 0)
        return nullptr;

    Py_INCREF(&pyClusterGroup_Type);
    return (PyObject*)&pyClusterGroup_Type;
}

PY_PLASMA_IFC_METHODS(ClusterGroup, plClusterGroup)
