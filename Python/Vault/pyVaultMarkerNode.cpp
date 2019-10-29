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

PY_PLASMA_VALUE_NEW(VaultMarkerNode, plVaultMarkerNode)

PY_PROPERTY(ST::string, VaultMarkerNode, ageName, getAgeName, setAgeName)
PY_PROPERTY(int, VaultMarkerNode, torans, getTorans, setTorans)
PY_PROPERTY(int, VaultMarkerNode, hSpans, getHSpans, setHSpans)
PY_PROPERTY(int, VaultMarkerNode, vSpans, getVSpans, setVSpans)
PY_PROPERTY(float, VaultMarkerNode, markerPosX, getMarkerPosX, setMarkerPosX)
PY_PROPERTY(float, VaultMarkerNode, markerPosY, getMarkerPosY, setMarkerPosY)
PY_PROPERTY(float, VaultMarkerNode, markerPosZ, getMarkerPosZ, setMarkerPosZ)
PY_PROPERTY(ST::string, VaultMarkerNode, markerText, getMarkerText, setMarkerText)

static PyGetSetDef pyVaultMarkerNode_GetSet[] = {
    pyVaultMarkerNode_ageName_getset,
    pyVaultMarkerNode_torans_getset,
    pyVaultMarkerNode_hSpans_getset,
    pyVaultMarkerNode_vSpans_getset,
    pyVaultMarkerNode_markerPosX_getset,
    pyVaultMarkerNode_markerPosY_getset,
    pyVaultMarkerNode_markerPosZ_getset,
    pyVaultMarkerNode_markerText_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(VaultMarkerNode, plVaultMarkerNode, "plVaultMarkerNode wrapper")

PY_PLASMA_TYPE_INIT(VaultMarkerNode)
{
    pyVaultMarkerNode_Type.tp_new = pyVaultMarkerNode_new;
    pyVaultMarkerNode_Type.tp_getset = pyVaultMarkerNode_GetSet;
    pyVaultMarkerNode_Type.tp_base = &pyVaultNode_Type;
    if (PyType_CheckAndReady(&pyVaultMarkerNode_Type) < 0)
        return nullptr;

    Py_INCREF(&pyVaultMarkerNode_Type);
    return (PyObject*)&pyVaultMarkerNode_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(VaultMarkerNode, plVaultMarkerNode)
