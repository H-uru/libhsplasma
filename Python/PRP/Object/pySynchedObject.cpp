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

#include "pySynchedObject.h"

#include <PRP/Object/plSynchedObject.h>
#include "PRP/pyCreatable.h"
#include "PRP/KeyedObject/pyKeyedObject.h"

PY_PLASMA_NEW_MSG(SynchedObject, "plSynchedObject is abstract")

PY_METHOD_VA(SynchedObject, setExclude,
    "Params: state\n"
    "Add an SDL state to the Exclude list")
{
    const char* str;
    if (!PyArg_ParseTuple(args, "s", &str)) {
        PyErr_SetString(PyExc_TypeError, "setExclude expects a string");
        return nullptr;
    }
    self->fThis->setExclude(str);
    Py_RETURN_NONE;
}

PY_METHOD_VA(SynchedObject, setVolatile,
    "Params: state\n"
    "Add an SDL state to the Volatile list")
{
    const char* str;
    if (!PyArg_ParseTuple(args, "s", &str)) {
        PyErr_SetString(PyExc_TypeError, "setVolatile expects a string");
        return nullptr;
    }
    self->fThis->setVolatile(str);
    Py_RETURN_NONE;
}

static PyMethodDef pySynchedObject_Methods[] = {
    pySynchedObject_setExclude_method,
    pySynchedObject_setVolatile_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(SynchedObject, excludes)
{
    plSynchedObject* so = self->fThis;
    PyObject* list = PyTuple_New(so->getExcludes().size());
    for (size_t i=0; i<so->getExcludes().size(); i++)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(so->getExcludes()[i]));
    return list;
}

PY_GETSET_SETTER_DECL(SynchedObject, excludes)
{
    PY_PROPERTY_CHECK_NULL(excludes)
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "excludes should be a sequence of strings");
        return -1;
    }
    Py_ssize_t count = seq.size();
    for (Py_ssize_t i=0; i<count; i++) {
        PyObject* item = seq.get(i);
        if (!pyPlasma_check<ST::string>(item)) {
            PyErr_SetString(PyExc_TypeError, "excludes should be a list of strings");
            return -1;
        }
        self->fThis->setExclude(pyPlasma_get<ST::string>(item));
    }
    return 0;
}

PY_PROPERTY_GETSET_DECL(SynchedObject, excludes)

PY_GETSET_GETTER_DECL(SynchedObject, volatiles)
{
    plSynchedObject* so = self->fThis;
    PyObject* list = PyTuple_New(so->getVolatiles().size());
    for (size_t i=0; i<so->getVolatiles().size(); i++)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(so->getVolatiles()[i]));
    return list;
}

PY_GETSET_SETTER_DECL(SynchedObject, volatiles)
{
    PY_PROPERTY_CHECK_NULL(volatiles)
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "volatiles should be a list of strings");
        return -1;
    }
    Py_ssize_t count = seq.size();
    for (Py_ssize_t i=0; i<count; i++) {
        PyObject* item = seq.get(i);
        if (!pyPlasma_check<ST::string>(item)) {
            PyErr_SetString(PyExc_TypeError, "volatiles should be a list of strings");
            return -1;
        }
        self->fThis->setVolatile(pyPlasma_get<ST::string>(item));
    }
    return 0;
}

PY_PROPERTY_GETSET_DECL(SynchedObject, volatiles)

PY_PROPERTY(int, SynchedObject, synchFlags, getSynchFlags, setSynchFlags)

static PyGetSetDef pySynchedObject_GetSet[] = {
    pySynchedObject_synchFlags_getset,
    pySynchedObject_excludes_getset,
    pySynchedObject_volatiles_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(SynchedObject, plSynchedObject, "plSynchedObject wrapper")

PY_PLASMA_TYPE_INIT(SynchedObject)
{
    pySynchedObject_Type.tp_new = pySynchedObject_new;
    pySynchedObject_Type.tp_methods = pySynchedObject_Methods;
    pySynchedObject_Type.tp_getset = pySynchedObject_GetSet;
    pySynchedObject_Type.tp_base = &pyKeyedObject_Type;
    if (PyType_CheckAndReady(&pySynchedObject_Type) < 0)
        return nullptr;

    /* Flags */
    PY_TYPE_ADD_CONST(SynchedObject, "kDontDirty",
                      plSynchedObject::kDontDirty);
    PY_TYPE_ADD_CONST(SynchedObject, "kSendReliably",
                      plSynchedObject::kSendReliably);
    PY_TYPE_ADD_CONST(SynchedObject, "kHasConstantNetGroup",
                      plSynchedObject::kHasConstantNetGroup);
    PY_TYPE_ADD_CONST(SynchedObject, "kDontSynchGameMessages",
                      plSynchedObject::kDontSynchGameMessages);
    PY_TYPE_ADD_CONST(SynchedObject, "kExcludePersistentState",
                      plSynchedObject::kExcludePersistentState);
    PY_TYPE_ADD_CONST(SynchedObject, "kExcludeAllPersistentState",
                      plSynchedObject::kExcludeAllPersistentState);
    PY_TYPE_ADD_CONST(SynchedObject, "kLocalOnly",
                      plSynchedObject::kLocalOnly);
    PY_TYPE_ADD_CONST(SynchedObject, "kHasVolatileState",
                      plSynchedObject::kHasVolatileState);
    PY_TYPE_ADD_CONST(SynchedObject, "kAllStateIsVolatile",
                      plSynchedObject::kAllStateIsVolatile);

    /* SDLSendFlags -- stored in some messages */
    PY_TYPE_ADD_CONST(SynchedObject, "kBCastToClients",
                      plSynchedObject::kBCastToClients);
    PY_TYPE_ADD_CONST(SynchedObject, "kForceFullSend",
                      plSynchedObject::kForceFullSend);
    PY_TYPE_ADD_CONST(SynchedObject, "kSkipLocalOwnershipCheck",
                      plSynchedObject::kSkipLocalOwnershipCheck);
    PY_TYPE_ADD_CONST(SynchedObject, "kSendImmediately",
                      plSynchedObject::kSendImmediately);
    PY_TYPE_ADD_CONST(SynchedObject, "kDontPersistOnServer",
                      plSynchedObject::kDontPersistOnServer);
    PY_TYPE_ADD_CONST(SynchedObject, "kUseRelevanceRegions",
                      plSynchedObject::kUseRelevanceRegions);
    PY_TYPE_ADD_CONST(SynchedObject, "kNewState",
                      plSynchedObject::kNewState);
    PY_TYPE_ADD_CONST(SynchedObject, "kIsAvatarState",
                      plSynchedObject::kIsAvatarState);

    Py_INCREF(&pySynchedObject_Type);
    return (PyObject*)&pySynchedObject_Type;
}

PY_PLASMA_IFC_METHODS(SynchedObject, plSynchedObject)
