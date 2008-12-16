#include <Python.h>
#include <PRP/Avatar/plPointChannel.h>
#include "pyAGChannel.h"
#include "../pyCreatable.h"
#include "../Animation/pyController.h"

extern "C" {

static PyObject* pyPointControllerChannel_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyPointControllerChannel* self = (pyPointControllerChannel*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plPointControllerChannel();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyPointControllerChannel_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyPointControllerChannel_FromPointControllerChannel(plPointControllerChannel::Convert(cre->fThis));
}

static PyObject* pyPointControllerChannel_getController(pyPointControllerChannel* self, void*) {
    return pyController_FromController(self->fThis->getController());
}

static int pyPointControllerChannel_setController(pyPointControllerChannel* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setController(NULL);
        return 0;
    }
    if (!pyController_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "controller should be a plController");
        return -1;
    }
    self->fThis->setController(((pyController*)value)->fThis);
    ((pyController*)value)->fPyOwned = false;
    return 0;
}

static PyMethodDef pyPointControllerChannel_Methods[] = {
    { "Convert", (PyCFunction)pyPointControllerChannel_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plPointControllerChannel" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyPointControllerChannel_GetSet[] = {
    { "controller", (getter)pyPointControllerChannel_getController, (setter)pyPointControllerChannel_setController, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyPointControllerChannel_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plPointControllerChannel", /* tp_name */
    sizeof(pyPointControllerChannel),   /* tp_basicsize */
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
    "plPointControllerChannel wrapper", /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyPointControllerChannel_Methods,   /* tp_methods */
    NULL,                               /* tp_members */
    pyPointControllerChannel_GetSet,    /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyPointControllerChannel_new,       /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyPointControllerChannel_Type() {
    pyPointControllerChannel_Type.tp_base = &pyPointChannel_Type;
    if (PyType_Ready(&pyPointControllerChannel_Type) < 0)
        return NULL;

    Py_INCREF(&pyPointControllerChannel_Type);
    return (PyObject*)&pyPointControllerChannel_Type;
}

int pyPointControllerChannel_Check(PyObject* obj) {
    if (obj->ob_type == &pyPointControllerChannel_Type
        || PyType_IsSubtype(obj->ob_type, &pyPointControllerChannel_Type))
        return 1;
    return 0;
}

PyObject* pyPointControllerChannel_FromPointControllerChannel(class plPointControllerChannel* chan) {
    if (chan == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyPointControllerChannel* pyobj = PyObject_New(pyPointControllerChannel, &pyPointControllerChannel_Type);
    pyobj->fThis = chan;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
