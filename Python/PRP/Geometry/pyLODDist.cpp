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

#include "pyClusterGroup.h"

#include <PRP/Geometry/plClusterGroup.h>
#include "Stream/pyStream.h"

extern "C" {

PY_PLASMA_NEW_MSG(LODDist, "Cannot create plLODDist objects from Python")

static PyObject* pyLODDist_read(pyLODDist* self, PyObject* args) {
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

static PyObject* pyLODDist_write(pyLODDist* self, PyObject* args) {
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

static PyMethodDef pyLODDist_Methods[] = {
    { "read", (PyCFunction)pyLODDist_read, METH_VARARGS,
      "Params: stream\n"
      "Reads this object from the stream" },
    { "write", (PyCFunction)pyLODDist_write, METH_VARARGS,
      "Params: stream\n"
      "Writes this object to the stream" },
    { NULL, NULL, 0, NULL }
};

PY_PROPERTY(float, LODDist, min, getMin, setMin)
PY_PROPERTY(float, LODDist, max, getMax, setMax)

static PyGetSetDef pyLODDist_GetSet[] = {
    pyLODDist_min_getset,
    pyLODDist_max_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyLODDist_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plLODDist",             /* tp_name */
    sizeof(pyLODDist),                  /* tp_basicsize */
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
    "plLODDist wrapper",                /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyLODDist_Methods,                  /* tp_methods */
    NULL,                               /* tp_members */
    pyLODDist_GetSet,                   /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyLODDist_new,                      /* tp_new */
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

PyObject* Init_pyLODDist_Type() {
    if (PyType_Ready(&pyLODDist_Type) < 0)
        return NULL;

    Py_INCREF(&pyLODDist_Type);
    return (PyObject*)&pyLODDist_Type;
}

PY_PLASMA_IFC_METHODS(LODDist, plLODDist)

}
