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

PY_PLASMA_VALUE_NEW(VaultTextNoteNode, plVaultTextNoteNode)

PY_PROPERTY(int, VaultTextNoteNode, noteType, getNoteType, setNoteType)
PY_PROPERTY(int, VaultTextNoteNode, noteSubType, getNoteSubType, setNoteSubType)
PY_PROPERTY(ST::string, VaultTextNoteNode, noteTitle, getNoteTitle, setNoteTitle)

PY_GETSET_GETTER_DECL(VaultTextNoteNode, noteContents)
{
    return PyString_FromStringAndSize((const char*)self->fThis->getNoteContents().getData(),
                                      self->fThis->getNoteContents().getSize());
}

PY_GETSET_SETTER_DECL(VaultTextNoteNode, noteContents)
{
    if (value && PyAnyString_Check(value)) {
        ST::string str = PyAnyString_AsSTString(value);
        self->fThis->getNoteContents().setData(str.size(), (const unsigned char*)str.c_str());
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "noteContents is a string");
        return -1;
    }
}

PY_PROPERTY_GETSET_DECL(VaultTextNoteNode, noteContents)

static PyGetSetDef pyVaultTextNoteNode_GetSet[] = {
    pyVaultTextNoteNode_noteType_getset,
    pyVaultTextNoteNode_noteSubType_getset,
    pyVaultTextNoteNode_noteTitle_getset,
    pyVaultTextNoteNode_noteContents_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(VaultTextNoteNode, plVaultTextNoteNode, "plVaultTextNoteNode wrapper")

PY_PLASMA_TYPE_INIT(VaultTextNoteNode)
{
    pyVaultTextNoteNode_Type.tp_new = pyVaultTextNoteNode_new;
    pyVaultTextNoteNode_Type.tp_getset = pyVaultTextNoteNode_GetSet;
    pyVaultTextNoteNode_Type.tp_base = &pyVaultNode_Type;
    if (PyType_CheckAndReady(&pyVaultTextNoteNode_Type) < 0)
        return nullptr;

    Py_INCREF(&pyVaultTextNoteNode_Type);
    return (PyObject*)&pyVaultTextNoteNode_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(VaultTextNoteNode, plVaultTextNoteNode)
