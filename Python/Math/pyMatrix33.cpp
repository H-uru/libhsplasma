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

#include "pyMatrix.h"

#include <Math/hsMatrix33.h>
#include "Stream/pyStream.h"

PY_PLASMA_VALUE_DEALLOC(Matrix33)

PY_PLASMA_INIT_DECL(Matrix33)
{
    PyObject* init = nullptr;
    if (!PyArg_ParseTuple(args, "|O", &init))
        return -1;

    if (init) {
        if (pyMatrix33_Check(init)) {
            (*self->fThis) = pyPlasma_get<hsMatrix33>(init);
        } else {
            PyErr_SetString(PyExc_TypeError, "__init__ expects a matrix");
            return -1;
        }
    } else {
        self->fThis->Reset();
    }
    return 0;
}

PY_PLASMA_VALUE_NEW(Matrix33, hsMatrix33)

PY_PLASMA_SUBSCRIPT_DECL(Matrix33)
{
    int i, j;
    if (!PyArg_ParseTuple(key, "ii", &i, &j)) {
        PyErr_SetString(PyExc_TypeError, "Matrix subscript expects int, int");
        return nullptr;
    }
    return pyPlasma_convert((*self->fThis)(i, j));
}

PY_PLASMA_ASS_SUBSCRIPT_DECL(Matrix33)
{
    int i, j;
    if (!PyArg_ParseTuple(key, "ii", &i, &j)) {
        PyErr_SetString(PyExc_TypeError, "Matrix subscript expects int, int");
        return -1;
    }
    if (!pyPlasma_check<float>(value)) {
        PyErr_SetString(PyExc_TypeError, "Matrix values should be floats");
        return -1;
    }
    (*self->fThis)(i, j) = pyPlasma_get<float>(value);
    return 0;
}

PY_GETSET_GETTER_DECL(Matrix33, mat)
{
    PyObject* t1 = PyTuple_New(3);
    PyObject* t2 = PyTuple_New(3);
    PyObject* t3 = PyTuple_New(3);
    PyTuple_SET_ITEM(t1, 0, pyPlasma_convert((*self->fThis)(0, 0)));
    PyTuple_SET_ITEM(t1, 1, pyPlasma_convert((*self->fThis)(0, 1)));
    PyTuple_SET_ITEM(t1, 2, pyPlasma_convert((*self->fThis)(0, 2)));
    PyTuple_SET_ITEM(t2, 0, pyPlasma_convert((*self->fThis)(1, 0)));
    PyTuple_SET_ITEM(t2, 1, pyPlasma_convert((*self->fThis)(1, 1)));
    PyTuple_SET_ITEM(t2, 2, pyPlasma_convert((*self->fThis)(1, 2)));
    PyTuple_SET_ITEM(t3, 0, pyPlasma_convert((*self->fThis)(2, 0)));
    PyTuple_SET_ITEM(t3, 1, pyPlasma_convert((*self->fThis)(2, 1)));
    PyTuple_SET_ITEM(t3, 2, pyPlasma_convert((*self->fThis)(2, 2)));

    PyObject* mat = PyTuple_New(3);
    PyTuple_SET_ITEM(mat, 0, t1);
    PyTuple_SET_ITEM(mat, 1, t2);
    PyTuple_SET_ITEM(mat, 2, t3);
    return mat;
}

PY_PROPERTY_GETSET_RO_DECL(Matrix33, mat)

PyGetSetDef pyMatrix33_GetSet[] = {
    pyMatrix33_mat_getset,
    PY_GETSET_TERMINATOR
};

PY_METHOD_VA(Matrix33, read,
    "Params: stream\n"
    "Reads this matrix from `stream`")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects a hsStream");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects a hsStream");
        return nullptr;
    }
    self->fThis->read(stream->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(Matrix33, write,
    "Params: stream\n"
    "Writes this matrix to `stream`")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects a hsStream");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects a hsStream");
        return nullptr;
    }
    self->fThis->write(stream->fThis);
    Py_RETURN_NONE;
}

PyMethodDef pyMatrix33_Methods[] = {
    pyMatrix33_read_method,
    pyMatrix33_write_method,
    PY_METHOD_TERMINATOR
};

PY_PLASMA_TYPE(Matrix33, hsMatrix33, "hsMatrix33 wrapper");
PY_PLASMA_TYPE_AS_MAPPING(Matrix33)

PY_PLASMA_TYPE_INIT(Matrix33)
{
    pyMatrix33_As_Mapping.mp_subscript = pyMatrix33_mp_subscript;
    pyMatrix33_As_Mapping.mp_ass_subscript = pyMatrix33_mp_ass_subscript;
    pyMatrix33_Type.tp_dealloc = pyMatrix33_dealloc;
    pyMatrix33_Type.tp_init = pyMatrix33___init__;
    pyMatrix33_Type.tp_new = pyMatrix33_new;
    pyMatrix33_Type.tp_as_mapping = &pyMatrix33_As_Mapping;
    pyMatrix33_Type.tp_methods = pyMatrix33_Methods;
    pyMatrix33_Type.tp_getset = pyMatrix33_GetSet;
    if (PyType_CheckAndReady(&pyMatrix33_Type) < 0)
        return nullptr;

    Py_INCREF(&pyMatrix33_Type);
    return (PyObject*)&pyMatrix33_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(Matrix33, hsMatrix33)
