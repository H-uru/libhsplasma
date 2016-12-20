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

extern "C" {

static PyObject* pyGUICtrlProcWriteableObject_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "pfGUICtrlProcWriteableObject is abstract");
    return NULL;
}

static PyObject* pyGUICtrlProcWriteableObject_Read(PyObject*, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "Read expects an hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "Read expects an hsStream");
        return NULL;
    }
    pfGUICtrlProcWriteableObject* proc = pfGUICtrlProcWriteableObject::Read(stream->fThis);
    PyObject* pyproc = NULL;
    if (proc == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
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

static PyObject* pyGUICtrlProcWriteableObject_Write(PyObject*, PyObject* args) {
    pyStream* stream;
    pyGUICtrlProcWriteableObject* proc;
    if (!PyArg_ParseTuple(args, "OO", &stream, &proc)) {
        PyErr_SetString(PyExc_TypeError, "Write expects hsStream, pfGUICtrlProcWriteableObject");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream) || !pyGUICtrlProcWriteableObject_Check((PyObject*)proc)) {
        PyErr_SetString(PyExc_TypeError, "Write expects hsStream, pfGUICtrlProcWriteableObject");
        return NULL;
    }
    pfGUICtrlProcWriteableObject::Write(stream->fThis, proc->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef pyGUICtrlProcWriteableObject_Methods[] = {
    { "Read", (PyCFunction)pyGUICtrlProcWriteableObject_Read, METH_VARARGS | METH_STATIC,
      "Params: stream\n"
      "Read a writable GUI Proc object from `stream`" },
    { "Write", (PyCFunction)pyGUICtrlProcWriteableObject_Write, METH_VARARGS | METH_STATIC,
      "Params: stream, proc\n"
      "Write a writable GUI Proc object to `stream`" },
    { NULL, NULL, 0, NULL }
};

PY_PROPERTY_RO(GUICtrlProcWriteableObject, type, getType)

static PyGetSetDef pyGUICtrlProcWriteableObject_GetSet[] = {
    pyGUICtrlProcWriteableObject_type_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyGUICtrlProcWriteableObject_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.pfGUICtrlProcWriteableObject", /* tp_name */
    sizeof(pyGUICtrlProcWriteableObject), /* tp_basicsize */
    0,                                  /* tp_itemsize */

    NULL,                               /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_compare */
    NULL,                               /* tp_repr */
    NULL,                               /* tp_as_number */
    NULL,                               /* tp_as_sequence */
    NULL,                               /* tp_as_mapping */
    NULL,                               /* tp_hash */
    NULL,                               /* tp_call */
    NULL,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */

    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
    "pfGUICtrlProcWriteableObject wrapper", /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyGUICtrlProcWriteableObject_Methods, /* tp_methods */
    NULL,                               /* tp_members */
    pyGUICtrlProcWriteableObject_GetSet, /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyGUICtrlProcWriteableObject_new,   /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */

    NULL,                               /* tp_del */
    TP_VERSION_TAG_INIT                 /* tp_version_tag */
    TP_FINALIZE_INIT                    /* tp_finalize */
};

PyObject* Init_pyGUICtrlProcWriteableObject_Type() {
    pyGUICtrlProcWriteableObject_Type.tp_base = &pyGUICtrlProcObject_Type;
    if (PyType_Ready(&pyGUICtrlProcWriteableObject_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyGUICtrlProcWriteableObject_Type.tp_dict, "kNull",
                         PyInt_FromLong(pfGUICtrlProcWriteableObject::kNull));
    PyDict_SetItemString(pyGUICtrlProcWriteableObject_Type.tp_dict, "kConsoleCmd",
                         PyInt_FromLong(pfGUICtrlProcWriteableObject::kConsoleCmd));
    PyDict_SetItemString(pyGUICtrlProcWriteableObject_Type.tp_dict, "kPythonScript",
                         PyInt_FromLong(pfGUICtrlProcWriteableObject::kPythonScript));
    PyDict_SetItemString(pyGUICtrlProcWriteableObject_Type.tp_dict, "kCloseDlg",
                         PyInt_FromLong(pfGUICtrlProcWriteableObject::kCloseDlg));

    Py_INCREF(&pyGUICtrlProcWriteableObject_Type);
    return (PyObject*)&pyGUICtrlProcWriteableObject_Type;
}

PY_PLASMA_IFC_METHODS(GUICtrlProcWriteableObject, pfGUICtrlProcWriteableObject)

}
