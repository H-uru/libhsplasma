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

#include <Math/hsGeometry3.h>
#include "Stream/pyStream.h"

extern "C" {

static void pyPlane3_dealloc(pyPlane3* self) {
    delete self->fThis;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static int pyPlane3___init__(pyPlane3* self, PyObject* args, PyObject* kwds) {
    float x = 0.0f, y = 0.0f, z = 0.0f, w = 0.0f;
    PyObject* init = NULL;
    static char* kwlist[] = { _pycs("X"), _pycs("Y"), _pycs("Z"), _pycs("W"), NULL };
    static char* kwlist2[] = { _pycs("Plane"), NULL };

    if (PyArg_ParseTupleAndKeywords(args, kwds, "ffff", kwlist, &x, &y, &z, &w)) {
        (*self->fThis) = hsPlane3(hsVector3(x, y, z), w);
    } else if (PyErr_Clear(), PyArg_ParseTupleAndKeywords(args, kwds, "|O", kwlist2, &init)) {
        if (init == NULL) {
            (*self->fThis) = hsPlane3();
            return 0;
        }
        if (pyPlane3_Check(init)) {
            (*self->fThis) = (*((pyPlane3*)init)->fThis);
        } else {
            PyErr_SetString(PyExc_TypeError, "__init__ expects a Plane");
            return -1;
        }
    } else {
        return -1;
    }

    return 0;
}

static PyObject* pyPlane3_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyPlane3* self = (pyPlane3*)type->tp_alloc(type, 0);
    if (self != NULL)
        self->fThis = new hsPlane3();
    return (PyObject*)self;
}

static PyObject* pyPlane3_Repr(pyPlane3* self) {
    plString repr = plString::Format("hsPlane3(%f, %f, %f, %f)",
             self->fThis->N.X, self->fThis->N.Y, self->fThis->N.Z, self->fThis->W);
    return pyPlasma_convert(repr);
}

static PyObject* pyPlane3_read(pyPlane3* self, PyObject* args) {
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

static PyObject* pyPlane3_write(pyPlane3* self, PyObject* args) {
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

PyMethodDef pyPlane3_Methods[] = {
    { "read", (PyCFunction)pyPlane3_read, METH_VARARGS,
      "Params: stream\n"
      "Reads this Plane from `stream`" },
    { "write", (PyCFunction)pyPlane3_write, METH_VARARGS,
      "Params: stream\n"
      "Writes this Plane to `stream`" },
    { NULL, NULL, 0, NULL }
};

PY_PROPERTY_MEMBER(float, Plane3, X, N.X)
PY_PROPERTY_MEMBER(float, Plane3, Y, N.Y)
PY_PROPERTY_MEMBER(float, Plane3, Z, N.Z)
PY_PROPERTY_MEMBER(float, Plane3, W, W)

PyGetSetDef pyPlane3_GetSet[] = {
    pyPlane3_X_getset,
    pyPlane3_Y_getset,
    pyPlane3_Z_getset,
    pyPlane3_W_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyPlane3_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.hsPlane3",              /* tp_name */
    sizeof(pyPlane3),                   /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pyPlane3_dealloc,       /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_compare */
    (reprfunc)pyPlane3_Repr,            /* tp_repr */
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
    "hsPlane3 wrapper",                 /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyPlane3_Methods,                   /* tp_methods */
    NULL,                               /* tp_members */
    pyPlane3_GetSet,                    /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyPlane3___init__,        /* tp_init */
    NULL,                               /* tp_alloc */
    pyPlane3_new,                       /* tp_new */
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

PyObject* Init_pyPlane3_Type() {
    if (PyType_Ready(&pyPlane3_Type) < 0)
        return NULL;

    Py_INCREF(&pyPlane3_Type);
    return (PyObject*)&pyPlane3_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(Plane3, hsPlane3)

}
