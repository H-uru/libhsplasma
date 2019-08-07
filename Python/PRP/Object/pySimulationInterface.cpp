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

#include "pyObjInterface.h"

#include <PRP/Object/plSimulationInterface.h>
#include "PRP/pyCreatable.h"
#include "PRP/KeyedObject/pyKey.h"

PY_PLASMA_NEW(SimulationInterface, plSimulationInterface)

PY_PROPERTY(plKey, SimulationInterface, physical, getPhysical, setPhysical)

PyGetSetDef pySimulationInterface_GetSet[] = {
    pySimulationInterface_physical_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(SimulationInterface, plSimulationInterface,
               "plSimulationInterface wrapper")

PY_PLASMA_TYPE_INIT(SimulationInterface)
{
    pySimulationInterface_Type.tp_new = pySimulationInterface_new;
    pySimulationInterface_Type.tp_getset = pySimulationInterface_GetSet;
    pySimulationInterface_Type.tp_base = &pyObjInterface_Type;
    if (PyType_CheckAndReady(&pySimulationInterface_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(SimulationInterface, "kWeightless",
                      plSimulationInterface::kWeightless);
    PY_TYPE_ADD_CONST(SimulationInterface, "kPinned",
                      plSimulationInterface::kPinned);
    PY_TYPE_ADD_CONST(SimulationInterface, "kWarp",
                      plSimulationInterface::kWarp);
    PY_TYPE_ADD_CONST(SimulationInterface, "kUpright",
                      plSimulationInterface::kUpright);
    PY_TYPE_ADD_CONST(SimulationInterface, "kPassive",
                      plSimulationInterface::kPassive);
    PY_TYPE_ADD_CONST(SimulationInterface, "kRotationForces",
                      plSimulationInterface::kRotationForces);
    PY_TYPE_ADD_CONST(SimulationInterface, "kCameraAvoidObject",
                      plSimulationInterface::kCameraAvoidObject);
    PY_TYPE_ADD_CONST(SimulationInterface, "kPhysAnim",
                      plSimulationInterface::kPhysAnim);
    PY_TYPE_ADD_CONST(SimulationInterface, "kStartInactive",
                      plSimulationInterface::kStartInactive);
    PY_TYPE_ADD_CONST(SimulationInterface, "kNoSynchronize",
                      plSimulationInterface::kNoSynchronize);
    PY_TYPE_ADD_CONST(SimulationInterface, "kSuppressed",
                      plSimulationInterface::kSuppressed);
    PY_TYPE_ADD_CONST(SimulationInterface, "kNoOwnershipChange",
                      plSimulationInterface::kNoOwnershipChange);
    PY_TYPE_ADD_CONST(SimulationInterface, "kAvAnimPushable",
                      plSimulationInterface::kAvAnimPushable);

    Py_INCREF(&pySimulationInterface_Type);
    return (PyObject*)&pySimulationInterface_Type;
}

PY_PLASMA_IFC_METHODS(SimulationInterface, plSimulationInterface)
