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

#include "pyParticleSystem.h"

#include <PRP/Particle/plParticleSystem.h>
#include "PRP/Modifier/pyModifier.h"
#include "PRP/Animation/pyController.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/pyCreatable.h"
#include "Math/pyGeometry3.h"
#include "pyParticleEmitter.h"

PY_PLASMA_NEW(ParticleSystem, plParticleSystem)

PY_METHOD_VA(ParticleSystem, allocEmitters,
    "Params: count\n"
    "Allocate space for `count` max emitters.")
{
    int count;
    if (!PyArg_ParseTuple(args, "i", &count)) {
        PyErr_SetString(PyExc_TypeError, "allocEmitters expects an int");
        return nullptr;
    }
    self->fThis->allocEmitters(count);
    Py_RETURN_NONE;
}

PY_METHOD_VA(ParticleSystem, getEmitter,
    "Params: index\n"
    "Returns the specified emitter attached to the Particle System")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "getEmitter expects an int");
        return nullptr;
    }
    return ICreate(self->fThis->getEmitter(idx));
}

PY_METHOD_VA(ParticleSystem, setEmitter,
    "Params: index, emitter\n"
    "Set the specified emitter.  Use allocEmitters to make space for new emitters.")
{
    int idx;
    PyObject* emitter;
    if (!PyArg_ParseTuple(args, "iO", &idx, &emitter)) {
        PyErr_SetString(PyExc_TypeError, "setEmitter expects int, plParticleEmitter");
        return nullptr;
    }
    if (!pyParticleEmitter_Check(emitter)) {
        PyErr_SetString(PyExc_TypeError, "setEmitter expects int, plParticleEmitter");
        return nullptr;
    }
    self->fThis->setEmitter(idx, ((pyParticleEmitter*)emitter)->fThis);
    ((pyParticleEmitter*)emitter)->fPyOwned = false;
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(ParticleSystem, clearEmitters,
    "Remove all emitters from the Particle System")
{
    self->fThis->clearEmitters();
    Py_RETURN_NONE;
}

PY_METHOD_VA(ParticleSystem, addEmitter,
    "Params: emitter\n"
    "Add an emitter to the Particle System")
{
    PyObject* emitter;
    if (!PyArg_ParseTuple(args, "O", &emitter)) {
        PyErr_SetString(PyExc_TypeError, "addEmitter expects a plParticleEmitter");
        return nullptr;
    }
    if (!pyParticleEmitter_Check(emitter)) {
        PyErr_SetString(PyExc_TypeError, "addEmitter expects a plParticleEmitter");
        return nullptr;
    }
    self->fThis->addEmitter(((pyParticleEmitter*)emitter)->fThis);
    ((pyParticleEmitter*)emitter)->fPyOwned = false;
    Py_RETURN_NONE;
}

PY_METHOD_VA(ParticleSystem, delEmitter,
    "Params: idx\n"
    "Remove an emitter from the Particle System")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delEmitter expects an int");
        return nullptr;
    }
    self->fThis->delEmitter(idx);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(ParticleSystem, clearForces,
    "Remove all force keys from the Particle System")
{
    self->fThis->clearForces();
    Py_RETURN_NONE;
}

PY_METHOD_VA(ParticleSystem, addForce,
    "Params: key\n"
    "Add a force key to the Particle System")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addForce expects a plKey");
        return nullptr;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addForce expects a plKey");
        return nullptr;
    }
    self->fThis->addForce(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(ParticleSystem, delForce,
    "Params: idx\n"
    "Remove a force key from the Particle System")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delForce expects an int");
        return nullptr;
    }
    self->fThis->delForce(idx);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(ParticleSystem, clearEffects,
    "Remove all effect keys from the Particle System")
{
    self->fThis->clearEffects();
    Py_RETURN_NONE;
}

PY_METHOD_VA(ParticleSystem, addEffect,
    "Params: key\n"
    "Add an effect key to the Particle System")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addEffect expects a plKey");
        return nullptr;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addEffect expects a plKey");
        return nullptr;
    }
    self->fThis->addEffect(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(ParticleSystem, delEffect,
    "Params: idx\n"
    "Remove an effect key from the Particle System")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delEffect expects an int");
        return nullptr;
    }
    self->fThis->delEffect(idx);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(ParticleSystem, clearConstraints,
    "Remove all constraint keys from the Particle System")
{
    self->fThis->clearConstraints();
    Py_RETURN_NONE;
}

PY_METHOD_VA(ParticleSystem, addConstraint,
    "Params: key\n"
    "Add a constraint key to the Particle System")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addConstraint expects a plKey");
        return nullptr;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addConstraint expects a plKey");
        return nullptr;
    }
    self->fThis->addConstraint(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(ParticleSystem, delConstraint,
    "Params: idx\n"
    "Remove a constraint key from the Particle System")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delConstraint expects an int");
        return nullptr;
    }
    self->fThis->delConstraint(idx);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(ParticleSystem, clearPermaLights,
    "Remove all permaLight keys from the Particle System")
{
    self->fThis->clearPermaLights();
    Py_RETURN_NONE;
}

