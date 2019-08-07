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

/* pyParticleFadeOutEffect */
PY_PLASMA_NEW(ParticleFadeOutEffect, plParticleFadeOutEffect)

PY_PROPERTY(float, ParticleFadeOutEffect, length, getLength, setLength)
PY_PROPERTY(float, ParticleFadeOutEffect, ignoreZ, getIgnoreZ, setIgnoreZ)

static PyGetSetDef pyParticleFadeOutEffect_GetSet[] = {
    pyParticleFadeOutEffect_length_getset,
    pyParticleFadeOutEffect_ignoreZ_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ParticleFadeOutEffect, plParticleFadeOutEffect,
               "plParticleFadeOutEffect wrapper")

PY_PLASMA_TYPE_INIT(ParticleFadeOutEffect)
{
    pyParticleFadeOutEffect_Type.tp_new = pyParticleFadeOutEffect_new;
    pyParticleFadeOutEffect_Type.tp_getset = pyParticleFadeOutEffect_GetSet;
    pyParticleFadeOutEffect_Type.tp_base = &pyParticleEffect_Type;
    if (PyType_CheckAndReady(&pyParticleFadeOutEffect_Type) < 0)
        return nullptr;

    Py_INCREF(&pyParticleFadeOutEffect_Type);
    return (PyObject*)&pyParticleFadeOutEffect_Type;
}

PY_PLASMA_IFC_METHODS(ParticleFadeOutEffect, plParticleFadeOutEffect)


/* pyParticleFadeVolumeEffect */
PY_PLASMA_NEW(ParticleFadeVolumeEffect, plParticleFadeVolumeEffect)

PY_PROPERTY(float, ParticleFadeVolumeEffect, length, getLength, setLength)
PY_PROPERTY(float, ParticleFadeVolumeEffect, ignoreZ, getIgnoreZ, setIgnoreZ)

static PyGetSetDef pyParticleFadeVolumeEffect_GetSet[] = {
    pyParticleFadeVolumeEffect_length_getset,
    pyParticleFadeVolumeEffect_ignoreZ_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ParticleFadeVolumeEffect, plParticleFadeVolumeEffect,
               "plParticleFadeVolumeEffect wrapper")

PY_PLASMA_TYPE_INIT(ParticleFadeVolumeEffect)
{
    pyParticleFadeVolumeEffect_Type.tp_new = pyParticleFadeVolumeEffect_new;
    pyParticleFadeVolumeEffect_Type.tp_getset = pyParticleFadeVolumeEffect_GetSet;
    pyParticleFadeVolumeEffect_Type.tp_base = &pyParticleEffect_Type;
    if (PyType_CheckAndReady(&pyParticleFadeVolumeEffect_Type) < 0)
        return nullptr;

    Py_INCREF(&pyParticleFadeVolumeEffect_Type);
    return (PyObject*)&pyParticleFadeVolumeEffect_Type;
}

PY_PLASMA_IFC_METHODS(ParticleFadeVolumeEffect, plParticleFadeVolumeEffect)
