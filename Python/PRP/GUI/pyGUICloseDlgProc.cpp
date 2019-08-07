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

PY_PLASMA_NEW(GUICloseDlgProc, pfGUICloseDlgProc)

PY_PLASMA_TYPE(GUICloseDlgProc, pfGUICloseDlgProc, "pfGUICloseDlgProc wrapper")

PY_PLASMA_TYPE_INIT(GUICloseDlgProc)
{
    pyGUICloseDlgProc_Type.tp_new = pyGUICloseDlgProc_new;
    pyGUICloseDlgProc_Type.tp_base = &pyGUICtrlProcWriteableObject_Type;
    if (PyType_CheckAndReady(&pyGUICloseDlgProc_Type) < 0)
        return nullptr;

    Py_INCREF(&pyGUICloseDlgProc_Type);
    return (PyObject*)&pyGUICloseDlgProc_Type;
}

PY_PLASMA_IFC_METHODS(GUICloseDlgProc, pfGUICloseDlgProc)
