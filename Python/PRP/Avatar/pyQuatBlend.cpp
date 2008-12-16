#include <Python.h>
#include <PRP/Avatar/plQuatChannel.h>
#include "pyAGChannel.h"
#include "../pyCreatable.h"

extern "C" {

static PyObject* pyQuatBlend_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyQuatBlend* self = (pyQuatBlend*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plQuatBlend();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyQuatBlend_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyQuatBlend_FromQuatBlend(plQuatBlend::Convert(cre->fThis));
}

static PyMethodDef pyQuatBlend_Methods[] = {
    { "Convert", (PyCFunction)pyQuatBlend_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plQuatBlend" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyQuatBlend_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plQuatBlend",             /* tp_name */
    sizeof(pyQuatBlend),                /* tp_basicsize */
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
    "plQuatBlend wrapper",              /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyQuatBlend_Methods,                /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyQuatBlend_new,                    /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyQuatBlend_Type() {
    pyQuatBlend_Type.tp_base = &pyQuatChannel_Type;
    if (PyType_Ready(&pyQuatBlend_Type) < 0)
        return NULL;

    Py_INCREF(&pyQuatBlend_Type);
    return (PyObject*)&pyQuatBlend_Type;
}

int pyQuatBlend_Check(PyObject* obj) {
    if (obj->ob_type == &pyQuatBlend_Type
        || PyType_IsSubtype(obj->ob_type, &pyQuatBlend_Type))
        return 1;
    return 0;
}

PyObject* pyQuatBlend_FromQuatBlend(class plQuatBlend* chan) {
    if (chan == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyQuatBlend* pyobj = PyObject_New(pyQuatBlend, &pyQuatBlend_Type);
    pyobj->fThis = chan;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
