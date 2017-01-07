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

#include "pyDynamicEnvMap.h"

#include <PRP/Surface/plDynamicEnvMap.h>
#include "pyRenderTarget.h"
#include "PRP/KeyedObject/pyKey.h"
#include "Math/pyGeometry3.h"
#include "Sys/pyColor.h"

extern "C" {

PY_PLASMA_NEW(DynamicCamMap, plDynamicCamMap)

PY_METHOD_VA(DynamicCamMap, addMatLayer,
    "Params: key\n"
    "Adds a layer key")
{
    PyObject* key;
    if (!(PyArg_ParseTuple(args, "O", &key) && pyKey_Check(key))) {
        PyErr_SetString(PyExc_TypeError, "addMatLayer expects a plKey");
        return NULL;
    }
    self->fThis->addMatLayer(*((pyKey*)key)->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(DynamicCamMap, clearMatLayers, "Clears the list of layer keys") {
    self->fThis->clearMatLayers();
    Py_RETURN_NONE;
}

PY_METHOD_VA(DynamicCamMap, delMatLayer,
    "Params: idx\n"
    "Removes a layer key")
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delMatLayer expects an int");
        return NULL;
    }
    self->fThis->delMatLayer((size_t)idx);
    Py_RETURN_NONE;
}

PY_METHOD_VA(DynamicCamMap, addTargetNode,
    "Params: key\n"
    "Adds a target SceneObject key")
{
    PyObject* key;
    if (!(PyArg_ParseTuple(args, "O", &key) && pyKey_Check(key))) {
        PyErr_SetString(PyExc_TypeError, "addTargetNode expects a plKey");
        return NULL;
    }
    self->fThis->addTargetNode(*((pyKey*)key)->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(DynamicCamMap, clearTargetNodes,
    "Clears the list of target SceneObject keys")
{
    self->fThis->clearTargetNodes();
    Py_RETURN_NONE;
}

PY_METHOD_VA(DynamicCamMap, delTargetNode,
    "Params: idx\n"
    "Removes a target SceneObject key")
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delTargetNode expects an int");
        return NULL;
    }
    self->fThis->delTargetNode((size_t)idx);
    Py_RETURN_NONE;
}

PY_METHOD_VA(DynamicCamMap, addVisRegion,
    "Params: key\n"
    "Adds a VisRegion key")
{
    PyObject* key;
    if (!(PyArg_ParseTuple(args, "O", &key) && pyKey_Check(key))) {
        PyErr_SetString(PyExc_TypeError, "addVisRegion expects a plKey");
        return NULL;
    }
    self->fThis->addVisRegion(*((pyKey*)key)->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(DynamicCamMap, clearVisRegions,
    "Clears the list of VisRegion keys")
{
    self->fThis->clearVisRegions();
    Py_RETURN_NONE;
}

PY_METHOD_VA(DynamicCamMap, delVisRegion,
    "Params: idx\n"
    "Removes a VisRegion key")
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delVisRegion expects an int");
        return NULL;
    }
    self->fThis->delVisRegion((size_t)idx);
    Py_RETURN_NONE;
}

PY_METHOD_VA(DynamicCamMap, addVisRegionName,
    "Params: name\n"
    "Adds a VisRegion name")
{
    PyObject* name;
    if (!(PyArg_ParseTuple(args, "O", &name) && PyAnyStr_Check(name))) {
        PyErr_SetString(PyExc_TypeError, "addVisRegionName expects a string");
        return NULL;
    }
    self->fThis->addVisRegionName(PyStr_To_PlStr(name));
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(DynamicCamMap, clearVisRegionNames,
    "Clears the list of VisRegion names")
{
    self->fThis->clearVisRegionNames();
    Py_RETURN_NONE;
}

PY_METHOD_VA(DynamicCamMap, delVisRegionName,
    "Params: idx\n"
    "Removes a VisRegion name")
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delVisRegionName expects an int");
        return NULL;
    }
    self->fThis->delVisRegionName((size_t)idx);
    Py_RETURN_NONE;
}

