#include <Python.h>
#include <PRP/Avatar/plMatrixChannel.h>
#include "pyAGApplicator.h"
#include "../pyCreatable.h"

extern "C" {

static PyObject* pyMatrixChannelApplicator_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyMatrixChannelApplicator* self = (pyMatrixChannelApplicator*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plMatrixChannelApplicator();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyMatrixChannelApplicator_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyMatrixChannelApplicator_FromMatrixChannelApplicator(plMatrixChannelApplicator::Convert(cre->fThis));
}

static PyMethodDef pyMatrixChannelApplicator_Methods[] = {
    { "Convert", (PyCFunction)pyMatrixChannelApplicator_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plMatrixChannelApplicator" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyMatrixChannelApplicator_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plMatrixChannelApplicator", /* tp_name */
    sizeof(pyMatrixChannelApplicator),   /* tp_basicsize */
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
    "plMatrixChannelApplicator wrapper", /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyMatrixChannelApplicator_Methods,   /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyMatrixChannelApplicator_new,       /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyMatrixChannelApplicator_Type() {
    pyMatrixChannelApplicator_Type.tp_base = &pyAGApplicator_Type;
    if (PyType_Ready(&pyMatrixChannelApplicator_Type) < 0)
        return NULL;

    Py_INCREF(&pyMatrixChannelApplicator_Type);
    return (PyObject*)&pyMatrixChannelApplicator_Type;
}

int pyMatrixChannelApplicator_Check(PyObject* obj) {
    if (obj->ob_type == &pyMatrixChannelApplicator_Type
        || PyType_IsSubtype(obj->ob_type, &pyMatrixChannelApplicator_Type))
        return 1;
    return 0;
}

PyObject* pyMatrixChannelApplicator_FromMatrixChannelApplicator(class plMatrixChannelApplicator* app) {
    if (app == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyMatrixChannelApplicator* pyobj = PyObject_New(pyMatrixChannelApplicator, &pyMatrixChannelApplicator_Type);
    pyobj->fThis = app;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
