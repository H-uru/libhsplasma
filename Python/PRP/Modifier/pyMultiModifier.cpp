#include <PyPlasma.h>
#include <PRP/Modifier/plModifier.h>
#include "pyModifier.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyMultiModifier_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "plMultiModifier is abstract");
    return NULL;
}

static PyObject* pyMultiModifier_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyMultiModifier_FromMultiModifier(plMultiModifier::Convert(cre->fThis));
}

static PyObject* pyMultiModifier_getFlag(pyMultiModifier* self, PyObject* args) {
    int flag;
    if (!PyArg_ParseTuple(args, "i", &flag)) {
        PyErr_SetString(PyExc_TypeError, "getFlag expects an int");
        return NULL;
    }
    return PyBool_FromLong(self->fThis->getFlag(flag) ? 1 : 0);
}

static PyObject* pyMultiModifier_setFlag(pyMultiModifier* self, PyObject* args) {
    int flag, value;
    if (!PyArg_ParseTuple(args, "ii", &flag, &value)) {
        PyErr_SetString(PyExc_TypeError, "setFlag expects int, bool");
        return NULL;
    }
    self->fThis->setFlag(flag, value != 0);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef pyMultiModifier_Methods[] = {
    { "Convert", (PyCFunction)pyMultiModifier_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plMultiModifier" },
    { "getFlag", (PyCFunction)pyMultiModifier_getFlag, METH_VARARGS,
      "Params: flag\n"
      "Returns whether the specified modifier flag is set" },
    { "setFlag", (PyCFunction)pyMultiModifier_setFlag, METH_VARARGS,
      "Params: flag, value\n"
      "Sets the specified modifier flag" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyMultiModifier_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plMultiModifier",         /* tp_name */
    sizeof(pyMultiModifier),            /* tp_basicsize */
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
    "plMultiModifier wrapper",          /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyMultiModifier_Methods,            /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyMultiModifier_new,                /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyMultiModifier_Type() {
    pyMultiModifier_Type.tp_base = &pyModifier_Type;
    if (PyType_Ready(&pyMultiModifier_Type) < 0)
        return NULL;

    Py_INCREF(&pyMultiModifier_Type);
    return (PyObject*)&pyMultiModifier_Type;
}

int pyMultiModifier_Check(PyObject* obj) {
    if (obj->ob_type == &pyMultiModifier_Type
        || PyType_IsSubtype(obj->ob_type, &pyMultiModifier_Type))
        return 1;
    return 0;
}

PyObject* pyMultiModifier_FromMultiModifier(class plMultiModifier* mod) {
    if (mod == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyMultiModifier* pymod = PyObject_New(pyMultiModifier, &pyMultiModifier_Type);
    pymod->fThis = mod;
    pymod->fPyOwned = false;
    return (PyObject*)pymod;
}

}
