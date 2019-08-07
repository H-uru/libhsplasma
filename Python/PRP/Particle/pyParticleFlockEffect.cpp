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

PY_PLASMA_NEW(ParticleFlockEffect, plParticleFlockEffect)

PY_PROPERTY(hsVector3, ParticleFlockEffect, targetOffset, getTargetOffset, setTargetOffset)
PY_PROPERTY(hsVector3, ParticleFlockEffect, dissenterTarget, getDissenterTarget, setDissenterTarget)
PY_PROPERTY(float, ParticleFlockEffect, infAvgRadSq, getInfAvgRadSq, setInfAvgRadSq)
PY_PROPERTY(float, ParticleFlockEffect, infRepRadSq, getInfRepRadSq, setInfRepRadSq)
PY_PROPERTY(float, ParticleFlockEffect, avgVelStr, getAvgVelStr, setAvgVelStr)
PY_PROPERTY(float, ParticleFlockEffect, repDirStr, getRepDirStr, setRepDirStr)
PY_PROPERTY(float, ParticleFlockEffect, goalOrbitStr, getGoalOrbitStr, setGoalOrbitStr)
PY_PROPERTY(float, ParticleFlockEffect, goalChaseStr, getGoalChaseStr, setGoalChaseStr)
PY_PROPERTY(float, ParticleFlockEffect, goalDistSq, getGoalDistSq, setGoalDistSq)
PY_PROPERTY(float, ParticleFlockEffect, fullChaseDistSq, getFullChaseDistSq, setFullChaseDistSq)
PY_PROPERTY(float, ParticleFlockEffect, maxOrbitSpeed, getMaxOrbitSpeed, setMaxOrbitSpeed)
PY_PROPERTY(float, ParticleFlockEffect, maxChaseSpeed, getMaxChaseSpeed, setMaxChaseSpeed)
PY_PROPERTY(float, ParticleFlockEffect, maxParticles, getMaxParticles, setMaxParticles)

static PyGetSetDef pyParticleFlockEffect_GetSet[] = {
    pyParticleFlockEffect_targetOffset_getset,
    pyParticleFlockEffect_dissenterTarget_getset,
    pyParticleFlockEffect_infAvgRadSq_getset,
    pyParticleFlockEffect_infRepRadSq_getset,
    pyParticleFlockEffect_avgVelStr_getset,
    pyParticleFlockEffect_repDirStr_getset,
    pyParticleFlockEffect_goalOrbitStr_getset,
    pyParticleFlockEffect_goalChaseStr_getset,
    pyParticleFlockEffect_goalDistSq_getset,
    pyParticleFlockEffect_fullChaseDistSq_getset,
    pyParticleFlockEffect_maxOrbitSpeed_getset,
    pyParticleFlockEffect_maxChaseSpeed_getset,
    pyParticleFlockEffect_maxParticles_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ParticleFlockEffect, plParticleFlockEffect,
               "plParticleFlockEffect wrapper")

PY_PLASMA_TYPE_INIT(ParticleFlockEffect)
{
    pyParticleFlockEffect_Type.tp_new = pyParticleFlockEffect_new;
    pyParticleFlockEffect_Type.tp_getset = pyParticleFlockEffect_GetSet;
    pyParticleFlockEffect_Type.tp_base = &pyParticleEffect_Type;
    if (PyType_CheckAndReady(&pyParticleFlockEffect_Type) < 0)
        return nullptr;

    Py_INCREF(&pyParticleFlockEffect_Type);
    return (PyObject*)&pyParticleFlockEffect_Type;
}

PY_PLASMA_IFC_METHODS(ParticleFlockEffect, plParticleFlockEffect)
