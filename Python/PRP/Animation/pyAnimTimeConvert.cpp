#include <PyPlasma.h>
#include <PRP/Animation/plAnimTimeConvert.h>
#include "pyAnimTimeConvert.h"
#include "pyATCEaseCurves.h"
#include "PRP/Message/pyEventCallbackMsg.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyAnimTimeConvert_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyAnimTimeConvert* self = (pyAnimTimeConvert*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plAnimTimeConvert();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyAnimTimeConvert_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyAnimTimeConvert_FromAnimTimeConvert(plAnimTimeConvert::Convert(cre->fThis));
}

static PyObject* pyAnimTimeConvert_addCallback(pyAnimTimeConvert* self, PyObject* args) {
    pyEventCallbackMsg* msg;
    if (!PyArg_ParseTuple(args, "O", &msg)) {
        PyErr_SetString(PyExc_TypeError, "addCallback expects a plEventCallbackMsg");
        return NULL;
    }
    if (!pyEventCallbackMsg_Check((PyObject*)msg)) {
        PyErr_SetString(PyExc_TypeError, "addCallback expects a plEventCallbackMsg");
        return NULL;
    }
    msg->fPyOwned = false;
    self->fThis->addCallback(msg->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyAnimTimeConvert_delCallback(pyAnimTimeConvert* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delCallback expects an int");
        return NULL;
    }
    self->fThis->delCallback(idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyAnimTimeConvert_clearCallbacks(pyAnimTimeConvert* self) {
    self->fThis->clearCallbacks();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyAnimTimeConvert_getFlags(pyAnimTimeConvert* self, void*) {
    return PyInt_FromLong(self->fThis->getFlags());
}

static PyObject* pyAnimTimeConvert_getBegin(pyAnimTimeConvert* self, void*) {
    return PyFloat_FromDouble(self->fThis->getBegin());
}

static PyObject* pyAnimTimeConvert_getEnd(pyAnimTimeConvert* self, void*) {
    return PyFloat_FromDouble(self->fThis->getEnd());
}

static PyObject* pyAnimTimeConvert_getLoopBegin(pyAnimTimeConvert* self, void*) {
    return PyFloat_FromDouble(self->fThis->getLoopBegin());
}

static PyObject* pyAnimTimeConvert_getLoopEnd(pyAnimTimeConvert* self, void*) {
    return PyFloat_FromDouble(self->fThis->getLoopEnd());
}

static PyObject* pyAnimTimeConvert_getSpeed(pyAnimTimeConvert* self, void*) {
    return PyFloat_FromDouble(self->fThis->getSpeed());
}

static PyObject* pyAnimTimeConvert_getCurTime(pyAnimTimeConvert* self, void*) {
    return PyFloat_FromDouble(self->fThis->getCurrentAnimTime());
}

static PyObject* pyAnimTimeConvert_getEvalTime(pyAnimTimeConvert* self, void*) {
    return PyFloat_FromDouble(self->fThis->getLastEvalWorldTime());
}

static PyObject* pyAnimTimeConvert_getEaseIn(pyAnimTimeConvert* self, void*) {
    return pyATCEaseCurve_FromATCEaseCurve(self->fThis->getEaseInCurve());
}

static PyObject* pyAnimTimeConvert_getEaseOut(pyAnimTimeConvert* self, void*) {
    return pyATCEaseCurve_FromATCEaseCurve(self->fThis->getEaseOutCurve());
}

static PyObject* pyAnimTimeConvert_getSpeedCurve(pyAnimTimeConvert* self, void*) {
    return pyATCEaseCurve_FromATCEaseCurve(self->fThis->getSpeedEaseCurve());
}

static PyObject* pyAnimTimeConvert_getStops(pyAnimTimeConvert* self, void*) {
    PyObject* list = PyList_New(self->fThis->getStopPoints().getSize());
    for (size_t i=0; i<self->fThis->getStopPoints().getSize(); i++)
        PyList_SET_ITEM(list, i, PyFloat_FromDouble(self->fThis->getStopPoints()[i]));
    return list;
}

static PyObject* pyAnimTimeConvert_getCallbacks(pyAnimTimeConvert* self, void*) {
    PyObject* list = PyList_New(self->fThis->getCallbacks().getSize());
    for (size_t i=0; i<self->fThis->getCallbacks().getSize(); i++)
        PyList_SET_ITEM(list, i, pyEventCallbackMsg_FromEventCallbackMsg(self->fThis->getCallbacks()[i]));
    return list;
}

static int pyAnimTimeConvert_setFlags(pyAnimTimeConvert* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "flags should be an int");
        return -1;
    }
    self->fThis->setFlags(PyInt_AsLong(value));
    return 0;
}

static int pyAnimTimeConvert_setBegin(pyAnimTimeConvert* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "begin should be a float");
        return -1;
    }
    self->fThis->setRange(PyFloat_AsDouble(value), self->fThis->getEnd());
    return 0;
}