PY_METHOD_VA(ParticleSystem, addPermaLight,
    "Params: key\n"
    "Add a permaLight key to the Particle System")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addPermaLight expects a plKey");
        return nullptr;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addPermaLight expects a plKey");
        return nullptr;
    }
    self->fThis->addPermaLight(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(ParticleSystem, delPermaLight,
    "Params: idx\n"
    "Remove a permaLight key from the Particle System")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delPermaLight expects an int");
        return nullptr;
    }
    self->fThis->delPermaLight(idx);
    Py_RETURN_NONE;
}

PyMethodDef pyParticleSystem_Methods[] = {
    pyParticleSystem_allocEmitters_method,
    pyParticleSystem_getEmitter_method,
    pyParticleSystem_setEmitter_method,
    pyParticleSystem_clearEmitters_method,
    pyParticleSystem_addEmitter_method,
    pyParticleSystem_delEmitter_method,
    pyParticleSystem_clearForces_method,
    pyParticleSystem_addForce_method,
    pyParticleSystem_delForce_method,
    pyParticleSystem_clearEffects_method,
    pyParticleSystem_addEffect_method,
    pyParticleSystem_delEffect_method,
    pyParticleSystem_clearConstraints_method,
    pyParticleSystem_addConstraint_method,
    pyParticleSystem_delConstraint_method,
    pyParticleSystem_clearPermaLights_method,
    pyParticleSystem_addPermaLight_method,
    pyParticleSystem_delPermaLight_method,
    PY_METHOD_TERMINATOR
};


PY_PROPERTY(plKey, ParticleSystem, material, getMaterial, setMaterial)
PY_PROPERTY(uint32_t, ParticleSystem, XTiles, getXTiles, setXTiles)
PY_PROPERTY(uint32_t, ParticleSystem, YTiles, getYTiles, setYTiles)
PY_PROPERTY(hsVector3, ParticleSystem, accel, getAccel, setAccel)
PY_PROPERTY(float, ParticleSystem, preSim, getPreSim, setPreSim)
PY_PROPERTY(float, ParticleSystem, drag, getDrag, setDrag)
PY_PROPERTY(float, ParticleSystem, windMult, getWindMult, setWindMult)
PY_PROPERTY(uint32_t, ParticleSystem, maxTotalParticles, getMaxTotalParticles,
            setMaxTotalParticles)
PY_PROPERTY_RO(ParticleSystem, numValidEmitters, getNumValidEmitters)
PY_PROPERTY_RO(ParticleSystem, maxEmitters, getMaxEmitters)
PY_PROPERTY_CREATABLE(plController, Controller, ParticleSystem, ambientCtl,
                      getAmbientCtl, setAmbientCtl)
PY_PROPERTY_CREATABLE(plController, Controller, ParticleSystem, diffuseCtl,
                      getDiffuseCtl, setDiffuseCtl)
PY_PROPERTY_CREATABLE(plController, Controller, ParticleSystem, opacityCtl,
                      getOpacityCtl, setOpacityCtl)
PY_PROPERTY_CREATABLE(plController, Controller, ParticleSystem, widthCtl,
                      getWidthCtl, setWidthCtl)
PY_PROPERTY_CREATABLE(plController, Controller, ParticleSystem, heightCtl,
                      getHeightCtl, setHeightCtl)


PY_GETSET_GETTER_DECL(ParticleSystem, forces)
{
    const auto& keys = self->fThis->getForces();
    PyObject* result = PyTuple_New(keys.size());
    for (size_t i = 0; i < keys.size(); ++i)
        PyTuple_SET_ITEM(result, i, pyPlasma_convert(keys[i]));
    return result;
}

PY_GETSET_SETTER_DECL(ParticleSystem, forces)
{
    PY_PROPERTY_CHECK_NULL(forces);
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "forces should be a sequence of plKeys");
        return -1;
    }
    std::vector<plKey> keys(seq.size());
    for (size_t i = 0; i < keys.size(); ++i) {
        PyObject* value = seq.get(i);
        if (!pyPlasma_check<plKey>(value)) {
            PyErr_SetString(PyExc_TypeError, "forces should be a sequence of plKeys");
            return -1;
        }
        keys[i] = pyPlasma_get<plKey>(value);
    }
    self->fThis->getForces() = keys;
    return 0;
}

PY_PROPERTY_GETSET_DECL(ParticleSystem, forces)


PY_GETSET_GETTER_DECL(ParticleSystem, effects)
{
    const auto& keys = self->fThis->getEffects();
    PyObject* result = PyTuple_New(keys.size());
    for (size_t i = 0; i < keys.size(); ++i)
        PyTuple_SET_ITEM(result, i, pyPlasma_convert(keys[i]));
    return result;
}

