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

#include "pyBoundInterface.h"

#include <PRP/Particle/plBoundInterface.h>
#include "PRP/Object/pyObjInterface.h"
#include "PRP/Region/pyConvexVolume.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW(BoundInterface, plBoundInterface)

PY_PROPERTY_CREATABLE(plConvexVolume, ConvexVolume, BoundInterface, bounds,
                      getBounds, setBounds)

static PyGetSetDef pyBoundInterface_GetSet[] = {
    pyBoundInterface_bounds_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(BoundInterface, plBoundInterface, "plBoundInterface wrapper")

PY_PLASMA_TYPE_INIT(BoundInterface)
{
    pyBoundInterface_Type.tp_new = pyBoundInterface_new;
    pyBoundInterface_Type.tp_getset = pyBoundInterface_GetSet;
    pyBoundInterface_Type.tp_base = &pyObjInterface_Type;
    if (PyType_CheckAndReady(&pyBoundInterface_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(BoundInterface, "kDisable", plBoundInterface::kDisable);
    PY_TYPE_ADD_CONST(BoundInterface, "kNumProps", plBoundInterface::kNumProps);

    Py_INCREF(&pyBoundInterface_Type);
    return (PyObject*)&pyBoundInterface_Type;
}

PY_PLASMA_IFC_METHODS(BoundInterface, plBoundInterface)
