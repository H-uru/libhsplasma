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

#include "pyEventData.h"

#include <PRP/Message/proEventData.h>
#include "PRP/KeyedObject/pyKey.h"

PY_PLASMA_NEW(MultiStageEventData, proMultiStageEventData)

PY_PROPERTY(int, MultiStageEventData, stage, getStage, setStage)
PY_PROPERTY(int, MultiStageEventData, event, getEvent, setEvent)
PY_PROPERTY(plKey, MultiStageEventData, avatar, getAvatar, setAvatar)

static PyGetSetDef pyMultiStageEventData_GetSet[] = {
    pyMultiStageEventData_stage_getset,
    pyMultiStageEventData_event_getset,
    pyMultiStageEventData_avatar_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(MultiStageEventData, proMultiStageEventData,
               "proMultiStageEventData wrapper")

PY_PLASMA_TYPE_INIT(MultiStageEventData)
{
    pyMultiStageEventData_Type.tp_new = pyMultiStageEventData_new;
    pyMultiStageEventData_Type.tp_getset = pyMultiStageEventData_GetSet;
    pyMultiStageEventData_Type.tp_base = &pyEventData_Type;
    if (PyType_CheckAndReady(&pyMultiStageEventData_Type) < 0)
        return nullptr;

    Py_INCREF(&pyMultiStageEventData_Type);
    return (PyObject*)&pyMultiStageEventData_Type;
}

PY_PLASMA_IFC_METHODS(MultiStageEventData, proMultiStageEventData)
