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

#include "pyVaultNode.h"
#include "pyServerGuid.h"
#include "Sys/pyUnifiedTime.h"

PY_PLASMA_VALUE_DEALLOC(VaultNode)
PY_PLASMA_EMPTY_INIT(VaultNode)
PY_PLASMA_VALUE_NEW(VaultNode, plVaultNode)

PY_METHOD_VA(VaultNode, hasField,
    "Params: field\n"
    "Returns if the node uses the given field")
{
    unsigned int field;
    if (!PyArg_ParseTuple(args, "I", &field)) {
        PyErr_SetString(PyExc_TypeError, "hasField expects an unsigned int");
        return nullptr;
    }
    return PyBool_FromBool(self->fThis->hasField(field));
}

PY_METHOD_VA(VaultNode, delField,
             "Params: field\n"
             "Deletes the requested field from the node")
{
    unsigned int field;
    if (!PyArg_ParseTuple(args, "I", &field)) {
        PyErr_SetString(PyExc_TypeError, "delField expects an unsigned int");
        return nullptr;
    }
    self->fThis->delField(field);
    Py_RETURN_NONE;
}

static PyMethodDef pyVaultNode_Methods[] = {
    pyVaultNode_hasField_method,
    pyVaultNode_delField_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY_RO(VaultNode, isValid, isValid)
PY_PROPERTY(unsigned int, VaultNode, nodeID, getNodeID, setNodeID)
PY_PROPERTY(unsigned int, VaultNode, group, getGroup, setGroup)
PY_PROPERTY(unsigned int, VaultNode, creator, getCreator, setCreator)

PY_PROPERTY_READ(VaultNode, nodeType, getNodeType)
PY_GETSET_SETTER_DECL(VaultNode, nodeType)
{
    if (value && pyPlasma_check<unsigned int>(value)) {
        // Magickal code to cast the node to its new type
        unsigned int newType = pyPlasma_get<unsigned int>(value);
        switch (newType) {
        case plVault::kNodePlayer:
            Py_TYPE(self) = &pyVaultPlayerNode_Type;
            break;
        case plVault::kNodeAge:
            Py_TYPE(self) = &pyVaultAgeNode_Type;
            break;
        case plVault::kNodeGameServer:
            Py_TYPE(self) = &pyVaultGameServerNode_Type;
            break;
        case plVault::kNodeAdmin:
            Py_TYPE(self) = &pyVaultAdminNode_Type;
            break;
        case plVault::kNodeVaultServer:
            Py_TYPE(self) = &pyVaultServerNode_Type;
            break;
        case plVault::kNodeFolder:
            Py_TYPE(self) = &pyVaultFolderNode_Type;
            break;
        case plVault::kNodePlayerInfo:
            Py_TYPE(self) = &pyVaultPlayerInfoNode_Type;
            break;
        case plVault::kNodeSystem:
            Py_TYPE(self) = &pyVaultSystemNode_Type;
            break;
        case plVault::kNodeImage:
            Py_TYPE(self) = &pyVaultImageNode_Type;
            break;
        case plVault::kNodeTextNote:
            Py_TYPE(self) = &pyVaultTextNoteNode_Type;
            break;
        case plVault::kNodeSDL:
            Py_TYPE(self) = &pyVaultSDLNode_Type;
            break;
        case plVault::kNodeAgeLink:
            Py_TYPE(self) = &pyVaultAgeLinkNode_Type;
            break;
        case plVault::kNodeChronicle:
            Py_TYPE(self) = &pyVaultChronicleNode_Type;
            break;
        case plVault::kNodePlayerInfoList:
            Py_TYPE(self) = &pyVaultPlayerInfoListNode_Type;
            break;
        case plVault::kNodeMarker:
            Py_TYPE(self) = &pyVaultMarkerNode_Type;
            break;
        case plVault::kNodeAgeInfo:
            Py_TYPE(self) = &pyVaultAgeInfoNode_Type;
            break;
        case plVault::kNodeAgeInfoList:
            Py_TYPE(self) = &pyVaultAgeInfoListNode_Type;
            break;
        case plVault::kNodeMarkerList:
            Py_TYPE(self) = &pyVaultMarkerListNode_Type;
            break;
        case plVault::kNodeInvalid:
        case plVault::kNodeVNodeMgrLow:
        case plVault::kNodeCCR:
        case plVault::kNodeVNodeMgrHigh:
        case plVault::kNodeUNUSED:
            Py_TYPE(self) = &pyVaultNode_Type;
            break;
        default:
            PyErr_SetString(PyExc_ValueError, "Invalid node type");
            return -1;
        }
        self->fThis->setNodeType(newType);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "nodeType should be an int");
        return -1;
    }
}
PY_PROPERTY_GETSET_DECL(VaultNode, nodeType)

