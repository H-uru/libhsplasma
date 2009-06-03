#include <PyPlasma.h>
#include <PRP/Message/proEventData.h>
#include "pyEventData.h"
#include "PRP/KeyedObject/pyKey.h"

extern "C" {

static PyObject* pyControlKeyEventData_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyControlKeyEventData* self = (pyControlKeyEventData*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new proControlKeyEventData();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyControlKeyEventData_Convert(PyObject*, PyObject* args) {
    pyEventData* evt;
    if (!PyArg_ParseTuple(args, "O", &evt)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a proEventData");
        return NULL;
    }
    if (!pyEventData_Check((PyObject*)evt)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a proEventData");
        return NULL;
    }
    return pyControlKeyEventData_FromControlKeyEventData(proControlKeyEventData::Convert(evt->fThis));
}

static PyObject* pyControlKeyEventData_getControlKey(pyControlKeyEventData* self, void*) {
    return PyInt_FromLong(self->fThis->getControlKey());
}

static PyObject* pyControlKeyEventData_getDown(pyControlKeyEventData* self, void*) {
    return PyBool_FromLong(self->fThis->isDown());
}

static int pyControlKeyEventData_setControlKey(pyControlKeyEventData* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "controlKey should be an int");
        return -1;
    }
    self->fThis->setControlKey(PyInt_AsLong(value));
    return 0;
}

static int pyControlKeyEventData_setDown(pyControlKeyEventData* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "down should be a bool");
        return -1;
    }
    self->fThis->setDown(PyInt_AsLong(value) != 0);
    return 0;
}

static PyMethodDef pyControlKeyEventData_Methods[] = {
    { "Convert", (PyCFunction)pyControlKeyEventData_Convert, METH_VARARGS | METH_STATIC,
      "Convert a proEventData to a proControlKeyEventData" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyControlKeyEventData_GetSet[] = {
    { "controlKey", (getter)pyControlKeyEventData_getControlKey, (setter)pyControlKeyEventData_setControlKey, NULL, NULL },
    { "down", (getter)pyControlKeyEventData_getDown, (setter)pyControlKeyEventData_setDown, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyControlKeyEventData_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.proControlKeyEventData",  /* tp_name */
    sizeof(pyControlKeyEventData),      /* tp_basicsize */
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
    "proControlKeyEventData wrapper",   /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyControlKeyEventData_Methods,      /* tp_methods */
    NULL,                               /* tp_members */
    pyControlKeyEventData_GetSet,       /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyControlKeyEventData_new,          /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyControlKeyEventData_Type() {
    pyControlKeyEventData_Type.tp_base = &pyEventData_Type;
    if (PyType_Ready(&pyControlKeyEventData_Type) < 0)
        return NULL;

    Py_INCREF(&pyControlKeyEventData_Type);
    return (PyObject*)&pyControlKeyEventData_Type;
}

int pyControlKeyEventData_Check(PyObject* obj) {
    if (obj->ob_type == &pyControlKeyEventData_Type
        || PyType_IsSubtype(obj->ob_type, &pyControlKeyEventData_Type))
        return 1;
    return 0;
}

PyObject* pyControlKeyEventData_FromControlKeyEventData(proControlKeyEventData* evt) {
    if (evt == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyControlKeyEventData* pyobj = PyObject_New(pyControlKeyEventData, &pyControlKeyEventData_Type);
    pyobj->fThis = evt;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
