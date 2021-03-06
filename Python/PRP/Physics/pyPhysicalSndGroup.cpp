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

#include "pyPhysicalSndGroup.h"

#include <PRP/Physics/plPhysicalSndGroup.h>
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/KeyedObject/pyKeyedObject.h"

PY_PLASMA_NEW(PhysicalSndGroup, plPhysicalSndGroup)

PY_METHOD_VA(PhysicalSndGroup, addImpactSound, "Params: sound")
{
    PyObject* sound;
    if (!PyArg_ParseTuple(args, "O", &sound) || !pyPlasma_check<plKey>(sound)) {
        PyErr_SetString(PyExc_TypeError, "addImpactSound expects a plKey");
        return nullptr;
    }
    self->fThis->addImpactSound(pyPlasma_get<plKey>(sound));
    Py_RETURN_NONE;
}

PY_METHOD_VA(PhysicalSndGroup, delImpactSound, "Params: idx")
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delImpactSound expects an int");
        return nullptr;
    }
    if ((size_t)idx < self->fThis->getImpactSounds().size()) {
        self->fThis->delImpactSound(idx);
        Py_RETURN_NONE;
    } else {
        PyErr_SetNone(PyExc_IndexError);
        return nullptr;
    }
}

PY_METHOD_NOARGS(PhysicalSndGroup, clearImpactSounds, "Removes all slide sounds")
{
    self->fThis->clearImpactSounds();
    Py_RETURN_NONE;
}

PY_METHOD_VA(PhysicalSndGroup, addSlideSound, "Params: sound")
{
    PyObject* sound;
    if (!PyArg_ParseTuple(args, "O", &sound) || !pyPlasma_check<plKey>(sound)) {
        PyErr_SetString(PyExc_TypeError, "addSlideSound expects a plKey");
        return nullptr;
    }
    self->fThis->addSlideSound(pyPlasma_get<plKey>(sound));
    Py_RETURN_NONE;
}

PY_METHOD_VA(PhysicalSndGroup, delSlideSound, "Params: idx")
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delSlideSound expects an int");
        return nullptr;
    }
    if ((size_t)idx < self->fThis->getSlideSounds().size()) {
        self->fThis->delSlideSound(idx);
        Py_RETURN_NONE;
    } else {
        PyErr_SetNone(PyExc_IndexError);
        return nullptr;
    }
}

PY_METHOD_NOARGS(PhysicalSndGroup, clearSlideSounds, "Removes all slide sounds")
{
    self->fThis->clearSlideSounds();
    Py_RETURN_NONE;
}

static PyMethodDef pyPhysicalSndGroup_Methods[] = {
    pyPhysicalSndGroup_addImpactSound_method,
    pyPhysicalSndGroup_delImpactSound_method,
    pyPhysicalSndGroup_clearImpactSounds_method,
    pyPhysicalSndGroup_addSlideSound_method,
    pyPhysicalSndGroup_delSlideSound_method,
    pyPhysicalSndGroup_clearSlideSounds_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY(unsigned int, PhysicalSndGroup, group, getGroup, setGroup)

PY_GETSET_GETTER_DECL(PhysicalSndGroup, impactSounds)
{
    const std::vector<plKey>& sounds = self->fThis->getImpactSounds();
    PyObject* tup = PyTuple_New(sounds.size());
    for (size_t i = 0; i < sounds.size(); ++i)
        PyTuple_SET_ITEM(tup, i, pyPlasma_convert(sounds[i]));
    return tup;
}
PY_GETSET_SETTER_DECL(PhysicalSndGroup, impactSounds)
{
    PY_PROPERTY_CHECK_NULL(impactSounds);
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "impactSounds should be a sequence of plKey");
        return -1;
    }
    self->fThis->getImpactSounds().resize(seq.size());
    for (size_t i = 0; i < self->fThis->getImpactSounds().size(); ++i) {
        PyObject* item = seq.get(i);
        if (!pyPlasma_check<plKey>(item)) {
            PyErr_SetString(PyExc_TypeError, "impactSounds should be a sequence of plKey");
            return -1;
        }
        self->fThis->getImpactSounds()[i] = pyPlasma_get<plKey>(item);
    }
    return 0;
}
PY_PROPERTY_GETSET_DECL(PhysicalSndGroup, impactSounds)

