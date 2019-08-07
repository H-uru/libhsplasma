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

#include <PRP/Modifier/plPostEffectMod.h>
#include "pyPostEffectMod.h"
#include "PRP/Modifier/pyModifier.h"
#include "PRP/KeyedObject/pyKey.h"
#include "Math/pyMatrix.h"

PY_PLASMA_NEW(PostEffectMod, plPostEffectMod)

PY_PROPERTY(float, PostEffectMod, hither, getHither, setHither)
PY_PROPERTY(float, PostEffectMod, yon, getHither, setYon)
PY_PROPERTY(float, PostEffectMod, fovX, getFovX, setFovX)
PY_PROPERTY(float, PostEffectMod, fovY, getFovY, setFovY)
PY_PROPERTY(plKey, PostEffectMod, nodeKey, getNodeKey, setNodeKey)
PY_PROPERTY(hsMatrix44, PostEffectMod, defaultW2C, getDefaultW2C, setDefaultW2C)
PY_PROPERTY(hsMatrix44, PostEffectMod, defaultC2W, getDefaultC2W, setDefaultC2W)

static PyGetSetDef pyPostEffectMod_GetSet[] = {
    pyPostEffectMod_hither_getset,
    pyPostEffectMod_yon_getset,
    pyPostEffectMod_fovX_getset,
    pyPostEffectMod_fovY_getset,
    pyPostEffectMod_nodeKey_getset,
    pyPostEffectMod_defaultW2C_getset,
    pyPostEffectMod_defaultC2W_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(PostEffectMod, plPostEffectMod, "plPostEffectMod wrapper")

PY_PLASMA_TYPE_INIT(PostEffectMod)
{
    pyPostEffectMod_Type.tp_new = pyPostEffectMod_new;
    pyPostEffectMod_Type.tp_getset = pyPostEffectMod_GetSet;
    pyPostEffectMod_Type.tp_base = &pySingleModifier_Type;
    if (PyType_CheckAndReady(&pyPostEffectMod_Type) < 0)
        return nullptr;

    Py_INCREF(&pyPostEffectMod_Type);
    return (PyObject*)&pyPostEffectMod_Type;
}

PY_PLASMA_IFC_METHODS(PostEffectMod, plPostEffectMod)
