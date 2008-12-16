#include <Python.h>
#include <PRP/Avatar/plQuatChannel.h>
#include "pyAGApplicator.h"
#include "../pyCreatable.h"

extern "C" {

static PyObject* pyQuatChannelApplicator_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyQuatChannelApplicator* self = (pyQuatChannelApplicator*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plQuatChannelApplicator();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyQuatChannelApplicator_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyQuatChannelApplicator_FromQuatChannelApplicator(plQuatChannelApplicator::Convert(cre->fThis));
}

static PyMethodDef pyQuatChannelApplicator_Methods[] = {
    { "Convert", (PyCFunction)pyQuatChannelApplicator_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plQuatChannelApplicator" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyQuatChannelApplicator_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plQuatChannelApplicator", /* tp_name */
    sizeof(pyQuatChannelApplicator),   /* tp_basicsize */
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
    "plQuatChannelApplicator wrapper", /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyQuatChannelApplicator_Methods,   /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyQuatChannelApplicator_new,       /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyQuatChannelApplicator_Type() {
    pyQuatChannelApplicator_Type.tp_base = &pyAGApplicator_Type;
    if (PyType_Ready(&pyQuatChannelApplicator_Type) < 0)
        return NULL;

    Py_INCREF(&pyQuatChannelApplicator_Type);
    return (PyObject*)&pyQuatChannelApplicator_Type;
}

int pyQuatChannelApplicator_Check(PyObject* obj) {
    if (obj->ob_type == &pyQuatChannelApplicator_Type
        || PyType_IsSubtype(obj->ob_type, &pyQuatChannelApplicator_Type))
        return 1;
    return 0;
}

PyObject* pyQuatChannelApplicator_FromQuatChannelApplicator(class plQuatChannelApplicator* app) {
    if (app == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyQuatChannelApplicator* pyobj = PyObject_New(pyQuatChannelApplicator, &pyQuatChannelApplicator_Type);
    pyobj->fThis = app;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
