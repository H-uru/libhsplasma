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

#include "pyStream.h"

#include <Stream/hsRAMStream.h>

extern "C" {

PY_PLASMA_NEW(RAMStream, hsRAMStream)

static PyObject* pyRAMStream_resize(pyRAMStream* self, PyObject* args) {
    int newSize;

    if (!PyArg_ParseTuple(args, "i", &newSize)) {
        PyErr_SetString(PyExc_TypeError, "resize expects an int");
        return NULL;
    }
    self->fThis->resize(newSize);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef pyRAMStream_Methods[] = {
    { "resize", (PyCFunction)pyRAMStream_resize, METH_VARARGS,
      "Params: newsize\n"
      "Allocates newsize bytes in the internal buffer.  This will truncate "
      "data if it's shorter than the current buffer, or zero-fill the extra "
      "space if it's larger than the current buffer." },
    { NULL, NULL, 0, NULL }
};

PY_GETSET_GETTER_DECL(RAMStream, buffer) {
    char* buf = new char[self->fThis->size()];
    self->fThis->copyTo(buf, self->fThis->size());
    PyObject* bufObj = PyBytes_FromStringAndSize(buf, self->fThis->size());
    delete[] buf;
    return bufObj;
}

PY_GETSET_SETTER_DECL(RAMStream, buffer) {
    if (!PyBytes_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "buffer should be a binary string");
        return -1;
    }
    char* buf;
    Py_ssize_t len;
    PyBytes_AsStringAndSize(value, &buf, &len);
    self->fThis->copyFrom(buf, len);
    return 0;
}

PY_PROPERTY_GETSET_DECL(RAMStream, buffer)

static PyGetSetDef pyRAMStream_GetSet[] = {
    pyRAMStream_buffer_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyRAMStream_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.hsRAMStream",           /* tp_name */
    sizeof(pyRAMStream),                /* tp_basicsize */
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

    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
    "hsRAMStream wrapper",              /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyRAMStream_Methods,                /* tp_methods */
    NULL,                               /* tp_members */
    pyRAMStream_GetSet,                 /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyRAMStream_new,                    /* tp_new */
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

PyObject* Init_pyRAMStream_Type() {
    pyRAMStream_Type.tp_base = &pyStream_Type;
    if (PyType_Ready(&pyRAMStream_Type) < 0)
        return NULL;

    Py_INCREF(&pyRAMStream_Type);
    return (PyObject*)&pyRAMStream_Type;
}

PY_PLASMA_IFC_METHODS(RAMStream, hsRAMStream)

}
