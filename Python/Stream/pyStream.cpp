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

extern "C" {

PY_PLASMA_DEALLOC(Stream)

PY_PLASMA_INIT_DECL(Stream) {
    static char* kwlist[] = { _pycs("ver"), NULL };

    int ver = PlasmaVer::pvUnknown;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|i", kwlist, &ver))
        return -1;

    self->fThis->setVer((PlasmaVer)ver);
    return 0;
}

PY_PLASMA_NEW_MSG(Stream, "hsStream is abstract")

static PyObject* pyStream_close(pyStream* self) {
    self->fThis->close();
    Py_RETURN_NONE;
}

static PyObject* pyStream_eof(pyStream* self) {
    return pyPlasma_convert(self->fThis->eof());
}

static PyObject* pyStream_seek(pyStream* self, PyObject* args) {
    int32_t pos;
    if (!PyArg_ParseTuple(args, "i", &pos)) {
        PyErr_SetString(PyExc_TypeError, "seek expects an int");
        return NULL;
    }
    self->fThis->seek((uint32_t)pos);
    Py_RETURN_NONE;
}

static PyObject* pyStream_skip(pyStream* self, PyObject* args) {
    uint32_t count;
    if (!PyArg_ParseTuple(args, "i", &count)) {
        PyErr_SetString(PyExc_TypeError, "skip expects an int");
        return NULL;
    }
    self->fThis->skip(count);
    Py_RETURN_NONE;
}

static PyObject* pyStream_fastForward(pyStream* self) {
    self->fThis->fastForward();
    Py_RETURN_NONE;
}

static PyObject* pyStream_rewind(pyStream* self) {
    self->fThis->rewind();
    Py_RETURN_NONE;
}

static PyObject* pyStream_flush(pyStream* self) {
    self->fThis->flush();
    Py_RETURN_NONE;
}

static PyObject* pyStream_read(pyStream* self, PyObject* args) {
    int size;
    if (!PyArg_ParseTuple(args, "i", &size)) {
        PyErr_SetString(PyExc_TypeError, "read expects an int");
        return NULL;
    }
    char* buf = new char[size];
    try {
        self->fThis->read((size_t)size, buf);
        PyObject* data = PyBytes_FromStringAndSize(buf, size);
        delete[] buf;
        return data;
    } catch (...) {
        delete[] buf;
        PyErr_SetString(PyExc_IOError, "Error reading from stream");
        return NULL;
    }
}

static PyObject* pyStream_write(pyStream* self, PyObject* args) {
    const char* data;
    int dataSize;
    if (!PyArg_ParseTuple(args, "s#", &data, &dataSize)) {
        PyErr_SetString(PyExc_TypeError, "write expects a binary string");
        return NULL;
    }
    try {
        self->fThis->write((size_t)dataSize, data);
        Py_RETURN_NONE;
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error writing to stream");
        return NULL;
    }
}

static PyObject* pyStream_writeFrom(pyStream* self, PyObject* args) {
    pyStream* from;
    if (!PyArg_ParseTuple(args, "O", &from)) {
        PyErr_SetString(PyExc_TypeError, "writeFrom expects a pyStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)from)) {
        PyErr_SetString(PyExc_TypeError, "writeFrom expects a pyStream");
        return NULL;
    }
    try {
        self->fThis->writeFrom(from->fThis);
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error copying stream");
        return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject* pyStream_readByte(pyStream* self) {
    try {
        return pyPlasma_convert(self->fThis->readByte());
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error reading from stream");
        return NULL;
    }
}

static PyObject* pyStream_readShort(pyStream* self) {
    try {
        return pyPlasma_convert(self->fThis->readShort());
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error reading from stream");
        return NULL;
    }
}

static PyObject* pyStream_readInt(pyStream* self) {
    try {
        return pyPlasma_convert(self->fThis->readInt());
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error reading from stream");
        return NULL;
    }
}

static PyObject* pyStream_readFloat(pyStream* self) {
    try {
        return pyPlasma_convert(self->fThis->readFloat());
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error reading from stream");
        return NULL;
    }
}

static PyObject* pyStream_readDouble(pyStream* self) {
    try {
        return pyPlasma_convert(self->fThis->readDouble());
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error reading from stream");
        return NULL;
    }
}

static PyObject* pyStream_readBool(pyStream* self) {
    try {
        return pyPlasma_convert(self->fThis->readBool());
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error reading from stream");
        return NULL;
    }
}

static PyObject* pyStream_readSafeStr(pyStream* self) {
    try {
        return pyPlasma_convert(self->fThis->readSafeStr());
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error reading from stream");
        return NULL;
    }
}

static PyObject* pyStream_readSafeWStr(pyStream* self) {
    try {
        return pyPlasma_convert(self->fThis->readSafeWStr());
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error reading from stream");
        return NULL;
    }
}

static PyObject* pyStream_readLine(pyStream* self) {
    try {
        return pyPlasma_convert(self->fThis->readLine());
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error reading from stream");
        return NULL;
    }
}

static PyObject* pyStream_writeByte(pyStream* self, PyObject* args) {
    int8_t b;
    if (!PyArg_ParseTuple(args, "b", &b)) {
        PyErr_SetString(PyExc_TypeError, "writeByte expects a byte");
        return NULL;
    }
    try {
        self->fThis->writeByte(b);
        Py_RETURN_NONE;
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error writing to stream");
        return NULL;
    }
}

static PyObject* pyStream_writeShort(pyStream* self, PyObject* args) {
    int16_t h;
    if (!PyArg_ParseTuple(args, "h", &h)) {
        PyErr_SetString(PyExc_TypeError, "writeShort expects a short");
        return NULL;
    }
    try {
        self->fThis->writeShort(h);
        Py_RETURN_NONE;
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error writing to stream");
        return NULL;
    }
}

static PyObject* pyStream_writeInt(pyStream* self, PyObject* args) {
    int32_t i;
    if (!PyArg_ParseTuple(args, "i", &i)) {
        PyErr_SetString(PyExc_TypeError, "writeInt expects an int");
        return NULL;
    }
    try {
        self->fThis->writeInt(i);
        Py_RETURN_NONE;
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error writing to stream");
        return NULL;
    }
}

static PyObject* pyStream_writeFloat(pyStream* self, PyObject* args) {
    float f;
    if (!PyArg_ParseTuple(args, "f", &f)) {
        PyErr_SetString(PyExc_TypeError, "writeFloat expects a float");
        return NULL;
    }
    try {
        self->fThis->writeFloat(f);
        Py_RETURN_NONE;
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error writing to stream");
        return NULL;
    }
}

static PyObject* pyStream_writeDouble(pyStream* self, PyObject* args) {
    double d;
    if (!PyArg_ParseTuple(args, "d", &d)) {
        PyErr_SetString(PyExc_TypeError, "writeDouble expects a double");
        return NULL;
    }
    try {
        self->fThis->writeDouble(d);
        Py_RETURN_NONE;
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error writing to stream");
        return NULL;
    }
}

static PyObject* pyStream_writeBool(pyStream* self, PyObject* args) {
    bool b;
    if (!PyArg_ParseTuple(args, "b", &b)) {
        PyErr_SetString(PyExc_TypeError, "writeBool expects a bool");
        return NULL;
    }
    try {
        self->fThis->writeBool(b);
        Py_RETURN_NONE;
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error writing to stream");
        return NULL;
    }
}

static PyObject* pyStream_writeSafeStr(pyStream* self, PyObject* args) {
    const char* str;
    if (!PyArg_ParseTuple(args, "s", &str)) {
        PyErr_SetString(PyExc_TypeError, "writeSafeStr expects a string");
        return NULL;
    }
    try {
        self->fThis->writeSafeStr(str);
        Py_RETURN_NONE;
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error writing to stream");
        return NULL;
    }
}

static PyObject* pyStream_writeSafeWStr(pyStream* self, PyObject* args) {
    const char* str;
    if (!PyArg_ParseTuple(args, "s", &str)) {
        PyErr_SetString(PyExc_TypeError, "writeSafeWStr expects a string");
        return NULL;
    }
    try {
        self->fThis->writeSafeWStr(str);
        Py_RETURN_NONE;
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error writing to stream");
        return NULL;
    }
}

static PyObject* pyStream_writeLine(pyStream* self, PyObject* args) {
    const char* str;
    if (!PyArg_ParseTuple(args, "s", &str)) {
        PyErr_SetString(PyExc_TypeError, "writeLine expects a string");
        return NULL;
    }
    try {
        self->fThis->writeLine(str);
        Py_RETURN_NONE;
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error writing to stream");
        return NULL;
    }
}

static PyMethodDef pyStream_Methods[] = {
    { "close", (PyCFunction)pyStream_close, METH_NOARGS,
      "Closes the stream, if it is open" },
    { "eof", (PyCFunction)pyStream_eof, METH_NOARGS,
      "Returns True if the position is at the end of the stream" },
    { "seek", (PyCFunction)pyStream_seek, METH_VARARGS,
      "Params: position\n"
      "Seeks to the specified position within the stream " },
    { "skip", (PyCFunction)pyStream_skip, METH_VARARGS,
      "Params: count\n"
      "Skips `count` bytes within the stream" },
    { "fastForward", (PyCFunction)pyStream_fastForward, METH_NOARGS,
      "Seeks directly to the end of the stream" },
    { "rewind", (PyCFunction)pyStream_rewind, METH_NOARGS,
      "Seeks directly to the beginning of the stream" },
    { "flush", (PyCFunction)pyStream_flush, METH_NOARGS,
      "Flushes the stream" },
    { "read", (PyCFunction)pyStream_read, METH_VARARGS,
      "Params: size\n"
      "Reads `size` bytes and returns a binary string with the data" },
    { "write", (PyCFunction)pyStream_write, METH_VARARGS,
      "Params: data\n"
      "Writes `data` (as a binary string) to the stream" },
    { "writeFrom", (PyCFunction)pyStream_writeFrom, METH_VARARGS,
      "Params: stream\n"
      "Copies the contents of `stream` to this stream" },
    { "readByte", (PyCFunction)pyStream_readByte, METH_NOARGS, NULL },
    { "readShort", (PyCFunction)pyStream_readShort, METH_NOARGS, NULL },
    { "readInt", (PyCFunction)pyStream_readInt, METH_NOARGS, NULL },
    { "readFloat", (PyCFunction)pyStream_readFloat, METH_NOARGS, NULL },
    { "readDouble", (PyCFunction)pyStream_readDouble, METH_NOARGS, NULL },
    { "readBool", (PyCFunction)pyStream_readBool, METH_NOARGS, NULL },
    { "readSafeStr", (PyCFunction)pyStream_readSafeStr, METH_NOARGS, NULL },
    { "readSafeWStr", (PyCFunction)pyStream_readSafeWStr, METH_NOARGS, NULL },
    { "readLine", (PyCFunction)pyStream_readLine, METH_NOARGS, NULL },
    { "writeByte", (PyCFunction)pyStream_writeByte, METH_VARARGS, NULL },
    { "writeShort", (PyCFunction)pyStream_writeShort, METH_VARARGS, NULL },
    { "writeInt", (PyCFunction)pyStream_writeInt, METH_VARARGS, NULL },
    { "writeFloat", (PyCFunction)pyStream_writeFloat, METH_VARARGS, NULL },
    { "writeDouble", (PyCFunction)pyStream_writeDouble, METH_VARARGS, NULL },
    { "writeBool", (PyCFunction)pyStream_writeBool, METH_VARARGS, NULL },
    { "writeSafeStr", (PyCFunction)pyStream_writeSafeStr, METH_VARARGS, NULL },
    { "writeSafeWStr", (PyCFunction)pyStream_writeSafeWStr, METH_VARARGS, NULL },
    { "writeLine", (PyCFunction)pyStream_writeLine, METH_VARARGS, NULL },
    { NULL, NULL, 0, NULL }
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

PyTypeObject pyStream_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.hsStream",              /* tp_name */
    sizeof(pyStream),                   /* tp_basicsize */
    0,                                  /* tp_itemsize */

    pyStream_dealloc,                   /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_compare */
    NULL,                               /* tp_repr */
    NULL,                               /* tp_as_number */
    NULL,                               /* tp_as_sequence */
    NULL,                               /* tp_as_mapping */
    NULL,                               /* tp_hash */
    NULL,                               /* tp_call */
    NULL,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */

    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
    "hsStream wrapper",                 /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyStream_Methods,                   /* tp_methods */
    NULL,                               /* tp_members */
    pyStream_GetSet,                    /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    pyStream___init__,                  /* tp_init */
    NULL,                               /* tp_alloc */
    pyStream_new,                       /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */

    NULL,                               /* tp_del */
    TP_VERSION_TAG_INIT                 /* tp_version_tag */
    TP_FINALIZE_INIT                    /* tp_finalize */
};

PyObject* Init_pyStream_Type() {
    if (PyType_Ready(&pyStream_Type) < 0)
        return NULL;

    Py_INCREF(&pyStream_Type);
    return (PyObject*)&pyStream_Type;
}

PY_PLASMA_IFC_METHODS(Stream, hsStream)

}
