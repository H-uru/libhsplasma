#include <Python.h>
#include <PRP/Message/proEventData.h>
#include "pyEventData.h"
#include "../KeyedObject/pyKey.h"

extern "C" {

static PyObject* pyClimbingBlockerHitEventData_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyClimbingBlockerHitEventData* self = (pyClimbingBlockerHitEventData*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new proClimbingBlockerHitEventData();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyClimbingBlockerHitEventData_Convert(PyObject*, PyObject* args) {
    pyEventData* evt;
    if (!PyArg_ParseTuple(args, "O", &evt)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a proEventData");
        return NULL;
    }
    if (!pyEventData_Check((PyObject*)evt)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a proEventData");
        return NULL;
    }
    return pyClimbingBlockerHitEventData_FromClimbingBlockerHitEventData(proClimbingBlockerHitEventData::Convert(evt->fThis));
}

static PyObject* pyClimbingBlockerHitEventData_getBlocker(pyClimbingBlockerHitEventData* self, void*) {
    return pyKey_FromKey(self->fThis->getBlocker());
}

static int pyClimbingBlockerHitEventData_setBlocker(pyClimbingBlockerHitEventData* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setBlocker(plKey());
        return 0;
    } else if (pyKey_Check(value)) {
        self->fThis->setBlocker(*((pyKey*)value)->fThis);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "blocker should be a plKey");
        return -1;
    }
}

static PyMethodDef pyClimbingBlockerHitEventData_Methods[] = {
    { "Convert", (PyCFunction)pyClimbingBlockerHitEventData_Convert, METH_VARARGS | METH_STATIC,
      "Convert a proEventData to a proClimbingBlockerHitEventData" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyClimbingBlockerHitEventData_GetSet[] = {
    { "blocker", (getter)pyClimbingBlockerHitEventData_getBlocker, (setter)pyClimbingBlockerHitEventData_setBlocker, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyClimbingBlockerHitEventData_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.proClimbingBlockerHitEventData", /* tp_name */
    sizeof(pyClimbingBlockerHitEventData), /* tp_basicsize */
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
    "proClimbingBlockerHitEventData wrapper", /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyClimbingBlockerHitEventData_Methods, /* tp_methods */
    NULL,                               /* tp_members */
    pyClimbingBlockerHitEventData_GetSet, /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyClimbingBlockerHitEventData_new,  /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyClimbingBlockerHitEventData_Type() {
    pyClimbingBlockerHitEventData_Type.tp_base = &pyEventData_Type;
    if (PyType_Ready(&pyClimbingBlockerHitEventData_Type) < 0)
        return NULL;

    Py_INCREF(&pyClimbingBlockerHitEventData_Type);
    return (PyObject*)&pyClimbingBlockerHitEventData_Type;
}

int pyClimbingBlockerHitEventData_Check(PyObject* obj) {
    if (obj->ob_type == &pyClimbingBlockerHitEventData_Type
        || PyType_IsSubtype(obj->ob_type, &pyClimbingBlockerHitEventData_Type))
        return 1;
    return 0;
}

PyObject* pyClimbingBlockerHitEventData_FromClimbingBlockerHitEventData(proClimbingBlockerHitEventData* evt) {
    if (evt == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyClimbingBlockerHitEventData* pyobj = PyObject_New(pyClimbingBlockerHitEventData, &pyClimbingBlockerHitEventData_Type);
    pyobj->fThis = evt;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
