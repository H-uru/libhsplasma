#include <Python.h>
#include <PRP/Geometry/plOccluder.h>
#include "pyOccluder.h"
#include "../Object/pyObjInterface.h"
#include "../Region/pyBounds.h"
#include "../pyCreatable.h"

extern "C" {

static int pyOccluder___init__(pyOccluder* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pyOccluder_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyOccluder* self = (pyOccluder*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plOccluder();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyOccluder_Convert(PyObject*, PyObject* args) {
    pyCreatable* cre;
    if (!PyArg_ParseTuple(args, "O", &cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    if (!pyCreatable_Check((PyObject*)cre)) {
        PyErr_SetString(PyExc_TypeError, "Convert expects a plCreatable");
        return NULL;
    }
    return pyOccluder_FromOccluder(plOccluder::Convert(cre->fThis));
}

static PyObject* pyOccluder_getBounds(pyOccluder* self, void*) {
    return pyBounds3Ext_FromBounds3Ext(self->fThis->GetBounds());
}

static PyObject* pyOccluder_getPriority(pyOccluder* self, void*) {
    return PyInt_FromLong(self->fThis->GetPriority());
}

static PyObject* pyOccluder_getPolys(pyOccluder* self, void*) {
    PyObject* list = PyList_New(self->fThis->GetNumPolys());
    for (size_t i=0; i<self->fThis->GetNumPolys(); i++)
        PyList_SET_ITEM(list, i, pyCullPoly_FromCullPoly(self->fThis->GetPoly(i)));
    return list;
}

static PyMethodDef pyOccluder_Methods[] = {
    { "Convert", (PyCFunction)pyOccluder_Convert, METH_VARARGS | METH_STATIC,
      "Convert a plCreatable to a plOccluder" },
    { "getBounds", (PyCFunction)pyOccluder_getBounds, METH_NOARGS,
      "Returns the hsBounds3Ext of the Occluder" },
    { "getPriority", (PyCFunction)pyOccluder_getPriority, METH_NOARGS,
      "Returns the priority of the plOccluder" },
    { "getPolys", (PyCFunction)pyOccluder_getPolys, METH_NOARGS,
      "Returns an array of plCullPoly objects" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyOccluder_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plOccluder",             /* tp_name */
    sizeof(pyOccluder),                /* tp_basicsize */
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
    "plOccluder wrapper",              /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyOccluder_Methods,                /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyOccluder___init__,     /* tp_init */
    NULL,                               /* tp_alloc */
    pyOccluder_new,                    /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyOccluder_Type() {
    pyOccluder_Type.tp_base = &pyObjInterface_Type;
    if (PyType_Ready(&pyOccluder_Type) < 0)
        return NULL;

    Py_INCREF(&pyOccluder_Type);
    return (PyObject*)&pyOccluder_Type;
}

int pyOccluder_Check(PyObject* obj) {
    if (obj->ob_type == &pyOccluder_Type
        || PyType_IsSubtype(obj->ob_type, &pyOccluder_Type))
        return 1;
    return 0;
}

PyObject* pyOccluder_FromOccluder(class plOccluder* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyOccluder* pobj = PyObject_New(pyOccluder, &pyOccluder_Type);
    pobj->fThis = obj;
    pobj->fPyOwned = false;
    return (PyObject*)pobj;
}

}
