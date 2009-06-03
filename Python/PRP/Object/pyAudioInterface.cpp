#include <PyPlasma.h>
#include <PRP/Object/plAudioInterface.h>
#include "pyObjInterface.h"
#include "PRP/pyCreatable.h"
#include "PRP/KeyedObject/pyKey.h"

extern "C" {

static PyObject* pyAudioInterface_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyAudioInterface* self = (pyAudioInterface*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plAudioInterface();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyAudioInterface_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyAudioInterface_FromAudioInterface(plAudioInterface::Convert(cre->fThis));
}

static PyObject* pyAudioInterface_getAudible(pyAudioInterface* self, void*) {
    return pyKey_FromKey(self->fThis->getAudible());
}

static int pyAudioInterface_setAudible(pyAudioInterface* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setAudible(plKey());
        return 0;
    } else if (pyKey_Check(value)) {
        self->fThis->setAudible(*((pyKey*)value)->fThis);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "audible should be a plKey");
        return -1;
    }
}

PyMethodDef pyAudioInterface_Methods[] = {
    { "Convert", (PyCFunction)pyAudioInterface_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plAudioInterface" },
    { NULL, NULL, 0, NULL }
};

PyGetSetDef pyAudioInterface_GetSet[] = {
    { "audible", (getter)pyAudioInterface_getAudible, (setter)pyAudioInterface_setAudible,
      "The Audible key", NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyAudioInterface_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plAudioInterface",        /* tp_name */
    sizeof(pyAudioInterface),           /* tp_basicsize */
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
    "plAudioInterface wrapper",         /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyAudioInterface_Methods,           /* tp_methods */
    NULL,                               /* tp_members */
    pyAudioInterface_GetSet,            /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyAudioInterface_new,               /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyAudioInterface_Type() {
    pyAudioInterface_Type.tp_base = &pyObjInterface_Type;
    if (PyType_Ready(&pyAudioInterface_Type) < 0)
        return NULL;

    Py_INCREF(&pyAudioInterface_Type);
    return (PyObject*)&pyAudioInterface_Type;
}

int pyAudioInterface_Check(PyObject* obj) {
    if (obj->ob_type == &pyAudioInterface_Type
        || PyType_IsSubtype(obj->ob_type, &pyAudioInterface_Type))
        return 1;
    return 0;
}

PyObject* pyAudioInterface_FromAudioInterface(class plAudioInterface* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyAudioInterface* intf = PyObject_New(pyAudioInterface, &pyAudioInterface_Type);
    intf->fThis = obj;
    intf->fPyOwned = false;
    return (PyObject*)intf;
}

}
