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

#include "pyATCEaseCurves.h"

#include <PRP/Animation/plATCEaseCurves.h>
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW(ATCEaseCurve, plATCEaseCurve)

PY_PROPERTY(float, ATCEaseCurve, startSpeed, getStartSpeed, setStartSpeed)
PY_PROPERTY(float, ATCEaseCurve, speed, getSpeed, setSpeed)
PY_PROPERTY(float, ATCEaseCurve, minLength, getMinLength, setMinLength)
PY_PROPERTY(float, ATCEaseCurve, maxLength, getMaxLength, setMaxLength)
PY_PROPERTY(float, ATCEaseCurve, length, getLength, setLength)
PY_PROPERTY(double, ATCEaseCurve, beginWorldTime, getBeginWorldTime, setBeginWorldTime)

static PyGetSetDef pyATCEaseCurve_GetSet[] = {
    pyATCEaseCurve_startSpeed_getset,
    pyATCEaseCurve_speed_getset,
    pyATCEaseCurve_minLength_getset,
    pyATCEaseCurve_maxLength_getset,
    pyATCEaseCurve_length_getset,
    pyATCEaseCurve_beginWorldTime_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ATCEaseCurve, plATCEaseCurve, "plATCEaseCurve wrapper")

PY_PLASMA_TYPE_INIT(ATCEaseCurve)
{
    pyATCEaseCurve_Type.tp_new = pyATCEaseCurve_new;
    pyATCEaseCurve_Type.tp_getset = pyATCEaseCurve_GetSet;
    pyATCEaseCurve_Type.tp_base = &pyCreatable_Type;
    if (PyType_CheckAndReady(&pyATCEaseCurve_Type) < 0)
        return nullptr;

    Py_INCREF(&pyATCEaseCurve_Type);
    return (PyObject*)&pyATCEaseCurve_Type;
}

PY_PLASMA_IFC_METHODS(ATCEaseCurve, plATCEaseCurve)
