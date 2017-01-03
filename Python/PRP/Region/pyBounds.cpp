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

#include "pyBounds.h"

#include <PRP/Region/hsBounds.h>
#include "Stream/pyStream.h"

extern "C" {

PY_PLASMA_VALUE_DEALLOC(Bounds)
PY_PLASMA_EMPTY_INIT(Bounds)
PY_PLASMA_VALUE_NEW(Bounds, hsBounds)

PY_METHOD_NOARGS(Bounds, ClassName,
    "Returns the RTTI Class name of this Bounds object")
{
    return PyString_FromString(self->fThis->ClassName());
}

PY_METHOD_VA(Bounds, read,
    "Params: stream\n"
    "Read this Bounds object from the stream")
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

PY_METHOD_VA(Bounds, write,
    "Params: stream\n"
    "Write this Bounds object to the stream")
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

static PyMethodDef pyBounds_Methods[] = {
    pyBounds_ClassName_method,
    pyBounds_read_method,
    pyBounds_write_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY(int, Bounds, type, getType, setType)

static PyGetSetDef pyBounds_GetSet[] = {
    pyBounds_type_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyBounds_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.hsBounds",              /* tp_name */
    sizeof(pyBounds),                   /* tp_basicsize */
    0,                                  /* tp_itemsize */

    pyBounds_dealloc,                   /* tp_dealloc */
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
    "hsBounds wrapper",                 /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyBounds_Methods,                   /* tp_methods */
    NULL,                               /* tp_members */
    pyBounds_GetSet,                    /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    pyBounds___init__,                  /* tp_init */
    NULL,                               /* tp_alloc */
    pyBounds_new,                       /* tp_new */
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

PyObject* Init_pyBounds_Type() {
    if (PyType_Ready(&pyBounds_Type) < 0)
        return NULL;

    Py_INCREF(&pyBounds_Type);
    return (PyObject*)&pyBounds_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(Bounds, hsBounds)

}
