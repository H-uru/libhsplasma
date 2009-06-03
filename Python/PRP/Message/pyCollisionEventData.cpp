#include <PyPlasma.h>
#include <PRP/Message/proEventData.h>
#include "pyEventData.h"
#include "PRP/KeyedObject/pyKey.h"

extern "C" {

static PyObject* pyCollisionEventData_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyCollisionEventData* self = (pyCollisionEventData*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new proCollisionEventData();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyCollisionEventData_Convert(PyObject*, PyObject* args) {
    pyEventData* evt;
    if (!PyArg_ParseTuple(args, "O", &evt)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a proEventData");
        return NULL;
    }
    if (!pyEventData_Check((PyObject*)evt)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a proEventData");
        return NULL;
    }
    return pyCollisionEventData_FromCollisionEventData(proCollisionEventData::Convert(evt->fThis));
}

static PyObject* pyCollisionEventData_getEnter(pyCollisionEventData* self, void*) {
    return PyBool_FromLong(self->fThis->isEnter());
}

static PyObject* pyCollisionEventData_getHitter(pyCollisionEventData* self, void*) {
    return pyKey_FromKey(self->fThis->getHitter());
}

static PyObject* pyCollisionEventData_getHittee(pyCollisionEventData* self, void*) {
    return pyKey_FromKey(self->fThis->getHittee());
}

static int pyCollisionEventData_setEnter(pyCollisionEventData* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "enter should be a bool");
        return -1;
    }
    self->fThis->setEnter(PyInt_AsLong(value) != 0);
    return 0;
}

static int pyCollisionEventData_setHitter(pyCollisionEventData* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setHitter(plKey());
        return 0;
    } else if (pyKey_Check(value)) {
        self->fThis->setHitter(*((pyKey*)value)->fThis);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "hitter should be a plKey");
        return -1;
    }
}

static int pyCollisionEventData_setHittee(pyCollisionEventData* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setHittee(plKey());
        return 0;
    } else if (pyKey_Check(value)) {
        self->fThis->setHittee(*((pyKey*)value)->fThis);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "hittee should be a plKey");
        return -1;
    }
}

static PyMethodDef pyCollisionEventData_Methods[] = {
    { "Convert", (PyCFunction)pyCollisionEventData_Convert, METH_VARARGS | METH_STATIC,
      "Convert a proEventData to a proCollisionEventData" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyCollisionEventData_GetSet[] = {
    { "enter", (getter)pyCollisionEventData_getEnter, (setter)pyCollisionEventData_setEnter, NULL, NULL },
    { "hitter", (getter)pyCollisionEventData_getHitter, (setter)pyCollisionEventData_setHitter, NULL, NULL },
    { "hittee", (getter)pyCollisionEventData_getHittee, (setter)pyCollisionEventData_setHittee, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyCollisionEventData_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.proCollisionEventData",   /* tp_name */
    sizeof(pyCollisionEventData),       /* tp_basicsize */
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
    "proCollisionEventData wrapper",    /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyCollisionEventData_Methods,       /* tp_methods */
    NULL,                               /* tp_members */
    pyCollisionEventData_GetSet,        /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyCollisionEventData_new,           /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyCollisionEventData_Type() {
    pyCollisionEventData_Type.tp_base = &pyEventData_Type;
    if (PyType_Ready(&pyCollisionEventData_Type) < 0)
        return NULL;

    Py_INCREF(&pyCollisionEventData_Type);
    return (PyObject*)&pyCollisionEventData_Type;
}

int pyCollisionEventData_Check(PyObject* obj) {
    if (obj->ob_type == &pyCollisionEventData_Type
        || PyType_IsSubtype(obj->ob_type, &pyCollisionEventData_Type))
        return 1;
    return 0;
}

PyObject* pyCollisionEventData_FromCollisionEventData(proCollisionEventData* evt) {
    if (evt == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyCollisionEventData* pyobj = PyObject_New(pyCollisionEventData, &pyCollisionEventData_Type);
    pyobj->fThis = evt;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
