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

#include <PyPlasma.h>
#include <Stream/hsStream.h>
#include "pyStream.h"

extern "C" {

static void pyFileStream_dealloc(pyFileStream* self) {
    delete self->fThis;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject* pyFileStream_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyFileStream* self = (pyFileStream*)type->tp_alloc(type, 0);
    if (self != NULL)
        self->fThis = new hsFileStream();
    return (PyObject*)self;
}

static PyObject* pyFileStream_open(pyFileStream* self, PyObject* args) {
    const char* filename;
    int mode;

    if (!PyArg_ParseTuple(args, "si", &filename, &mode)) {
        PyErr_SetString(PyExc_TypeError, "open expects string, int");
        return NULL;
    }
    try {
        if (!self->fThis->open(filename, (FileMode)mode)) {
            PyErr_SetString(PyExc_IOError, "Error opening file");
            return NULL;
        }
        Py_INCREF(Py_None);
        return Py_None;
    } catch (...) {
        PyErr_SetString(PyExc_IOError, "Error opening file");
        return NULL;
    }
}

static PyObject* pyFileStream_close(pyFileStream* self) {
    self->fThis->close();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef pyFileStream_Methods[] = {
    { "open", (PyCFunction)pyFileStream_open, METH_VARARGS,
      "Params: filename, mode\n"
      "Opens the specified file.\n"
      "Mode is: fmRead, fmWrite, fmReadWrite, fmCreate" },
    { "close", (PyCFunction)pyFileStream_close, METH_NOARGS,
      "Closes the active file, if it is open" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyFileStream_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.hsFileStream",            /* tp_name */
    sizeof(pyFileStream),               /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pyFileStream_dealloc,   /* tp_dealloc */
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
    "hsFileStream wrapper",             /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyFileStream_Methods,               /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyFileStream_new,                   /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyFileStream_Type() {
    pyFileStream_Type.tp_base = &pyStream_Type;
    if (PyType_Ready(&pyFileStream_Type) < 0)
        return NULL;

    Py_INCREF(&pyFileStream_Type);
    return (PyObject*)&pyFileStream_Type;
}

}
