#include <Python.h>
#include <PRP/Animation/plKeyControllers.h>
#include "pyLeafController.h"
#include "../pyCreatable.h"

extern "C" {

static int pyMatrix44Controller___init__(pyMatrix44Controller* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pyMatrix44Controller_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyMatrix44Controller* self = (pyMatrix44Controller*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plMatrix44Controller();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyMatrix44Controller_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyMatrix44Controller_FromMatrix44Controller(plMatrix44Controller::Convert(cre->fThis));
}

static PyMethodDef pyMatrix44Controller_Methods[] = {
    { "Convert", (PyCFunction)pyMatrix44Controller_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plMatrix44Controller" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyMatrix44Controller_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plMatrix44Controller",    /* tp_name */
    sizeof(pyMatrix44Controller),       /* tp_basicsize */
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
    "plMatrix44Controller wrapper",     /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyMatrix44Controller_Methods,       /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyMatrix44Controller___init__, /* tp_init */
    NULL,                               /* tp_alloc */
    pyMatrix44Controller_new,           /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyMatrix44Controller_Type() {
    pyMatrix44Controller_Type.tp_base = &pyLeafController_Type;
    if (PyType_Ready(&pyMatrix44Controller_Type) < 0)
        return NULL;

    Py_INCREF(&pyMatrix44Controller_Type);
    return (PyObject*)&pyMatrix44Controller_Type;
}

int pyMatrix44Controller_Check(PyObject* obj) {
    if (obj->ob_type == &pyMatrix44Controller_Type
        || PyType_IsSubtype(obj->ob_type, &pyMatrix44Controller_Type))
        return 1;
    return 0;
}

PyObject* pyMatrix44Controller_FromMatrix44Controller(class plMatrix44Controller* controller) {
    if (controller == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyMatrix44Controller* pyobj = PyObject_New(pyMatrix44Controller, &pyMatrix44Controller_Type);
    pyobj->fThis = controller;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
