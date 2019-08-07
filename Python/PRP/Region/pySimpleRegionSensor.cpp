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

#include "pySimpleRegionSensor.h"

#include <PRP/Region/plSimpleRegionSensor.h>
#include "PRP/Message/pyMessage.h"
#include "PRP/Modifier/pyModifier.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW(SimpleRegionSensor, plSimpleRegionSensor)

PY_PROPERTY_CREATABLE(plMessage, Message, SimpleRegionSensor, enterMsg,
                      getEnterMsg, setEnterMsg)
PY_PROPERTY_CREATABLE(plMessage, Message, SimpleRegionSensor, exitMsg,
                      getExitMsg, setExitMsg)

PyGetSetDef pySimpleRegionSensor_GetSet[] = {
    pySimpleRegionSensor_enterMsg_getset,
    pySimpleRegionSensor_exitMsg_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(SimpleRegionSensor, plSimpleRegionSensor,
               "plSimpleRegionSensor wrapper")

PY_PLASMA_TYPE_INIT(SimpleRegionSensor)
{
    pySimpleRegionSensor_Type.tp_new = pySimpleRegionSensor_new;
    pySimpleRegionSensor_Type.tp_getset = pySimpleRegionSensor_GetSet;
    pySimpleRegionSensor_Type.tp_base = &pySingleModifier_Type;
    if (PyType_CheckAndReady(&pySimpleRegionSensor_Type) < 0)
        return nullptr;

    Py_INCREF(&pySimpleRegionSensor_Type);
    return (PyObject*)&pySimpleRegionSensor_Type;
}

PY_PLASMA_IFC_METHODS(SimpleRegionSensor, plSimpleRegionSensor);
