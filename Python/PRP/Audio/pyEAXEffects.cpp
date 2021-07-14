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

#include "pyEAXEffects.h"

#include <PRP/Audio/plEAXEffects.h>

PY_PLASMA_NEW(EAXSourceSettings, plEAXSourceSettings)

PY_PROPERTY(bool, EAXSourceSettings, enable, isEnabled, enable)
PY_PROPERTY(short, EAXSourceSettings, room, getRoom, setRoom)
PY_PROPERTY(short, EAXSourceSettings, roomHF, getRoomHF, setRoomHF)
PY_PROPERTY(bool, EAXSourceSettings, roomAuto, getRoomAuto, setRoomAuto)
PY_PROPERTY(bool, EAXSourceSettings, roomHFAuto, getRoomHFAuto, setRoomHFAuto)
PY_PROPERTY(short, EAXSourceSettings, outsideVolHF, getOutsideVolHF, setOutsideVolHF)
PY_PROPERTY(float, EAXSourceSettings, airAbsorptionFactor, getAirAbsorptionFactor, setAirAbsorptionFactor)
PY_PROPERTY(float, EAXSourceSettings, roomRolloffFactor, getRoomRolloffFactor, setRoomRolloffFactor)
PY_PROPERTY(float, EAXSourceSettings, dopplerFactor, getDopplerFactor, setDopplerFactor)
PY_PROPERTY(float, EAXSourceSettings, rolloffFactor, getRolloffFactor, setRolloffFactor)
PY_PROPERTY(float, EAXSourceSettings, occlusionSoftValue, getOcclusionSoftValue, setOcclusionSoftValue)
PY_PROPERTY_PROXY_RO(plEAXSourceSoftSettings, EAXSourceSettings, softStarts, getSoftStarts)
PY_PROPERTY_PROXY_RO(plEAXSourceSoftSettings, EAXSourceSettings, softEnds, getSoftEnds)

static PyGetSetDef pyEAXSourceSettings_GetSet[] = {
    pyEAXSourceSettings_enable_getset,
    pyEAXSourceSettings_room_getset,
    pyEAXSourceSettings_roomHF_getset,
    pyEAXSourceSettings_roomAuto_getset,
    pyEAXSourceSettings_roomHFAuto_getset,
    pyEAXSourceSettings_outsideVolHF_getset,
    pyEAXSourceSettings_airAbsorptionFactor_getset,
    pyEAXSourceSettings_roomRolloffFactor_getset,
    pyEAXSourceSettings_dopplerFactor_getset,
    pyEAXSourceSettings_rolloffFactor_getset,
    pyEAXSourceSettings_occlusionSoftValue_getset,
    pyEAXSourceSettings_softStarts_getset,
    pyEAXSourceSettings_softEnds_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(EAXSourceSettings, plEAXSourceSettings,
    "plEAXSourceSettings wrapper")

    PY_PLASMA_TYPE_INIT(EAXSourceSettings)
{
    pyEAXSourceSettings_Type.tp_new = pyEAXSourceSettings_new;
    pyEAXSourceSettings_Type.tp_getset = pyEAXSourceSettings_GetSet;
    if (PyType_CheckAndReady(&pyEAXSourceSettings_Type) < 0)
        return nullptr;

    Py_INCREF(&pyEAXSourceSettings_Type);
    return (PyObject*)&pyEAXSourceSettings_Type;
}

PY_PLASMA_IFC_METHODS(EAXSourceSettings, plEAXSourceSettings)

/* EAXSourceSoftSettings */

PY_PLASMA_NEW(EAXSourceSoftSettings, plEAXSourceSoftSettings)

PY_METHOD_NOARGS(EAXSourceSoftSettings, reset,
    "Resets to recommended settings")
{
    self->fThis->reset();
    Py_RETURN_NONE;
}

static PyMethodDef pyEAXSourceSoftSettings_Methods[] = {
    pyEAXSourceSoftSettings_reset_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY(float, EAXSourceSoftSettings, occlusion, getOcclusion, setOcclusion)
PY_PROPERTY(float, EAXSourceSoftSettings, lfRatio, getLFRatio, setLFRatio)
PY_PROPERTY(float, EAXSourceSoftSettings, roomRatio, getRoomRatio, setRoomRatio)
PY_PROPERTY(float, EAXSourceSoftSettings, directRatio, getDirectRatio, setDirectRatio)

static PyGetSetDef pyEAXSourceSoftSettings_GetSet[] = {
    pyEAXSourceSoftSettings_occlusion_getset,
    pyEAXSourceSoftSettings_lfRatio_getset,
    pyEAXSourceSoftSettings_roomRatio_getset,
    pyEAXSourceSoftSettings_directRatio_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(EAXSourceSoftSettings, plEAXSourceSoftSettings,
    "plEAXSourceSoftSettings wrapper")

    PY_PLASMA_TYPE_INIT(EAXSourceSoftSettings)
{
    pyEAXSourceSoftSettings_Type.tp_new = pyEAXSourceSoftSettings_new;
    pyEAXSourceSoftSettings_Type.tp_methods = pyEAXSourceSoftSettings_Methods;
    pyEAXSourceSoftSettings_Type.tp_getset = pyEAXSourceSoftSettings_GetSet;
    if (PyType_CheckAndReady(&pyEAXSourceSoftSettings_Type) < 0)
        return nullptr;

    Py_INCREF(&pyEAXSourceSoftSettings_Type);
    return (PyObject*)&pyEAXSourceSoftSettings_Type;
}

PY_PLASMA_IFC_METHODS(EAXSourceSoftSettings, plEAXSourceSoftSettings)
