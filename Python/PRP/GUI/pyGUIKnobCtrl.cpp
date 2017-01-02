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

#include <PRP/GUI/pfGUIKnobCtrl.h>
#include "pyGUIKnobCtrl.h"
#include "pyGUIValueCtrl.h"
#include "PRP/KeyedObject/pyKey.h"
#include "Math/pyGeometry3.h"

extern "C" {

PY_PLASMA_NEW(GUIKnobCtrl, pfGUIKnobCtrl)

static PyObject* pyGUIKnobCtrl_addAnim(pyGUIKnobCtrl* self, PyObject* args) {
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

static PyObject* pyGUIKnobCtrl_delAnim(pyGUIKnobCtrl* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delAnim expects an int");
        return NULL;
    }
    self->fThis->delAnimationKey(idx);
    Py_RETURN_NONE;
}

static PyObject* pyGUIKnobCtrl_clearAnims(pyGUIKnobCtrl* self) {
    self->fThis->clearAnimationKeys();
    Py_RETURN_NONE;
}

static PyObject* pyGUIKnobCtrl_getAnimationKeys(pyGUIKnobCtrl* self, void*) {
    PyObject* list = PyTuple_New(self->fThis->getAnimationKeys().size());
    for (size_t i = 0; i<self->fThis->getAnimationKeys().size(); i++)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(self->fThis->getAnimationKeys()[i]));
    return list;
}

static int pyGUIKnobCtrl_setAnimationKeys(pyGUIKnobCtrl* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add animations, use addAnim()");
    return -1;
}

static PyMethodDef pyGUIKnobCtrl_Methods[] = {
    { "addAnim", (PyCFunction)pyGUIKnobCtrl_addAnim, METH_VARARGS,
    "Params: key\n"
    "Add an animation to the knob" },
    { "delAnim", (PyCFunction)pyGUIKnobCtrl_delAnim, METH_VARARGS,
    "Params: idx\n"
    "Remove an animation from the knob" },
    { "clearAnims", (PyCFunction)pyGUIKnobCtrl_clearAnims, METH_NOARGS,
    "Remove all animation keys from the knob" },
    { NULL, NULL, 0, NULL }
};

PY_PROPERTY(ST::string, GUIKnobCtrl, animName, getAnimName, setAnimName)
PY_PROPERTY(hsVector3, GUIKnobCtrl, animStartPos, getAnimStartPos, setAnimStartPos)
PY_PROPERTY(hsVector3, GUIKnobCtrl, animEndPos, getAnimEndPos, setAnimEndPos)

static PyGetSetDef pyGUIKnobCtrl_GetSet[] = {
    pyGUIKnobCtrl_animName_getset,
    pyGUIKnobCtrl_animStartPos_getset,
    pyGUIKnobCtrl_animEndPos_getset,
    { _pycs("animationKeys"), (getter)pyGUIKnobCtrl_getAnimationKeys, (setter)pyGUIKnobCtrl_setAnimationKeys, NULL, NULL },
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(GUIKnobCtrl, pfGUIKnobCtrl, "pfGUIKnobCtrl wrapper");

PY_PLASMA_TYPE_INIT(GUIKnobCtrl) {
    pyGUIKnobCtrl_Type.tp_new = pyGUIKnobCtrl_new;
    pyGUIKnobCtrl_Type.tp_getset = pyGUIKnobCtrl_GetSet;
    pyGUIKnobCtrl_Type.tp_base = &pyGUIValueCtrl_Type;
    if (PyType_Ready(&pyGUIKnobCtrl_Type) < 0)
        return NULL;

    /* Konstants */
    PY_TYPE_ADD_CONST(GUIKnobCtrl, "kReverseValues", pfGUIKnobCtrl::kReverseValues);
    PY_TYPE_ADD_CONST(GUIKnobCtrl, "kLeftRightOrientation", pfGUIKnobCtrl::kLeftRightOrientation);
    PY_TYPE_ADD_CONST(GUIKnobCtrl, "kMapToScreenRange", pfGUIKnobCtrl::kMapToScreenRange);
    PY_TYPE_ADD_CONST(GUIKnobCtrl, "kTriggerOnlyOnMouseUp", pfGUIKnobCtrl::kTriggerOnlyOnMouseUp);
    PY_TYPE_ADD_CONST(GUIKnobCtrl, "kMapToAnimationRange", pfGUIKnobCtrl::kMapToAnimationRange);

    Py_INCREF(&pyGUIKnobCtrl_Type);
    return (PyObject*)&pyGUIKnobCtrl_Type;
}

PY_PLASMA_IFC_METHODS(GUIKnobCtrl, pfGUIKnobCtrl)

}