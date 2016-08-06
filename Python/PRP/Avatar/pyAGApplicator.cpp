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

#include "pyAGApplicator.h"

#include <PRP/Avatar/plAGApplicator.h>
#include "pyAGChannel.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyAGApplicator_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "plAGApplicator is abstract");
    return NULL;
}

static PyObject* pyAGApplicator_getChannel(pyAGApplicator* self, void*) {
    return ICreate(self->fThis->getChannel());
}

static PyObject* pyAGApplicator_getEnabled(pyAGApplicator* self, void*) {
    return PyBool_FromLong(self->fThis->isEnabled() ? 1 : 0);
}

static PyObject* pyAGApplicator_getChannelName(pyAGApplicator* self, void*) {
    return PlStr_To_PyStr(self->fThis->getChannelName());
}

static int pyAGApplicator_setChannel(pyAGApplicator* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setChannel(NULL);
        return 0;
    }
    if (!pyAGChannel_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "channel should be a plAGChannel");
        return -1;
    }
    self->fThis->setChannel(((pyAGChannel*)value)->fThis);
    ((pyAGChannel*)value)->fPyOwned = false;
    return 0;
}

static int pyAGApplicator_setEnabled(pyAGApplicator* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "enabled should be a bool");
        return -1;
    }
    self->fThis->setEnabled(PyInt_AsLong(value) != 0);
    return 0;
}

static int pyAGApplicator_setChannelName(pyAGApplicator* self, PyObject* value, void*) {
    if (value == NULL || !PyAnyStr_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "channelName should be a string");
        return -1;
    }
    self->fThis->setChannelName(PyStr_To_PlStr(value));
    return 0;
}

static PyMethodDef pyAGApplicator_Methods[] = {
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyAGApplicator_GetSet[] = {
    { _pycs("channel"), (getter)pyAGApplicator_getChannel,
        (setter)pyAGApplicator_setChannel, NULL, NULL },
    { _pycs("enabled"), (getter)pyAGApplicator_getEnabled,
        (setter)pyAGApplicator_setEnabled, NULL, NULL },
    { _pycs("channelName"), (getter)pyAGApplicator_getChannelName,
        (setter)pyAGApplicator_setChannelName, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyAGApplicator_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plAGApplicator",        /* tp_name */
    sizeof(pyAGApplicator),             /* tp_basicsize */
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
    "plAGApplicator wrapper",           /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyAGApplicator_Methods,             /* tp_methods */
    NULL,                               /* tp_members */
    pyAGApplicator_GetSet,              /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyAGApplicator_new,                 /* tp_new */
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

PyObject* Init_pyAGApplicator_Type() {
    pyAGApplicator_Type.tp_base = &pyCreatable_Type;
    if (PyType_Ready(&pyAGApplicator_Type) < 0)
        return NULL;

    Py_INCREF(&pyAGApplicator_Type);
    return (PyObject*)&pyAGApplicator_Type;
}

int pyAGApplicator_Check(PyObject* obj) {
    if (obj->ob_type == &pyAGApplicator_Type
        || PyType_IsSubtype(obj->ob_type, &pyAGApplicator_Type))
        return 1;
    return 0;
}

PyObject* pyAGApplicator_FromAGApplicator(class plAGApplicator* app) {
    if (app == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyAGApplicator* pyobj = PyObject_New(pyAGApplicator, &pyAGApplicator_Type);
    pyobj->fThis = app;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
