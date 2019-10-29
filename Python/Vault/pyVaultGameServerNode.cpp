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

PY_PLASMA_VALUE_NEW(VaultGameServerNode, plVaultGameServerNode)

PY_PROPERTY(ST::string, VaultGameServerNode, ageFilename, getAgeFilename, setAgeFilename)
PY_PROPERTY(plServerGuid, VaultGameServerNode, ageInstanceGuid, getAgeInstanceGuid, setAgeInstanceGuid)

static PyGetSetDef pyVaultGameServerNode_GetSet[] = {
    pyVaultGameServerNode_ageFilename_getset,
    pyVaultGameServerNode_ageInstanceGuid_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(VaultGameServerNode, plVaultGameServerNode, "plVaultGameServerNode wrapper")

PY_PLASMA_TYPE_INIT(VaultGameServerNode)
{
    pyVaultGameServerNode_Type.tp_new = pyVaultGameServerNode_new;
    pyVaultGameServerNode_Type.tp_getset = pyVaultGameServerNode_GetSet;
    pyVaultGameServerNode_Type.tp_base = &pyVaultNode_Type;
    if (PyType_CheckAndReady(&pyVaultGameServerNode_Type) < 0)
        return nullptr;

    Py_INCREF(&pyVaultGameServerNode_Type);
    return (PyObject*)&pyVaultGameServerNode_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(VaultGameServerNode, plVaultGameServerNode)
