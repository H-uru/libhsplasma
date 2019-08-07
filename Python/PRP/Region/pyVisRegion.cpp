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

#include "pyVisRegion.h"

#include <PRP/Region/plVisRegion.h>
#include "PRP/Object/pyObjInterface.h"
#include "PRP/KeyedObject/pyKey.h"

PY_PLASMA_NEW(VisRegion, plVisRegion)

PY_PROPERTY(plKey, VisRegion, region, getRegion, setRegion)
PY_PROPERTY(plKey, VisRegion, visMgr, getVisMgr, setVisMgr)

PyGetSetDef pyVisRegion_GetSet[] = {
    pyVisRegion_region_getset,
    pyVisRegion_visMgr_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(VisRegion, plVisRegion, "plVisRegion wrapper")

PY_PLASMA_TYPE_INIT(VisRegion)
{
    pyVisRegion_Type.tp_new = pyVisRegion_new;
    pyVisRegion_Type.tp_getset = pyVisRegion_GetSet;
    pyVisRegion_Type.tp_base = &pyObjInterface_Type;
    if (PyType_CheckAndReady(&pyVisRegion_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(VisRegion, "kDisable", plVisRegion::kDisable);
    PY_TYPE_ADD_CONST(VisRegion, "kIsNot", plVisRegion::kIsNot);
    PY_TYPE_ADD_CONST(VisRegion, "kReplaceNormal", plVisRegion::kReplaceNormal);
    PY_TYPE_ADD_CONST(VisRegion, "kDisableNormal", plVisRegion::kDisableNormal);

    Py_INCREF(&pyVisRegion_Type);
    return (PyObject*)&pyVisRegion_Type;
}

PY_PLASMA_IFC_METHODS(VisRegion, plVisRegion)
