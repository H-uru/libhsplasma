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

PY_PLASMA_NEW(GUIKnobCtrl, pfGUIKnobCtrl)

PY_METHOD_VA(GUIKnobCtrl, addAnimationKey,
    "Params: animation key\n"
    "Add an animation to the knob")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addAnimationKey expects a plKey");
        return nullptr;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addAnimationKey expects a plKey");
        return nullptr;
    }
    self->fThis->addAnimationKey(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(GUIKnobCtrl, delAnimationKey,
    "Params: idx\n"
    "Remove an animation from the knob")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delAnimationKey expects an int");
        return nullptr;
    }
    self->fThis->delAnimationKey(idx);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(GUIKnobCtrl, clearAnimationKeys,
    "Remove all animation keys from the knob")
{
    self->fThis->clearAnimationKeys();
    Py_RETURN_NONE;
}

static PyMethodDef pyGUIKnobCtrl_Methods[] = {
    pyGUIKnobCtrl_addAnimationKey_method,
    pyGUIKnobCtrl_delAnimationKey_method,
    pyGUIKnobCtrl_clearAnimationKeys_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(GUIKnobCtrl, animationKeys)
{
    PyObject* list = PyTuple_New(self->fThis->getAnimationKeys().size());
    for (size_t i = 0; i<self->fThis->getAnimationKeys().size(); i++)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(self->fThis->getAnimationKeys()[i]));
    return list;
}
PY_PROPERTY_SETTER_MSG(GUIKnobCtrl, animationKeys, "To add animations, use addAnimationKey()")
PY_PROPERTY_GETSET_DECL(GUIKnobCtrl, animationKeys)

PY_PROPERTY(ST::string, GUIKnobCtrl, animName, getAnimName, setAnimName)
PY_PROPERTY(hsVector3, GUIKnobCtrl, animStartPos, getAnimStartPos, setAnimStartPos)
PY_PROPERTY(hsVector3, GUIKnobCtrl, animEndPos, getAnimEndPos, setAnimEndPos)

static PyGetSetDef pyGUIKnobCtrl_GetSet[] = {
    pyGUIKnobCtrl_animName_getset,
    pyGUIKnobCtrl_animStartPos_getset,
    pyGUIKnobCtrl_animEndPos_getset,
    pyGUIKnobCtrl_animationKeys_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(GUIKnobCtrl, pfGUIKnobCtrl, "pfGUIKnobCtrl wrapper")

PY_PLASMA_TYPE_INIT(GUIKnobCtrl)
{
    pyGUIKnobCtrl_Type.tp_new = pyGUIKnobCtrl_new;
    pyGUIKnobCtrl_Type.tp_methods = pyGUIKnobCtrl_Methods;
    pyGUIKnobCtrl_Type.tp_getset = pyGUIKnobCtrl_GetSet;
    pyGUIKnobCtrl_Type.tp_base = &pyGUIValueCtrl_Type;
    if (PyType_CheckAndReady(&pyGUIKnobCtrl_Type) < 0)
        return nullptr;

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
