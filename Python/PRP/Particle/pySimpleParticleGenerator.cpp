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

PY_GETSET_GETTER_DECL(SimpleParticleGenerator, initPos)
{
    const auto& pos = self->fThis->getInitPos();
    PyObject* result = PyTuple_New(pos.size());
    for (size_t i = 0; i < pos.size(); ++i)
        PyTuple_SET_ITEM(result, i, pyVector3_FromVector3(pos[i]));
    return result;
}

PY_GETSET_SETTER_DECL(SimpleParticleGenerator, initPos)
{
    PY_PROPERTY_CHECK_NULL(initPos);
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "initPos should be a sequence of hsVector3 objects");
        return -1;
    }
    std::vector<hsVector3> pos(seq.size());
    for (size_t i = 0; i < pos.size(); ++i) {
        PyObject* vec = seq.get(i);
        if (!pyVector3_Check(vec)) {
            PyErr_SetString(PyExc_TypeError, "initPos should be a sequence of hsVector3 objects");
            return -1;
        }
        pos[i] = *((pyVector3*)vec)->fThis;
    }
    self->fThis->setInitPos(pos);
    return 0;
}

PY_PROPERTY_GETSET_DECL(SimpleParticleGenerator, initPos)


PY_GETSET_GETTER_DECL(SimpleParticleGenerator, initPitch)
{
    const auto& pitch = self->fThis->getInitPitch();
    PyObject* result = PyTuple_New(pitch.size());
    for (size_t i = 0; i < pitch.size(); ++i)
        PyTuple_SET_ITEM(result, i, pyPlasma_convert(pitch[i]));
    return result;
}

PY_GETSET_SETTER_DECL(SimpleParticleGenerator, initPitch)
{
    PY_PROPERTY_CHECK_NULL(initPitch);
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "initPitch should be a sequence of floats");
        return -1;
    }
    std::vector<float> pitch(seq.size());
    for (size_t i = 0; i < pitch.size(); ++i) {
        PyObject* value = seq.get(i);
        if (!pyPlasma_check<float>(value)) {
            PyErr_SetString(PyExc_TypeError, "initPitch should be a sequence of floats");
            return -1;
        }
        pitch[i] = pyPlasma_get<float>(value);
    }
    self->fThis->setInitPitch(pitch);
    return 0;
}

PY_PROPERTY_GETSET_DECL(SimpleParticleGenerator, initPitch)


PY_GETSET_GETTER_DECL(SimpleParticleGenerator, initYaw)
{
    const auto& yaw = self->fThis->getInitYaw();
    PyObject* result = PyTuple_New(yaw.size());
    for (size_t i = 0; i < yaw.size(); ++i)
        PyTuple_SET_ITEM(result, i, pyPlasma_convert(yaw[i]));
    return result;
}

PY_GETSET_SETTER_DECL(SimpleParticleGenerator, initYaw)
{
    PY_PROPERTY_CHECK_NULL(initYaw);
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "initYaw should be a sequence of floats");
        return -1;
    }
    std::vector<float> yaw(seq.size());
    for (size_t i = 0; i < yaw.size(); ++i) {
        PyObject* value = seq.get(i);
        if (!pyPlasma_check<float>(value)) {
            PyErr_SetString(PyExc_TypeError, "initYaw should be a sequence of floats");
            return -1;
        }
        yaw[i] = pyPlasma_get<float>(value);
    }
    self->fThis->setInitYaw(yaw);
    return 0;
}

PY_PROPERTY_GETSET_DECL(SimpleParticleGenerator, initYaw)


PY_PROPERTY(float, SimpleParticleGenerator, particlesPerSecond,
            getParticlesPerSecond, setParticlesPerSecond)
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
