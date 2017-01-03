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

extern "C" {

PY_PLASMA_VALUE_DEALLOC(Matrix33)

PY_PLASMA_INIT_DECL(Matrix33) {
    PyObject* init = NULL;
    if (!PyArg_ParseTuple(args, "|O", &init))
        return -1;

    if (init != NULL) {
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

static PyObject* pyMatrix33_Subscript(pyMatrix33* self, PyObject* key) {
    int i, j;
    if (!PyArg_ParseTuple(key, "ii", &i, &j)) {
        PyErr_SetString(PyExc_TypeError, "Matrix subscript expects int, int");
        return NULL;
    }
    return pyPlasma_convert((*self->fThis)(i, j));
}

static int pyMatrix33_AssSubscript(pyMatrix33* self, PyObject* key, PyObject* value) {
    int i, j;
    if (!PyArg_ParseTuple(key, "ii", &i, &j)) {
        PyErr_SetString(PyExc_TypeError, "Matrix subscript expects int, int");
        return -1;
    }
    if (!PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "Matrix values should be floats");
        return -1;
    }
    (*self->fThis)(i, j) = PyFloat_AsDouble(value);
    return 0;
}

static PyMappingMethods pyMatrix33_As_Mapping = {
    NULL,                                   /* mp_length */
    (binaryfunc)pyMatrix33_Subscript,       /* mp_subscript */
    (objobjargproc)pyMatrix33_AssSubscript  /* mp_ass_subscript */
};

PY_GETSET_GETTER_DECL(Matrix33, mat) {
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
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects a hsStream");
        return NULL;
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
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects a hsStream");
        return NULL;
    }
    self->fThis->write(stream->fThis);
    Py_RETURN_NONE;
}

PyMethodDef pyMatrix33_Methods[] = {
    pyMatrix33_read_method,
    pyMatrix33_write_method,
    PY_METHOD_TERMINATOR
};

PyTypeObject pyMatrix33_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.hsMatrix33",            /* tp_name */
    sizeof(pyMatrix33),                 /* tp_basicsize */
    0,                                  /* tp_itemsize */

    pyMatrix33_dealloc,                 /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_compare */
    NULL,                               /* tp_repr */
    NULL,                               /* tp_as_number */
    NULL,                               /* tp_as_sequence */
    &pyMatrix33_As_Mapping,             /* tp_as_mapping */
    NULL,                               /* tp_hash */
    NULL,                               /* tp_call */
    NULL,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */

    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_CHECKTYPES, /* tp_flags */
    "hsMatrix33 wrapper",               /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyMatrix33_Methods,                 /* tp_methods */
    NULL,                               /* tp_members */
    pyMatrix33_GetSet,                  /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    pyMatrix33___init__,                /* tp_init */
    NULL,                               /* tp_alloc */
    pyMatrix33_new,                     /* tp_new */
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

PyObject* Init_pyMatrix33_Type() {
    if (PyType_Ready(&pyMatrix33_Type) < 0)
        return NULL;

    Py_INCREF(&pyMatrix33_Type);
    return (PyObject*)&pyMatrix33_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(Matrix33, hsMatrix33)

}
