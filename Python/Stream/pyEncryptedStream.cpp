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

PyTypeObject pyEncryptedStream_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plEncryptedStream",     /* tp_name */
    sizeof(pyEncryptedStream),          /* tp_basicsize */
    0,                                  /* tp_itemsize */

    NULL,                               /* tp_dealloc */
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
    "plEncryptedStream wrapper",        /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyEncryptedStream_Methods,          /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyEncryptedStream_new,              /* tp_new */
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

PyObject* Init_pyEncryptedStream_Type() {
    pyEncryptedStream_Type.tp_base = &pyFileStream_Type;
    if (PyType_Ready(&pyEncryptedStream_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyEncryptedStream_Type.tp_dict, "kEncNone",
                         PyInt_FromLong(plEncryptedStream::kEncNone));
    PyDict_SetItemString(pyEncryptedStream_Type.tp_dict, "kEncXtea",
                         PyInt_FromLong(plEncryptedStream::kEncXtea));
    PyDict_SetItemString(pyEncryptedStream_Type.tp_dict, "kEncAES",
                         PyInt_FromLong(plEncryptedStream::kEncAES));
    PyDict_SetItemString(pyEncryptedStream_Type.tp_dict, "kEncDroid",
                         PyInt_FromLong(plEncryptedStream::kEncDroid));
    PyDict_SetItemString(pyEncryptedStream_Type.tp_dict, "kEncAuto",
                         PyInt_FromLong(plEncryptedStream::kEncAuto));

    Py_INCREF(&pyEncryptedStream_Type);
    return (PyObject*)&pyEncryptedStream_Type;
}

PY_PLASMA_IFC_METHODS(EncryptedStream, plEncryptedStream)

}
