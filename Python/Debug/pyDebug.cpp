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

PY_PLASMA_NEW_MSG(Debug, "plDebug is static")

PY_METHOD_STATIC_VA(Debug, Init,
    "Params: level=kDLWarning, stream=None\n"
    "Initialize the debug logger")
{
    int level = plDebug::kDLWarning;
    pyStream* stream = nullptr;
    if (!PyArg_ParseTuple(args, "|iO", &level, &stream)) {
        PyErr_SetString(PyExc_TypeError, "Init expects int, hsStream");
        return nullptr;
    }
    if (stream && !pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "Init expects int, hsStream");
        return nullptr;
    }
    plDebug::Init(level, (stream == nullptr) ? nullptr : stream->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_STATIC_VA(Debug, InitFile,
    "Params: level=kDLWarning, filename=\"Plasma.log\"\n"
    "Initialize the debug logger to a file output")
{
    int level = plDebug::kDLWarning;
    ST::string filename = ST_LITERAL("Plasma.log");
    if (!PyArg_ParseTuple(args, "|iO&", &level, PyAnyString_PathDecoder, &filename)) {
        PyErr_SetString(PyExc_TypeError, "InitFile expects int, string (or an os.PathLike object)");
        return nullptr;
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
        return nullptr;
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
        return nullptr;
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
        return nullptr;
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

typedef PyObject pyDebug;
PY_PLASMA_TYPE(Debug, "plDebug", "Plasma debug logger class")

PY_PLASMA_TYPE_INIT(Debug)
{
    pyDebug_Type.tp_new = pyDebug_new;
    pyDebug_Type.tp_methods = pyDebug_Methods;
    if (PyType_CheckAndReady(&pyDebug_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(Debug, "kDLNone", plDebug::kDLNone);
    PY_TYPE_ADD_CONST(Debug, "kDLError", plDebug::kDLError);
    PY_TYPE_ADD_CONST(Debug, "kDLWarning", plDebug::kDLWarning);
    PY_TYPE_ADD_CONST(Debug, "kDLDebug", plDebug::kDLDebug);
    PY_TYPE_ADD_CONST(Debug, "kDLAll", plDebug::kDLAll);

    Py_INCREF(&pyDebug_Type);
    return (PyObject*)&pyDebug_Type;
}
