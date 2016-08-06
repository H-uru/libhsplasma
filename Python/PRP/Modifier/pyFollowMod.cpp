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

#include "pyFollowMod.h"

#include <PRP/Modifier/plFollowMod.h>
#include "PRP/Modifier/pyModifier.h"
#include "PRP/KeyedObject/pyKey.h"

extern "C" {

static PyObject* pyFollowMod_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyFollowMod* self = (pyFollowMod*) type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plFollowMod();
        self->fPyOwned = true;
    }
    return (PyObject*) self;
}

static PyObject* pyFollowMod_getLeaderType(pyFollowMod* self, void*) {
    return PyInt_FromLong(self->fThis->getLeaderType());
}

static PyObject* pyFollowMod_getMode(pyFollowMod* self, void*) {
    return PyInt_FromLong(self->fThis->getMode());
}

static PyObject* pyFollowMod_getLeader(pyFollowMod* self, void*) {
    return pyKey_FromKey(self->fThis->getLeader());
}

static int pyFollowMod_setLeaderType(pyFollowMod* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "leaderType should be an int");
        return -1;
    }
    self->fThis->setLeaderType(static_cast<plFollowMod::FollowLeaderType>(PyInt_AsLong(value)));
    return 0;
}

static int pyFollowMod_setMode(pyFollowMod* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "mode should be an int");
        return -1;
    }
    self->fThis->setMode(PyInt_AsLong(value));
    return 0;
}

static int pyFollowMod_setLeader(pyFollowMod* self, PyObject* value, void*) {
    if (value == NULL || !pyKey_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "leader should be a plKey");
        return -1;
    }
    self->fThis->setLeader(*((pyKey*) value)->fThis);
    return 0;
}

static PyGetSetDef pyFollowMod_GetSet [] = {
    { _pycs("leaderType"), (getter) pyFollowMod_getLeaderType,
        (setter) pyFollowMod_setLeaderType, NULL, NULL },
    { _pycs("mode"), (getter) pyFollowMod_getMode,
        (setter) pyFollowMod_setMode, NULL, NULL },
    { _pycs("leader"), (getter) pyFollowMod_getLeader,
        (setter) pyFollowMod_setLeader, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyFollowMod_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plFollowMod",           /* tp_name */
    sizeof(pyFollowMod),                /* tp_basicsize */
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
    "plFollowMod wrapper",              /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyFollowMod_GetSet,                 /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyFollowMod_new,                    /* tp_new */
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

PyObject* Init_pyFollowMod_Type() {
    pyFollowMod_Type.tp_base = &pySingleModifier_Type;
    if (PyType_Ready(&pyFollowMod_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyFollowMod_Type.tp_dict, "kFollowPlayer",
        PyInt_FromLong(plFollowMod::kFollowPlayer));
    PyDict_SetItemString(pyFollowMod_Type.tp_dict, "kFollowObject",
        PyInt_FromLong(plFollowMod::kFollowObject));
    PyDict_SetItemString(pyFollowMod_Type.tp_dict, "kFollowCamera",
        PyInt_FromLong(plFollowMod::kFollowCamera));
    PyDict_SetItemString(pyFollowMod_Type.tp_dict, "kFollowListener",
        PyInt_FromLong(plFollowMod::kFollowListener));

    PyDict_SetItemString(pyFollowMod_Type.tp_dict, "kPositionX",
        PyInt_FromLong(plFollowMod::kPositionX));
    PyDict_SetItemString(pyFollowMod_Type.tp_dict, "kPositionY",
        PyInt_FromLong(plFollowMod::kPositionY));
    PyDict_SetItemString(pyFollowMod_Type.tp_dict, "kPositionZ",
        PyInt_FromLong(plFollowMod::kPositionZ));
    PyDict_SetItemString(pyFollowMod_Type.tp_dict, "kPosition",
        PyInt_FromLong(plFollowMod::kPosition));
    PyDict_SetItemString(pyFollowMod_Type.tp_dict, "kRotate",
        PyInt_FromLong(plFollowMod::kRotate));
    PyDict_SetItemString(pyFollowMod_Type.tp_dict, "kFullTransform",
        PyInt_FromLong(plFollowMod::kFullTransform));

    Py_INCREF(&pyFollowMod_Type);
    return (PyObject*) &pyFollowMod_Type;
}

int pyFollowMod_Check(PyObject* obj) {
    if (obj->ob_type == &pyFollowMod_Type
        || PyType_IsSubtype(obj->ob_type, &pyFollowMod_Type))
        return 1;
    return 0;
}

PyObject* pyFollowMod_FromFollowMod(class plFollowMod* mod) {
    if (mod == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyFollowMod* pymod = PyObject_New(pyFollowMod, &pyFollowMod_Type);
    pymod->fThis = mod;
    pymod->fPyOwned = false;
    return (PyObject*) pymod;
}

}
