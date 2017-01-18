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

#include <PRP/GUI/pfGUIProgressCtrl.h>
#include "pyGUIProgressCtrl.h"
#include "PRP/GUI/pyGUIValueCtrl.h"
#include "PRP/KeyedObject/pyKey.h"

extern "C" {

PY_PLASMA_NEW(GUIProgressCtrl, pfGUIProgressCtrl)

PY_METHOD_VA(GUIProgressCtrl, addAnim,
    "Params: animation key\n"
    "Add an animation to the progress control")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addAnim expects a plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addAnim expects a plKey");
        return NULL;
    }
    self->fThis->addAnimKey(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(GUIProgressCtrl, delAnim,
    "Params: idx\n"
    "Remove an animation from the progress control")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delAnim expects an int");
        return NULL;
    }
    self->fThis->delAnimKey(idx);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(GUIProgressCtrl, clearAnims,
    "Remove all animation keys from the progress control")
{
    self->fThis->clearAnimKeys();
    Py_RETURN_NONE;
}

static PyMethodDef pyGUIProgressCtrl_Methods[] = {
    pyGUIProgressCtrl_addAnim_method,
    pyGUIProgressCtrl_delAnim_method,
    pyGUIProgressCtrl_clearAnims_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(GUIProgressCtrl, animationKeys) {
    PyObject* list = PyTuple_New(self->fThis->getAnimKeys().size());
    for (size_t i = 0; i<self->fThis->getAnimKeys().size(); i++)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(self->fThis->getAnimKeys()[i]));
    return list;
}

PY_PROPERTY_SETTER_MSG(GUIProgressCtrl, animationKeys, "To add animations, use addAnim()")
PY_PROPERTY_GETSET_DECL(GUIProgressCtrl, animationKeys)

PY_PROPERTY(ST::string, GUIProgressCtrl, animName, getAnimName, setAnimName)

static PyGetSetDef pyGUIProgressCtrl_GetSet[] = {
    pyGUIProgressCtrl_animName_getset,
    pyGUIProgressCtrl_animationKeys_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(GUIProgressCtrl, pfGUIProgressCtrl, "pfGUIProgressCtrl wrapper");

PY_PLASMA_TYPE_INIT(GUIProgressCtrl) {
    pyGUIProgressCtrl_Type.tp_new = pyGUIProgressCtrl_new;
    pyGUIProgressCtrl_Type.tp_getset = pyGUIProgressCtrl_GetSet;
    pyGUIProgressCtrl_Type.tp_methods = pyGUIProgressCtrl_Methods;
    pyGUIProgressCtrl_Type.tp_base = &pyGUIValueCtrl_Type;
    if (PyType_Ready(&pyGUIProgressCtrl_Type) < 0)
        return NULL;

    /* Konstants */
    PY_TYPE_ADD_CONST(GUIProgressCtrl, "kReverseValues", pfGUIProgressCtrl::kReverseValues);
    PY_TYPE_ADD_CONST(GUIProgressCtrl, "kLeftRightOrientation", pfGUIProgressCtrl::kLeftRightOrientation);
    PY_TYPE_ADD_CONST(GUIProgressCtrl, "kMapToScreenRange", pfGUIProgressCtrl::kMapToScreenRange);
    PY_TYPE_ADD_CONST(GUIProgressCtrl, "kTriggerOnlyOnMouseUp", pfGUIProgressCtrl::kTriggerOnlyOnMouseUp);
    PY_TYPE_ADD_CONST(GUIProgressCtrl, "kMapToAnimationRange", pfGUIProgressCtrl::kMapToAnimationRange);

    Py_INCREF(&pyGUIProgressCtrl_Type);
    return (PyObject*)&pyGUIProgressCtrl_Type;
}

PY_PLASMA_IFC_METHODS(GUIProgressCtrl, pfGUIProgressCtrl)

}
