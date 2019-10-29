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

PY_PLASMA_VALUE_NEW(VaultPlayerNode, plVaultPlayerNode)

PY_PROPERTY(int, VaultPlayerNode, disabled, getDisabled, setDisabled)
PY_PROPERTY(int, VaultPlayerNode, explorer, getExplorer, setExplorer)
PY_PROPERTY(unsigned int, VaultPlayerNode, onlineTime, getOnlineTime, setOnlineTime)
PY_PROPERTY(ST::string, VaultPlayerNode, avatarShape, getAvatarShape, setAvatarShape)
PY_PROPERTY(ST::string, VaultPlayerNode, playerName, getPlayerName, setPlayerName)
PY_PROPERTY(ST::string, VaultPlayerNode, accountUuid, getAccountUuid, setAccountUuid)

static PyGetSetDef pyVaultPlayerNode_GetSet[] = {
    pyVaultPlayerNode_disabled_getset,
    pyVaultPlayerNode_explorer_getset,
    pyVaultPlayerNode_onlineTime_getset,
    pyVaultPlayerNode_avatarShape_getset,
    pyVaultPlayerNode_playerName_getset,
    pyVaultPlayerNode_accountUuid_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(VaultPlayerNode, plVaultPlayerNode, "plVaultPlayerNode wrapper")

PY_PLASMA_TYPE_INIT(VaultPlayerNode)
{
    pyVaultPlayerNode_Type.tp_new = pyVaultPlayerNode_new;
    pyVaultPlayerNode_Type.tp_getset = pyVaultPlayerNode_GetSet;
    pyVaultPlayerNode_Type.tp_base = &pyVaultNode_Type;
    if (PyType_CheckAndReady(&pyVaultPlayerNode_Type) < 0)
        return nullptr;

    Py_INCREF(&pyVaultPlayerNode_Type);
    return (PyObject*)&pyVaultPlayerNode_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(VaultPlayerNode, plVaultPlayerNode)
