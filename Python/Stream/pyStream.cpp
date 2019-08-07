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

#include "pyStream.h"

#include <Stream/hsStream.h>

PY_PLASMA_DEALLOC(Stream)

PY_PLASMA_INIT_DECL(Stream)
{
    static char* kwlist[] = { _pycs("ver"), nullptr };

    int ver = PlasmaVer::pvUnknown;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|i", kwlist, &ver))
        return -1;

    self->fThis->setVer((PlasmaVer)ver);
    return 0;
}

PY_PLASMA_NEW_MSG(Stream, "hsStream is abstract")

PY_METHOD_NOARGS(Stream, close, "Closes the stream, if it is open")
{
    self->fThis->close();
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(Stream, eof,
    "Returns True if the position is at the end of the stream")
{
    return pyPlasma_convert(self->fThis->eof());
}

PY_METHOD_VA(Stream, seek,
    "Params: position\n"
    "Seeks to the specified position within the stream")
{
    int32_t pos;
    if (!PyArg_ParseTuple(args, "i", &pos)) {
        PyErr_SetString(PyExc_TypeError, "seek expects an int");
        return nullptr;
    }
    self->fThis->seek((uint32_t)pos);
    Py_RETURN_NONE;
}

PY_METHOD_VA(Stream, skip,
    "Params: count\n"
    "Skips `count` bytes within the stream")
{
    uint32_t count;
    if (!PyArg_ParseTuple(args, "i", &count)) {
        PyErr_SetString(PyExc_TypeError, "skip expects an int");
        return nullptr;
    }
    self->fThis->skip(count);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(Stream, fastForward, "Seeks directly to the end of the stream")
{
    self->fThis->fastForward();
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(Stream, rewind, "Seeks directly to the beginning of the stream")
{
    self->fThis->rewind();
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(Stream, flush, "Flushes the stream")
{
    self->fThis->flush();
    Py_RETURN_NONE;
}

PY_METHOD_VA(Stream, read,
    "Params: size\n"
    "Reads `size` bytes and returns a binary string with the data")
{
    int size;
    if (!PyArg_ParseTuple(args, "i", &size)) {
        PyErr_SetString(PyExc_TypeError, "read expects an int");
        return nullptr;
    }
    PyObject* bufObj = PyBytes_FromStringAndSize(nullptr, size);
    try {
        char* buf = PyBytes_AS_STRING(bufObj);
        self->fThis->read((size_t)size, buf);
        return bufObj;
    } catch (...) {
        Py_DECREF(bufObj);
        PyErr_SetString(PyExc_IOError, "Error reading from stream");
        return nullptr;
    }
}

PY_METHOD_VA(Stream, write,
    "Params: data\n"
    "Writes `data` (as a binary string) to the stream")
{
    const char* data;
    int dataSize;
    if (!PyArg_ParseTuple(args, "s#", &data, &dataSize)) {
        PyErr_SetString(PyExc_TypeError, "write expects a binary string");
        return nullptr;
    }
    try {
        self->fThis->write((size_t)dataSize, data);
        Py_RETURN_NONE;
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error writing to stream");
        return nullptr;
    }
}

PY_METHOD_VA(Stream, writeFrom,
    "Params: stream\n"
    "Copies the contents of `stream` to this stream")
{
    pyStream* from;
    if (!PyArg_ParseTuple(args, "O", &from)) {
        PyErr_SetString(PyExc_TypeError, "writeFrom expects a pyStream");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)from)) {
        PyErr_SetString(PyExc_TypeError, "writeFrom expects a pyStream");
        return nullptr;
    }
    try {
        self->fThis->writeFrom(from->fThis);
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error copying stream");
        return nullptr;
    }

    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(Stream, readByte, nullptr)
{
    try {
        return pyPlasma_convert(self->fThis->readByte());
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error reading from stream");
        return nullptr;
    }
}

PY_METHOD_NOARGS(Stream, readShort, nullptr)
{
    try {
        return pyPlasma_convert(self->fThis->readShort());
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error reading from stream");
        return nullptr;
    }
}

PY_METHOD_NOARGS(Stream, readInt, nullptr)
{
    try {
        return pyPlasma_convert(self->fThis->readInt());
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error reading from stream");
        return nullptr;
    }
}

PY_METHOD_NOARGS(Stream, readFloat, nullptr)
{
    try {
        return pyPlasma_convert(self->fThis->readFloat());
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error reading from stream");
        return nullptr;
    }
}

PY_METHOD_NOARGS(Stream, readDouble, nullptr)
{
    try {
        return pyPlasma_convert(self->fThis->readDouble());
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error reading from stream");
        return nullptr;
    }
}

PY_METHOD_NOARGS(Stream, readBool, nullptr)
{
    try {
        return pyPlasma_convert(self->fThis->readBool());
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error reading from stream");
        return nullptr;
    }
}

PY_METHOD_NOARGS(Stream, readSafeStr, nullptr)
{
    try {
        return pyPlasma_convert(self->fThis->readSafeStr());
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error reading from stream");
        return nullptr;
    }
}

PY_METHOD_NOARGS(Stream, readSafeWStr, nullptr)
{
    try {
        return pyPlasma_convert(self->fThis->readSafeWStr());
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error reading from stream");
        return nullptr;
    }
}

PY_METHOD_NOARGS(Stream, readLine, nullptr)
{
    try {
        return pyPlasma_convert(self->fThis->readLine());
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error reading from stream");
        return nullptr;
    }
}

PY_METHOD_VA(Stream, writeByte, nullptr)
{
    int8_t b;
    if (!PyArg_ParseTuple(args, "b", &b)) {
        PyErr_SetString(PyExc_TypeError, "writeByte expects a byte");
        return nullptr;
    }
    try {
        self->fThis->writeByte(b);
        Py_RETURN_NONE;
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error writing to stream");
        return nullptr;
    }
}

PY_METHOD_VA(Stream, writeShort, nullptr)
{
    int16_t h;
    if (!PyArg_ParseTuple(args, "h", &h)) {
        PyErr_SetString(PyExc_TypeError, "writeShort expects a short");
        return nullptr;
    }
    try {
        self->fThis->writeShort(h);
        Py_RETURN_NONE;
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error writing to stream");
        return nullptr;
    }
}

PY_METHOD_VA(Stream, writeInt, nullptr)
{
    int32_t i;
    if (!PyArg_ParseTuple(args, "i", &i)) {
        PyErr_SetString(PyExc_TypeError, "writeInt expects an int");
        return nullptr;
    }
    try {
        self->fThis->writeInt(i);
        Py_RETURN_NONE;
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error writing to stream");
        return nullptr;
    }
}

PY_METHOD_VA(Stream, writeFloat, nullptr)
{
    float f;
    if (!PyArg_ParseTuple(args, "f", &f)) {
        PyErr_SetString(PyExc_TypeError, "writeFloat expects a float");
        return nullptr;
    }
    try {
        self->fThis->writeFloat(f);
        Py_RETURN_NONE;
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error writing to stream");
        return nullptr;
    }
}

PY_METHOD_VA(Stream, writeDouble, nullptr)
{
    double d;
    if (!PyArg_ParseTuple(args, "d", &d)) {
        PyErr_SetString(PyExc_TypeError, "writeDouble expects a double");
        return nullptr;
    }
    try {
        self->fThis->writeDouble(d);
        Py_RETURN_NONE;
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error writing to stream");
        return nullptr;
    }
}

PY_METHOD_VA(Stream, writeBool, nullptr)
{
    bool b;
    if (!PyArg_ParseTuple(args, "b", &b)) {
        PyErr_SetString(PyExc_TypeError, "writeBool expects a bool");
        return nullptr;
    }
    try {
        self->fThis->writeBool(b);
        Py_RETURN_NONE;
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error writing to stream");
        return nullptr;
    }
}

PY_METHOD_VA(Stream, writeSafeStr, nullptr)
{
    const char* str;
    if (!PyArg_ParseTuple(args, "s", &str)) {
        PyErr_SetString(PyExc_TypeError, "writeSafeStr expects a string");
        return nullptr;
    }
    try {
        self->fThis->writeSafeStr(str);
        Py_RETURN_NONE;
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error writing to stream");
        return nullptr;
    }
}

PY_METHOD_VA(Stream, writeSafeWStr, nullptr)
{
    const char* str;
    if (!PyArg_ParseTuple(args, "s", &str)) {
        PyErr_SetString(PyExc_TypeError, "writeSafeWStr expects a string");
        return nullptr;
    }
    try {
        self->fThis->writeSafeWStr(str);
        Py_RETURN_NONE;
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error writing to stream");
        return nullptr;
    }
}

PY_METHOD_VA(Stream, writeLine, nullptr)
{
    const char* str;
    if (!PyArg_ParseTuple(args, "s", &str)) {
        PyErr_SetString(PyExc_TypeError, "writeLine expects a string");
        return nullptr;
    }
    try {
        self->fThis->writeLine(str);
        Py_RETURN_NONE;
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error writing to stream");
        return nullptr;
    }
}

static PyMethodDef pyStream_Methods[] = {
    pyStream_close_method,
    pyStream_eof_method,
    pyStream_seek_method,
    pyStream_skip_method,
    pyStream_fastForward_method,
    pyStream_rewind_method,
    pyStream_flush_method,
    pyStream_read_method,
    pyStream_write_method,
    pyStream_writeFrom_method,
    pyStream_readByte_method,
    pyStream_readShort_method,
    pyStream_readInt_method,
    pyStream_readFloat_method,
    pyStream_readDouble_method,
    pyStream_readBool_method,
    pyStream_readSafeStr_method,
    pyStream_readSafeWStr_method,
    pyStream_readLine_method,
    pyStream_writeByte_method,
    pyStream_writeShort_method,
    pyStream_writeInt_method,
    pyStream_writeFloat_method,
    pyStream_writeDouble_method,
    pyStream_writeBool_method,
    pyStream_writeSafeStr_method,
    pyStream_writeSafeWStr_method,
    pyStream_writeLine_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY(PlasmaVer, Stream, version, getVer, setVer)
PY_PROPERTY_RO(Stream, size, size)
PY_PROPERTY_RO(Stream, pos, pos)

static PyGetSetDef pyStream_GetSet[] = {
    pyStream_version_getset,
    pyStream_size_getset,
    pyStream_pos_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(Stream, hsStream, "hsStream wrapper")

PY_PLASMA_TYPE_INIT(Stream)
{
    pyStream_Type.tp_dealloc = pyStream_dealloc;
    pyStream_Type.tp_init = pyStream___init__;
    pyStream_Type.tp_new = pyStream_new;
    pyStream_Type.tp_methods = pyStream_Methods;
    pyStream_Type.tp_getset = pyStream_GetSet;
    if (PyType_CheckAndReady(&pyStream_Type) < 0)
        return nullptr;

    Py_INCREF(&pyStream_Type);
    return (PyObject*)&pyStream_Type;
}

PY_PLASMA_IFC_METHODS(Stream, hsStream)
