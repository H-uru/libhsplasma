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
#include "PRP/KeyedObject/pyKey.h"

/* pyParticleCollisionEffect */
PY_PLASMA_NEW(ParticleCollisionEffect, plParticleCollisionEffect)

PY_PROPERTY(plKey, ParticleCollisionEffect, sceneObj, getSceneObj, setSceneObj)

static PyGetSetDef pyParticleCollisionEffect_GetSet[] = {
    pyParticleCollisionEffect_sceneObj_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ParticleCollisionEffect, plParticleCollisionEffect,
               "plParticleCollisionEffect wrapper")

PY_PLASMA_TYPE_INIT(ParticleCollisionEffect)
{
    pyParticleCollisionEffect_Type.tp_new = pyParticleCollisionEffect_new;
    pyParticleCollisionEffect_Type.tp_getset = pyParticleCollisionEffect_GetSet;
    pyParticleCollisionEffect_Type.tp_base = &pyParticleEffect_Type;
    if (PyType_CheckAndReady(&pyParticleCollisionEffect_Type) < 0)
        return nullptr;

    Py_INCREF(&pyParticleCollisionEffect_Type);
    return (PyObject*)&pyParticleCollisionEffect_Type;
}

PY_PLASMA_IFC_METHODS(ParticleCollisionEffect, plParticleCollisionEffect)


/* pyParticleCollisionEffectBeat */
PY_PLASMA_NEW(ParticleCollisionEffectBeat, plParticleCollisionEffectBeat)
PY_PLASMA_TYPE(ParticleCollisionEffectBeat, plParticleCollisionEffectBeat,
               "plParticleCollisionEffectBeat wrapper")

PY_PLASMA_TYPE_INIT(ParticleCollisionEffectBeat)
{
    pyParticleCollisionEffectBeat_Type.tp_new = pyParticleCollisionEffectBeat_new;
    pyParticleCollisionEffectBeat_Type.tp_base = &pyParticleCollisionEffect_Type;
    if (PyType_CheckAndReady(&pyParticleCollisionEffectBeat_Type) < 0)
        return nullptr;

    Py_INCREF(&pyParticleCollisionEffectBeat_Type);
    return (PyObject*)&pyParticleCollisionEffectBeat_Type;
}

PY_PLASMA_IFC_METHODS(ParticleCollisionEffectBeat, plParticleCollisionEffectBeat)


/* pyParticleCollisionEffectBounce */
PY_PLASMA_NEW(ParticleCollisionEffectBounce, plParticleCollisionEffectBounce)

PY_PROPERTY(float, ParticleCollisionEffectBounce, bounce, getBounce, setBounce)
PY_PROPERTY(float, ParticleCollisionEffectBounce, friction, getFriction, setFriction)

static PyGetSetDef pyParticleCollisionEffectBounce_GetSet[] = {
    pyParticleCollisionEffectBounce_bounce_getset,
    pyParticleCollisionEffectBounce_friction_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ParticleCollisionEffectBounce, plParticleCollisionEffectBounce,
               "plParticleCollisionEffectBounce wrapper")

PY_PLASMA_TYPE_INIT(ParticleCollisionEffectBounce)
{
    pyParticleCollisionEffectBounce_Type.tp_new = pyParticleCollisionEffectBounce_new;
    pyParticleCollisionEffectBounce_Type.tp_getset = pyParticleCollisionEffectBounce_GetSet;
    pyParticleCollisionEffectBounce_Type.tp_base = &pyParticleCollisionEffect_Type;
    if (PyType_CheckAndReady(&pyParticleCollisionEffectBounce_Type) < 0)
        return nullptr;

    Py_INCREF(&pyParticleCollisionEffectBounce_Type);
    return (PyObject*)&pyParticleCollisionEffectBounce_Type;
}

PY_PLASMA_IFC_METHODS(ParticleCollisionEffectBounce, plParticleCollisionEffectBounce)


/* pyParticleCollisionEffectDie */
PY_PLASMA_NEW(ParticleCollisionEffectDie, plParticleCollisionEffectDie)
PY_PLASMA_TYPE(ParticleCollisionEffectDie, plParticleCollisionEffectDie,
               "plParticleCollisionEffectDie wrapper")

PY_PLASMA_TYPE_INIT(ParticleCollisionEffectDie)
{
    pyParticleCollisionEffectDie_Type.tp_new = pyParticleCollisionEffectDie_new;
    pyParticleCollisionEffectDie_Type.tp_base = &pyParticleCollisionEffect_Type;
    if (PyType_CheckAndReady(&pyParticleCollisionEffectDie_Type) < 0)
        return nullptr;

    Py_INCREF(&pyParticleCollisionEffectDie_Type);
    return (PyObject*)&pyParticleCollisionEffectDie_Type;
}

PY_PLASMA_IFC_METHODS(ParticleCollisionEffectDie, plParticleCollisionEffectDie)
