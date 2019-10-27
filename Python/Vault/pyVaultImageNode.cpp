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

PY_PLASMA_VALUE_NEW(VaultImageNode, plVaultImageNode)

PY_PLASMA_TYPE(VaultImageNode, plVaultImageNode, "plVaultImageNode wrapper")

PY_PROPERTY(int, VaultImageNode, imageType, getImageType, setImageType)
PY_PROPERTY(ST::string, VaultImageNode, imageTitle, getImageTitle, setImageTitle)

PY_GETSET_GETTER_DECL(VaultImageNode, imageData)
{
    return PyBytes_FromStringAndSize((const char*)self->fThis->getImageData().getData(),
                                     self->fThis->getImageData().getSize());
}

PY_GETSET_SETTER_DECL(VaultImageNode, imageData)
{
    if (value == nullptr || value == Py_None) {
        self->fThis->getImageData().setData(0, nullptr);
        return 0;
    } else if (PyBytes_Check(value)) {
        char* buf;
        Py_ssize_t size;
        PyBytes_AsStringAndSize(value, &buf, &size);
        self->fThis->getImageData().setData(size, (unsigned char*)buf);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "imageData should be a bytes object");
        return -1;
    }
}

PY_PROPERTY_GETSET_DECL(VaultImageNode, imageData)

static PyGetSetDef pyVaultImageNode_GetSet[] = {
    pyVaultImageNode_imageType_getset,
    pyVaultImageNode_imageTitle_getset,
    pyVaultImageNode_imageData_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE_INIT(VaultImageNode)
{
    pyVaultImageNode_Type.tp_new = pyVaultImageNode_new;
    pyVaultImageNode_Type.tp_base = &pyVaultNode_Type;
    pyVaultImageNode_Type.tp_getset = pyVaultImageNode_GetSet;
    if (PyType_CheckAndReady(&pyVaultImageNode_Type) < 0)
        return nullptr;

    Py_INCREF(&pyVaultImageNode_Type);
    return (PyObject*)&pyVaultImageNode_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(VaultImageNode, plVaultImageNode)
