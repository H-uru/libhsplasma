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

PY_PLASMA_VALUE_NEW(VaultSDLNode, plVaultSDLNode)

PY_PROPERTY(int, VaultSDLNode, sdlIdent, getSDLIdent, setSDLIdent)

PY_GETSET_GETTER_DECL(VaultSDLNode, sdlData)
{
    return PyBytes_FromStringAndSize((const char*)self->fThis->getSDLData().getData(),
                                     self->fThis->getSDLData().getSize());
}

PY_GETSET_SETTER_DECL(VaultSDLNode, sdlData)
{
    if (value == nullptr || value == Py_None) {
        self->fThis->getSDLData().setData(0, nullptr);
        return 0;
    } else if (PyBytes_Check(value)) {
        char* buf;
        Py_ssize_t size;
        PyBytes_AsStringAndSize(value, &buf, &size);
        self->fThis->getSDLData().setData(size, (unsigned char*)buf);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "sdlData should be a bytes object");
        return -1;
    }
}

PY_PROPERTY_GETSET_DECL(VaultSDLNode, sdlData)

static PyGetSetDef pyVaultSDLNode_GetSet[] = {
    pyVaultSDLNode_sdlIdent_getset,
    pyVaultSDLNode_sdlData_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(VaultSDLNode, plVaultSDLNode, "plVaultSDLNode wrapper")

PY_PLASMA_TYPE_INIT(VaultSDLNode)
{
    pyVaultSDLNode_Type.tp_new = pyVaultSDLNode_new;
    pyVaultSDLNode_Type.tp_getset = pyVaultSDLNode_GetSet;
    pyVaultSDLNode_Type.tp_base = &pyVaultNode_Type;
    if (PyType_CheckAndReady(&pyVaultSDLNode_Type) < 0)
        return nullptr;

    Py_INCREF(&pyVaultSDLNode_Type);
    return (PyObject*)&pyVaultSDLNode_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(VaultSDLNode, plVaultSDLNode)
