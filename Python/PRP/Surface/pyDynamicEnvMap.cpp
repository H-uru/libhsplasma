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
#include "PRP/pyCreatable.h"
#include "PRP/Surface/pyBitmap.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/Object/pySynchedObject.h"
#include "Math/pyGeometry3.h"
#include "Sys/pyColor.h"

// DynamicEnvMap

PY_PLASMA_NEW(DynamicEnvMap, plDynamicEnvMap)

PY_PROPERTY(plKey, DynamicEnvMap, rootNode, getRootNode, setRootNode)
PY_PROPERTY(hsVector3, DynamicEnvMap, position, getPosition, setPosition)
PY_PROPERTY(float, DynamicEnvMap, hither, getHither, setHither)
PY_PROPERTY(float, DynamicEnvMap, yon, getYon, setYon)
PY_PROPERTY(float, DynamicEnvMap, fogStart, getFogStart, setFogStart)
PY_PROPERTY(hsColorRGBA, DynamicEnvMap, color, getColor, setColor)
PY_PROPERTY(float, DynamicEnvMap, refreshRate, getRefreshRate, setRefreshRate)
PY_PROPERTY_VECTOR(plKey, DynamicEnvMap, visRegions, getVisRegions, setVisRegions)
PY_PROPERTY_VECTOR(ST::string, DynamicEnvMap, visRegionNames, getVisRegionNames, setVisRegionNames)
PY_PROPERTY(bool, DynamicEnvMap, incCharacters, getIncludeCharacters,
            setIncludeCharacters)

static PyGetSetDef pyDynamicEnvMap_GetSet[] = {
    pyDynamicEnvMap_rootNode_getset,
    pyDynamicEnvMap_position_getset,
    pyDynamicEnvMap_hither_getset,
    pyDynamicEnvMap_yon_getset,
    pyDynamicEnvMap_fogStart_getset,
    pyDynamicEnvMap_color_getset,
    pyDynamicEnvMap_refreshRate_getset,
    pyDynamicEnvMap_visRegions_getset,
    pyDynamicEnvMap_visRegionNames_getset,
    pyDynamicEnvMap_incCharacters_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(DynamicEnvMap, plDynamicEnvMap, "plDynamicEnvMap wrapper")

PY_PLASMA_TYPE_INIT(DynamicEnvMap)
{
    pyDynamicEnvMap_Type.tp_new = pyDynamicEnvMap_new;
    pyDynamicEnvMap_Type.tp_getset = pyDynamicEnvMap_GetSet;
    pyDynamicEnvMap_Type.tp_base = &pyCubicRenderTarget_Type;
    if (PyType_CheckAndReady(&pyDynamicEnvMap_Type) < 0)
        return nullptr;

    Py_INCREF(&pyDynamicEnvMap_Type);
    return (PyObject*)&pyDynamicEnvMap_Type;
}

PY_PLASMA_IFC_METHODS(DynamicEnvMap, plDynamicEnvMap)
