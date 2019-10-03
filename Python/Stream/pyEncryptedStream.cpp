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

#include <Stream/plEncryptedStream.h>

PY_PLASMA_NEW(EncryptedStream, plEncryptedStream)

PY_METHOD_VA(EncryptedStream, open,
    "Params: filename, mode, encryption\n"
    "Opens the specified file.\n"
    "Mode is: fmRead, fmWrite, fmReadWrite, fmCreate\n"
    "Encryption is: kEncNone, kEncXtea, kEncAES, kEncDroid, kEncAuto")
{
    ST::string filename;
    pyStream* stream;
    int mode, encryption;

    if (PyArg_ParseTuple(args, "O&ii", PyAnyString_PathDecoder, &filename, &mode, &encryption)) {
        try {
            if (!self->fThis->open(filename, (FileMode)mode, (plEncryptedStream::EncryptionType)encryption)) {
                PyErr_SetString(PyExc_IOError, "Error opening file");
                return nullptr;
            }
            Py_INCREF(self);
            return (PyObject*)self;
        } catch (const std::exception& ex) {
            PyErr_SetString(PyExc_IOError, ex.what());
            return nullptr;
        }
    } else if (PyErr_Clear(), PyArg_ParseTuple(args, "Oii", &stream, &mode, &encryption)) {
        if (!pyStream_Check((PyObject*)stream)) {
            PyErr_SetString(PyExc_TypeError, "open expects a string, hsStream stream, or an os.PathLike object, an int, and an int");
            return nullptr;
        }

        try {
            if (!self->fThis->open(stream->fThis, (FileMode)mode,
                                   (plEncryptedStream::EncryptionType)encryption)) {
                PyErr_SetString(PyExc_IOError, "Error opening stream");
                return nullptr;
            }
            Py_INCREF(self);
            return (PyObject*)self;
        } catch (const std::exception& ex) {
            PyErr_SetString(PyExc_IOError, ex.what());
            return nullptr;
        }
    } else {
        PyErr_SetString(PyExc_TypeError, "open expects a string, hsStream stream, or an os.PathLike object, an int, and an int");
        return nullptr;
    }
}

/* I really wanted this one to actually take a tuple, since it is a fixed-size
 * input value that is closely related.  However, the old code expected a
 * list, and requiring a tuple would break backwards compatibility, so we
 * now accept any sequence as a compromise */
PY_METHOD_VA(EncryptedStream, setKey,
    "Params: key\n"
    "Sets the encryption key. `key` should be a tuple of 4 ints")
{
    PyObject* keyListObj;
    if (!PyArg_ParseTuple(args, "O", &keyListObj)) {
        PyErr_SetString(PyExc_TypeError, "setKey expects an array of 4 ints");
        return nullptr;
    }
    pySequenceFastRef keyList(keyListObj);
    if (!keyList.isSequence() || keyList.size() != 4) {
        PyErr_SetString(PyExc_TypeError, "setKey expects a tuple of 4 ints");
        return nullptr;
    }
    int key[4];
    for (Py_ssize_t i=0; i<4; i++) {
        PyObject* k = keyList.get(i);
        if (!pyPlasma_check<int>(k)) {
            PyErr_SetString(PyExc_TypeError, "setKey expects a tuple of 4 ints");
            return nullptr;
        }
        key[i] = pyPlasma_get<int>(k);
    }
    self->fThis->setKey((unsigned int*)key);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(EncryptedStream, getEncType, "Returns the encryption type")
{
    return pyPlasma_convert(self->fThis->getEncType());
}

PY_METHOD_STATIC_VA(EncryptedStream, IsFileEncrypted,
    "(static)\n"
    "Params: filename\n"
    "Tests whether the specified file is encrypted")
{
    ST::string filename;
    if (!PyArg_ParseTuple(args, "O&", PyAnyString_PathDecoder, &filename)) {
        PyErr_SetString(PyExc_TypeError, "IsFileEncrypted expects a string or an os.PathLike object");
        return nullptr;
    }
    try {
        return pyPlasma_convert(plEncryptedStream::IsFileEncrypted(filename));
    } catch (const std::exception& ex) {
        PyErr_SetString(PyExc_IOError, ex.what());
        return nullptr;
    }
}

PY_METHOD_NOARGS(EncryptedStream, __enter__, nullptr)
{
    Py_INCREF(self);
    return (PyObject*)self;
}

PY_METHOD_VA(EncryptedStream, __exit__, nullptr)
{
    self->fThis->close();
    Py_RETURN_NONE;
}

static PyMethodDef pyEncryptedStream_Methods[] = {
    pyEncryptedStream_open_method,
    pyEncryptedStream_setKey_method,
    pyEncryptedStream_getEncType_method,
    pyEncryptedStream_IsFileEncrypted_method,
    pyEncryptedStream___enter___method,
    pyEncryptedStream___exit___method,
    PY_METHOD_TERMINATOR
};

PY_PLASMA_TYPE(EncryptedStream, plEncryptedStream, "plEncryptedStream wrapper")

PY_PLASMA_TYPE_INIT(EncryptedStream)
{
    pyEncryptedStream_Type.tp_new = pyEncryptedStream_new;
    pyEncryptedStream_Type.tp_methods = pyEncryptedStream_Methods;
    pyEncryptedStream_Type.tp_base = &pyFileStream_Type;
    if (PyType_CheckAndReady(&pyEncryptedStream_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(EncryptedStream, "kEncNone", plEncryptedStream::kEncNone);
    PY_TYPE_ADD_CONST(EncryptedStream, "kEncXtea", plEncryptedStream::kEncXtea);
    PY_TYPE_ADD_CONST(EncryptedStream, "kEncAES", plEncryptedStream::kEncAES);
    PY_TYPE_ADD_CONST(EncryptedStream, "kEncDroid", plEncryptedStream::kEncDroid);
    PY_TYPE_ADD_CONST(EncryptedStream, "kEncAuto", plEncryptedStream::kEncAuto);

    Py_INCREF(&pyEncryptedStream_Type);
    return (PyObject*)&pyEncryptedStream_Type;
}

PY_PLASMA_IFC_METHODS(EncryptedStream, plEncryptedStream)
