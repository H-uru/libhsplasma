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

#include "pyOneShotMod.h"

#include <PRP/Modifier/plOneShotMod.h>
#include "pyModifier.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyOneShotMod_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyOneShotMod* self = (pyOneShotMod*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plOneShotMod();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyOneShotMod_getAnimName(pyOneShotMod* self, void*) {
    return PlStr_To_PyStr(self->fThis->getAnimName());
}

static PyObject* pyOneShotMod_getDrivable(pyOneShotMod* self, void*) {
    return PyBool_FromLong(self->fThis->isDrivable() ? 1 : 0);
}

static PyObject* pyOneShotMod_getReversable(pyOneShotMod* self, void*) {
    return PyBool_FromLong(self->fThis->isReversable() ? 1 : 0);
}

static PyObject* pyOneShotMod_getSmartSeek(pyOneShotMod* self, void*) {
    return PyBool_FromLong(self->fThis->getSmartSeek() ? 1 : 0);
}

static PyObject* pyOneShotMod_getNoSeek(pyOneShotMod* self, void*) {
    return PyBool_FromLong(self->fThis->getNoSeek() ? 1 : 0);
}

static PyObject* pyOneShotMod_getSeekDuration(pyOneShotMod* self, void*) {
    return PyFloat_FromDouble(self->fThis->getSeekDuration());
}

static int pyOneShotMod_setAnimName(pyOneShotMod* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setAnimName("");
        return 0;
    }
    if (!PyAnyStr_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "animName should be a string");
        return -1;
    }
    self->fThis->setAnimName(PyStr_To_PlStr(value));
    return 0;
}

static int pyOneShotMod_setDrivable(pyOneShotMod* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "drivable should be a bool");
        return -1;
    }
    self->fThis->setDrivable(PyInt_AsLong(value) != 0);
    return 0;
}

static int pyOneShotMod_setReversable(pyOneShotMod* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "reversable should be a bool");
        return -1;
    }
    self->fThis->setReversable(PyInt_AsLong(value) != 0);
    return 0;
}

static int pyOneShotMod_setSmartSeek(pyOneShotMod* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "smartSeek should be a bool");
        return -1;
    }
    self->fThis->setSmartSeek(PyInt_AsLong(value) != 0);
    return 0;
}

static int pyOneShotMod_setNoSeek(pyOneShotMod* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "noSeek should be a bool");
        return -1;
    }
    self->fThis->setNoSeek(PyInt_AsLong(value) != 0);
    return 0;
}

static int pyOneShotMod_setSeekDuration(pyOneShotMod* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "seekDuration should be a bool");
        return -1;
    }
    self->fThis->setSeekDuration(PyFloat_AsDouble(value));
    return 0;
}

static PyMethodDef pyOneShotMod_Methods[] = {
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyOneShotMod_GetSet[] = {
    { _pycs("animName"), (getter)pyOneShotMod_getAnimName,
        (setter)pyOneShotMod_setAnimName, NULL, NULL },
    { _pycs("drivable"), (getter)pyOneShotMod_getDrivable,
        (setter)pyOneShotMod_setDrivable, NULL, NULL },
    { _pycs("reversable"), (getter)pyOneShotMod_getReversable,
        (setter)pyOneShotMod_setReversable, NULL, NULL },
    { _pycs("smartSeek"), (getter)pyOneShotMod_getSmartSeek,
        (setter)pyOneShotMod_setSmartSeek, NULL, NULL },
    { _pycs("noSeek"), (getter)pyOneShotMod_getNoSeek,
        (setter)pyOneShotMod_setNoSeek, NULL, NULL },
    { _pycs("seekDuration"), (getter)pyOneShotMod_getSeekDuration,
        (setter)pyOneShotMod_setSeekDuration, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyOneShotMod_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plOneShotMod",          /* tp_name */
    sizeof(pyOneShotMod),               /* tp_basicsize */
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
    "plOneShotMod wrapper",             /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyOneShotMod_Methods,               /* tp_methods */
    NULL,                               /* tp_members */
    pyOneShotMod_GetSet,                /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyOneShotMod_new,                   /* tp_new */
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

PyObject* Init_pyOneShotMod_Type() {
    pyOneShotMod_Type.tp_base = &pyMultiModifier_Type;
    if (PyType_Ready(&pyOneShotMod_Type) < 0)
        return NULL;

    Py_INCREF(&pyOneShotMod_Type);
    return (PyObject*)&pyOneShotMod_Type;
}

int pyOneShotMod_Check(PyObject* obj) {
    if (obj->ob_type == &pyOneShotMod_Type
        || PyType_IsSubtype(obj->ob_type, &pyOneShotMod_Type))
        return 1;
    return 0;
}

PyObject* pyOneShotMod_FromOneShotMod(class plOneShotMod* mod) {
    if (mod == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyOneShotMod* pymod = PyObject_New(pyOneShotMod, &pyOneShotMod_Type);
    pymod->fThis = mod;
    pymod->fPyOwned = false;
    return (PyObject*)pymod;
}

}
