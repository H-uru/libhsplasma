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

#include <PRP/Light/plOmniLightInfo.h>
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW(SpotLightInfo, plSpotLightInfo)

PY_PROPERTY(float, SpotLightInfo, falloff, getFalloff, setFalloff)
PY_PROPERTY(float, SpotLightInfo, spotInner, getSpotInner, setSpotInner)
PY_PROPERTY(float, SpotLightInfo, spotOuter, getSpotOuter, setSpotOuter)

static PyGetSetDef pySpotLightInfo_GetSet[] = {
    pySpotLightInfo_falloff_getset,
    pySpotLightInfo_spotInner_getset,
    pySpotLightInfo_spotOuter_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(SpotLightInfo, plSpotLightInfo, "plSpotLightInfo wrapper")

PY_PLASMA_TYPE_INIT(SpotLightInfo)
{
    pySpotLightInfo_Type.tp_new = pySpotLightInfo_new;
    pySpotLightInfo_Type.tp_getset = pySpotLightInfo_GetSet;
    pySpotLightInfo_Type.tp_base = &pyOmniLightInfo_Type;
    if (PyType_CheckAndReady(&pySpotLightInfo_Type) < 0)
        return nullptr;

    Py_INCREF(&pySpotLightInfo_Type);
    return (PyObject*)&pySpotLightInfo_Type;
}

PY_PLASMA_IFC_METHODS(SpotLightInfo, plSpotLightInfo)
