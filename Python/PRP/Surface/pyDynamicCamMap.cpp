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

PY_PLASMA_NEW(DynamicCamMap, plDynamicCamMap)

PY_METHOD_VA(DynamicCamMap, addMatLayer,
    "Params: key\n"
    "Adds a layer key")
{
    PyObject* key;
    if (!(PyArg_ParseTuple(args, "O", &key) && pyKey_Check(key))) {
        PyErr_SetString(PyExc_TypeError, "addMatLayer expects a plKey");
        return nullptr;
    }
    self->fThis->addMatLayer(pyPlasma_get<plKey>(key));
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(DynamicCamMap, clearMatLayers, "Clears the list of layer keys")
{
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
        return nullptr;
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
        return nullptr;
    }
    self->fThis->addTargetNode(pyPlasma_get<plKey>(key));
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
        return nullptr;
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
        return nullptr;
    }
    self->fThis->addVisRegion(pyPlasma_get<plKey>(key));
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
        return nullptr;
    }
    self->fThis->delVisRegion((size_t)idx);
    Py_RETURN_NONE;
}

PY_METHOD_VA(DynamicCamMap, addVisRegionName,
    "Params: name\n"
    "Adds a VisRegion name")
{
    PyObject* name;
    if (!(PyArg_ParseTuple(args, "O", &name) && pyPlasma_check<ST::string>(name))) {
        PyErr_SetString(PyExc_TypeError, "addVisRegionName expects a string");
        return nullptr;
    }
    self->fThis->addVisRegionName(pyPlasma_get<ST::string>(name));
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
        return nullptr;
    }
    self->fThis->delVisRegionName((size_t)idx);
    Py_RETURN_NONE;
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

PY_GETSET_GETTER_DECL(DynamicCamMap, visRegions)
{
    const std::vector<plKey>& keys = self->fThis->getVisRegions();
    PyObject* regionList = PyTuple_New(keys.size());
    for (size_t i=0; i<keys.size(); i++)
        PyTuple_SET_ITEM(regionList, i, pyPlasma_convert(keys[i]));
    return regionList;
}

PY_GETSET_SETTER_DECL(DynamicCamMap, visRegions)
{
    PY_PROPERTY_CHECK_NULL(visRegions)
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "visRegions should be a sequence of plKeys");
        return -1;
    }
    Py_ssize_t count = seq.size();
    std::vector<plKey> regions(count);
    for (Py_ssize_t i=0; i<count; i++) {
        PyObject* region = seq.get(i);
        if (pyKey_Check(region)) {
            regions[i] = pyPlasma_get<plKey>(region);
        } else {
            PyErr_SetString(PyExc_TypeError, "visRegions should be a sequence of plKeys");
            return -1;
        }
    }
    self->fThis->setVisRegions(regions);
    return 0;
}

PY_PROPERTY_GETSET_DECL(DynamicCamMap, visRegions)

PY_GETSET_GETTER_DECL(DynamicCamMap, targetNodes)
{
    const std::vector<plKey>& keys = self->fThis->getTargetNodes();
    PyObject* nodeList = PyTuple_New(keys.size());
    for (size_t i=0; i<keys.size(); i++)
        PyTuple_SET_ITEM(nodeList, i, pyPlasma_convert(keys[i]));
    return nodeList;
}

PY_GETSET_SETTER_DECL(DynamicCamMap, targetNodes)
{
    PY_PROPERTY_CHECK_NULL(targetNodes)
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "targetNodes should be a sequence of plKeys");
        return -1;
    }
    Py_ssize_t count = seq.size();
    std::vector<plKey> nodes(count);
    for (Py_ssize_t i=0; i<count; i++) {
        PyObject* node = seq.get(i);
        if (pyKey_Check(node)){
            nodes[i] = pyPlasma_get<plKey>(node);
        } else {
            PyErr_SetString(PyExc_TypeError, "targetNodes should be a sequence of plKeys");
            return -1;
        }
    }
    self->fThis->setTargetNodes(nodes);
    return 0;
}

