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

PY_PROPERTY(float, DynamicCamMap, hither, getHither, setHither)
PY_PROPERTY(float, DynamicCamMap, yon, getYon, setYon)
PY_PROPERTY(float, DynamicCamMap, fogStart, getFogStart, setFogStart)
PY_PROPERTY(hsColorRGBA, DynamicCamMap, color, getColor, setColor)
PY_PROPERTY(float, DynamicCamMap, refreshRate, getRefreshRate, setRefreshRate)
PY_PROPERTY_VECTOR(plKey, DynamicCamMap, visRegions, getVisRegions, setVisRegions)
PY_PROPERTY_VECTOR(plKey, DynamicCamMap, targetNodes, getTargetNodes, setTargetNodes)
PY_PROPERTY_VECTOR(plKey, DynamicCamMap, matLayers, getMatLayers, setMatLayers)
PY_PROPERTY_VECTOR(ST::string, DynamicCamMap, visRegionNames, getVisRegionNames, setVisRegionNames)
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
