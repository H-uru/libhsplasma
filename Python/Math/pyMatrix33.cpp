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

#include <PyPlasma.h>
#include <Math/hsMatrix33.h>
#include "pyMatrix.h"
#include "Stream/pyStream.h"

extern "C" {

static void pyMatrix33_dealloc(pyMatrix33* self) {
    delete self->fThis;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static int pyMatrix33___init__(pyMatrix33* self, PyObject* args, PyObject* kwds) {
    PyObject* init = NULL;
    if (!PyArg_ParseTuple(args, "|O", &init))
        return -1;

    if (init != NULL) {
        if (pyMatrix33_Check(init)) {
            (*self->fThis) = (*((pyMatrix33*)init)->fThis);
        } else {
            PyErr_SetString(PyExc_TypeError, "__init__ expects a matrix");
            return -1;
        }
    } else {
        self->fThis->Reset();
    }
    return 0;
}

static PyObject* pyMatrix33_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyMatrix33* self = (pyMatrix33*)type->tp_alloc(type, 0);
    if (self != NULL)
        self->fThis = new hsMatrix33();
    return (PyObject*)self;
}

static PyObject* pyMatrix33_Subscript(pyMatrix33* self, PyObject* key) {
    int i, j;
    if (!PyArg_ParseTuple(key, "ii", &i, &j)) {
        PyErr_SetString(PyExc_TypeError, "Matrix subscript expects int, int");
        return NULL;
    }
    return PyFloat_FromDouble((*self->fThis)(i, j));
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

static PyObject* pyMatrix33_getMat(pyMatrix33* self, void*) {
    PyObject* l1 = PyList_New(3);
    PyObject* l2 = PyList_New(3);
    PyObject* l3 = PyList_New(3);
    PyList_SET_ITEM(l1, 0, PyFloat_FromDouble((*self->fThis)(0, 0)));
    PyList_SET_ITEM(l1, 1, PyFloat_FromDouble((*self->fThis)(0, 1)));
    PyList_SET_ITEM(l1, 2, PyFloat_FromDouble((*self->fThis)(0, 2)));
    PyList_SET_ITEM(l2, 0, PyFloat_FromDouble((*self->fThis)(1, 0)));
    PyList_SET_ITEM(l2, 1, PyFloat_FromDouble((*self->fThis)(1, 1)));
    PyList_SET_ITEM(l2, 2, PyFloat_FromDouble((*self->fThis)(1, 2)));
    PyList_SET_ITEM(l3, 0, PyFloat_FromDouble((*self->fThis)(2, 0)));
    PyList_SET_ITEM(l3, 1, PyFloat_FromDouble((*self->fThis)(2, 1)));
    PyList_SET_ITEM(l3, 2, PyFloat_FromDouble((*self->fThis)(2, 2)));

    PyObject* list = PyList_New(3);
    PyList_SET_ITEM(list, 0, l1);
    PyList_SET_ITEM(list, 1, l2);
    PyList_SET_ITEM(list, 2, l3);
    return list;
}

static int pyMatrix33_setMat(pyMatrix33* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "mat is read-only");
    return -1;
}

static PyObject* pyMatrix33_read(pyMatrix33* self, PyObject* args) {
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
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyMatrix33_write(pyMatrix33* self, PyObject* args) {
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
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMappingMethods pyMatrix33_As_Mapping = {
    NULL,                                   /* mp_length */
    (binaryfunc)pyMatrix33_Subscript,       /* mp_subscript */
    (objobjargproc)pyMatrix33_AssSubscript  /* mp_ass_subscript */
};

PyGetSetDef pyMatrix33_GetSet[] = {
    { "mat", (getter)pyMatrix33_getMat, (setter)pyMatrix33_setMat, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyMethodDef pyMatrix33_Methods[] = {
    { "read", (PyCFunction)pyMatrix33_read, METH_VARARGS,
      "Params: stream\n"
      "Reads this matrix from `stream`" },
    { "write", (PyCFunction)pyMatrix33_write, METH_VARARGS,
      "Params: stream\n"
      "Writes this matrix to `stream`" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyMatrix33_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.hsMatrix33",              /* tp_name */
    sizeof(pyMatrix33),                 /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pyMatrix33_dealloc,     /* tp_dealloc */
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

    (initproc)pyMatrix33___init__,      /* tp_init */
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
};

PyObject* Init_pyMatrix33_Type() {
    if (PyType_Ready(&pyMatrix33_Type) < 0)
        return NULL;

    Py_INCREF(&pyMatrix33_Type);
    return (PyObject*)&pyMatrix33_Type;
}

int pyMatrix33_Check(PyObject* obj) {
    if (obj->ob_type == &pyMatrix33_Type
        || PyType_IsSubtype(obj->ob_type, &pyMatrix33_Type))
        return 1;
    return 0;
}

PyObject* pyMatrix33_FromMatrix33(const hsMatrix33& mat) {
    pyMatrix33* pmat = PyObject_New(pyMatrix33, &pyMatrix33_Type);
    pmat->fThis = new hsMatrix33(mat);
    return (PyObject*)pmat;
}

}
