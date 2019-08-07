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

#include "pyFixedWaterState7.h"

#include <PRP/Surface/plFixedWaterState7.h>

PY_PLASMA_EMPTY_INIT(WaveState7)
PY_PLASMA_NEW(WaveState7, plFixedWaterState7::WaveState)

PY_PROPERTY_MEMBER(float, WaveState7, maxLength, fMaxLength)
PY_PROPERTY_MEMBER(float, WaveState7, minLength, fMinLength)
PY_PROPERTY_MEMBER(float, WaveState7, ampOverLen, fAmpOverLen)
PY_PROPERTY_MEMBER(float, WaveState7, chop, fChop)
PY_PROPERTY_MEMBER(float, WaveState7, angleDev, fAngleDev)

static PyGetSetDef pyWaveState7_GetSet[] = {
    pyWaveState7_maxLength_getset,
    pyWaveState7_minLength_getset,
    pyWaveState7_ampOverLen_getset,
    pyWaveState7_chop_getset,
    pyWaveState7_angleDev_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(WaveState7, plFixedWaterState7.WaveState,
               "plFixedWaterState7::WaveState wrapper")

PY_PLASMA_TYPE_INIT(WaveState7)
{
    pyWaveState7_Type.tp_init = pyWaveState7___init__;
    pyWaveState7_Type.tp_new = pyWaveState7_new;
    pyWaveState7_Type.tp_getset = pyWaveState7_GetSet;
    if (PyType_CheckAndReady(&pyWaveState7_Type) < 0)
        return nullptr;

    Py_INCREF(&pyWaveState7_Type);
    return (PyObject*)&pyWaveState7_Type;
}

PY_PLASMA_IFC_METHODS(WaveState7, plFixedWaterState7::WaveState)
