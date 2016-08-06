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

#include "pyResponderMsg.h"

#include <PRP/Message/plResponderMsg.h>
#include "PRP/KeyedObject/pyKey.h"

extern "C" {

static PyObject* pyOneShotMsg_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyOneShotMsg* self = (pyOneShotMsg*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plOneShotMsg();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyOneShotMsg_clearCallbacks(pyOneShotMsg* self) {
    self->fThis->getCallbacks().clearCallbacks();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyOneShotMsg_addCallback(pyOneShotMsg* self, PyObject* args) {
    char* marker;
    PyObject* key;
    short user;
    if (!PyArg_ParseTuple(args, "esOh", "utf8", &marker, &key, &user) || !pyKey_Check(key)) {
        PyErr_SetString(PyExc_TypeError, "addCallback expects string, plKey, int");
        return NULL;
    }
    self->fThis->getCallbacks().addCallback(marker, *((pyKey*)key)->fThis, user);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyOneShotMsg_delCallback(pyOneShotMsg* self, PyObject* args) {
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delCallback expects an int");
        return NULL;
    }
    plOneShotCallbacks& cbs = self->fThis->getCallbacks();
    if (size_t(idx) >= cbs.getNumCallbacks()) {
        PyErr_SetNone(PyExc_IndexError);
        return NULL;
    }
    cbs.delCallback(idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef pyOneShotMsg_Methods[] = {
    { "clearCallbacks", (PyCFunction)pyOneShotMsg_clearCallbacks, METH_NOARGS,
      "Remove all callbacks" },
    { "addCallback", (PyCFunction)pyOneShotMsg_addCallback, METH_VARARGS,
      "Params: marker, receiver, user\n"
      "Add a callback" },
    { "delCallback", (PyCFunction)pyOneShotMsg_delCallback, METH_VARARGS,
      "Params: idx\n"
      "Remove a callback" },
    { NULL, NULL, 0, NULL }
};

static PyObject* pyOneShotMsg_getCallbacks(pyOneShotMsg* self, void*) {
    const plOneShotCallbacks& cbs = self->fThis->getCallbacks();
    PyObject* tup = PyTuple_New(cbs.getNumCallbacks());
    for (size_t i = 0; i < cbs.getNumCallbacks(); ++i) {
        const auto& cb = cbs.getCallbacks()[i];
        PyObject* value = Py_BuildValue("OOh", PlStr_To_PyStr(cb.fMarker), pyKey_FromKey(cb.fReceiver), cb.fUser);
        PyTuple_SET_ITEM(tup, i, value);
    }
    return tup;
}

static PyGetSetDef pyOneShotMsg_GetSet[] = {
    { _pycs("callbacks"), (getter)pyOneShotMsg_getCallbacks, NULL, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyOneShotMsg_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plOneShotMsg",          /* tp_name */
    sizeof(pyOneShotMsg),               /* tp_basicsize */
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
    "plOneShotMsg wrapper",                   /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyOneShotMsg_Methods,               /* tp_methods */
    NULL,                               /* tp_members */
    pyOneShotMsg_GetSet,                /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyOneShotMsg_new,                   /* tp_new */
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

PyObject* Init_pyOneShotMsg_Type() {
    pyOneShotMsg_Type.tp_base = &pyResponderMsg_Type;
    if (PyType_Ready(&pyOneShotMsg_Type) < 0)
        return NULL;

    Py_INCREF(&pyOneShotMsg_Type);
    return (PyObject*)&pyOneShotMsg_Type;
}

int pyOneShotMsg_Check(PyObject* obj) {
    if (obj->ob_type == &pyOneShotMsg_Type
        || PyType_IsSubtype(obj->ob_type, &pyOneShotMsg_Type))
        return 1;
    return 0;
}

PyObject* pyOneShotMsg_FromOneShotMsg(class plOneShotMsg* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyOneShotMsg* pyobj = PyObject_New(pyOneShotMsg, &pyOneShotMsg_Type);
    pyobj->fThis = obj;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
