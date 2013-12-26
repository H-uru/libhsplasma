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
#include "PRP/KeyedObject/pyKey.h"

extern "C" {

static PyObject* pyContainedEventData_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyContainedEventData* self = (pyContainedEventData*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new proContainedEventData();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyContainedEventData_getContained(pyContainedEventData* self, void*) {
    return pyKey_FromKey(self->fThis->getContained());
}

static PyObject* pyContainedEventData_getContainer(pyContainedEventData* self, void*) {
    return pyKey_FromKey(self->fThis->getContainer());
}

static PyObject* pyContainedEventData_getEntering(pyContainedEventData* self, void*) {
    return PyBool_FromLong(self->fThis->isEntering());
}

static int pyContainedEventData_setContained(pyContainedEventData* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setContained(plKey());
        return 0;
    } else if (pyKey_Check(value)) {
        self->fThis->setContained(*((pyKey*)value)->fThis);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "contained should be a plKey");
        return -1;
    }
}

static int pyContainedEventData_setContainer(pyContainedEventData* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        self->fThis->setContainer(plKey());
        return 0;
    } else if (pyKey_Check(value)) {
        self->fThis->setContainer(*((pyKey*)value)->fThis);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "container should be a plKey");
        return -1;
    }
}

static int pyContainedEventData_setEntering(pyContainedEventData* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "entering should be a bool");
        return -1;
    }
    self->fThis->setEntering(PyInt_AsLong(value) != 0);
    return 0;
}

static PyMethodDef pyContainedEventData_Methods[] = {
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyContainedEventData_GetSet[] = {
    { _pycs("contained"), (getter)pyContainedEventData_getContained,
        (setter)pyContainedEventData_setContained, NULL, NULL },
    { _pycs("container"), (getter)pyContainedEventData_getContainer,
        (setter)pyContainedEventData_setContainer, NULL, NULL },
    { _pycs("entering"), (getter)pyContainedEventData_getEntering,
        (setter)pyContainedEventData_setEntering, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyContainedEventData_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.proContainedEventData", /* tp_name */
    sizeof(pyContainedEventData),       /* tp_basicsize */
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
    "proContainedEventData wrapper",    /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyContainedEventData_Methods,       /* tp_methods */
    NULL,                               /* tp_members */
    pyContainedEventData_GetSet,        /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyContainedEventData_new,           /* tp_new */
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

PyObject* Init_pyContainedEventData_Type() {
    pyContainedEventData_Type.tp_base = &pyEventData_Type;
    if (PyType_Ready(&pyContainedEventData_Type) < 0)
        return NULL;

    Py_INCREF(&pyContainedEventData_Type);
    return (PyObject*)&pyContainedEventData_Type;
}

int pyContainedEventData_Check(PyObject* obj) {
    if (obj->ob_type == &pyContainedEventData_Type
        || PyType_IsSubtype(obj->ob_type, &pyContainedEventData_Type))
        return 1;
    return 0;
}

PyObject* pyContainedEventData_FromContainedEventData(proContainedEventData* evt) {
    if (evt == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyContainedEventData* pyobj = PyObject_New(pyContainedEventData, &pyContainedEventData_Type);
    pyobj->fThis = evt;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
