#include <PyPlasma.h>
#include <PRP/Avatar/plScalarChannel.h>
#include "pyAGChannel.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyATCChannel_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyATCChannel* self = (pyATCChannel*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plATCChannel();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyATCChannel_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyATCChannel_FromATCChannel(plATCChannel::Convert(cre->fThis));
}

static PyMethodDef pyATCChannel_Methods[] = {
    { "Convert", (PyCFunction)pyATCChannel_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plATCChannel" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyATCChannel_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plATCChannel",            /* tp_name */
    sizeof(pyATCChannel),               /* tp_basicsize */
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
    "plATCChannel wrapper",             /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyATCChannel_Methods,               /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyATCChannel_new,                   /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyATCChannel_Type() {
    pyATCChannel_Type.tp_base = &pyScalarChannel_Type;
    if (PyType_Ready(&pyATCChannel_Type) < 0)
        return NULL;

    Py_INCREF(&pyATCChannel_Type);
    return (PyObject*)&pyATCChannel_Type;
}

int pyATCChannel_Check(PyObject* obj) {
    if (obj->ob_type == &pyATCChannel_Type
        || PyType_IsSubtype(obj->ob_type, &pyATCChannel_Type))
        return 1;
    return 0;
}

PyObject* pyATCChannel_FromATCChannel(class plATCChannel* chan) {
    if (chan == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyATCChannel* pyobj = PyObject_New(pyATCChannel, &pyATCChannel_Type);
    pyobj->fThis = chan;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
