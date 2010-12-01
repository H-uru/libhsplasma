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

#include <PyPlasma.h>
#include <PRP/Message/proEventData.h>
#include "pyEventData.h"

extern "C" {

static PyObject* pyActivateEventData_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyActivateEventData* self = (pyActivateEventData*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new proActivateEventData();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyActivateEventData_getActive(pyActivateEventData* self, void*) {
    return PyBool_FromLong(self->fThis->isActive());
}

static PyObject* pyActivateEventData_getActivate(pyActivateEventData* self, void*) {
    return PyBool_FromLong(self->fThis->isActivate());
}

static int pyActivateEventData_setActive(pyActivateEventData* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "active should be a bool");
        return -1;
    }
    self->fThis->setActive(PyInt_AsLong(value) != 0);
    return 0;
}

static int pyActivateEventData_setActivate(pyActivateEventData* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "activate should be a bool");
        return -1;
    }
    self->fThis->setActivate(PyInt_AsLong(value) != 0);
    return 0;
}

static PyMethodDef pyActivateEventData_Methods[] = {
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyActivateEventData_GetSet[] = {
    { "active", (getter)pyActivateEventData_getActive, (setter)pyActivateEventData_setActive, NULL, NULL },
    { "activate", (getter)pyActivateEventData_getActivate, (setter)pyActivateEventData_setActivate, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyActivateEventData_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.proActivateEventData",    /* tp_name */
    sizeof(pyActivateEventData),        /* tp_basicsize */
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
    "proActivateEventData wrapper",     /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyActivateEventData_Methods,        /* tp_methods */
    NULL,                               /* tp_members */
    pyActivateEventData_GetSet,         /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyActivateEventData_new,            /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */

    NULL,                               /* tp_del */
    TP_VERSION_TAG_INIT                 /* tp_version_tag */
};

PyObject* Init_pyActivateEventData_Type() {
    pyActivateEventData_Type.tp_base = &pyEventData_Type;
    if (PyType_Ready(&pyActivateEventData_Type) < 0)
        return NULL;

    Py_INCREF(&pyActivateEventData_Type);
    return (PyObject*)&pyActivateEventData_Type;
}

int pyActivateEventData_Check(PyObject* obj) {
    if (obj->ob_type == &pyActivateEventData_Type
        || PyType_IsSubtype(obj->ob_type, &pyActivateEventData_Type))
        return 1;
    return 0;
}

PyObject* pyActivateEventData_FromActivateEventData(proActivateEventData* evt) {
    if (evt == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyActivateEventData* pyobj = PyObject_New(pyActivateEventData, &pyActivateEventData_Type);
    pyobj->fThis = evt;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
