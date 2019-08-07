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

PY_PLASMA_NEW(FacingEventData, proFacingEventData)

PY_PROPERTY(plKey, FacingEventData, facer, getFacer, setFacer)
PY_PROPERTY(plKey, FacingEventData, facee, getFacee, setFacee)
PY_PROPERTY(float, FacingEventData, dot, getDot, setDot)
PY_PROPERTY(bool, FacingEventData, enabled, isEnabled, setEnabled)

static PyGetSetDef pyFacingEventData_GetSet[] = {
    pyFacingEventData_facer_getset,
    pyFacingEventData_facee_getset,
    pyFacingEventData_dot_getset,
    pyFacingEventData_enabled_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(FacingEventData, proFacingEventData, "proFacingEventData wrapper")

PY_PLASMA_TYPE_INIT(FacingEventData)
{
    pyFacingEventData_Type.tp_new = pyFacingEventData_new;
    pyFacingEventData_Type.tp_getset = pyFacingEventData_GetSet;
    pyFacingEventData_Type.tp_base = &pyEventData_Type;
    if (PyType_CheckAndReady(&pyFacingEventData_Type) < 0)
        return nullptr;

    Py_INCREF(&pyFacingEventData_Type);
    return (PyObject*)&pyFacingEventData_Type;
}

PY_PLASMA_IFC_METHODS(FacingEventData, proFacingEventData)
