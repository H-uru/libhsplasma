#include <Python.h>
#include <PRP/Object/plDrawInterface.h>
#include "pyObjInterface.h"
#include "../pyCreatable.h"
#include "../KeyedObject/pyKey.h"

extern "C" {

static PyObject* pyDrawInterface_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyDrawInterface* self = (pyDrawInterface*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plDrawInterface();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyDrawInterface_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyDrawInterface_FromDrawInterface(plDrawInterface::Convert(cre->fThis));
}

static PyObject* pyDrawInterface_clearDrawables(pyDrawInterface* self) {
    self->fThis->clearDrawables();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyDrawInterface_addDrawable(pyDrawInterface* self, PyObject* args) {
    pyKey* draw;
    int key;
    if (!PyArg_ParseTuple(args, "Oi", &draw, &key)) {
        PyErr_SetString(PyExc_TypeError, "addDrawable expects plKey, int");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)draw)) {
        PyErr_SetString(PyExc_TypeError, "addDrawable expects plKey, int");
        return NULL;
    }
    self->fThis->addDrawable(*draw->fThis, key);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyDrawInterface_delDrawable(pyDrawInterface* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delDrawable expects an int");
        return NULL;
    }
    self->fThis->delDrawable(idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyDrawInterface_clearRegions(pyDrawInterface* self) {
    self->fThis->clearRegions();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyDrawInterface_addRegion(pyDrawInterface* self, PyObject* args) {
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addRegion expects a plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addRegion expects a plKey");
        return NULL;
    }
    self->fThis->addRegion(*key->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyDrawInterface_delRegion(pyDrawInterface* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delRegion expects an int");
        return NULL;
    }
    self->fThis->delRegion(idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyDrawInterface_getDrawables(pyDrawInterface* self, void*) {
    PyObject* list = PyList_New(self->fThis->getNumDrawables());
    for (size_t i=0; i<self->fThis->getNumDrawables(); i++) {
        PyObject* tup = Py_BuildValue("(Oi)",
            pyKey_FromKey(self->fThis->getDrawable(i)),
            self->fThis->getDrawableKey(i));
        if (tup == NULL)
            return NULL;
        PyList_SET_ITEM(list, i, tup);
    }
    return list;
}

static PyObject* pyDrawInterface_getRegions(pyDrawInterface* self, void*) {
    PyObject* list = PyList_New(self->fThis->getNumRegions());
    for (size_t i=0; i<self->fThis->getNumRegions(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getRegion(i)));
    return list;
}

static int pyDrawInterface_setDrawables(pyDrawInterface* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add Drawables, use addDrawable");
    return -1;
}

static int pyDrawInterface_setRegions(pyDrawInterface* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add Regions, use addRegion");
    return -1;
}

PyMethodDef pyDrawInterface_Methods[] = {
    { "Convert", (PyCFunction)pyDrawInterface_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plDrawInterface" },
    { "clearDrawables", (PyCFunction)pyDrawInterface_clearDrawables, METH_NOARGS,
      "Removes all drawables from the Draw Interface" },
    { "addDrawable", (PyCFunction)pyDrawInterface_addDrawable, METH_VARARGS,
      "Params: (key, idx,)\n"
      "Adds a drawable reference and key index to the Draw Interface" },
    { "delDrawable", (PyCFunction)pyDrawInterface_delDrawable, METH_VARARGS,
      "Params: idx\n"
      "Removes a drawable reference and key from the Draw Interface" },
    { "clearRegions", (PyCFunction)pyDrawInterface_clearRegions, METH_NOARGS,
      "Removes all regions from the Draw Interface" },
    { "addRegion", (PyCFunction)pyDrawInterface_addRegion, METH_VARARGS,
      "Params: key\n"
      "Adds a region to the Draw Interface" },
    { "delRegion", (PyCFunction)pyDrawInterface_delRegion, METH_VARARGS,
      "Params: idx\n"
      "Removes a region from the Draw Interface" },
    { NULL, NULL, 0, NULL }
};

PyGetSetDef pyDrawInterface_GetSet[] = {
    { "drawables", (getter)pyDrawInterface_getDrawables, (setter)pyDrawInterface_setDrawables,
      "Drawable references and keys", NULL },
    { "regions", (getter)pyDrawInterface_getRegions, (setter)pyDrawInterface_setRegions,
      "Drawable regions", NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyDrawInterface_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plDrawInterface",         /* tp_name */
    sizeof(pyDrawInterface),            /* tp_basicsize */
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
    "plDrawInterface wrapper",          /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyDrawInterface_Methods,            /* tp_methods */
    NULL,                               /* tp_members */
    pyDrawInterface_GetSet,             /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyDrawInterface_new,                /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyDrawInterface_Type() {
    pyDrawInterface_Type.tp_base = &pyObjInterface_Type;
    if (PyType_Ready(&pyDrawInterface_Type) < 0)
        return NULL;

    Py_INCREF(&pyDrawInterface_Type);
    return (PyObject*)&pyDrawInterface_Type;
}

int pyDrawInterface_Check(PyObject* obj) {
    if (obj->ob_type == &pyDrawInterface_Type
        || PyType_IsSubtype(obj->ob_type, &pyDrawInterface_Type))
        return 1;
    return 0;
}

PyObject* pyDrawInterface_FromDrawInterface(class plDrawInterface* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyDrawInterface* intf = PyObject_New(pyDrawInterface, &pyDrawInterface_Type);
    intf->fThis = obj;
    intf->fPyOwned = false;
    return (PyObject*)intf;
}

}
