#include <PyPlasma.h>
#include <PRP/Animation/plKeyControllers.h>
#include "pyLeafController.h"
#include "PRP/pyCreatable.h"

extern "C" {

static int pyQuatController___init__(pyQuatController* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pyQuatController_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyQuatController* self = (pyQuatController*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plQuatController();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyQuatController_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyQuatController_FromQuatController(plQuatController::Convert(cre->fThis));
}

static PyMethodDef pyQuatController_Methods[] = {
    { "Convert", (PyCFunction)pyQuatController_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plQuatController" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyQuatController_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plQuatController",        /* tp_name */
    sizeof(pyQuatController),           /* tp_basicsize */
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
    "plQuatController wrapper",         /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyQuatController_Methods,           /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyQuatController___init__, /* tp_init */
    NULL,                               /* tp_alloc */
    pyQuatController_new,               /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyQuatController_Type() {
    pyQuatController_Type.tp_base = &pyLeafController_Type;
    if (PyType_Ready(&pyQuatController_Type) < 0)
        return NULL;

    Py_INCREF(&pyQuatController_Type);
    return (PyObject*)&pyQuatController_Type;
}

int pyQuatController_Check(PyObject* obj) {
    if (obj->ob_type == &pyQuatController_Type
        || PyType_IsSubtype(obj->ob_type, &pyQuatController_Type))
        return 1;
    return 0;
}

PyObject* pyQuatController_FromQuatController(class plQuatController* controller) {
    if (controller == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyQuatController* pyobj = PyObject_New(pyQuatController, &pyQuatController_Type);
    pyobj->fThis = controller;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
