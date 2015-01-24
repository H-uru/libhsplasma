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
#include <PRP/Audio/plSoundBuffer.h>
#include "pySoundBuffer.h"
#include "Stream/pyStream.h"

extern "C" {

static PyObject* pyWAVHeader_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "Cannot construct plWAVHeader objects in Python");
    return NULL;
}

static PyObject* pyWAVHeader_read(pyWAVHeader* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects a hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects a hsStream");
        return NULL;
    }
    self->fThis->read(stream->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyWAVHeader_write(pyWAVHeader* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects a hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects a hsStream");
        return NULL;
    }
    self->fThis->write(stream->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyWAVHeader_getFormat(pyWAVHeader* self, void*) {
    return PyInt_FromLong(self->fThis->getFormatTag());
}

static PyObject* pyWAVHeader_getNumChans(pyWAVHeader* self, void*) {
    return PyInt_FromLong(self->fThis->getNumChannels());
}

static PyObject* pyWAVHeader_getSamples(pyWAVHeader* self, void*) {
    return PyInt_FromLong(self->fThis->getNumSamplesPerSec());
}

static PyObject* pyWAVHeader_getBPS(pyWAVHeader* self, void*) {
    return PyInt_FromLong(self->fThis->getAvgBytesPerSec());
}

static PyObject* pyWAVHeader_getAlign(pyWAVHeader* self, void*) {
    return PyInt_FromLong(self->fThis->getBlockAlign());
}

static PyObject* pyWAVHeader_getBits(pyWAVHeader* self, void*) {
    return PyInt_FromLong(self->fThis->getBitsPerSample());
}

static int pyWAVHeader_setFormat(pyWAVHeader* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "formatTag should be an int");
        return -1;
    }
    self->fThis->setFormatTag(PyInt_AsLong(value));
    return 0;
}

static int pyWAVHeader_setNumChans(pyWAVHeader* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "numChannels should be an int");
        return -1;
    }
    self->fThis->setNumChannels(PyInt_AsLong(value));
    return 0;
}

static int pyWAVHeader_setSamples(pyWAVHeader* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "samplesPerSec should be an int");
        return -1;
    }
    self->fThis->setNumSamplesPerSec(PyInt_AsLong(value));
    return 0;
}

static int pyWAVHeader_setBPS(pyWAVHeader* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "avgBytesPerSec should be an int");
        return -1;
    }
    self->fThis->setAvgBytesPerSec(PyInt_AsLong(value));
    return 0;
}

static int pyWAVHeader_setAlign(pyWAVHeader* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "blockAlign should be an int");
        return -1;
    }
    self->fThis->setBlockAlign(PyInt_AsLong(value));
    return 0;
}

static int pyWAVHeader_setBits(pyWAVHeader* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "bitsPerSample should be an int");
        return -1;
    }
    self->fThis->setBitsPerSample(PyInt_AsLong(value));
    return 0;
}

static PyMethodDef pyWAVHeader_Methods[] = {
    { "read", (PyCFunction)pyWAVHeader_read, METH_VARARGS,
      "Params: stream\n"
      "Reads this object from `stream`" },
    { "write", (PyCFunction)pyWAVHeader_write, METH_VARARGS,
      "Params: stream\n"
      "Writes this object to `stream`" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyWAVHeader_GetSet[] = {
    { _pycs("formatTag"), (getter)pyWAVHeader_getFormat,
        (setter)pyWAVHeader_setFormat, NULL, NULL },
    { _pycs("numChannels"), (getter)pyWAVHeader_getNumChans,
        (setter)pyWAVHeader_setNumChans, NULL, NULL },
    { _pycs("samplesPerSec"), (getter)pyWAVHeader_getSamples,
        (setter)pyWAVHeader_setSamples, NULL, NULL },
    { _pycs("avgBytesPerSec"), (getter)pyWAVHeader_getBPS,
        (setter)pyWAVHeader_setBPS, NULL, NULL },
    { _pycs("blockAlign"), (getter)pyWAVHeader_getAlign,
        (setter)pyWAVHeader_setAlign, NULL, NULL },
    { _pycs("bitsPerSample"), (getter)pyWAVHeader_getBits,
        (setter)pyWAVHeader_setBits, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyWAVHeader_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plWAVHeader",           /* tp_name */
    sizeof(pyWAVHeader),                /* tp_basicsize */
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

    Py_TPFLAGS_DEFAULT,                 /* tp_flags */
    "plWAVHeader wrapper",              /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyWAVHeader_Methods,                /* tp_methods */
    NULL,                               /* tp_members */
    pyWAVHeader_GetSet,                 /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyWAVHeader_new,                    /* tp_new */
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

PyObject* Init_pyWAVHeader_Type() {
    if (PyType_Ready(&pyWAVHeader_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyWAVHeader_Type.tp_dict, "kPCMFormatTag",
                         PyInt_FromLong(plWAVHeader::kPCMFormatTag));

    Py_INCREF(&pyWAVHeader_Type);
    return (PyObject*)&pyWAVHeader_Type;
}

PyObject* pyWAVHeader_FromWAVHeader(plWAVHeader& header) {
    pyWAVHeader* pyObj = PyObject_New(pyWAVHeader, &pyWAVHeader_Type);
    pyObj->fThis = &header;
    return (PyObject*)pyObj;
}

}
