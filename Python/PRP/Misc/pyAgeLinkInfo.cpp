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
#include "PRP/Misc/plAgeLinkInfo.h"
#include "pyAgeLinkInfo.h"
#include <PRP/pyCreatable.h>

extern "C" {

static PyObject* pyAgeInfoStruct_new(PyTypeObject* type, PyObject* , PyObject* ) {
    pyAgeInfoStruct* self = (pyAgeInfoStruct*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plAgeInfoStruct();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static int pyAgeInfoStruct_setAgeFilename(pyAgeInfoStruct* self, PyObject* value, void*) {
    if (value == NULL || !PyAnyStr_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "filename should be a string");
        return -1;
    }
    self->fThis->setAgeFilename(PyStr_To_PlStr(value));
    return -1;
}
static PyObject *pyAgeInfoStruct_getAgeFilename(pyAgeInfoStruct* self, void*) {
    return PyString_FromString(self->fThis->getAgeFilename());
}

static int pyAgeInfoStruct_setAgeInstanceName(pyAgeInfoStruct* self, PyObject* value, void*) {
    if (value == NULL || !PyAnyStr_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "ageInstanceName should be a string");
        return -1;
    }
    self->fThis->setAgeInstanceName(PyStr_To_PlStr(value));
    return -1;
}
static PyObject *pyAgeInfoStruct_getAgeInstanceName(pyAgeInfoStruct* self, void*) {
    return PyString_FromString(self->fThis->getAgeInstanceName());
}

PyGetSetDef pyAgeInfoStruct_GetSet[] = {
    { _pycs("ageFilename"), (getter)pyAgeInfoStruct_getAgeFilename,
        (setter)pyAgeInfoStruct_setAgeFilename, NULL, NULL },
    { _pycs("ageInstanceName"), (getter)pyAgeInfoStruct_getAgeInstanceName,
        (setter)pyAgeInfoStruct_setAgeInstanceName, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyAgeInfoStruct_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plAgeInfoStruct",       /* tp_name */
    sizeof(pyAgeInfoStruct),            /* tp_basicsize */
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
    "plAgeInfoStruct wrapper",                 /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyAgeInfoStruct_GetSet,             /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyAgeInfoStruct_new,                /* tp_new */
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

PyObject* Init_pyAgeInfoStruct_Type() {
    pyAgeInfoStruct_Type.tp_base = &pyCreatable_Type;
    if (PyType_Ready(&pyAgeInfoStruct_Type) < 0)
        return NULL;

    Py_INCREF(&pyAgeInfoStruct_Type);
    return (PyObject*)&pyAgeInfoStruct_Type;
}

int pyAgeInfoStruct_Check(PyObject* obj) {
    if (obj->ob_type == &pyAgeInfoStruct_Type
        || PyType_IsSubtype(obj->ob_type, &pyAgeInfoStruct_Type))
        return 1;
    return 0;
}

PyObject* pyAgeInfoStruct_FromAgeInfoStruct(plAgeInfoStruct* als) {
    if (als == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyAgeInfoStruct* pyobj = PyObject_New(pyAgeInfoStruct, &pyAgeInfoStruct_Type);
    pyobj->fThis = als;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

static PyObject* pyAgeLinkStruct_new(PyTypeObject* type, PyObject* , PyObject* ) {
    pyAgeLinkStruct* self = (pyAgeLinkStruct*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plAgeLinkStruct();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static int pyAgeLinkStruct_setLinkingRules(pyAgeLinkStruct* self, PyObject* value, void*) {
    self->fThis->setLinkingRules(PyInt_AsLong(value));
    return -1;
}
static PyObject *pyAgeLinkStruct_getLinkingRules(pyAgeLinkStruct* self, void*) {
    return PyInt_FromLong(self->fThis->getLinkingRules());
}

static int pyAgeLinkStruct_setAgeInfo(pyAgeLinkStruct* , PyObject* , void*) {
    PyErr_SetString(PyExc_RuntimeError, "ageInfo is read-only");
    return -1;
}
static PyObject *pyAgeLinkStruct_getAgeInfo(pyAgeLinkStruct*self , void*) {
    return pyAgeInfoStruct_FromAgeInfoStruct(&self->fThis->getAgeInfo());
}

PyGetSetDef pyAgeLinkStruct_GetSet[] = {
    { _pycs("ageInfo"), (getter)pyAgeLinkStruct_getAgeInfo,
        (setter)pyAgeLinkStruct_setAgeInfo, NULL, NULL },
    { _pycs("linkingRules"), (getter)pyAgeLinkStruct_getLinkingRules,
        (setter)pyAgeLinkStruct_setLinkingRules, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyAgeLinkStruct_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plAgeLinkStruct",       /* tp_name */
    sizeof(pyAgeLinkStruct),            /* tp_basicsize */
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
    "plAgeLinkStruct wrapper",                 /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyAgeLinkStruct_GetSet,             /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyAgeLinkStruct_new,                /* tp_new */
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

PyObject* Init_pyAgeLinkStruct_Type() {
    pyAgeLinkStruct_Type.tp_base = &pyCreatable_Type;
    if (PyType_Ready(&pyAgeLinkStruct_Type) < 0)
        return NULL;

    Py_INCREF(&pyAgeLinkStruct_Type);
    return (PyObject*)&pyAgeLinkStruct_Type;
}

int pyAgeLinkStruct_Check(PyObject* obj) {
    if (obj->ob_type == &pyAgeLinkStruct_Type
        || PyType_IsSubtype(obj->ob_type, &pyAgeLinkStruct_Type))
        return 1;
    return 0;
}

PyObject* pyAgeLinkStruct_FromAgeLinkStruct(plAgeLinkStruct* als) {
    if (als == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyAgeLinkStruct* pyobj = PyObject_New(pyAgeLinkStruct, &pyAgeLinkStruct_Type);
    pyobj->fThis = als;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}