PY_PROPERTY_GETSET_DECL(DynamicCamMap, targetNodes)

PY_GETSET_GETTER_DECL(DynamicCamMap, matLayers)
{
    const std::vector<plKey>& keys = self->fThis->getMatLayers();
    PyObject* layerList = PyTuple_New(keys.size());
    for (size_t i=0; i<keys.size(); i++)
        PyTuple_SET_ITEM(layerList, i, pyPlasma_convert(keys[i]));
    return layerList;
}

PY_GETSET_SETTER_DECL(DynamicCamMap, matLayers)
{
    PY_PROPERTY_CHECK_NULL(matLayers)
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "matLayers should be a sequence of plKeys");
        return -1;
    }
    Py_ssize_t count = seq.size();
    std::vector<plKey> layers(count);
    for (Py_ssize_t i=0; i<count; i++) {
        PyObject* layer = seq.get(i);
        if (pyKey_Check(layer)){
            layers[i] = pyPlasma_get<plKey>(layer);
        } else {
            PyErr_SetString(PyExc_TypeError, "matLayers should be a sequence of plKeys");
            return -1;
        }
    }
    self->fThis->setMatLayers(layers);
    return 0;
}

PY_PROPERTY_GETSET_DECL(DynamicCamMap, matLayers)

PY_GETSET_GETTER_DECL(DynamicCamMap, visRegionNames)
{
    const std::vector<ST::string>& names = self->fThis->getVisRegionNames();
    PyObject* regionNameList = PyTuple_New(names.size());
    for (size_t i=0; i<names.size(); i++)
        PyTuple_SET_ITEM(regionNameList, i, pyPlasma_convert(names[i]));
    return regionNameList;
}

PY_GETSET_SETTER_DECL(DynamicCamMap, visRegionNames)
{
    PY_PROPERTY_CHECK_NULL(visRegionNames)
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "visRegionNames should be a sequence of strings");
        return -1;
    }
    Py_ssize_t count = seq.size();
    std::vector<ST::string> names(count);
    for (Py_ssize_t i=0; i<count; i++) {
        PyObject* name = seq.get(i);
        if (pyPlasma_check<ST::string>(name)) {
            names[i] = pyPlasma_get<ST::string>(name);
        } else {
            PyErr_SetString(PyExc_TypeError, "visRegionNames should be a sequence of strings");
            return -1;
        }
    }
    self->fThis->setVisRegionNames(names);
    return 0;
}

PY_PROPERTY_GETSET_DECL(DynamicCamMap, visRegionNames)

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
    pyDynamicCamMap_visRegions_getset,
    pyDynamicCamMap_targetNodes_getset,
    pyDynamicCamMap_matLayers_getset,
    pyDynamicCamMap_visRegionNames_getset,
    pyDynamicCamMap_incCharacters_getset,
    pyDynamicCamMap_camera_getset,
    pyDynamicCamMap_rootNode_getset,
    pyDynamicCamMap_disableTexture_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(DynamicCamMap, plDynamicCamMap, "plDynamicCamMap wrapper")

PY_PLASMA_TYPE_INIT(DynamicCamMap)
{
    pyDynamicCamMap_Type.tp_new = pyDynamicCamMap_new;
    pyDynamicCamMap_Type.tp_methods = pyDynamicCamMap_Methods;
    pyDynamicCamMap_Type.tp_getset = pyDynamicCamMap_GetSet;
    pyDynamicCamMap_Type.tp_base = &pyRenderTarget_Type;
    if (PyType_CheckAndReady(&pyDynamicCamMap_Type) < 0)
        return nullptr;

    Py_INCREF(&pyDynamicCamMap_Type);
    return (PyObject*)&pyDynamicCamMap_Type;
}

PY_PLASMA_IFC_METHODS(DynamicCamMap, plDynamicCamMap)
