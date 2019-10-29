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

PY_PLASMA_VALUE_NEW(VaultAgeLinkNode, plVaultAgeLinkNode)

PY_PROPERTY(int, VaultAgeLinkNode, unlocked, getUnlocked, setUnlocked)
PY_PROPERTY(int, VaultAgeLinkNode, volatile, getVolatile, setVolatile)

PY_GETSET_GETTER_DECL(VaultAgeLinkNode, spawnPoints)
{
    return PyString_FromStringAndSize((const char*)self->fThis->getSpawnPoints().getData(),
                                      self->fThis->getSpawnPoints().getSize());
}

PY_GETSET_SETTER_DECL(VaultAgeLinkNode, spawnPoints)
{
    if (value && PyAnyString_Check(value)) {
        ST::string str = PyAnyString_AsSTString(value);
        self->fThis->getSpawnPoints().setData(str.size(), (const unsigned char*)str.c_str());
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "spawnPoints is a string");
        return -1;
    }
}

PY_PROPERTY_GETSET_DECL(VaultAgeLinkNode, spawnPoints)

static PyGetSetDef pyVaultAgeLinkNode_GetSet[] = {
    pyVaultAgeLinkNode_unlocked_getset,
    pyVaultAgeLinkNode_volatile_getset,
    pyVaultAgeLinkNode_spawnPoints_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(VaultAgeLinkNode, plVaultAgeLinkNode, "plVaultAgeLinkNode wrapper")

PY_PLASMA_TYPE_INIT(VaultAgeLinkNode)
{
    pyVaultAgeLinkNode_Type.tp_new = pyVaultAgeLinkNode_new;
    pyVaultAgeLinkNode_Type.tp_getset = pyVaultAgeLinkNode_GetSet;
    pyVaultAgeLinkNode_Type.tp_base = &pyVaultNode_Type;
    if (PyType_CheckAndReady(&pyVaultAgeLinkNode_Type) < 0)
        return nullptr;

    Py_INCREF(&pyVaultAgeLinkNode_Type);
    return (PyObject*)&pyVaultAgeLinkNode_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(VaultAgeLinkNode, plVaultAgeLinkNode)
