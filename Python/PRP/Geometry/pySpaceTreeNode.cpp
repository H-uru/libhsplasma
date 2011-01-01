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

extern "C" {

static void pySpaceTreeNode_dealloc(pySpaceTreeNode* self) {
    delete self->fThis;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static int pySpaceTreeNode___init__(pySpaceTreeNode* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pySpaceTreeNode_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pySpaceTreeNode* self = (pySpaceTreeNode*)type->tp_alloc(type, 0);
    if (self != NULL)
        self->fThis = new plSpaceTreeNode();
    return (PyObject*)self;
}

static PyObject* pySpaceTreeNode_getChildren(pySpaceTreeNode* self) {
    PyObject* children = PyTuple_New(2);
    PyTuple_SET_ITEM(children, 0, PyInt_FromLong(self->fThis->getLChild()));
    PyTuple_SET_ITEM(children, 1, PyInt_FromLong(self->fThis->getRChild()));
    return children;
}

static PyObject* pySpaceTreeNode_getLeafIndex(pySpaceTreeNode* self) {
    return PyInt_FromLong(self->fThis->getLeafIndex());
}

static PyObject* pySpaceTreeNode_setChildren(pySpaceTreeNode* self, PyObject* args) {
    int left, right;
    if (!PyArg_ParseTuple(args, "ii", &left, &right)) {
        PyErr_SetString(PyExc_TypeError, "setChildren expects int, int");
        return NULL;
    }
    self->fThis->setChildren(left, right);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pySpaceTreeNode_setLeafIndex(pySpaceTreeNode* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "setLeafIndex expects an int");
        return NULL;
    }
    self->fThis->setLeafIndex(idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pySpaceTreeNode_getBounds(pySpaceTreeNode* self, void*) {
    return pyBounds3Ext_FromBounds3Ext(self->fThis->getBounds());
}

static PyObject* pySpaceTreeNode_getFlags(pySpaceTreeNode* self, void*) {
    return PyInt_FromLong(self->fThis->getFlags());
}

static PyObject* pySpaceTreeNode_getParent(pySpaceTreeNode* self, void*) {
    return PyInt_FromLong(self->fThis->getParent());
}

static int pySpaceTreeNode_setBounds(pySpaceTreeNode* self, PyObject* value, void*) {
    if (value == NULL || !pyBounds3Ext_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "bounds should be an hsBounds3Ext");
        return -1;
    }
    self->fThis->setBounds(*((pyBounds3Ext*)value)->fThis);
    return 0;
}

static int pySpaceTreeNode_setFlags(pySpaceTreeNode* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "flags should be an int");
        return -1;
    }
    self->fThis->setFlags(PyInt_AsLong(value));
    return 0;
}

static int pySpaceTreeNode_setParent(pySpaceTreeNode* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "parent should be an int");
        return -1;
    }
    self->fThis->setParent(PyInt_AsLong(value));
    return 0;
}

static PyMethodDef pySpaceTreeNode_Methods[] = {
    { "getChildren", (PyCFunction)pySpaceTreeNode_getChildren, METH_NOARGS,
      "Returns a tuple with the indices of the child nodes" },
    { "getLeafIndex", (PyCFunction)pySpaceTreeNode_getLeafIndex, METH_NOARGS,
      "Returns the node's leaf index" },
    { "setChildren", (PyCFunction)pySpaceTreeNode_setChildren, METH_VARARGS,
      "Params: left, right\n"
      "Sets the node to a parent node with the specified child indices" },
    { "setLeafIndex", (PyCFunction)pySpaceTreeNode_setLeafIndex, METH_VARARGS,
      "Params: idx\n"
      "Sets the node to a leaf node with the specified leaf index" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pySpaceTreeNode_GetSet[] = {
    { "bounds", (getter)pySpaceTreeNode_getBounds, (setter)pySpaceTreeNode_setBounds, NULL, NULL },
    { "flags", (getter)pySpaceTreeNode_getFlags, (setter)pySpaceTreeNode_setFlags, NULL, NULL },
    { "parent", (getter)pySpaceTreeNode_getParent, (setter)pySpaceTreeNode_setParent, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pySpaceTreeNode_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plSpaceTreeNode",         /* tp_name */
    sizeof(pySpaceTreeNode),            /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pySpaceTreeNode_dealloc, /* tp_dealloc */
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

    Py_TPFLAGS_DEFAULT,                 /* tp_flags */
    "plSpaceTreeNode wrapper",          /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pySpaceTreeNode_Methods,            /* tp_methods */
    NULL,                               /* tp_members */
    pySpaceTreeNode_GetSet,             /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pySpaceTreeNode___init__, /* tp_init */
    NULL,                               /* tp_alloc */
    pySpaceTreeNode_new,                /* tp_new */
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

PyObject* Init_pySpaceTreeNode_Type() {
    if (PyType_Ready(&pySpaceTreeNode_Type) < 0)
        return NULL;

    PyDict_SetItemString(pySpaceTreeNode_Type.tp_dict, "kNone",
                         PyInt_FromLong(plSpaceTreeNode::kNone));
    PyDict_SetItemString(pySpaceTreeNode_Type.tp_dict, "kIsLeaf",
                         PyInt_FromLong(plSpaceTreeNode::kIsLeaf));
    PyDict_SetItemString(pySpaceTreeNode_Type.tp_dict, "kDirty",
                         PyInt_FromLong(plSpaceTreeNode::kDirty));
    PyDict_SetItemString(pySpaceTreeNode_Type.tp_dict, "kDisabled",
                         PyInt_FromLong(plSpaceTreeNode::kDisabled));
    PyDict_SetItemString(pySpaceTreeNode_Type.tp_dict, "kEmpty",
                         PyInt_FromLong(plSpaceTreeNode::kEmpty));
    PyDict_SetItemString(pySpaceTreeNode_Type.tp_dict, "kEnabledTemp",
                         PyInt_FromLong(plSpaceTreeNode::kEnabledTemp));

    Py_INCREF(&pySpaceTreeNode_Type);
    return (PyObject*)&pySpaceTreeNode_Type;
}

int pySpaceTreeNode_Check(PyObject* obj) {
    if (obj->ob_type == &pySpaceTreeNode_Type
        || PyType_IsSubtype(obj->ob_type, &pySpaceTreeNode_Type))
        return 1;
    return 0;
}

PyObject* pySpaceTreeNode_FromSpaceTreeNode(const plSpaceTreeNode& node) {
    pySpaceTreeNode* pnode = PyObject_New(pySpaceTreeNode, &pySpaceTreeNode_Type);
    pnode->fThis = new plSpaceTreeNode(node);
    return (PyObject*)pnode;
}

}
