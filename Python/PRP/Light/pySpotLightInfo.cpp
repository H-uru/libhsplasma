#include <Python.h>
#include <PRP/Light/plOmniLightInfo.h>
#include "pyLightInfo.h"
#include "../pyCreatable.h"

extern "C" {

static PyObject* pySpotLightInfo_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pySpotLightInfo* self = (pySpotLightInfo*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plSpotLightInfo();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pySpotLightInfo_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pySpotLightInfo_FromSpotLightInfo(plSpotLightInfo::Convert(cre->fThis));
}

static PyObject* pySpotLightInfo_getFalloff(pySpotLightInfo* self, void*) {
    return PyFloat_FromDouble(self->fThis->getFalloff());
}

static PyObject* pySpotLightInfo_getSpotInner(pySpotLightInfo* self, void*) {
    return PyFloat_FromDouble(self->fThis->getSpotInner());
}

static PyObject* pySpotLightInfo_getSpotOuter(pySpotLightInfo* self, void*) {
    return PyFloat_FromDouble(self->fThis->getSpotOuter());
}

static PyObject* pySpotLightInfo_getEffectiveFOV(pySpotLightInfo* self, void*) {
    return PyFloat_FromDouble(self->fThis->getEffectiveFOV());
}

static int pySpotLightInfo_setFalloff(pySpotLightInfo* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "falloff should be a float");
        return -1;
    }
    self->fThis->setFalloff(PyFloat_AsDouble(value));
    return 0;
}

static int pySpotLightInfo_setSpotInner(pySpotLightInfo* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "spotInner should be a float");
        return -1;
    }
    self->fThis->setSpotInner(PyFloat_AsDouble(value));
    return 0;
}

static int pySpotLightInfo_setSpotOuter(pySpotLightInfo* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "spotOuter should be a float");
        return -1;
    }
    self->fThis->setSpotOuter(PyFloat_AsDouble(value));
    return 0;
}

static int pySpotLightInfo_setEffectiveFOV(pySpotLightInfo* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "effectiveFOV should be a float");
        return -1;
    }
    self->fThis->setEffectiveFOV(PyFloat_AsDouble(value));
    return 0;
}

static PyMethodDef pySpotLightInfo_Methods[] = {
    { "Convert", (PyCFunction)pySpotLightInfo_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plSpotLightInfo" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pySpotLightInfo_GetSet[] = {
    { "falloff", (getter)pySpotLightInfo_getFalloff, (setter)pySpotLightInfo_setFalloff, NULL, NULL },
    { "spotInner", (getter)pySpotLightInfo_getSpotInner, (setter)pySpotLightInfo_setSpotInner, NULL, NULL },
    { "spotOuter", (getter)pySpotLightInfo_getSpotOuter, (setter)pySpotLightInfo_setSpotOuter, NULL, NULL },
    { "effectiveFOV", (getter)pySpotLightInfo_getEffectiveFOV, (setter)pySpotLightInfo_setEffectiveFOV, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pySpotLightInfo_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plSpotLightInfo",         /* tp_name */
    sizeof(pySpotLightInfo),            /* tp_basicsize */
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
    "plSpotLightInfo wrapper",          /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pySpotLightInfo_Methods,            /* tp_methods */
    NULL,                               /* tp_members */
    pySpotLightInfo_GetSet,             /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pySpotLightInfo_new,                /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pySpotLightInfo_Type() {
    pySpotLightInfo_Type.tp_base = &pyOmniLightInfo_Type;
    if (PyType_Ready(&pySpotLightInfo_Type) < 0)
        return NULL;

    Py_INCREF(&pySpotLightInfo_Type);
    return (PyObject*)&pySpotLightInfo_Type;
}

int pySpotLightInfo_Check(PyObject* obj) {
    if (obj->ob_type == &pySpotLightInfo_Type
        || PyType_IsSubtype(obj->ob_type, &pySpotLightInfo_Type))
        return 1;
    return 0;
}

PyObject* pySpotLightInfo_FromSpotLightInfo(class plSpotLightInfo* light) {
    if (light == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pySpotLightInfo* pyLight = PyObject_New(pySpotLightInfo, &pySpotLightInfo_Type);
    pyLight->fThis = light;
    pyLight->fPyOwned = false;
    return (PyObject*)pyLight;
}

}
