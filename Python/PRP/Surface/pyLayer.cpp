#include <Python.h>
#include <PRP/Surface/plLayer.h>
#include "pyLayer.h"
#include "pyGMatState.h"
#include "../pyCreatable.h"

extern "C" {

static PyObject* pyLayer_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyLayer* self = (pyLayer*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plLayer();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyLayer_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyLayer_FromLayer(plLayer::Convert(cre->fThis));
}

static PyObject* pyLayer_getState(pyLayer* self, void*) {
    return pyGMatState_FromGMatState(self->fThis->getState());
}

static int pyLayer_setState(pyLayer* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "state is not assignable");
    return -1;
}

static PyMethodDef pyLayer_Methods[] = {
    { "Convert", (PyCFunction)pyLayer_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plLayer" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyLayer_GetSet[] = {
    { "state", (getter)pyLayer_getState, (setter)pyLayer_setState, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyLayer_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plLayer",                 /* tp_name */
    sizeof(pyLayer),                    /* tp_basicsize */
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
    "plLayer wrapper",                  /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyLayer_Methods,                    /* tp_methods */
    NULL,                               /* tp_members */
    pyLayer_GetSet,                     /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyLayer_new,                        /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyLayer_Type() {
    pyLayer_Type.tp_base = &pyLayerInterface_Type;
    if (PyType_Ready(&pyLayer_Type) < 0)
        return NULL;

    Py_INCREF(&pyLayer_Type);
    return (PyObject*)&pyLayer_Type;
}

int pyLayer_Check(PyObject* obj) {
    if (obj->ob_type == &pyLayer_Type
        || PyType_IsSubtype(obj->ob_type, &pyLayer_Type))
        return 1;
    return 0;
}

PyObject* pyLayer_FromLayer(class plLayer* layer) {
    if (layer == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyLayer* pylay = PyObject_New(pyLayer, &pyLayer_Type);
    pylay->fThis = layer;
    pylay->fPyOwned = false;
    return (PyObject*)pylay;
}

}
