#include <PyPlasma.h>
#include <PRP/Animation/plController.h>
#include "pyController.h"
#include "PRP/pyCreatable.h"

extern "C" {

static int pyCompoundController___init__(pyCompoundController* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pyCompoundController_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyCompoundController* self = (pyCompoundController*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plCompoundController();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyCompoundController_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyCompoundController_FromCompoundController(plCompoundController::Convert(cre->fThis));
}

static PyObject* pyCompoundController_getX(pyCompoundController* self, void*) {
    return pyController_FromController(self->fThis->getXController());
}

static PyObject* pyCompoundController_getY(pyCompoundController* self, void*) {
    return pyController_FromController(self->fThis->getYController());
}

static PyObject* pyCompoundController_getZ(pyCompoundController* self, void*) {
    return pyController_FromController(self->fThis->getZController());
}

static int pyCompoundController_setX(pyCompoundController* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setXController(NULL);
        return 0;
    }
    if (!pyController_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "X should be a plController");
        return -1;
    }
    self->fThis->setXController(((pyController*)value)->fThis);
    ((pyController*)value)->fPyOwned = false;
    return 0;
}

static int pyCompoundController_setY(pyCompoundController* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setYController(NULL);
        return 0;
    }
    if (!pyController_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "Y should be a plController");
        return -1;
    }
    self->fThis->setYController(((pyController*)value)->fThis);
    ((pyController*)value)->fPyOwned = false;
    return 0;
}

static int pyCompoundController_setZ(pyCompoundController* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setZController(NULL);
        return 0;
    }
    if (!pyController_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "Z should be a plController");
        return -1;
    }
    self->fThis->setZController(((pyController*)value)->fThis);
    ((pyController*)value)->fPyOwned = false;
    return 0;
}

static PyMethodDef pyCompoundController_Methods[] = {
    { "Convert", (PyCFunction)pyCompoundController_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plCompoundController" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyCompoundController_GetSet[] = {
    { "X", (getter)pyCompoundController_getX, (setter)pyCompoundController_setX, NULL, NULL },
    { "Y", (getter)pyCompoundController_getY, (setter)pyCompoundController_setY, NULL, NULL },
    { "Z", (getter)pyCompoundController_getZ, (setter)pyCompoundController_setZ, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyCompoundController_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plCompoundController",    /* tp_name */
    sizeof(pyCompoundController),       /* tp_basicsize */
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
    "plCompoundController wrapper",     /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyCompoundController_Methods,       /* tp_methods */
    NULL,                               /* tp_members */
    pyCompoundController_GetSet,        /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyCompoundController___init__, /* tp_init */
    NULL,                               /* tp_alloc */
    pyCompoundController_new,           /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyCompoundController_Type() {
    pyCompoundController_Type.tp_base = &pyController_Type;
    if (PyType_Ready(&pyCompoundController_Type) < 0)
        return NULL;

    Py_INCREF(&pyCompoundController_Type);
    return (PyObject*)&pyCompoundController_Type;
}

int pyCompoundController_Check(PyObject* obj) {
    if (obj->ob_type == &pyCompoundController_Type
        || PyType_IsSubtype(obj->ob_type, &pyCompoundController_Type))
        return 1;
    return 0;
}

PyObject* pyCompoundController_FromCompoundController(class plCompoundController* controller) {
    if (controller == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyCompoundController* pyobj = PyObject_New(pyCompoundController, &pyCompoundController_Type);
    pyobj->fThis = controller;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
