#include <Python.h>
#include <Math/hsMatrix44.h>
#include "pyMatrix44.h"
#include "pyGeometry3.h"
#include "../Stream/pyStream.h"

extern "C" {

static void pyMatrix44_dealloc(pyMatrix44* self) {
    delete self->fThis;
    self->ob_type->tp_free((PyObject*)self);
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
            return pyMatrix44_FromMatrix44(*((pyMatrix44*)left)->fThis * *((pyMatrix44*)right)->fThis);
        } else if (pyVector3_Check(right)) {
            PyErr_Clear();
            return pyVector3_FromVector3(*((pyMatrix44*)left)->fThis * *((pyVector3*)right)->fThis);
        } else {
            PyErr_SetString(PyExc_TypeError, "Matrix multiplication requires a matrix or a vector");
            return NULL;
        }
    } else if (pyMatrix44_Check(right)) {
        if (pyVector3_Check(left)) {
            return pyVector3_FromVector3(*((pyVector3*)left)->fThis * *((pyMatrix44*)right)->fThis);
        } else {
            PyErr_SetString(PyExc_TypeError, "Matrix multiplication requires a matrix or a vector");
            return NULL;
        }
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

static PyObject* pyMatrix44_getMat(pyMatrix44* self, void*) {
    PyObject* l1 = PyList_New(4);
    PyObject* l2 = PyList_New(4);
    PyObject* l3 = PyList_New(4);
    PyObject* l4 = PyList_New(4);
    PyList_SET_ITEM(l1, 0, PyFloat_FromDouble((*self->fThis)(0, 0)));
    PyList_SET_ITEM(l1, 1, PyFloat_FromDouble((*self->fThis)(0, 1)));
    PyList_SET_ITEM(l1, 2, PyFloat_FromDouble((*self->fThis)(0, 2)));
    PyList_SET_ITEM(l1, 3, PyFloat_FromDouble((*self->fThis)(0, 3)));
    PyList_SET_ITEM(l2, 0, PyFloat_FromDouble((*self->fThis)(1, 0)));
    PyList_SET_ITEM(l2, 1, PyFloat_FromDouble((*self->fThis)(1, 1)));
    PyList_SET_ITEM(l2, 2, PyFloat_FromDouble((*self->fThis)(1, 2)));
    PyList_SET_ITEM(l2, 3, PyFloat_FromDouble((*self->fThis)(1, 3)));
    PyList_SET_ITEM(l3, 0, PyFloat_FromDouble((*self->fThis)(2, 0)));
    PyList_SET_ITEM(l3, 1, PyFloat_FromDouble((*self->fThis)(2, 1)));
    PyList_SET_ITEM(l3, 2, PyFloat_FromDouble((*self->fThis)(2, 2)));
    PyList_SET_ITEM(l3, 3, PyFloat_FromDouble((*self->fThis)(2, 3)));
    PyList_SET_ITEM(l4, 0, PyFloat_FromDouble((*self->fThis)(3, 0)));
    PyList_SET_ITEM(l4, 1, PyFloat_FromDouble((*self->fThis)(3, 1)));
    PyList_SET_ITEM(l4, 2, PyFloat_FromDouble((*self->fThis)(3, 2)));
    PyList_SET_ITEM(l4, 3, PyFloat_FromDouble((*self->fThis)(3, 3)));

    PyObject* list = PyList_New(4);
    PyList_SET_ITEM(list, 0, l1);
    PyList_SET_ITEM(list, 1, l2);
    PyList_SET_ITEM(list, 2, l3);
    PyList_SET_ITEM(list, 3, l4);
    return list;
}

static PyObject* pyMatrix44_getGlMat(pyMatrix44* self, void*) {
    PyObject* list = PyList_New(16);
    float glmat[16];
    memcpy(glmat, self->fThis->glMatrix(), sizeof(float) * 16);
    PyList_SET_ITEM(list, 0, PyFloat_FromDouble(glmat[0]));
    PyList_SET_ITEM(list, 1, PyFloat_FromDouble(glmat[1]));
    PyList_SET_ITEM(list, 2, PyFloat_FromDouble(glmat[2]));
    PyList_SET_ITEM(list, 3, PyFloat_FromDouble(glmat[3]));
    PyList_SET_ITEM(list, 4, PyFloat_FromDouble(glmat[4]));
    PyList_SET_ITEM(list, 5, PyFloat_FromDouble(glmat[5]));
    PyList_SET_ITEM(list, 6, PyFloat_FromDouble(glmat[6]));
    PyList_SET_ITEM(list, 7, PyFloat_FromDouble(glmat[7]));
    PyList_SET_ITEM(list, 8, PyFloat_FromDouble(glmat[8]));
    PyList_SET_ITEM(list, 9, PyFloat_FromDouble(glmat[9]));
    PyList_SET_ITEM(list, 10, PyFloat_FromDouble(glmat[10]));
    PyList_SET_ITEM(list, 11, PyFloat_FromDouble(glmat[11]));
    PyList_SET_ITEM(list, 12, PyFloat_FromDouble(glmat[12]));
    PyList_SET_ITEM(list, 13, PyFloat_FromDouble(glmat[13]));
    PyList_SET_ITEM(list, 14, PyFloat_FromDouble(glmat[14]));
    PyList_SET_ITEM(list, 15, PyFloat_FromDouble(glmat[15]));
    return list;
}

static int pyMatrix44_setMat(pyMatrix44* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "mat is read-only");
    return -1;
}

