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

PY_PLASMA_NEW(AgeInfoStruct, plAgeInfoStruct)

PY_PROPERTY(ST::string, AgeInfoStruct, ageFilename, getAgeFilename, setAgeFilename)
PY_PROPERTY(ST::string, AgeInfoStruct, ageInstanceName, getAgeInstanceName, setAgeInstanceName)

PY_GETSET_GETTER_DECL(AgeInfoStruct, ageInstanceGuid)
{
    return pyPlasma_convert(self->fThis->getAgeInstanceGuid().toString());
}

PY_GETSET_SETTER_DECL(AgeInfoStruct, ageInstanceGuid)
{
    PY_PROPERTY_CHECK_NULL(ageInstanceGuid)
    if (!pyPlasma_check<ST::string>(value)) {
        PyErr_SetString(PyExc_TypeError, "ageInstanceGuid should be a string");
        return -1;
    }
    try {
        plUuid uuid(pyPlasma_get<ST::string>(value));
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

PY_PLASMA_TYPE(AgeInfoStruct, plAgeInfoStruct, "plAgeInfoStruct wrapper")

PY_PLASMA_TYPE_INIT(AgeInfoStruct)
{
    pyAgeInfoStruct_Type.tp_new = pyAgeInfoStruct_new;
    pyAgeInfoStruct_Type.tp_getset = pyAgeInfoStruct_GetSet;
    pyAgeInfoStruct_Type.tp_base = &pyCreatable_Type;
    if (PyType_CheckAndReady(&pyAgeInfoStruct_Type) < 0)
        return nullptr;

    Py_INCREF(&pyAgeInfoStruct_Type);
    return (PyObject*)&pyAgeInfoStruct_Type;
}

PY_PLASMA_IFC_METHODS(AgeInfoStruct, plAgeInfoStruct)
