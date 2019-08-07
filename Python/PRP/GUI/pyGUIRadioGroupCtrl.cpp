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

#include <PRP/GUI/pfGUIRadioGroupCtrl.h>
#include "pyGUIRadioGroupCtrl.h"
#include "PRP/GUI/pyGUIControlMod.h"
#include "PRP/KeyedObject/pyKey.h"

PY_PLASMA_NEW(GUIRadioGroupCtrl, pfGUIRadioGroupCtrl)

PY_METHOD_VA(GUIRadioGroupCtrl, addControl,
    "Params: animation key\n"
    "Add a control to the radio group")
{
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addControl expects a plKey");
        return nullptr;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addControl expects a plKey");
        return nullptr;
    }
    self->fThis->addControl(*key->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(GUIRadioGroupCtrl, delControl,
    "Params: idx\n"
    "Remove a control from the radio group")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delControl expects an int");
        return nullptr;
    }
    self->fThis->delControl(idx);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(GUIRadioGroupCtrl, clearControls,
    "Remove all controls from the radio group")
{
    self->fThis->clearControls();
    Py_RETURN_NONE;
}

static PyMethodDef pyGUIRadioGroupCtrl_Methods[] = {
    pyGUIRadioGroupCtrl_addControl_method,
    pyGUIRadioGroupCtrl_delControl_method,
    pyGUIRadioGroupCtrl_clearControls_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(GUIRadioGroupCtrl, controls)
{
    PyObject* list = PyTuple_New(self->fThis->getControls().size());
    for (size_t i = 0; i<self->fThis->getControls().size(); i++)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(self->fThis->getControls()[i]));
    return list;
}

PY_PROPERTY_SETTER_MSG(GUIRadioGroupCtrl, controls, "To add controls, use addControl()")
PY_PROPERTY_GETSET_DECL(GUIRadioGroupCtrl, controls)

PY_PROPERTY(int, GUIRadioGroupCtrl, defaultValue, getDefaultValue, setDefaultValue)

static PyGetSetDef pyGUIRadioGroupCtrl_GetSet[] = {
    pyGUIRadioGroupCtrl_controls_getset,
    pyGUIRadioGroupCtrl_defaultValue_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(GUIRadioGroupCtrl, pfGUIRadioGroupCtrl, "pfGUIRadioGroupCtrl wrapper")

PY_PLASMA_TYPE_INIT(GUIRadioGroupCtrl)
{
    pyGUIRadioGroupCtrl_Type.tp_new = pyGUIRadioGroupCtrl_new;
    pyGUIRadioGroupCtrl_Type.tp_methods = pyGUIRadioGroupCtrl_Methods;
    pyGUIRadioGroupCtrl_Type.tp_getset = pyGUIRadioGroupCtrl_GetSet;
    pyGUIRadioGroupCtrl_Type.tp_base = &pyGUIControlMod_Type;
    if (PyType_CheckAndReady(&pyGUIRadioGroupCtrl_Type) < 0)
        return nullptr;

    /* Konstants */
    PY_TYPE_ADD_CONST(GUIRadioGroupCtrl, "kAllowNoSelection", pfGUIRadioGroupCtrl::kAllowNoSelection);

    Py_INCREF(&pyGUIRadioGroupCtrl_Type);
    return (PyObject*)&pyGUIRadioGroupCtrl_Type;
}

PY_PLASMA_IFC_METHODS(GUIRadioGroupCtrl, pfGUIRadioGroupCtrl)
