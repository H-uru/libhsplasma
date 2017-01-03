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

#include "pyDebug.h"

#include <Debug/plDebug.h>
#include "Stream/pyStream.h"

extern "C" {

PY_PLASMA_NEW_MSG(Debug, "plDebug is static")

PY_METHOD_STATIC_VA(Debug, Init,
    "Params: level=kDLWarning, stream=None\n"
    "Initialize the debug logger")
{
    int level = plDebug::kDLWarning;
    pyStream* stream = NULL;
    if (!PyArg_ParseTuple(args, "|iO", &level, &stream)) {
        PyErr_SetString(PyExc_TypeError, "Init expects int, hsStream");
        return NULL;
    }
    if (stream != NULL && !pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "Init expects int, hsStream");
        return NULL;
    }
    plDebug::Init(level, (stream == NULL) ? NULL : stream->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_STATIC_VA(Debug, InitFile,
    "Params: level=kDLWarning, filename=\"Plasma.log\"\n"
    "Initialize the debug logger to a file output")
{
    int level = plDebug::kDLWarning;
    const char* filename = "Plasma.log";
    if (!PyArg_ParseTuple(args, "|is", &level, &filename)) {
        PyErr_SetString(PyExc_TypeError, "InitFile expects int, string");
        return NULL;
    }
    plDebug::InitFile(level, filename);
    Py_RETURN_NONE;
}

PY_METHOD_STATIC_VA(Debug, Error,
    "Params: message\n"
    "Write an error message")
{
    const char* msg;
    if (!PyArg_ParseTuple(args, "s", &msg)) {
        PyErr_SetString(PyExc_TypeError, "Error expects a string");
        return NULL;
    }
    plDebug::Error(msg);
    Py_RETURN_NONE;
}

PY_METHOD_STATIC_VA(Debug, Warning,
    "Params: message\n"
    "Write a warning message")
{
    const char* msg;
    if (!PyArg_ParseTuple(args, "s", &msg)) {
        PyErr_SetString(PyExc_TypeError, "Warning expects a string");
        return NULL;
    }
    plDebug::Warning(msg);
    Py_RETURN_NONE;
}

PY_METHOD_STATIC_VA(Debug, Debug,
    "Params: message\n"
    "Write a debug message")
{
    const char* msg;
    if (!PyArg_ParseTuple(args, "s", &msg)) {
        PyErr_SetString(PyExc_TypeError, "Debug expects a string");
        return NULL;
    }
    plDebug::Debug(msg);
    Py_RETURN_NONE;
}

static PyMethodDef pyDebug_Methods[] = {
    pyDebug_Init_method,
    pyDebug_InitFile_method,
    pyDebug_Error_method,
    pyDebug_Warning_method,
    pyDebug_Debug_method,
    PY_METHOD_TERMINATOR
};

PyTypeObject pyDebug_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plDebug",               /* tp_name */
    sizeof(PyObject),                   /* tp_basicsize */
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

    Py_TPFLAGS_DEFAULT,                 /* tp_flags */
    "Plasma debug logger class",        /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyDebug_Methods,                    /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyDebug_new,                        /* tp_new */
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

PyObject* Init_pyDebug_Type() {
    if (PyType_Ready(&pyDebug_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyDebug_Type.tp_dict, "kDLNone",
                         PyInt_FromLong(plDebug::kDLNone));
    PyDict_SetItemString(pyDebug_Type.tp_dict, "kDLError",
                         PyInt_FromLong(plDebug::kDLError));
    PyDict_SetItemString(pyDebug_Type.tp_dict, "kDLWarning",
                         PyInt_FromLong(plDebug::kDLWarning));
    PyDict_SetItemString(pyDebug_Type.tp_dict, "kDLDebug",
                         PyInt_FromLong(plDebug::kDLDebug));
    PyDict_SetItemString(pyDebug_Type.tp_dict, "kDLAll",
                         PyInt_FromLong(plDebug::kDLAll));

    Py_INCREF(&pyDebug_Type);
    return (PyObject*)&pyDebug_Type;
}

}
