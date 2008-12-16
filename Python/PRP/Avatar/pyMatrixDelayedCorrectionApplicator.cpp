#include <Python.h>
#include <PRP/Avatar/plMatrixChannel.h>
#include "pyAGApplicator.h"
#include "../pyCreatable.h"

extern "C" {

static PyObject* pyMatrixDelayedCorrectionApplicator_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyMatrixDelayedCorrectionApplicator* self = (pyMatrixDelayedCorrectionApplicator*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plMatrixDelayedCorrectionApplicator();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyMatrixDelayedCorrectionApplicator_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyMatrixDelayedCorrectionApplicator_FromMatrixDelayedCorrectionApplicator(plMatrixDelayedCorrectionApplicator::Convert(cre->fThis));
}

static PyMethodDef pyMatrixDelayedCorrectionApplicator_Methods[] = {
    { "Convert", (PyCFunction)pyMatrixDelayedCorrectionApplicator_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plMatrixDelayedCorrectionApplicator" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyMatrixDelayedCorrectionApplicator_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plMatrixDelayedCorrectionApplicator", /* tp_name */
    sizeof(pyMatrixDelayedCorrectionApplicator),   /* tp_basicsize */
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
    "plMatrixDelayedCorrectionApplicator wrapper", /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyMatrixDelayedCorrectionApplicator_Methods,   /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyMatrixDelayedCorrectionApplicator_new,       /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyMatrixDelayedCorrectionApplicator_Type() {
    pyMatrixDelayedCorrectionApplicator_Type.tp_base = &pyMatrixChannelApplicator_Type;
    if (PyType_Ready(&pyMatrixDelayedCorrectionApplicator_Type) < 0)
        return NULL;

    Py_INCREF(&pyMatrixDelayedCorrectionApplicator_Type);
    return (PyObject*)&pyMatrixDelayedCorrectionApplicator_Type;
}

int pyMatrixDelayedCorrectionApplicator_Check(PyObject* obj) {
    if (obj->ob_type == &pyMatrixDelayedCorrectionApplicator_Type
        || PyType_IsSubtype(obj->ob_type, &pyMatrixDelayedCorrectionApplicator_Type))
        return 1;
    return 0;
}

PyObject* pyMatrixDelayedCorrectionApplicator_FromMatrixDelayedCorrectionApplicator(class plMatrixDelayedCorrectionApplicator* app) {
    if (app == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyMatrixDelayedCorrectionApplicator* pyobj = PyObject_New(pyMatrixDelayedCorrectionApplicator, &pyMatrixDelayedCorrectionApplicator_Type);
    pyobj->fThis = app;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
