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

#include "pyShadowCaster.h"

#include <PRP/Light/plShadowCaster.h>
#include "PRP/Modifier/pyModifier.h"

PY_PLASMA_NEW(ShadowCaster, plShadowCaster)

PY_PROPERTY(unsigned char, ShadowCaster, castFlags, getCastFlags, setCastFlags)
PY_PROPERTY(float, ShadowCaster, boost, getBoost, setBoost)
PY_PROPERTY(float, ShadowCaster, attenScale, getAttenScale, setAttenScale)
PY_PROPERTY(float, ShadowCaster, blurScale, getBlurScale, setBlurScale)
PY_PROPERTY(float, ShadowCaster, maxOpacity, getMaxOpacity, setMaxOpacity)

static PyGetSetDef pyShadowCaster_GetSet[] = {
    pyShadowCaster_castFlags_getset,
    pyShadowCaster_boost_getset,
    pyShadowCaster_attenScale_getset,
    pyShadowCaster_blurScale_getset,
    pyShadowCaster_maxOpacity_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ShadowCaster, plShadowCaster, "plShadowCaster wrapper")

PY_PLASMA_TYPE_INIT(ShadowCaster)
{
    pyShadowCaster_Type.tp_new = pyShadowCaster_new;
    pyShadowCaster_Type.tp_getset = pyShadowCaster_GetSet;
    pyShadowCaster_Type.tp_base = &pyMultiModifier_Type;
    if (PyType_CheckAndReady(&pyShadowCaster_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(ShadowCaster, "kNone", plShadowCaster::kNone);
    PY_TYPE_ADD_CONST(ShadowCaster, "kSelfShadow", plShadowCaster::kSelfShadow);
    PY_TYPE_ADD_CONST(ShadowCaster, "kPerspective", plShadowCaster::kPerspective);
    PY_TYPE_ADD_CONST(ShadowCaster, "kLimitRes", plShadowCaster::kLimitRes);

    Py_INCREF(&pyShadowCaster_Type);
    return (PyObject*)&pyShadowCaster_Type;
}

PY_PLASMA_IFC_METHODS(ShadowCaster, plShadowCaster)
