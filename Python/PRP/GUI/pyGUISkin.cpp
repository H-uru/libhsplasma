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

#include <PRP/GUI/pfGUISkin.h>
#include "pyGUISkin.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/KeyedObject/pyKeyedObject.h"

PY_PLASMA_NEW(GUISkin, pfGUISkin)

PY_PROPERTY(plKey, GUISkin, texture, getTexture, setTexture)
PY_PROPERTY(unsigned short, GUISkin, itemMargin, getItemMargin, setItemMargin)
PY_PROPERTY(unsigned short, GUISkin, borderMargin, getBorderMargin, setBorderMargin)

static PyGetSetDef pyGUISkin_GetSet[] = {
    pyGUISkin_texture_getset,
    pyGUISkin_itemMargin_getset,
    pyGUISkin_borderMargin_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(GUISkin, pfGUISkin, "pfGUISkin wrapper")

PY_PLASMA_TYPE_INIT(GUISkin)
{
    pyGUISkin_Type.tp_new = pyGUISkin_new;
    pyGUISkin_Type.tp_getset = pyGUISkin_GetSet;
    pyGUISkin_Type.tp_base = &pyKeyedObject_Type;
    if (PyType_CheckAndReady(&pyGUISkin_Type) < 0)
        return nullptr;

    /* Konstants */
    PY_TYPE_ADD_CONST(GUISkin, "kUpLeftCorner", pfGUISkin::kUpLeftCorner);
    PY_TYPE_ADD_CONST(GUISkin, "kTopSpan", pfGUISkin::kTopSpan);
    PY_TYPE_ADD_CONST(GUISkin, "kUpRightCorner", pfGUISkin::kUpRightCorner);
    PY_TYPE_ADD_CONST(GUISkin, "kRightSpan", pfGUISkin::kRightSpan);
    PY_TYPE_ADD_CONST(GUISkin, "kLowerRightCorner", pfGUISkin::kLowerRightCorner);
    PY_TYPE_ADD_CONST(GUISkin, "kBottomSpan", pfGUISkin::kBottomSpan);
    PY_TYPE_ADD_CONST(GUISkin, "kLowerLeftCorner", pfGUISkin::kLowerLeftCorner);
    PY_TYPE_ADD_CONST(GUISkin, "kLeftSpan", pfGUISkin::kLeftSpan);
    PY_TYPE_ADD_CONST(GUISkin, "kMiddleFill", pfGUISkin::kMiddleFill);
    PY_TYPE_ADD_CONST(GUISkin, "kSelectedFill", pfGUISkin::kSelectedFill);
    PY_TYPE_ADD_CONST(GUISkin, "kSubMenuArrow", pfGUISkin::kSubMenuArrow);
    PY_TYPE_ADD_CONST(GUISkin, "kSelectedSubMenuArrow", pfGUISkin::kSelectedSubMenuArrow);
    PY_TYPE_ADD_CONST(GUISkin, "kTreeButtonClosed", pfGUISkin::kTreeButtonClosed);
    PY_TYPE_ADD_CONST(GUISkin, "kTreeButtonOpen", pfGUISkin::kTreeButtonOpen);

    Py_INCREF(&pyGUISkin_Type);
    return (PyObject*)&pyGUISkin_Type;
}

PY_PLASMA_IFC_METHODS(GUISkin, pfGUISkin)
