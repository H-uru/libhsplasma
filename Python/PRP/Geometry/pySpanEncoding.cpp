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

extern "C" {

PY_PLASMA_DEALLOC(SpanEncoding)
PY_PLASMA_EMPTY_INIT(SpanEncoding)
PY_PLASMA_NEW(SpanEncoding, plSpanEncoding)

PY_METHOD_VA(SpanEncoding, read,
    "Params: stream\n"
    "Reads this object from the stream")
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

PY_METHOD_VA(SpanEncoding, write,
    "Params: stream\n"
    "Writes this object to the stream")
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

static PyMethodDef pySpanEncoding_Methods[] = {
    pySpanEncoding_read_method,
    pySpanEncoding_write_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY(unsigned int, SpanEncoding, code, getCode, setCode)
PY_PROPERTY(float, SpanEncoding, posScale, getPosScale, setPosScale)

static PyGetSetDef pySpanEncoding_GetSet[] = {
    pySpanEncoding_code_getset,
    pySpanEncoding_posScale_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pySpanEncoding_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plSpanEncoding",        /* tp_name */
    sizeof(pySpanEncoding),             /* tp_basicsize */
    0,                                  /* tp_itemsize */

    pySpanEncoding_dealloc,             /* tp_dealloc */
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
    "plSpanEncoding wrapper",           /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pySpanEncoding_Methods,             /* tp_methods */
    NULL,                               /* tp_members */
    pySpanEncoding_GetSet,              /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    pySpanEncoding___init__,            /* tp_init */
    NULL,                               /* tp_alloc */
    pySpanEncoding_new,                 /* tp_new */
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

PyObject* Init_pySpanEncoding_Type() {
    if (PyType_Ready(&pySpanEncoding_Type) < 0)
        return NULL;

    PY_TYPE_ADD_CONST(SpanEncoding, "kPosNone", plSpanEncoding::kPosNone);
    PY_TYPE_ADD_CONST(SpanEncoding, "kPos888", plSpanEncoding::kPos888);
    PY_TYPE_ADD_CONST(SpanEncoding, "kPos161616", plSpanEncoding::kPos161616);
    PY_TYPE_ADD_CONST(SpanEncoding, "kPos101010", plSpanEncoding::kPos101010);
    PY_TYPE_ADD_CONST(SpanEncoding, "kPos008", plSpanEncoding::kPos008);
    PY_TYPE_ADD_CONST(SpanEncoding, "kPosMask", plSpanEncoding::kPosMask);

    PY_TYPE_ADD_CONST(SpanEncoding, "kColNone", plSpanEncoding::kColNone);
    PY_TYPE_ADD_CONST(SpanEncoding, "kColA8", plSpanEncoding::kColA8);
    PY_TYPE_ADD_CONST(SpanEncoding, "kColI8", plSpanEncoding::kColI8);
    PY_TYPE_ADD_CONST(SpanEncoding, "kColAI88", plSpanEncoding::kColAI88);
    PY_TYPE_ADD_CONST(SpanEncoding, "kColRGB888", plSpanEncoding::kColRGB888);
    PY_TYPE_ADD_CONST(SpanEncoding, "kColARGB8888", plSpanEncoding::kColARGB8888);
    PY_TYPE_ADD_CONST(SpanEncoding, "kColMask", plSpanEncoding::kColMask);

    Py_INCREF(&pySpanEncoding_Type);
    return (PyObject*)&pySpanEncoding_Type;
}

PY_PLASMA_IFC_METHODS(SpanEncoding, plSpanEncoding)

}
