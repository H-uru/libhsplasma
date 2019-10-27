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

#include "pyVaultStore.h"
#include "pyVaultNode.h"
#include "Stream/pyStream.h"

#include <Vault/plVaultStore.h>

PY_PLASMA_DEALLOC(VaultStore)
PY_PLASMA_EMPTY_INIT(VaultStore)
PY_PLASMA_NEW(VaultStore, plVaultStore)

PY_PLASMA_SUBSCRIPT_DECL(VaultStore)
{
    if (pyPlasma_check<unsigned int>(key)) {
        unsigned int nodeID = pyPlasma_get<unsigned int>(key);
        if (nodeID < self->fThis->getFirstNodeID() || nodeID > self->fThis->getLastNodeID()) {
            PyErr_SetNone(PyExc_LookupError);
            return nullptr;
        }
        return pyPlasma_convert(self->fThis->getNode(nodeID));
    } else {
        PyErr_SetString(PyExc_TypeError, "key should be an int");
        return nullptr;
    }
}

PY_PLASMA_ASS_SUBSCRIPT_DECL(VaultStore)
{
    if (!pyPlasma_check<unsigned int>(key)) {
        PyErr_SetString(PyExc_TypeError, "key should be an int");
        return -1;
    }

    if (value == nullptr || value == Py_None) {
        self->fThis->delNode(pyPlasma_get<unsigned int>(key));
        return 0;
    } else {
        PyErr_SetString(PyExc_RuntimeError, "To add a node, use addNode()");
        return -1;
    }
}

PY_METHOD_VA(VaultStore, Import,
    "Params: source\n"
    "Imports a vault data store from a file or stream")
{
    ST::string filename;
    PyObject* stream;
    if (PyArg_ParseTuple(args, "O&", PyAnyString_PathDecoder, &filename)) {
        try {
            self->fThis->ImportFile(filename);
            Py_RETURN_NONE;
        } catch (const std::exception& ex) {
            PyErr_SetString(PyExc_IOError, ex.what());
            return nullptr;
        }
    } else if (PyErr_Clear(), PyArg_ParseTuple(args, "O", &stream) && pyStream_Check(stream)) {
        try {
            self->fThis->Import(((pyStream*)stream)->fThis);
            Py_RETURN_NONE;
        } catch (const std::exception & ex) {
            PyErr_SetString(PyExc_IOError, ex.what());
            return nullptr;
        }
    } else {
        PyErr_SetString(PyExc_TypeError, "Import expects string or stream");
        return nullptr;
    }
}

PY_METHOD_VA(VaultStore, Export,
    "Params: destination, encrypt\n"
    "Exports a vault data store to a file or stream")
{
    ST::string filename;
    bool encrypt = true;
    PyObject* stream;
    if (PyArg_ParseTuple(args, "O&|b", PyAnyString_PathDecoder, &filename, &encrypt)) {
        try {
            self->fThis->ExportFile(filename);
            Py_RETURN_NONE;
        } catch (const std::exception & ex) {
            PyErr_SetString(PyExc_IOError, ex.what());
            return nullptr;
        }
    } else if (PyErr_Clear(), PyArg_ParseTuple(args, "O", &stream) && pyStream_Check(stream)) {
        try {
            self->fThis->Export(((pyStream*)stream)->fThis);
            Py_RETURN_NONE;
        } catch (const std::exception & ex) {
            PyErr_SetString(PyExc_IOError, ex.what());
            return nullptr;
        }
    } else {
        PyErr_SetString(PyExc_TypeError, "Export expects string (and an optional bool) or stream");
        return nullptr;
    }
}

PY_METHOD_VA(VaultStore, getChildren,
    "Params: parent\n"
    "Returns a copy of the immediate children of the requested node")
{
    unsigned int idx;
    if (!PyArg_ParseTuple(args, "I", &idx)) {
        PyErr_SetString(PyExc_TypeError, "getChildren expects an int");
        return nullptr;
    }

    std::vector<plVaultNode> children = self->fThis->getChildren(idx);
    PyObject* tup = PyTuple_New(children.size());
    for (size_t i = 0; i < children.size(); ++i)
        PyTuple_SET_ITEM(tup, i, pyPlasma_convert(children[i]));
    return tup;
}

