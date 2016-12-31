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

#include "pyMessageWithCallbacks.h"

#include <PRP/Message/plMessageWithCallbacks.h>
#include "pyMessage.h"
#include "PRP/pyCreatable.h"

extern "C" {

PY_PLASMA_NEW(MessageWithCallbacks, plMessageWithCallbacks)

static PyObject* pyMessageWithCallbacks_addCallback(pyMessageWithCallbacks* self, PyObject* args) {
    PyObject* msg;
    if (!(PyArg_ParseTuple(args, "O", &msg) && pyMessage_Check(msg))) {
        PyErr_SetString(PyExc_TypeError, "addCallback expects a plMessage");
        return NULL;
    }
    self->fThis->addCallback(((pyMessage*)msg)->fThis);
    ((pyMessage*)msg)->fPyOwned = false;
    Py_RETURN_NONE;
}

static PyObject* pyMessageWithCallbacks_clearCallbacks(pyMessageWithCallbacks* self) {
    self->fThis->clearCallbacks();
    Py_RETURN_NONE;
}

static PyObject* pyMessageWithCallbacks_delCallback(pyMessageWithCallbacks* self, PyObject* args) {
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delCallback expects an int");
        return NULL;
    }
    if (size_t(idx) >= self->fThis->getCallbacks().size()) {
        PyErr_SetNone(PyExc_IndexError);
        return NULL;
    }
    self->fThis->delCallback((size_t)idx);
    Py_RETURN_NONE;
}

static PyMethodDef pyMessageWithCallbacks_Methods[] = {
    { "addCallback", (PyCFunction)pyMessageWithCallbacks_addCallback, METH_VARARGS,
      "Params: key\n"
      "Adds a callback message" },
    { "clearCallbacks", (PyCFunction)pyMessageWithCallbacks_clearCallbacks, METH_NOARGS,
      "Removes all callback messages" },
    { "delCallback", (PyCFunction)pyMessageWithCallbacks_delCallback, METH_VARARGS,
      "Params: idx\n"
      "Removes a callback message" },
    { NULL, NULL, 0, NULL }
};

static PyObject* pyMessageWithCallbacks_getCallbacks(pyMessageWithCallbacks* self, void*) {
    const std::vector<plMessage*>& callbacks = self->fThis->getCallbacks();
    PyObject* tup = PyTuple_New(callbacks.size());
    for (size_t i = 0; i < callbacks.size(); ++i)
        PyTuple_SET_ITEM(tup, i, ICreate(callbacks[i]));
    return tup;
}

static int pyMessageWithCallbacks_setCallbacks(pyMessageWithCallbacks* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add callbacks, use addCallback");
    return -1;
}

static PyGetSetDef pyMessageWithCallbacks_GetSet[] = {
    { _pycs("callbacks"), (getter)pyMessageWithCallbacks_getCallbacks,
       (setter)pyMessageWithCallbacks_setCallbacks, NULL, NULL },
    PY_GETSET_TERMINATOR
};

PyTypeObject pyMessageWithCallbacks_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plMessageWithCallbacks", /* tp_name */
    sizeof(pyMessageWithCallbacks),      /* tp_basicsize */
    0,                                   /* tp_itemsize */

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
    "plMessageWithCallbacks wrapper",         /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyMessageWithCallbacks_Methods,     /* tp_methods */
    NULL,                               /* tp_members */
    pyMessageWithCallbacks_GetSet,      /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyMessageWithCallbacks_new,         /* tp_new */
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

PyObject* Init_pyMessageWithCallbacks_Type() {
    pyMessageWithCallbacks_Type.tp_base = &pyMessage_Type;
    if (PyType_Ready(&pyMessageWithCallbacks_Type) < 0)
        return NULL;

    Py_INCREF(&pyMessageWithCallbacks_Type);
    return (PyObject*)&pyMessageWithCallbacks_Type;
}

PY_PLASMA_IFC_METHODS(MessageWithCallbacks, plMessageWithCallbacks)

};
