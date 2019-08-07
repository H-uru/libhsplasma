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

#include "pySceneNode.h"

#include <PRP/plSceneNode.h>
#include "KeyedObject/pyKey.h"
#include "KeyedObject/pyKeyedObject.h"

PY_PLASMA_NEW(SceneNode, plSceneNode)

PY_METHOD_NOARGS(SceneNode, clear, "Removes all objects from the Scene Node")
{
    self->fThis->clearSceneObjects();
    self->fThis->clearPoolObjects();
    Py_RETURN_NONE;
}

PY_METHOD_VA(SceneNode, addSceneObject,
    "Params: key\n"
    "Adds the Scene Object to the Scene Node")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addSceneObject expects a plKey");
        return nullptr;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addSceneObject expects a plKey");
        return nullptr;
    }
    self->fThis->addSceneObject(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(SceneNode, addPoolObject,
    "Params: key\n"
    "Adds the Object to the Scene Node")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addPoolObject expects a plKey");
        return nullptr;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addPoolObject expects a plKey");
        return nullptr;
    }
    self->fThis->addPoolObject(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(SceneNode, addSceneObjects,
    "Params: keyArray\n"
    "Adds multiple Scene Objects to the Scene Node")
{
    PyObject* seqObj;
    if (!PyArg_ParseTuple(args, "O", &seqObj)) {
        PyErr_SetString(PyExc_TypeError, "addSceneObjects expects a sequence of plKeys");
        return nullptr;
    }
    pySequenceFastRef list(seqObj);
    if (!list.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "addSceneObjects expects a sequence of plKeys");
        return nullptr;
    }
    std::vector<plKey> addend(list.size());
    for (size_t i=0; i<addend.size(); i++) {
        PyObject* key = list.get(i);
        if (!pyKey_Check(key)) {
            PyErr_SetString(PyExc_TypeError, "addSceneObjects expects a sequence of plKeys");
            return nullptr;
        }
        addend[i] = pyPlasma_get<plKey>(key);
    }
    self->fThis->getSceneObjects().insert(self->fThis->getSceneObjects().end(),
                                          addend.begin(), addend.end());
    Py_RETURN_NONE;
}

PY_METHOD_VA(SceneNode, addPoolObjects,
    "Params: keyArray\n"
    "Adds multiple Object to the Scene Node")
{
    PyObject* seqObj;
    if (!PyArg_ParseTuple(args, "O", &seqObj)) {
        PyErr_SetString(PyExc_TypeError, "addPoolObjects expects a sequence of plKeys");
        return nullptr;
    }
    pySequenceFastRef list(seqObj);
    if (!list.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "addPoolObjects expects a sequence of plKeys");
        return nullptr;
    }
    std::vector<plKey> addend(list.size());
    for (size_t i=0; i<addend.size(); i++) {
        PyObject* key = list.get(i);
        if (!pyKey_Check(key)) {
            PyErr_SetString(PyExc_TypeError, "addPoolObjects expects a sequence of plKeys");
            return nullptr;
        }
        addend[i] = pyPlasma_get<plKey>(key);
    }
    self->fThis->getPoolObjects().insert(self->fThis->getPoolObjects().end(),
                                         addend.begin(), addend.end());
    Py_RETURN_NONE;
}

PyMethodDef pySceneNode_Methods[] = {
    pySceneNode_clear_method,
    pySceneNode_addSceneObject_method,
    pySceneNode_addPoolObject_method,
    pySceneNode_addSceneObjects_method,
    pySceneNode_addPoolObjects_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(SceneNode, sceneObjects)
{
    PyObject* list = PyTuple_New(self->fThis->getSceneObjects().size());
    for (size_t i=0; i<self->fThis->getSceneObjects().size(); i++)
        PyTuple_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getSceneObjects()[i]));
    return list;
}

PY_PROPERTY_SETTER_MSG(SceneNode, sceneObjects, "To add Scene Objects, use addSceneObjects")
PY_PROPERTY_GETSET_DECL(SceneNode, sceneObjects)

PY_GETSET_GETTER_DECL(SceneNode, poolObjects)
{
    PyObject* list = PyTuple_New(self->fThis->getPoolObjects().size());
    for (size_t i=0; i<self->fThis->getPoolObjects().size(); i++)
        PyTuple_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getPoolObjects()[i]));
    return list;
}

PY_PROPERTY_SETTER_MSG(SceneNode, poolObjects, "To add Pool Objects, use addPoolObjects")
PY_PROPERTY_GETSET_DECL(SceneNode, poolObjects)

PyGetSetDef pySceneNode_GetSet[] = {
    pySceneNode_sceneObjects_getset,
    pySceneNode_poolObjects_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(SceneNode, plSceneNode, "plSceneNode wrapper")

PY_PLASMA_TYPE_INIT(SceneNode)
{
    pySceneNode_Type.tp_new = pySceneNode_new;
    pySceneNode_Type.tp_methods = pySceneNode_Methods;
    pySceneNode_Type.tp_getset = pySceneNode_GetSet;
    pySceneNode_Type.tp_base = &pyKeyedObject_Type;
    if (PyType_CheckAndReady(&pySceneNode_Type) < 0)
        return nullptr;

    Py_INCREF(&pySceneNode_Type);
    return (PyObject*)&pySceneNode_Type;
}

PY_PLASMA_IFC_METHODS(SceneNode, plSceneNode)