static PyObject* pyDynamicCamMap_getVisRegions(pyDynamicCamMap* self, void*) {
    const std::vector<plKey>& keys = self->fThis->getVisRegions();
    PyObject* regionList = PyList_New(keys.size());
    for (size_t i=0; i<keys.size(); i++)
        PyList_SET_ITEM(regionList, i, pyKey_FromKey(keys[i]));
    return regionList;
}

static PyObject* pyDynamicCamMap_getTargetNodes(pyDynamicCamMap* self, void*) {
    const std::vector<plKey>& keys = self->fThis->getTargetNodes();
    PyObject* nodeList = PyList_New(keys.size());
    for (size_t i=0; i<keys.size(); i++)
        PyList_SET_ITEM(nodeList, i, pyKey_FromKey(keys[i]));
    return nodeList;
}

static PyObject* pyDynamicCamMap_getMatLayers(pyDynamicCamMap* self, void*) {
    const std::vector<plKey>& keys = self->fThis->getMatLayers();
    PyObject* layerList = PyList_New(keys.size());
    for (size_t i=0; i<keys.size(); i++)
        PyList_SET_ITEM(layerList, i, pyKey_FromKey(keys[i]));
    return layerList;
}

static PyObject* pyDynamicCamMap_getVisRegionNames(pyDynamicCamMap* self, void*) {
    const std::vector<plString>& names = self->fThis->getVisRegionNames();
    PyObject* regionNameList = PyList_New(names.size());
    for (size_t i=0; i<names.size(); i++)
        PyList_SET_ITEM(regionNameList, i, PlasmaString_To_PyString(names[i]));
    return regionNameList;
}

static int pyDynamicCamMap_setVisRegions(pyDynamicCamMap* self, PyObject* value, void*) {
    if (value == NULL || !PySequence_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "visRegions should be a sequence of plKeys");
        return -1;
    }
    std::vector<plKey> regions;
    regions.resize(PySequence_Size(value));
    for (Py_ssize_t i=0; i<PySequence_Size(value); i++) {
        PyObject* region = PySequence_GetItem(value, i);
        if (pyKey_Check(region)){
            regions[i] = *(reinterpret_cast<pyKey *>(region)->fThis);
        } else {
            PyErr_SetString(PyExc_TypeError, "visRegions should be a sequence of plKeys");
            return -1;
        }
    }
    self->fThis->setVisRegions(regions);
    return 0;
}

static int pyDynamicCamMap_setTargetNodes(pyDynamicCamMap* self, PyObject* value, void*) {
    if (value == NULL || !PySequence_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "targetNodes should be a sequence of plKeys");
        return -1;
    }
    std::vector<plKey> nodes;
    nodes.resize(PySequence_Size(value));
    for (Py_ssize_t i=0; i<PySequence_Size(value); i++) {
        PyObject* node = PySequence_GetItem(value, i);
        if (pyKey_Check(node)){
            nodes[i] = *(reinterpret_cast<pyKey *>(node)->fThis);
        } else {
            PyErr_SetString(PyExc_TypeError, "targetNodes should be a sequence of plKeys");
            return -1;
        }
    }
    self->fThis->setTargetNodes(nodes);
    return 0;
}

static int pyDynamicCamMap_setMatLayers(pyDynamicCamMap* self, PyObject* value, void*) {
    if (value == NULL || !PySequence_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "matLayers should be a sequence of plKeys");
        return -1;
    }
    std::vector<plKey> layers;
    layers.resize(PySequence_Size(value));
    for (Py_ssize_t i=0; i<PySequence_Size(value); i++) {
        PyObject* layer = PySequence_GetItem(value, i);
        if (pyKey_Check(layer)){
            layers[i] = *(reinterpret_cast<pyKey *>(layer)->fThis);
        } else {
            PyErr_SetString(PyExc_TypeError, "matLayers should be a sequence of plKeys");
            return -1;
        }
    }
    self->fThis->setMatLayers(layers);
    return 0;
}

