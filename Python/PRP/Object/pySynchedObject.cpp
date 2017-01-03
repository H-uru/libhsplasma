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

extern "C" {

PY_PLASMA_NEW_MSG(SynchedObject, "plSynchedObject is abstract")

PY_METHOD_VA(SynchedObject, setExclude,
    "Params: state\n"
    "Add an SDL state to the Exclude list")
{
    const char* str;
    if (!PyArg_ParseTuple(args, "s", &str)) {
        PyErr_SetString(PyExc_TypeError, "setExclude expects a string");
        return NULL;
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
        return NULL;
    }
    self->fThis->setVolatile(str);
    Py_RETURN_NONE;
}

static PyObject* pySynchedObject_getExcludes(pySynchedObject* self, void*) {
    plSynchedObject* so = self->fThis;
    PyObject* list = PyList_New(so->getExcludes().size());
    for (size_t i=0; i<so->getExcludes().size(); i++)
        PyList_SET_ITEM(list, i, pyPlasma_convert(so->getExcludes()[i]));
    return list;
}

static PyObject* pySynchedObject_getVolatiles(pySynchedObject* self, void*) {
    plSynchedObject* so = self->fThis;
    PyObject* list = PyList_New(so->getVolatiles().size());
    for (size_t i=0; i<so->getVolatiles().size(); i++)
        PyList_SET_ITEM(list, i, pyPlasma_convert(so->getVolatiles()[i]));
    return list;
}

static int pySynchedObject_setExcludes(pySynchedObject* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->clearExcludes();
        return 0;
    } else if (PyList_Check(value)) {
        size_t count = PyList_Size(value);
        for (size_t i=0; i<count; i++) {
            if (!PyAnyStr_Check(PyList_GetItem(value, i))) {
                PyErr_SetString(PyExc_TypeError, "excludes should be a list of strings");
                return -1;
            }
            self->fThis->setExclude(PyStr_To_PlStr(PyList_GetItem(value, i)));
        }
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "excludes should be a list of strings");
        return -1;
    }
}

static int pySynchedObject_setVolatiles(pySynchedObject* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->clearVolatiles();
        return 0;
    } else if (PyList_Check(value)) {
        size_t count = PyList_Size(value);
        for (size_t i=0; i<count; i++) {
            if (!PyAnyStr_Check(PyList_GetItem(value, i))) {
                PyErr_SetString(PyExc_TypeError, "volatiles should be a list of strings");
                return -1;
            }
            self->fThis->setVolatile(PyStr_To_PlStr(PyList_GetItem(value, i)));
        }
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "volatiles should be a list of strings");
        return -1;
    }
}

static PyMethodDef pySynchedObject_Methods[] = {
    pySynchedObject_setExclude_method,
    pySynchedObject_setVolatile_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY(int, SynchedObject, synchFlags, getSynchFlags, setSynchFlags)

static PyGetSetDef pySynchedObject_GetSet[] = {
    pySynchedObject_synchFlags_getset,
    { _pycs("excludes"), (getter)pySynchedObject_getExcludes,
        (setter)pySynchedObject_setExcludes, _pycs("SDL Exclude States"), NULL },
    { _pycs("volatiles"), (getter)pySynchedObject_getVolatiles,
        (setter)pySynchedObject_setVolatiles, _pycs("SDL Volatile States"), NULL },
    PY_GETSET_TERMINATOR
};

PyTypeObject pySynchedObject_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plSynchedObject",       /* tp_name */
    sizeof(pySynchedObject),            /* tp_basicsize */
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
    "plSynchedObject wrapper",          /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pySynchedObject_Methods,            /* tp_methods */
    NULL,                               /* tp_members */
    pySynchedObject_GetSet,             /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pySynchedObject_new,                /* tp_new */
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

PyObject* Init_pySynchedObject_Type() {
    pySynchedObject_Type.tp_base = &pyKeyedObject_Type;
    if (PyType_Ready(&pySynchedObject_Type) < 0)
        return NULL;

    /* Flags */
    PyDict_SetItemString(pySynchedObject_Type.tp_dict, "kDontDirty",
                         PyInt_FromLong(plSynchedObject::kDontDirty));
    PyDict_SetItemString(pySynchedObject_Type.tp_dict, "kSendReliably",
                         PyInt_FromLong(plSynchedObject::kSendReliably));
    PyDict_SetItemString(pySynchedObject_Type.tp_dict, "kHasConstantNetGroup",
                         PyInt_FromLong(plSynchedObject::kHasConstantNetGroup));
    PyDict_SetItemString(pySynchedObject_Type.tp_dict, "kDontSynchGameMessages",
                         PyInt_FromLong(plSynchedObject::kDontSynchGameMessages));
    PyDict_SetItemString(pySynchedObject_Type.tp_dict, "kExcludePersistentState",
                         PyInt_FromLong(plSynchedObject::kExcludePersistentState));
    PyDict_SetItemString(pySynchedObject_Type.tp_dict, "kExcludeAllPersistentState",
                         PyInt_FromLong(plSynchedObject::kExcludeAllPersistentState));
    PyDict_SetItemString(pySynchedObject_Type.tp_dict, "kLocalOnly",
                         PyInt_FromLong(plSynchedObject::kLocalOnly));
    PyDict_SetItemString(pySynchedObject_Type.tp_dict, "kHasVolatileState",
                         PyInt_FromLong(plSynchedObject::kHasVolatileState));
    PyDict_SetItemString(pySynchedObject_Type.tp_dict, "kAllStateIsVolatile",
                         PyInt_FromLong(plSynchedObject::kAllStateIsVolatile));

    /* SDLSendFlags -- stored in some messages */
    PyDict_SetItemString(pySynchedObject_Type.tp_dict, "kBCastToClients",
                         PyInt_FromLong(plSynchedObject::kBCastToClients));
    PyDict_SetItemString(pySynchedObject_Type.tp_dict, "kForceFullSend",
                         PyInt_FromLong(plSynchedObject::kForceFullSend));
    PyDict_SetItemString(pySynchedObject_Type.tp_dict, "kSkipLocalOwnershipCheck",
                         PyInt_FromLong(plSynchedObject::kSkipLocalOwnershipCheck));
    PyDict_SetItemString(pySynchedObject_Type.tp_dict, "kSendImmediately",
                         PyInt_FromLong(plSynchedObject::kSendImmediately));
    PyDict_SetItemString(pySynchedObject_Type.tp_dict, "kDontPersistOnServer",
                         PyInt_FromLong(plSynchedObject::kDontPersistOnServer));
    PyDict_SetItemString(pySynchedObject_Type.tp_dict, "kUseRelevanceRegions",
                         PyInt_FromLong(plSynchedObject::kUseRelevanceRegions));
    PyDict_SetItemString(pySynchedObject_Type.tp_dict, "kNewState",
                         PyInt_FromLong(plSynchedObject::kNewState));
    PyDict_SetItemString(pySynchedObject_Type.tp_dict, "kIsAvatarState",
                         PyInt_FromLong(plSynchedObject::kIsAvatarState));

    Py_INCREF(&pySynchedObject_Type);
    return (PyObject*)&pySynchedObject_Type;
}

PY_PLASMA_IFC_METHODS(SynchedObject, plSynchedObject)

}