static int pyAnimTimeConvert_setEnd(pyAnimTimeConvert* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "end should be a float");
        return -1;
    }
    self->fThis->setRange(self->fThis->getBegin(), PyFloat_AsDouble(value));
    return 0;
}

static int pyAnimTimeConvert_setLoopBegin(pyAnimTimeConvert* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "loopBegin should be a float");
        return -1;
    }
    self->fThis->setLoop(PyFloat_AsDouble(value), self->fThis->getLoopEnd());
    return 0;
}

static int pyAnimTimeConvert_setLoopEnd(pyAnimTimeConvert* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "loopEnd should be a float");
        return -1;
    }
    self->fThis->setLoop(self->fThis->getLoopBegin(), PyFloat_AsDouble(value));
    return 0;
}

static int pyAnimTimeConvert_setSpeed(pyAnimTimeConvert* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "speed should be a float");
        return -1;
    }
    self->fThis->setSpeed(PyFloat_AsDouble(value));
    return 0;
}

static int pyAnimTimeConvert_setCurTime(pyAnimTimeConvert* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "currentAnimTime should be a float");
        return -1;
    }
    self->fThis->setCurrentAnimTime(PyFloat_AsDouble(value));
    return 0;
}

static int pyAnimTimeConvert_setEvalTime(pyAnimTimeConvert* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "lastEvalWorldTime should be a float");
        return -1;
    }
    self->fThis->setLastEvalWorldTime(PyFloat_AsDouble(value));
    return 0;
}

static int pyAnimTimeConvert_setEaseIn(pyAnimTimeConvert* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        Py_XDECREF(value);
        self->fThis->setEaseInCurve(NULL);
        return 0;
    }
    if (!pyATCEaseCurve_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "easeInCurve should be a float");
        return -1;
    }
    self->fThis->setEaseInCurve(((pyATCEaseCurve*)value)->fThis);
    ((pyATCEaseCurve*)value)->fPyOwned = false;
    return 0;
}

static int pyAnimTimeConvert_setEaseOut(pyAnimTimeConvert* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        Py_XDECREF(value);
        self->fThis->setEaseOutCurve(NULL);
        return 0;
    }
    if (!pyATCEaseCurve_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "easeOutCurve should be a float");
        return -1;
    }
    self->fThis->setEaseOutCurve(((pyATCEaseCurve*)value)->fThis);
    ((pyATCEaseCurve*)value)->fPyOwned = false;
    return 0;
}

static int pyAnimTimeConvert_setSpeedCurve(pyAnimTimeConvert* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        Py_XDECREF(value);
        self->fThis->setSpeedEaseCurve(NULL);
        return 0;
    }
    if (!pyATCEaseCurve_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "speedEaseCurve should be a float");
        return -1;
    }
    self->fThis->setSpeedEaseCurve(((pyATCEaseCurve*)value)->fThis);
    ((pyATCEaseCurve*)value)->fPyOwned = false;
    return 0;
}

static int pyAnimTimeConvert_setStops(pyAnimTimeConvert* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        Py_XDECREF(value);
        self->fThis->setStopPoints(hsTArray<float>());
        return 0;
    }
    if (!PyList_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "stopPoints should be a list of floats");
        return -1;
    }
    hsTArray<float> stops;
    stops.setSize(PyList_Size(value));
    for (size_t i=0; i<stops.getSize(); i++) {
        PyObject* itm = PyList_GetItem(value, i);
        if (!PyFloat_Check(itm)) {
            PyErr_SetString(PyExc_TypeError, "stopPoints should be a list of floats");
            return -1;
        }
        stops[i] = PyFloat_AsDouble(itm);
    }
    self->fThis->setStopPoints(stops);
    return 0;
}

