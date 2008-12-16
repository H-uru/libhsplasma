#include <Python.h>
#include <PRP/Avatar/plScalarChannel.h>
#include "pyAGChannel.h"
#include "../pyCreatable.h"

extern "C" {

static PyObject* pyScalarConstant_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyScalarConstant* self = (pyScalarConstant*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plScalarConstant();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyScalarConstant_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyScalarConstant_FromScalarConstant(plScalarConstant::Convert(cre->fThis));
}

static PyMethodDef pyScalarConstant_Methods[] = {
    { "Convert", (PyCFunction)pyScalarConstant_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plScalarConstant" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyScalarConstant_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plScalarConstant",           /* tp_name */
    sizeof(pyScalarConstant),              /* tp_basicsize */
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
    "plScalarConstant wrapper",            /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyScalarConstant_Methods,              /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyScalarConstant_new,                  /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyScalarConstant_Type() {
    pyScalarConstant_Type.tp_base = &pyScalarChannel_Type;
    if (PyType_Ready(&pyScalarConstant_Type) < 0)
        return NULL;

    Py_INCREF(&pyScalarConstant_Type);
    return (PyObject*)&pyScalarConstant_Type;
}

int pyScalarConstant_Check(PyObject* obj) {
    if (obj->ob_type == &pyScalarConstant_Type
        || PyType_IsSubtype(obj->ob_type, &pyScalarConstant_Type))
        return 1;
    return 0;
}

PyObject* pyScalarConstant_FromScalarConstant(class plScalarConstant* chan) {
    if (chan == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyScalarConstant* pyobj = PyObject_New(pyScalarConstant, &pyScalarConstant_Type);
    pyobj->fThis = chan;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
