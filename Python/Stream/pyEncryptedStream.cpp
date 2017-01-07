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

extern "C" {

PY_PLASMA_NEW(EncryptedStream, plEncryptedStream)

PY_METHOD_VA(EncryptedStream, open,
    "Params: filename, mode, encryption\n"
    "Opens the specified file.\n"
    "Mode is: fmRead, fmWrite, fmReadWrite, fmCreate\n"
    "Encryption is: kEncNone, kEncXtea, kEncAES, kEncDroid, kEncAuto")
{
    const char* filename;
    int mode, encryption;

    if (!PyArg_ParseTuple(args, "sii", &filename, &mode, &encryption)) {
        PyErr_SetString(PyExc_TypeError, "open expects string, int, int");
        return NULL;
    }
    try {
        if (!self->fThis->open(filename, (FileMode)mode,
                               (plEncryptedStream::EncryptionType)encryption)) {
            PyErr_SetString(PyExc_IOError, "Error opening file");
            return NULL;
        }
        Py_INCREF(self);
        return (PyObject*)self;
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error opening file");
        return NULL;
    }
}

PY_METHOD_VA(EncryptedStream, setKey,
    "Params: key\n"
    "Sets the encryption key. `key` should be an array of 4 ints")
{
    PyObject* keyList;
    if (!PyArg_ParseTuple(args, "O", &keyList)) {
        PyErr_SetString(PyExc_TypeError, "setKey expects an array of 4 ints");
        return NULL;
    }
    Py_INCREF(keyList);
    if (!PyList_Check(keyList) || (PyList_Size(keyList) != 4)) {
        Py_DECREF(keyList);
        PyErr_SetString(PyExc_TypeError, "setKey expects an array of 4 ints");
        return NULL;
    }
    int key[4];
    for (int i=0; i<4; i++) {
        PyObject* k = PyList_GetItem(keyList, i);
        Py_INCREF(k);
        if (!PyInt_Check(k)) {
            Py_DECREF(k);
            Py_DECREF(keyList);
            PyErr_SetString(PyExc_TypeError, "setKey expects an array of 4 ints");
            return NULL;
        }
        key[i] = PyInt_AsLong(k);
        Py_DECREF(k);
    }
    Py_DECREF(keyList);
    self->fThis->setKey((unsigned int*)key);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(EncryptedStream, getEncType, "Returns the encryption type") {
    return pyPlasma_convert(self->fThis->getEncType());
}

PY_METHOD_STATIC_VA(EncryptedStream, IsFileEncrypted,
    "(static)\n"
    "Params: filename\n"
    "Tests whether the specified file is encrypted")
{
    const char* filename;
    if (!PyArg_ParseTuple(args, "s", &filename)) {
        PyErr_SetString(PyExc_TypeError, "IsFileEncrypted expects a string");
        return NULL;
    }
    return pyPlasma_convert(plEncryptedStream::IsFileEncrypted(filename));
}

PY_METHOD_NOARGS(EncryptedStream, __enter__, NULL) {
    Py_INCREF(self);
    return (PyObject*)self;
}

PY_METHOD_VA(EncryptedStream, __exit__, NULL) {
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

PY_PLASMA_TYPE_INIT(EncryptedStream) {
    pyEncryptedStream_Type.tp_new = pyEncryptedStream_new;
    pyEncryptedStream_Type.tp_methods = pyEncryptedStream_Methods;
    pyEncryptedStream_Type.tp_base = &pyFileStream_Type;
    if (PyType_Ready(&pyEncryptedStream_Type) < 0)
        return NULL;

    PY_TYPE_ADD_CONST(EncryptedStream, "kEncNone", plEncryptedStream::kEncNone);
    PY_TYPE_ADD_CONST(EncryptedStream, "kEncXtea", plEncryptedStream::kEncXtea);
    PY_TYPE_ADD_CONST(EncryptedStream, "kEncAES", plEncryptedStream::kEncAES);
    PY_TYPE_ADD_CONST(EncryptedStream, "kEncDroid", plEncryptedStream::kEncDroid);
    PY_TYPE_ADD_CONST(EncryptedStream, "kEncAuto", plEncryptedStream::kEncAuto);

    Py_INCREF(&pyEncryptedStream_Type);
    return (PyObject*)&pyEncryptedStream_Type;
}

PY_PLASMA_IFC_METHODS(EncryptedStream, plEncryptedStream)

}
