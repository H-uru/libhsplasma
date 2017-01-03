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

#include "pyGBufferGroup.h"

#include <PRP/Geometry/plGBufferGroup.h>
#include "Math/pyGeometry3.h"
#include "Stream/pyStream.h"

extern "C" {

PY_PLASMA_VALUE_DEALLOC(GBufferTriangle)
PY_PLASMA_EMPTY_INIT(GBufferTriangle)
PY_PLASMA_VALUE_NEW(GBufferTriangle, plGBufferTriangle)

PY_METHOD_VA(GBufferTriangle, read,
    "Params: stream\n"
    "Reads the triangle from a stream")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects an hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects an hsStream");
        return NULL;
    }
    self->fThis->read(stream->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(GBufferTriangle, write,
    "Params: stream\n"
    "Writes the triangle to a stream")
{
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
    Py_RETURN_NONE;
}

static PyMethodDef pyGBufferTriangle_Methods[] = {
    pyGBufferTriangle_read_method,
    pyGBufferTriangle_write_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY_MEMBER(unsigned short, GBufferTriangle, index1, fIndex1)
PY_PROPERTY_MEMBER(unsigned short, GBufferTriangle, index2, fIndex2)
PY_PROPERTY_MEMBER(unsigned short, GBufferTriangle, index3, fIndex3)
PY_PROPERTY_MEMBER(unsigned short, GBufferTriangle, spanIndex, fSpanIndex)
PY_PROPERTY_MEMBER(hsVector3, GBufferTriangle, center, fCenter)

static PyGetSetDef pyGBufferTriangle_GetSet[] = {
    pyGBufferTriangle_index1_getset,
    pyGBufferTriangle_index2_getset,
    pyGBufferTriangle_index3_getset,
    pyGBufferTriangle_spanIndex_getset,
    pyGBufferTriangle_center_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyGBufferTriangle_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plGBufferTriangle",     /* tp_name */
    sizeof(pyGBufferTriangle),          /* tp_basicsize */
    0,                                  /* tp_itemsize */

    pyGBufferTriangle_dealloc,          /* tp_dealloc */
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
    "plGBufferTriangle wrapper",        /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyGBufferTriangle_Methods,          /* tp_methods */
    NULL,                               /* tp_members */
    pyGBufferTriangle_GetSet,           /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    pyGBufferTriangle___init__,         /* tp_init */
    NULL,                               /* tp_alloc */
    pyGBufferTriangle_new,              /* tp_new */
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

PyObject* Init_pyGBufferTriangle_Type() {
    if (PyType_Ready(&pyGBufferTriangle_Type) < 0)
        return NULL;

    Py_INCREF(&pyGBufferTriangle_Type);
    return (PyObject*)&pyGBufferTriangle_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(GBufferTriangle, plGBufferTriangle)

}
