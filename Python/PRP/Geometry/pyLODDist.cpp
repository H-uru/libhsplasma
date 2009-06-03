#include <PyPlasma.h>
#include <PRP/Geometry/plClusterGroup.h>
#include "pyClusterGroup.h"
#include "Stream/pyStream.h"

extern "C" {

static PyObject* pyLODDist_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "Cannot create plLODDist objects from Python");
    return NULL;
}

static PyObject* pyLODDist_read(pyLODDist* self, PyObject* args) {
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

static PyObject* pyLODDist_write(pyLODDist* self, PyObject* args) {
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

static PyObject* pyLODDist_getMin(pyLODDist* self, void*) {
    return PyFloat_FromDouble(self->fThis->getMin());
}

static PyObject* pyLODDist_getMax(pyLODDist* self, void*) {
    return PyFloat_FromDouble(self->fThis->getMax());
}

static int pyLODDist_setMin(pyLODDist* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "min should be a float");
        return -1;
    }
    self->fThis->setMin(PyFloat_AsDouble(value));
    return 0;
}

static int pyLODDist_setMax(pyLODDist* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "max should be a float");
        return -1;
    }
    self->fThis->setMax(PyFloat_AsDouble(value));
    return 0;
}

static PyMethodDef pyLODDist_Methods[] = {
    { "read", (PyCFunction)pyLODDist_read, METH_VARARGS,
      "Params: stream\n"
      "Reads this object from the stream" },
    { "write", (PyCFunction)pyLODDist_write, METH_VARARGS,
      "Params: stream\n"
      "Writes this object to the stream" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyLODDist_GetSet[] = {
    { "min", (getter)pyLODDist_getMin, (setter)pyLODDist_setMin, NULL, NULL },
    { "max", (getter)pyLODDist_getMax, (setter)pyLODDist_setMax, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyLODDist_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plLODDist",               /* tp_name */
    sizeof(pyLODDist),                  /* tp_basicsize */
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
    "plLODDist wrapper",                /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyLODDist_Methods,                  /* tp_methods */
    NULL,                               /* tp_members */
    pyLODDist_GetSet,                   /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyLODDist_new,                      /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyLODDist_Type() {
    if (PyType_Ready(&pyLODDist_Type) < 0)
        return NULL;

    Py_INCREF(&pyLODDist_Type);
    return (PyObject*)&pyLODDist_Type;
}

PyObject* pyLODDist_FromLODDist(plLODDist& dist) {
    pyLODDist* obj = PyObject_New(pyLODDist, &pyLODDist_Type);
    obj->fThis = &dist;
    return (PyObject*)obj;
}

}