static int pyAnimTimeConvert_setCallbacks(pyAnimTimeConvert* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add callbacks, use addCallback()");
    return -1;
}

static PyMethodDef pyAnimTimeConvert_Methods[] = {
    { "Convert", (PyCFunction)pyAnimTimeConvert_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plAnimTimeConvert" },
    { "addCallback", (PyCFunction)pyAnimTimeConvert_addCallback, METH_VARARGS,
      "Params: callback\n"
      "Add a callback message to the object" },
    { "delCallback", (PyCFunction)pyAnimTimeConvert_delCallback, METH_VARARGS,
      "Params: idx\n"
      "Delete a callback message from the object" },
    { "clearCallbacks", (PyCFunction)pyAnimTimeConvert_clearCallbacks, METH_NOARGS,
      "Delete all callbacks from the object" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyAnimTimeConvert_GetSet[] = {
    { "flags", (getter)pyAnimTimeConvert_getFlags, (setter)pyAnimTimeConvert_setFlags, NULL, NULL },
    { "begin", (getter)pyAnimTimeConvert_getBegin, (setter)pyAnimTimeConvert_setBegin, NULL, NULL },
    { "end", (getter)pyAnimTimeConvert_getEnd, (setter)pyAnimTimeConvert_setEnd, NULL, NULL },
    { "loopBegin", (getter)pyAnimTimeConvert_getLoopBegin, (setter)pyAnimTimeConvert_setLoopBegin, NULL, NULL },
    { "loopEnd", (getter)pyAnimTimeConvert_getLoopEnd, (setter)pyAnimTimeConvert_setLoopEnd, NULL, NULL },
    { "speed", (getter)pyAnimTimeConvert_getSpeed, (setter)pyAnimTimeConvert_setSpeed, NULL, NULL },
    { "currentAnimTime", (getter)pyAnimTimeConvert_getCurTime, (setter)pyAnimTimeConvert_setCurTime, NULL, NULL },
    { "lastEvalWorldTime", (getter)pyAnimTimeConvert_getEvalTime, (setter)pyAnimTimeConvert_setEvalTime, NULL, NULL },
    { "easeInCurve", (getter)pyAnimTimeConvert_getEaseIn, (setter)pyAnimTimeConvert_setEaseIn, NULL, NULL },
    { "easeOutCurve", (getter)pyAnimTimeConvert_getEaseOut, (setter)pyAnimTimeConvert_setEaseOut, NULL, NULL },
    { "speedEaseCurve", (getter)pyAnimTimeConvert_getSpeedCurve, (setter)pyAnimTimeConvert_setSpeedCurve, NULL, NULL },
    { "stopPoints", (getter)pyAnimTimeConvert_getStops, (setter)pyAnimTimeConvert_setStops, NULL, NULL },
    { "callbacks", (getter)pyAnimTimeConvert_getCallbacks, (setter)pyAnimTimeConvert_setCallbacks, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyAnimTimeConvert_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plAnimTimeConvert",       /* tp_name */
    sizeof(pyAnimTimeConvert),          /* tp_basicsize */
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
    "plAnimTimeConvert wrapper",        /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyAnimTimeConvert_Methods,          /* tp_methods */
    NULL,                               /* tp_members */
    pyAnimTimeConvert_GetSet,           /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyAnimTimeConvert_new,              /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyAnimTimeConvert_Type() {
    pyAnimTimeConvert_Type.tp_base = &pyCreatable_Type;
    if (PyType_Ready(&pyAnimTimeConvert_Type) < 0)
        return NULL;

    Py_INCREF(&pyAnimTimeConvert_Type);
    return (PyObject*)&pyAnimTimeConvert_Type;
}

int pyAnimTimeConvert_Check(PyObject* obj) {
    if (obj->ob_type == &pyAnimTimeConvert_Type
        || PyType_IsSubtype(obj->ob_type, &pyAnimTimeConvert_Type))
        return 1;
    return 0;
}

PyObject* pyAnimTimeConvert_FromAnimTimeConvert(class plAnimTimeConvert* atc) {
    if (atc == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyAnimTimeConvert* pyobj = PyObject_New(pyAnimTimeConvert, &pyAnimTimeConvert_Type);
    pyobj->fThis = atc;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
