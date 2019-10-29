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

PY_PLASMA_VALUE_NEW(VaultAgeNode, plVaultAgeNode)

PY_PROPERTY(plServerGuid, VaultAgeNode, ageInstanceGuid, getAgeInstanceGuid, setAgeInstanceGuid)

static PyGetSetDef pyVaultAgeNode_GetSet[] = {
    pyVaultAgeNode_ageInstanceGuid_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(VaultAgeNode, plVaultAgeNode, "plVaultAgeNode wrapper")

PY_PLASMA_TYPE_INIT(VaultAgeNode)
{
    pyVaultAgeNode_Type.tp_new = pyVaultAgeNode_new;
    pyVaultAgeNode_Type.tp_getset = pyVaultAgeNode_GetSet;
    pyVaultAgeNode_Type.tp_base = &pyVaultNode_Type;
    if (PyType_CheckAndReady(&pyVaultAgeNode_Type) < 0)
        return nullptr;

    Py_INCREF(&pyVaultAgeNode_Type);
    return (PyObject*)&pyVaultAgeNode_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(VaultAgeNode, plVaultAgeNode)
