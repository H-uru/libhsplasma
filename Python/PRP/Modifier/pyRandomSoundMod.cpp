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

#include "pyRandomSoundMod.h"
#include "pyRandomCommandMod.h"

#include <PRP/Modifier/plRandomSoundMod.h>
#include "pyModifier.h"
#include "PRP/pyCreatable.h"


/* plRandomSoundModGroup */
PY_PLASMA_NEW(RandomSoundModGroup, plRandomSoundModGroup)

PY_PLASMA_TYPE(RandomSoundModGroup, plRandomSoundModGroup, "plRandomSoundModGroup wrapper")

PY_PLASMA_TYPE_INIT(RandomSoundModGroup)
{
    pyRandomSoundModGroup_Type.tp_new = pyRandomSoundModGroup_new;
    if (PyType_CheckAndReady(&pyRandomSoundModGroup_Type) < 0)
        return nullptr;

    Py_INCREF(&pyRandomSoundModGroup_Type);
    return (PyObject*)&pyRandomSoundModGroup_Type;
}

PY_PLASMA_IFC_METHODS(RandomSoundModGroup, plRandomSoundModGroup)


/* plRandomSoundMod */
PY_PLASMA_NEW(RandomSoundMod, plRandomSoundMod)

PY_METHOD_VA(RandomSoundMod, addGroup,
    "Params: group\n"
    "Add a RandomSoundModGroup to this RandomSoundMod")
{
    pyRandomSoundModGroup* group;
    if (!PyArg_ParseTuple(args, "O", &group)) {
        PyErr_SetString(PyExc_TypeError, "addGroup expects a plRandomSoundModGroup");
        return nullptr;
    }
    if (!pyRandomSoundModGroup_Check((PyObject*)group)) {
        PyErr_SetString(PyExc_TypeError, "addGroup expects a plRandomSoundModGroup");
        return nullptr;
    }
    group->fPyOwned = false;
    self->fThis->addGroup(*group->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(RandomSoundMod, delGroup,
    "Params: idx\n"
    "Delete a RandomSoundModGroup from this RandomSoundMod")
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delGroup expects an int");
        return nullptr;
    }
    if ((size_t)idx < self->fThis->getGroups().size()) {
        self->fThis->delGroup(idx);
        Py_RETURN_NONE;
    } else {
        PyErr_SetNone(PyExc_IndexError);
        return nullptr;
    }
}

PY_METHOD_NOARGS(RandomSoundMod, clearGroups,
    "Remove all RandomSoundModGroups from this RandomSoundMod")
{
    self->fThis->clearGroups();
    Py_RETURN_NONE;
}

static PyMethodDef pyRandomSoundMod_Methods[] = {
    pyRandomSoundMod_addGroup_method,
    pyRandomSoundMod_delGroup_method,
    pyRandomSoundMod_clearGroups_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(RandomSoundMod, groups)
{
    PyObject* list = PyTuple_New(self->fThis->getGroups().size());
    for (size_t i = 0; i < self->fThis->getGroups().size(); ++i)
        PyTuple_SET_ITEM(list, i, pyRandomSoundModGroup_FromRandomSoundModGroup(&self->fThis->getGroups()[i]));
    return list;
}

PY_PROPERTY_SETTER_MSG(RandomSoundMod, groups, "To add groups, use addGroup()")
PY_PROPERTY_GETSET_DECL(RandomSoundMod, groups)

static PyGetSetDef pyRandomSoundMod_GetSet[] = {
    pyRandomSoundMod_groups_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(RandomSoundMod, plRandomSoundMod, "plRandomSoundMod wrapper")

PY_PLASMA_TYPE_INIT(RandomSoundMod)
{
    pyRandomSoundMod_Type.tp_new = pyRandomSoundMod_new;
    pyRandomSoundMod_Type.tp_base = &pyRandomCommandMod_Type;
    pyRandomSoundMod_Type.tp_methods = pyRandomSoundMod_Methods;
    pyRandomSoundMod_Type.tp_getset = pyRandomSoundMod_GetSet;
    if (PyType_CheckAndReady(&pyRandomSoundMod_Type) < 0)
        return nullptr;

    Py_INCREF(&pyRandomSoundMod_Type);
    return (PyObject*)&pyRandomSoundMod_Type;
}

PY_PLASMA_IFC_METHODS(RandomSoundMod, plRandomSoundMod)
