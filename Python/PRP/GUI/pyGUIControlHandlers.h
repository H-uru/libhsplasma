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

#ifndef _PYGUICONTROLHANDLERS_H
#define _PYGUICONTROLHANDLERS_H

#include "PyPlasma.h"

PY_WRAP_PLASMA(GUICtrlProcObject, class pfGUICtrlProcObject)
PY_WRAP_PLASMA(GUIDialogProc, class pfGUIDialogProc)
PY_WRAP_PLASMA(GUICtrlProcWriteableObject, class pfGUICtrlProcWriteableObject)
PY_WRAP_PLASMA(GUICloseDlgProc, class pfGUICloseDlgProc)
PY_WRAP_PLASMA(GUIConsoleCmdProc, class pfGUIConsoleCmdProc)
PY_WRAP_PLASMA(GUIPythonScriptProc, class pfGUIPythonScriptProc)

PyObject* ICreateGUIControlHandler(class pfGUICtrlProcObject*);

/* Python property helpers */
#define PY_PROPERTY_GUIPROC_READ(myType, name, getter)                  \
    PY_GETSET_GETTER_DECL(myType, name)                                 \
    {                                                                   \
        return ICreateGUIControlHandler(self->fThis->getter());         \
    }

#define PY_PROPERTY_GUIPROC_WRITE(pyType, myType, name, setter)         \
    PY_GETSET_SETTER_DECL(myType, name)                                 \
    {                                                                   \
        if (value == Py_None) {                                         \
            self->fThis->setter(nullptr);                               \
            return 0;                                                   \
        }                                                               \
        if (!py##pyType##_Check(value)) {                               \
            PyErr_SetString(PyExc_TypeError, #name " expected type pf" #pyType); \
            return -1;                                                  \
        }                                                               \
        self->fThis->setter(((py##pyType*)value)->fThis);               \
        return 0;                                                       \
    }

#define PY_PROPERTY_GUIPROC(pyType, myType, name, getter, setter)       \
    PY_PROPERTY_GUIPROC_READ(myType, name, getter)                      \
    PY_PROPERTY_GUIPROC_WRITE(pyType, myType, name, setter)             \
    PY_PROPERTY_GETSET_DECL(myType, name)

#endif
