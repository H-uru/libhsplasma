#include <Python.h>
#include <PRP/Animation/plPosController.h>
#include "pyPosController.h"
#include "pyLeafController.h"
#include "../pyCreatable.h"

extern "C" {

static int pySimplePosController___init__(pySimplePosController* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pySimplePosController_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pySimplePosController* self = (pySimplePosController*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plSimplePosController();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pySimplePosController_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pySimplePosController_FromSimplePosController(plSimplePosController::Convert(cre->fThis));
}

static PyObject* pySimplePosController_getPosition(pySimplePosController* self, void*) {
    return pyPoint3Controller_FromPoint3Controller(self->fThis->getPosition());
}

static int pySimplePosController_setPosition(pySimplePosController* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setPosition(NULL);
        return 0;
    }
    if (!pyPoint3Controller_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "position should be a plPoint3Controller");
        return -1;
    }
    self->fThis->setPosition(((pyPoint3Controller*)value)->fThis);
    ((pyPoint3Controller*)value)->fPyOwned = false;
    return 0;
}

static PyMethodDef pySimplePosController_Methods[] = {
    { "Convert", (PyCFunction)pySimplePosController_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plSimplePosController" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pySimplePosController_GetSet[] = {
    { "position", (getter)pySimplePosController_getPosition, (setter)pySimplePosController_setPosition, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pySimplePosController_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plSimplePosController",   /* tp_name */
    sizeof(pySimplePosController),      /* tp_basicsize */
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
    "plSimplePosController wrapper",    /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pySimplePosController_Methods,      /* tp_methods */
    NULL,                               /* tp_members */
    pySimplePosController_GetSet,       /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pySimplePosController___init__, /* tp_init */
    NULL,                               /* tp_alloc */
    pySimplePosController_new,          /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pySimplePosController_Type() {
    pySimplePosController_Type.tp_base = &pyPosController_Type;
    if (PyType_Ready(&pySimplePosController_Type) < 0)
        return NULL;

    Py_INCREF(&pySimplePosController_Type);
    return (PyObject*)&pySimplePosController_Type;
}

int pySimplePosController_Check(PyObject* obj) {
    if (obj->ob_type == &pySimplePosController_Type
        || PyType_IsSubtype(obj->ob_type, &pySimplePosController_Type))
        return 1;
    return 0;
}

PyObject* pySimplePosController_FromSimplePosController(class plSimplePosController* controller) {
    if (controller == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pySimplePosController* pyobj = PyObject_New(pySimplePosController, &pySimplePosController_Type);
    pyobj->fThis = controller;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
