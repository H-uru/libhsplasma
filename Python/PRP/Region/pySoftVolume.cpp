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

#include "pySoftVolume.h"

#include <PRP/Region/plSoftVolume.h>
#include "PRP/Object/pyObjInterface.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW_MSG(SoftVolume, "plSoftVolume is abstract")

PY_PROPERTY(unsigned int, SoftVolume, listenState, getListenState, setListenState)
PY_PROPERTY(float, SoftVolume, insideStrength, getInsideStrength, setInsideStrength)
PY_PROPERTY(float, SoftVolume, outsideStrength, getOutsideStrength, setOutsideStrength)

PyGetSetDef pySoftVolume_GetSet[] = {
    pySoftVolume_listenState_getset,
    pySoftVolume_insideStrength_getset,
    pySoftVolume_outsideStrength_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(SoftVolume, plSoftVolume, "plSoftVolume wrapper")

PY_PLASMA_TYPE_INIT(SoftVolume)
{
    pySoftVolume_Type.tp_new = pySoftVolume_new;
    pySoftVolume_Type.tp_getset = pySoftVolume_GetSet;
    pySoftVolume_Type.tp_base = &pyObjInterface_Type;
    if (PyType_CheckAndReady(&pySoftVolume_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(SoftVolume, "kListenNone", plSoftVolume::kListenNone);
    PY_TYPE_ADD_CONST(SoftVolume, "kListenCheck", plSoftVolume::kListenCheck);
    PY_TYPE_ADD_CONST(SoftVolume, "kListenPosSet", plSoftVolume::kListenPosSet);
    PY_TYPE_ADD_CONST(SoftVolume, "kListenDirty", plSoftVolume::kListenDirty);
    PY_TYPE_ADD_CONST(SoftVolume, "kListenRegistered", plSoftVolume::kListenRegistered);

    Py_INCREF(&pySoftVolume_Type);
    return (PyObject*)&pySoftVolume_Type;
}

PY_PLASMA_IFC_METHODS(SoftVolume, plSoftVolume)
