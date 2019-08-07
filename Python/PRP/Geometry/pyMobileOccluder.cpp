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

#include "pyOccluder.h"

#include <PRP/Geometry/plOccluder.h>
#include "PRP/Region/pyBounds.h"
#include "PRP/pyCreatable.h"
#include "Math/pyMatrix.h"

PY_PLASMA_NEW(MobileOccluder, plMobileOccluder)

PY_PROPERTY(hsMatrix44, MobileOccluder, localToWorld, getLocalToWorld, setLocalToWorld)
PY_PROPERTY(hsMatrix44, MobileOccluder, worldToLocal, getWorldToLocal, setWorldToLocal)
PY_PROPERTY_BOUNDS(Bounds3Ext, MobileOccluder, localBounds, getLocalBounds, setLocalBounds)

static PyGetSetDef pyMobileOccluder_GetSet[] = {
    pyMobileOccluder_localToWorld_getset,
    pyMobileOccluder_worldToLocal_getset,
    pyMobileOccluder_localBounds_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(MobileOccluder, plMobileOccluder, "plMobileOccluder wrapper")

PY_PLASMA_TYPE_INIT(MobileOccluder)
{
    pyMobileOccluder_Type.tp_new = pyMobileOccluder_new;
    pyMobileOccluder_Type.tp_getset = pyMobileOccluder_GetSet;
    pyMobileOccluder_Type.tp_base = &pyOccluder_Type;
    if (PyType_CheckAndReady(&pyMobileOccluder_Type) < 0)
        return nullptr;

    Py_INCREF(&pyMobileOccluder_Type);
    return (PyObject*)&pyMobileOccluder_Type;
}

PY_PLASMA_IFC_METHODS(MobileOccluder, plMobileOccluder)
