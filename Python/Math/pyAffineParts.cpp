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
#include <Math/hsAffineParts.h>
#include "pyGeometry3.h"
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

static PyObject* pyAffineParts_getI(pyAffineParts* self, void*) {
    return PyInt_FromLong(self->fThis->fI);
}

static PyObject* pyAffineParts_getT(pyAffineParts* self, void*) {
    return pyVector3_FromVector3(self->fThis->fT);
}

static PyObject* pyAffineParts_getQ(pyAffineParts* self, void*) {
    return pyQuat_FromQuat(self->fThis->fQ);
}

static PyObject* pyAffineParts_getU(pyAffineParts* self, void*) {
    return pyQuat_FromQuat(self->fThis->fU);
}

static PyObject* pyAffineParts_getK(pyAffineParts* self, void*) {
    return pyVector3_FromVector3(self->fThis->fK);
}

static PyObject* pyAffineParts_getF(pyAffineParts* self, void*) {
    return PyFloat_FromDouble(self->fThis->fF);
}

static int pyAffineParts_setI(pyAffineParts* self, PyObject* value, void*) {
    if (!PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "I should be be an int");
        return -1;
    }
    self->fThis->fI = PyInt_AsLong(value);
    return 0;
}

static int pyAffineParts_setT(pyAffineParts* self, PyObject* value, void*) {
    if (!pyVector3_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "T should be an hsVector3");
        return -1;
    }
    self->fThis->fT = *((pyVector3*)value)->fThis;
    return 0;
}

static int pyAffineParts_setQ(pyAffineParts* self, PyObject* value, void*) {
    if (!pyQuat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "Q should be an hsQuat");
        return -1;
    }
    self->fThis->fQ = *((pyQuat*)value)->fThis;
    return 0;
}

static int pyAffineParts_setU(pyAffineParts* self, PyObject* value, void*) {
    if (!pyQuat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "U should be an hsUuat");
        return -1;
    }
    self->fThis->fU = *((pyQuat*)value)->fThis;
    return 0;
}

static int pyAffineParts_setK(pyAffineParts* self, PyObject* value, void*) {
    if (!pyVector3_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "K should be an hsVector3");
        return -1;
    }
    self->fThis->fK = *((pyVector3*)value)->fThis;
    return 0;
}

static int pyAffineParts_setF(pyAffineParts* self, PyObject* value, void*) {
    if (!PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "F should be a float");
        return -1;
    }
    self->fThis->fF = PyFloat_AsDouble(value);
    return 0;
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

PyGetSetDef pyAffineParts_GetSet[] = {
    { _pycs("I"), (getter)pyAffineParts_getI, (setter)pyAffineParts_setI, NULL, NULL },
    { _pycs("T"), (getter)pyAffineParts_getT, (setter)pyAffineParts_setT, NULL, NULL },
    { _pycs("Q"), (getter)pyAffineParts_getQ, (setter)pyAffineParts_setQ, NULL, NULL },
    { _pycs("U"), (getter)pyAffineParts_getU, (setter)pyAffineParts_setU, NULL, NULL },
    { _pycs("K"), (getter)pyAffineParts_getK, (setter)pyAffineParts_setK, NULL, NULL },
    { _pycs("F"), (getter)pyAffineParts_getF, (setter)pyAffineParts_setF, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
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

int pyAffineParts_Check(PyObject* obj) {
    if (obj->ob_type == &pyAffineParts_Type
        || PyType_IsSubtype(obj->ob_type, &pyAffineParts_Type))
        return 1;
    return 0;
}

PyObject* pyAffineParts_FromAffineParts(const hsAffineParts& quat) {
    pyAffineParts* pq = PyObject_New(pyAffineParts, &pyAffineParts_Type);
    pq->fThis = new hsAffineParts(quat);
    return (PyObject*)pq;
}

}
