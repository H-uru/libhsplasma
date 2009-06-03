#include <PyPlasma.h>
#include <PRP/Animation/plATCEaseCurves.h>
#include "pyATCEaseCurves.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyConstAccelEaseCurve_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyConstAccelEaseCurve* self = (pyConstAccelEaseCurve*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plConstAccelEaseCurve();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyConstAccelEaseCurve_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyConstAccelEaseCurve_FromConstAccelEaseCurve(plConstAccelEaseCurve::Convert(cre->fThis));
}

static PyMethodDef pyConstAccelEaseCurve_Methods[] = {
    { "Convert", (PyCFunction)pyConstAccelEaseCurve_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plConstAccelEaseCurve" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyConstAccelEaseCurve_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plConstAccelEaseCurve",   /* tp_name */
    sizeof(pyConstAccelEaseCurve),      /* tp_basicsize */
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
    "plConstAccelEaseCurve wrapper",    /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyConstAccelEaseCurve_Methods,      /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyConstAccelEaseCurve_new,          /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyConstAccelEaseCurve_Type() {
    pyConstAccelEaseCurve_Type.tp_base = &pyATCEaseCurve_Type;
    if (PyType_Ready(&pyConstAccelEaseCurve_Type) < 0)
        return NULL;

    Py_INCREF(&pyConstAccelEaseCurve_Type);
    return (PyObject*)&pyConstAccelEaseCurve_Type;
}

int pyConstAccelEaseCurve_Check(PyObject* obj) {
    if (obj->ob_type == &pyConstAccelEaseCurve_Type
        || PyType_IsSubtype(obj->ob_type, &pyConstAccelEaseCurve_Type))
        return 1;
    return 0;
}

PyObject* pyConstAccelEaseCurve_FromConstAccelEaseCurve(class plConstAccelEaseCurve* curve) {
    if (curve == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyConstAccelEaseCurve* pyobj = PyObject_New(pyConstAccelEaseCurve, &pyConstAccelEaseCurve_Type);
    pyobj->fThis = curve;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
