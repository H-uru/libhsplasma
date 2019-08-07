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

PY_PLASMA_NEW(GUIConsoleCmdProc, pfGUIConsoleCmdProc)

PY_PROPERTY(ST::string, GUIConsoleCmdProc, command, getCommand, setCommand)

static PyGetSetDef pyGUIConsoleCmdProc_GetSet[] = {
    pyGUIConsoleCmdProc_command_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(GUIConsoleCmdProc, pfGUIConsoleCmdProc, "pfGUIConsoleCmdProc wrapper")

PY_PLASMA_TYPE_INIT(GUIConsoleCmdProc)
{
    pyGUIConsoleCmdProc_Type.tp_new = pyGUIConsoleCmdProc_new;
    pyGUIConsoleCmdProc_Type.tp_getset = pyGUIConsoleCmdProc_GetSet;
    pyGUIConsoleCmdProc_Type.tp_base = &pyGUICtrlProcWriteableObject_Type;
    if (PyType_CheckAndReady(&pyGUIConsoleCmdProc_Type) < 0)
        return nullptr;

    Py_INCREF(&pyGUIConsoleCmdProc_Type);
    return (PyObject*)&pyGUIConsoleCmdProc_Type;
}

PY_PLASMA_IFC_METHODS(GUIConsoleCmdProc, pfGUIConsoleCmdProc)
