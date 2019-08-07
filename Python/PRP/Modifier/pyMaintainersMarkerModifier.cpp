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

#include "pyMaintainersMarkerModifier.h"

#include <PRP/Modifier/plMaintainersMarkerModifier.h>
#include "pyModifier.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW(MaintainersMarkerModifier, plMaintainersMarkerModifier)

PY_PROPERTY(unsigned int, MaintainersMarkerModifier, calibration,
            getCalibration, setCalibration)

static PyGetSetDef pyMaintainersMarkerModifier_GetSet[] = {
    pyMaintainersMarkerModifier_calibration_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(MaintainersMarkerModifier, plMaintainersMarkerModifier,
               "plMaintainersMarkerModifier wrapper")

PY_PLASMA_TYPE_INIT(MaintainersMarkerModifier)
{
    pyMaintainersMarkerModifier_Type.tp_new = pyMaintainersMarkerModifier_new;
    pyMaintainersMarkerModifier_Type.tp_getset = pyMaintainersMarkerModifier_GetSet;
    pyMaintainersMarkerModifier_Type.tp_base = &pyMultiModifier_Type;
    if (PyType_CheckAndReady(&pyMaintainersMarkerModifier_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(MaintainersMarkerModifier, "kBroken",
                      plMaintainersMarkerModifier::kBroken);
    PY_TYPE_ADD_CONST(MaintainersMarkerModifier, "kRepaired",
                      plMaintainersMarkerModifier::kRepaired);
    PY_TYPE_ADD_CONST(MaintainersMarkerModifier, "kCalibrated",
                      plMaintainersMarkerModifier::kCalibrated);

    Py_INCREF(&pyMaintainersMarkerModifier_Type);
    return (PyObject*)&pyMaintainersMarkerModifier_Type;
}

PY_PLASMA_IFC_METHODS(MaintainersMarkerModifier, plMaintainersMarkerModifier)
