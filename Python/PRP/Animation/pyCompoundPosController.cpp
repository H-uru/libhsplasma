#include <Python.h>
#include <PRP/Animation/plPosController.h>
#include "pyPosController.h"
#include "pyLeafController.h"
#include "../pyCreatable.h"

extern "C" {

static int pyCompoundPosController___init__(pyCompoundPosController* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pyCompoundPosController_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyCompoundPosController* self = (pyCompoundPosController*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plCompoundPosController();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyCompoundPosController_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyCompoundPosController_FromCompoundPosController(plCompoundPosController::Convert(cre->fThis));
}

static PyObject* pyCompoundPosController_getX(pyCompoundPosController* self, void*) {
    return pyScalarController_FromScalarController(self->fThis->getX());
}

static PyObject* pyCompoundPosController_getY(pyCompoundPosController* self, void*) {
    return pyScalarController_FromScalarController(self->fThis->getY());
}

static PyObject* pyCompoundPosController_getZ(pyCompoundPosController* self, void*) {
    return pyScalarController_FromScalarController(self->fThis->getZ());
}

static int pyCompoundPosController_setX(pyCompoundPosController* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setX(NULL);
        return 0;
    }
    if (!pyScalarController_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "X should be a plScalarController");
        return -1;
    }
    self->fThis->setX(((pyScalarController*)value)->fThis);
    ((pyScalarController*)value)->fPyOwned = false;
    return 0;
}

static int pyCompoundPosController_setY(pyCompoundPosController* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setY(NULL);
        return 0;
    }
    if (!pyScalarController_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "Y should be a plScalarController");
        return -1;
    }
    self->fThis->setY(((pyScalarController*)value)->fThis);
    ((pyScalarController*)value)->fPyOwned = false;
    return 0;
}

static int pyCompoundPosController_setZ(pyCompoundPosController* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setZ(NULL);
        return 0;
    }
    if (!pyScalarController_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "Z should be a plScalarController");
        return -1;
    }
    self->fThis->setZ(((pyScalarController*)value)->fThis);
    ((pyScalarController*)value)->fPyOwned = false;
    return 0;
}

static PyMethodDef pyCompoundPosController_Methods[] = {
    { "Convert", (PyCFunction)pyCompoundPosController_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plCompoundPosController" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyCompoundPosController_GetSet[] = {
    { "X", (getter)pyCompoundPosController_getX, (setter)pyCompoundPosController_setX, NULL, NULL },
    { "Y", (getter)pyCompoundPosController_getY, (setter)pyCompoundPosController_setY, NULL, NULL },
    { "Z", (getter)pyCompoundPosController_getZ, (setter)pyCompoundPosController_setZ, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyCompoundPosController_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plCompoundPosController", /* tp_name */
    sizeof(pyCompoundPosController),    /* tp_basicsize */
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
    "plCompoundPosController wrapper",  /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyCompoundPosController_Methods,    /* tp_methods */
    NULL,                               /* tp_members */
    pyCompoundPosController_GetSet,     /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyCompoundPosController___init__, /* tp_init */
    NULL,                               /* tp_alloc */
    pyCompoundPosController_new,        /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyCompoundPosController_Type() {
    pyCompoundPosController_Type.tp_base = &pyPosController_Type;
    if (PyType_Ready(&pyCompoundPosController_Type) < 0)
        return NULL;

    Py_INCREF(&pyCompoundPosController_Type);
    return (PyObject*)&pyCompoundPosController_Type;
}

int pyCompoundPosController_Check(PyObject* obj) {
    if (obj->ob_type == &pyCompoundPosController_Type
        || PyType_IsSubtype(obj->ob_type, &pyCompoundPosController_Type))
        return 1;
    return 0;
}

PyObject* pyCompoundPosController_FromCompoundPosController(class plCompoundPosController* controller) {
    if (controller == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyCompoundPosController* pyobj = PyObject_New(pyCompoundPosController, &pyCompoundPosController_Type);
    pyobj->fThis = controller;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
