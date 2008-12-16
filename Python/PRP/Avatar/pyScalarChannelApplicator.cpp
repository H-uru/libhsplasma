#include <Python.h>
#include <PRP/Avatar/plScalarChannel.h>
#include "pyAGApplicator.h"
#include "../pyCreatable.h"

extern "C" {

static PyObject* pyScalarChannelApplicator_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyScalarChannelApplicator* self = (pyScalarChannelApplicator*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plScalarChannelApplicator();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyScalarChannelApplicator_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyScalarChannelApplicator_FromScalarChannelApplicator(plScalarChannelApplicator::Convert(cre->fThis));
}

static PyMethodDef pyScalarChannelApplicator_Methods[] = {
    { "Convert", (PyCFunction)pyScalarChannelApplicator_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plScalarChannelApplicator" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyScalarChannelApplicator_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plScalarChannelApplicator", /* tp_name */
    sizeof(pyScalarChannelApplicator),   /* tp_basicsize */
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
    "plScalarChannelApplicator wrapper", /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyScalarChannelApplicator_Methods,   /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyScalarChannelApplicator_new,       /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyScalarChannelApplicator_Type() {
    pyScalarChannelApplicator_Type.tp_base = &pyAGApplicator_Type;
    if (PyType_Ready(&pyScalarChannelApplicator_Type) < 0)
        return NULL;

    Py_INCREF(&pyScalarChannelApplicator_Type);
    return (PyObject*)&pyScalarChannelApplicator_Type;
}

int pyScalarChannelApplicator_Check(PyObject* obj) {
    if (obj->ob_type == &pyScalarChannelApplicator_Type
        || PyType_IsSubtype(obj->ob_type, &pyScalarChannelApplicator_Type))
        return 1;
    return 0;
}

PyObject* pyScalarChannelApplicator_FromScalarChannelApplicator(class plScalarChannelApplicator* app) {
    if (app == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyScalarChannelApplicator* pyobj = PyObject_New(pyScalarChannelApplicator, &pyScalarChannelApplicator_Type);
    pyobj->fThis = app;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
