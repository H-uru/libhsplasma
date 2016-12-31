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

#include "pyAgeLinkInfo.h"

#include <PRP/Misc/plAgeLinkInfo.h>
#include <Sys/plUuid.h>
#include "PRP/pyCreatable.h"

extern "C" {

PY_PLASMA_NEW(AgeInfoStruct, plAgeInfoStruct)

PY_PROPERTY(plString, AgeInfoStruct, ageFilename, getAgeFilename, setAgeFilename)
PY_PROPERTY(plString, AgeInfoStruct, ageInstanceName, getAgeInstanceName, setAgeInstanceName)

PY_GETSET_GETTER_DECL(AgeInfoStruct, ageInstanceGuid) {
    return pyPlasma_convert(self->fThis->getAgeInstanceGuid().toString());
}

PY_GETSET_SETTER_DECL(AgeInfoStruct, ageInstanceGuid) {
    if (value == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "ageInstanceGuid cannot be deleted");
        return -1;
    } else if (!pyPlasma_check<plString>(value)) {
        PyErr_SetString(PyExc_TypeError, "ageInstanceGuid should be a string");
        return -1;
    }
    try {
        plUuid uuid(pyPlasma_get<plString>(value));
        self->fThis->setAgeInstanceGuid(uuid);
    } catch (const hsBadParamException&) {
        PyErr_SetString(PyExc_ValueError, "ageInstanceGuid must be a valid UUID string");
        return -1;
    }
    return 0;
}

PY_PROPERTY_GETSET_DECL(AgeInfoStruct, ageInstanceGuid)

PyGetSetDef pyAgeInfoStruct_GetSet[] = {
    pyAgeInfoStruct_ageFilename_getset,
    pyAgeInfoStruct_ageInstanceName_getset,
    pyAgeInfoStruct_ageInstanceGuid_getset,
    PY_GETSET_TERMINATOR
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

PY_PLASMA_IFC_METHODS(AgeInfoStruct, plAgeInfoStruct)

}
