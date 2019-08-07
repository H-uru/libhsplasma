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

#include "pyFilterCoordInterface.h"

#include "Math/pyMatrix.h"
#include <PRP/Animation/plFilterCoordInterface.h>
#include <PRP/Object/plCoordinateInterface.h>
#include "PRP/Object/pyObjInterface.h"

PY_PLASMA_NEW(FilterCoordInterface, plFilterCoordInterface)

PY_PROPERTY(unsigned int, FilterCoordInterface, filterMask, getFilterMask, setFilterMask)
PY_PROPERTY(hsMatrix44, FilterCoordInterface, refParentLocalToWorld,
            getRefParentLocalToWorld, setRefParentLocalToWorld)

static PyGetSetDef pyFilterCoordInterface_GetSet[] = {
    pyFilterCoordInterface_filterMask_getset,
    pyFilterCoordInterface_refParentLocalToWorld_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(FilterCoordInterface, plFilterCoordInterface, "plFilterCoordInterface wrapper")

PY_PLASMA_TYPE_INIT(FilterCoordInterface)
{
    pyFilterCoordInterface_Type.tp_new = pyFilterCoordInterface_new;
    pyFilterCoordInterface_Type.tp_getset = pyFilterCoordInterface_GetSet;
    pyFilterCoordInterface_Type.tp_base = &pyCoordinateInterface_Type;
    if (PyType_CheckAndReady(&pyFilterCoordInterface_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(FilterCoordInterface, "kNoRotation", plFilterCoordInterface::kNoRotation);
    PY_TYPE_ADD_CONST(FilterCoordInterface, "kNoTransX", plFilterCoordInterface::kNoTransX);
    PY_TYPE_ADD_CONST(FilterCoordInterface, "kNoTransY", plFilterCoordInterface::kNoTransY);
    PY_TYPE_ADD_CONST(FilterCoordInterface, "kNoTransZ", plFilterCoordInterface::kNoTransZ);
    PY_TYPE_ADD_CONST(FilterCoordInterface, "kNoMove", plFilterCoordInterface::kNoMove);
    PY_TYPE_ADD_CONST(FilterCoordInterface, "kNoNothing", plFilterCoordInterface::kNoNothing);

    Py_INCREF(&pyFilterCoordInterface_Type);
    return (PyObject*)&pyFilterCoordInterface_Type;
}

PY_PLASMA_IFC_METHODS(FilterCoordInterface, plFilterCoordInterface)
