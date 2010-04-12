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
#include <PRP/Animation/hsKeys.h>
#include "pyKeys.h"
#include "Math/pyGeometry3.h"

extern "C" {

static int pyCompressedQuatKey64___init__(pyCompressedQuatKey64* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pyCompressedQuatKey64_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyCompressedQuatKey64* self = (pyCompressedQuatKey64*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new hsCompressedQuatKey64();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyCompressedQuatKey64_setValue(pyCompressedQuatKey64* self, PyObject* args) {
    pyQuat* value;
    int type;
    if (!PyArg_ParseTuple(args, "Oi", &value, &type)) {
        PyErr_SetString(PyExc_TypeError, "setValue expects hsQuat, int");
        return NULL;
    }
    if (!pyQuat_Check((PyObject*)value)) {
        PyErr_SetString(PyExc_TypeError, "setValue expects hsQuat, int");
        return NULL;
    }
    self->fThis->setQuat(*value->fThis, type);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyCompressedQuatKey64_getValue(pyCompressedQuatKey64* self, void*) {
    return pyQuat_FromQuat(self->fThis->getQuat());
}

static int pyCompressedQuatKey64_setValueErr(pyCompressedQuatKey64* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To set the compressed quat, use setValue()");
    return -1;
}

static PyMethodDef pyCompressedQuatKey64_Methods[] = {
    { "setValue", (PyCFunction)pyCompressedQuatKey64_setValue, METH_VARARGS,
      "Params: quat, type\n"
      "Set the hsQuat data.  Type is the compression nuking to use" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyCompressedQuatKey64_GetSet[] = {
    { "value", (getter)pyCompressedQuatKey64_getValue, (setter)pyCompressedQuatKey64_setValueErr, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyCompressedQuatKey64_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.hsCompressedQuatKey64",   /* tp_name */
    sizeof(pyCompressedQuatKey64),      /* tp_basicsize */
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
    "hsCompressedQuatKey64 wrapper",    /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyCompressedQuatKey64_Methods,      /* tp_methods */
    NULL,                               /* tp_members */
    pyCompressedQuatKey64_GetSet,       /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyCompressedQuatKey64___init__, /* tp_init */
    NULL,                               /* tp_alloc */
    pyCompressedQuatKey64_new,          /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */
};

PyObject* Init_pyCompressedQuatKey64_Type() {
    pyCompressedQuatKey64_Type.tp_base = &pyKeyFrame_Type;
    if (PyType_Ready(&pyCompressedQuatKey64_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyCompressedQuatKey64_Type.tp_dict, "kCompQuatNukeX",
                         PyInt_FromLong(hsCompressedQuatKey64::kCompQuatNukeX));
    PyDict_SetItemString(pyCompressedQuatKey64_Type.tp_dict, "kCompQuatNukeY",
                         PyInt_FromLong(hsCompressedQuatKey64::kCompQuatNukeY));
    PyDict_SetItemString(pyCompressedQuatKey64_Type.tp_dict, "kCompQuatNukeZ",
                         PyInt_FromLong(hsCompressedQuatKey64::kCompQuatNukeZ));
    PyDict_SetItemString(pyCompressedQuatKey64_Type.tp_dict, "kCompQuatNukeW",
                         PyInt_FromLong(hsCompressedQuatKey64::kCompQuatNukeW));

    Py_INCREF(&pyCompressedQuatKey64_Type);
    return (PyObject*)&pyCompressedQuatKey64_Type;
}

int pyCompressedQuatKey64_Check(PyObject* obj) {
    if (obj->ob_type == &pyCompressedQuatKey64_Type
        || PyType_IsSubtype(obj->ob_type, &pyCompressedQuatKey64_Type))
        return 1;
    return 0;
}

PyObject* pyCompressedQuatKey64_FromCompressedQuatKey64(hsCompressedQuatKey64* frame) {
    if (frame == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyCompressedQuatKey64* pyobj = PyObject_New(pyCompressedQuatKey64, &pyCompressedQuatKey64_Type);
    pyobj->fThis = frame;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
