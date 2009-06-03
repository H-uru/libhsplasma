#include <PyPlasma.h>
#include <PRP/Region/hsBounds.h>
#include "pyBounds.h"
#include "Stream/pyStream.h"

extern "C" {

static void pyBounds_dealloc(pyBounds* self) {
    delete self->fThis;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static int pyBounds___init__(pyBounds* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pyBounds_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyBounds* self = (pyBounds*)type->tp_alloc(type, 0);
    if (self != NULL)
        self->fThis = new hsBounds();
    return (PyObject*)self;
}

static PyObject* pyBounds_ClassName(pyBounds* self) {
    return PyString_FromString(self->fThis->ClassName());
}

static PyObject* pyBounds_read(pyBounds* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects an hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects an hsStream");
        return NULL;
    }
    self->fThis->read(stream->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyBounds_write(pyBounds* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects an hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects an hsStream");
        return NULL;
    }
    self->fThis->write(stream->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyBounds_getType(pyBounds* self, void*) {
    return PyInt_FromLong(self->fThis->getType());
}

static int pyBounds_setType(pyBounds* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "type should be an int");
        return -1;
    }
    self->fThis->setType(PyInt_AsLong(value));
    return 0;
}

static PyMethodDef pyBounds_Methods[] = {
    { "ClassName", (PyCFunction)pyBounds_ClassName, METH_NOARGS,
      "Returns the RTTI Class name of this Bounds object" },
    { "read", (PyCFunction)pyBounds_read, METH_VARARGS,
      "Params: stream\n"
      "Read this Bounds object from the stream" },
    { "write", (PyCFunction)pyBounds_write, METH_VARARGS,
      "Params: stream\n"
      "Write this Bounds object to the stream" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyBounds_GetSet[] = {
    { "type", (getter)pyBounds_getType, (setter)pyBounds_setType, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyBounds_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.hsBounds",                /* tp_name */
    sizeof(pyBounds),                   /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pyBounds_dealloc,       /* tp_dealloc */
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

    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
    "hsBounds wrapper",                 /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyBounds_Methods,                   /* tp_methods */
    NULL,                               /* tp_members */
    pyBounds_GetSet,                    /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyBounds___init__,        /* tp_init */
    NULL,                               /* tp_alloc */
    pyBounds_new,                       /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyBounds_Type() {
    if (PyType_Ready(&pyBounds_Type) < 0)
        return NULL;

    Py_INCREF(&pyBounds_Type);
    return (PyObject*)&pyBounds_Type;
}

int pyBounds_Check(PyObject* obj) {
    if (obj->ob_type == &pyBounds_Type
        || PyType_IsSubtype(obj->ob_type, &pyBounds_Type))
        return 1;
    return 0;
}

PyObject* pyBounds_FromBounds(const hsBounds& bounds) {
    pyBounds* obj = PyObject_New(pyBounds, &pyBounds_Type);
    obj->fThis = new hsBounds(bounds);
    return (PyObject*)obj;
}

}
