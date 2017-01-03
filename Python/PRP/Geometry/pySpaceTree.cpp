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

#include "pySpaceTree.h"

#include <PRP/Geometry/plSpaceTree.h>
#include "PRP/Region/pyBounds.h"
#include "PRP/pyCreatable.h"

extern "C" {

PY_PLASMA_EMPTY_INIT(SpaceTree)
PY_PLASMA_NEW(SpaceTree, plSpaceTree)

PY_METHOD_NOARGS(SpaceTree, clear, "Clears the contents of this space tree") {
    self->fThis->clear();
    Py_RETURN_NONE;
}

PY_METHOD_VA(SpaceTree, getNode,
    "Params: idx\n"
    "Returns the specified node")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "getNode expects an int");
        return NULL;
    }
    return pySpaceTreeNode_FromSpaceTreeNode(self->fThis->getNode(idx));
}

PY_METHOD_NOARGS(SpaceTree, getRoot, "Returns the root node") {
    return pySpaceTreeNode_FromSpaceTreeNode(self->fThis->getRoot());
}

PY_METHOD_VA(SpaceTree, addLeaf,
    "Params: bounds\n"
    "Creates a leaf node and returns its index")
{
    pyBounds3Ext* bounds;
    if (!PyArg_ParseTuple(args, "O", &bounds)) {
        PyErr_SetString(PyExc_TypeError, "addLeaf expects an hsBounds3Ext");
        return NULL;
    }
    if (!pyBounds3Ext_Check((PyObject*)bounds)) {
        PyErr_SetString(PyExc_TypeError, "addLeaf expects an hsBounds3Ext");
        return NULL;
    }
    return pyPlasma_convert(self->fThis->addLeaf(*bounds->fThis));
}

PY_METHOD_VA(SpaceTree, addParent,
    "Params: bounds, leftChild, rightChild\n"
    "Creates a normal node with the specified children, and returns its index")
{
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
    return pyPlasma_convert(self->fThis->addParent(*bounds->fThis, left, right));
}

static PyMethodDef pySpaceTree_Methods[] = {
    pySpaceTree_clear_method,
    pySpaceTree_getNode_method,
    pySpaceTree_getRoot_method,
    pySpaceTree_addLeaf_method,
    pySpaceTree_addParent_method,
    PY_METHOD_TERMINATOR
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

    pySpaceTree___init__,               /* tp_init */
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
    TP_FINALIZE_INIT                    /* tp_finalize */
};

PyObject* Init_pySpaceTree_Type() {
    pySpaceTree_Type.tp_base = &pyCreatable_Type;
    if (PyType_Ready(&pySpaceTree_Type) < 0)
        return NULL;

    Py_INCREF(&pySpaceTree_Type);
    return (PyObject*)&pySpaceTree_Type;
}

PY_PLASMA_IFC_METHODS(SpaceTree, plSpaceTree)

}
