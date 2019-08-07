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

#include <PRP/GUI/pfGUIPopUpMenu.h>
#include "pyGUIPopUpMenu.h"
#include "PRP/GUI/pyGUIDialogMod.h"
#include "PRP/KeyedObject/pyKey.h"

PY_PLASMA_NEW(GUIPopUpMenu, pfGUIPopUpMenu)

PY_PROPERTY(unsigned short, GUIPopUpMenu, margin, getMargin, setMargin)
PY_PROPERTY(plKey, GUIPopUpMenu, skin, getSkin, setSkin)
PY_PROPERTY(plKey, GUIPopUpMenu, originContext, getOriginContext, setOriginContext)
PY_PROPERTY(plKey, GUIPopUpMenu, originAnchor, getOriginAnchor, setOriginAnchor)
PY_PROPERTY(pfGUIPopUpMenu::Alignment, GUIPopUpMenu, alignment, getAlignment, setAlignment)

static PyGetSetDef pyGUIPopUpMenu_GetSet[] = {
    pyGUIPopUpMenu_margin_getset,
    pyGUIPopUpMenu_skin_getset,
    pyGUIPopUpMenu_originContext_getset,
    pyGUIPopUpMenu_originAnchor_getset,
    pyGUIPopUpMenu_alignment_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(GUIPopUpMenu, pfGUIPopUpMenu, "pfGUIPopUpMenu wrapper")

PY_PLASMA_TYPE_INIT(GUIPopUpMenu)
{
    pyGUIPopUpMenu_Type.tp_new = pyGUIPopUpMenu_new;
    pyGUIPopUpMenu_Type.tp_getset = pyGUIPopUpMenu_GetSet;
    pyGUIPopUpMenu_Type.tp_base = &pyGUIDialogMod_Type;
    if (PyType_CheckAndReady(&pyGUIPopUpMenu_Type) < 0)
        return nullptr;

    /* Konstants */
    PY_TYPE_ADD_CONST(GUIPopUpMenu, "kAlignUpLeft", pfGUIPopUpMenu::kAlignUpLeft);
    PY_TYPE_ADD_CONST(GUIPopUpMenu, "kAlignUpRight", pfGUIPopUpMenu::kAlignUpRight);
    PY_TYPE_ADD_CONST(GUIPopUpMenu, "kAlignDownLeft", pfGUIPopUpMenu::kAlignDownLeft);
    PY_TYPE_ADD_CONST(GUIPopUpMenu, "kAlignDownRight", pfGUIPopUpMenu::kAlignDownRight);

    PY_TYPE_ADD_CONST(GUIPopUpMenu, "kStayOpenAfterClick", pfGUIPopUpMenu::kStayOpenAfterClick);
    PY_TYPE_ADD_CONST(GUIPopUpMenu, "kModalOutsideMenus", pfGUIPopUpMenu::kModalOutsideMenus);
    PY_TYPE_ADD_CONST(GUIPopUpMenu, "kOpenSubMenusOnHover", pfGUIPopUpMenu::kOpenSubMenusOnHover);
    PY_TYPE_ADD_CONST(GUIPopUpMenu, "kScaleWithResolution", pfGUIPopUpMenu::kScaleWithResolution);
    
    Py_INCREF(&pyGUIPopUpMenu_Type);
    return (PyObject*)&pyGUIPopUpMenu_Type;
}

PY_PLASMA_IFC_METHODS(GUIPopUpMenu, pfGUIPopUpMenu)
