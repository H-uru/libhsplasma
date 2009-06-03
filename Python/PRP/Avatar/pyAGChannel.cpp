#include <PyPlasma.h>
#include <PRP/Avatar/plAGChannel.h>
#include "pyAGChannel.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyAGChannel_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "plAGApplicator is abstract");
    return NULL;
}

static PyObject* pyAGChannel_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyAGChannel_FromAGChannel(plAGChannel::Convert(cre->fThis));
}

static PyObject* pyAGChannel_getName(pyAGChannel* self, void*) {
    return PyString_FromString(self->fThis->getName());
}

static int pyAGChannel_setName(pyAGChannel* self, PyObject* value, void*) {
    if (value == NULL || !PyString_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "name should be a string");
        return -1;
    }
    self->fThis->setName(PyString_AsString(value));
    return 0;
}

static PyMethodDef pyAGChannel_Methods[] = {
    { "Convert", (PyCFunction)pyAGChannel_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plAGChannel" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyAGChannel_GetSet[] = {
    { "name", (getter)pyAGChannel_getName, (setter)pyAGChannel_setName, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyAGChannel_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plAGChannel",             /* tp_name */
    sizeof(pyAGChannel),                /* tp_basicsize */
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
    "plAGChannel wrapper",              /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyAGChannel_Methods,                /* tp_methods */
    NULL,                               /* tp_members */
    pyAGChannel_GetSet,                 /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyAGChannel_new,                    /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyAGChannel_Type() {
    pyAGChannel_Type.tp_base = &pyCreatable_Type;
    if (PyType_Ready(&pyAGChannel_Type) < 0)
        return NULL;

    Py_INCREF(&pyAGChannel_Type);
    return (PyObject*)&pyAGChannel_Type;
}

int pyAGChannel_Check(PyObject* obj) {
    if (obj->ob_type == &pyAGChannel_Type
        || PyType_IsSubtype(obj->ob_type, &pyAGChannel_Type))
        return 1;
    return 0;
}

PyObject* pyAGChannel_FromAGChannel(class plAGChannel* chan) {
    if (chan == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyAGChannel* pyobj = PyObject_New(pyAGChannel, &pyAGChannel_Type);
    pyobj->fThis = chan;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
