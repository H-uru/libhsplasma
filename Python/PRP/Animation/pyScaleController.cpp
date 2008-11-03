#include <Python.h>
#include <PRP/Animation/plScaleController.h>
#include "pyScaleController.h"
#include "pyController.h"
#include "../pyCreatable.h"

extern "C" {

static PyObject* pyScaleController_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "plScaleController is abstract");
    return NULL;
}

static PyObject* pyScaleController_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyScaleController_FromScaleController(plScaleController::Convert(cre->fThis));
}

static PyObject* pyScaleController_getType(pyScaleController* self, void*) {
    return PyInt_FromLong(self->fThis->getType());
}

static int pyScaleController_setType(pyScaleController* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "type is read-only");
    return -1;
}

static PyMethodDef pyScaleController_Methods[] = {
    { "Convert", (PyCFunction)pyScaleController_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plScaleController" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyScaleController_GetSet[] = {
    { "type", (getter)pyScaleController_getType, (setter)pyScaleController_setType, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyScaleController_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plScaleController",       /* tp_name */
    sizeof(pyScaleController),          /* tp_basicsize */
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
    "plScaleController wrapper",        /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyScaleController_Methods,          /* tp_methods */
    NULL,                               /* tp_members */
    pyScaleController_GetSet,           /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyScaleController_new,              /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyScaleController_Type() {
    pyScaleController_Type.tp_base = &pyController_Type;
    if (PyType_Ready(&pyScaleController_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyScaleController_Type.tp_dict, "kSimple",
                         PyInt_FromLong(plScaleController::kSimple));

    Py_INCREF(&pyScaleController_Type);
    return (PyObject*)&pyScaleController_Type;
}

int pyScaleController_Check(PyObject* obj) {
    if (obj->ob_type == &pyScaleController_Type
        || PyType_IsSubtype(obj->ob_type, &pyScaleController_Type))
        return 1;
    return 0;
}

PyObject* pyScaleController_FromScaleController(class plScaleController* controller) {
    if (controller == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyScaleController* pyobj = PyObject_New(pyScaleController, &pyScaleController_Type);
    pyobj->fThis = controller;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
