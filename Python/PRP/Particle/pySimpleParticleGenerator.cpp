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

#include "pyParticleGenerator.h"

#include <PRP/Particle/plParticleGenerator.h>
#include "Math/pyGeometry3.h"

PY_PLASMA_NEW(SimpleParticleGenerator, plSimpleParticleGenerator)

PY_PROPERTY(float, SimpleParticleGenerator, particlesPerSecond,
            getParticlesPerSecond, setParticlesPerSecond)
PY_PROPERTY_VECTOR(hsVector3, SimpleParticleGenerator, initPos, getInitPos, setInitPos)
PY_PROPERTY_VECTOR(float, SimpleParticleGenerator, initPitch, getInitPitch, setInitPitch)
PY_PROPERTY_VECTOR(float, SimpleParticleGenerator, initYaw, getInitYaw, setInitYaw)
PY_PROPERTY(float, SimpleParticleGenerator, angleRange, getAngleRange, setAngleRange)
PY_PROPERTY(float, SimpleParticleGenerator, velMin, getVelMin, setVelMin)
PY_PROPERTY(float, SimpleParticleGenerator, velMax, getVelMax, setVelMax)
PY_PROPERTY(float, SimpleParticleGenerator, XSize, getXSize, setXSize)
PY_PROPERTY(float, SimpleParticleGenerator, YSize, getYSize, setYSize)
PY_PROPERTY(float, SimpleParticleGenerator, scaleMin, getScaleMin, setScaleMin)
PY_PROPERTY(float, SimpleParticleGenerator, scaleMax, getScaleMax, setScaleMax)
PY_PROPERTY(float, SimpleParticleGenerator, genLife, getGenLife, setGenLife)
PY_PROPERTY(float, SimpleParticleGenerator, partLifeMin, getPartLifeMin, setPartLifeMin)
PY_PROPERTY(float, SimpleParticleGenerator, partLifeMax, getPartLifeMax, setPartLifeMax)
PY_PROPERTY(float, SimpleParticleGenerator, partMassRange, getPartMassRange, setPartMassRange)
PY_PROPERTY(float, SimpleParticleGenerator, partRadsPerSecRange, getPartRadsPerSecRange,
            setPartRadsPerSecRange)

static PyGetSetDef pySimpleParticleGenerator_GetSet[] = {
    pySimpleParticleGenerator_particlesPerSecond_getset,
    pySimpleParticleGenerator_initPos_getset,
    pySimpleParticleGenerator_initPitch_getset,
    pySimpleParticleGenerator_initYaw_getset,
    pySimpleParticleGenerator_angleRange_getset,
    pySimpleParticleGenerator_velMin_getset,
    pySimpleParticleGenerator_velMax_getset,
    pySimpleParticleGenerator_XSize_getset,
    pySimpleParticleGenerator_YSize_getset,
    pySimpleParticleGenerator_scaleMin_getset,
    pySimpleParticleGenerator_scaleMax_getset,
    pySimpleParticleGenerator_genLife_getset,
    pySimpleParticleGenerator_partLifeMin_getset,
    pySimpleParticleGenerator_partLifeMax_getset,
    pySimpleParticleGenerator_partMassRange_getset,
    pySimpleParticleGenerator_partRadsPerSecRange_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(SimpleParticleGenerator, plSimpleParticleGenerator,
               "plSimpleParticleGenerator wrapper")

PY_PLASMA_TYPE_INIT(SimpleParticleGenerator)
{
    pySimpleParticleGenerator_Type.tp_new = pySimpleParticleGenerator_new;
    pySimpleParticleGenerator_Type.tp_getset = pySimpleParticleGenerator_GetSet;
    pySimpleParticleGenerator_Type.tp_base = &pyParticleGenerator_Type;
    if (PyType_CheckAndReady(&pySimpleParticleGenerator_Type) < 0)
        return nullptr;

    Py_INCREF(&pySimpleParticleGenerator_Type);
    return (PyObject*)&pySimpleParticleGenerator_Type;
}

PY_PLASMA_IFC_METHODS(SimpleParticleGenerator, plSimpleParticleGenerator)
