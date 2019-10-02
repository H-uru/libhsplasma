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

#include "pyStream.h"

#include <Stream/hsStream.h>

PY_PLASMA_NEW(FileStream, hsFileStream)

PY_METHOD_VA(FileStream, open,
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

PY_METHOD_NOARGS(FileStream, __enter__, nullptr)
{
    Py_INCREF(self);
    return (PyObject*)self;
}

PY_METHOD_VA(FileStream, __exit__, nullptr)
{
    self->fThis->close();
    Py_RETURN_NONE;
}

static PyMethodDef pyFileStream_Methods[] = {
    pyFileStream_open_method,
    pyFileStream___enter___method,
    pyFileStream___exit___method,
    PY_METHOD_TERMINATOR
};

PY_PLASMA_TYPE(FileStream, hsFileStream, "hsFileStream wrapper")

PY_PLASMA_TYPE_INIT(FileStream)
{
    pyFileStream_Type.tp_new = pyFileStream_new;
    pyFileStream_Type.tp_methods = pyFileStream_Methods;
    pyFileStream_Type.tp_base = &pyStream_Type;
    if (PyType_CheckAndReady(&pyFileStream_Type) < 0)
        return nullptr;

    Py_INCREF(&pyFileStream_Type);
    return (PyObject*)&pyFileStream_Type;
}

PY_PLASMA_IFC_METHODS(FileStream, hsFileStream)
