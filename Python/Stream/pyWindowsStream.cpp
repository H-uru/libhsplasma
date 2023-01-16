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

#ifdef _WIN32

#include "pyStream.h"

#include <Stream/hsWindowsStream.h>

PY_PLASMA_NEW(WindowsStream, hsWindowsStream)

PY_METHOD_VA(WindowsStream, open,
    "Params: filename, mode\n"
    "Opens the specified file.\n"
    "Mode is: fmRead, fmWrite, fmReadWrite, fmCreate")
{
    ST::string filename;
    int mode;

    if (!PyArg_ParseTuple(args, "O&i", PyAnyString_PathDecoder, &filename, &mode)) {
        PyErr_SetString(PyExc_TypeError, "open expects string or an os.PathLike object, int");
        return nullptr;
    }
    try {
        if (!self->fThis->open(filename, (FileMode)mode)) {
            PyErr_SetString(PyExc_IOError, "Error opening file");
            return nullptr;
        }
        Py_INCREF(self);
        return (PyObject*)self;
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error opening file");
        return nullptr;
    }
}

PY_METHOD_NOARGS(WindowsStream, __enter__, nullptr)
{
    Py_INCREF(self);
    return (PyObject*)self;
}

PY_METHOD_VA(WindowsStream, __exit__, nullptr)
{
    self->fThis->close();
    Py_RETURN_NONE;
}

static PyMethodDef pyWindowsStream_Methods[] = {
    pyWindowsStream_open_method,
    pyWindowsStream___enter___method,
    pyWindowsStream___exit___method,
    PY_METHOD_TERMINATOR
};

PY_PLASMA_TYPE(WindowsStream, hsWindowsStream, "hsWindowsStream wrapper")

PY_PLASMA_TYPE_INIT(WindowsStream)
{
    pyWindowsStream_Type.tp_new = pyWindowsStream_new;
    pyWindowsStream_Type.tp_methods = pyWindowsStream_Methods;
    pyWindowsStream_Type.tp_base = &pyStream_Type;
    if (PyType_CheckAndReady(&pyWindowsStream_Type) < 0)
        return nullptr;

    Py_INCREF(&pyWindowsStream_Type);
    return (PyObject*)&pyWindowsStream_Type;
}

PY_PLASMA_IFC_METHODS(WindowsStream, hsWindowsStream)

#endif
