#include <PyPlasma.h>
#include <PRP/Avatar/plPointChannel.h>
#include "pyAGChannel.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyPointBlend_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyPointBlend* self = (pyPointBlend*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plPointBlend();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyPointBlend_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyPointBlend_FromPointBlend(plPointBlend::Convert(cre->fThis));
}

static PyMethodDef pyPointBlend_Methods[] = {
    { "Convert", (PyCFunction)pyPointBlend_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plPointBlend" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyPointBlend_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plPointBlend",            /* tp_name */
    sizeof(pyPointBlend),               /* tp_basicsize */
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
    "plPointBlend wrapper",             /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyPointBlend_Methods,               /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyPointBlend_new,                   /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyPointBlend_Type() {
    pyPointBlend_Type.tp_base = &pyPointChannel_Type;
    if (PyType_Ready(&pyPointBlend_Type) < 0)
        return NULL;

    Py_INCREF(&pyPointBlend_Type);
    return (PyObject*)&pyPointBlend_Type;
}

int pyPointBlend_Check(PyObject* obj) {
    if (obj->ob_type == &pyPointBlend_Type
        || PyType_IsSubtype(obj->ob_type, &pyPointBlend_Type))
        return 1;
    return 0;
}

PyObject* pyPointBlend_FromPointBlend(class plPointBlend* chan) {
    if (chan == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyPointBlend* pyobj = PyObject_New(pyPointBlend, &pyPointBlend_Type);
    pyobj->fThis = chan;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
