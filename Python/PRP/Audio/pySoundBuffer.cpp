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

PY_PLASMA_NEW(SoundBuffer, plSoundBuffer)

PY_PROPERTY_PROXY(plWAVHeader, SoundBuffer, header, getHeader)
PY_PROPERTY_PATHLIKE(SoundBuffer, fileName, getFileName, setFileName)
PY_PROPERTY(unsigned int, SoundBuffer, flags, getFlags, setFlags)
PY_PROPERTY(size_t, SoundBuffer, dataLength, getDataLength, setDataLength)

PY_GETSET_GETTER_DECL(SoundBuffer, data)
{
    if (self->fThis->getData() == nullptr) {
        Py_RETURN_NONE;
    } else {
        return PyBytes_FromStringAndSize((const char*)self->fThis->getData(),
                                         self->fThis->getDataLength());
    }
}

PY_GETSET_SETTER_DECL(SoundBuffer, data)
{
    PY_PROPERTY_CHECK_NULL(data)
    if (value == Py_None) {
        self->fThis->setData(0, nullptr);
        return 0;
    } else if (!PyBytes_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "data should be a binary string");
        return -1;
    }
    char* buffer;
    Py_ssize_t length;
    PyBytes_AsStringAndSize(value, &buffer, &length);
    self->fThis->setData(length, (const unsigned char*)buffer);
    return 0;
}

PY_PROPERTY_GETSET_DECL(SoundBuffer, data)

static PyGetSetDef pySoundBuffer_GetSet[] = {
    pySoundBuffer_header_getset,
    pySoundBuffer_fileName_getset,
    pySoundBuffer_flags_getset,
    pySoundBuffer_data_getset,
    pySoundBuffer_dataLength_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(SoundBuffer, plSoundBuffer, "plSoundBuffer wrapper")

PY_PLASMA_TYPE_INIT(SoundBuffer)
{
    pySoundBuffer_Type.tp_new = pySoundBuffer_new;
    pySoundBuffer_Type.tp_getset = pySoundBuffer_GetSet;
    pySoundBuffer_Type.tp_base = &pyKeyedObject_Type;
    if (PyType_CheckAndReady(&pySoundBuffer_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(SoundBuffer, "kIsExternal", plSoundBuffer::kIsExternal);
    PY_TYPE_ADD_CONST(SoundBuffer, "kAlwaysExternal", plSoundBuffer::kAlwaysExternal);
    PY_TYPE_ADD_CONST(SoundBuffer, "kOnlyLeftChannel", plSoundBuffer::kOnlyLeftChannel);
    PY_TYPE_ADD_CONST(SoundBuffer, "kOnlyRightChannel", plSoundBuffer::kOnlyRightChannel);
    PY_TYPE_ADD_CONST(SoundBuffer, "kStreamCompressed", plSoundBuffer::kStreamCompressed);

    Py_INCREF(&pySoundBuffer_Type);
    return (PyObject*)&pySoundBuffer_Type;
}

PY_PLASMA_IFC_METHODS(SoundBuffer, plSoundBuffer)
