#include <Python.h>
#include <PRP/Avatar/plMatrixChannel.h>
#include "pyAGChannel.h"
#include "../pyCreatable.h"

extern "C" {

static PyObject* pyMatrixBlend_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyMatrixBlend* self = (pyMatrixBlend*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plMatrixBlend();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyMatrixBlend_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyMatrixBlend_FromMatrixBlend(plMatrixBlend::Convert(cre->fThis));
}

static PyMethodDef pyMatrixBlend_Methods[] = {
    { "Convert", (PyCFunction)pyMatrixBlend_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plMatrixBlend" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyMatrixBlend_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plMatrixBlend",           /* tp_name */
    sizeof(pyMatrixBlend),              /* tp_basicsize */
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
    "plMatrixBlend wrapper",            /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyMatrixBlend_Methods,              /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyMatrixBlend_new,                  /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyMatrixBlend_Type() {
    pyMatrixBlend_Type.tp_base = &pyMatrixChannel_Type;
    if (PyType_Ready(&pyMatrixBlend_Type) < 0)
        return NULL;

    Py_INCREF(&pyMatrixBlend_Type);
    return (PyObject*)&pyMatrixBlend_Type;
}

int pyMatrixBlend_Check(PyObject* obj) {
    if (obj->ob_type == &pyMatrixBlend_Type
        || PyType_IsSubtype(obj->ob_type, &pyMatrixBlend_Type))
        return 1;
    return 0;
}

PyObject* pyMatrixBlend_FromMatrixBlend(class plMatrixBlend* chan) {
    if (chan == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyMatrixBlend* pyobj = PyObject_New(pyMatrixBlend, &pyMatrixBlend_Type);
    pyobj->fThis = chan;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