PY_GETSET_GETTER_DECL(PhysicalSndGroup, slideSounds)
{
    const std::vector<plKey>& sounds = self->fThis->getSlideSounds();
    PyObject* tup = PyTuple_New(sounds.size());
    for (size_t i = 0; i < sounds.size(); ++i)
        PyTuple_SET_ITEM(tup, i, pyPlasma_convert(sounds[i]));
    return tup;
}
PY_GETSET_SETTER_DECL(PhysicalSndGroup, slideSounds)
{
    PY_PROPERTY_CHECK_NULL(slideSounds);
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "slideSounds should be a sequence of plKey");
        return -1;
    }
    self->fThis->getSlideSounds().resize(seq.size());
    for (size_t i = 0; i < self->fThis->getSlideSounds().size(); ++i) {
        PyObject* item = seq.get(i);
        if (!pyPlasma_check<plKey>(item)) {
            PyErr_SetString(PyExc_TypeError, "slideSounds should be a sequence of plKey");
            return -1;
        }
        self->fThis->getSlideSounds()[i] = pyPlasma_get<plKey>(item);
    }
    return 0;
}
PY_PROPERTY_GETSET_DECL(PhysicalSndGroup, slideSounds)

static PyGetSetDef pyPhysicalSndGroup_GetSet[] = {
    pyPhysicalSndGroup_group_getset,
    pyPhysicalSndGroup_impactSounds_getset,
    pyPhysicalSndGroup_slideSounds_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(PhysicalSndGroup, plPhysicalSndGroup, "plPhysicalSndGroup wrapper")

PY_PLASMA_TYPE_INIT(PhysicalSndGroup)
{
    pyPhysicalSndGroup_Type.tp_new = pyPhysicalSndGroup_new;
    pyPhysicalSndGroup_Type.tp_methods = pyPhysicalSndGroup_Methods;
    pyPhysicalSndGroup_Type.tp_getset = pyPhysicalSndGroup_GetSet;
    pyPhysicalSndGroup_Type.tp_base = &pyKeyedObject_Type;
    if (PyType_CheckAndReady(&pyPhysicalSndGroup_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(PhysicalSndGroup, "kNone", plPhysicalSndGroup::kNone);
    PY_TYPE_ADD_CONST(PhysicalSndGroup, "kMetal", plPhysicalSndGroup::kMetal);
    PY_TYPE_ADD_CONST(PhysicalSndGroup, "kGrass", plPhysicalSndGroup::kGrass);
    PY_TYPE_ADD_CONST(PhysicalSndGroup, "kWood", plPhysicalSndGroup::kWood);
    PY_TYPE_ADD_CONST(PhysicalSndGroup, "kStone", plPhysicalSndGroup::kStone);
    PY_TYPE_ADD_CONST(PhysicalSndGroup, "kWater", plPhysicalSndGroup::kWater);
    PY_TYPE_ADD_CONST(PhysicalSndGroup, "kBone", plPhysicalSndGroup::kBone);
    PY_TYPE_ADD_CONST(PhysicalSndGroup, "kDirt", plPhysicalSndGroup::kDirt);
    PY_TYPE_ADD_CONST(PhysicalSndGroup, "kRug", plPhysicalSndGroup::kRug);
    PY_TYPE_ADD_CONST(PhysicalSndGroup, "kCone", plPhysicalSndGroup::kCone);
    PY_TYPE_ADD_CONST(PhysicalSndGroup, "kUser1", plPhysicalSndGroup::kUser1);
    PY_TYPE_ADD_CONST(PhysicalSndGroup, "kUser2", plPhysicalSndGroup::kUser2);
    PY_TYPE_ADD_CONST(PhysicalSndGroup, "kUser3", plPhysicalSndGroup::kUser3);

    Py_INCREF(&pyPhysicalSndGroup_Type);
    return (PyObject*)&pyPhysicalSndGroup_Type;
}

PY_PLASMA_IFC_METHODS(PhysicalSndGroup, plPhysicalSndGroup)

