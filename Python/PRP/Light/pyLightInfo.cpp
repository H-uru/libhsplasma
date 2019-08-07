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

#include "pyLightInfo.h"

#include <PRP/Light/plLightInfo.h>
#include "PRP/Object/pyObjInterface.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/pyCreatable.h"
#include "Sys/pyColor.h"
#include "Math/pyMatrix.h"

PY_PLASMA_NEW_MSG(LightInfo, "plLightInfo is abstract")

PY_METHOD_NOARGS(LightInfo, clearVisRegions, "Remove all VisRegions from the light")
{
    self->fThis->clearVisRegions();
    Py_RETURN_NONE;
}

PY_METHOD_VA(LightInfo, addVisRegion,
    "Params: regionKey\n"
    "Add a VisRegion to the light")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key) || !pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addVisRegion expects a plKey");
        return nullptr;
    }
    self->fThis->addVisRegion(*key->fThis);
    Py_RETURN_NONE;
}

static PyMethodDef pyLightInfo_Methods[] = {
    pyLightInfo_clearVisRegions_method,
    pyLightInfo_addVisRegion_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(LightInfo, visRegions)
{
    PyObject* list = PyTuple_New(self->fThis->getVisRegions().size());
    for (size_t i=0; i<self->fThis->getVisRegions().size(); i++)
        PyTuple_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getVisRegions()[i]));
    return list;
}

PY_PROPERTY_SETTER_MSG(LightInfo, visRegions, "To add Vis Regions, use addVisRegion()")
PY_PROPERTY_GETSET_DECL(LightInfo, visRegions)

PY_PROPERTY(hsColorRGBA, LightInfo, ambient, getAmbient, setAmbient)
PY_PROPERTY(hsColorRGBA, LightInfo, diffuse, getDiffuse, setDiffuse)
PY_PROPERTY(hsColorRGBA, LightInfo, specular, getSpecular, setSpecular)
PY_PROPERTY(hsMatrix44, LightInfo, lightToLocal, getLightToLocal, setLightToLocal)
PY_PROPERTY(hsMatrix44, LightInfo, localToLight, getLocalToLight, setLocalToLight)
PY_PROPERTY(hsMatrix44, LightInfo, lightToWorld, getLightToWorld, setLightToWorld)
PY_PROPERTY(hsMatrix44, LightInfo, worldToLight, getWorldToLight, setWorldToLight)
PY_PROPERTY(plKey, LightInfo, projection, getProjection, setProjection)
PY_PROPERTY(plKey, LightInfo, softVolume, getSoftVolume, setSoftVolume)
PY_PROPERTY(plKey, LightInfo, sceneNode, getSceneNode, setSceneNode)

static PyGetSetDef pyLightInfo_GetSet[] = {
    pyLightInfo_ambient_getset,
    pyLightInfo_diffuse_getset,
    pyLightInfo_specular_getset,
    pyLightInfo_lightToLocal_getset,
    pyLightInfo_localToLight_getset,
    pyLightInfo_lightToWorld_getset,
    pyLightInfo_worldToLight_getset,
    pyLightInfo_projection_getset,
    pyLightInfo_softVolume_getset,
    pyLightInfo_sceneNode_getset,
    pyLightInfo_visRegions_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(LightInfo, plLightInfo, "plLightInfo wrapper")

PY_PLASMA_TYPE_INIT(LightInfo)
{
    pyLightInfo_Type.tp_new = pyLightInfo_new;
    pyLightInfo_Type.tp_methods = pyLightInfo_Methods;
    pyLightInfo_Type.tp_getset = pyLightInfo_GetSet;
    pyLightInfo_Type.tp_base = &pyObjInterface_Type;
    if (PyType_CheckAndReady(&pyLightInfo_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(LightInfo, "kLPObsolete", plLightInfo::kLPObsolete);
    PY_TYPE_ADD_CONST(LightInfo, "kLPCastShadows", plLightInfo::kLPCastShadows);
    PY_TYPE_ADD_CONST(LightInfo, "kLPMovable", plLightInfo::kLPMovable);
    PY_TYPE_ADD_CONST(LightInfo, "kLPHasIncludes", plLightInfo::kLPHasIncludes);
    PY_TYPE_ADD_CONST(LightInfo, "kLPIncludesChars", plLightInfo::kLPIncludesChars);
    PY_TYPE_ADD_CONST(LightInfo, "kLPOverAll", plLightInfo::kLPOverAll);
    PY_TYPE_ADD_CONST(LightInfo, "kLPHasSpecular", plLightInfo::kLPHasSpecular);
    PY_TYPE_ADD_CONST(LightInfo, "kLPShadowOnly", plLightInfo::kLPShadowOnly);
    PY_TYPE_ADD_CONST(LightInfo, "kLPShadowLightGroup", plLightInfo::kLPShadowLightGroup);
    PY_TYPE_ADD_CONST(LightInfo, "kLPForceProj", plLightInfo::kLPForceProj);

    Py_INCREF(&pyLightInfo_Type);
    return (PyObject*)&pyLightInfo_Type;
}

PY_PLASMA_IFC_METHODS(LightInfo, plLightInfo)
