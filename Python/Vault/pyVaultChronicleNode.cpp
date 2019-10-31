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

PY_PLASMA_VALUE_NEW(VaultChronicleNode, plVaultChronicleNode)

PY_PROPERTY(int, VaultChronicleNode, entryType, getEntryType, setEntryType)
PY_PROPERTY(ST::string, VaultChronicleNode, entryName, getEntryName, setEntryName)
PY_PROPERTY(ST::string, VaultChronicleNode, entryValue, getEntryValue, setEntryValue)

static PyGetSetDef pyVaultChronicleNode_GetSet[] = {
    pyVaultChronicleNode_entryType_getset,
    pyVaultChronicleNode_entryName_getset,
    pyVaultChronicleNode_entryValue_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(VaultChronicleNode, plVaultChronicleNode, "plVaultChronicleNode wrapper")

PY_PLASMA_TYPE_INIT(VaultChronicleNode)
{
    pyVaultChronicleNode_Type.tp_new = pyVaultChronicleNode_new;
    pyVaultChronicleNode_Type.tp_getset = pyVaultChronicleNode_GetSet;
    pyVaultChronicleNode_Type.tp_base = &pyVaultNode_Type;
    if (PyType_CheckAndReady(&pyVaultChronicleNode_Type) < 0)
        return nullptr;

    Py_INCREF(&pyVaultChronicleNode_Type);
    return (PyObject*)&pyVaultChronicleNode_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(VaultChronicleNode, plVaultChronicleNode)
