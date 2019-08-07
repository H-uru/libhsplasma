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

#include "pySound.h"

PY_PLASMA_NEW_MSG(FadeParams, "Cannot construct plFadeParams objects in Python")

PY_PROPERTY_MEMBER(float, FadeParams, lengthInSecs, fLengthInSecs)
PY_PROPERTY_MEMBER(float, FadeParams, volStart, fVolStart)
PY_PROPERTY_MEMBER(float, FadeParams, volEnd, fVolEnd)
PY_PROPERTY_MEMBER(unsigned char, FadeParams, type, fType)
PY_PROPERTY_MEMBER(bool, FadeParams, stopWhenDone, fStopWhenDone)
PY_PROPERTY_MEMBER(bool, FadeParams, fadeSoftVol, fFadeSoftVol)
PY_PROPERTY_MEMBER(float, FadeParams, currTime, fCurrTime)

static PyGetSetDef pyFadeParams_GetSet[] = {
    pyFadeParams_lengthInSecs_getset,
    pyFadeParams_volStart_getset,
    pyFadeParams_volEnd_getset,
    pyFadeParams_type_getset,
    pyFadeParams_stopWhenDone_getset,
    pyFadeParams_fadeSoftVol_getset,
    pyFadeParams_currTime_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(FadeParams, plFadeParams, "plFadeParams wrapper")

PY_PLASMA_TYPE_INIT(FadeParams)
{
    pyFadeParams_Type.tp_new = pyFadeParams_new;
    pyFadeParams_Type.tp_getset = pyFadeParams_GetSet;
    if (PyType_CheckAndReady(&pyFadeParams_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(FadeParams, "kLinear", plSound::plFadeParams::kLinear);
    PY_TYPE_ADD_CONST(FadeParams, "kLogarithmic", plSound::plFadeParams::kLogarithmic);
    PY_TYPE_ADD_CONST(FadeParams, "kExponential", plSound::plFadeParams::kExponential);

    Py_INCREF(&pyFadeParams_Type);
    return (PyObject*)&pyFadeParams_Type;
}

PY_PLASMA_IFC_METHODS(FadeParams, plSound::plFadeParams)