PY_PROPERTY(unsigned int, VaultNode, permissions, getPermissions, setPermissions)
PY_PROPERTY(plUnifiedTime, VaultNode, autoTime, getAutoTime, setAutoTime)
PY_PROPERTY(plUnifiedTime, VaultNode, modifyTime, getModifyTime, setModifyTime)
PY_PROPERTY(plUnifiedTime, VaultNode, createAgeTime, getCreateAgeTime, setCreateAgeTime)
PY_PROPERTY(ST::string, VaultNode, createAgeName, getCreateAgeName, setCreateAgeName)
PY_PROPERTY(plServerGuid, VaultNode, createAgeGuid, getCreateAgeGuid, setCreateAgeGuid)
PY_PROPERTY(plServerGuid, VaultNode, guid1, getGuid1, setGuid1)
PY_PROPERTY(plServerGuid, VaultNode, guid2, getGuid2, setGuid2)
PY_PROPERTY(int, VaultNode, int32_1, getInt32_1, setInt32_1)
PY_PROPERTY(int, VaultNode, int32_2, getInt32_2, setInt32_2)
PY_PROPERTY(int, VaultNode, int32_3, getInt32_3, setInt32_3)
PY_PROPERTY(int, VaultNode, int32_4, getInt32_4, setInt32_4)
PY_PROPERTY(unsigned int, VaultNode, uint32_1, getUInt32_1, setUInt32_1)
PY_PROPERTY(unsigned int, VaultNode, uint32_2, getUInt32_2, setUInt32_2)
PY_PROPERTY(unsigned int, VaultNode, uint32_3, getUInt32_3, setUInt32_3)
PY_PROPERTY(unsigned int, VaultNode, uint32_4, getUInt32_4, setUInt32_4)
PY_PROPERTY(ST::string, VaultNode, string64_1, getString64_1, setString64_1)
PY_PROPERTY(ST::string, VaultNode, string64_2, getString64_2, setString64_2)
PY_PROPERTY(ST::string, VaultNode, string64_3, getString64_3, setString64_3)
PY_PROPERTY(ST::string, VaultNode, string64_4, getString64_4, setString64_4)
PY_PROPERTY(ST::string, VaultNode, string64_5, getString64_5, setString64_5)
PY_PROPERTY(ST::string, VaultNode, string64_6, getString64_6, setString64_6)
PY_PROPERTY(ST::string, VaultNode, istring64_1, getIString64_1, setIString64_1)
PY_PROPERTY(ST::string, VaultNode, istring64_2, getIString64_2, setIString64_2)
PY_PROPERTY(ST::string, VaultNode, text_1, getText_1, setText_1)
PY_PROPERTY(ST::string, VaultNode, text_2, getText_2, setText_2)

PY_GETSET_GETTER_DECL(VaultNode, blob_1)
{
    return PyBytes_FromStringAndSize((const char*)self->fThis->getBlob_1().getData(),
                                     self->fThis->getBlob_1().getSize());
}

PY_GETSET_SETTER_DECL(VaultNode, blob_1)
{
    if (value == nullptr || value == Py_None) {
        self->fThis->getBlob_1().setData(0, nullptr);
        return 0;
    } else if (PyBytes_Check(value)) {
        char* buf;
        Py_ssize_t size;
        PyBytes_AsStringAndSize(value, &buf, &size);
        self->fThis->getBlob_1().setData(size, (unsigned char*)buf);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "blob_1 should be a bytes object");
        return -1;
    }
}

PY_PROPERTY_GETSET_DECL(VaultNode, blob_1)

PY_GETSET_GETTER_DECL(VaultNode, blob_2)
{
    return PyBytes_FromStringAndSize((const char*)self->fThis->getBlob_2().getData(),
                                     self->fThis->getBlob_2().getSize());
}

PY_GETSET_SETTER_DECL(VaultNode, blob_2)
{
    if (value == nullptr || value == Py_None) {
        self->fThis->getBlob_2().setData(0, nullptr);
        return 0;
    } else if (PyBytes_Check(value)) {
        char* buf;
        Py_ssize_t size;
        PyBytes_AsStringAndSize(value, &buf, &size);
        self->fThis->getBlob_2().setData(size, (unsigned char*)buf);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "blob_2 should be a bytes object");
        return -1;
    }
}

PY_PROPERTY_GETSET_DECL(VaultNode, blob_2)

static PyGetSetDef pyVaultNode_GetSet[] = {
    pyVaultNode_isValid_getset,
    pyVaultNode_nodeID_getset,
    pyVaultNode_group_getset,
    pyVaultNode_creator_getset,
    pyVaultNode_nodeType_getset,
    pyVaultNode_permissions_getset,
    pyVaultNode_autoTime_getset,
    pyVaultNode_modifyTime_getset,
    pyVaultNode_createAgeTime_getset,
    pyVaultNode_createAgeGuid_getset,
    pyVaultNode_guid1_getset,
    pyVaultNode_guid2_getset,
    pyVaultNode_createAgeName_getset,
    pyVaultNode_int32_1_getset,
    pyVaultNode_int32_2_getset,
    pyVaultNode_int32_3_getset,
    pyVaultNode_int32_4_getset,
    pyVaultNode_uint32_1_getset,
    pyVaultNode_uint32_2_getset,
    pyVaultNode_uint32_3_getset,
    pyVaultNode_uint32_4_getset,
    pyVaultNode_string64_1_getset,
    pyVaultNode_string64_2_getset,
    pyVaultNode_string64_3_getset,
    pyVaultNode_string64_4_getset,
    pyVaultNode_string64_5_getset,
    pyVaultNode_string64_6_getset,
    pyVaultNode_istring64_1_getset,
    pyVaultNode_istring64_2_getset,
    pyVaultNode_text_1_getset,
    pyVaultNode_text_2_getset,
    pyVaultNode_blob_1_getset,
    pyVaultNode_blob_2_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(VaultNode, plVaultNode, "plVaultNode wrapper")

PY_PLASMA_TYPE_INIT(VaultNode)
{
    pyVaultNode_Type.tp_dealloc = pyVaultNode_dealloc;
    pyVaultNode_Type.tp_init = pyVaultNode___init__;
    pyVaultNode_Type.tp_new = pyVaultNode_new;
    pyVaultNode_Type.tp_methods = pyVaultNode_Methods;
    pyVaultNode_Type.tp_getset = pyVaultNode_GetSet;
    if (PyType_CheckAndReady(&pyVaultNode_Type) < 0)
        return nullptr;

    Py_INCREF(&pyVaultNode_Type);
    return (PyObject*)&pyVaultNode_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(VaultNode, plVaultNode)
