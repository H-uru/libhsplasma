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

PY_PLASMA_VALUE_DEALLOC(SpaceTreeNode)
PY_PLASMA_EMPTY_INIT(SpaceTreeNode)
PY_PLASMA_VALUE_NEW(SpaceTreeNode, plSpaceTreeNode)

PY_METHOD_NOARGS(SpaceTreeNode, getChildren,
    "Returns a tuple with the indices of the child nodes")
{
    PyObject* children = PyTuple_New(2);
    PyTuple_SET_ITEM(children, 0, pyPlasma_convert(self->fThis->getLChild()));
    PyTuple_SET_ITEM(children, 1, pyPlasma_convert(self->fThis->getRChild()));
    return children;
}

PY_METHOD_NOARGS(SpaceTreeNode, getLeafIndex, "Returns the node's leaf index")
{
    return pyPlasma_convert(self->fThis->getLeafIndex());
}

PY_METHOD_VA(SpaceTreeNode, setChildren,
    "Params: left, right\n"
    "Sets the node to a parent node with the specified child indices")
{
    int left, right;
    if (!PyArg_ParseTuple(args, "ii", &left, &right)) {
        PyErr_SetString(PyExc_TypeError, "setChildren expects int, int");
        return nullptr;
    }
    self->fThis->setChildren(left, right);
    Py_RETURN_NONE;
}

PY_METHOD_VA(SpaceTreeNode, setLeafIndex,
    "Params: idx\n"
    "Sets the node to a leaf node with the specified leaf index")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "setLeafIndex expects an int");
        return nullptr;
    }
    self->fThis->setLeafIndex(idx);
    Py_RETURN_NONE;
}

static PyMethodDef pySpaceTreeNode_Methods[] = {
    pySpaceTreeNode_getChildren_method,
    pySpaceTreeNode_getLeafIndex_method,
    pySpaceTreeNode_setChildren_method,
    pySpaceTreeNode_setLeafIndex_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY_BOUNDS(Bounds3Ext, SpaceTreeNode, bounds, getBounds, setBounds)
PY_PROPERTY(unsigned short, SpaceTreeNode, flags, getFlags, setFlags)
PY_PROPERTY(short, SpaceTreeNode, parent, getParent, setParent)

static PyGetSetDef pySpaceTreeNode_GetSet[] = {
    pySpaceTreeNode_bounds_getset,
    pySpaceTreeNode_flags_getset,
    pySpaceTreeNode_parent_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(SpaceTreeNode, plSpaceTreeNode, "plSpaceTreeNode wrapper")

PY_PLASMA_TYPE_INIT(SpaceTreeNode)
{
    pySpaceTreeNode_Type.tp_dealloc = pySpaceTreeNode_dealloc;
    pySpaceTreeNode_Type.tp_init = pySpaceTreeNode___init__;
    pySpaceTreeNode_Type.tp_new = pySpaceTreeNode_new;
    pySpaceTreeNode_Type.tp_methods = pySpaceTreeNode_Methods;
    pySpaceTreeNode_Type.tp_getset = pySpaceTreeNode_GetSet;
    if (PyType_CheckAndReady(&pySpaceTreeNode_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(SpaceTreeNode, "kNone", plSpaceTreeNode::kNone);
    PY_TYPE_ADD_CONST(SpaceTreeNode, "kIsLeaf", plSpaceTreeNode::kIsLeaf);
    PY_TYPE_ADD_CONST(SpaceTreeNode, "kDirty", plSpaceTreeNode::kDirty);
    PY_TYPE_ADD_CONST(SpaceTreeNode, "kDisabled", plSpaceTreeNode::kDisabled);
    PY_TYPE_ADD_CONST(SpaceTreeNode, "kEmpty", plSpaceTreeNode::kEmpty);
    PY_TYPE_ADD_CONST(SpaceTreeNode, "kEnabledTemp", plSpaceTreeNode::kEnabledTemp);

    Py_INCREF(&pySpaceTreeNode_Type);
    return (PyObject*)&pySpaceTreeNode_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(SpaceTreeNode, plSpaceTreeNode)
