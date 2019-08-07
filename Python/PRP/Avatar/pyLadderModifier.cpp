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

#include "pyLadderModifier.h"

#include <PRP/Avatar/plLadderModifier.h>
#include "PRP/Modifier/pyModifier.h"
#include "PRP/KeyedObject/pyKey.h"
#include "Math/pyGeometry3.h"

/* pyAvLadderMod */
PY_PLASMA_NEW(AvLadderMod, plAvLadderMod)

PY_PROPERTY(bool, AvLadderMod, goingUp, getGoingUp, setGoingUp)
PY_PROPERTY(int, AvLadderMod, loops, getLoops, setLoops)
PY_PROPERTY(int, AvLadderMod, type, getType, setType)
PY_PROPERTY(bool, AvLadderMod, enabled, isEnabled, setEnabled)
PY_PROPERTY(hsVector3, AvLadderMod, ladderView, getLadderView, setLadderView)

static PyGetSetDef pyAvLadderMod_GetSet[] = {
    pyAvLadderMod_goingUp_getset,
    pyAvLadderMod_loops_getset,
    pyAvLadderMod_type_getset,
    pyAvLadderMod_enabled_getset,
    pyAvLadderMod_ladderView_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(AvLadderMod, plAvLadderMod, "plAvLadderMod wrapper")

PY_PLASMA_TYPE_INIT(AvLadderMod)
{
    pyAvLadderMod_Type.tp_new = pyAvLadderMod_new;
    pyAvLadderMod_Type.tp_getset = pyAvLadderMod_GetSet;
    pyAvLadderMod_Type.tp_base = &pySingleModifier_Type;
    if (PyType_CheckAndReady(&pyAvLadderMod_Type) < 0)
        return nullptr;

    /* Konstants */
    PY_TYPE_ADD_CONST(AvLadderMod, "kBig", plAvLadderMod::kBig);
    PY_TYPE_ADD_CONST(AvLadderMod, "kFourFeet", plAvLadderMod::kFourFeet);
    PY_TYPE_ADD_CONST(AvLadderMod, "kTwoFeet", plAvLadderMod::kTwoFeet);

    Py_INCREF(&pyAvLadderMod_Type);
    return (PyObject*)&pyAvLadderMod_Type;
}

PY_PLASMA_IFC_METHODS(AvLadderMod, plAvLadderMod)


/* pyLadderModifier */
PY_PLASMA_NEW(LadderModifier, plLadderModifier)

PY_PROPERTY(plKey, LadderModifier, topLogic, getTopLogic, setTopLogic)
PY_PROPERTY(plKey, LadderModifier, bottomLogic, getBottomLogic, setBottomLogic)
PY_PROPERTY(plKey, LadderModifier, mainLogic, getMainLogic, setMainLogic)
PY_PROPERTY(plKey, LadderModifier, exitTop, getExitTop, setExitTop)
PY_PROPERTY(plKey, LadderModifier, exitBottom, getExitBottom, setExitBottom)
PY_PROPERTY(plKey, LadderModifier, topPos, getTopPos, setTopPos)
PY_PROPERTY(plKey, LadderModifier, bottomPos, getBottomPos, setBottomPos)

static PyGetSetDef pyLadderModifier_GetSet[] = {
    pyLadderModifier_topLogic_getset,
    pyLadderModifier_bottomLogic_getset,
    pyLadderModifier_mainLogic_getset,
    pyLadderModifier_exitTop_getset,
    pyLadderModifier_exitBottom_getset,
    pyLadderModifier_topPos_getset,
    pyLadderModifier_bottomPos_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(LadderModifier, plLadderModifier, "plLadderModifier wrapper")

PY_PLASMA_TYPE_INIT(LadderModifier)
{
    pyLadderModifier_Type.tp_new = pyLadderModifier_new;
    pyLadderModifier_Type.tp_getset = pyLadderModifier_GetSet;
    pyLadderModifier_Type.tp_base = &pySingleModifier_Type;
    if (PyType_CheckAndReady(&pyLadderModifier_Type) < 0)
        return nullptr;

    Py_INCREF(&pyLadderModifier_Type);
    return (PyObject*)&pyLadderModifier_Type;
}

PY_PLASMA_IFC_METHODS(LadderModifier, plLadderModifier)
