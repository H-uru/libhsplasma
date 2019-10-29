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

#ifndef _PYVAULTNODE_H
#define _PYVAULTNODE_H

#include "PyPlasma.h"
#include <Vault/plVaultNode.h>
#include <Vault/plVaultNodeTypes.h>

extern PyTypeObject pyVault_Type;
PyObject* Init_pyVault_Type();

PY_WRAP_PLASMA_VALUE(VaultNode, plVaultNode);

PY_WRAP_PLASMA_VALUE(VaultPlayerNode, plVaultPlayerNode);
PY_WRAP_PLASMA_VALUE(VaultAgeNode, plVaultAgeNode);
PY_WRAP_PLASMA_VALUE(VaultGameServerNode, plVaultGameServerNode);
PY_WRAP_PLASMA_VALUE(VaultAdminNode, plVaultAdminNode);
PY_WRAP_PLASMA_VALUE(VaultServerNode, plVaultServerNode);
PY_WRAP_PLASMA_VALUE(VaultFolderNode, plVaultFolderNode);
PY_WRAP_PLASMA_VALUE(VaultPlayerInfoNode, plVaultPlayerInfoNode);
PY_WRAP_PLASMA_VALUE(VaultSystemNode, plVaultSystemNode);
PY_WRAP_PLASMA_VALUE(VaultImageNode, plVaultImageNode);
PY_WRAP_PLASMA_VALUE(VaultTextNoteNode, plVaultTextNoteNode);
PY_WRAP_PLASMA_VALUE(VaultSDLNode, plVaultSDLNode);
PY_WRAP_PLASMA_VALUE(VaultAgeLinkNode, plVaultAgeLinkNode);
PY_WRAP_PLASMA_VALUE(VaultChronicleNode, plVaultChronicleNode);
PY_WRAP_PLASMA_VALUE(VaultPlayerInfoListNode, plVaultPlayerInfoListNode);
PY_WRAP_PLASMA_VALUE(VaultMarkerNode, plVaultMarkerNode);
PY_WRAP_PLASMA_VALUE(VaultAgeInfoNode, plVaultAgeInfoNode);
PY_WRAP_PLASMA_VALUE(VaultAgeInfoListNode, plVaultAgeInfoListNode);
PY_WRAP_PLASMA_VALUE(VaultMarkerListNode, plVaultMarkerListNode);

inline PyObject* pyPlasma_convert(const plVaultNode& node)
{
    switch (node.getNodeType()) {
    case plVault::kNodePlayer:
        return pyVaultPlayerNode_FromVaultPlayerNode(*((plVaultPlayerNode*)&node));
    case plVault::kNodeAge:
        return pyVaultAgeNode_FromVaultAgeNode(*((plVaultAgeNode*)&node));
    case plVault::kNodeGameServer:
        return pyVaultGameServerNode_FromVaultGameServerNode(*((plVaultGameServerNode*)&node));
    case plVault::kNodeAdmin:
        return pyVaultAdminNode_FromVaultAdminNode(*((plVaultAdminNode*)&node));
    case plVault::kNodeVaultServer:
        return pyVaultServerNode_FromVaultServerNode(*((plVaultServerNode*)&node));
    case plVault::kNodeFolder:
        return pyVaultFolderNode_FromVaultFolderNode(*((plVaultFolderNode*)&node));
    case plVault::kNodePlayerInfo:
        return pyVaultPlayerInfoNode_FromVaultPlayerInfoNode(*((plVaultPlayerInfoNode*)&node));
    case plVault::kNodeSystem:
        return pyVaultSystemNode_FromVaultSystemNode(*((plVaultSystemNode*)&node));
    case plVault::kNodeImage:
        return pyVaultImageNode_FromVaultImageNode(*((plVaultImageNode*)&node));
    case plVault::kNodeTextNote:
        return pyVaultTextNoteNode_FromVaultTextNoteNode(*((plVaultTextNoteNode*)&node));
    case plVault::kNodeSDL:
        return pyVaultSDLNode_FromVaultSDLNode(*((plVaultSDLNode*)&node));
    case plVault::kNodeAgeLink:
        return pyVaultAgeLinkNode_FromVaultAgeLinkNode(*((plVaultAgeLinkNode*)&node));
    case plVault::kNodeChronicle:
        return pyVaultChronicleNode_FromVaultChronicleNode(*((plVaultChronicleNode*)&node));
    case plVault::kNodePlayerInfoList:
        return pyVaultPlayerInfoListNode_FromVaultPlayerInfoListNode(*((plVaultPlayerInfoListNode*)&node));
    case plVault::kNodeMarker:
        return pyVaultMarkerNode_FromVaultMarkerNode(*((plVaultMarkerNode*)&node));
    case plVault::kNodeAgeInfo:
        return pyVaultAgeInfoNode_FromVaultAgeInfoNode(*((plVaultAgeInfoNode*)&node));
    case plVault::kNodeAgeInfoList:
        return pyVaultAgeInfoListNode_FromVaultAgeInfoListNode(*((plVaultAgeInfoListNode*)&node));
    case plVault::kNodeMarkerList:
        return pyVaultMarkerListNode_FromVaultMarkerListNode(*((plVaultMarkerListNode*)&node));
    default:
        return pyVaultNode_FromVaultNode(node);
    }
}

template <> inline int pyPlasma_check<plVaultNode>(PyObject* value) { return pyVaultNode_Check(value); }
template <> inline plVaultNode pyPlasma_get(PyObject* value) { return *((pyVaultNode*)value)->fThis; }

#endif
