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

#include <PRP/GUI/pfGUIListBoxMod.h>
#include "pyGUIListBoxMod.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/GUI/pyGUIControlMod.h"

/* pyGUIListElement */
PY_PLASMA_VALUE_NEW(GUIListElement, pfGUIListElement)

PY_PROPERTY(bool, GUIListElement, selected, isSelected, setSelected)

static PyGetSetDef pyGUIListElement_GetSet[] = {
    pyGUIListElement_selected_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(GUIListElement, pfGUIListElement, "pfGUIListElement wrapper")

PY_PLASMA_TYPE_INIT(GUIListElement)
{
    pyGUIListElement_Type.tp_new = pyGUIListElement_new;
    pyGUIListElement_Type.tp_getset = pyGUIListElement_GetSet;
    if (PyType_CheckAndReady(&pyGUIListElement_Type) < 0)
        return nullptr;

    /* Konstants */
    PY_TYPE_ADD_CONST(GUIListElement, "kText", pfGUIListElement::kText);
    PY_TYPE_ADD_CONST(GUIListElement, "kPicture", pfGUIListElement::kPicture);
    PY_TYPE_ADD_CONST(GUIListElement, "kTreeRoot", pfGUIListElement::kTreeRoot);

    Py_INCREF(&pyGUIListElement_Type);
    return (PyObject*)&pyGUIListElement_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(GUIListElement, pfGUIListElement)


/* pyGUIListBoxMod */
PY_PLASMA_NEW(GUIListBoxMod, pfGUIListBoxMod)

PY_PROPERTY(plKey, GUIListBoxMod, scrollCtrl, getScrollCtrl, setScrollCtrl)

static PyGetSetDef pyGUIListBoxMod_GetSet[] = {
    pyGUIListBoxMod_scrollCtrl_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(GUIListBoxMod, pfGUIListBoxMod, "pfGUIListBoxMod wrapper")

PY_PLASMA_TYPE_INIT(GUIListBoxMod)
{
    pyGUIListBoxMod_Type.tp_new = pyGUIListBoxMod_new;
    pyGUIListBoxMod_Type.tp_getset = pyGUIListBoxMod_GetSet;
    pyGUIListBoxMod_Type.tp_base = &pyGUIControlMod_Type;
    if (PyType_CheckAndReady(&pyGUIListBoxMod_Type) < 0)
        return nullptr;

    /* Konstants */
    PY_TYPE_ADD_CONST(GUIListBoxMod, "kSingleSelect", pfGUIListBoxMod::kSingleSelect);
    PY_TYPE_ADD_CONST(GUIListBoxMod, "kDragAndDropCapable", pfGUIListBoxMod::kDragAndDropCapable);
    PY_TYPE_ADD_CONST(GUIListBoxMod, "kDisableSelection", pfGUIListBoxMod::kDisableSelection);
    PY_TYPE_ADD_CONST(GUIListBoxMod, "kDisableKeyActions", pfGUIListBoxMod::kDisableKeyActions);
    PY_TYPE_ADD_CONST(GUIListBoxMod, "kAllowMultipleElementsPerRow", pfGUIListBoxMod::kAllowMultipleElementsPerRow);
    PY_TYPE_ADD_CONST(GUIListBoxMod, "kScrollLeftToRight", pfGUIListBoxMod::kScrollLeftToRight);
    PY_TYPE_ADD_CONST(GUIListBoxMod, "kAllowMousePassThrough", pfGUIListBoxMod::kAllowMousePassThrough);
    PY_TYPE_ADD_CONST(GUIListBoxMod, "kGrowLeavesAndProcessOxygen", pfGUIListBoxMod::kGrowLeavesAndProcessOxygen);
    PY_TYPE_ADD_CONST(GUIListBoxMod, "kHandsOffMultiSelect", pfGUIListBoxMod::kHandsOffMultiSelect);
    PY_TYPE_ADD_CONST(GUIListBoxMod, "kForbidNoSelection", pfGUIListBoxMod::kForbidNoSelection);

    Py_INCREF(&pyGUIListBoxMod_Type);
    return (PyObject*)&pyGUIListBoxMod_Type;
}

PY_PLASMA_IFC_METHODS(GUIListBoxMod, pfGUIListBoxMod)
