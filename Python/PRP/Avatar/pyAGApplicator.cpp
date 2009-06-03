#include <PyPlasma.h>
#include <PRP/Avatar/plAGApplicator.h>
#include "pyAGApplicator.h"
#include "pyAGChannel.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyAGApplicator_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "plAGApplicator is abstract");
    return NULL;
}

static PyObject* pyAGApplicator_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyAGApplicator_FromAGApplicator(plAGApplicator::Convert(cre->fThis));
}

static PyObject* pyAGApplicator_getChannel(pyAGApplicator* self, void*) {
    return pyAGChannel_FromAGChannel(self->fThis->getChannel());
}

static PyObject* pyAGApplicator_getEnabled(pyAGApplicator* self, void*) {
    return PyBool_FromLong(self->fThis->isEnabled() ? 1 : 0);
}

static PyObject* pyAGApplicator_getChannelName(pyAGApplicator* self, void*) {
    return PyString_FromString(self->fThis->getChannelName());
}

static int pyAGApplicator_setChannel(pyAGApplicator* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setChannel(NULL);
        return 0;
    }
    if (!pyAGChannel_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "channel should be a plAGChannel");
        return -1;
    }
    self->fThis->setChannel(((pyAGChannel*)value)->fThis);
    ((pyAGChannel*)value)->fPyOwned = false;
    return 0;
}

static int pyAGApplicator_setEnabled(pyAGApplicator* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "enabled should be a bool");
        return -1;
    }
    self->fThis->setEnabled(PyInt_AsLong(value) != 0);
    return 0;
}

static int pyAGApplicator_setChannelName(pyAGApplicator* self, PyObject* value, void*) {
    if (value == NULL || !PyString_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "channelName should be a string");
        return -1;
    }
    self->fThis->setChannelName(PyString_AsString(value));
    return 0;
}

static PyMethodDef pyAGApplicator_Methods[] = {
    { "Convert", (PyCFunction)pyAGApplicator_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plAGApplicator" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyAGApplicator_GetSet[] = {
    { "channel", (getter)pyAGApplicator_getChannel, (setter)pyAGApplicator_setChannel, NULL, NULL },
    { "enabled", (getter)pyAGApplicator_getEnabled, (setter)pyAGApplicator_setEnabled, NULL, NULL },
    { "channelName", (getter)pyAGApplicator_getChannelName, (setter)pyAGApplicator_setChannelName, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyAGApplicator_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plAGApplicator",          /* tp_name */
    sizeof(pyAGApplicator),             /* tp_basicsize */
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
    "plAGApplicator wrapper",           /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyAGApplicator_Methods,             /* tp_methods */
    NULL,                               /* tp_members */
    pyAGApplicator_GetSet,              /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyAGApplicator_new,                 /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyAGApplicator_Type() {
    pyAGApplicator_Type.tp_base = &pyCreatable_Type;
    if (PyType_Ready(&pyAGApplicator_Type) < 0)
        return NULL;

    Py_INCREF(&pyAGApplicator_Type);
    return (PyObject*)&pyAGApplicator_Type;
}

int pyAGApplicator_Check(PyObject* obj) {
    if (obj->ob_type == &pyAGApplicator_Type
        || PyType_IsSubtype(obj->ob_type, &pyAGApplicator_Type))
        return 1;
    return 0;
}

PyObject* pyAGApplicator_FromAGApplicator(class plAGApplicator* app) {
    if (app == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyAGApplicator* pyobj = PyObject_New(pyAGApplicator, &pyAGApplicator_Type);
    pyobj->fThis = app;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
