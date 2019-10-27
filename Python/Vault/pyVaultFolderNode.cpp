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

PY_PLASMA_VALUE_NEW(VaultFolderNode, plVaultFolderNode)

PY_PROPERTY(unsigned int, VaultFolderNode, folderType, getFolderType, setFolderType)
PY_PROPERTY(ST::string, VaultFolderNode, folderName, getFolderName, setFolderName)

static PyGetSetDef pyVaultFolderNode_GetSet[] = {
    pyVaultFolderNode_folderType_getset,
    pyVaultFolderNode_folderName_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(VaultFolderNode, plVaultFolderNode, "plVaultFolderNode wrapper")

PY_PLASMA_TYPE_INIT(VaultFolderNode)
{
    pyVaultFolderNode_Type.tp_new = pyVaultFolderNode_new;
    pyVaultFolderNode_Type.tp_getset = pyVaultFolderNode_GetSet;
    pyVaultFolderNode_Type.tp_base = &pyVaultNode_Type;
    if (PyType_CheckAndReady(&pyVaultFolderNode_Type) < 0)
        return nullptr;

    Py_INCREF(&pyVaultFolderNode_Type);
    return (PyObject*)&pyVaultFolderNode_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(VaultFolderNode, plVaultFolderNode)
