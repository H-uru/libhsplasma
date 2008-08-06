#include <Python.h>
#include <PRP/Object/plCoordinateInterface.h>
#include "pyObjInterface.h"
#include "../pyCreatable.h"
#include "../KeyedObject/pyKey.h"
#include "../../Math/pyMatrix44.h"

extern "C" {

static PyObject* pyCoordinateInterface_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyCoordinateInterface* self = (pyCoordinateInterface*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plCoordinateInterface();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyCoordinateInterface_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyCoordinateInterface_FromCoordinateInterface(plCoordinateInterface::Convert(cre->fThis));
}

static PyObject* pyCoordinateInterface_clearChildren(pyCoordinateInterface* self) {
    self->fThis->clearChildren();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyCoordinateInterface_addChild(pyCoordinateInterface* self, PyObject* args) {
    pyKey* key;
    if (!PyArg_ParseTuple(args, "O", &key)) {
        PyErr_SetString(PyExc_TypeError, "addChild expects a plKey");
        return NULL;
    }
    if (!pyKey_Check((PyObject*)key)) {
        PyErr_SetString(PyExc_TypeError, "addChild expects a plKey");
        return NULL;
    }
    self->fThis->addChild(*key->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyCoordinateInterface_getL2W(pyCoordinateInterface* self, void*) {
    return pyMatrix44_FromMatrix44Ref(&self->fThis->getLocalToWorld());
}

static PyObject* pyCoordinateInterface_getW2L(pyCoordinateInterface* self, void*) {
    return pyMatrix44_FromMatrix44Ref(&self->fThis->getWorldToLocal());
}

static PyObject* pyCoordinateInterface_getL2P(pyCoordinateInterface* self, void*) {
    return pyMatrix44_FromMatrix44Ref(&self->fThis->getLocalToParent());
}

static PyObject* pyCoordinateInterface_getP2L(pyCoordinateInterface* self, void*) {
    return pyMatrix44_FromMatrix44Ref(&self->fThis->getParentToLocal());
}

static PyObject* pyCoordinateInterface_getChildren(pyCoordinateInterface* self, void*) {
    PyObject* list = PyList_New(self->fThis->getNumChildren());
    for (size_t i=0; i<self->fThis->getNumChildren(); i++)
        PyList_SET_ITEM(list, i, pyKey_FromKey(self->fThis->getChild(i)));
    return list;
}

static int pyCoordinateInterface_setL2W(pyCoordinateInterface* self, PyObject* value, void*) {
    if (value == NULL || (!pyMatrix44_Check(value))) {
        PyErr_SetString(PyExc_TypeError, "localToWorld should be an hsMatrix44");
        return -1;
    }
    self->fThis->getLocalToWorld() = *((pyMatrix44*)value)->fThis;
    return 0;
}

static int pyCoordinateInterface_setW2L(pyCoordinateInterface* self, PyObject* value, void*) {
    if (value == NULL || (!pyMatrix44_Check(value))) {
        PyErr_SetString(PyExc_TypeError, "worldToLocal should be an hsMatrix44");
        return -1;
    }
    self->fThis->getWorldToLocal() = *((pyMatrix44*)value)->fThis;
    return 0;
}

static int pyCoordinateInterface_setL2P(pyCoordinateInterface* self, PyObject* value, void*) {
    if (value == NULL || (!pyMatrix44_Check(value))) {
        PyErr_SetString(PyExc_TypeError, "local2Parent should be an hsMatrix44");
        return -1;
    }
    self->fThis->getLocalToParent() = *((pyMatrix44*)value)->fThis;
    return 0;
}

static int pyCoordinateInterface_setP2L(pyCoordinateInterface* self, PyObject* value, void*) {
    if (value == NULL || (!pyMatrix44_Check(value))) {
        PyErr_SetString(PyExc_TypeError, "parentToLocal should be an hsMatrix44");
        return -1;
    }
    self->fThis->getParentToLocal() = *((pyMatrix44*)value)->fThis;
    return 0;
}

static int pyCoordinateInterface_setChildren(pyCoordinateInterface* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add Children, use addChild");
    return -1;
}

PyMethodDef pyCoordinateInterface_Methods[] = {
    { "Convert", (PyCFunction)pyCoordinateInterface_Convert, METH_VARARGS | METH_STATIC,
      "Convert a Creatable to a plCoordinateInterface" },
    { "clearChildren", (PyCFunction)pyCoordinateInterface_clearChildren, METH_NOARGS,
      "Removes all children from the Coordinate Interface" },
    { "addChild", (PyCFunction)pyCoordinateInterface_addChild, METH_VARARGS,
      "Params: key\n"
      "Adds a child CoordInterface to this CoordInterface" },
    { NULL, NULL, 0, NULL }
};

PyGetSetDef pyCoordinateInterface_GetSet[] = {
    { "localToWorld", (getter)pyCoordinateInterface_getL2W, (setter)pyCoordinateInterface_setL2W,
      "Local -> World transform matrix", NULL },
    { "worldToLocal", (getter)pyCoordinateInterface_getW2L, (setter)pyCoordinateInterface_setW2L,
      "World -> Local transform matrix", NULL },
    { "localToParent", (getter)pyCoordinateInterface_getL2P, (setter)pyCoordinateInterface_setL2P,
      "Local -> Parent transform matrix", NULL },
    { "parentToLocal", (getter)pyCoordinateInterface_getP2L, (setter)pyCoordinateInterface_setP2L,
      "Parent -> Local transform matrix", NULL },
    { "children", (getter)pyCoordinateInterface_getChildren, (setter)pyCoordinateInterface_setChildren,
      "Child CoordinateInterfaces", NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyCoordinateInterface_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plCoordinateInterface",   /* tp_name */
    sizeof(pyCoordinateInterface),      /* tp_basicsize */
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
    "plCoordinateInterface wrapper",    /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyCoordinateInterface_Methods,      /* tp_methods */
    NULL,                               /* tp_members */
    pyCoordinateInterface_GetSet,       /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyCoordinateInterface_new,          /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyCoordinateInterface_Type() {
    pyCoordinateInterface_Type.tp_base = &pyObjInterface_Type;
    if (PyType_Ready(&pyCoordinateInterface_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyCoordinateInterface_Type.tp_dict, "kDisable",
                         PyInt_FromLong(plCoordinateInterface::kDisable));
    PyDict_SetItemString(pyCoordinateInterface_Type.tp_dict, "kCanEverDelayTransform",
                         PyInt_FromLong(plCoordinateInterface::kCanEverDelayTransform));
    PyDict_SetItemString(pyCoordinateInterface_Type.tp_dict, "kDelayedTransformEval",
                         PyInt_FromLong(plCoordinateInterface::kDelayedTransformEval));

    Py_INCREF(&pyCoordinateInterface_Type);
    return (PyObject*)&pyCoordinateInterface_Type;
}

int pyCoordinateInterface_Check(PyObject* obj) {
    if (obj->ob_type == &pyCoordinateInterface_Type
        || PyType_IsSubtype(obj->ob_type, &pyCoordinateInterface_Type))
        return 1;
    return 0;
}

PyObject* pyCoordinateInterface_FromCoordinateInterface(class plCoordinateInterface* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyCoordinateInterface* intf = PyObject_New(pyCoordinateInterface, &pyCoordinateInterface_Type);
    intf->fThis = obj;
    intf->fPyOwned = false;
    return (PyObject*)intf;
}

}
