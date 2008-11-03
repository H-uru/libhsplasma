#include <Python.h>
#include <PRP/Animation/plKeyControllers.h>
#include "pyLeafController.h"
#include "../pyCreatable.h"

extern "C" {

static int pyScaleValueController___init__(pyScaleValueController* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pyScaleValueController_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyScaleValueController* self = (pyScaleValueController*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plScaleValueController();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyScaleValueController_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyScaleValueController_FromScaleValueController(plScaleValueController::Convert(cre->fThis));
}

static PyMethodDef pyScaleValueController_Methods[] = {
    { "Convert", (PyCFunction)pyScaleValueController_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plScaleValueController" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyScaleValueController_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plScaleValueController",  /* tp_name */
    sizeof(pyScaleValueController),     /* tp_basicsize */
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
    "plScaleValueController wrapper",   /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyScaleValueController_Methods,     /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyScaleValueController___init__, /* tp_init */
    NULL,                               /* tp_alloc */
    pyScaleValueController_new,         /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyScaleValueController_Type() {
    pyScaleValueController_Type.tp_base = &pyLeafController_Type;
    if (PyType_Ready(&pyScaleValueController_Type) < 0)
        return NULL;

    Py_INCREF(&pyScaleValueController_Type);
    return (PyObject*)&pyScaleValueController_Type;
}

int pyScaleValueController_Check(PyObject* obj) {
    if (obj->ob_type == &pyScaleValueController_Type
        || PyType_IsSubtype(obj->ob_type, &pyScaleValueController_Type))
        return 1;
    return 0;
}

PyObject* pyScaleValueController_FromScaleValueController(class plScaleValueController* controller) {
    if (controller == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyScaleValueController* pyobj = PyObject_New(pyScaleValueController, &pyScaleValueController_Type);
    pyobj->fThis = controller;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
