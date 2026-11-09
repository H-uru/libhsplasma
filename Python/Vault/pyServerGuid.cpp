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

#include "pyServerGuid.h"

PY_PLASMA_VALUE_DEALLOC(ServerGuid)

PY_PLASMA_INIT_DECL(ServerGuid)
{
    const char* str = nullptr;
    if (!PyArg_ParseTuple(args, "|s", &str)) {
        PyErr_SetString(PyExc_TypeError, "__init__ expects an optional string");
        return -1;
    }

    if (str)
        *(self->fThis) = plServerGuid::FromString(str);
    return 0;
}

PY_PLASMA_VALUE_NEW(ServerGuid, plServerGuid)

PY_PLASMA_LENGTH_DECL(ServerGuid)
{
    return 8;
}

PY_PLASMA_SUBSCRIPT_DECL(ServerGuid)
{
    if (pyPlasma_check<size_t>(key)) {
        size_t idx = pyPlasma_get<size_t>(key);
        if (idx > 7) {
            PyErr_SetNone(PyExc_IndexError);
            return nullptr;
        }
        return pyPlasma_convert(self->fThis[idx]);
    } else {
        PyErr_SetString(PyExc_TypeError, "mapping key is an int");
        return nullptr;
    }
}

PY_PLASMA_ASS_SUBSCRIPT_DECL(ServerGuid)
{
    if (value == nullptr || value == Py_None) {
        PyErr_SetString(PyExc_RuntimeError, "Cannot delete from mapping");
        return -1;
    }

    if (pyPlasma_check<size_t>(key)) {
        size_t idx = pyPlasma_get<size_t>(key);
        if (idx > 7) {
            PyErr_SetNone(PyExc_IndexError);
            return -1;
        }
        if (!pyPlasma_check<unsigned char>(value)) {
            PyErr_SetString(PyExc_TypeError, "mapping value is a byte");
            return -1;
        }
        self->fThis->operator[](idx) = pyPlasma_get<unsigned char>(value);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "mapping key is an int");
        return -1;
    }
}

PY_PLASMA_STR_DECL(ServerGuid)
{
    return PyUnicode_FromSTString(self->fThis->toString());
}

PY_PLASMA_RICHCOMPARE_DECL(ServerGuid)
{
    switch (op) {
    case Py_EQ:
        if (*left->fThis == *right->fThis)
            Py_RETURN_TRUE;
        else
            Py_RETURN_FALSE;
    case Py_NE:
        if (*left->fThis != *right->fThis)
            Py_RETURN_TRUE;
        else
            Py_RETURN_FALSE;
    default:
        PyErr_SetNone(PyExc_NotImplementedError);
        return nullptr;
    }
}

static PyType_Slot pyServerGuid_Slots[] = {
    PY_TYPE_SLOT(Py_tp_doc, "plServerGuid wrapper"),
    PY_TYPE_SLOT(Py_tp_dealloc, pyServerGuid_dealloc),
    PY_TYPE_SLOT(Py_tp_init, pyServerGuid___init__),
    PY_TYPE_SLOT(Py_tp_new, pyServerGuid_new),
    PY_TYPE_SLOT(Py_tp_richcompare, pyServerGuid_richcompare),
    PY_TYPE_SLOT(Py_tp_str, pyServerGuid_str),
    PY_TYPE_SLOT(Py_mp_ass_subscript, pyServerGuid_mp_ass_subscript),
    PY_TYPE_SLOT(Py_mp_length, pyServerGuid_length),
    PY_TYPE_SLOT(Py_mp_subscript, pyServerGuid_mp_subscript),
    PY_TYPE_SLOT_TERMINATOR
};

PY_PLASMA_TYPE_NO_BASE(ServerGuid, "hsServerGuid") { }

PY_PLASMA_VALUE_IFC_METHODS(ServerGuid, plServerGuid)
