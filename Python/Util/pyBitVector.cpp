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

#include "pyBitVector.h"

#include <Util/hsBitVector.h>
#include "Stream/pyStream.h"

PY_PLASMA_DEALLOC(BitVector)
PY_PLASMA_EMPTY_INIT(BitVector)
PY_PLASMA_NEW(BitVector, hsBitVector)

PY_PLASMA_SUBSCRIPT_DECL(BitVector)
{
    if (pyPlasma_check<ST::string>(key)) {
        ST::string name = pyPlasma_get<ST::string>(key);
        unsigned int idx = self->fThis->getValue(name.c_str());
        return pyPlasma_convert(self->fThis->get(idx));
    } else if (pyPlasma_check<unsigned int>(key)) {
        unsigned int idx = pyPlasma_get<unsigned int>(key);
        return pyPlasma_convert(self->fThis->get(idx));
    } else {
        PyErr_SetString(PyExc_TypeError, "Invalid subscript");
        return nullptr;
    }
}

PY_PLASMA_ASS_SUBSCRIPT_DECL(BitVector)
{
    if (!pyPlasma_check<bool>(value)) {
        PyErr_SetString(PyExc_TypeError, "BitVector bits should be bools");
        return -1;
    }
    bool b = pyPlasma_get<bool>(value);

    if (pyPlasma_check<ST::string>(key)) {
        ST::string name = pyPlasma_get<ST::string>(key);
        unsigned int idx = self->fThis->getValue(name.c_str());
        self->fThis->set(idx, b);
        return 0;
    } else if (pyPlasma_check<unsigned int>(key)) {
        unsigned int idx = pyPlasma_get<unsigned int>(key);
        self->fThis->set(idx, b);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "Invalid subscript");
        return -1;
    }
}

PY_METHOD_NOARGS(BitVector, isEmpty, "Returns whether the vector is empty")
{
    return pyPlasma_convert(self->fThis->isEmpty());
}

PY_METHOD_NOARGS(BitVector, clear, "Clears the vector of all bits")
{
    self->fThis->clear();
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(BitVector, compact,
    "Compacts the vector to the smallest size necessary to\n"
    "store all of the contained bits")
{
    self->fThis->compact();
    Py_RETURN_NONE;
}

PY_METHOD_VA(BitVector, getName,
    "Params: index\n"
    "Returns the name of the bit at `index`")
{
    int index;
    if (!PyArg_ParseTuple(args, "i", &index)) {
        PyErr_SetString(PyExc_TypeError, "getName expects an int");
        return nullptr;
    }
    return pyPlasma_convert(self->fThis->getName((size_t)index));
}

PY_METHOD_VA(BitVector, getValue,
    "Params: name\n"
    "Returns the index of the bit named `name`")
{
    const char* name;
    if (!PyArg_ParseTuple(args, "s", &name)) {
        PyErr_SetString(PyExc_TypeError, "getValue expects a string");
        return nullptr;
    }
    return pyPlasma_convert(self->fThis->getValue(name));
}

PY_METHOD_VA(BitVector, setName,
    "Params: index, name\n"
    "Names the bit at `index` to `name`")
{
    int index;
    const char* name;
    if (!PyArg_ParseTuple(args, "is", &index, &name)) {
        PyErr_SetString(PyExc_TypeError, "setName expects int, string");
        return nullptr;
    }
    self->fThis->setName(index, name);
    Py_RETURN_NONE;
}

PY_METHOD_VA(BitVector, read,
    "Params: stream\n"
    "Read this BitVector from `stream`")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects a hsStream");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects a hsStream");
        return nullptr;
    }
    self->fThis->read(stream->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(BitVector, write,
    "Params: stream\n"
    "Write this BitVector to `stream`")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects a hsStream");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects a hsStream");
        return nullptr;
    }
    self->fThis->write(stream->fThis);
    Py_RETURN_NONE;
}

static PyMethodDef pyBitVector_Methods[] = {
    pyBitVector_isEmpty_method,
    pyBitVector_clear_method,
    pyBitVector_compact_method,
    pyBitVector_getName_method,
    pyBitVector_getValue_method,
    pyBitVector_setName_method,
    pyBitVector_read_method,
    pyBitVector_write_method,
    PY_METHOD_TERMINATOR
};

PY_PLASMA_TYPE(BitVector, hsBitVector, "hsBitVector wrapper")
PY_PLASMA_TYPE_AS_MAPPING(BitVector)

PY_PLASMA_TYPE_INIT(BitVector)
{
    pyBitVector_As_Mapping.mp_subscript = pyBitVector_mp_subscript;
    pyBitVector_As_Mapping.mp_ass_subscript = pyBitVector_mp_ass_subscript;
    pyBitVector_Type.tp_dealloc = pyBitVector_dealloc;
    pyBitVector_Type.tp_init = pyBitVector___init__;
    pyBitVector_Type.tp_new = pyBitVector_new;
    pyBitVector_Type.tp_as_mapping = &pyBitVector_As_Mapping;
    pyBitVector_Type.tp_methods = pyBitVector_Methods;
    if (PyType_CheckAndReady(&pyBitVector_Type) < 0)
        return nullptr;

    Py_INCREF(&pyBitVector_Type);
    return (PyObject*)&pyBitVector_Type;
}

PY_PLASMA_IFC_METHODS(BitVector, hsBitVector)
