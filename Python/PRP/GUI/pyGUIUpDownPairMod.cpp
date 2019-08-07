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

#include <PRP/GUI/pfGUIUpDownPairMod.h>
#include "pyGUIUpDownPairMod.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/GUI/pyGUIValueCtrl.h"

PY_PLASMA_NEW(GUIUpDownPairMod, pfGUIUpDownPairMod)

PY_PROPERTY(plKey, GUIUpDownPairMod, upControl, getUpControl, setUpControl)
PY_PROPERTY(plKey, GUIUpDownPairMod, downControl, getDownControl, setDownControl)

static PyGetSetDef pyGUIUpDownPairMod_GetSet[] = {
    pyGUIUpDownPairMod_upControl_getset,
    pyGUIUpDownPairMod_downControl_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(GUIUpDownPairMod, pfGUIUpDownPairMod, "pfGUIUpDownPairMod wrapper")

PY_PLASMA_TYPE_INIT(GUIUpDownPairMod)
{
    pyGUIUpDownPairMod_Type.tp_new = pyGUIUpDownPairMod_new;
    pyGUIUpDownPairMod_Type.tp_getset = pyGUIUpDownPairMod_GetSet;
    pyGUIUpDownPairMod_Type.tp_base = &pyGUIValueCtrl_Type;
    if (PyType_CheckAndReady(&pyGUIUpDownPairMod_Type) < 0)
        return nullptr;

    Py_INCREF(&pyGUIUpDownPairMod_Type);
    return (PyObject*)&pyGUIUpDownPairMod_Type;
}

PY_PLASMA_IFC_METHODS(GUIUpDownPairMod, pfGUIUpDownPairMod)
