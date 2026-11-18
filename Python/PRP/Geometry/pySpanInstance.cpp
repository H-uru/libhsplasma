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

#include "pySpanInstance.h"

#include <PRP/Geometry/plSpanInstance.h>
#include "Stream/pyStream.h"
#include "Math/pyMatrix.h"
#include "Math/pyGeometry3.h"

PY_PLASMA_DEALLOC(SpanInstance)
PY_PLASMA_EMPTY_INIT(SpanInstance)
PY_PLASMA_NEW(SpanInstance, plSpanInstance)

PY_METHOD_VA(SpanInstance, read,
    "Params: stream, encoding, numVerts\n"
    "Reads this object from the stream")
{
    pyStream* stream;
    pySpanEncoding* encoding;
    int numVerts;
    if (!PyArg_ParseTuple(args, "OOi", &stream, &encoding, &numVerts)) {
        PyErr_SetString(PyExc_TypeError, "read expects hsStream, plSpanEncoding, int");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream) || !pySpanEncoding_Check((PyObject*)encoding)) {
        PyErr_SetString(PyExc_TypeError, "read expects hsStream, plSpanEncoding, int");
        return nullptr;
    }
    self->fThis->read(stream->fThis, *encoding->fThis, numVerts);
    Py_RETURN_NONE;
}

PY_METHOD_VA(SpanInstance, write,
    "Params: stream\n"
    "Writes this object to the stream")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects an hsStream");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects an hsStream");
        return nullptr;
    }
    self->fThis->write(stream->fThis);
    Py_RETURN_NONE;
}

static PyMethodDef pySpanInstance_Methods[] = {
    pySpanInstance_read_method,
    pySpanInstance_write_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY_VECTOR(hsVector3, SpanInstance, posDeltas, getPosDeltas, setPosDeltas)
PY_PROPERTY_VECTOR(unsigned int, SpanInstance, colors, getColors, setColors)
PY_PROPERTY(hsMatrix44, SpanInstance, localToWorld, getLocalToWorld, setLocalToWorld)

static PyGetSetDef pySpanInstance_GetSet[] = {
    pySpanInstance_posDeltas_getset,
    pySpanInstance_colors_getset,
    pySpanInstance_localToWorld_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(SpanInstance, plSpanInstance, "plSpanInstance wrapper")

PY_PLASMA_TYPE_INIT(SpanInstance)
{
    pySpanInstance_Type.tp_dealloc = pySpanInstance_dealloc;
    pySpanInstance_Type.tp_init = pySpanInstance___init__;
    pySpanInstance_Type.tp_new = pySpanInstance_new;
    pySpanInstance_Type.tp_methods = pySpanInstance_Methods;
    pySpanInstance_Type.tp_getset = pySpanInstance_GetSet;
    if (PyType_CheckAndReady(&pySpanInstance_Type) < 0)
        return nullptr;

    Py_INCREF(&pySpanInstance_Type);
    return (PyObject*)&pySpanInstance_Type;
}

PY_PLASMA_IFC_METHODS(SpanInstance, plSpanInstance)
