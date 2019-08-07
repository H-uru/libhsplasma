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

#include "pyGUIControlHandlers.h"

#include <PRP/GUI/pfGUIControlHandlers.h>

PY_PLASMA_DEALLOC(GUICtrlProcObject)
PY_PLASMA_EMPTY_INIT(GUICtrlProcObject)
PY_PLASMA_NEW_MSG(GUICtrlProcObject, "pfGUICtrlProcObject is abstract")

PY_PLASMA_TYPE(GUICtrlProcObject, pfGUICtrlProcObject, "pfGUICtrlProcObject wrapper")

PY_PLASMA_TYPE_INIT(GUICtrlProcObject)
{
    pyGUICtrlProcObject_Type.tp_dealloc = pyGUICtrlProcObject_dealloc;
    pyGUICtrlProcObject_Type.tp_init = pyGUICtrlProcObject___init__;
    pyGUICtrlProcObject_Type.tp_new = pyGUICtrlProcObject_new;
    if (PyType_CheckAndReady(&pyGUICtrlProcObject_Type) < 0)
        return nullptr;

    Py_INCREF(&pyGUICtrlProcObject_Type);
    return (PyObject*)&pyGUICtrlProcObject_Type;
}

PY_PLASMA_IFC_METHODS(GUICtrlProcObject, pfGUICtrlProcObject)
