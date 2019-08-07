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

#include "pyParticleEffect.h"

#include <PRP/Particle/plParticleEffect.h>
#include "Math/pyGeometry3.h"

/* pyParticleWindEffect */
PY_PLASMA_NEW(ParticleWindEffect, plParticleWindEffect)

PY_PROPERTY(float, ParticleWindEffect, strength, getStrength, setStrength)
PY_PROPERTY(float, ParticleWindEffect, constancy, getConstancy, setConstancy)
PY_PROPERTY(float, ParticleWindEffect, swirl, getSwirl, setSwirl)
PY_PROPERTY(bool, ParticleWindEffect, horizontal, isHorizontal, setHorizontal)
PY_PROPERTY(hsVector3, ParticleWindEffect, refDir, getRefDir, setRefDir)
PY_PROPERTY(hsVector3, ParticleWindEffect, dir, getDir, setDir)

static PyGetSetDef pyParticleWindEffect_GetSet[] = {
    pyParticleWindEffect_strength_getset,
    pyParticleWindEffect_constancy_getset,
    pyParticleWindEffect_swirl_getset,
    pyParticleWindEffect_horizontal_getset,
    pyParticleWindEffect_refDir_getset,
    pyParticleWindEffect_dir_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ParticleWindEffect, plParticleWindEffect, "plParticleWindEffect wrapper")

PY_PLASMA_TYPE_INIT(ParticleWindEffect)
{
    pyParticleWindEffect_Type.tp_new = pyParticleWindEffect_new;
    pyParticleWindEffect_Type.tp_getset = pyParticleWindEffect_GetSet;
    pyParticleWindEffect_Type.tp_base = &pyParticleEffect_Type;
    if (PyType_CheckAndReady(&pyParticleWindEffect_Type) < 0)
        return nullptr;

    Py_INCREF(&pyParticleWindEffect_Type);
    return (PyObject*)&pyParticleWindEffect_Type;
}

PY_PLASMA_IFC_METHODS(ParticleWindEffect, plParticleWindEffect)


/* pyParticleLocalWind */
PY_PLASMA_NEW(ParticleLocalWind, plParticleLocalWind)

PY_PROPERTY(hsVector3, ParticleLocalWind, scale, getScale, setScale)
PY_PROPERTY(float, ParticleLocalWind, speed, getSpeed, setSpeed)

static PyGetSetDef pyParticleLocalWind_GetSet[] = {
    pyParticleLocalWind_scale_getset,
    pyParticleLocalWind_speed_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ParticleLocalWind, plParticleLocalWind, "plParticleLocalWind wrapper")

PY_PLASMA_TYPE_INIT(ParticleLocalWind)
{
    pyParticleLocalWind_Type.tp_new = pyParticleLocalWind_new;
    pyParticleLocalWind_Type.tp_getset = pyParticleLocalWind_GetSet;
    pyParticleLocalWind_Type.tp_base = &pyParticleWindEffect_Type;
    if (PyType_CheckAndReady(&pyParticleLocalWind_Type) < 0)
        return nullptr;

    Py_INCREF(&pyParticleLocalWind_Type);
    return (PyObject*)&pyParticleLocalWind_Type;
}

PY_PLASMA_IFC_METHODS(ParticleLocalWind, plParticleLocalWind)


/* pyParticleUniformWind */
PY_PLASMA_NEW(ParticleUniformWind, plParticleUniformWind)

PY_PROPERTY(float, ParticleUniformWind, freqMin, getFreqMin, setFreqMin)
PY_PROPERTY(float, ParticleUniformWind, freqMax, getFreqMax, setFreqMax)
PY_PROPERTY(float, ParticleUniformWind, freqRate, getFreqRate, setFreqRate)

static PyGetSetDef pyParticleUniformWind_GetSet[] = {
    pyParticleUniformWind_freqMin_getset,
    pyParticleUniformWind_freqMax_getset,
    pyParticleUniformWind_freqRate_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ParticleUniformWind, plParticleUniformWind,
               "plParticleUniformWind wrapper")

PY_PLASMA_TYPE_INIT(ParticleUniformWind)
{
    pyParticleUniformWind_Type.tp_new = pyParticleUniformWind_new;
    pyParticleUniformWind_Type.tp_getset = pyParticleUniformWind_GetSet;
    pyParticleUniformWind_Type.tp_base = &pyParticleWindEffect_Type;
    if (PyType_CheckAndReady(&pyParticleUniformWind_Type) < 0)
        return nullptr;

    Py_INCREF(&pyParticleUniformWind_Type);
    return (PyObject*)&pyParticleUniformWind_Type;
}

PY_PLASMA_IFC_METHODS(ParticleUniformWind, plParticleUniformWind)
