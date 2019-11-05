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

PY_PLASMA_NEW(DynaTorpedoMgr, plDynaTorpedoMgr)
PY_PLASMA_TYPE(DynaTorpedoMgr, plDynaTorpedoMgr, "plDynaTorpedoMgr wrapper")

PY_PLASMA_TYPE_INIT(DynaTorpedoMgr)
{
    pyDynaTorpedoMgr_Type.tp_new = pyDynaTorpedoMgr_new;
    pyDynaTorpedoMgr_Type.tp_base = &pyDynaRippleMgr_Type;
    if (PyType_CheckAndReady(&pyDynaTorpedoMgr_Type) < 0)
        return nullptr;

    Py_INCREF(&pyDynaTorpedoMgr_Type);
    return (PyObject*)&pyDynaTorpedoMgr_Type;
}

PY_PLASMA_IFC_METHODS(DynaTorpedoMgr, plDynaTorpedoMgr)
