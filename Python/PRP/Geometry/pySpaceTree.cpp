/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <PyPlasma.h>
#include <PRP/Geometry/plSpaceTree.h>
#include "pySpaceTree.h"
#include "PRP/Region/pyBounds.h"
#include "PRP/pyCreatable.h"

extern "C" {

static int pySpaceTree___init__(pySpaceTree* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pySpaceTree_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pySpaceTree* self = (pySpaceTree*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plSpaceTree();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pySpaceTree_clear(pySpaceTree* self) {
    self->fThis->clear();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pySpaceTree_getNode(pySpaceTree* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "getNode expects an int");
        return NULL;
    }
    return pySpaceTreeNode_FromSpaceTreeNode(self->fThis->getNode(idx));
}

static PyObject* pySpaceTree_getRoot(pySpaceTree* self) {
    return pySpaceTreeNode_FromSpaceTreeNode(self->fThis->getRoot());
}

static PyObject* pySpaceTree_addLeaf(pySpaceTree* self, PyObject* args) {
    pyBounds3Ext* bounds;
    if (!PyArg_ParseTuple(args, "O", &bounds)) {
        PyErr_SetString(PyExc_TypeError, "addLeaf expects an hsBounds3Ext");
        return NULL;
    }
    if (!pyBounds3Ext_Check((PyObject*)bounds)) {
        PyErr_SetString(PyExc_TypeError, "addLeaf expects an hsBounds3Ext");
        return NULL;
    }
    return PyInt_FromLong(self->fThis->addLeaf(*bounds->fThis));
}

static PyObject* pySpaceTree_addParent(pySpaceTree* self, PyObject* args) {
    pyBounds3Ext* bounds;
    int left, right;
    if (!PyArg_ParseTuple(args, "Oii", &bounds, &left, &right)) {
        PyErr_SetString(PyExc_TypeError, "addParent expects hsBounds3Ext, int, int");
        return NULL;
    }
    if (!pyBounds3Ext_Check((PyObject*)bounds)) {
        PyErr_SetString(PyExc_TypeError, "addParent expects hsBounds3Ext, int, int");
        return NULL;
    }
    return PyInt_FromLong(self->fThis->addParent(*bounds->fThis, left, right));
}

static PyMethodDef pySpaceTree_Methods[] = {
    { "clear", (PyCFunction)pySpaceTree_clear, METH_NOARGS,
      "Clears the contents of this space tree" },
    { "getNode", (PyCFunction)pySpaceTree_getNode, METH_VARARGS,
      "Params: idx\n"
      "Returns the specified node" },
    { "getRoot", (PyCFunction)pySpaceTree_getRoot, METH_NOARGS,
      "Returns the root node" },
    { "addLeaf", (PyCFunction)pySpaceTree_addLeaf, METH_VARARGS,
      "Params: bounds\n"
      "Creates a leaf node and returns its index" },
    { "addParent", (PyCFunction)pySpaceTree_addParent, METH_VARARGS,
      "Params: bounds, leftChild, rightChild\n"
      "Creates a normal node with the specified children, and returns its index" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pySpaceTree_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plSpaceTree",           /* tp_name */
    sizeof(pySpaceTree),                /* tp_basicsize */
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
    "plSpaceTree wrapper",              /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pySpaceTree_Methods,                /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pySpaceTree___init__,     /* tp_init */
    NULL,                               /* tp_alloc */
    pySpaceTree_new,                    /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */

    NULL,                               /* tp_del */
    TP_VERSION_TAG_INIT                 /* tp_version_tag */
};

PyObject* Init_pySpaceTree_Type() {
    pySpaceTree_Type.tp_base = &pyCreatable_Type;
    if (PyType_Ready(&pySpaceTree_Type) < 0)
        return NULL;

    Py_INCREF(&pySpaceTree_Type);
    return (PyObject*)&pySpaceTree_Type;
}

int pySpaceTree_Check(PyObject* obj) {
    if (obj->ob_type == &pySpaceTree_Type
        || PyType_IsSubtype(obj->ob_type, &pySpaceTree_Type))
        return 1;
    return 0;
}

PyObject* pySpaceTree_FromSpaceTree(class plSpaceTree* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pySpaceTree* pobj = PyObject_New(pySpaceTree, &pySpaceTree_Type);
    pobj->fThis = obj;
    pobj->fPyOwned = false;
    return (PyObject*)pobj;
}

}
