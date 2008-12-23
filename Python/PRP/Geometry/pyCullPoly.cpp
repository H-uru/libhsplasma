#include <Python.h>
#include <PRP/Geometry/plCullPoly.h>
#include <Math/hsGeometry3.h>
#include "pyOccluder.h"
#include "../../Math/pyGeometry3.h"

extern "C" {

static void pyCullPoly_dealloc(pyCullPoly* self) {
    delete self->fThis;
    self->ob_type->tp_free((PyObject*)self);
}

static int pyCullPoly___init__(pyCullPoly* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pyCullPoly_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyCullPoly* self = (pyCullPoly*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plCullPoly();
    }
    return (PyObject*)self;
}

static PyObject* pyCullPoly_getVerts(pyCullPoly* self, void*) {
    
    hsTArray<hsVector3> verts;
    verts = self->fThis->GetVerts();
    PyObject* list = PyList_New(verts.getSize());
    for (size_t i=0; i<verts.getSize(); i++)
        PyList_SET_ITEM(list, i, pyVector3_FromVector3(verts[i]));
    return list;
}

static PyMethodDef pyCullPoly_Methods[] = {
    { "getVerts", (PyCFunction)pyCullPoly_getVerts, METH_NOARGS,
      "Returns the vertices for a given polygon" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyCullPoly_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                                  /* ob_size */
    "PyPlasma.plCullPoly",             /* tp_name */
    sizeof(pyCullPoly),                /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pyCullPoly_dealloc,    /* tp_dealloc */
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
    "plCullPoly wrapper",              /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyCullPoly_Methods,                /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyCullPoly___init__,     /* tp_init */
    NULL,                               /* tp_alloc */
    pyCullPoly_new,                    /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyCullPoly_Type() {
    if (PyType_Ready(&pyCullPoly_Type) < 0)
        return NULL;

    Py_INCREF(&pyCullPoly_Type);
    return (PyObject*)&pyCullPoly_Type;
}

int pyCullPoly_Check(PyObject* obj) {
    if (obj->ob_type == &pyCullPoly_Type
        || PyType_IsSubtype(obj->ob_type, &pyCullPoly_Type))
        return 1;
    return 0;
}

PyObject* pyCullPoly_FromCullPoly(const plCullPoly& pCre) {
    pyCullPoly* obj = PyObject_New(pyCullPoly, &pyCullPoly_Type);
    obj->fThis = new plCullPoly(pCre);
    return (PyObject*)obj;
}

}
