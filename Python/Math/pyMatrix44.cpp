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

#include <Math/hsMatrix44.h>
#include "pyGeometry3.h"
#include "Stream/pyStream.h"

extern "C" {

static void pyMatrix44_dealloc(pyMatrix44* self) {
    delete self->fThis;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static int pyMatrix44___init__(pyMatrix44* self, PyObject* args, PyObject* kwds) {
    PyObject* init = NULL;
    if (!PyArg_ParseTuple(args, "|O", &init))
        return -1;

    if (init != NULL) {
        if (pyMatrix44_Check(init)) {
            (*self->fThis) = (*((pyMatrix44*)init)->fThis);
        } else {
            PyErr_SetString(PyExc_TypeError, "__init__ expects a matrix");
            return -1;
        }
    } else {
        self->fThis->Reset();
    }
    return 0;
}

static PyObject* pyMatrix44_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyMatrix44* self = (pyMatrix44*)type->tp_alloc(type, 0);
    if (self != NULL)
        self->fThis = new hsMatrix44();
    return (PyObject*)self;
}

static PyObject* pyMatrix44_multiply(PyObject* left, PyObject* right) {
    if (pyMatrix44_Check(left)) {
        if (pyMatrix44_Check(right)) {
            return pyPlasma_convert(*((pyMatrix44*)left)->fThis * *((pyMatrix44*)right)->fThis);
        } else {
            PyErr_SetString(PyExc_TypeError, "Multiplication operand is not another matrix");
            return NULL;
        }
    } else if (pyMatrix44_Check(right)) {
        PyErr_SetString(PyExc_TypeError, "Multiplication operand is not another matrix");
        return NULL;
    }
    // This should not happen...
    return NULL;
}

static PyObject* pyMatrix44_Subscript(pyMatrix44* self, PyObject* key) {
    int i, j;
    if (!PyArg_ParseTuple(key, "ii", &i, &j)) {
        PyErr_SetString(PyExc_TypeError, "Matrix subscript expects int, int");
        return NULL;
    }
    return PyFloat_FromDouble((*self->fThis)(i, j));
}

static int pyMatrix44_AssSubscript(pyMatrix44* self, PyObject* key, PyObject* value) {
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

PY_GETSET_GETTER_DECL(Matrix44, mat) {
    PyObject* t1 = PyTuple_New(4);
    PyObject* t2 = PyTuple_New(4);
    PyObject* t3 = PyTuple_New(4);
    PyObject* t4 = PyTuple_New(4);
    PyTuple_SET_ITEM(t1, 0, pyPlasma_convert((*self->fThis)(0, 0)));
    PyTuple_SET_ITEM(t1, 1, pyPlasma_convert((*self->fThis)(0, 1)));
    PyTuple_SET_ITEM(t1, 2, pyPlasma_convert((*self->fThis)(0, 2)));
    PyTuple_SET_ITEM(t1, 3, pyPlasma_convert((*self->fThis)(0, 3)));
    PyTuple_SET_ITEM(t2, 0, pyPlasma_convert((*self->fThis)(1, 0)));
    PyTuple_SET_ITEM(t2, 1, pyPlasma_convert((*self->fThis)(1, 1)));
    PyTuple_SET_ITEM(t2, 2, pyPlasma_convert((*self->fThis)(1, 2)));
    PyTuple_SET_ITEM(t2, 3, pyPlasma_convert((*self->fThis)(1, 3)));
    PyTuple_SET_ITEM(t3, 0, pyPlasma_convert((*self->fThis)(2, 0)));
    PyTuple_SET_ITEM(t3, 1, pyPlasma_convert((*self->fThis)(2, 1)));
    PyTuple_SET_ITEM(t3, 2, pyPlasma_convert((*self->fThis)(2, 2)));
    PyTuple_SET_ITEM(t3, 3, pyPlasma_convert((*self->fThis)(2, 3)));
    PyTuple_SET_ITEM(t4, 0, pyPlasma_convert((*self->fThis)(3, 0)));
    PyTuple_SET_ITEM(t4, 1, pyPlasma_convert((*self->fThis)(3, 1)));
    PyTuple_SET_ITEM(t4, 2, pyPlasma_convert((*self->fThis)(3, 2)));
    PyTuple_SET_ITEM(t4, 3, pyPlasma_convert((*self->fThis)(3, 3)));

    PyObject* mat = PyTuple_New(4);
    PyTuple_SET_ITEM(mat, 0, t1);
    PyTuple_SET_ITEM(mat, 1, t2);
    PyTuple_SET_ITEM(mat, 2, t3);
    PyTuple_SET_ITEM(mat, 3, t4);
    return mat;
}

PY_PROPERTY_GETSET_RO_DECL(Matrix44, mat)

PY_GETSET_GETTER_DECL(Matrix44, glMat) {
    PyObject* mat = PyTuple_New(16);
    const float* glmat = self->fThis->glMatrix();
    PyTuple_SET_ITEM(mat, 0, pyPlasma_convert(glmat[0]));
    PyTuple_SET_ITEM(mat, 1, pyPlasma_convert(glmat[1]));
    PyTuple_SET_ITEM(mat, 2, pyPlasma_convert(glmat[2]));
    PyTuple_SET_ITEM(mat, 3, pyPlasma_convert(glmat[3]));
    PyTuple_SET_ITEM(mat, 4, pyPlasma_convert(glmat[4]));
    PyTuple_SET_ITEM(mat, 5, pyPlasma_convert(glmat[5]));
    PyTuple_SET_ITEM(mat, 6, pyPlasma_convert(glmat[6]));
    PyTuple_SET_ITEM(mat, 7, pyPlasma_convert(glmat[7]));
    PyTuple_SET_ITEM(mat, 8, pyPlasma_convert(glmat[8]));
    PyTuple_SET_ITEM(mat, 9, pyPlasma_convert(glmat[9]));
    PyTuple_SET_ITEM(mat, 10, pyPlasma_convert(glmat[10]));
    PyTuple_SET_ITEM(mat, 11, pyPlasma_convert(glmat[11]));
    PyTuple_SET_ITEM(mat, 12, pyPlasma_convert(glmat[12]));
    PyTuple_SET_ITEM(mat, 13, pyPlasma_convert(glmat[13]));
    PyTuple_SET_ITEM(mat, 14, pyPlasma_convert(glmat[14]));
    PyTuple_SET_ITEM(mat, 15, pyPlasma_convert(glmat[15]));
    return mat;
}

PY_PROPERTY_GETSET_RO_DECL(Matrix44, glMat)

static PyObject* pyMatrix44_Identity(PyObject*) {
    return pyPlasma_convert(hsMatrix44::Identity());
}

static PyObject* pyMatrix44_TranslateMat(PyObject*, PyObject* args) {
    pyVector3* vec;
    if (!PyArg_ParseTuple(args, "O", &vec)) {
        PyErr_SetString(PyExc_TypeError, "TranslateMat expects an hsVector3");
        return NULL;
    }
    if (!pyVector3_Check((PyObject*)vec)) {
        PyErr_SetString(PyExc_TypeError, "TranslateMat expects an hsVector3");
        return NULL;
    }
    return pyPlasma_convert(hsMatrix44::TranslateMat(*vec->fThis));
}

static PyObject* pyMatrix44_RotateMat(PyObject*, PyObject* args) {
    int axis;
    float angle;
    if (!PyArg_ParseTuple(args, "if", &axis, &angle)) {
        PyErr_SetString(PyExc_TypeError, "RotateMat expects int, float");
        return NULL;
    }
    return pyPlasma_convert(hsMatrix44::RotateMat(axis, angle));
}

static PyObject* pyMatrix44_ScaleMat(PyObject*, PyObject* args) {
    pyVector3* vec;
    if (!PyArg_ParseTuple(args, "O", &vec)) {
        PyErr_SetString(PyExc_TypeError, "ScaleMat expects an hsVector3");
        return NULL;
    }
    if (!pyVector3_Check((PyObject*)vec)) {
        PyErr_SetString(PyExc_TypeError, "ScaleMat expects an hsVector3");
        return NULL;
    }
    return pyPlasma_convert(hsMatrix44::ScaleMat(*vec->fThis));
}

static PyObject* pyMatrix44_inverse(pyMatrix44* self) {
    return pyPlasma_convert(self->fThis->inverse());
}

static PyObject* pyMatrix44_isIdentity(pyMatrix44* self) {
    return pyPlasma_convert(self->fThis->IsIdentity());
}

static PyObject* pyMatrix44_translate(pyMatrix44* self, PyObject* args) {
    pyVector3* vec;
    if (!PyArg_ParseTuple(args, "O", &vec)) {
        PyErr_SetString(PyExc_TypeError, "translate expects an hsVector3");
        return NULL;
    }
    if (!pyVector3_Check((PyObject*)vec)) {
        PyErr_SetString(PyExc_TypeError, "translate expects an hsVector3");
        return NULL;
    }
    self->fThis->translate(*vec->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyMatrix44_rotate(pyMatrix44* self, PyObject* args) {
    int axis;
    float angle;
    if (!PyArg_ParseTuple(args, "if", &axis, &angle)) {
        PyErr_SetString(PyExc_TypeError, "rotate expects int, float");
        return NULL;
    }
    self->fThis->rotate(axis, angle);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyMatrix44_scale(pyMatrix44* self, PyObject* args) {
    pyVector3* vec;
    if (!PyArg_ParseTuple(args, "O", &vec)) {
        PyErr_SetString(PyExc_TypeError, "scale expects an hsVector3");
        return NULL;
    }
    if (!pyVector3_Check((PyObject*)vec)) {
        PyErr_SetString(PyExc_TypeError, "scale expects an hsVector3");
        return NULL;
    }
    self->fThis->scale(*vec->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyMatrix44_setTranslate(pyMatrix44* self, PyObject* args) {
    pyVector3* vec;
    if (!PyArg_ParseTuple(args, "O", &vec)) {
        PyErr_SetString(PyExc_TypeError, "setTranslate expects an hsVector3");
        return NULL;
    }
    if (!pyVector3_Check((PyObject*)vec)) {
        PyErr_SetString(PyExc_TypeError, "setTranslate expects an hsVector3");
        return NULL;
    }
    self->fThis->setTranslate(*vec->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyMatrix44_setRotate(pyMatrix44* self, PyObject* args) {
    int axis;
    float angle;
    if (!PyArg_ParseTuple(args, "if", &axis, &angle)) {
        PyErr_SetString(PyExc_TypeError, "setRotate expects int, float");
        return NULL;
    }
    self->fThis->setRotate(axis, angle);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyMatrix44_setScale(pyMatrix44* self, PyObject* args) {
    pyVector3* vec;
    if (!PyArg_ParseTuple(args, "O", &vec)) {
        PyErr_SetString(PyExc_TypeError, "setScale expects an hsVector3");
        return NULL;
    }
    if (!pyVector3_Check((PyObject*)vec)) {
        PyErr_SetString(PyExc_TypeError, "setScale expects an hsVector3");
        return NULL;
    }
    self->fThis->setScale(*vec->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyMatrix44_multPoint(pyMatrix44* self, PyObject* args) {
    pyVector3* vec;
    if (!PyArg_ParseTuple(args, "O", &vec)) {
        PyErr_SetString(PyExc_TypeError, "multPoint expects an hsVector3");
        return NULL;
    }
    if (!pyVector3_Check((PyObject*)vec)) {
        PyErr_SetString(PyExc_TypeError, "multPoint expects an hsVector3");
        return NULL;
    }
    hsVector3 result = self->fThis->multPoint(*vec->fThis);
    return pyPlasma_convert(result);
}

static PyObject* pyMatrix44_multVector(pyMatrix44* self, PyObject* args) {
    pyVector3* vec;
    if (!PyArg_ParseTuple(args, "O", &vec)) {
        PyErr_SetString(PyExc_TypeError, "multVector expects an hsVector3");
        return NULL;
    }
    if (!pyVector3_Check((PyObject*)vec)) {
        PyErr_SetString(PyExc_TypeError, "multVector expects an hsVector3");
        return NULL;
    }
    hsVector3 result = self->fThis->multVector(*vec->fThis);
    return pyPlasma_convert(result);
}

static PyObject* pyMatrix44_read(pyMatrix44* self, PyObject* args) {
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

static PyObject* pyMatrix44_write(pyMatrix44* self, PyObject* args) {
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

PyNumberMethods pyMatrix44_As_Number = {
    NULL,                               /* nb_add */
    NULL,                               /* nb_subtract */
    (binaryfunc)pyMatrix44_multiply,    /* nb_multiply */
#if (PY_MAJOR_VERSION < 3)
    NULL,                               /* nb_divide */
#endif
    NULL,                               /* nb_remainder */
    NULL,                               /* nb_divmod */
    NULL,                               /* nb_power */
    NULL,                               /* nb_negative */
    NULL,                               /* nb_positive */
    NULL,                               /* nb_absolute */
    NULL,                               /* nb_nonzero */
    NULL,                               /* nb_invert */
    NULL,                               /* nb_lshift */
    NULL,                               /* nb_rshift */
    NULL,                               /* nb_and */
    NULL,                               /* nb_xor */
    NULL,                               /* nb_or */
#if (PY_MAJOR_VERSION < 3)
    NULL,                               /* nb_coerce */
#endif
    NULL,                               /* nb_int */
    NULL,                               /* nb_long */
    NULL,                               /* nb_float */
#if (PY_MAJOR_VERSION < 3)
    NULL,                               /* nb_oct */
    NULL,                               /* nb_hex */
#endif
    NULL,                               /* nb_inplace_add */
    NULL,                               /* nb_inplace_subtract */
    NULL,                               /* nb_inplace_multiply */
#if (PY_MAJOR_VERSION < 3)
    NULL,                               /* nb_inplace_divide */
#endif
    NULL,                               /* nb_inplace_remainder */
    NULL,                               /* nb_inplace_power */
    NULL,                               /* nb_inplace_lshift */
    NULL,                               /* nb_inplace_rshift */
    NULL,                               /* nb_inplace_and */
    NULL,                               /* nb_inplace_xor */
    NULL,                               /* nb_inplace_or */
    NULL,                               /* nb_floor_divide */
    NULL,                               /* nb_true_divide */
    NULL,                               /* nb_inplace_floor_divide */
    NULL,                               /* nb_inplace_true_divide */
#if ((PY_MAJOR_VERSION > 2) || (PY_MAJOR_VERSION == 2 && PY_MINOR_VERSION >= 5))
    NULL,                               /* nb_index */
#endif
#if ((PY_MAJOR_VERSION > 3) || (PY_MAJOR_VERSION == 3 && PY_MINOR_VERSION >= 5))
    NULL,                               /* nb_matrix_multiply */
    NULL,                               /* nb_inplace_matrix_multiply */
#endif
};

static PyMappingMethods pyMatrix44_As_Mapping = {
    NULL,                                   /* mp_length */
    (binaryfunc)pyMatrix44_Subscript,       /* mp_subscript */
    (objobjargproc)pyMatrix44_AssSubscript  /* mp_ass_subscript */
};

PyGetSetDef pyMatrix44_GetSet[] = {
    pyMatrix44_mat_getset,
    pyMatrix44_glMat_getset,
    PY_GETSET_TERMINATOR
};

PyMethodDef pyMatrix44_Methods[] = {
    { "Identity", (PyCFunction)pyMatrix44_Identity, METH_NOARGS | METH_STATIC,
      "Creates an identity matrix" },
    { "TranslateMat", (PyCFunction)pyMatrix44_TranslateMat, METH_VARARGS | METH_STATIC,
      "Params: vector\n"
      "Creates a translation matrix" },
    { "RotateMat", (PyCFunction)pyMatrix44_RotateMat, METH_VARARGS | METH_STATIC,
      "Params: axis, angle\n"
      "Creates a rotation matrix" },
    { "ScaleMat", (PyCFunction)pyMatrix44_ScaleMat, METH_VARARGS | METH_STATIC,
      "Params: vector\n"
      "Creates a scaling matrix" },
    { "inverse", (PyCFunction)pyMatrix44_inverse, METH_NOARGS,
      "Returns the inverse of the matrix" },
    { "isIdentity", (PyCFunction)pyMatrix44_isIdentity, METH_NOARGS,
      "Returns True if the matrix is the identity matrix" },
    { "translate", (PyCFunction)pyMatrix44_translate, METH_VARARGS,
      "Params: vector\n"
      "Translate the matrix by the specified vector" },
    { "rotate", (PyCFunction)pyMatrix44_rotate, METH_VARARGS,
      "Params: axis, angle\n"
      "Rotate the matrix around the specified axis by angle radians" },
    { "scale", (PyCFunction)pyMatrix44_scale, METH_VARARGS,
      "Params: vector\n"
      "Scale the matrix by the specified vector" },
    { "setTranslate", (PyCFunction)pyMatrix44_setTranslate, METH_VARARGS,
      "Params: vector\n"
      "Set the absolute translation" },
    { "setRotate", (PyCFunction)pyMatrix44_setRotate, METH_VARARGS,
      "Params: axis, angle\n"
      "Set the absolute rotation to be along `axis` at `angle` radians" },
    { "setScale", (PyCFunction)pyMatrix44_setScale, METH_VARARGS,
      "Params: vector\n"
      "Set the absolute scale" },
    { "multPoint", (PyCFunction)pyMatrix44_multPoint, METH_VARARGS,
      "Params: vector\n"
      "Multiply a point by the matrix and add displacement" },
    { "multVector", (PyCFunction)pyMatrix44_multVector, METH_VARARGS,
      "Params: vector\n"
      "Multiply a vector by the matrix and do not add displacement" },
    { "read", (PyCFunction)pyMatrix44_read, METH_VARARGS,
      "Params: stream\n"
      "Reads this matrix from `stream`" },
    { "write", (PyCFunction)pyMatrix44_write, METH_VARARGS,
      "Params: stream\n"
      "Writes this matrix to `stream`" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyMatrix44_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.hsMatrix44",            /* tp_name */
    sizeof(pyMatrix44),                 /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pyMatrix44_dealloc,     /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_compare */
    NULL,                               /* tp_repr */
    &pyMatrix44_As_Number,              /* tp_as_number */
    NULL,                               /* tp_as_sequence */
    &pyMatrix44_As_Mapping,             /* tp_as_mapping */
    NULL,                               /* tp_hash */
    NULL,                               /* tp_call */
    NULL,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */

    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_CHECKTYPES, /* tp_flags */
    "hsMatrix44 wrapper",               /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyMatrix44_Methods,                 /* tp_methods */
    NULL,                               /* tp_members */
    pyMatrix44_GetSet,                  /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyMatrix44___init__,      /* tp_init */
    NULL,                               /* tp_alloc */
    pyMatrix44_new,                     /* tp_new */
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

PyObject* Init_pyMatrix44_Type() {
    if (PyType_Ready(&pyMatrix44_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyMatrix44_Type.tp_dict, "kRight",
                         PyInt_FromLong(hsMatrix44::kRight));
    PyDict_SetItemString(pyMatrix44_Type.tp_dict, "kUp",
                         PyInt_FromLong(hsMatrix44::kUp));
    PyDict_SetItemString(pyMatrix44_Type.tp_dict, "kView",
                         PyInt_FromLong(hsMatrix44::kView));

    Py_INCREF(&pyMatrix44_Type);
    return (PyObject*)&pyMatrix44_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(Matrix44, hsMatrix44)

}
