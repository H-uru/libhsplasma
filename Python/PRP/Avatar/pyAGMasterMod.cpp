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

#include "pyAGMasterMod.h"

#include <PRP/Avatar/plAGMasterMod.h>
#include "PRP/Modifier/pyModifier.h"
#include "PRP/KeyedObject/pyKey.h"

extern "C" {

static PyObject* pyAGMasterMod_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyAGMasterMod* self = (pyAGMasterMod*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plAGMasterMod();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyAGMasterMod_addPrivateAnim(pyAGMasterMod* self, PyObject* args) {
    PyObject* key;
    if (!(PyArg_ParseTuple(args, "O", &key) && pyKey_Check(key))) {
        PyErr_SetString(PyExc_TypeError, "addPrivateAnim expects a plKey");
        return NULL;
    }
    self->fThis->addPrivateAnim(*((pyKey*)key)->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyAGMasterMod_clearPrivateAnims(pyAGMasterMod* self) {
    self->fThis->clearPrivateAnims();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyAGMasterMod_delPrivateAnim(pyAGMasterMod* self, PyObject* args) {
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delPrivateAnim expects an int");
        return NULL;
    }
    self->fThis->delPrivateAnim((size_t)idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyAGMasterMod_addEoaKey(pyAGMasterMod* self, PyObject* args) {
    PyObject* key;
    if (!(PyArg_ParseTuple(args, "O", &key) && pyKey_Check(key))) {
        PyErr_SetString(PyExc_TypeError, "addEoaKey expects a plKey");
        return NULL;
    }
    self->fThis->addEoaKey(*((pyKey*)key)->fThis);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyAGMasterMod_clearEoaKeys(pyAGMasterMod* self) {
    self->fThis->clearEoaKeys();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyAGMasterMod_delEoaKey(pyAGMasterMod* self, PyObject* args) {
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delEoaKey expects an int");
        return NULL;
    }
    self->fThis->delEoaKey((size_t)idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef pyAGMasterMod_Methods[] = {
    { "addPrivateAnim", (PyCFunction)pyAGMasterMod_addPrivateAnim, METH_VARARGS,
      "Params: key\n"
      "Adds an animation key" },
    { "clearPrivateAnims", (PyCFunction)pyAGMasterMod_clearPrivateAnims, METH_NOARGS,
      "Removes all animation keys" },
    { "delPrivateAnim", (PyCFunction)pyAGMasterMod_delPrivateAnim, METH_VARARGS,
      "Params: idx\n"
      "Removes an animation key" },
    { "addEoaKey", (PyCFunction)pyAGMasterMod_addEoaKey, METH_VARARGS,
      "Params: key\n"
      "Adds an EoA key" },
    { "clearEoaKeys", (PyCFunction)pyAGMasterMod_clearEoaKeys, METH_NOARGS,
      "Removes all EoA keys" },
    { "delEoaKey", (PyCFunction)pyAGMasterMod_delEoaKey, METH_VARARGS,
      "Params: idx\n"
      "Removes an EoA key" },
    { NULL, NULL, 0, NULL }
};

static PyObject* pyAGMasterMod_getPrivateAnims(pyAGMasterMod* self, void*) {
    const std::vector<plKey>& anims = self->fThis->getPrivateAnims();
    PyObject* tup = PyTuple_New(anims.size());
    for (size_t i = 0; i < anims.size(); ++i)
        PyTuple_SET_ITEM(tup, i, pyKey_FromKey(anims[i]));
    return tup;
}

static PyObject* pyAGMasterMod_getEoaKeys(pyAGMasterMod* self, void*) {
    const std::vector<plKey>& keys = self->fThis->getEoaKeys();
    PyObject* tup = PyTuple_New(keys.size());
    for (size_t i = 0; i < keys.size(); ++i)
        PyTuple_SET_ITEM(tup, i, pyKey_FromKey(keys[i]));
    return tup;
}

static PyObject* pyAGMasterMod_getGroupName(pyAGMasterMod* self, void*) {
    return PlStr_To_PyStr(self->fThis->getGroupName());
}

static PyObject* pyAGMasterMod_getIsGrouped(pyAGMasterMod* self, void*) {
    return PyBool_FromLong(self->fThis->getIsGrouped() ? 1 : 0);
}

static PyObject* pyAGMasterMod_getIsGroupMaster(pyAGMasterMod* self, void*) {
    return PyBool_FromLong(self->fThis->getIsGroupMaster() ? 1 : 0);
}

static PyObject* pyAGMasterMod_getMsgForwarder(pyAGMasterMod* self, void*) {
    return pyKey_FromKey(self->fThis->getMsgForwarder());
}

static int pyAGMasterMod_setPrivateAnims(pyAGMasterMod* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add privateAnims, use addPrivateAnim()");
    return -1;
}

static int pyAGMasterMod_setEoaKeys(pyAGMasterMod* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add eoaKeys, use addEoaKey()");
    return -1;
}

static int pyAGMasterMod_setGroupName(pyAGMasterMod* self, PyObject* value, void*) {
    if (value == NULL || !PyAnyStr_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "groupName should be a string");
        return -1;
    }
    self->fThis->setGroupName(PyStr_To_PlStr(value));
    return 0;
}

static int pyAGMasterMod_setIsGrouped(pyAGMasterMod* self, PyObject* value, void*) {
    if (value == NULL || !PyBool_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "isGrouped should be a boolean");
        return -1;
    }
    self->fThis->setIsGrouped(PyInt_AsLong(value) != 0);
    return 0;
}

static int pyAGMasterMod_setIsGroupMaster(pyAGMasterMod* self, PyObject* value, void*) {
    if (value == NULL || !PyBool_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "isGroupMaster should be a boolean");
        return -1;
    }
    self->fThis->setIsGroupMaster(PyInt_AsLong(value) != 0);
    return 0;
}

static int pyAGMasterMod_setMsgForwarder(pyAGMasterMod* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setMsgForwarder(plKey());
        return 0;
    } else if (pyKey_Check(value)) {
        self->fThis->setMsgForwarder(*((pyKey*)value)->fThis);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "msgForwarder should be a plKey");
        return -1;
    }
}

static PyGetSetDef pyAGMasterMod_GetSet[] = {
    { _pycs("privateAnims"), (getter)pyAGMasterMod_getPrivateAnims, (setter)pyAGMasterMod_setPrivateAnims, NULL, NULL },
    { _pycs("eoaKeys"), (getter)pyAGMasterMod_getEoaKeys, (setter)pyAGMasterMod_setEoaKeys, NULL, NULL },
    { _pycs("groupName"), (getter)pyAGMasterMod_getGroupName, (setter)pyAGMasterMod_setGroupName, NULL, NULL },
    { _pycs("isGrouped"), (getter)pyAGMasterMod_getIsGrouped, (setter)pyAGMasterMod_setIsGrouped, NULL, NULL },
    { _pycs("isGroupMaster"), (getter)pyAGMasterMod_getIsGroupMaster, (setter)pyAGMasterMod_setIsGroupMaster, NULL, NULL },
    { _pycs("msgForwarder"), (getter)pyAGMasterMod_getMsgForwarder, (setter)pyAGMasterMod_setMsgForwarder, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyAGMasterMod_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plAGMasterMod",         /* tp_name */
    sizeof(pyAGMasterMod),              /* tp_basicsize */
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
    "plAGMasterMod wrapper",                  /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyAGMasterMod_Methods,              /* tp_methods */
    NULL,                               /* tp_members */
    pyAGMasterMod_GetSet,               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyAGMasterMod_new,                  /* tp_new */
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

PyObject* Init_pyAGMasterMod_Type() {
    pyAGMasterMod_Type.tp_base = &pySingleModifier_Type;
    if (PyType_Ready(&pyAGMasterMod_Type) < 0)
        return NULL;

    Py_INCREF(&pyAGMasterMod_Type);
    return (PyObject*)&pyAGMasterMod_Type;
}

PY_PLASMA_IFC_METHODS(AGMasterMod, plAGMasterMod)

};
