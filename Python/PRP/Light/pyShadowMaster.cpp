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

#include "pyShadowMaster.h"

#include <PRP/Light/plShadowMaster.h>
#include "PRP/Object/pyObjInterface.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW(ShadowMaster, plShadowMaster)

PY_PROPERTY(float, ShadowMaster, attenDist, getAttenDist, setAttenDist)
PY_PROPERTY(float, ShadowMaster, maxDist, getMaxDist, setMaxDist)
PY_PROPERTY(float, ShadowMaster, minDist, getMinDist, setMinDist)
PY_PROPERTY(float, ShadowMaster, power, getPower, setPower)
PY_PROPERTY(unsigned int, ShadowMaster, maxSize, getMaxSize, setMaxSize)
PY_PROPERTY(unsigned int, ShadowMaster, minSize, getMinSize, setMinSize)

static PyGetSetDef pyShadowMaster_GetSet[] = {
    pyShadowMaster_attenDist_getset,
    pyShadowMaster_maxDist_getset,
    pyShadowMaster_minDist_getset,
    pyShadowMaster_power_getset,
    pyShadowMaster_maxSize_getset,
    pyShadowMaster_minSize_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ShadowMaster, plShadowMaster, "plShadowMaster wrapper")

PY_PLASMA_TYPE_INIT(ShadowMaster)
{
    pyShadowMaster_Type.tp_new = pyShadowMaster_new;
    pyShadowMaster_Type.tp_getset = pyShadowMaster_GetSet;
    pyShadowMaster_Type.tp_base = &pyObjInterface_Type;
    if (PyType_CheckAndReady(&pyShadowMaster_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(ShadowMaster, "kDisable", plShadowMaster::kDisable);
    PY_TYPE_ADD_CONST(ShadowMaster, "kSelfShadow", plShadowMaster::kSelfShadow);
    PY_TYPE_ADD_CONST(ShadowMaster, "kNumProps", plShadowMaster::kNumProps);

    Py_INCREF(&pyShadowMaster_Type);
    return (PyObject*)&pyShadowMaster_Type;
}

PY_PLASMA_IFC_METHODS(ShadowMaster, plShadowMaster)
