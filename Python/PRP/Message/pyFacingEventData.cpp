#include <Python.h>
#include <PRP/Message/proEventData.h>
#include "pyEventData.h"
#include "../KeyedObject/pyKey.h"

extern "C" {

static PyObject* pyFacingEventData_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyFacingEventData* self = (pyFacingEventData*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new proFacingEventData();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyFacingEventData_Convert(PyObject*, PyObject* args) {
    pyEventData* evt;
    if (!PyArg_ParseTuple(args, "O", &evt)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a proEventData");
        return NULL;
    }
    if (!pyEventData_Check((PyObject*)evt)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a proEventData");
        return NULL;
    }
    return pyFacingEventData_FromFacingEventData(proFacingEventData::Convert(evt->fThis));
}

static PyObject* pyFacingEventData_getFacer(pyFacingEventData* self, void*) {
    return pyKey_FromKey(self->fThis->getFacer());
}

static PyObject* pyFacingEventData_getFacee(pyFacingEventData* self, void*) {
    return pyKey_FromKey(self->fThis->getFacee());
}

static PyObject* pyFacingEventData_getDot(pyFacingEventData* self, void*) {
    return PyFloat_FromDouble(self->fThis->getDot());
}

static PyObject* pyFacingEventData_getEnabled(pyFacingEventData* self, void*) {
    return PyBool_FromLong(self->fThis->isEnabled());
}

static int pyFacingEventData_setFacer(pyFacingEventData* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setFacer(plKey());
        return 0;
    } else if (pyKey_Check(value)) {
        self->fThis->setFacer(*((pyKey*)value)->fThis);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "facer should be a plKey");
        return -1;
    }
}

static int pyFacingEventData_setFacee(pyFacingEventData* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setFacee(plKey());
        return 0;
    } else if (pyKey_Check(value)) {
        self->fThis->setFacee(*((pyKey*)value)->fThis);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "facee should be a plKey");
        return -1;
    }
}

static int pyFacingEventData_setDot(pyFacingEventData* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "dot should be a float");
        return -1;
    }
    self->fThis->setDot(PyFloat_AsDouble(value));
    return 0;
}

static int pyFacingEventData_setEnabled(pyFacingEventData* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "enabled should be a bool");
        return -1;
    }
    self->fThis->setEnabled(PyInt_AsLong(value) != 0);
    return 0;
}

static PyMethodDef pyFacingEventData_Methods[] = {
    { "Convert", (PyCFunction)pyFacingEventData_Convert, METH_VARARGS | METH_STATIC,
      "Convert a proEventData to a proFacingEventData" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyFacingEventData_GetSet[] = {
    { "facer", (getter)pyFacingEventData_getFacer, (setter)pyFacingEventData_setFacer, NULL, NULL },
    { "facee", (getter)pyFacingEventData_getFacee, (setter)pyFacingEventData_setFacee, NULL, NULL },
    { "dot", (getter)pyFacingEventData_getDot, (setter)pyFacingEventData_setDot, NULL, NULL },
    { "enabled", (getter)pyFacingEventData_getEnabled, (setter)pyFacingEventData_setEnabled, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyFacingEventData_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.proFacingEventData",      /* tp_name */
    sizeof(pyFacingEventData),          /* tp_basicsize */
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
    "proFacingEventData wrapper",       /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyFacingEventData_Methods,          /* tp_methods */
    NULL,                               /* tp_members */
    pyFacingEventData_GetSet,           /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyFacingEventData_new,              /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyFacingEventData_Type() {
    pyFacingEventData_Type.tp_base = &pyEventData_Type;
    if (PyType_Ready(&pyFacingEventData_Type) < 0)
        return NULL;

    Py_INCREF(&pyFacingEventData_Type);
    return (PyObject*)&pyFacingEventData_Type;
}

int pyFacingEventData_Check(PyObject* obj) {
    if (obj->ob_type == &pyFacingEventData_Type
        || PyType_IsSubtype(obj->ob_type, &pyFacingEventData_Type))
        return 1;
    return 0;
}

PyObject* pyFacingEventData_FromFacingEventData(proFacingEventData* evt) {
    if (evt == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyFacingEventData* pyobj = PyObject_New(pyFacingEventData, &pyFacingEventData_Type);
    pyobj->fThis = evt;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
