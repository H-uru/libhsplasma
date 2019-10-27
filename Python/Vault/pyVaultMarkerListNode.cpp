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

PY_PLASMA_VALUE_NEW(VaultMarkerListNode, plVaultMarkerListNode)

PY_PROPERTY(ST::string, VaultMarkerListNode, ageName, getAgeName, setAgeName)
PY_PROPERTY(int, VaultMarkerListNode, gameType, getGameType, setGameType)
PY_PROPERTY(int, VaultMarkerListNode, roundLength, getRoundLength, setRoundLength)
PY_PROPERTY(unsigned int, VaultMarkerListNode, authorID, getAuthorID, setAuthorID)
PY_PROPERTY(ST::string, VaultMarkerListNode, gameTitle, getGameTitle, setGameTitle)
PY_PROPERTY(ST::string, VaultMarkerListNode, authorName, getAuthorName, setAuthorName)

static PyGetSetDef pyVaultMarkerListNode_GetSet[] = {
    pyVaultMarkerListNode_ageName_getset,
    pyVaultMarkerListNode_gameType_getset,
    pyVaultMarkerListNode_roundLength_getset,
    pyVaultMarkerListNode_authorID_getset,
    pyVaultMarkerListNode_gameTitle_getset,
    pyVaultMarkerListNode_authorName_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(VaultMarkerListNode, plVaultMarkerListNode, "plVaultMarkerListNode wrapper")

PY_PLASMA_TYPE_INIT(VaultMarkerListNode)
{
    pyVaultMarkerListNode_Type.tp_new = pyVaultMarkerListNode_new;
    pyVaultMarkerListNode_Type.tp_getset = pyVaultMarkerListNode_GetSet;
    pyVaultMarkerListNode_Type.tp_base = &pyVaultNode_Type;
    if (PyType_CheckAndReady(&pyVaultMarkerListNode_Type) < 0)
        return nullptr;

    Py_INCREF(&pyVaultMarkerListNode_Type);
    return (PyObject*)&pyVaultMarkerListNode_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(VaultMarkerListNode, plVaultMarkerListNode)
