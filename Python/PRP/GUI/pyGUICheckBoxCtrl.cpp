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

#include <PRP/GUI/pfGUICheckBoxCtrl.h>
#include "pyGUICheckBoxCtrl.h"
#include "PRP/GUI/pyGUIControlMod.h"
#include "PRP/KeyedObject/pyKey.h"

PY_PLASMA_NEW(GUICheckBoxCtrl, pfGUICheckBoxCtrl)

PY_METHOD_VA(GUICheckBoxCtrl, addAnimKey,
    "Params: animation key\n"
    "Add an animation to the checkbox control")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addAnimKey expects a plKey");
        return nullptr;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addAnimKey expects a plKey");
        return nullptr;
    }
    self->fThis->addAnimKey(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(GUICheckBoxCtrl, delAnimKey,
    "Params: idx\n"
    "Remove an animation from the checkbox control")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delAnimKey expects an int");
        return nullptr;
    }
    self->fThis->delAnimKey(idx);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(GUICheckBoxCtrl, clearAnimKeys,
    "Remove all animation keys from the checkbox control")
{
    self->fThis->clearAnimKeys();
    Py_RETURN_NONE;
}

static PyMethodDef pyGUICheckBoxCtrl_Methods[] = {
    pyGUICheckBoxCtrl_addAnimKey_method,
    pyGUICheckBoxCtrl_delAnimKey_method,
    pyGUICheckBoxCtrl_clearAnimKeys_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(GUICheckBoxCtrl, animKeys)
{
    PyObject* list = PyTuple_New(self->fThis->getAnimKeys().size());
    for (size_t i = 0; i<self->fThis->getAnimKeys().size(); i++)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(self->fThis->getAnimKeys()[i]));
    return list;
}
PY_PROPERTY_SETTER_MSG(GUICheckBoxCtrl, animKeys, "To add animations, use addAnimKey()")
PY_PROPERTY_GETSET_DECL(GUICheckBoxCtrl, animKeys)

PY_PROPERTY(ST::string, GUICheckBoxCtrl, animName, getAnimName, setAnimName)
PY_PROPERTY(bool, GUICheckBoxCtrl, checked, isChecked, setChecked)

static PyGetSetDef pyGUICheckBoxCtrl_GetSet[] = {
    pyGUICheckBoxCtrl_animName_getset,
    pyGUICheckBoxCtrl_checked_getset,
    pyGUICheckBoxCtrl_animKeys_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(GUICheckBoxCtrl, pfGUICheckBoxCtrl, "pfGUICheckBoxCtrl wrapper")

PY_PLASMA_TYPE_INIT(GUICheckBoxCtrl)
{
    pyGUICheckBoxCtrl_Type.tp_new = pyGUICheckBoxCtrl_new;
    pyGUICheckBoxCtrl_Type.tp_methods = pyGUICheckBoxCtrl_Methods;
    pyGUICheckBoxCtrl_Type.tp_getset = pyGUICheckBoxCtrl_GetSet;
    pyGUICheckBoxCtrl_Type.tp_base = &pyGUIControlMod_Type;
    if (PyType_CheckAndReady(&pyGUICheckBoxCtrl_Type) < 0)
        return nullptr;

    Py_INCREF(&pyGUICheckBoxCtrl_Type);
    return (PyObject*)&pyGUICheckBoxCtrl_Type;
}

PY_PLASMA_IFC_METHODS(GUICheckBoxCtrl, pfGUICheckBoxCtrl)
