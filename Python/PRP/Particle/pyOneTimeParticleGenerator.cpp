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

PY_PLASMA_NEW(OneTimeParticleGenerator, plOneTimeParticleGenerator)

PY_GETSET_GETTER_DECL(OneTimeParticleGenerator, position)
{
    const auto& pos = self->fThis->getPosition();
    PyObject* result = PyTuple_New(pos.size());
    for (size_t i = 0; i < pos.size(); ++i)
        PyTuple_SET_ITEM(result, i, pyVector3_FromVector3(pos[i]));
    return result;
}

PY_GETSET_SETTER_DECL(OneTimeParticleGenerator, position)
{
    PY_PROPERTY_CHECK_NULL(position);
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "position should be a sequence of hsVector3 objects");
        return -1;
    }
    std::vector<hsVector3> pos(seq.size());
    for (size_t i = 0; i < pos.size(); ++i) {
        PyObject* vec = seq.get(i);
        if (!pyVector3_Check(vec)) {
            PyErr_SetString(PyExc_TypeError, "position should be a sequence of hsVector3 objects");
            return -1;
        }
        pos[i] = *((pyVector3*)vec)->fThis;
    }
    self->fThis->setPosition(pos);
    return 0;
}

PY_PROPERTY_GETSET_DECL(OneTimeParticleGenerator, position)


PY_GETSET_GETTER_DECL(OneTimeParticleGenerator, direction)
{
    const auto& dir = self->fThis->getDirection();
    PyObject* result = PyTuple_New(dir.size());
    for (size_t i = 0; i < dir.size(); ++i)
        PyTuple_SET_ITEM(result, i, pyVector3_FromVector3(dir[i]));
    return result;
}

PY_GETSET_SETTER_DECL(OneTimeParticleGenerator, direction)
{
    PY_PROPERTY_CHECK_NULL(direction);
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "direction should be a sequence of hsVector3 objects");
        return -1;
    }
    std::vector<hsVector3> dir(seq.size());
    for (size_t i = 0; i < dir.size(); ++i) {
        PyObject* vec = seq.get(i);
        if (!pyVector3_Check(vec)) {
            PyErr_SetString(PyExc_TypeError, "direction should be a sequence of hsVector3 objects");
            return -1;
        }
        dir[i] = *((pyVector3*)vec)->fThis;
    }
    self->fThis->setDirection(dir);
    return 0;
}

PY_PROPERTY_GETSET_DECL(OneTimeParticleGenerator, direction)


PY_PROPERTY(float, OneTimeParticleGenerator, XSize, getXSize, setXSize)
PY_PROPERTY(float, OneTimeParticleGenerator, YSize, getYSize, setYSize)
PY_PROPERTY(float, OneTimeParticleGenerator, scaleMin, getScaleMin, setScaleMin)
PY_PROPERTY(float, OneTimeParticleGenerator, scaleMax, getScaleMax, setScaleMax)
PY_PROPERTY(float, OneTimeParticleGenerator, partRadsPerSecRange,
            getPartRadsPerSecRange, setPartRadsPerSecRange)

static PyGetSetDef pyOneTimeParticleGenerator_GetSet[] = {
    pyOneTimeParticleGenerator_position_getset,
    pyOneTimeParticleGenerator_direction_getset,
    pyOneTimeParticleGenerator_XSize_getset,
    pyOneTimeParticleGenerator_YSize_getset,
    pyOneTimeParticleGenerator_scaleMin_getset,
    pyOneTimeParticleGenerator_scaleMax_getset,
    pyOneTimeParticleGenerator_partRadsPerSecRange_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(OneTimeParticleGenerator, plOneTimeParticleGenerator,
               "plOneTimeParticleGenerator wrapper")

PY_PLASMA_TYPE_INIT(OneTimeParticleGenerator)
{
    pyOneTimeParticleGenerator_Type.tp_new = pyOneTimeParticleGenerator_new;
    pyOneTimeParticleGenerator_Type.tp_getset = pyOneTimeParticleGenerator_GetSet;
    pyOneTimeParticleGenerator_Type.tp_base = &pyParticleGenerator_Type;
    if (PyType_CheckAndReady(&pyOneTimeParticleGenerator_Type) < 0)
        return nullptr;

    Py_INCREF(&pyOneTimeParticleGenerator_Type);
    return (PyObject*)&pyOneTimeParticleGenerator_Type;
}

PY_PLASMA_IFC_METHODS(OneTimeParticleGenerator, plOneTimeParticleGenerator)
