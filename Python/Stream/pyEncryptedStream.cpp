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

#include <PyPlasma.h>
#include <Stream/plEncryptedStream.h>
#include "pyStream.h"

extern "C" {

static void pyEncryptedStream_dealloc(pyEncryptedStream* self) {
    delete self->fThis;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject* pyEncryptedStream_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyEncryptedStream* self = (pyEncryptedStream*)type->tp_alloc(type, 0);
    int version = PlasmaVer::pvUnknown;
    PyArg_ParseTuple(args, "|i", &version);
    if (self != NULL)
        self->fThis = new plEncryptedStream((PlasmaVer)version);
    return (PyObject*)self;
}

static PyObject* pyEncryptedStream_open(pyEncryptedStream* self, PyObject* args) {
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
        Py_INCREF(Py_None);
        return Py_None;
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error opening file");
        return NULL;
    }
}

static PyObject* pyEncryptedStream_close(pyEncryptedStream* self) {
    self->fThis->close();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyEncryptedStream_setKey(pyEncryptedStream* self, PyObject* args) {
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
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyEncryptedStream_getEncType(pyEncryptedStream* self) {
    return PyInt_FromLong(self->fThis->getEncType());
}

static PyObject* pyEncryptedStream_IsFileEncrypted(PyObject*, PyObject* args) {
    const char* filename;
    if (!PyArg_ParseTuple(args, "s", &filename)) {
        PyErr_SetString(PyExc_TypeError, "IsFileEncrypted expects a string");
        return NULL;
    }
    bool result = plEncryptedStream::IsFileEncrypted(filename);
    return PyBool_FromLong(result ? 1 : 0);
}

static PyMethodDef pyEncryptedStream_Methods[] = {
    { "open", (PyCFunction)pyEncryptedStream_open, METH_VARARGS,
      "Params: filename, mode, encryption\n"
      "Opens the specified file.\n"
      "Mode is: fmRead, fmWrite, fmReadWrite, fmCreate\n"
      "Encryption is: kEncNone, kEncXtea, kEncAES, kEncDroid, kEncAuto" },
    { "close", (PyCFunction)pyEncryptedStream_close, METH_NOARGS,
      "Closes the active file, if it is open" },
    { "setKey", (PyCFunction)pyEncryptedStream_setKey, METH_VARARGS,
      "Params: key\n"
      "Sets the encryption key. `key` should be an array of 4 ints" },
    { "getEncType", (PyCFunction)pyEncryptedStream_getEncType, METH_NOARGS,
      "Returns the encryption type" },
    { "IsFileEncrypted", (PyCFunction)pyEncryptedStream_IsFileEncrypted,
      METH_VARARGS | METH_STATIC,
      "(static)\n"
      "Params: filename\n"
      "Tests whether the specified file is encrypted" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyEncryptedStream_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plEncryptedStream",     /* tp_name */
    sizeof(pyEncryptedStream),          /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pyEncryptedStream_dealloc, /* tp_dealloc */
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

}
