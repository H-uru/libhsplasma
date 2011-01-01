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

static int pyCompressedQuatKey32___init__(pyCompressedQuatKey32* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pyCompressedQuatKey32_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyCompressedQuatKey32* self = (pyCompressedQuatKey32*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new hsCompressedQuatKey32();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyCompressedQuatKey32_setValue(pyCompressedQuatKey32* self, PyObject* args) {
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

static PyObject* pyCompressedQuatKey32_getValue(pyCompressedQuatKey32* self, void*) {
    return pyQuat_FromQuat(self->fThis->getQuat());
}

static int pyCompressedQuatKey32_setValueErr(pyCompressedQuatKey32* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To set the compressed quat, use setValue()");
    return -1;
}

static PyMethodDef pyCompressedQuatKey32_Methods[] = {
    { "setValue", (PyCFunction)pyCompressedQuatKey32_setValue, METH_VARARGS,
      "Params: quat, type\n"
      "Set the hsQuat data.  Type is the compression nuking to use" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyCompressedQuatKey32_GetSet[] = {
    { "value", (getter)pyCompressedQuatKey32_getValue, (setter)pyCompressedQuatKey32_setValueErr, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyCompressedQuatKey32_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.hsCompressedQuatKey32",   /* tp_name */
    sizeof(pyCompressedQuatKey32),      /* tp_basicsize */
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
    "hsCompressedQuatKey32 wrapper",    /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyCompressedQuatKey32_Methods,      /* tp_methods */
    NULL,                               /* tp_members */
    pyCompressedQuatKey32_GetSet,       /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyCompressedQuatKey32___init__, /* tp_init */
    NULL,                               /* tp_alloc */
    pyCompressedQuatKey32_new,          /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */

    NULL,                               /* tp_del */
    TP_VERSION_TAG_INIT                 /* tp_version_tag */
};

PyObject* Init_pyCompressedQuatKey32_Type() {
    pyCompressedQuatKey32_Type.tp_base = &pyKeyFrame_Type;
    if (PyType_Ready(&pyCompressedQuatKey32_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyCompressedQuatKey32_Type.tp_dict, "kCompQuatNukeX",
                         PyInt_FromLong(hsCompressedQuatKey32::kCompQuatNukeX));
    PyDict_SetItemString(pyCompressedQuatKey32_Type.tp_dict, "kCompQuatNukeY",
                         PyInt_FromLong(hsCompressedQuatKey32::kCompQuatNukeY));
    PyDict_SetItemString(pyCompressedQuatKey32_Type.tp_dict, "kCompQuatNukeZ",
                         PyInt_FromLong(hsCompressedQuatKey32::kCompQuatNukeZ));
    PyDict_SetItemString(pyCompressedQuatKey32_Type.tp_dict, "kCompQuatNukeW",
                         PyInt_FromLong(hsCompressedQuatKey32::kCompQuatNukeW));

    Py_INCREF(&pyCompressedQuatKey32_Type);
    return (PyObject*)&pyCompressedQuatKey32_Type;
}

int pyCompressedQuatKey32_Check(PyObject* obj) {
    if (obj->ob_type == &pyCompressedQuatKey32_Type
        || PyType_IsSubtype(obj->ob_type, &pyCompressedQuatKey32_Type))
        return 1;
    return 0;
}

PyObject* pyCompressedQuatKey32_FromCompressedQuatKey32(hsCompressedQuatKey32* frame) {
    if (frame == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyCompressedQuatKey32* pyobj = PyObject_New(pyCompressedQuatKey32, &pyCompressedQuatKey32_Type);
    pyobj->fThis = frame;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