static int pyMatrix44_setGlMat(pyMatrix44* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "glMat is read-only");
    return -1;
}

static PyObject* pyMatrix44_Identity(PyObject*) {
    return pyMatrix44_FromMatrix44(hsMatrix44::Identity());
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
    return pyMatrix44_FromMatrix44(hsMatrix44::TranslateMat(*vec->fThis));
}

static PyObject* pyMatrix44_RotateMat(PyObject*, PyObject* args) {
    int axis;
    float angle;
    if (!PyArg_ParseTuple(args, "if", &axis, &angle)) {
        PyErr_SetString(PyExc_TypeError, "RotateMat expects int, float");
        return NULL;
    }
    return pyMatrix44_FromMatrix44(hsMatrix44::RotateMat(axis, angle));
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
    return pyMatrix44_FromMatrix44(hsMatrix44::ScaleMat(*vec->fThis));
}

static PyObject* pyMatrix44_isIdentity(pyMatrix44* self) {
    return PyBool_FromLong(self->fThis->IsIdentity() ? 1 : 0);
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
    NULL,                               /* nb_divide */
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
    NULL,                               /* nb_coerce */
    NULL,                               /* nb_int */
    NULL,                               /* nb_long */
    NULL,                               /* nb_float */
    NULL,                               /* nb_oct */
    NULL,                               /* nb_hex */
    NULL,                               /* nb_inplace_add */
    NULL,                               /* nb_inplace_subtract */
    NULL,                               /* nb_inplace_divide */
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
};

static PyMappingMethods pyMatrix44_As_Mapping = {
    NULL,                                   /* mp_length */
    (binaryfunc)pyMatrix44_Subscript,       /* mp_subscript */
    (objobjargproc)pyMatrix44_AssSubscript  /* mp_ass_subscript */
};

PyGetSetDef pyMatrix44_GetSet[] = {
    { "mat", (getter)pyMatrix44_getMat, (setter)pyMatrix44_setMat, NULL, NULL },
    { "glMat", (getter)pyMatrix44_getGlMat, (setter)pyMatrix44_setGlMat, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
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
    { "read", (PyCFunction)pyMatrix44_read, METH_VARARGS,
      "Params: stream\n"
      "Reads this matrix from `stream`" },
    { "write", (PyCFunction)pyMatrix44_write, METH_VARARGS,
      "Params: stream\n"
      "Writes this matrix to `stream`" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyMatrix44_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.hsMatrix44",              /* tp_name */
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

int pyMatrix44_Check(PyObject* obj) {
    if (obj->ob_type == &pyMatrix44_Type
        || PyType_IsSubtype(obj->ob_type, &pyMatrix44_Type))
        return 1;
    return 0;
}

PyObject* pyMatrix44_FromMatrix44(const hsMatrix44& mat) {
    pyMatrix44* pmat = PyObject_New(pyMatrix44, &pyMatrix44_Type);
    pmat->fThis = new hsMatrix44(mat);
    return (PyObject*)pmat;
}

}
