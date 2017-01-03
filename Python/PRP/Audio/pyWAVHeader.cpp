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
#include "Stream/pyStream.h"

extern "C" {

PY_PLASMA_DEALLOC(WAVHeader)
PY_PLASMA_NEW(WAVHeader, plWAVHeader)

PY_METHOD_VA(WAVHeader, read,
    "Params: stream\n"
    "Reads this object from `stream`")
{
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
    Py_RETURN_NONE;
}

PY_METHOD_VA(WAVHeader, write,
    "Params: stream\n"
    "Writes this object to `stream`")
{
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
    Py_RETURN_NONE;
}

static PyMethodDef pyWAVHeader_Methods[] = {
    pyWAVHeader_read_method,
    pyWAVHeader_write_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY(unsigned short, WAVHeader, formatTag, getFormatTag, setFormatTag)
PY_PROPERTY(unsigned short, WAVHeader, numChannels, getNumChannels, setNumChannels)
PY_PROPERTY(unsigned int, WAVHeader, samplesPerSec, getNumSamplesPerSec, setNumSamplesPerSec)
PY_PROPERTY(unsigned int, WAVHeader, avgBytesPerSec, getAvgBytesPerSec, setAvgBytesPerSec)
PY_PROPERTY(unsigned short, WAVHeader, blockAlign, getBlockAlign, setBlockAlign)
PY_PROPERTY(unsigned short, WAVHeader, bitsPerSample, getBitsPerSample, setBitsPerSample)

static PyGetSetDef pyWAVHeader_GetSet[] = {
    pyWAVHeader_formatTag_getset,
    pyWAVHeader_numChannels_getset,
    pyWAVHeader_samplesPerSec_getset,
    pyWAVHeader_avgBytesPerSec_getset,
    pyWAVHeader_blockAlign_getset,
    pyWAVHeader_bitsPerSample_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyWAVHeader_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plWAVHeader",           /* tp_name */
    sizeof(pyWAVHeader),                /* tp_basicsize */
    0,                                  /* tp_itemsize */

    pyWAVHeader_dealloc,                /* tp_dealloc */
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

PY_PLASMA_IFC_METHODS(WAVHeader, plWAVHeader)

}
