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

#include <PRP/GUI/pfGUIDialogMod.h>
#include "pyGUIDialogMod.h"
#include "pyGUIControlMod.h"
#include "PRP/Modifier/pyModifier.h"
#include "PRP/KeyedObject/pyKey.h"

PY_PLASMA_NEW(GUIDialogMod, pfGUIDialogMod)

PY_METHOD_VA(GUIDialogMod, addControl,
    "Params: control\n"
    "Add a control to the dialog mod")
{
    pyKey* control;
    if (!PyArg_ParseTuple(args, "O", &control)) {
        PyErr_SetString(PyExc_TypeError, "addControl expects a plKey");
        return nullptr;
    }
    if (!pyKey_Check((PyObject*)control)) {
        PyErr_SetString(PyExc_TypeError, "addControl expects a plKey");
        return nullptr;
    }
    self->fThis->addControl(*control->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(GUIDialogMod, delControl,
    "Params: idx\n"
    "Remove a control from the dialog mod")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delControl expects an int");
        return nullptr;
    }
    self->fThis->delControl(idx);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(GUIDialogMod, clearControls,
    "Remove all controls from the dialog mod")
{
    self->fThis->clearControls();
    Py_RETURN_NONE;
}

static PyMethodDef pyGUIDialogMod_Methods[] = {
    pyGUIDialogMod_addControl_method,
    pyGUIDialogMod_delControl_method,
    pyGUIDialogMod_clearControls_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY(int, GUIDialogMod, tagID, getTagID, setTagID)
PY_PROPERTY(int, GUIDialogMod, version, getVersion, setVersion)
PY_PROPERTY(plKey, GUIDialogMod, renderMod, getRenderMod, setRenderMod)
PY_PROPERTY(ST::string, GUIDialogMod, name, getName, setName)
PY_PROPERTY(plKey, GUIDialogMod, procReceiver, getProcReceiver, setProcReceiver)
PY_PROPERTY(plKey, GUIDialogMod, sceneNode, getSceneNode, setSceneNode)
PY_PROPERTY_PROXY(pfGUIColorScheme, GUIDialogMod, colorScheme, getColorScheme)

PY_GETSET_GETTER_DECL(GUIDialogMod, controls)
{
    PyObject* list = PyTuple_New(self->fThis->getControls().size());
    for (size_t i = 0; i < self->fThis->getControls().size(); i++)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(self->fThis->getControls()[i]));
    return list;
}
PY_PROPERTY_SETTER_MSG(GUIDialogMod, controls, "To add controls, use addControl()")
PY_PROPERTY_GETSET_DECL(GUIDialogMod, controls)

static PyGetSetDef pyGUIDialogMod_GetSet[] = {
    pyGUIDialogMod_tagID_getset,
    pyGUIDialogMod_version_getset,
    pyGUIDialogMod_renderMod_getset,
    pyGUIDialogMod_name_getset,
    pyGUIDialogMod_procReceiver_getset,
    pyGUIDialogMod_sceneNode_getset,
    pyGUIDialogMod_colorScheme_getset,
    pyGUIDialogMod_controls_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(GUIDialogMod, pfGUIDialogMod, "pfGUIDialogMod wrapper")

PY_PLASMA_TYPE_INIT(GUIDialogMod)
{
    pyGUIDialogMod_Type.tp_new = pyGUIDialogMod_new;
    pyGUIDialogMod_Type.tp_methods = pyGUIDialogMod_Methods;
    pyGUIDialogMod_Type.tp_getset = pyGUIDialogMod_GetSet;
    pyGUIDialogMod_Type.tp_base = &pySingleModifier_Type;
    if (PyType_CheckAndReady(&pyGUIDialogMod_Type) < 0)
        return nullptr;

    Py_INCREF(&pyGUIDialogMod_Type);
    return (PyObject*) &pyGUIDialogMod_Type;
}

PY_PLASMA_IFC_METHODS(GUIDialogMod, pfGUIDialogMod)
