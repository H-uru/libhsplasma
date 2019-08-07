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

#include "pyVolumeSensorConditionalObject.h"

#include <PRP/ConditionalObject/plVolumeSensorConditionalObject.h>

PY_PLASMA_NEW(VolumeSensorConditionalObjectNoArbitration,
              plVolumeSensorConditionalObjectNoArbitration)

PY_PLASMA_TYPE(VolumeSensorConditionalObjectNoArbitration,
               plVolumeSensorConditionalObjectNoArbitration,
               "plVolumeSensorConditionalObjectNoArbitration wrapper")

PY_PLASMA_TYPE_INIT(VolumeSensorConditionalObjectNoArbitration)
{
    pyVolumeSensorConditionalObjectNoArbitration_Type.tp_new = pyVolumeSensorConditionalObjectNoArbitration_new;
    pyVolumeSensorConditionalObjectNoArbitration_Type.tp_base = &pyVolumeSensorConditionalObject_Type;
    if (PyType_CheckAndReady(&pyVolumeSensorConditionalObjectNoArbitration_Type) < 0)
        return nullptr;

    Py_INCREF(&pyVolumeSensorConditionalObjectNoArbitration_Type);
    return (PyObject*)&pyVolumeSensorConditionalObjectNoArbitration_Type;
}

PY_PLASMA_IFC_METHODS(VolumeSensorConditionalObjectNoArbitration,
                      plVolumeSensorConditionalObjectNoArbitration)
