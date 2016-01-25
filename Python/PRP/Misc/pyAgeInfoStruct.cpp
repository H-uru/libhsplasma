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
#include <PRP/Misc/plAgeLinkInfo.h>
#include <Sys/plUuid.h>

#include "pyAgeLinkInfo.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyAgeInfoStruct_new(PyTypeObject* type, PyObject*, PyObject*) {
    pyAgeInfoStruct* self = (pyAgeInfoStruct*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plAgeInfoStruct();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyAgeInfoStruct_getAgeFilename(pyAgeInfoStruct* self, void*) {
    return PlStr_To_PyStr(self->fThis->getAgeFilename());
}

static PyObject* pyAgeInfoStruct_getAgeInstanceName(pyAgeInfoStruct* self, void*) {
    return PlStr_To_PyStr(self->fThis->getAgeInstanceName());
}

static PyObject* pyAgeInfoStruct_getAgeInstanceGuid(pyAgeInfoStruct* self, void*) {
    return PlStr_To_PyStr(self->fThis->getAgeInstanceGuid().toString());
}

static int pyAgeInfoStruct_setAgeFilename(pyAgeInfoStruct* self, PyObject* value, void*) {
    if (value == NULL || !PyAnyStr_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "filename should be a string");
        return -1;
    }
    self->fThis->setAgeFilename(PyStr_To_PlStr(value));
    return 0;
}

static int pyAgeInfoStruct_setAgeInstanceName(pyAgeInfoStruct* self, PyObject* value, void*) {
    if (value == NULL || !PyAnyStr_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "ageInstanceName should be a string");
        return -1;
    }
    self->fThis->setAgeInstanceName(PyStr_To_PlStr(value));
    return 0;
}

static int pyAgeInfoStruct_setAgeInstanceGuid(pyAgeInfoStruct* self, PyObject* value, void*) {
    if (value == NULL || !PyAnyStr_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "ageInstanceGuid should be a string");
        return -1;
    }
    try {
        plUuid uuid(PyStr_To_PlStr(value));
        self->fThis->setAgeInstanceGuid(uuid);
    } catch (const hsBadParamException&) {
        PyErr_SetString(PyExc_ValueError, "ageInstanceGuid must be a valid UUID string");
        return -1;
    }
    return 0;
}

PyGetSetDef pyAgeInfoStruct_GetSet[] = {
    { _pycs("ageFilename"), (getter)pyAgeInfoStruct_getAgeFilename,
     (setter)pyAgeInfoStruct_setAgeFilename, NULL, NULL },
    { _pycs("ageInstanceName"), (getter)pyAgeInfoStruct_getAgeInstanceName,
     (setter)pyAgeInfoStruct_setAgeInstanceName, NULL, NULL },
    { _pycs("ageInstanceGuid"), (getter)pyAgeInfoStruct_getAgeInstanceGuid,
     (setter)pyAgeInfoStruct_setAgeInstanceGuid, NULL, NULL },
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
    TP_FINALIZE_INIT                    /* tp_finalize */
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

}
