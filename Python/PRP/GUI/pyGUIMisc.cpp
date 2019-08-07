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

#include <PRP/GUI/pfGUIMisc.hpp>
#include "pyGUIMisc.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/GUI/pyGUIControlMod.h"

/* pyGUIClickMapCtrl */
PY_PLASMA_NEW(GUIClickMapCtrl, pfGUIClickMapCtrl)

PY_PLASMA_TYPE(GUIClickMapCtrl, pfGUIClickMapCtrl, "pfGUIClickMapCtrl wrapper")

PY_PLASMA_TYPE_INIT(GUIClickMapCtrl)
{
    pyGUIClickMapCtrl_Type.tp_new = pyGUIClickMapCtrl_new;
    pyGUIClickMapCtrl_Type.tp_base = &pyGUIControlMod_Type;
    if (PyType_CheckAndReady(&pyGUIClickMapCtrl_Type) < 0)
        return nullptr;

    /* Konstants */
    PY_TYPE_ADD_CONST(GUIClickMapCtrl, "kReportDragging", pfGUIClickMapCtrl::kReportDragging);
    PY_TYPE_ADD_CONST(GUIClickMapCtrl, "kReportHovering", pfGUIClickMapCtrl::kReportHovering);

    Py_INCREF(&pyGUIClickMapCtrl_Type);
    return (PyObject*)&pyGUIClickMapCtrl_Type;
}

PY_PLASMA_IFC_METHODS(GUIClickMapCtrl, pfGUIClickMapCtrl)


/* pyGUIDragBarCtrl */
PY_PLASMA_NEW(GUIDragBarCtrl, pfGUIDragBarCtrl)

PY_PLASMA_TYPE(GUIDragBarCtrl, pfGUIDragBarCtrl, "pfGUIDragBarCtrl wrapper")

PY_PLASMA_TYPE_INIT(GUIDragBarCtrl)
{
    pyGUIDragBarCtrl_Type.tp_new = pyGUIDragBarCtrl_new;
    pyGUIDragBarCtrl_Type.tp_base = &pyGUIControlMod_Type;
    if (PyType_CheckAndReady(&pyGUIDragBarCtrl_Type) < 0)
        return nullptr;

    Py_INCREF(&pyGUIDragBarCtrl_Type);
    return (PyObject*)&pyGUIDragBarCtrl_Type;
}

PY_PLASMA_IFC_METHODS(GUIDragBarCtrl, pfGUIDragBarCtrl)


/* pyGUIDraggableMod */
PY_PLASMA_NEW(GUIDraggableMod, pfGUIDraggableMod)

PY_PLASMA_TYPE(GUIDraggableMod, pfGUIDraggableMod, "pfGUIDraggableMod wrapper")

PY_PLASMA_TYPE_INIT(GUIDraggableMod)
{
    pyGUIDraggableMod_Type.tp_new = pyGUIDraggableMod_new;
    pyGUIDraggableMod_Type.tp_base = &pyGUIControlMod_Type;
    if (PyType_CheckAndReady(&pyGUIDraggableMod_Type) < 0)
        return nullptr;

    /* Konstants */
    PY_TYPE_ADD_CONST(GUIDraggableMod, "kReportDragging", pfGUIDraggableMod::kReportDragging);
    PY_TYPE_ADD_CONST(GUIDraggableMod, "kHideCursorWhileDragging", pfGUIDraggableMod::kHideCursorWhileDragging);
    PY_TYPE_ADD_CONST(GUIDraggableMod, "kAlwaysSnapBackToStart", pfGUIDraggableMod::kAlwaysSnapBackToStart);

    Py_INCREF(&pyGUIDraggableMod_Type);
    return (PyObject*)&pyGUIDraggableMod_Type;
}

PY_PLASMA_IFC_METHODS(GUIDraggableMod, pfGUIDraggableMod)


/* pyGUIEditBoxMod */
PY_PLASMA_NEW(GUIEditBoxMod, pfGUIEditBoxMod)

PY_PLASMA_TYPE(GUIEditBoxMod, pfGUIEditBoxMod, "pfGUIEditBoxMod wrapper")

PY_PLASMA_TYPE_INIT(GUIEditBoxMod)
{
    pyGUIEditBoxMod_Type.tp_new = pyGUIEditBoxMod_new;
    pyGUIEditBoxMod_Type.tp_base = &pyGUIControlMod_Type;
    if (PyType_CheckAndReady(&pyGUIEditBoxMod_Type) < 0)
        return nullptr;

    Py_INCREF(&pyGUIEditBoxMod_Type);
    return (PyObject*)&pyGUIEditBoxMod_Type;
}

PY_PLASMA_IFC_METHODS(GUIEditBoxMod, pfGUIEditBoxMod)
