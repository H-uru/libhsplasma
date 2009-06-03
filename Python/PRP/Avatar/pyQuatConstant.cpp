#include <PyPlasma.h>
#include <PRP/Avatar/plQuatChannel.h>
#include "pyAGChannel.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyQuatConstant_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyQuatConstant* self = (pyQuatConstant*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plQuatConstant();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyQuatConstant_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyQuatConstant_FromQuatConstant(plQuatConstant::Convert(cre->fThis));
}

static PyMethodDef pyQuatConstant_Methods[] = {
    { "Convert", (PyCFunction)pyQuatConstant_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plQuatConstant" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyQuatConstant_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plQuatConstant",          /* tp_name */
    sizeof(pyQuatConstant),             /* tp_basicsize */
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
    "plQuatConstant wrapper",              /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyQuatConstant_Methods,                /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyQuatConstant_new,                    /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyQuatConstant_Type() {
    pyQuatConstant_Type.tp_base = &pyQuatChannel_Type;
    if (PyType_Ready(&pyQuatConstant_Type) < 0)
        return NULL;

    Py_INCREF(&pyQuatConstant_Type);
    return (PyObject*)&pyQuatConstant_Type;
}

int pyQuatConstant_Check(PyObject* obj) {
    if (obj->ob_type == &pyQuatConstant_Type
        || PyType_IsSubtype(obj->ob_type, &pyQuatConstant_Type))
        return 1;
    return 0;
}

PyObject* pyQuatConstant_FromQuatConstant(class plQuatConstant* chan) {
    if (chan == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyQuatConstant* pyobj = PyObject_New(pyQuatConstant, &pyQuatConstant_Type);
    pyobj->fThis = chan;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
