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

extern "C" {

PY_PLASMA_NEW(SceneNode, plSceneNode)

PY_METHOD_NOARGS(SceneNode, clear, "Removes all objects from the Scene Node") {
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
        return NULL;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addSceneObject expects a plKey");
        return NULL;
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
        return NULL;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addPoolObject expects a plKey");
        return NULL;
    }
    self->fThis->addPoolObject(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(SceneNode, addSceneObjects,
    "Params: keyArray\n"
    "Adds multiple Scene Objects to the Scene Node")
{
    PyObject* list;
    if (!PyArg_ParseTuple(args, "O", &list)) {
        PyErr_SetString(PyExc_TypeError, "addSceneObjects expects a list of plKeys");
        return NULL;
    }
    if (!PyList_Check(list)) {
        PyErr_SetString(PyExc_TypeError, "addSceneObjects expects a list of plKeys");
        return NULL;
    }
    std::vector<plKey> addend(PyList_Size(list));
    for (size_t i=0; i<addend.size(); i++) {
        pyKey* key = (pyKey*)PyList_GetItem(list, i);
        if (key == NULL)
            return NULL;
        if (!pyKey_Check((PyObject*)key)) {
            PyErr_SetString(PyExc_TypeError, "addSceneObjects expects a list of plKeys");
            return NULL;
        }
        addend[i] = *key->fThis;
    }
    self->fThis->getSceneObjects().insert(self->fThis->getSceneObjects().end(),
                                          addend.begin(), addend.end());
    Py_RETURN_NONE;
}

PY_METHOD_VA(SceneNode, addPoolObjects,
    "Params: keyArray\n"
    "Adds multiple Object to the Scene Node")
{
    PyObject* list;
    if (!PyArg_ParseTuple(args, "O", &list)) {
        PyErr_SetString(PyExc_TypeError, "addPoolObjects expects a list of plKeys");
        return NULL;
    }
    if (!PyList_Check(list)) {
        PyErr_SetString(PyExc_TypeError, "addPoolObjects expects a list of plKeys");
        return NULL;
    }
    std::vector<plKey> addend(PyList_Size(list));
    for (size_t i=0; i<addend.size(); i++) {
        pyKey* key = (pyKey*)PyList_GetItem(list, i);
        if (key == NULL)
            return NULL;
        if (!pyKey_Check((PyObject*)key)) {
            PyErr_SetString(PyExc_TypeError, "addPoolObjects expects a list of plKeys");
            return NULL;
        }
        addend[i] = *key->fThis;
    }
    self->fThis->getPoolObjects().insert(self->fThis->getPoolObjects().end(),
                                         addend.begin(), addend.end());
    Py_RETURN_NONE;
}

static PyObject* pySceneNode_getSceneObjects(pySceneNode* self, void*) {
    PyObject* list = PyList_New(self->fThis->getSceneObjects().size());
    for (size_t i=0; i<self->fThis->getSceneObjects().size(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getSceneObjects()[i]));
    return list;
}

static PyObject* pySceneNode_getPoolObjects(pySceneNode* self, void*) {
    PyObject* list = PyList_New(self->fThis->getPoolObjects().size());
    for (size_t i=0; i<self->fThis->getPoolObjects().size(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getPoolObjects()[i]));
    return list;
}

static int pySceneNode_setSceneObjects(pySceneNode* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add Scene Objects, use addSceneObjects");
    return -1;
}

static int pySceneNode_setPoolObjects(pySceneNode* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add Pool Objects, use addPoolObjects");
    return -1;
}

PyMethodDef pySceneNode_Methods[] = {
    pySceneNode_clear_method,
    pySceneNode_addSceneObject_method,
    pySceneNode_addPoolObject_method,
    pySceneNode_addSceneObjects_method,
    pySceneNode_addPoolObjects_method,
    PY_METHOD_TERMINATOR
};

PyGetSetDef pySceneNode_GetSet[] = {
    { _pycs("sceneObjects"), (getter)pySceneNode_getSceneObjects,
        (setter)pySceneNode_setSceneObjects, NULL, NULL },
    { _pycs("poolObjects"), (getter)pySceneNode_getPoolObjects,
        (setter)pySceneNode_setPoolObjects, NULL, NULL },
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(SceneNode, plSceneNode, "plSceneNode wrapper")

PY_PLASMA_TYPE_INIT(SceneNode) {
    pySceneNode_Type.tp_new = pySceneNode_new;
    pySceneNode_Type.tp_methods = pySceneNode_Methods;
    pySceneNode_Type.tp_getset = pySceneNode_GetSet;
    pySceneNode_Type.tp_base = &pyKeyedObject_Type;
    if (PyType_CheckAndReady(&pySceneNode_Type) < 0)
        return NULL;

    Py_INCREF(&pySceneNode_Type);
    return (PyObject*)&pySceneNode_Type;
}

PY_PLASMA_IFC_METHODS(SceneNode, plSceneNode)

}