static int pyDynamicCamMap_setVisRegionNames(pyDynamicCamMap* self, PyObject* value, void*) {
    if (value == NULL || !PySequence_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "visRegionNames should be a sequence of strings");
        return -1;
    }
    std::vector<plString> names;
    names.resize(PySequence_Size(value));
    for (Py_ssize_t i=0; i<PySequence_Size(value); i++) {
        PyObject* name = PySequence_GetItem(value, i);
        if (PyAnyStr_Check(name)) {
            names[i] = PyString_To_PlasmaString(name);
        } else {
            PyErr_SetString(PyExc_TypeError, "visRegionNames should be a sequence of strings");
            return -1;
        }
    }
    self->fThis->setVisRegionNames(names);
    return 0;
}

static PyMethodDef pyDynamicCamMap_Methods[] = {
    pyDynamicCamMap_addMatLayer_method,
    pyDynamicCamMap_clearMatLayers_method,
    pyDynamicCamMap_delMatLayer_method,
    pyDynamicCamMap_addTargetNode_method,
    pyDynamicCamMap_clearTargetNodes_method,
    pyDynamicCamMap_delTargetNode_method,
    pyDynamicCamMap_addVisRegion_method,
    pyDynamicCamMap_clearVisRegions_method,
    pyDynamicCamMap_delVisRegion_method,
    pyDynamicCamMap_addVisRegionName_method,
    pyDynamicCamMap_clearVisRegionNames_method,
    pyDynamicCamMap_delVisRegionName_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY(float, DynamicCamMap, hither, getHither, setHither)
PY_PROPERTY(float, DynamicCamMap, yon, getYon, setYon)
PY_PROPERTY(float, DynamicCamMap, fogStart, getFogStart, setFogStart)
PY_PROPERTY(hsColorRGBA, DynamicCamMap, color, getColor, setColor)
PY_PROPERTY(float, DynamicCamMap, refreshRate, getRefreshRate, setRefreshRate)
PY_PROPERTY(bool, DynamicCamMap, incCharacters, getIncludeCharacters,
            setIncludeCharacters)
PY_PROPERTY(plKey, DynamicCamMap, camera, getCamera, setCamera)
PY_PROPERTY(plKey, DynamicCamMap, rootNode, getRootNode, setRootNode)
PY_PROPERTY(plKey, DynamicCamMap, disableTexture, getDisableTexture, setDisableTexture)

static PyGetSetDef pyDynamicCamMap_GetSet[] = {
    pyDynamicCamMap_hither_getset,
    pyDynamicCamMap_yon_getset,
    pyDynamicCamMap_fogStart_getset,
    pyDynamicCamMap_color_getset,
    pyDynamicCamMap_refreshRate_getset,
    { _pycs("visRegions"), (getter)pyDynamicCamMap_getVisRegions, (setter)pyDynamicCamMap_setVisRegions, NULL, NULL },
    { _pycs("targetNodes"), (getter)pyDynamicCamMap_getTargetNodes, (setter)pyDynamicCamMap_setTargetNodes, NULL, NULL },
    { _pycs("matLayers"), (getter)pyDynamicCamMap_getMatLayers, (setter)pyDynamicCamMap_setMatLayers, NULL, NULL },
    { _pycs("visRegionNames"), (getter)pyDynamicCamMap_getVisRegionNames, (setter)pyDynamicCamMap_setVisRegionNames, NULL, NULL },
    pyDynamicCamMap_incCharacters_getset,
    pyDynamicCamMap_camera_getset,
    pyDynamicCamMap_rootNode_getset,
    pyDynamicCamMap_disableTexture_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(DynamicCamMap, plDynamicCamMap, "plDynamicCamMap wrapper")

PY_PLASMA_TYPE_INIT(DynamicCamMap) {
    pyDynamicCamMap_Type.tp_new = pyDynamicCamMap_new;
    pyDynamicCamMap_Type.tp_methods = pyDynamicCamMap_Methods;
    pyDynamicCamMap_Type.tp_getset = pyDynamicCamMap_GetSet;
    pyDynamicCamMap_Type.tp_base = &pyRenderTarget_Type;
    if (PyType_Ready(&pyDynamicCamMap_Type) < 0)
        return NULL;

    Py_INCREF(&pyDynamicCamMap_Type);
    return (PyObject*)&pyDynamicCamMap_Type;
}

PY_PLASMA_IFC_METHODS(DynamicCamMap, plDynamicCamMap)

}
