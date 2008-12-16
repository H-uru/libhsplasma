#include <Python.h>
#include <PRP/Avatar/plPointChannel.h>
#include "pyAGChannel.h"
#include "../pyCreatable.h"

extern "C" {

static PyObject* pyPointTimeScale_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyPointTimeScale* self = (pyPointTimeScale*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plPointTimeScale();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyPointTimeScale_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyPointTimeScale_FromPointTimeScale(plPointTimeScale::Convert(cre->fThis));
}

static PyMethodDef pyPointTimeScale_Methods[] = {
    { "Convert", (PyCFunction)pyPointTimeScale_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plPointTimeScale" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyPointTimeScale_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plPointTimeScale",            /* tp_name */
    sizeof(pyPointTimeScale),               /* tp_basicsize */
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
    "plPointTimeScale wrapper",             /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyPointTimeScale_Methods,               /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyPointTimeScale_new,                   /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyPointTimeScale_Type() {
    pyPointTimeScale_Type.tp_base = &pyPointChannel_Type;
    if (PyType_Ready(&pyPointTimeScale_Type) < 0)
        return NULL;

    Py_INCREF(&pyPointTimeScale_Type);
    return (PyObject*)&pyPointTimeScale_Type;
}

int pyPointTimeScale_Check(PyObject* obj) {
    if (obj->ob_type == &pyPointTimeScale_Type
        || PyType_IsSubtype(obj->ob_type, &pyPointTimeScale_Type))
        return 1;
    return 0;
}

PyObject* pyPointTimeScale_FromPointTimeScale(class plPointTimeScale* chan) {
    if (chan == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyPointTimeScale* pyobj = PyObject_New(pyPointTimeScale, &pyPointTimeScale_Type);
    pyobj->fThis = chan;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
