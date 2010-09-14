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
#include <PRP/Object/plSceneObject.h>
#include "pySceneObject.h"
#include "pySynchedObject.h"
#include "PRP/pyCreatable.h"
#include "PRP/KeyedObject/pyKey.h"

extern "C" {

static PyObject* pySceneObject_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pySceneObject* self = (pySceneObject*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plSceneObject();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pySceneObject_clearInterfaces(pySceneObject* self) {
    self->fThis->clearInterfaces();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pySceneObject_clearModifiers(pySceneObject* self) {
    self->fThis->clearModifiers();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pySceneObject_addInterface(pySceneObject* self, PyObject* args) {
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addInterface expects a plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addInterface expects a plKey");
        return NULL;
    }
    self->fThis->addInterface(*key->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pySceneObject_addModifier(pySceneObject* self, PyObject* args) {
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addModifier expects a plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addModifier expects a plKey");
        return NULL;
    }
    self->fThis->addModifier(*key->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pySceneObject_delInterface(pySceneObject* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delInterface expects an int");
        return NULL;
    }
    self->fThis->delInterface(idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pySceneObject_delModifier(pySceneObject* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delModifier expects an int");
        return NULL;
    }
    self->fThis->delModifier(idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pySceneObject_getDraw(pySceneObject* self, void*) {
    return pyKey_FromKey(self->fThis->getDrawInterface());
}

static PyObject* pySceneObject_getSim(pySceneObject* self, void*) {
    return pyKey_FromKey(self->fThis->getSimInterface());
}

static PyObject* pySceneObject_getCoord(pySceneObject* self, void*) {
    return pyKey_FromKey(self->fThis->getCoordInterface());
}

static PyObject* pySceneObject_getAudio(pySceneObject* self, void*) {
    return pyKey_FromKey(self->fThis->getAudioInterface());
}

static PyObject* pySceneObject_getNode(pySceneObject* self, void*) {
    return pyKey_FromKey(self->fThis->getSceneNode());
}

static PyObject* pySceneObject_getIntfs(pySceneObject* self, void*) {
    PyObject* list = PyList_New(self->fThis->getInterfaces().getSize());
    for (size_t i=0; i<self->fThis->getInterfaces().getSize(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getInterfaces()[i]));
    return list;
}

static PyObject* pySceneObject_getMods(pySceneObject* self, void*) {
    PyObject* list = PyList_New(self->fThis->getModifiers().getSize());
    for (size_t i=0; i<self->fThis->getModifiers().getSize(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getModifiers()[i]));
    return list;
}

static int pySceneObject_setDraw(pySceneObject* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setDrawInterface(plKey());
        return 0;
    } else if (pyKey_Check(value)) {
        self->fThis->setDrawInterface(*((pyKey*)value)->fThis);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "draw should be a plKey");
        return -1;
    }
}

static int pySceneObject_setSim(pySceneObject* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setSimInterface(plKey());
        return 0;
    } else if (pyKey_Check(value)) {
        self->fThis->setSimInterface(*((pyKey*)value)->fThis);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "sim should be a plKey");
        return -1;
    }
}

static int pySceneObject_setCoord(pySceneObject* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setCoordInterface(plKey());
        return 0;
    } else if (pyKey_Check(value)) {
        self->fThis->setCoordInterface(*((pyKey*)value)->fThis);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "coord should be a plKey");
        return -1;
    }
}

static int pySceneObject_setAudio(pySceneObject* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setAudioInterface(plKey());
        return 0;
    } else if (pyKey_Check(value)) {
        self->fThis->setAudioInterface(*((pyKey*)value)->fThis);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "audio should be a plKey");
        return -1;
    }
}

static int pySceneObject_setNode(pySceneObject* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setSceneNode(plKey());
        return 0;
    } else if (pyKey_Check(value)) {
        self->fThis->setSceneNode(*((pyKey*)value)->fThis);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "sceneNode should be a plKey");
        return -1;
    }
}

static int pySceneObject_setIntfs(pySceneObject* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add Interfaces, use addInterface");
    return -1;
}

static int pySceneObject_setMods(pySceneObject* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add Modifiers, use addModifier");
    return -1;
}

PyMethodDef pySceneObject_Methods[] = {
    { "clearInterfaces", (PyCFunction)pySceneObject_clearInterfaces, METH_NOARGS,
      "Remove all Interfaces from the Scene Object" },
    { "clearModifiers", (PyCFunction)pySceneObject_clearModifiers, METH_NOARGS,
      "Remove all Modifiers from the Scene Object" },
    { "addInterface", (PyCFunction)pySceneObject_addInterface, METH_VARARGS,
      "Params: key\n"
      "Add an Interface to the Scene Object" },
    { "addModifier", (PyCFunction)pySceneObject_addModifier, METH_VARARGS,
      "Params: key\n"
      "Add a Modifier to the Scene Object" },
    { "delInterface", (PyCFunction)pySceneObject_delInterface, METH_VARARGS,
      "Params: idx\n"
      "Removes an interface from the Scene Object" },
    { "delModifier", (PyCFunction)pySceneObject_delModifier, METH_VARARGS,
      "Params: idx\n"
      "Removes a modifier from the Scene Object" },
    { NULL, NULL, 0, NULL }
};

PyGetSetDef pySceneObject_GetSet[] = {
    { "draw", (getter)pySceneObject_getDraw, (setter)pySceneObject_setDraw,
      "DrawInterface", NULL },
    { "sim", (getter)pySceneObject_getSim, (setter)pySceneObject_setSim,
      "SimulationInterface", NULL },
    { "coord", (getter)pySceneObject_getCoord, (setter)pySceneObject_setCoord,
      "CoordinateInterface", NULL },
    { "audio", (getter)pySceneObject_getAudio, (setter)pySceneObject_setAudio,
      "AudioInterface", NULL },
    { "sceneNode", (getter)pySceneObject_getNode, (setter)pySceneObject_setNode,
      "The SceneNode this object belongs to", NULL },
    { "interfaces", (getter)pySceneObject_getIntfs, (setter)pySceneObject_setIntfs,
      "Extra SceneObject Interfaces", NULL },
    { "modifiers", (getter)pySceneObject_getMods, (setter)pySceneObject_setMods,
      "SceneObject Modifiers", NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pySceneObject_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plSceneObject",           /* tp_name */
    sizeof(pySceneObject),              /* tp_basicsize */
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
    "plSceneObject wrapper",            /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pySceneObject_Methods,              /* tp_methods */
    NULL,                               /* tp_members */
    pySceneObject_GetSet,               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pySceneObject_new,                  /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pySceneObject_Type() {
    pySceneObject_Type.tp_base = &pySynchedObject_Type;
    if (PyType_Ready(&pySceneObject_Type) < 0)
        return NULL;

    Py_INCREF(&pySceneObject_Type);
    return (PyObject*)&pySceneObject_Type;
}

int pySceneObject_Check(PyObject* obj) {
    if (obj->ob_type == &pySceneObject_Type
        || PyType_IsSubtype(obj->ob_type, &pySceneObject_Type))
        return 1;
    return 0;
}

PyObject* pySceneObject_FromSceneObject(class plSceneObject* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pySceneObject* so = PyObject_New(pySceneObject, &pySceneObject_Type);
    so->fThis = obj;
    so->fPyOwned = false;
    return (PyObject*)so;
}

}
