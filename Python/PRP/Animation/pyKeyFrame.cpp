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

extern "C" {

static void pyKeyFrame_dealloc(pyKeyFrame* self) {
    if (self->fPyOwned)
        delete self->fThis;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject* pyKeyFrame_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "hsKeyFrame is abstract");
    return NULL;
}

static PyObject* pyKeyFrame_read(pyKeyFrame* self, PyObject* args) {
    pyStream* stream;
    int type;
    if (!PyArg_ParseTuple(args, "Oi", &stream, &type)) {
        PyErr_SetString(PyExc_TypeError, "read expects hsStream, int");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects hsStream, int");
        return NULL;
    }
    self->fThis->read(stream->fThis, type);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyKeyFrame_write(pyKeyFrame* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects an hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects an hsStream");
        return NULL;
    }
    self->fThis->write(stream->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef pyKeyFrame_Methods[] = {
    { "read", (PyCFunction)pyKeyFrame_read, METH_VARARGS,
      "Params: stream, type\n"
      "Reads this object from the stream" },
    { "write", (PyCFunction)pyKeyFrame_write, METH_VARARGS,
      "Params: stream\n"
      "Writes this object to the stream" },
    { NULL, NULL, 0, NULL }
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

PyTypeObject pyKeyFrame_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.hsKeyFrame",            /* tp_name */
    sizeof(pyKeyFrame),                 /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pyKeyFrame_dealloc,     /* tp_dealloc */
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
    "hsKeyFrame wrapper",               /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyKeyFrame_Methods,                 /* tp_methods */
    NULL,                               /* tp_members */
    pyKeyFrame_GetSet,                  /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyKeyFrame_new,                     /* tp_new */
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

PyObject* Init_pyKeyFrame_Type() {
    if (PyType_Ready(&pyKeyFrame_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyKeyFrame_Type.tp_dict, "kUnknownKeyFrame",
                         PyInt_FromLong(hsKeyFrame::kUnknownKeyFrame));
    PyDict_SetItemString(pyKeyFrame_Type.tp_dict, "kPoint3KeyFrame",
                         PyInt_FromLong(hsKeyFrame::kPoint3KeyFrame));
    PyDict_SetItemString(pyKeyFrame_Type.tp_dict, "kBezPoint3KeyFrame",
                         PyInt_FromLong(hsKeyFrame::kBezPoint3KeyFrame));
    PyDict_SetItemString(pyKeyFrame_Type.tp_dict, "kScalarKeyFrame",
                         PyInt_FromLong(hsKeyFrame::kScalarKeyFrame));
    PyDict_SetItemString(pyKeyFrame_Type.tp_dict, "kBezScalarKeyFrame",
                         PyInt_FromLong(hsKeyFrame::kBezScalarKeyFrame));
    PyDict_SetItemString(pyKeyFrame_Type.tp_dict, "kScaleKeyFrame",
                         PyInt_FromLong(hsKeyFrame::kScaleKeyFrame));
    PyDict_SetItemString(pyKeyFrame_Type.tp_dict, "kBezScaleKeyFrame",
                         PyInt_FromLong(hsKeyFrame::kBezScaleKeyFrame));
    PyDict_SetItemString(pyKeyFrame_Type.tp_dict, "kQuatKeyFrame",
                         PyInt_FromLong(hsKeyFrame::kQuatKeyFrame));
    PyDict_SetItemString(pyKeyFrame_Type.tp_dict, "kCompressedQuatKeyFrame32",
                         PyInt_FromLong(hsKeyFrame::kCompressedQuatKeyFrame32));
    PyDict_SetItemString(pyKeyFrame_Type.tp_dict, "kCompressedQuatKeyFrame64",
                         PyInt_FromLong(hsKeyFrame::kCompressedQuatKeyFrame64));
    PyDict_SetItemString(pyKeyFrame_Type.tp_dict, "k3dsMaxKeyFrame",
                         PyInt_FromLong(hsKeyFrame::k3dsMaxKeyFrame));
    PyDict_SetItemString(pyKeyFrame_Type.tp_dict, "kMatrix33KeyFrame",
                         PyInt_FromLong(hsKeyFrame::kMatrix33KeyFrame));
    PyDict_SetItemString(pyKeyFrame_Type.tp_dict, "kMatrix44KeyFrame",
                         PyInt_FromLong(hsKeyFrame::kMatrix44KeyFrame));

    Py_INCREF(&pyKeyFrame_Type);
    return (PyObject*)&pyKeyFrame_Type;
}

PY_PLASMA_IFC_METHODS(KeyFrame, hsKeyFrame)

}
