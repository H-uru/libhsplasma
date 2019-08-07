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

#include "pySceneObject.h"

#include <PRP/Object/plSceneObject.h>
#include "pySynchedObject.h"
#include "PRP/pyCreatable.h"
#include "PRP/KeyedObject/pyKey.h"

PY_PLASMA_NEW(SceneObject, plSceneObject)

PY_METHOD_NOARGS(SceneObject, clearInterfaces,
    "Remove all Interfaces from the Scene Object")
{
    self->fThis->clearInterfaces();
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(SceneObject, clearModifiers,
    "Remove all Modifiers from the Scene Object")
{
    self->fThis->clearModifiers();
    Py_RETURN_NONE;
}

PY_METHOD_VA(SceneObject, addInterface,
    "Params: key\n"
    "Add an Interface to the Scene Object")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addInterface expects a plKey");
        return nullptr;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addInterface expects a plKey");
        return nullptr;
    }
    self->fThis->addInterface(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(SceneObject, addModifier,
    "Params: key\n"
    "Add a Modifier to the Scene Object")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addModifier expects a plKey");
        return nullptr;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addModifier expects a plKey");
        return nullptr;
    }
    self->fThis->addModifier(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(SceneObject, delInterface,
    "Params: idx\n"
    "Removes an interface from the Scene Object")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delInterface expects an int");
        return nullptr;
    }
    self->fThis->delInterface(idx);
    Py_RETURN_NONE;
}

PY_METHOD_VA(SceneObject, delModifier,
    "Params: idx\n"
    "Removes a modifier from the Scene Object")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delModifier expects an int");
        return nullptr;
    }
    self->fThis->delModifier(idx);
    Py_RETURN_NONE;
}

PyMethodDef pySceneObject_Methods[] = {
    pySceneObject_clearInterfaces_method,
    pySceneObject_clearModifiers_method,
    pySceneObject_addInterface_method,
    pySceneObject_addModifier_method,
    pySceneObject_delInterface_method,
    pySceneObject_delModifier_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(SceneObject, interfaces)
{
    PyObject* list = PyTuple_New(self->fThis->getInterfaces().size());
    for (size_t i=0; i<self->fThis->getInterfaces().size(); i++)
        PyTuple_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getInterfaces()[i]));
    return list;
}

PY_PROPERTY_SETTER_MSG(SceneObject, interfaces, "To add Interfaces, use addInterface")
PY_PROPERTY_GETSET_DECL(SceneObject, interfaces)

PY_GETSET_GETTER_DECL(SceneObject, modifiers)
{
    PyObject* list = PyTuple_New(self->fThis->getModifiers().size());
    for (size_t i=0; i<self->fThis->getModifiers().size(); i++)
        PyTuple_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getModifiers()[i]));
    return list;
}

PY_PROPERTY_SETTER_MSG(SceneObject, modifiers, "To add Modifiers, use addModifier")
PY_PROPERTY_GETSET_DECL(SceneObject, modifiers)

PY_PROPERTY(plKey, SceneObject, draw, getDrawInterface, setDrawInterface)
PY_PROPERTY(plKey, SceneObject, sim, getSimInterface, setSimInterface)
PY_PROPERTY(plKey, SceneObject, coord, getCoordInterface, setCoordInterface)
PY_PROPERTY(plKey, SceneObject, audio, getAudioInterface, setAudioInterface)
PY_PROPERTY(plKey, SceneObject, sceneNode, getSceneNode, setSceneNode)

PyGetSetDef pySceneObject_GetSet[] = {
    pySceneObject_draw_getset,
    pySceneObject_sim_getset,
    pySceneObject_coord_getset,
    pySceneObject_audio_getset,
    pySceneObject_sceneNode_getset,
    pySceneObject_interfaces_getset,
    pySceneObject_modifiers_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(SceneObject, plSceneObject, "plSceneObject wrapper")

PY_PLASMA_TYPE_INIT(SceneObject)
{
    pySceneObject_Type.tp_new = pySceneObject_new;
    pySceneObject_Type.tp_methods = pySceneObject_Methods;
    pySceneObject_Type.tp_getset = pySceneObject_GetSet;
    pySceneObject_Type.tp_base = &pySynchedObject_Type;
    if (PyType_CheckAndReady(&pySceneObject_Type) < 0)
        return nullptr;

    Py_INCREF(&pySceneObject_Type);
    return (PyObject*)&pySceneObject_Type;
}

PY_PLASMA_IFC_METHODS(SceneObject, plSceneObject)
