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

#include "pyKeys.h"

#include <PRP/Animation/hsKeys.h>
#include "Stream/pyStream.h"

PY_PLASMA_DEALLOC(KeyFrame)
PY_PLASMA_NEW_MSG(KeyFrame, "hsKeyFrame is abstract")

PY_METHOD_VA(KeyFrame, read,
    "Params: stream, type\n"
    "Reads this object from the stream")
{
    pyStream* stream;
    int type;
    if (!PyArg_ParseTuple(args, "Oi", &stream, &type)) {
        PyErr_SetString(PyExc_TypeError, "read expects hsStream, int");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects hsStream, int");
        return nullptr;
    }
    self->fThis->read(stream->fThis, type);
    Py_RETURN_NONE;
}

PY_METHOD_VA(KeyFrame, write,
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

static PyMethodDef pyKeyFrame_Methods[] = {
    pyKeyFrame_read_method,
    pyKeyFrame_write_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY(unsigned int, KeyFrame, type, getType, setType)
PY_PROPERTY(unsigned int, KeyFrame, frame, getFrame, setFrame)
PY_PROPERTY(float, KeyFrame, frameTime, getFrameTime, setFrameTime)

static PyGetSetDef pyKeyFrame_GetSet[] = {
    pyKeyFrame_type_getset,
    pyKeyFrame_frame_getset,
    pyKeyFrame_frameTime_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(KeyFrame, hsKeyFrame, "hsKeyFrame wrapper")

PY_PLASMA_TYPE_INIT(KeyFrame)
{
    pyKeyFrame_Type.tp_dealloc = pyKeyFrame_dealloc;
    pyKeyFrame_Type.tp_new = pyKeyFrame_new;
    pyKeyFrame_Type.tp_methods = pyKeyFrame_Methods;
    pyKeyFrame_Type.tp_getset = pyKeyFrame_GetSet;
    if (PyType_CheckAndReady(&pyKeyFrame_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(KeyFrame, "kUnknownKeyFrame", hsKeyFrame::kUnknownKeyFrame);
    PY_TYPE_ADD_CONST(KeyFrame, "kPoint3KeyFrame", hsKeyFrame::kPoint3KeyFrame);
    PY_TYPE_ADD_CONST(KeyFrame, "kBezPoint3KeyFrame", hsKeyFrame::kBezPoint3KeyFrame);
    PY_TYPE_ADD_CONST(KeyFrame, "kScalarKeyFrame", hsKeyFrame::kScalarKeyFrame);
    PY_TYPE_ADD_CONST(KeyFrame, "kBezScalarKeyFrame", hsKeyFrame::kBezScalarKeyFrame);
    PY_TYPE_ADD_CONST(KeyFrame, "kScaleKeyFrame", hsKeyFrame::kScaleKeyFrame);
    PY_TYPE_ADD_CONST(KeyFrame, "kBezScaleKeyFrame", hsKeyFrame::kBezScaleKeyFrame);
    PY_TYPE_ADD_CONST(KeyFrame, "kQuatKeyFrame", hsKeyFrame::kQuatKeyFrame);
    PY_TYPE_ADD_CONST(KeyFrame, "kCompressedQuatKeyFrame32", hsKeyFrame::kCompressedQuatKeyFrame32);
    PY_TYPE_ADD_CONST(KeyFrame, "kCompressedQuatKeyFrame64", hsKeyFrame::kCompressedQuatKeyFrame64);
    PY_TYPE_ADD_CONST(KeyFrame, "k3dsMaxKeyFrame", hsKeyFrame::k3dsMaxKeyFrame);
    PY_TYPE_ADD_CONST(KeyFrame, "kMatrix33KeyFrame", hsKeyFrame::kMatrix33KeyFrame);
    PY_TYPE_ADD_CONST(KeyFrame, "kMatrix44KeyFrame", hsKeyFrame::kMatrix44KeyFrame);

    Py_INCREF(&pyKeyFrame_Type);
    return (PyObject*)&pyKeyFrame_Type;
}

PY_PLASMA_IFC_METHODS(KeyFrame, hsKeyFrame)
