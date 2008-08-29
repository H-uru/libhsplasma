#include <Python.h>
#include <PRP/Geometry/plGBufferGroup.h>
#include "pyGBufferGroup.h"

extern "C" {

static void pyGBufferCell_dealloc(pyGBufferCell* self) {
    delete self->fThis;
    self->ob_type->tp_free((PyObject*)self);
}

static int pyGBufferCell___init__(pyGBufferCell* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pyGBufferCell_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyGBufferCell* self = (pyGBufferCell*)type->tp_alloc(type, 0);
    if (self != NULL)
        self->fThis = new plGBufferCell();
    return (PyObject*)self;
}

static PyObject* pyGBufferCell_getVtxStart(pyGBufferCell* self, void*) {
    return PyInt_FromLong(self->fThis->fVtxStart);
}

static PyObject* pyGBufferCell_getColorStart(pyGBufferCell* self, void*) {
    return PyInt_FromLong(self->fThis->fColorStart);
}

static PyObject* pyGBufferCell_getLength(pyGBufferCell* self, void*) {
    return PyInt_FromLong(self->fThis->fLength);
}

static int pyGBufferCell_setVtxStart(pyGBufferCell* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "vtxStart should be an int");
        return -1;
    }
    self->fThis->fVtxStart = PyInt_AsLong(value);
    return 0;
}

static int pyGBufferCell_setColorStart(pyGBufferCell* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "colorStart should be an int");
        return -1;
    }
    self->fThis->fColorStart = PyInt_AsLong(value);
    return 0;
}

static int pyGBufferCell_setLength(pyGBufferCell* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "length should be an int");
        return -1;
    }
    self->fThis->fLength = PyInt_AsLong(value);
    return 0;
}

static PyGetSetDef pyGBufferCell_GetSet[] = {
    { "vtxStart", (getter)pyGBufferCell_getVtxStart, (setter)pyGBufferCell_setVtxStart, NULL, NULL },
    { "colorStart", (getter)pyGBufferCell_getColorStart, (setter)pyGBufferCell_setColorStart, NULL, NULL },
    { "length", (getter)pyGBufferCell_getLength, (setter)pyGBufferCell_setLength, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyGBufferCell_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plGBufferCell",           /* tp_name */
    sizeof(pyGBufferCell),              /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pyGBufferCell_dealloc,  /* tp_dealloc */
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
    "plGBufferCell wrapper",            /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyGBufferCell_GetSet,               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyGBufferCell___init__,   /* tp_init */
    NULL,                               /* tp_alloc */
    pyGBufferCell_new,                  /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyGBufferCell_Type() {
    if (PyType_Ready(&pyGBufferCell_Type) < 0)
        return NULL;

    Py_INCREF(&pyGBufferCell_Type);
    return (PyObject*)&pyGBufferCell_Type;
}

int pyGBufferCell_Check(PyObject* obj) {
    if (obj->ob_type == &pyGBufferCell_Type
        || PyType_IsSubtype(obj->ob_type, &pyGBufferCell_Type))
        return 1;
    return 0;
}

PyObject* pyGBufferCell_FromGBufferCell(const plGBufferCell& cell) {
    pyGBufferCell* pycell = PyObject_New(pyGBufferCell, &pyGBufferCell_Type);
    pycell->fThis = new plGBufferCell(cell);
    return (PyObject*)pycell;
}

}
