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
#include "Stream/pyStream.h"

PY_PLASMA_NEW_MSG(GUICtrlProcWriteableObject, "pfGUICtrlProcWriteableObject is abstract")

PY_METHOD_STATIC_VA(GUICtrlProcWriteableObject, Read,
    "Params: stream\n"
    "Read a writable GUI Proc object from `stream`")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "Read expects an hsStream");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "Read expects an hsStream");
        return nullptr;
    }
    pfGUICtrlProcWriteableObject* proc = pfGUICtrlProcWriteableObject::Read(stream->fThis);
    PyObject* pyproc = nullptr;
    if (proc == nullptr) {
        Py_RETURN_NONE;
    } else if (proc->getType() == pfGUICtrlProcWriteableObject::kConsoleCmd) {
        pyproc = pyGUIConsoleCmdProc_FromGUIConsoleCmdProc((pfGUIConsoleCmdProc*)proc);
        ((pyGUIConsoleCmdProc*)pyproc)->fPyOwned = true;
    } else if (proc->getType() == pfGUICtrlProcWriteableObject::kPythonScript) {
        pyproc = pyGUIPythonScriptProc_FromGUIPythonScriptProc((pfGUIPythonScriptProc*)proc);
        ((pyGUIPythonScriptProc*)pyproc)->fPyOwned = true;
    } else if (proc->getType() == pfGUICtrlProcWriteableObject::kCloseDlg) {
        pyproc = pyGUICloseDlgProc_FromGUICloseDlgProc((pfGUICloseDlgProc*)proc);
        ((pyGUICloseDlgProc*)pyproc)->fPyOwned = true;
    } else {
        pyproc = pyGUICtrlProcWriteableObject_FromGUICtrlProcWriteableObject((pfGUICtrlProcWriteableObject*)proc);
        ((pyGUICtrlProcWriteableObject*)pyproc)->fPyOwned = true;
    }
    return pyproc;
}

PY_METHOD_STATIC_VA(GUICtrlProcWriteableObject, Write,
    "Params: stream, proc\n"
    "Write a writable GUI Proc object to `stream`")
{
    pyStream* stream;
    pyGUICtrlProcWriteableObject* proc;
    if (!PyArg_ParseTuple(args, "OO", &stream, &proc)) {
        PyErr_SetString(PyExc_TypeError, "Write expects hsStream, pfGUICtrlProcWriteableObject");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream) || !pyGUICtrlProcWriteableObject_Check((PyObject*)proc)) {
        PyErr_SetString(PyExc_TypeError, "Write expects hsStream, pfGUICtrlProcWriteableObject");
        return nullptr;
    }
    pfGUICtrlProcWriteableObject::Write(stream->fThis, proc->fThis);
    Py_RETURN_NONE;
}

static PyMethodDef pyGUICtrlProcWriteableObject_Methods[] = {
    pyGUICtrlProcWriteableObject_Read_method,
    pyGUICtrlProcWriteableObject_Write_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY_RO(GUICtrlProcWriteableObject, type, getType)

static PyGetSetDef pyGUICtrlProcWriteableObject_GetSet[] = {
    pyGUICtrlProcWriteableObject_type_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(GUICtrlProcWriteableObject, pfGUICtrlProcWriteableObject,
               "pfGUICtrlProcWriteableObject wrapper")

PY_PLASMA_TYPE_INIT(GUICtrlProcWriteableObject)
{
    pyGUICtrlProcWriteableObject_Type.tp_new = pyGUICtrlProcWriteableObject_new;
    pyGUICtrlProcWriteableObject_Type.tp_methods = pyGUICtrlProcWriteableObject_Methods;
    pyGUICtrlProcWriteableObject_Type.tp_getset = pyGUICtrlProcWriteableObject_GetSet;
    pyGUICtrlProcWriteableObject_Type.tp_base = &pyGUICtrlProcObject_Type;
    if (PyType_CheckAndReady(&pyGUICtrlProcWriteableObject_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(GUICtrlProcWriteableObject, "kNull",
                      pfGUICtrlProcWriteableObject::kNull);
    PY_TYPE_ADD_CONST(GUICtrlProcWriteableObject, "kConsoleCmd",
                      pfGUICtrlProcWriteableObject::kConsoleCmd);
    PY_TYPE_ADD_CONST(GUICtrlProcWriteableObject, "kPythonScript",
                      pfGUICtrlProcWriteableObject::kPythonScript);
    PY_TYPE_ADD_CONST(GUICtrlProcWriteableObject, "kCloseDlg",
                      pfGUICtrlProcWriteableObject::kCloseDlg);

    Py_INCREF(&pyGUICtrlProcWriteableObject_Type);
    return (PyObject*)&pyGUICtrlProcWriteableObject_Type;
}

PY_PLASMA_IFC_METHODS(GUICtrlProcWriteableObject, pfGUICtrlProcWriteableObject)
