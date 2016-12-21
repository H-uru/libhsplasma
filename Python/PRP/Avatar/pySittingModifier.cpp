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

#include "pySittingModifier.h"

#include <PRP/Avatar/plSittingModifier.h>
#include "PRP/Modifier/pyModifier.h"
#include "PRP/KeyedObject/pyKey.h"

extern "C" {

static PyObject* pySittingModifier_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pySittingModifier* self = (pySittingModifier*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plSittingModifier();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pySittingModifier_addNotifyKey(pySittingModifier* self, PyObject* args) {
    PyObject* key;
    if (!(PyArg_ParseTuple(args, "O", &key) && pyKey_Check(key))) {
        PyErr_SetString(PyExc_TypeError, "addNotifyKey expects a plKey");
        return NULL;
    }
    self->fThis->addNotifyKey(*((pyKey*)key)->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pySittingModifier_clearNotifyKeys(pySittingModifier* self) {
    self->fThis->clearNotifyKeys();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pySittingModifier_delNotifyKey(pySittingModifier* self, PyObject* args) {
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delNotifyKey expects an int");
        return NULL;
    }
    self->fThis->delNotifyKey((size_t)idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef pySittingModifier_Methods[] = {
    { "addNotifyKey", (PyCFunction)pySittingModifier_addNotifyKey, METH_VARARGS,
      "Params: key\n"
      "Adds a LogicMod notify key" },
    { "clearNotifyKeys", (PyCFunction)pySittingModifier_clearNotifyKeys, METH_NOARGS,
      "Removes all LogicMod notify keys" },
    { "delNotifyKey", (PyCFunction)pySittingModifier_delNotifyKey, METH_VARARGS,
      "Params: idx\n"
      "Removes a LogicMod notify key" },
    { NULL, NULL, 0, NULL }
};

static PyObject* pySittingModifier_getMiscFlags(pySittingModifier* self, void*) {
    return PyInt_FromLong(self->fThis->getMiscFlags());
}

static PyObject* pySittingModifier_getNotifyKeys(pySittingModifier* self, void*) {
    PyObject* keys = PyTuple_New(self->fThis->getNotifyKeys().size());
    for (size_t i = 0; i < self->fThis->getNotifyKeys().size(); ++i)
        PyTuple_SET_ITEM(keys, i, pyKey_FromKey(self->fThis->getNotifyKeys()[i]));
    return keys;
}

static int pySittingModifier_setMiscFlags(pySittingModifier* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "miscFlags should be an int");
        return -1;
    }
    self->fThis->setMiscFlags((uint8_t)PyInt_AsLong(value));
    return 0;
}

static int pySittingModifier_setNotifyKeys(pySittingModifier* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add notifyKeys, use addNotifyKey()");
    return -1;
}

static PyGetSetDef pySittingModifier_GetSet[] = {
    { _pycs("miscFlags"), (getter)pySittingModifier_getMiscFlags, (setter)pySittingModifier_setMiscFlags, NULL, NULL },
    { _pycs("notifyKeys"), (getter)pySittingModifier_getNotifyKeys, (setter)pySittingModifier_setNotifyKeys, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pySittingModifier_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plSittingModifier",     /* tp_name */
    sizeof(pySittingModifier),          /* tp_basicsize */
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
    "plSittingModifier wrapper",        /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pySittingModifier_Methods,          /* tp_methods */
    NULL,                               /* tp_members */
    pySittingModifier_GetSet,           /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pySittingModifier_new,              /* tp_new */
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

PyObject* Init_pySittingModifier_Type() {
    pySittingModifier_Type.tp_base = &pySingleModifier_Type;
    if (PyType_Ready(&pySittingModifier_Type) < 0)
        return NULL;

    PyDict_SetItemString(pySittingModifier_Type.tp_dict, "kApproachFront",
                         PyInt_FromLong(plSittingModifier::kApproachFront));
    PyDict_SetItemString(pySittingModifier_Type.tp_dict, "kApproachLeft",
                         PyInt_FromLong(plSittingModifier::kApproachLeft));
    PyDict_SetItemString(pySittingModifier_Type.tp_dict, "kApproachRight",
                         PyInt_FromLong(plSittingModifier::kApproachRight));
    PyDict_SetItemString(pySittingModifier_Type.tp_dict, "kApproachRear",
                         PyInt_FromLong(plSittingModifier::kApproachRear));
    PyDict_SetItemString(pySittingModifier_Type.tp_dict, "kApproachMask",
                         PyInt_FromLong(plSittingModifier::kApproachMask));
    PyDict_SetItemString(pySittingModifier_Type.tp_dict, "kDisableForward",
                         PyInt_FromLong(plSittingModifier::kDisableForward));

    Py_INCREF(&pySittingModifier_Type);
    return (PyObject*)&pySittingModifier_Type;
}

PY_PLASMA_IFC_METHODS(SittingModifier, plSittingModifier)

};
