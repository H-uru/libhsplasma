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

#include "pyAGModifier.h"

#include <PRP/Avatar/plAGModifier.h>
#include "PRP/Modifier/pyModifier.h"

PY_PLASMA_NEW(AGModifier, plAGModifier)

PY_PROPERTY(ST::string, AGModifier, channelName, getChannelName, setChannelName)
PY_PROPERTY(bool, AGModifier, autoApply, getAutoApply, setAutoApply)
PY_PROPERTY(bool, AGModifier, enabled, getEnabled, setEnabled)

static PyGetSetDef pyAGModifier_GetSet[] = {
    pyAGModifier_channelName_getset,
    pyAGModifier_autoApply_getset,
    pyAGModifier_enabled_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(AGModifier, plAGModifier, "plAGModifier wrapper")

PY_PLASMA_TYPE_INIT(AGModifier)
{
    pyAGModifier_Type.tp_new = pyAGModifier_new;
    pyAGModifier_Type.tp_getset = pyAGModifier_GetSet;
    pyAGModifier_Type.tp_base = &pyModifier_Type;
    if (PyType_CheckAndReady(&pyAGModifier_Type) < 0)
        return nullptr;

    Py_INCREF(&pyAGModifier_Type);
    return (PyObject*)&pyAGModifier_Type;
}

PY_PLASMA_IFC_METHODS(AGModifier, plAGModifier)
