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

#include "pyDynaRippleMgr.h"

#include <PRP/Surface/plDynaRippleMgr.h>
#include "PRP/KeyedObject/pyKey.h"

PY_PLASMA_NEW(DynaRippleVSMgr, plDynaRippleVSMgr)
PY_PLASMA_TYPE(DynaRippleVSMgr, plDynaRippleVSMgr, "plDynaRippleVSMgr wrapper")

PY_PROPERTY(plKey, DynaRippleVSMgr, waveSet, getWaveSet, setWaveSet)

static PyGetSetDef pyDynaRippleVSMgr_GetSet[] = {
    pyDynaRippleVSMgr_waveSet_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE_INIT(DynaRippleVSMgr)
{
    pyDynaRippleVSMgr_Type.tp_new = pyDynaRippleVSMgr_new;
    pyDynaRippleVSMgr_Type.tp_getset = pyDynaRippleVSMgr_GetSet;
    pyDynaRippleVSMgr_Type.tp_base = &pyDynaRippleMgr_Type;
    if (PyType_CheckAndReady(&pyDynaRippleVSMgr_Type) < 0)
        return nullptr;

    Py_INCREF(&pyDynaRippleVSMgr_Type);
    return (PyObject*)&pyDynaRippleVSMgr_Type;
}

PY_PLASMA_IFC_METHODS(DynaRippleVSMgr, plDynaRippleVSMgr)
