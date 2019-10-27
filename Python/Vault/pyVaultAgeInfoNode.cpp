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

PY_PLASMA_VALUE_NEW(VaultAgeInfoNode, plVaultAgeInfoNode)

PY_PROPERTY(int, VaultAgeInfoNode, ageSequenceNumber, getAgeSequenceNumber, setAgeSequenceNumber)
PY_PROPERTY(int, VaultAgeInfoNode, isPublic, getIsPublic, setIsPublic)
PY_PROPERTY(int, VaultAgeInfoNode, ageLanguage, getAgeLanguage, setAgeLanguage)
PY_PROPERTY(unsigned int, VaultAgeInfoNode, ageID, getAgeID, setAgeID)
PY_PROPERTY(unsigned int, VaultAgeInfoNode, ageCzarID, getAgeCzarID, setAgeCzarID)
PY_PROPERTY(unsigned int, VaultAgeInfoNode, ageInfoFlags, getAgeInfoFlags, setAgeInfoFlags)
PY_PROPERTY(ST::string, VaultAgeInfoNode, ageFilename, getAgeFilename, setAgeFilename)
PY_PROPERTY(ST::string, VaultAgeInfoNode, ageInstanceName, getAgeInstanceName, setAgeInstanceName)
PY_PROPERTY(plServerGuid, VaultAgeInfoNode, ageInstanceGuid, getAgeInstanceGuid, setAgeInstanceGuid)
PY_PROPERTY(ST::string, VaultAgeInfoNode, ageDescription, getAgeDescription, setAgeDescription)

static PyGetSetDef pyVaultAgeInfoNode_GetSet[] = {
    pyVaultAgeInfoNode_ageSequenceNumber_getset,
    pyVaultAgeInfoNode_isPublic_getset,
    pyVaultAgeInfoNode_ageLanguage_getset,
    pyVaultAgeInfoNode_ageID_getset,
    pyVaultAgeInfoNode_ageCzarID_getset,
    pyVaultAgeInfoNode_ageInfoFlags_getset,
    pyVaultAgeInfoNode_ageFilename_getset,
    pyVaultAgeInfoNode_ageInstanceName_getset,
    pyVaultAgeInfoNode_ageInstanceGuid_getset,
    pyVaultAgeInfoNode_ageDescription_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(VaultAgeInfoNode, plVaultAgeInfoNode, "plVaultAgeInfoNode wrapper")

PY_PLASMA_TYPE_INIT(VaultAgeInfoNode)
{
    pyVaultAgeInfoNode_Type.tp_new = pyVaultAgeInfoNode_new;
    pyVaultAgeInfoNode_Type.tp_getset = pyVaultAgeInfoNode_GetSet;
    pyVaultAgeInfoNode_Type.tp_base = &pyVaultNode_Type;
    if (PyType_CheckAndReady(&pyVaultAgeInfoNode_Type) < 0)
        return nullptr;

    Py_INCREF(&pyVaultAgeInfoNode_Type);
    return (PyObject*)&pyVaultAgeInfoNode_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(VaultAgeInfoNode, plVaultAgeInfoNode)
