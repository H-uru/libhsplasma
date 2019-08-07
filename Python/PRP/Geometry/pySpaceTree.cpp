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

PY_PLASMA_EMPTY_INIT(SpaceTree)
PY_PLASMA_NEW(SpaceTree, plSpaceTree)

PY_METHOD_NOARGS(SpaceTree, clear, "Clears the contents of this space tree")
{
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
        return nullptr;
    }
    return pySpaceTreeNode_FromSpaceTreeNode(self->fThis->getNode(idx));
}

PY_METHOD_NOARGS(SpaceTree, getRoot, "Returns the root node")
{
    return pySpaceTreeNode_FromSpaceTreeNode(self->fThis->getRoot());
}

PY_METHOD_VA(SpaceTree, addLeaf,
    "Params: bounds\n"
    "Creates a leaf node and returns its index")
{
    pyBounds3Ext* bounds;
    if (!PyArg_ParseTuple(args, "O", &bounds)) {
        PyErr_SetString(PyExc_TypeError, "addLeaf expects an hsBounds3Ext");
        return nullptr;
    }
    if (!pyBounds3Ext_Check((PyObject*)bounds)) {
        PyErr_SetString(PyExc_TypeError, "addLeaf expects an hsBounds3Ext");
        return nullptr;
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
        return nullptr;
    }
    if (!pyBounds3Ext_Check((PyObject*)bounds)) {
        PyErr_SetString(PyExc_TypeError, "addParent expects hsBounds3Ext, int, int");
        return nullptr;
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

PY_PLASMA_TYPE(SpaceTree, plSpaceTree, "plSpaceTree wrapper")

PY_PLASMA_TYPE_INIT(SpaceTree)
{
    pySpaceTree_Type.tp_init = pySpaceTree___init__;
    pySpaceTree_Type.tp_new = pySpaceTree_new;
    pySpaceTree_Type.tp_methods = pySpaceTree_Methods;
    pySpaceTree_Type.tp_base = &pyCreatable_Type;
    if (PyType_CheckAndReady(&pySpaceTree_Type) < 0)
        return nullptr;

    Py_INCREF(&pySpaceTree_Type);
    return (PyObject*)&pySpaceTree_Type;
}

PY_PLASMA_IFC_METHODS(SpaceTree, plSpaceTree)
