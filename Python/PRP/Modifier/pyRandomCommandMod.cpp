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

#include "pyRandomCommandMod.h"

#include <PRP/Modifier/plRandomCommandMod.h>
#include "pyModifier.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW(RandomCommandMod, plRandomCommandMod)

PY_PROPERTY(unsigned char, RandomCommandMod, state, getState, setState)
PY_PROPERTY(unsigned char, RandomCommandMod, mode, getMode, setMode)
PY_PROPERTY(float, RandomCommandMod, minDelay, getMinDelay, setMinDelay)
PY_PROPERTY(float, RandomCommandMod, maxDelay, getMaxDelay, setMaxDelay)

static PyGetSetDef pyRandomCommandMod_GetSet[] = {
    pyRandomCommandMod_state_getset,
    pyRandomCommandMod_mode_getset,
    pyRandomCommandMod_minDelay_getset,
    pyRandomCommandMod_maxDelay_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(RandomCommandMod, plRandomCommandMod, "plRandomCommandMod wrapper")

PY_PLASMA_TYPE_INIT(RandomCommandMod)
{
    pyRandomCommandMod_Type.tp_new = pyRandomCommandMod_new;
    pyRandomCommandMod_Type.tp_getset = pyRandomCommandMod_GetSet;
    pyRandomCommandMod_Type.tp_base = &pySingleModifier_Type;
    if (PyType_CheckAndReady(&pyRandomCommandMod_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(RandomCommandMod, "kNormal", plRandomCommandMod::kNormal);
    PY_TYPE_ADD_CONST(RandomCommandMod, "kNoRepeats", plRandomCommandMod::kNoRepeats);
    PY_TYPE_ADD_CONST(RandomCommandMod, "kCoverall", plRandomCommandMod::kCoverall);
    PY_TYPE_ADD_CONST(RandomCommandMod, "kOneCycle", plRandomCommandMod::kOneCycle);
    PY_TYPE_ADD_CONST(RandomCommandMod, "kOneCmd", plRandomCommandMod::kOneCmd);
    PY_TYPE_ADD_CONST(RandomCommandMod, "kDelayFromEnd", plRandomCommandMod::kDelayFromEnd);
    PY_TYPE_ADD_CONST(RandomCommandMod, "kSequential", plRandomCommandMod::kSequential);
    PY_TYPE_ADD_CONST(RandomCommandMod, "kStopped", plRandomCommandMod::kStopped);

    Py_INCREF(&pyRandomCommandMod_Type);
    return (PyObject*)&pyRandomCommandMod_Type;
}

PY_PLASMA_IFC_METHODS(RandomCommandMod, plRandomCommandMod)
