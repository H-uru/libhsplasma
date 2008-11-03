#include <Python.h>
#include <PRP/Animation/hsKeys.h>
#include "pyKeys.h"
#include "../../Math/pyMatrix.h"

extern "C" {

static int pyMatrix33Key___init__(pyMatrix33Key* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pyMatrix33Key_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyMatrix33Key* self = (pyMatrix33Key*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new hsMatrix33Key();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyMatrix33Key_getValue(pyMatrix33Key* self, void*) {
    return pyMatrix33_FromMatrix33(self->fThis->fValue);
}

static int pyMatrix33Key_setValue(pyMatrix33Key* self, PyObject* value, void*) {
    if (value == NULL || !pyMatrix33_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "value should be an hsMatrix33");
        return -1;
    }
    self->fThis->fValue = *((pyMatrix33*)value)->fThis;
    return 0;
}

static PyGetSetDef pyMatrix33Key_GetSet[] = {
    { "value", (getter)pyMatrix33Key_getValue, (setter)pyMatrix33Key_setValue, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyMatrix33Key_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.hsMatrix33Key",           /* tp_name */
    sizeof(pyMatrix33Key),              /* tp_basicsize */
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
    "hsMatrix33Key wrapper",            /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyMatrix33Key_GetSet,               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyMatrix33Key___init__,   /* tp_init */
    NULL,                               /* tp_alloc */
    pyMatrix33Key_new,                  /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyMatrix33Key_Type() {
    pyMatrix33Key_Type.tp_base = &pyKeyFrame_Type;
    if (PyType_Ready(&pyMatrix33Key_Type) < 0)
        return NULL;

    Py_INCREF(&pyMatrix33Key_Type);
    return (PyObject*)&pyMatrix33Key_Type;
}

int pyMatrix33Key_Check(PyObject* obj) {
    if (obj->ob_type == &pyMatrix33Key_Type
        || PyType_IsSubtype(obj->ob_type, &pyMatrix33Key_Type))
        return 1;
    return 0;
}

PyObject* pyMatrix33Key_FromMatrix33Key(hsMatrix33Key* frame) {
    if (frame == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyMatrix33Key* pyobj = PyObject_New(pyMatrix33Key, &pyMatrix33Key_Type);
    pyobj->fThis = frame;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
