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

PY_PLASMA_VALUE_NEW(VaultSystemNode, plVaultSystemNode)

PY_PROPERTY(int, VaultSystemNode, ccrStatus, getCCRStatus, setCCRStatus)

static PyGetSetDef pyVaultSystemNode_GetSet[] = {
    pyVaultSystemNode_ccrStatus_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(VaultSystemNode, plVaultSystemNode, "plVaultSystemNode wrapper")

PY_PLASMA_TYPE_INIT(VaultSystemNode)
{
    pyVaultSystemNode_Type.tp_new = pyVaultSystemNode_new;
    pyVaultSystemNode_Type.tp_getset = pyVaultSystemNode_GetSet;
    pyVaultSystemNode_Type.tp_base = &pyVaultNode_Type;
    if (PyType_CheckAndReady(&pyVaultSystemNode_Type) < 0)
        return nullptr;

    Py_INCREF(&pyVaultSystemNode_Type);
    return (PyObject*)&pyVaultSystemNode_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(VaultSystemNode, plVaultSystemNode)
