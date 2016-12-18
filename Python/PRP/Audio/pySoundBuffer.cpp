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

#include "pySoundBuffer.h"

#include <PRP/Audio/plSoundBuffer.h>
#include "PRP/KeyedObject/pyKeyedObject.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pySoundBuffer_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pySoundBuffer* self = (pySoundBuffer*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plSoundBuffer();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pySoundBuffer_getHeader(pySoundBuffer* self, void*) {
    return pyWAVHeader_FromWAVHeader(&self->fThis->getHeader());
}

static PyObject* pySoundBuffer_getFileName(pySoundBuffer* self, void*) {
    return PlStr_To_PyStr(self->fThis->getFileName());
}

static PyObject* pySoundBuffer_getFlags(pySoundBuffer* self, void*) {
    return PyInt_FromLong(self->fThis->getFlags());
}

static PyObject* pySoundBuffer_getDataLength(pySoundBuffer* self, void*) {
    return PyInt_FromLong(self->fThis->getFlags());
}

static PyObject* pySoundBuffer_getData(pySoundBuffer* self, void*) {
    if (self->fThis->getData() == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    } else {
        return PyBytes_FromStringAndSize((const char*)self->fThis->getData(),
                                         self->fThis->getDataLength());
    }
}

static int pySoundBuffer_setHeader(pySoundBuffer* self, PyObject* value, void*) {
    if (value == NULL || !pyWAVHeader_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "header should be a plWAVHeader");
        return -1;
    }
    self->fThis->getHeader() = *((pyWAVHeader*)value)->fThis;
    return 0;
}

static int pySoundBuffer_setFileName(pySoundBuffer* self, PyObject* value, void*) {
    if (value == NULL || !PyAnyStr_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "fileName should be a string");
        return -1;
    }
    self->fThis->setFileName(PyStr_To_PlStr(value));
    return 0;
}

static int pySoundBuffer_setFlags(pySoundBuffer* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "flags should be an int");
        return -1;
    }
    self->fThis->setFlags(PyInt_AsLong(value));
    return 0;
}

static int pySoundBuffer_setDataLength(pySoundBuffer* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "dataLength should be an int");
        return -1;
    }
    self->fThis->setData(PyInt_AsLong(value), NULL);
    return 0;
}

static int pySoundBuffer_setData(pySoundBuffer* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setData(0, NULL);
        return 0;
    }
    if (!PyBytes_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "data should be a binary string");
        return -1;
    }
    char* buffer;
    Py_ssize_t length;
    PyBytes_AsStringAndSize(value, &buffer, &length);
    self->fThis->setData(length, (const unsigned char*)buffer);
    return 0;
}


static PyGetSetDef pySoundBuffer_GetSet[] = {
    { _pycs("header"), (getter)pySoundBuffer_getHeader,
        (setter)pySoundBuffer_setHeader, NULL, NULL },
    { _pycs("fileName"), (getter)pySoundBuffer_getFileName,
        (setter)pySoundBuffer_setFileName, NULL, NULL },
    { _pycs("flags"), (getter)pySoundBuffer_getFlags,
        (setter)pySoundBuffer_setFlags, NULL, NULL },
    { _pycs("data"), (getter)pySoundBuffer_getData,
        (setter)pySoundBuffer_setData, NULL, NULL },
    { _pycs("dataLength"), (getter)pySoundBuffer_getDataLength,
        (setter)pySoundBuffer_setDataLength, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pySoundBuffer_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plSoundBuffer",         /* tp_name */
    sizeof(pySoundBuffer),              /* tp_basicsize */
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
    "plSoundBuffer wrapper",            /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pySoundBuffer_GetSet,               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pySoundBuffer_new,                  /* tp_new */
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

PyObject* Init_pySoundBuffer_Type() {
    pySoundBuffer_Type.tp_base = &pyKeyedObject_Type;
    if (PyType_Ready(&pySoundBuffer_Type) < 0)
        return NULL;

    PyDict_SetItemString(pySoundBuffer_Type.tp_dict, "kIsExternal",
                         PyInt_FromLong(plSoundBuffer::kIsExternal));
    PyDict_SetItemString(pySoundBuffer_Type.tp_dict, "kAlwaysExternal",
                         PyInt_FromLong(plSoundBuffer::kAlwaysExternal));
    PyDict_SetItemString(pySoundBuffer_Type.tp_dict, "kOnlyLeftChannel",
                         PyInt_FromLong(plSoundBuffer::kOnlyLeftChannel));
    PyDict_SetItemString(pySoundBuffer_Type.tp_dict, "kOnlyRightChannel",
                         PyInt_FromLong(plSoundBuffer::kOnlyRightChannel));
    PyDict_SetItemString(pySoundBuffer_Type.tp_dict, "kStreamCompressed",
                         PyInt_FromLong(plSoundBuffer::kStreamCompressed));

    Py_INCREF(&pySoundBuffer_Type);
    return (PyObject*)&pySoundBuffer_Type;
}

PY_PLASMA_IFC_METHODS(SoundBuffer, plSoundBuffer)

}
