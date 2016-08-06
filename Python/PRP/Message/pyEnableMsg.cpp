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

#include "pyEnableMsg.h"

#include <PRP/Message/plEnableMsg.h>
#include "pyMessage.h"

extern "C" {

static PyObject* pyEnableMsg_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyEnableMsg* self = (pyEnableMsg*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plEnableMsg();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyEnableMsg_getCmd(pyEnableMsg* self, PyObject* args) {
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "getCmd expects an int");
        return NULL;
    }
    return PyBool_FromLong(self->fThis->getCmd().get((size_t)idx) ? 1 : 0);
}

static PyObject* pyEnableMsg_getType(pyEnableMsg* self, PyObject* args) {
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "getType expects an int");
        return NULL;
    }
    return PyBool_FromLong(self->fThis->getTypes().get((size_t)idx) ? 1 : 0);
}

static PyObject* pyEnableMsg_setCmd(pyEnableMsg* self, PyObject* args) {
    Py_ssize_t idx, value;
    if (!PyArg_ParseTuple(args, "nn", &idx, &value)) {
        PyErr_SetString(PyExc_TypeError, "setCmd expects int, bool");
        return NULL;
    }
    self->fThis->getCmd().set(idx, value != 0);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyEnableMsg_setType(pyEnableMsg* self, PyObject* args) {
    Py_ssize_t idx, value;
    if (!PyArg_ParseTuple(args, "nn", &idx, &value)) {
        PyErr_SetString(PyExc_TypeError, "setType expects int, bool");
        return NULL;
    }
    self->fThis->getTypes().set(idx, value != 0);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef pyEnableMsg_Methods[] = {
    { "getCmd", (PyCFunction)pyEnableMsg_getCmd, METH_VARARGS,
      "Params: cmd" },
    { "getType", (PyCFunction)pyEnableMsg_getType, METH_VARARGS,
      "Params: type" },
    { "setCmd", (PyCFunction)pyEnableMsg_setCmd, METH_VARARGS,
      "Params: cmd, value" },
    { "setType", (PyCFunction)pyEnableMsg_setType, METH_VARARGS,
      "Params: type, value" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyEnableMsg_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plEnableMsg",           /* tp_name */
    sizeof(pyEnableMsg),                /* tp_basicsize */
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
    "plEnableMsg wrapper",                    /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyEnableMsg_Methods,                /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyEnableMsg_new,                    /* tp_new */
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

PyObject* Init_pyEnableMsg_Type() {
    pyEnableMsg_Type.tp_base = &pyMessage_Type;
    if (PyType_Ready(&pyEnableMsg_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyEnableMsg_Type.tp_dict, "kDisable",
                         PyInt_FromLong(plEnableMsg::kDisable));
    PyDict_SetItemString(pyEnableMsg_Type.tp_dict, "kEnable",
                         PyInt_FromLong(plEnableMsg::kEnable));
    PyDict_SetItemString(pyEnableMsg_Type.tp_dict, "kDrawable",
                         PyInt_FromLong(plEnableMsg::kDrawable));
    PyDict_SetItemString(pyEnableMsg_Type.tp_dict, "kPhysical",
                         PyInt_FromLong(plEnableMsg::kPhysical));
    PyDict_SetItemString(pyEnableMsg_Type.tp_dict, "kAudible",
                         PyInt_FromLong(plEnableMsg::kAudible));
    PyDict_SetItemString(pyEnableMsg_Type.tp_dict, "kAll",
                         PyInt_FromLong(plEnableMsg::kAll));
    PyDict_SetItemString(pyEnableMsg_Type.tp_dict, "kByType",
                         PyInt_FromLong(plEnableMsg::kByType));


    Py_INCREF(&pyEnableMsg_Type);
    return (PyObject*)&pyEnableMsg_Type;
}

int pyEnableMsg_Check(PyObject* obj) {
    if (obj->ob_type == &pyEnableMsg_Type
        || PyType_IsSubtype(obj->ob_type, &pyEnableMsg_Type))
        return 1;
    return 0;
}

PyObject* pyEnableMsg_FromEnableMsg(class plEnableMsg* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyEnableMsg* py = PyObject_New(pyEnableMsg, &pyEnableMsg_Type);
    py->fThis = obj;
    py->fPyOwned = false;
    return (PyObject*)py;
}

};