PY_METHOD_VA(VaultStore, findParents,
    "Params: child\n"
    "Returns a copy of the immediate parents of the requested node")
{
    unsigned int idx;
    if (!PyArg_ParseTuple(args, "I", &idx)) {
        PyErr_SetString(PyExc_TypeError, "findParents expects an int");
        return nullptr;
    }

    std::vector<plVaultNode> children = self->fThis->findParents(idx);
    PyObject* tup = PyTuple_New(children.size());
    for (size_t i = 0; i < children.size(); ++i)
        PyTuple_SET_ITEM(tup, i, pyPlasma_convert(children[i]));
    return tup;
}

PY_METHOD_VA(VaultStore, addNode,
    "Params: node\n"
    "Adds a copy of the given node to the vault store")
{
    PyObject* node;
    if (!PyArg_ParseTuple(args, "O", &node) || !pyPlasma_check<plVaultNode>(node)) {
        PyErr_SetString(PyExc_TypeError, "addNode expects a plVaultNode");
        return nullptr;
    }

    // Not returning the stored reference to Python due to ownership assumptions
    self->fThis->addNode(pyPlasma_get<plVaultNode>(node));
    Py_RETURN_NONE;
}

PY_METHOD_VA(VaultStore, addRef,
    "Params: parent, child, saver\n"
    "Adds a node reference")
{
    unsigned int parent;
    unsigned int child;
    unsigned int saver = 0;
    if (!PyArg_ParseTuple(args, "II|I", &parent, &child, &saver)) {
        PyErr_SetString(PyExc_TypeError, "addRef expects int, int, and an optional int");
        return nullptr;
    }

    self->fThis->addRef(parent, child, saver);
    Py_RETURN_NONE;
}

PY_METHOD_VA(VaultStore, delRef,
    "Params: parent, child\n"
    "Deletes a node reference")
{
    unsigned int parent;
    unsigned int child;
    if (!PyArg_ParseTuple(args, "II", &parent, &child)) {
        PyErr_SetString(PyExc_TypeError, "delRef expects int, int");
        return nullptr;
    }

    self->fThis->delRef(parent, child);
    Py_RETURN_NONE;
}

static PyMethodDef pyVaultStore_Methods[] = {
    pyVaultStore_Import_method,
    pyVaultStore_Export_method,
    pyVaultStore_getChildren_method,
    pyVaultStore_findParents_method,
    pyVaultStore_addNode_method,
    pyVaultStore_addRef_method,
    pyVaultStore_delRef_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY_RO(VaultStore, firstNodeID, getFirstNodeID)
PY_PROPERTY_RO(VaultStore, lastNodeID, getLastNodeID)

static PyGetSetDef pyVaultStore_GetSet[] = {
    pyVaultStore_firstNodeID_getset,
    pyVaultStore_lastNodeID_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(VaultStore, plVaultStore, "plVaultStore wrapper")
PY_PLASMA_TYPE_AS_MAPPING(VaultStore)

PY_PLASMA_TYPE_INIT(VaultStore)
{
    pyVaultStore_As_Mapping.mp_subscript = pyVaultStore_mp_subscript;
    pyVaultStore_As_Mapping.mp_ass_subscript = pyVaultStore_mp_ass_subscript;
    pyVaultStore_Type.tp_dealloc = pyVaultStore_dealloc;
    pyVaultStore_Type.tp_init = pyVaultStore___init__;
    pyVaultStore_Type.tp_new = pyVaultStore_new;
    pyVaultStore_Type.tp_as_mapping = &pyVaultStore_As_Mapping;
    pyVaultStore_Type.tp_methods = pyVaultStore_Methods;
    pyVaultStore_Type.tp_getset = pyVaultStore_GetSet;
    if (PyType_CheckAndReady(&pyVaultStore_Type) < 0)
        return nullptr;

    Py_INCREF(&pyVaultStore_Type);
    return (PyObject*)&pyVaultStore_Type;
}

PY_PLASMA_IFC_METHODS(VaultStore, plVaultStore)
