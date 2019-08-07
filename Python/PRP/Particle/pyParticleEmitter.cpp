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

#include "pyParticleEmitter.h"

#include <PRP/Particle/plParticleEmitter.h>
#include "pyParticleGenerator.h"
#include "PRP/pyCreatable.h"
#include "Sys/pyColor.h"

PY_PLASMA_NEW(ParticleEmitter, plParticleEmitter)

PY_PROPERTY(uint32_t, ParticleEmitter, miscFlags, getMiscFlags, setMiscFlags)
PY_PROPERTY(uint32_t, ParticleEmitter, spanIndex, getSpanIndex, setSpanIndex)
PY_PROPERTY(uint32_t, ParticleEmitter, maxParticles, getMaxParticles, setMaxParticles)
PY_PROPERTY_CREATABLE(plParticleGenerator, ParticleGenerator, ParticleEmitter,
                      generator, getGenerator, setGenerator)
PY_PROPERTY(hsColorRGBA, ParticleEmitter, color, getColor, setColor)

static PyGetSetDef pyParticleEmitter_GetSet[] = {
    pyParticleEmitter_miscFlags_getset,
    pyParticleEmitter_spanIndex_getset,
    pyParticleEmitter_maxParticles_getset,
    pyParticleEmitter_generator_getset,
    pyParticleEmitter_color_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ParticleEmitter, plParticleEmitter, "plParticleEmitter wrapper")

PY_PLASMA_TYPE_INIT(ParticleEmitter)
{
    pyParticleEmitter_Type.tp_new = pyParticleEmitter_new;
    pyParticleEmitter_Type.tp_getset = pyParticleEmitter_GetSet;
    pyParticleEmitter_Type.tp_base = &pyCreatable_Type;
    if (PyType_CheckAndReady(&pyParticleEmitter_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(ParticleEmitter, "kMatIsEmissive",
                      plParticleEmitter::kMatIsEmissive);
    PY_TYPE_ADD_CONST(ParticleEmitter, "kNormalUp",
                      plParticleEmitter::kNormalUp);
    PY_TYPE_ADD_CONST(ParticleEmitter, "kNormalVelUpVel",
                      plParticleEmitter::kNormalVelUpVel);
    PY_TYPE_ADD_CONST(ParticleEmitter, "kNormalFromCenter",
                      plParticleEmitter::kNormalFromCenter);
    PY_TYPE_ADD_CONST(ParticleEmitter, "kNormalDynamicMask",
                      plParticleEmitter::kNormalDynamicMask);
    PY_TYPE_ADD_CONST(ParticleEmitter, "kNormalPrecalcMask",
                      plParticleEmitter::kNormalPrecalcMask);
    PY_TYPE_ADD_CONST(ParticleEmitter, "kNormalViewFacing",
                      plParticleEmitter::kNormalViewFacing);
    PY_TYPE_ADD_CONST(ParticleEmitter, "kNormalNearestLight",
                      plParticleEmitter::kNormalNearestLight);
    PY_TYPE_ADD_CONST(ParticleEmitter, "kNeedsUpdate",
                      plParticleEmitter::kNeedsUpdate);
    PY_TYPE_ADD_CONST(ParticleEmitter, "kBorrowedGenerator",
                      plParticleEmitter::kBorrowedGenerator);
    PY_TYPE_ADD_CONST(ParticleEmitter, "kOverrideLocalToWorld",
                      plParticleEmitter::kOverrideLocalToWorld);
    PY_TYPE_ADD_CONST(ParticleEmitter, "kOnReserve",
                      plParticleEmitter::kOnReserve);
    PY_TYPE_ADD_CONST(ParticleEmitter, "kOrientationUp",
                      plParticleEmitter::kOrientationUp);
    PY_TYPE_ADD_CONST(ParticleEmitter, "kOrientationVelocityBased",
                      plParticleEmitter::kOrientationVelocityBased);
    PY_TYPE_ADD_CONST(ParticleEmitter, "kOrientationVelocityStretch",
                      plParticleEmitter::kOrientationVelocityStretch);
    PY_TYPE_ADD_CONST(ParticleEmitter, "kOrientationVelocityFlow",
                      plParticleEmitter::kOrientationVelocityFlow);
    PY_TYPE_ADD_CONST(ParticleEmitter, "kOrientationVelocityMask",
                      plParticleEmitter::kOrientationVelocityMask);
    PY_TYPE_ADD_CONST(ParticleEmitter, "kOrientationMask",
                      plParticleEmitter::kOrientationMask);

    Py_INCREF(&pyParticleEmitter_Type);
    return (PyObject*)&pyParticleEmitter_Type;
}

PY_PLASMA_IFC_METHODS(ParticleEmitter, plParticleEmitter)
