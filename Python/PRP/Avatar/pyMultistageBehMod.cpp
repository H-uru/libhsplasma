#include <Python.h>
#include <PRP/Avatar/plMultistageBehMod.h>
#include "pyMultistageBehMod.h"
#include "../Modifier/pyModifier.h"
#include "../KeyedObject/pyKey.h"
#include "../pyCreatable.h"

extern "C" {

static PyObject* pyMultistageBehMod_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyMultistageBehMod* self = (pyMultistageBehMod*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plMultistageBehMod();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyMultistageBehMod_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyMultistageBehMod_FromMultistageBehMod(plMultistageBehMod::Convert(cre->fThis));
}

static PyObject* pyMultistageBehMod_addStage(pyMultistageBehMod* self, PyObject* args) {
    pyAnimStage* anim;
    if (!PyArg_ParseTuple(args, "O", &anim)) {
        PyErr_SetString(PyExc_TypeError, "addStage expects a plAnimStage");
        return NULL;
    }
    if (!pyAnimStage_Check((PyObject*)anim)) {
        PyErr_SetString(PyExc_TypeError, "addStage expects a plAnimStage");
        return NULL;
    }
    self->fThis->addStage(anim->fThis);
    anim->fPyOwned = false;
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyMultistageBehMod_delStage(pyMultistageBehMod* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delStage expects an int");
        return NULL;
    }
    self->fThis->delStage(idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyMultistageBehMod_clearStages(pyMultistageBehMod* self) {
    self->fThis->clearStages();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyMultistageBehMod_addReceiver(pyMultistageBehMod* self, PyObject* args) {
    pyKey* rcvr;
    if (!PyArg_ParseTuple(args, "O", &rcvr)) {
        PyErr_SetString(PyExc_TypeError, "addReceiver expects a plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)rcvr)) {
        PyErr_SetString(PyExc_TypeError, "addReceiver expects a plKey");
        return NULL;
    }
    self->fThis->addReceiver(*rcvr->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyMultistageBehMod_delReceiver(pyMultistageBehMod* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delReceiver expects an int");
        return NULL;
    }
    self->fThis->delReceiver(idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyMultistageBehMod_clearReceivers(pyMultistageBehMod* self) {
    self->fThis->clearReceivers();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyMultistageBehMod_getStages(pyMultistageBehMod* self, void*) {
    PyObject* list = PyList_New(self->fThis->getNumStages());
    for (size_t i=0; i<self->fThis->getNumStages(); i++)
        PyList_SET_ITEM(list, i, pyAnimStage_FromAnimStage(self->fThis->getStage(i)));
    return list;
}

static PyObject* pyMultistageBehMod_getReceivers(pyMultistageBehMod* self, void*) {
    PyObject* list = PyList_New(self->fThis->getNumReceivers());
    for (size_t i=0; i<self->fThis->getNumReceivers(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getReceiver(i)));
    return list;
}

static PyObject* pyMultistageBehMod_getFreeze(pyMultistageBehMod* self, void*) {
    return PyBool_FromLong(self->fThis->getFreezePhys() ? 1 : 0);
}

static PyObject* pyMultistageBehMod_getSSeek(pyMultistageBehMod* self, void*) {
    return PyBool_FromLong(self->fThis->getSmartSeek() ? 1 : 0);
}

static PyObject* pyMultistageBehMod_getReverse(pyMultistageBehMod* self, void*) {
    return PyBool_FromLong(self->fThis->getReverseFBControlsOnRelease() ? 1 : 0);
}

static int pyMultistageBehMod_setStages(pyMultistageBehMod* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add stages, use addStage()");
    return -1;
}

static int pyMultistageBehMod_setReceivers(pyMultistageBehMod* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add receivers, use addReceiver()");
    return -1;
}

static int pyMultistageBehMod_setFreeze(pyMultistageBehMod* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "freezePhys should be a bool");
        return -1;
    }
    self->fThis->setFreezePhys(PyInt_AsLong(value) != 0);
    return 0;
}

static int pyMultistageBehMod_setSSeek(pyMultistageBehMod* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "smartSeek should be a bool");
        return -1;
    }
    self->fThis->setSmartSeek(PyInt_AsLong(value) != 0);
    return 0;
}

static int pyMultistageBehMod_setReverse(pyMultistageBehMod* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "reverseFBControlsOnRelease should be a bool");
        return -1;
    }
    self->fThis->setReverseFBControlsOnRelease(PyInt_AsLong(value) != 0);
    return 0;
}

static PyMethodDef pyMultistageBehMod_Methods[] = {
    { "Convert", (PyCFunction)pyMultistageBehMod_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plMultistageBehMod" },
    { "addStage", (PyCFunction)pyMultistageBehMod_addStage, METH_VARARGS,
      "Params: stage\n"
      "Add a plAnimStage to the behavior mod" },
    { "delStage", (PyCFunction)pyMultistageBehMod_delStage, METH_VARARGS,
      "Params: idx\n"
      "Remove a stage from the behavior mod" },
    { "clearStages", (PyCFunction)pyMultistageBehMod_clearStages, METH_NOARGS,
      "Remove all stages from the behavior mod" },
    { "addReceiver", (PyCFunction)pyMultistageBehMod_addReceiver, METH_VARARGS,
      "Params: key\n"
      "Add a receiver key to the behavior mod" },
    { "delReceiver", (PyCFunction)pyMultistageBehMod_delReceiver, METH_VARARGS,
      "Params: idx\n"
      "Remove a receiver from the behavior mod" },
    { "clearReceivers", (PyCFunction)pyMultistageBehMod_clearReceivers, METH_NOARGS,
      "Remove all receivers from the behavior mod" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyMultistageBehMod_GetSet[] = {
    { "stages", (getter)pyMultistageBehMod_getStages, (setter)pyMultistageBehMod_setStages, NULL, NULL },
    { "receivers", (getter)pyMultistageBehMod_getReceivers, (setter)pyMultistageBehMod_setReceivers, NULL, NULL },
    { "freezePhys", (getter)pyMultistageBehMod_getFreeze, (setter)pyMultistageBehMod_setFreeze, NULL, NULL },
    { "smartSeek", (getter)pyMultistageBehMod_getSSeek, (setter)pyMultistageBehMod_setSSeek, NULL, NULL },
    { "reverseFBControlsOnRelease", (getter)pyMultistageBehMod_getReverse, (setter)pyMultistageBehMod_setReverse, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyMultistageBehMod_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plMultistageBehMod",      /* tp_name */
    sizeof(pyMultistageBehMod),         /* tp_basicsize */
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
    "plMultistageBehMod wrapper",       /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyMultistageBehMod_Methods,         /* tp_methods */
    NULL,                               /* tp_members */
    pyMultistageBehMod_GetSet,          /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyMultistageBehMod_new,             /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyMultistageBehMod_Type() {
    pyMultistageBehMod_Type.tp_base = &pySingleModifier_Type;
    if (PyType_Ready(&pyMultistageBehMod_Type) < 0)
        return NULL;

    Py_INCREF(&pyMultistageBehMod_Type);
    return (PyObject*)&pyMultistageBehMod_Type;
}

int pyMultistageBehMod_Check(PyObject* obj) {
    if (obj->ob_type == &pyMultistageBehMod_Type
        || PyType_IsSubtype(obj->ob_type, &pyMultistageBehMod_Type))
        return 1;
    return 0;
}

PyObject* pyMultistageBehMod_FromMultistageBehMod(plMultistageBehMod* mod) {
    if (mod == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyMultistageBehMod* pyobj = PyObject_New(pyMultistageBehMod, &pyMultistageBehMod_Type);
    pyobj->fThis = mod;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