PY_GETSET_SETTER_DECL(ParticleSystem, effects)
{
    PY_PROPERTY_CHECK_NULL(effects);
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "effects should be a sequence of plKeys");
        return -1;
    }
    std::vector<plKey> keys(seq.size());
    for (size_t i = 0; i < keys.size(); ++i) {
        PyObject* value = seq.get(i);
        if (!pyPlasma_check<plKey>(value)) {
            PyErr_SetString(PyExc_TypeError, "effects should be a sequence of plKeys");
            return -1;
        }
        keys[i] = pyPlasma_get<plKey>(value);
    }
    self->fThis->getEffects() = keys;
    return 0;
}

PY_PROPERTY_GETSET_DECL(ParticleSystem, effects)


PY_GETSET_GETTER_DECL(ParticleSystem, constraints)
{
    const auto& keys = self->fThis->getConstraints();
    PyObject* result = PyTuple_New(keys.size());
    for (size_t i = 0; i < keys.size(); ++i)
        PyTuple_SET_ITEM(result, i, pyPlasma_convert(keys[i]));
    return result;
}

PY_GETSET_SETTER_DECL(ParticleSystem, constraints)
{
    PY_PROPERTY_CHECK_NULL(constraints);
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "constraints should be a sequence of plKeys");
        return -1;
    }
    std::vector<plKey> keys(seq.size());
    for (size_t i = 0; i < keys.size(); ++i) {
        PyObject* value = seq.get(i);
        if (!pyPlasma_check<plKey>(value)) {
            PyErr_SetString(PyExc_TypeError, "constraints should be a sequence of plKeys");
            return -1;
        }
        keys[i] = pyPlasma_get<plKey>(value);
    }
    self->fThis->getConstraints() = keys;
    return 0;
}

PY_PROPERTY_GETSET_DECL(ParticleSystem, constraints)


PY_GETSET_GETTER_DECL(ParticleSystem, permaLights)
{
    const auto& keys = self->fThis->getPermaLights();
    PyObject* result = PyTuple_New(keys.size());
    for (size_t i = 0; i < keys.size(); ++i)
        PyTuple_SET_ITEM(result, i, pyPlasma_convert(keys[i]));
    return result;
}

PY_GETSET_SETTER_DECL(ParticleSystem, permaLights)
{
    PY_PROPERTY_CHECK_NULL(permaLights);
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "permaLights should be a sequence of plKeys");
        return -1;
    }
    std::vector<plKey> keys(seq.size());
    for (size_t i = 0; i < keys.size(); ++i) {
        PyObject* value = seq.get(i);
        if (!pyPlasma_check<plKey>(value)) {
            PyErr_SetString(PyExc_TypeError, "permaLights should be a sequence of plKeys");
            return -1;
        }
        keys[i] = pyPlasma_get<plKey>(value);
    }
    self->fThis->getPermaLights() = keys;
    return 0;
}

PY_PROPERTY_GETSET_DECL(ParticleSystem, permaLights)

static PyGetSetDef pyParticleSystem_GetSet[] = {
    pyParticleSystem_material_getset,
    pyParticleSystem_XTiles_getset,
    pyParticleSystem_YTiles_getset,
    pyParticleSystem_accel_getset,
    pyParticleSystem_preSim_getset,
    pyParticleSystem_drag_getset,
    pyParticleSystem_windMult_getset,
    pyParticleSystem_maxTotalParticles_getset,
    pyParticleSystem_numValidEmitters_getset,
    pyParticleSystem_maxEmitters_getset,
    pyParticleSystem_ambientCtl_getset,
    pyParticleSystem_diffuseCtl_getset,
    pyParticleSystem_opacityCtl_getset,
    pyParticleSystem_widthCtl_getset,
    pyParticleSystem_heightCtl_getset,
    pyParticleSystem_forces_getset,
    pyParticleSystem_effects_getset,
    pyParticleSystem_constraints_getset,
    pyParticleSystem_permaLights_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ParticleSystem, plParticleSystem, "plParticleSystem wrapper")

PY_PLASMA_TYPE_INIT(ParticleSystem)
{
    pyParticleSystem_Type.tp_new = pyParticleSystem_new;
    pyParticleSystem_Type.tp_methods = pyParticleSystem_Methods;
    pyParticleSystem_Type.tp_getset = pyParticleSystem_GetSet;
    pyParticleSystem_Type.tp_base = &pyModifier_Type;
    if (PyType_CheckAndReady(&pyParticleSystem_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(ParticleSystem, "kEffectForce", plParticleSystem::kEffectForce);
    PY_TYPE_ADD_CONST(ParticleSystem, "kEffectMisc", plParticleSystem::kEffectMisc);
    PY_TYPE_ADD_CONST(ParticleSystem, "kEffectConstraint", plParticleSystem::kEffectConstraint);

    PY_TYPE_ADD_CONST(ParticleSystem, "kParticleSystemAlwaysUpdate",
                      plParticleSystem::kParticleSystemAlwaysUpdate);

    Py_INCREF(&pyParticleSystem_Type);
    return (PyObject*)&pyParticleSystem_Type;
}

PY_PLASMA_IFC_METHODS(ParticleSystem, plParticleSystem)
