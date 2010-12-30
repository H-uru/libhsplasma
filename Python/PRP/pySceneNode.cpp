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

#include <PyPlasma.h>
#include <PRP/plSceneNode.h>
#include "pySceneNode.h"
#include "KeyedObject/pyKey.h"
#include "KeyedObject/pyKeyedObject.h"
#include "pyCreatable.h"

extern "C" {

static PyObject* pySceneNode_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pySceneNode* self = (pySceneNode*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plSceneNode();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pySceneNode_clear(pySceneNode* self) {
    self->fThis->clearSceneObjects();
    self->fThis->clearPoolObjects();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pySceneNode_addSceneObject(pySceneNode* self, PyObject* args) {
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
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pySceneNode_addPoolObject(pySceneNode* self, PyObject* args) {
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
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pySceneNode_addSceneObjects(pySceneNode* self, PyObject* args) {
    PyObject* list;
    if (!PyArg_ParseTuple(args, "O", &list)) {
        PyErr_SetString(PyExc_TypeError, "addSceneObjects expects a list of plKeys");
        return NULL;
    }
    if (!PyList_Check(list)) {
        PyErr_SetString(PyExc_TypeError, "addSceneObjects expects a list of plKeys");
        return NULL;
    }
    hsTArray<plKey> addend;
    addend.setSize(PyList_Size(list));
    for (size_t i=0; i<addend.getSize(); i++) {
        pyKey* key = (pyKey*)PyList_GetItem(list, i);
        if (key == NULL)
            return NULL;
        if (!pyKey_Check((PyObject*)key)) {
            PyErr_SetString(PyExc_TypeError, "addSceneObjects expects a list of plKeys");
            return NULL;
        }
        addend[i] = *key->fThis;
    }
    self->fThis->getSceneObjects().append(addend);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pySceneNode_addPoolObjects(pySceneNode* self, PyObject* args) {
    PyObject* list;
    if (!PyArg_ParseTuple(args, "O", &list)) {
        PyErr_SetString(PyExc_TypeError, "addPoolObjects expects a list of plKeys");
        return NULL;
    }
    if (!PyList_Check(list)) {
        PyErr_SetString(PyExc_TypeError, "addPoolObjects expects a list of plKeys");
        return NULL;
    }
    hsTArray<plKey> addend;
    addend.setSize(PyList_Size(list));
    for (size_t i=0; i<addend.getSize(); i++) {
        pyKey* key = (pyKey*)PyList_GetItem(list, i);
        if (key == NULL)
            return NULL;
        if (!pyKey_Check((PyObject*)key)) {
            PyErr_SetString(PyExc_TypeError, "addPoolObjects expects a list of plKeys");
            return NULL;
        }
        addend[i] = *key->fThis;
    }
    self->fThis->getPoolObjects().append(addend);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pySceneNode_getSceneObjects(pySceneNode* self, void*) {
    PyObject* list = PyList_New(self->fThis->getSceneObjects().getSize());
    for (size_t i=0; i<self->fThis->getSceneObjects().getSize(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getSceneObjects()[i]));
    return list;
}

static PyObject* pySceneNode_getPoolObjects(pySceneNode* self, void*) {
    PyObject* list = PyList_New(self->fThis->getPoolObjects().getSize());
    for (size_t i=0; i<self->fThis->getPoolObjects().getSize(); i++)
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
    { "clear", (PyCFunction)pySceneNode_clear, METH_NOARGS,
      "Removes all objects from the Scene Node" },
    { "addSceneObject", (PyCFunction)pySceneNode_addSceneObject, METH_VARARGS,
      "Params: key\n"
      "Adds the Scene Object to the Scene Node" },
    { "addPoolObject", (PyCFunction)pySceneNode_addPoolObject, METH_VARARGS,
      "Params: key\n"
      "Adds the Object to the Scene Node" },
    { "addSceneObjects", (PyCFunction)pySceneNode_addSceneObjects, METH_VARARGS,
      "Params: keyArray\n"
      "Adds multiple Scene Objects to the Scene Node" },
    { "addPoolObject", (PyCFunction)pySceneNode_addPoolObjects, METH_VARARGS,
      "Params: keyArray\n"
      "Adds multiple Object to the Scene Node" },
    { NULL, NULL, 0, NULL }
};

PyGetSetDef pySceneNode_GetSet[] = {
    { "sceneObjects", (getter)pySceneNode_getSceneObjects,
      (setter)pySceneNode_setSceneObjects, NULL, NULL },
    { "poolObjects", (getter)pySceneNode_getPoolObjects,
      (setter)pySceneNode_setPoolObjects, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pySceneNode_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plSceneNode",             /* tp_name */
    sizeof(pySceneNode),                /* tp_basicsize */
    0,                                  /* tp_itemsize */

    NULL,                               /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_compare */
    NULL,                               /* tp_repr */
    NULL,                               /* tp_as_number */
    NULL,                               /* tp_as_sequence */
    NULL,                               /* tp_as_mapping */
    NULL,                               /* tp_hash */
    NULL,                               /* tp_call */
    NULL,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */

    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
    "plSceneNode wrapper",              /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pySceneNode_Methods,                /* tp_methods */
    NULL,                               /* tp_members */
    pySceneNode_GetSet,                 /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pySceneNode_new,                    /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */

    NULL,                               /* tp_del */
    TP_VERSION_TAG_INIT                 /* tp_version_tag */
};

PyObject* Init_pySceneNode_Type() {
    pySceneNode_Type.tp_base = &pyKeyedObject_Type;
    if (PyType_Ready(&pySceneNode_Type) < 0)
        return NULL;

    Py_INCREF(&pySceneNode_Type);
    return (PyObject*)&pySceneNode_Type;
}

int pySceneNode_Check(PyObject* obj) {
    if (obj->ob_type == &pySceneNode_Type
        || PyType_IsSubtype(obj->ob_type, &pySceneNode_Type))
        return 1;
    return 0;
}

PyObject* pySceneNode_FromSceneNode(class plSceneNode* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pySceneNode* node = PyObject_New(pySceneNode, &pySceneNode_Type);
    delete node->fThis;
    node->fThis = obj;
    node->fPyOwned = false;
    return (PyObject*)node;
}

}
