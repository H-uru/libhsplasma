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

#include "pyAudible.h"

#include <PRP/Audio/plAudible.h>
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW(WinAudible, plWinAudible)

PY_METHOD_VA(WinAudible, addSound,
    "Params: sound\n"
    "Add a sound object to the Audible")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addSound expects a plKey");
        return nullptr;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addSound expects a plKey");
        return nullptr;
    }
    self->fThis->addSound(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(WinAudible, delSound,
    "Params: idx\n"
    "Remove a sound object from the Audible")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delSound expects an int");
        return nullptr;
    }
    self->fThis->delSound(idx);
    Py_RETURN_NONE;
}

PY_METHOD_VA(WinAudible, clearSounds, "Remove all sound objects from the Audible")
{
    self->fThis->clearSounds();
    Py_RETURN_NONE;
}

static PyMethodDef pyWinAudible_Methods[] = {
    pyWinAudible_addSound_method,
    pyWinAudible_delSound_method,
    pyWinAudible_clearSounds_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(WinAudible, sounds)
{
    const std::vector<plKey>& sounds = self->fThis->getSounds();
    PyObject* list = PyTuple_New(sounds.size());
    for (size_t i=0; i<sounds.size(); i++)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(sounds[i]));
    return list;
}

PY_PROPERTY_SETTER_MSG(WinAudible, sounds, "To add sounds, use addSound()")
PY_PROPERTY_GETSET_DECL(WinAudible, sounds)

PY_PROPERTY(plKey, WinAudible, sceneNode, getSceneNode, setSceneNode)

static PyGetSetDef pyWinAudible_GetSet[] = {
    pyWinAudible_sounds_getset,
    pyWinAudible_sceneNode_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(WinAudible, plWinAudible, "plWinAudible wrapper")

PY_PLASMA_TYPE_INIT(WinAudible)
{
    pyWinAudible_Type.tp_new = pyWinAudible_new;
    pyWinAudible_Type.tp_methods = pyWinAudible_Methods;
    pyWinAudible_Type.tp_getset = pyWinAudible_GetSet;
    pyWinAudible_Type.tp_base = &pyAudible_Type;
    if (PyType_CheckAndReady(&pyWinAudible_Type) < 0)
        return nullptr;

    Py_INCREF(&pyWinAudible_Type);
    return (PyObject*)&pyWinAudible_Type;
}

PY_PLASMA_IFC_METHODS(WinAudible, plWinAudible)
