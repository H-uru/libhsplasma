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

#include <PRP/GUI/pfGUIMultiLineEditCtrl.h>
#include "pyGUIMultiLineEditCtrl.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/GUI/pyGUIControlMod.h"

PY_PLASMA_NEW(GUIMultiLineEditCtrl, pfGUIMultiLineEditCtrl)

PY_PROPERTY(plKey, GUIMultiLineEditCtrl, scrollCtrl, getScrollCtrl, setScrollCtrl)

static PyGetSetDef pyGUIMultiLineEditCtrl_GetSet[] = {
    pyGUIMultiLineEditCtrl_scrollCtrl_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(GUIMultiLineEditCtrl, pfGUIMultiLineEditCtrl, "pfGUIMultiLineEditCtrl wrapper")

PY_PLASMA_TYPE_INIT(GUIMultiLineEditCtrl)
{
    pyGUIMultiLineEditCtrl_Type.tp_new = pyGUIMultiLineEditCtrl_new;
    pyGUIMultiLineEditCtrl_Type.tp_getset = pyGUIMultiLineEditCtrl_GetSet;
    pyGUIMultiLineEditCtrl_Type.tp_base = &pyGUIControlMod_Type;
    if (PyType_CheckAndReady(&pyGUIMultiLineEditCtrl_Type) < 0)
        return nullptr;

    Py_INCREF(&pyGUIMultiLineEditCtrl_Type);
    return (PyObject*)&pyGUIMultiLineEditCtrl_Type;
}

PY_PLASMA_IFC_METHODS(GUIMultiLineEditCtrl, pfGUIMultiLineEditCtrl)
