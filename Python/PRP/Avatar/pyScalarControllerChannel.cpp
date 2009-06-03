#include <PyPlasma.h>
#include <PRP/Avatar/plScalarChannel.h>
#include "pyAGChannel.h"
#include "PRP/pyCreatable.h"
#include "PRP/Animation/pyController.h"

extern "C" {

static PyObject* pyScalarControllerChannel_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyScalarControllerChannel* self = (pyScalarControllerChannel*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plScalarControllerChannel();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyScalarControllerChannel_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyScalarControllerChannel_FromScalarControllerChannel(plScalarControllerChannel::Convert(cre->fThis));
}

static PyObject* pyScalarControllerChannel_getController(pyScalarControllerChannel* self, void*) {
    return pyController_FromController(self->fThis->getController());
}

static int pyScalarControllerChannel_setController(pyScalarControllerChannel* self, PyObject* value, void*) {
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

static PyMethodDef pyScalarControllerChannel_Methods[] = {
    { "Convert", (PyCFunction)pyScalarControllerChannel_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plScalarControllerChannel" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyScalarControllerChannel_GetSet[] = {
    { "controller", (getter)pyScalarControllerChannel_getController, (setter)pyScalarControllerChannel_setController, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyScalarControllerChannel_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plScalarControllerChannel", /* tp_name */
    sizeof(pyScalarControllerChannel),  /* tp_basicsize */
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
    "plScalarControllerChannel wrapper", /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyScalarControllerChannel_Methods,  /* tp_methods */
    NULL,                               /* tp_members */
    pyScalarControllerChannel_GetSet,   /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyScalarControllerChannel_new,      /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyScalarControllerChannel_Type() {
    pyScalarControllerChannel_Type.tp_base = &pyScalarChannel_Type;
    if (PyType_Ready(&pyScalarControllerChannel_Type) < 0)
        return NULL;

    Py_INCREF(&pyScalarControllerChannel_Type);
    return (PyObject*)&pyScalarControllerChannel_Type;
}

int pyScalarControllerChannel_Check(PyObject* obj) {
    if (obj->ob_type == &pyScalarControllerChannel_Type
        || PyType_IsSubtype(obj->ob_type, &pyScalarControllerChannel_Type))
        return 1;
    return 0;
}

PyObject* pyScalarControllerChannel_FromScalarControllerChannel(class plScalarControllerChannel* chan) {
    if (chan == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyScalarControllerChannel* pyobj = PyObject_New(pyScalarControllerChannel, &pyScalarControllerChannel_Type);
    pyobj->fThis = chan;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
