#include <Python.h>
#include <PRP/Object/plSynchedObject.h>
#include "pySynchedObject.h"
#include "../pyCreatable.h"
#include "../KeyedObject/pyKeyedObject.h"

extern "C" {

static PyObject* pySynchedObject_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "plSynchedObject is abstract");
    return NULL;
}

static PyObject* pySynchedObject_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pySynchedObject_FromSynchedObject(plSynchedObject::Convert(cre->fThis));
}

static PyObject* pySynchedObject_setExclude(pySynchedObject* self, PyObject* args) {
    const char* str;
    if (!PyArg_ParseTuple(args, "s", &str)) {
        PyErr_SetString(PyExc_TypeError, "setExclude expects a string");
        return NULL;
    }
    self->fThis->setExclude(str);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pySynchedObject_setVolatile(pySynchedObject* self, PyObject* args) {
    const char* str;
    if (!PyArg_ParseTuple(args, "s", &str)) {
        PyErr_SetString(PyExc_TypeError, "setVolatile expects a string");
        return NULL;
    }
    self->fThis->setVolatile(str);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pySynchedObject_getFlags(pySynchedObject* self, void*) {
    return PyInt_FromLong(self->fThis->getFlags());
}

static PyObject* pySynchedObject_getExcludes(pySynchedObject* self, void*) {
    PyObject* list = PyList_New(self->fThis->getExcludes().getSize());
    for (size_t i=0; i<self->fThis->getExcludes().getSize(); i++)
        PyList_SET_ITEM(list, i, PyString_FromString(self->fThis->getExcludes()[i].cstr()));
    return list;
}

static PyObject* pySynchedObject_getVolatiles(pySynchedObject* self, void*) {
    PyObject* list = PyList_New(self->fThis->getVolatiles().getSize());
    for (size_t i=0; i<self->fThis->getVolatiles().getSize(); i++)
        PyList_SET_ITEM(list, i, PyString_FromString(self->fThis->getVolatiles()[i].cstr()));
    return list;
}

static int pySynchedObject_setFlags(pySynchedObject* self, PyObject* value, void*) {
    int flags;
    if (value == NULL) {
        flags = 0;
    } else if (PyInt_Check(value)) {
        flags = PyInt_AsLong(value);
    } else {
        PyErr_SetString(PyExc_TypeError, "synchFlags must be an int");
        return -1;
    }
    self->fThis->setFlags(flags);
    return 0;
}

static int pySynchedObject_setExcludes(pySynchedObject* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->clearExcludes();
        return 0;
    } else if (PyList_Check(value)) {
        size_t count = PyList_Size(value);
        for (size_t i=0; i<count; i++) {
            if (!PyString_Check(PyList_GetItem(value, i))) {
                PyErr_SetString(PyExc_TypeError, "excludes should be a list of strings");
                return -1;
            }
            self->fThis->setExclude(PyString_AsString(PyList_GetItem(value, i)));
        }
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "excludes should be a list of strings");
        return -1;
    }
}

static int pySynchedObject_setVolatiles(pySynchedObject* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->clearVolatiles();
        return 0;
    } else if (PyList_Check(value)) {
        size_t count = PyList_Size(value);
        for (size_t i=0; i<count; i++) {
            if (!PyString_Check(PyList_GetItem(value, i))) {
                PyErr_SetString(PyExc_TypeError, "volatiles should be a list of strings");
                return -1;
            }
            self->fThis->setVolatile(PyString_AsString(PyList_GetItem(value, i)));
        }
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "volatiles should be a list of strings");
        return -1;
    }
}

static PyMethodDef pySynchedObject_Methods[] = {
    { "Convert", (PyCFunction)pySynchedObject_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plSynchedObject" },
    { "setExclude", (PyCFunction)pySynchedObject_setExclude, METH_VARARGS,
      "Params: state\n"
      "Add an SDL state to the Exclude list" },
    { "setVolatile", (PyCFunction)pySynchedObject_setVolatile, METH_VARARGS,
      "Params: state\n"
      "Add an SDL state to the Volatile list" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pySynchedObject_GetSet[] = {
    { "synchFlags", (getter)pySynchedObject_getFlags, (setter)pySynchedObject_setFlags,
      "Synched Object Flags", NULL },
    { "excludes", (getter)pySynchedObject_getExcludes, (setter)pySynchedObject_setExcludes,
      "SDL Exclude States", NULL },
    { "volatiles", (getter)pySynchedObject_getVolatiles, (setter)pySynchedObject_setVolatiles,
      "SDL Volatile States", NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pySynchedObject_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plSynchedObject",         /* tp_name */
    sizeof(pySynchedObject),            /* tp_basicsize */
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
    "plSynchedObject wrapper",          /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pySynchedObject_Methods,            /* tp_methods */
    NULL,                               /* tp_members */
    pySynchedObject_GetSet,             /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pySynchedObject_new,                /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pySynchedObject_Type() {
    pySynchedObject_Type.tp_base = &pyKeyedObject_Type;
    if (PyType_Ready(&pySynchedObject_Type) < 0)
        return NULL;

    PyDict_SetItemString(pySynchedObject_Type.tp_dict, "kDontDirty",
                         PyInt_FromLong(plSynchedObject::kDontDirty));
    PyDict_SetItemString(pySynchedObject_Type.tp_dict, "kSendReliably",
                         PyInt_FromLong(plSynchedObject::kSendReliably));
    PyDict_SetItemString(pySynchedObject_Type.tp_dict, "kHasConstantNetGroup",
                         PyInt_FromLong(plSynchedObject::kHasConstantNetGroup));
    PyDict_SetItemString(pySynchedObject_Type.tp_dict, "kDontSynchGameMessages",
                         PyInt_FromLong(plSynchedObject::kDontSynchGameMessages));
    PyDict_SetItemString(pySynchedObject_Type.tp_dict, "kExcludePersistentState",
                         PyInt_FromLong(plSynchedObject::kExcludePersistentState));
    PyDict_SetItemString(pySynchedObject_Type.tp_dict, "kExcludeAllPersistentState",
                         PyInt_FromLong(plSynchedObject::kExcludeAllPersistentState));
    PyDict_SetItemString(pySynchedObject_Type.tp_dict, "kLocalOnly",
                         PyInt_FromLong(plSynchedObject::kLocalOnly));
    PyDict_SetItemString(pySynchedObject_Type.tp_dict, "kHasVolatileState",
                         PyInt_FromLong(plSynchedObject::kHasVolatileState));
    PyDict_SetItemString(pySynchedObject_Type.tp_dict, "kAllStateIsVolatile",
                         PyInt_FromLong(plSynchedObject::kAllStateIsVolatile));

    Py_INCREF(&pySynchedObject_Type);
    return (PyObject*)&pySynchedObject_Type;
}

int pySynchedObject_Check(PyObject* obj) {
    if (obj->ob_type == &pySynchedObject_Type
        || PyType_IsSubtype(obj->ob_type, &pySynchedObject_Type))
        return 1;
    return 0;
}

PyObject* pySynchedObject_FromSynchedObject(class plSynchedObject* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pySynchedObject* so = PyObject_New(pySynchedObject, &pySynchedObject_Type);
    so->fThis = obj;
    so->fPyOwned = false;
    return (PyObject*)so;
}

}
