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

PY_PLASMA_VALUE_NEW(VaultPlayerInfoListNode, plVaultPlayerInfoListNode)

PY_PLASMA_TYPE(VaultPlayerInfoListNode, plVaultPlayerInfoListNode, "plVaultPlayerInfoListNode wrapper")

PY_PLASMA_TYPE_INIT(VaultPlayerInfoListNode)
{
    pyVaultPlayerInfoListNode_Type.tp_new = pyVaultPlayerInfoListNode_new;
    pyVaultPlayerInfoListNode_Type.tp_base = &pyVaultFolderNode_Type;
    if (PyType_CheckAndReady(&pyVaultPlayerInfoListNode_Type) < 0)
        return nullptr;

    Py_INCREF(&pyVaultPlayerInfoListNode_Type);
    return (PyObject*)&pyVaultPlayerInfoListNode_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(VaultPlayerInfoListNode, plVaultPlayerInfoListNode)
