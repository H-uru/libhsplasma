#include <PyPlasma.h>
#include <PRP/Avatar/plAGApplicator.h>
#include "pyAGApplicator.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pySoundVolumeApplicator_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pySoundVolumeApplicator* self = (pySoundVolumeApplicator*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plSoundVolumeApplicator();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pySoundVolumeApplicator_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pySoundVolumeApplicator_FromSoundVolumeApplicator(plSoundVolumeApplicator::Convert(cre->fThis));
}

static PyObject* pySoundVolumeApplicator_getIndex(pySoundVolumeApplicator* self, void*) {
    return PyInt_FromLong(self->fThis->getIndex());
}

static int pySoundVolumeApplicator_setIndex(pySoundVolumeApplicator* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "index should be an int");
        return -1;
    }
    self->fThis->setIndex(PyInt_AsLong(value));
    return 0;
}

static PyMethodDef pySoundVolumeApplicator_Methods[] = {
    { "Convert", (PyCFunction)pySoundVolumeApplicator_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plSoundVolumeApplicator" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pySoundVolumeApplicator_GetSet[] = {
    { "index", (getter)pySoundVolumeApplicator_getIndex, (setter)pySoundVolumeApplicator_setIndex, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pySoundVolumeApplicator_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plSoundVolumeApplicator", /* tp_name */
    sizeof(pySoundVolumeApplicator),    /* tp_basicsize */
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
    "plSoundVolumeApplicator wrapper",  /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pySoundVolumeApplicator_Methods,    /* tp_methods */
    NULL,                               /* tp_members */
    pySoundVolumeApplicator_GetSet,     /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pySoundVolumeApplicator_new,        /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pySoundVolumeApplicator_Type() {
    pySoundVolumeApplicator_Type.tp_base = &pyAGApplicator_Type;
    if (PyType_Ready(&pySoundVolumeApplicator_Type) < 0)
        return NULL;

    Py_INCREF(&pySoundVolumeApplicator_Type);
    return (PyObject*)&pySoundVolumeApplicator_Type;
}

int pySoundVolumeApplicator_Check(PyObject* obj) {
    if (obj->ob_type == &pySoundVolumeApplicator_Type
        || PyType_IsSubtype(obj->ob_type, &pySoundVolumeApplicator_Type))
        return 1;
    return 0;
}

PyObject* pySoundVolumeApplicator_FromSoundVolumeApplicator(class plSoundVolumeApplicator* app) {
    if (app == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pySoundVolumeApplicator* pyobj = PyObject_New(pySoundVolumeApplicator, &pySoundVolumeApplicator_Type);
    pyobj->fThis = app;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
