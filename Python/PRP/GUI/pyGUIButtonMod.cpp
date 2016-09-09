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
#include <PRP/GUI/pfGUIButtonMod.h>
#include "pyGUIButtonMod.h"
#include "PRP/KeyedObject/pyKey.h"

extern "C" {

PY_PLASMA_NEW(GUIButtonMod, pfGUIButtonMod)

static PyObject* pyGUIButtonMod_addAnim(pyGUIButtonMod* self, PyObject* args) {
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addAnim expects a plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addAnim expects a plKey");
        return NULL;
    }
    self->fThis->addAnimationKey(*key->fThis);
    Py_RETURN_NONE;
}

static PyObject* pyGUIButtonMod_delAnim(pyGUIButtonMod* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delAnim expects an int");
        return NULL;
    }
    self->fThis->delAnimationKey(idx);
    Py_RETURN_NONE;
}

static PyObject* pyGUIButtonMod_clearAnims(pyGUIButtonMod* self) {
    self->fThis->clearAnimationKeys();
    Py_RETURN_NONE;
}

static PyObject* pyGUIButtonMod_addMouseOver(pyGUIButtonMod* self, PyObject* args) {
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addMouseOver expects a plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addMouseOver expects a plKey");
        return NULL;
    }
    self->fThis->addMouseOverKey(*key->fThis);
    Py_RETURN_NONE;
}

static PyObject* pyGUIButtonMod_delMouseOver(pyGUIButtonMod* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delMouseOver expects an int");
        return NULL;
    }
    self->fThis->delMouseOverKey(idx);
    Py_RETURN_NONE;
}

static PyObject* pyGUIButtonMod_clearMouseOvers(pyGUIButtonMod* self) {
    self->fThis->clearMouseOverKeys();
    Py_RETURN_NONE;
}

static PyObject* pyGUIButtonMod_getAnimationKeys(pyGUIButtonMod* self, void*) {
    PyObject* list = PyTuple_New(self->fThis->getAnimationKeys().size());
    for (size_t i = 0; i<self->fThis->getAnimationKeys().size(); i++)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(self->fThis->getAnimationKeys()[i]));
    return list;
}

static PyObject* pyGUIButtonMod_getMouseOverKeys(pyGUIButtonMod* self, void*) {
    PyObject* list = PyTuple_New(self->fThis->getMouseOverKeys().size());
    for (size_t i = 0; i<self->fThis->getMouseOverKeys().size(); i++)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(self->fThis->getMouseOverKeys()[i]));
    return list;
}

static int pyGUIButtonMod_setAnimationKeys(pyGUIButtonMod* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add animations, use addAnim()");
    return -1;
}

static int pyGUIButtonMod_setMouseOverKeys(pyGUIButtonMod* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add mouse-over animations, use addMouseOver()");
    return -1;
}

static PyMethodDef pyGUIButtonMod_Methods[] = {
    { "addAnim", (PyCFunction)pyGUIButtonMod_addAnim, METH_VARARGS,
    "Params: key\n"
    "Add an animation to the button" },
    { "delAnim", (PyCFunction)pyGUIButtonMod_delAnim, METH_VARARGS,
    "Params: idx\n"
    "Remove an animation from the button" },
    { "clearAnims", (PyCFunction)pyGUIButtonMod_clearAnims, METH_NOARGS,
    "Remove all animation keys from the button" },
    { "addMouseOver", (PyCFunction)pyGUIButtonMod_addMouseOver, METH_VARARGS,
    "Params: key\n"
    "Add a mouse-over animation to the button" },
    { "delMouseOver", (PyCFunction)pyGUIButtonMod_delMouseOver, METH_VARARGS,
    "Params: idx\n"
    "Remove a mouse-over animation from the button" },
    { "clearMouseOver", (PyCFunction)pyGUIButtonMod_clearMouseOvers, METH_NOARGS,
    "Remove all mouse-over animation keys from the button" },
    { NULL, NULL, 0, NULL }
};

PY_PROPERTY(plString, GUIButtonMod, animName, getAnimationName, setAnimationName)
PY_PROPERTY(plString, GUIButtonMod, mouseOverAnimName, getMouseOverAnimName, setMouseOverAnimName)
PY_PROPERTY(plKey, GUIButtonMod, draggable, getDraggable, setDraggable)
PY_PROPERTY(int, GUIButtonMod, notifyType, getNotifyType, setNotifyType)

static PyGetSetDef pyGUIButtonMod_GetSet[] = {
    pyGUIButtonMod_animName_getset,
    pyGUIButtonMod_mouseOverAnimName_getset,
    pyGUIButtonMod_draggable_getset,
    pyGUIButtonMod_notifyType_getset,
    { _pycs("animationKeys"), (getter)pyGUIButtonMod_getAnimationKeys, (setter)pyGUIButtonMod_setAnimationKeys, NULL, NULL },
    { _pycs("mouseOverKeys"), (getter)pyGUIButtonMod_getMouseOverKeys, (setter)pyGUIButtonMod_setMouseOverKeys, NULL, NULL },
    PY_GETSET_TERMINATOR
};

PyTypeObject pyGUIButtonMod_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.pfGUIButtonMod",        /* tp_name */
    sizeof(pyGUIButtonMod),             /* tp_basicsize */
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
    "pfGUIButtonMod wrapper",           /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyGUIButtonMod_Methods,             /* tp_methods */
    NULL,                               /* tp_members */
    pyGUIButtonMod_GetSet,              /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyGUIButtonMod_new,                 /* tp_new */
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

PyObject* Init_pyGUIButtonMod_Type() {
    if (PyType_Ready(&pyGUIButtonMod_Type) < 0)
        return NULL;

    /* Konstants */
    PyDict_SetItemString(pyGUIButtonMod_Type.tp_dict,
        "kNotifyOnUp", pyPlasma_convert(pfGUIButtonMod::kNotifyOnUp));
    PyDict_SetItemString(pyGUIButtonMod_Type.tp_dict,
        "kNotifyOnDown", pyPlasma_convert(pfGUIButtonMod::kNotifyOnDown));
    PyDict_SetItemString(pyGUIButtonMod_Type.tp_dict,
        "kNotifyOnUpAndDown", pyPlasma_convert(pfGUIButtonMod::kNotifyOnUpAndDown));

    Py_INCREF(&pyGUIButtonMod_Type);
    return (PyObject*)&pyGUIButtonMod_Type;
}

PY_PLASMA_IFC_METHODS(GUIButtonMod, pfGUIButtonMod)

}