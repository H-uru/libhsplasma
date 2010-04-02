#include <PyPlasma.h>
#include <PRP/Modifier/plModifier.h>
#include "pyModifier.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pySingleModifier_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "plSingleModifier is abstract");
    return NULL;
}

static PyObject* pySingleModifier_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pySingleModifier_FromSingleModifier(plSingleModifier::Convert(cre->fThis));
}

static PyObject* pySingleModifier_getFlag(pySingleModifier* self, PyObject* args) {
    int flag;
    if (!PyArg_ParseTuple(args, "i", &flag)) {
        PyErr_SetString(PyExc_TypeError, "getFlag expects an int");
        return NULL;
    }
    return PyBool_FromLong(self->fThis->getFlag(flag) ? 1 : 0);
}

static PyObject* pySingleModifier_setFlag(pyMultiModifier* self, PyObject* args) {
    int flag, value;
    if (!PyArg_ParseTuple(args, "ii", &flag, &value)) {
        PyErr_SetString(PyExc_TypeError, "setFlag expects int, bool");
        return NULL;
    }
    self->fThis->setFlag(flag, value != 0);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef pySingleModifier_Methods[] = {
    { "Convert", (PyCFunction)pySingleModifier_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plSingleModifier" },
    { "getFlag", (PyCFunction)pySingleModifier_getFlag, METH_VARARGS,
      "Params: flag\n"
      "Returns whether the specified modifier flag is set" },
    { "setFlag", (PyCFunction)pySingleModifier_setFlag, METH_VARARGS,
      "Params: flag, value\n"
      "Sets the specified modifier flag" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pySingleModifier_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plSingleModifier",        /* tp_name */
    sizeof(pySingleModifier),           /* tp_basicsize */
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
    "plSingleModifier wrapper",         /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pySingleModifier_Methods,           /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pySingleModifier_new,               /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pySingleModifier_Type() {
    pySingleModifier_Type.tp_base = &pyModifier_Type;
    if (PyType_Ready(&pySingleModifier_Type) < 0)
        return NULL;

    Py_INCREF(&pySingleModifier_Type);
    return (PyObject*)&pySingleModifier_Type;
}

int pySingleModifier_Check(PyObject* obj) {
    if (obj->ob_type == &pySingleModifier_Type
        || PyType_IsSubtype(obj->ob_type, &pySingleModifier_Type))
        return 1;
    return 0;
}

PyObject* pySingleModifier_FromSingleModifier(class plSingleModifier* mod) {
    if (mod == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pySingleModifier* pymod = PyObject_New(pySingleModifier, &pySingleModifier_Type);
    pymod->fThis = mod;
    pymod->fPyOwned = false;
    return (PyObject*)pymod;
}

}
