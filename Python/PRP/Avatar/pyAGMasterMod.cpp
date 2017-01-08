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

PY_PLASMA_NEW(AGMasterMod, plAGMasterMod)

PY_METHOD_VA(AGMasterMod, addPrivateAnim,
    "Params: key\n"
    "Adds an animation key")
{
    PyObject* key;
    if (!(PyArg_ParseTuple(args, "O", &key) && pyKey_Check(key))) {
        PyErr_SetString(PyExc_TypeError, "addPrivateAnim expects a plKey");
        return NULL;
    }
    self->fThis->addPrivateAnim(*((pyKey*)key)->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(AGMasterMod, clearPrivateAnims, "Removes all animation keys") {
    self->fThis->clearPrivateAnims();
    Py_RETURN_NONE;
}

PY_METHOD_VA(AGMasterMod, delPrivateAnim,
    "Params: idx\n"
    "Removes an animation key")
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delPrivateAnim expects an int");
        return NULL;
    }
    self->fThis->delPrivateAnim((size_t)idx);
    Py_RETURN_NONE;
}

PY_METHOD_VA(AGMasterMod, addEoaKey,
    "Params: key\n"
    "Adds an EoA key")
{
    PyObject* key;
    if (!(PyArg_ParseTuple(args, "O", &key) && pyKey_Check(key))) {
        PyErr_SetString(PyExc_TypeError, "addEoaKey expects a plKey");
        return NULL;
    }
    self->fThis->addEoaKey(*((pyKey*)key)->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(AGMasterMod, clearEoaKeys, "Removes all EoA keys") {
    self->fThis->clearEoaKeys();
    Py_RETURN_NONE;
}

PY_METHOD_VA(AGMasterMod, delEoaKey,
    "Params: idx\n"
    "Removes an EoA key")
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delEoaKey expects an int");
        return NULL;
    }
    self->fThis->delEoaKey((size_t)idx);
    Py_RETURN_NONE;
}

static PyMethodDef pyAGMasterMod_Methods[] = {
    pyAGMasterMod_addPrivateAnim_method,
    pyAGMasterMod_clearPrivateAnims_method,
    pyAGMasterMod_delPrivateAnim_method,
    pyAGMasterMod_addEoaKey_method,
    pyAGMasterMod_clearEoaKeys_method,
    pyAGMasterMod_delEoaKey_method,
    PY_METHOD_TERMINATOR
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

static int pyAGMasterMod_setPrivateAnims(pyAGMasterMod* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add privateAnims, use addPrivateAnim()");
    return -1;
}

static int pyAGMasterMod_setEoaKeys(pyAGMasterMod* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add eoaKeys, use addEoaKey()");
    return -1;
}

PY_PROPERTY(plString, AGMasterMod, groupName, getGroupName, setGroupName)
PY_PROPERTY(bool, AGMasterMod, isGrouped, getIsGrouped, setIsGrouped)
PY_PROPERTY(bool, AGMasterMod, isGroupMaster, getIsGroupMaster, setIsGroupMaster)
PY_PROPERTY(plKey, AGMasterMod, msgForwarder, getMsgForwarder, setMsgForwarder)

static PyGetSetDef pyAGMasterMod_GetSet[] = {
    { _pycs("privateAnims"), (getter)pyAGMasterMod_getPrivateAnims, (setter)pyAGMasterMod_setPrivateAnims, NULL, NULL },
    { _pycs("eoaKeys"), (getter)pyAGMasterMod_getEoaKeys, (setter)pyAGMasterMod_setEoaKeys, NULL, NULL },
    pyAGMasterMod_groupName_getset,
    pyAGMasterMod_isGrouped_getset,
    pyAGMasterMod_isGroupMaster_getset,
    pyAGMasterMod_msgForwarder_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(AGMasterMod, plAGMasterMod, "plAGMasterMod wrapper")

PY_PLASMA_TYPE_INIT(AGMasterMod) {
    pyAGMasterMod_Type.tp_new = pyAGMasterMod_new;
    pyAGMasterMod_Type.tp_methods = pyAGMasterMod_Methods;
    pyAGMasterMod_Type.tp_getset = pyAGMasterMod_GetSet;
    pyAGMasterMod_Type.tp_base = &pySingleModifier_Type;
    if (PyType_CheckAndReady(&pyAGMasterMod_Type) < 0)
        return NULL;

    Py_INCREF(&pyAGMasterMod_Type);
    return (PyObject*)&pyAGMasterMod_Type;
}

PY_PLASMA_IFC_METHODS(AGMasterMod, plAGMasterMod)

};
