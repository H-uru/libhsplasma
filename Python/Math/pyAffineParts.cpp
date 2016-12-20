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

#include "pyGeometry3.h"

#include <Math/hsAffineParts.h>
#include "Stream/pyStream.h"

extern "C" {

static void pyAffineParts_dealloc(pyAffineParts* self) {
    delete self->fThis;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static int pyAffineParts___init__(pyAffineParts* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pyAffineParts_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyAffineParts* self = (pyAffineParts*)type->tp_alloc(type, 0);
    if (self != NULL)
        self->fThis = new hsAffineParts();
    return (PyObject*)self;
}

static PyObject* pyAffineParts_read(pyAffineParts* self, PyObject* args) {
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
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyAffineParts_write(pyAffineParts* self, PyObject* args) {
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
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyAffineParts_reset(pyAffineParts* self) {
    self->fThis->reset();
    Py_INCREF(Py_None);
    return Py_None;
}

PyMethodDef pyAffineParts_Methods[] = {
    { "read", (PyCFunction)pyAffineParts_read, METH_VARARGS,
      "Params: stream\n"
      "Reads this object from `stream`" },
    { "write", (PyCFunction)pyAffineParts_write, METH_VARARGS,
      "Params: stream\n"
      "Writes this object to `stream`" },
    { "reset", (PyCFunction)pyAffineParts_reset, METH_NOARGS,
      "Resets the transform to the identity" },
    { NULL, NULL, 0, NULL }
};

PY_PROPERTY_MEMBER(int, AffineParts, I, fI)
PY_PROPERTY_MEMBER(hsVector3, AffineParts, T, fT)
PY_PROPERTY_MEMBER(hsQuat, AffineParts, Q, fQ)
PY_PROPERTY_MEMBER(hsQuat, AffineParts, U, fU)
PY_PROPERTY_MEMBER(hsVector3, AffineParts, K, fK)
PY_PROPERTY_MEMBER(float, AffineParts, F, fF)

PyGetSetDef pyAffineParts_GetSet[] = {
    pyAffineParts_I_getset,
    pyAffineParts_T_getset,
    pyAffineParts_Q_getset,
    pyAffineParts_U_getset,
    pyAffineParts_K_getset,
    pyAffineParts_F_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyAffineParts_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.hsAffineParts",         /* tp_name */
    sizeof(pyAffineParts),              /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pyAffineParts_dealloc,  /* tp_dealloc */
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

    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_CHECKTYPES, /* tp_flags */
    "Plasma 3DS Max AffineParts wrapper", /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyAffineParts_Methods,              /* tp_methods */
    NULL,                               /* tp_members */
    pyAffineParts_GetSet,               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyAffineParts___init__,   /* tp_init */
    NULL,                               /* tp_alloc */
    pyAffineParts_new,                  /* tp_new */
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

PyObject* Init_pyAffineParts_Type() {
    if (PyType_Ready(&pyAffineParts_Type) < 0)
        return NULL;

    Py_INCREF(&pyAffineParts_Type);
    return (PyObject*)&pyAffineParts_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(AffineParts, hsAffineParts)

}
