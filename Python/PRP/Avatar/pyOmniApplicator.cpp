#include <Python.h>
#include <PRP/Avatar/plAGApplicator.h>
#include "pyAGApplicator.h"
#include "../pyCreatable.h"

extern "C" {

static PyObject* pyOmniApplicator_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyOmniApplicator* self = (pyOmniApplicator*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plOmniApplicator();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyOmniApplicator_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyOmniApplicator_FromOmniApplicator(plOmniApplicator::Convert(cre->fThis));
}

static PyMethodDef pyOmniApplicator_Methods[] = {
    { "Convert", (PyCFunction)pyOmniApplicator_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plOmniApplicator" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyOmniApplicator_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plOmniApplicator", /* tp_name */
    sizeof(pyOmniApplicator),   /* tp_basicsize */
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

    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
    "plOmniApplicator wrapper", /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyOmniApplicator_Methods,   /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyOmniApplicator_new,       /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyOmniApplicator_Type() {
    pyOmniApplicator_Type.tp_base = &pyAGApplicator_Type;
    if (PyType_Ready(&pyOmniApplicator_Type) < 0)
        return NULL;

    Py_INCREF(&pyOmniApplicator_Type);
    return (PyObject*)&pyOmniApplicator_Type;
}

int pyOmniApplicator_Check(PyObject* obj) {
    if (obj->ob_type == &pyOmniApplicator_Type
        || PyType_IsSubtype(obj->ob_type, &pyOmniApplicator_Type))
        return 1;
    return 0;
}

PyObject* pyOmniApplicator_FromOmniApplicator(class plOmniApplicator* app) {
    if (app == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyOmniApplicator* pyobj = PyObject_New(pyOmniApplicator, &pyOmniApplicator_Type);
    pyobj->fThis = app;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
