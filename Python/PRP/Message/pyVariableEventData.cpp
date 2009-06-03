#include <PyPlasma.h>
#include <PRP/Message/proEventData.h>
#include "pyEventData.h"
#include "PRP/KeyedObject/pyKey.h"

extern "C" {

static PyObject* pyVariableEventData_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyVariableEventData* self = (pyVariableEventData*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new proVariableEventData();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyVariableEventData_Convert(PyObject*, PyObject* args) {
    pyEventData* evt;
    if (!PyArg_ParseTuple(args, "O", &evt)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a proEventData");
        return NULL;
    }
    if (!pyEventData_Check((PyObject*)evt)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a proEventData");
        return NULL;
    }
    return pyVariableEventData_FromVariableEventData(proVariableEventData::Convert(evt->fThis));
}

static PyObject* pyVariableEventData_getName(pyVariableEventData* self, void*) {
    return PyString_FromString(self->fThis->getName().cstr());
}

static PyObject* pyVariableEventData_getDataType(pyVariableEventData* self, void*) {
    return PyInt_FromLong(self->fThis->getDataType());
}

static PyObject* pyVariableEventData_getNumber(pyVariableEventData* self, void*) {
    return PyFloat_FromDouble(self->fThis->getNumber());
}

static PyObject* pyVariableEventData_getKey(pyVariableEventData* self, void*) {
    return pyKey_FromKey(self->fThis->getKey());
}

static int pyVariableEventData_setName(pyVariableEventData* self, PyObject* value, void*) {
    if (value == NULL || !PyString_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "name should be a string");
        return -1;
    }
    self->fThis->setName(PyString_AsString(value));
    return 0;
}

static int pyVariableEventData_setDataType(pyVariableEventData* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "dataType should be an int");
        return -1;
    }
    self->fThis->setDataType(PyInt_AsLong(value));
    return 0;
}

static int pyVariableEventData_setNumber(pyVariableEventData* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "number should be a float");
        return -1;
    }
    self->fThis->setNumber(PyFloat_AsDouble(value));
    return 0;
}

static int pyVariableEventData_setKey(pyVariableEventData* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setKey(plKey());
        return 0;
    } else if (pyKey_Check(value)) {
        self->fThis->setKey(*((pyKey*)value)->fThis);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "key should be a plKey");
        return -1;
    }
}
static PyMethodDef pyVariableEventData_Methods[] = {
    { "Convert", (PyCFunction)pyVariableEventData_Convert, METH_VARARGS | METH_STATIC,
      "Convert a proEventData to a proVariableEventData" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyVariableEventData_GetSet[] = {
    { "name", (getter)pyVariableEventData_getName, (setter)pyVariableEventData_setName, NULL, NULL },
    { "dataType", (getter)pyVariableEventData_getDataType, (setter)pyVariableEventData_setDataType, NULL, NULL },
    { "number", (getter)pyVariableEventData_getNumber, (setter)pyVariableEventData_setNumber, NULL, NULL },
    { "key", (getter)pyVariableEventData_getKey, (setter)pyVariableEventData_setKey, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyVariableEventData_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.proVariableEventData",    /* tp_name */
    sizeof(pyVariableEventData),        /* tp_basicsize */
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
    "proVariableEventData wrapper",     /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyVariableEventData_Methods,        /* tp_methods */
    NULL,                               /* tp_members */
    pyVariableEventData_GetSet,         /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyVariableEventData_new,            /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyVariableEventData_Type() {
    pyVariableEventData_Type.tp_base = &pyEventData_Type;
    if (PyType_Ready(&pyVariableEventData_Type) < 0)
        return NULL;

    Py_INCREF(&pyVariableEventData_Type);
    return (PyObject*)&pyVariableEventData_Type;
}

int pyVariableEventData_Check(PyObject* obj) {
    if (obj->ob_type == &pyVariableEventData_Type
        || PyType_IsSubtype(obj->ob_type, &pyVariableEventData_Type))
        return 1;
    return 0;
}

PyObject* pyVariableEventData_FromVariableEventData(proVariableEventData* evt) {
    if (evt == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyVariableEventData* pyobj = PyObject_New(pyVariableEventData, &pyVariableEventData_Type);
    pyobj->fThis = evt;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
