#include <Python.h>
#include <PRP/Audio/plAudible.h>
#include "pyAudible.h"
#include "../KeyedObject/pyKeyedObject.h"
#include "../pyCreatable.h"

extern "C" {

static PyObject* pyAudible_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyAudible* self = (pyAudible*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plAudible();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyAudible_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyAudible_FromAudible(plAudible::Convert(cre->fThis));
}

static PyMethodDef pyAudible_Methods[] = {
    { "Convert", (PyCFunction)pyAudible_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plAudible" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyAudible_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plAudible",               /* tp_name */
    sizeof(pyAudible),                  /* tp_basicsize */
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
    "plAudible wrapper",                /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyAudible_Methods,                  /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyAudible_new,                      /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyAudible_Type() {
    pyAudible_Type.tp_base = &pyKeyedObject_Type;
    if (PyType_Ready(&pyAudible_Type) < 0)
        return NULL;

    Py_INCREF(&pyAudible_Type);
    return (PyObject*)&pyAudible_Type;
}

int pyAudible_Check(PyObject* obj) {
    if (obj->ob_type == &pyAudible_Type
        || PyType_IsSubtype(obj->ob_type, &pyAudible_Type))
        return 1;
    return 0;
}

PyObject* pyAudible_FromAudible(plAudible* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyAudible* pyobj = PyObject_New(pyAudible, &pyAudible_Type);
    pyobj->fThis = obj;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}