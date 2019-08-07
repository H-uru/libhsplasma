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

#include "pyOneShotMod.h"

#include <PRP/Modifier/plOneShotMod.h>
#include "pyModifier.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW(OneShotMod, plOneShotMod)

PY_PROPERTY(ST::string, OneShotMod, animName, getAnimName, setAnimName)
PY_PROPERTY(bool, OneShotMod, drivable, isDrivable, setDrivable)
PY_PROPERTY(bool, OneShotMod, reversable, isReversable, setReversable)
PY_PROPERTY(bool, OneShotMod, smartSeek, getSmartSeek, setSmartSeek)
PY_PROPERTY(bool, OneShotMod, noSeek, getNoSeek, setNoSeek)
PY_PROPERTY(float, OneShotMod, seekDuration, getSeekDuration, setSeekDuration)

static PyGetSetDef pyOneShotMod_GetSet[] = {
    pyOneShotMod_animName_getset,
    pyOneShotMod_drivable_getset,
    pyOneShotMod_reversable_getset,
    pyOneShotMod_smartSeek_getset,
    pyOneShotMod_noSeek_getset,
    pyOneShotMod_seekDuration_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(OneShotMod, plOneShotMod, "plOneShotMod wrapper")

PY_PLASMA_TYPE_INIT(OneShotMod)
{
    pyOneShotMod_Type.tp_new = pyOneShotMod_new;
    pyOneShotMod_Type.tp_getset = pyOneShotMod_GetSet;
    pyOneShotMod_Type.tp_base = &pyMultiModifier_Type;
    if (PyType_CheckAndReady(&pyOneShotMod_Type) < 0)
        return nullptr;

    Py_INCREF(&pyOneShotMod_Type);
    return (PyObject*)&pyOneShotMod_Type;
}

PY_PLASMA_IFC_METHODS(OneShotMod, plOneShotMod)
