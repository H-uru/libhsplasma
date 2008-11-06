#include <Python.h>
#include <PRP/Animation/plATCEaseCurves.h>
#include "pyATCEaseCurves.h"
#include "../pyCreatable.h"

extern "C" {

static PyObject* pyATCEaseCurve_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyATCEaseCurve* self = (pyATCEaseCurve*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plATCEaseCurve();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyATCEaseCurve_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyATCEaseCurve_FromATCEaseCurve(plATCEaseCurve::Convert(cre->fThis));
}

static PyObject* pyATCEaseCurve_getStartSpeed(pyATCEaseCurve* self, void*) {
    return PyFloat_FromDouble(self->fThis->getStartSpeed());
}

static PyObject* pyATCEaseCurve_getSpeed(pyATCEaseCurve* self, void*) {
    return PyFloat_FromDouble(self->fThis->getSpeed());
}

static PyObject* pyATCEaseCurve_getMinLength(pyATCEaseCurve* self, void*) {
    return PyFloat_FromDouble(self->fThis->getMinLength());
}

static PyObject* pyATCEaseCurve_getMaxLength(pyATCEaseCurve* self, void*) {
    return PyFloat_FromDouble(self->fThis->getMaxLength());
}

static PyObject* pyATCEaseCurve_getLength(pyATCEaseCurve* self, void*) {
    return PyFloat_FromDouble(self->fThis->getLength());
}

static PyObject* pyATCEaseCurve_getBegin(pyATCEaseCurve* self, void*) {
    return PyFloat_FromDouble(self->fThis->getBeginWorldTime());
}

static int pyATCEaseCurve_setStartSpeed(pyATCEaseCurve* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "startSpeed should be a float");
        return -1;
    }
    self->fThis->setStartSpeed(PyFloat_AsDouble(value));
    return 0;
}

static int pyATCEaseCurve_setSpeed(pyATCEaseCurve* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "speed should be a float");
        return -1;
    }
    self->fThis->setSpeed(PyFloat_AsDouble(value));
    return 0;
}

static int pyATCEaseCurve_setMinLength(pyATCEaseCurve* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "minLength should be a float");
        return -1;
    }
    self->fThis->setLengthBounds(PyFloat_AsDouble(value), self->fThis->getMaxLength());
    return 0;
}

static int pyATCEaseCurve_setMaxLength(pyATCEaseCurve* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "maxLength should be a float");
        return -1;
    }
    self->fThis->setLengthBounds(self->fThis->getMinLength(), PyFloat_AsDouble(value));
    return 0;
}

static int pyATCEaseCurve_setLength(pyATCEaseCurve* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "length should be a float");
        return -1;
    }
    self->fThis->setLength(PyFloat_AsDouble(value));
    return 0;
}

static int pyATCEaseCurve_setBegin(pyATCEaseCurve* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "beginWorldTime should be a float");
        return -1;
    }
    self->fThis->setBeginWorldTime(PyFloat_AsDouble(value));
    return 0;
}

static PyMethodDef pyATCEaseCurve_Methods[] = {
    { "Convert", (PyCFunction)pyATCEaseCurve_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plATCEaseCurve" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyATCEaseCurve_GetSet[] = {
    { "startSpeed", (getter)pyATCEaseCurve_getStartSpeed, (setter)pyATCEaseCurve_setStartSpeed, NULL, NULL },
    { "speed", (getter)pyATCEaseCurve_getSpeed, (setter)pyATCEaseCurve_setSpeed, NULL, NULL },
    { "minLength", (getter)pyATCEaseCurve_getMinLength, (setter)pyATCEaseCurve_setMinLength, NULL, NULL },
    { "maxLength", (getter)pyATCEaseCurve_getMaxLength, (setter)pyATCEaseCurve_setMaxLength, NULL, NULL },
    { "length", (getter)pyATCEaseCurve_getLength, (setter)pyATCEaseCurve_setLength, NULL, NULL },
    { "beginWorldTime", (getter)pyATCEaseCurve_getBegin, (setter)pyATCEaseCurve_setBegin, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyATCEaseCurve_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plATCEaseCurve",          /* tp_name */
    sizeof(pyATCEaseCurve),             /* tp_basicsize */
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
    "plATCEaseCurve wrapper",           /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyATCEaseCurve_Methods,             /* tp_methods */
    NULL,                               /* tp_members */
    pyATCEaseCurve_GetSet,              /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyATCEaseCurve_new,                 /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyATCEaseCurve_Type() {
    pyATCEaseCurve_Type.tp_base = &pyCreatable_Type;
    if (PyType_Ready(&pyATCEaseCurve_Type) < 0)
        return NULL;

    Py_INCREF(&pyATCEaseCurve_Type);
    return (PyObject*)&pyATCEaseCurve_Type;
}

int pyATCEaseCurve_Check(PyObject* obj) {
    if (obj->ob_type == &pyATCEaseCurve_Type
        || PyType_IsSubtype(obj->ob_type, &pyATCEaseCurve_Type))
        return 1;
    return 0;
}

PyObject* pyATCEaseCurve_FromATCEaseCurve(class plATCEaseCurve* curve) {
    if (curve == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyATCEaseCurve* pyobj = PyObject_New(pyATCEaseCurve, &pyATCEaseCurve_Type);
    pyobj->fThis = curve;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
