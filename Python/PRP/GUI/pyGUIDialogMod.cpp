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
#include <PRP/GUI/pfGUIDialogMod.h>
#include "pyGUIDialogMod.h"
#include "PRP/KeyedObject/pyKey.h"

extern "C" {

PY_PLASMA_NEW(GUIDialogMod, pfGUIDialogMod)

static PyObject* pyGUIDialogMod_addControl(pyGUIDialogMod* self, PyObject* args) {
    pyKey* ctrl;
    if (!PyArg_ParseTuple(args, "O", &ctrl)) {
        PyErr_SetString(PyExc_TypeError, "addControl expects a plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)ctrl)) {
        PyErr_SetString(PyExc_TypeError, "addControl expects a plKey");
        return NULL;
    }
    self->fThis->addControl(*ctrl->fThis);
    Py_RETURN_NONE;
}

static PyObject* pyGUIDialogMod_delControl(pyGUIDialogMod* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delControl expects an int");
        return NULL;
    }
    self->fThis->delControl(idx);
    Py_RETURN_NONE;
}

static PyObject* pyGUIDialogMod_clearControls(pyGUIDialogMod* self) {
    self->fThis->clearControls();
    Py_RETURN_NONE;
}

static PyObject* pyGUIDialogMod_getControls(pyGUIDialogMod* self, void*) {
    PyObject* list = PyTuple_New(self->fThis->getControls().size());
    for (size_t i = 0; i < self->fThis->getControls().size(); i++)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(self->fThis->getControls()[i]));
    return list;
}

static int pyGUIDialogMod_setControls(pyGUIDialogMod* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add controls, use addControl()");
    return -1;
}

static PyMethodDef pyGUIDialogMod_Methods[] = {
    { "addControl", (PyCFunction)pyGUIDialogMod_addControl, METH_VARARGS,
    "Params: stage\n"
    "Add a GUIControl to the dialog mod" },
    { "delControl", (PyCFunction)pyGUIDialogMod_delControl, METH_VARARGS,
    "Params: idx\n"
    "Remove a control from the dialog mod" },
    { "clearControls", (PyCFunction)pyGUIDialogMod_clearControls, METH_NOARGS,
    "Remove all controls from the dialog mod" },
    { NULL, NULL, NULL, NULL }
};

PY_PROPERTY(int, GUIDialogMod, tagID, getTagID, setTagID)
PY_PROPERTY(int, GUIDialogMod, version, getVersion, setVersion)
PY_PROPERTY(plKey, GUIDialogMod, renderMod, getRenderMod, setRenderMod)
PY_PROPERTY(plString, GUIDialogMod, name, getName, setName)
PY_PROPERTY(plKey, GUIDialogMod, procReceiver, getProcReceiver, setProcReceiver)
PY_PROPERTY(plKey, GUIDialogMod, sceneNode, getSceneNode, setSceneNode)

static PyGetSetDef pyGUIDialogMod_GetSet[] = {
    pyGUIDialogMod_tagID_getset,
    pyGUIDialogMod_version_getset,
    pyGUIDialogMod_renderMod_getset,
    pyGUIDialogMod_name_getset,
    pyGUIDialogMod_procReceiver_getset,
    pyGUIDialogMod_sceneNode_getset,
    { _pycs("controls"), (getter)pyGUIDialogMod_getControls, (setter)pyGUIDialogMod_setControls, NULL, NULL },
    PY_GETSET_TERMINATOR
};

PyTypeObject pyGUIDialogMod_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.pfGUIDialogMod",        /* tp_name */
    sizeof(pyGUIDialogMod),             /* tp_basicsize */
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
    "pfGUIDialogMod wrapper",           /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyGUIDialogMod_Methods,             /* tp_methods */
    NULL,                               /* tp_members */
    pyGUIDialogMod_GetSet,              /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyGUIDialogMod_new,                 /* tp_new */
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

PyObject* Init_pyGUIDialogMod_Type() {
    if (PyType_Ready(&pyGUIDialogMod_Type) < 0)
        return NULL;

    Py_INCREF(&pyGUIDialogMod_Type);
    return (PyObject*) &pyGUIDialogMod_Type;
}

PY_PLASMA_IFC_METHODS(GUIDialogMod, pfGUIDialogMod)

}