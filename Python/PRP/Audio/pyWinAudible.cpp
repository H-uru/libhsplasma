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

extern "C" {

static PyObject* pyWinAudible_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyWinAudible* self = (pyWinAudible*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plWinAudible();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyWinAudible_addSound(pyWinAudible* self, PyObject* args) {
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addSound expects a plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addSound expects a plKey");
        return NULL;
    }
    self->fThis->addSound(*key->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyWinAudible_delSound(pyWinAudible* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delSound expects an int");
        return NULL;
    }
    self->fThis->delSound(idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyWinAudible_clearSounds(pyWinAudible* self) {
    self->fThis->clearSounds();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyWinAudible_getSounds(pyWinAudible* self, void*) {
    PyObject* list = PyList_New(self->fThis->getSounds().size());
    for (size_t i=0; i<self->fThis->getSounds().size(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getSounds()[i]));
    return list;
}

static int pyWinAudible_setSounds(pyWinAudible* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "to add sounds, use addSound()");
    return -1;
}

static PyMethodDef pyWinAudible_Methods[] = {
    { "addSound", (PyCFunction)pyWinAudible_addSound, METH_VARARGS,
      "Params: sound\n"
      "Add a sound object to the Audible" },
    { "delSound", (PyCFunction)pyWinAudible_delSound, METH_VARARGS,
      "Params: idx\n"
      "Remove a sound object from the Audible" },
    { "clearSounds", (PyCFunction)pyWinAudible_clearSounds, METH_NOARGS,
      "Remove all sound objects from the Audible" },
    { NULL, NULL, 0, NULL }
};

PY_PROPERTY(plKey, WinAudible, sceneNode, getSceneNode, setSceneNode)

static PyGetSetDef pyWinAudible_GetSet[] = {
    { _pycs("sounds"), (getter)pyWinAudible_getSounds, (setter)pyWinAudible_setSounds, NULL, NULL },
    pyWinAudible_sceneNode_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyWinAudible_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plWinAudible",          /* tp_name */
    sizeof(pyWinAudible),               /* tp_basicsize */
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
    "plWinAudible wrapper",             /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyWinAudible_Methods,               /* tp_methods */
    NULL,                               /* tp_members */
    pyWinAudible_GetSet,                /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyWinAudible_new,                   /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */

    NULL,                               /* tp_del */
    TP_VERSION_TAG_INIT                 /* tp_version_tag */
    TP_FINALIZE_INIT                    /* tp_finalize */
};

PyObject* Init_pyWinAudible_Type() {
    pyWinAudible_Type.tp_base = &pyAudible_Type;
    if (PyType_Ready(&pyWinAudible_Type) < 0)
        return NULL;

    Py_INCREF(&pyWinAudible_Type);
    return (PyObject*)&pyWinAudible_Type;
}

PY_PLASMA_IFC_METHODS(WinAudible, plWinAudible)

}
