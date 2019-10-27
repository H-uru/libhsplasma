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

PY_PLASMA_VALUE_NEW(VaultPlayerInfoNode, plVaultPlayerInfoNode)

PY_PROPERTY(int, VaultPlayerInfoNode, online, getOnline, setOnline)
PY_PROPERTY(unsigned int, VaultPlayerInfoNode, playerID, getPlayerID, setPlayerID)
PY_PROPERTY(ST::string, VaultPlayerInfoNode, ageInstName, getAgeInstName, setAgeInstName)
PY_PROPERTY(plServerGuid, VaultPlayerInfoNode, ageInstGuid, getAgeInstGuid, setAgeInstGuid)
PY_PROPERTY(ST::string, VaultPlayerInfoNode, playerName, getPlayerName, setPlayerName)

static PyGetSetDef pyVaultPlayerInfoNode_GetSet[] = {
    pyVaultPlayerInfoNode_online_getset,
    pyVaultPlayerInfoNode_playerID_getset,
    pyVaultPlayerInfoNode_ageInstName_getset,
    pyVaultPlayerInfoNode_ageInstGuid_getset,
    pyVaultPlayerInfoNode_playerName_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(VaultPlayerInfoNode, plVaultPlayerInfoNode, "plVaultPlayerInfoNode wrapper")

PY_PLASMA_TYPE_INIT(VaultPlayerInfoNode)
{
    pyVaultPlayerInfoNode_Type.tp_new = pyVaultPlayerInfoNode_new;
    pyVaultPlayerInfoNode_Type.tp_getset = pyVaultPlayerInfoNode_GetSet;
    pyVaultPlayerInfoNode_Type.tp_base = &pyVaultNode_Type;
    if (PyType_CheckAndReady(&pyVaultPlayerInfoNode_Type) < 0)
        return nullptr;

    Py_INCREF(&pyVaultPlayerInfoNode_Type);
    return (PyObject*)&pyVaultPlayerInfoNode_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(VaultPlayerInfoNode, plVaultPlayerInfoNode)
