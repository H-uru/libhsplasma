#include <PyPlasma.h>
#include <PRP/Message/plEventCallbackMsg.h>
#include "pyEventCallbackMsg.h"
#include "pyMessage.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyEventCallbackMsg_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyEventCallbackMsg* self = (pyEventCallbackMsg*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plEventCallbackMsg();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyEventCallbackMsg_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyEventCallbackMsg_FromEventCallbackMsg(plEventCallbackMsg::Convert(cre->fThis));
}

static PyObject* pyEventCallbackMsg_getEventTime(pyEventCallbackMsg* self, void*) {
    return PyFloat_FromDouble(self->fThis->getEventTime());
}

static PyObject* pyEventCallbackMsg_getEvent(pyEventCallbackMsg* self, void*) {
    return PyInt_FromLong(self->fThis->getEvent());
}

static PyObject* pyEventCallbackMsg_getIndex(pyEventCallbackMsg* self, void*) {
    return PyInt_FromLong(self->fThis->getIndex());
}

static PyObject* pyEventCallbackMsg_getRepeats(pyEventCallbackMsg* self, void*) {
    return PyInt_FromLong(self->fThis->getRepeats());
}

static PyObject* pyEventCallbackMsg_getUser(pyEventCallbackMsg* self, void*) {
    return PyInt_FromLong(self->fThis->getUser());
}

static int pyEventCallbackMsg_setEventTime(pyEventCallbackMsg* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "eventTime should be a float");
        return -1;
    }
    self->fThis->setEventTime(PyFloat_AsDouble(value));
    return 0;
}

static int pyEventCallbackMsg_setEvent(pyEventCallbackMsg* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "event should be an int");
        return -1;
    }
    self->fThis->setEvent((CallbackEvent)PyInt_AsLong(value));
    return 0;
}

static int pyEventCallbackMsg_setIndex(pyEventCallbackMsg* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "index should be an int");
        return -1;
    }
    self->fThis->setIndex(PyInt_AsLong(value));
    return 0;
}

static int pyEventCallbackMsg_setRepeats(pyEventCallbackMsg* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "repeats should be an int");
        return -1;
    }
    self->fThis->setRepeats(PyInt_AsLong(value));
    return 0;
}

static int pyEventCallbackMsg_setUser(pyEventCallbackMsg* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "user should be an int");
        return -1;
    }
    self->fThis->setUser(PyInt_AsLong(value));
    return 0;
}

static PyMethodDef pyEventCallbackMsg_Methods[] = {
    { "Convert", (PyCFunction)pyEventCallbackMsg_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plEventCallbackMsg" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyEventCallbackMsg_GetSet[] = {
    { "eventTime", (getter)pyEventCallbackMsg_getEventTime, (setter)pyEventCallbackMsg_setEventTime, NULL, NULL },
    { "event", (getter)pyEventCallbackMsg_getEvent, (setter)pyEventCallbackMsg_setEvent, NULL, NULL },
    { "index", (getter)pyEventCallbackMsg_getIndex, (setter)pyEventCallbackMsg_setIndex, NULL, NULL },
    { "repeats", (getter)pyEventCallbackMsg_getRepeats, (setter)pyEventCallbackMsg_setRepeats, NULL, NULL },
    { "user", (getter)pyEventCallbackMsg_getUser, (setter)pyEventCallbackMsg_setUser, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyEventCallbackMsg_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plEventCallbackMsg",      /* tp_name */
    sizeof(pyEventCallbackMsg),         /* tp_basicsize */
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
    "plEventCallbackMsg wrapper",       /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyEventCallbackMsg_Methods,         /* tp_methods */
    NULL,                               /* tp_members */
    pyEventCallbackMsg_GetSet,          /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyEventCallbackMsg_new,             /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyEventCallbackMsg_Type() {
    pyEventCallbackMsg_Type.tp_base = &pyMessage_Type;
    if (PyType_Ready(&pyEventCallbackMsg_Type) < 0)
        return NULL;

    Py_INCREF(&pyEventCallbackMsg_Type);
    return (PyObject*)&pyEventCallbackMsg_Type;
}

int pyEventCallbackMsg_Check(PyObject* obj) {
    if (obj->ob_type == &pyEventCallbackMsg_Type
        || PyType_IsSubtype(obj->ob_type, &pyEventCallbackMsg_Type))
        return 1;
    return 0;
}

PyObject* pyEventCallbackMsg_FromEventCallbackMsg(class plEventCallbackMsg* msg) {
    if (msg == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyEventCallbackMsg* pyobj = PyObject_New(pyEventCallbackMsg, &pyEventCallbackMsg_Type);
    pyobj->fThis = msg;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
