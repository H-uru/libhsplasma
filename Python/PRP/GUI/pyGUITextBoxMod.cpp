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

#include <PRP/GUI/pfGUITextBoxMod.h>
#include "pyGUITextBoxMod.h"
#include "PRP/GUI/pyGUIControlMod.h"

PY_PLASMA_NEW(GUITextBoxMod, pfGUITextBoxMod)

PY_PROPERTY(ST::string, GUITextBoxMod, text, getText, setText)
PY_PROPERTY(ST::string, GUITextBoxMod, localizationPath, getLocalizationPath, setLocalizationPath)

static PyGetSetDef pyGUITextBoxMod_GetSet[] = {
    pyGUITextBoxMod_text_getset,
    pyGUITextBoxMod_localizationPath_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(GUITextBoxMod, pfGUITextBoxMod, "pfGUITextBoxMod wrapper")

PY_PLASMA_TYPE_INIT(GUITextBoxMod)
{
    pyGUITextBoxMod_Type.tp_new = pyGUITextBoxMod_new;
    pyGUITextBoxMod_Type.tp_getset = pyGUITextBoxMod_GetSet;
    pyGUITextBoxMod_Type.tp_base = &pyGUIControlMod_Type;
    if (PyType_CheckAndReady(&pyGUITextBoxMod_Type) < 0)
        return nullptr;

    /* Konstants */
    PY_TYPE_ADD_CONST(GUITextBoxMod, "kCenterJustify", pfGUITextBoxMod::kCenterJustify);
    PY_TYPE_ADD_CONST(GUITextBoxMod, "kRightJustify", pfGUITextBoxMod::kRightJustify);

    Py_INCREF(&pyGUITextBoxMod_Type);
    return (PyObject*)&pyGUITextBoxMod_Type;
}

PY_PLASMA_IFC_METHODS(GUITextBoxMod, pfGUITextBoxMod)
