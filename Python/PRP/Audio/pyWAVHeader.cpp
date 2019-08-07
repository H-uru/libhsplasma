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

PY_PLASMA_DEALLOC(WAVHeader)
PY_PLASMA_NEW(WAVHeader, plWAVHeader)

PY_METHOD_VA(WAVHeader, read,
    "Params: stream\n"
    "Reads this object from `stream`")
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

PY_METHOD_VA(WAVHeader, write,
    "Params: stream\n"
    "Writes this object to `stream`")
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

PY_PLASMA_TYPE(WAVHeader, plWAVHeader, "plWAVHeader wrapper")

PY_PLASMA_TYPE_INIT(WAVHeader)
{
    pyWAVHeader_Type.tp_dealloc = pyWAVHeader_dealloc;
    pyWAVHeader_Type.tp_new = pyWAVHeader_new;
    pyWAVHeader_Type.tp_methods = pyWAVHeader_Methods;
    pyWAVHeader_Type.tp_getset = pyWAVHeader_GetSet;
    if (PyType_CheckAndReady(&pyWAVHeader_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(WAVHeader, "kPCMFormatTag", plWAVHeader::kPCMFormatTag);

    Py_INCREF(&pyWAVHeader_Type);
    return (PyObject*)&pyWAVHeader_Type;
}

PY_PLASMA_IFC_METHODS(WAVHeader, plWAVHeader)
