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
#include "pySpawnPointInfo.h"
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW(AgeLinkStruct, plAgeLinkStruct)

PY_GETSET_GETTER_DECL(AgeLinkStruct, ageInfo)
{
    // This cannot be a subclass, since it's an inline member
    return pyAgeInfoStruct_FromAgeInfoStruct(&self->fThis->getAgeInfo());
}

PY_GETSET_SETTER_DECL(AgeLinkStruct, ageInfo)
{
    PY_PROPERTY_CHECK_NULL(ageInfo)

    plAgeInfoStruct& ais = self->fThis->getAgeInfo();
    if (value == Py_None) {
        self->fThis->setHasAgeInfo(false);
        ais = plAgeInfoStruct();
        return 0;
    } else if (pyAgeInfoStruct_Check(value)) {
        self->fThis->setHasAgeInfo(true);
        ais = *((pyAgeInfoStruct*)value)->fThis;
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "ageInfo must be a plAgeInfoStruct");
        return -1;
    }
}

PY_PROPERTY_GETSET_DECL(AgeLinkStruct, ageInfo)

PY_GETSET_GETTER_DECL(AgeLinkStruct, spawnPoint)
{
    return pySpawnPointInfo_FromSpawnPointInfo(&self->fThis->getSpawnPoint());
}

PY_GETSET_SETTER_DECL(AgeLinkStruct, spawnPoint)
{
    PY_PROPERTY_CHECK_NULL(spawnPoint)

    plSpawnPointInfo& spi = self->fThis->getSpawnPoint();
    if (value == Py_None) {
        self->fThis->setHasSpawnPoint(false);
        spi = plSpawnPointInfo();
        return 0;
    } else if (pySpawnPointInfo_Check(value)) {
        self->fThis->setHasSpawnPoint(true);
        spi = *((pySpawnPointInfo*)value)->fThis;
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "spawnPoint must be a plSpawnPointInfo");
        return -1;
    }
}

PY_PROPERTY_GETSET_DECL(AgeLinkStruct, spawnPoint)

PY_PROPERTY(signed char, AgeLinkStruct, linkingRules, getLinkingRules, setLinkingRules)

PY_PROPERTY_READ(AgeLinkStruct, parentAgeFilename, getParentAgeFilename)

PY_GETSET_SETTER_DECL(AgeLinkStruct, parentAgeFilename)
{
    PY_PROPERTY_CHECK_NULL(parentAgeFilename)
    if (value == Py_None) {
        self->fThis->clearParentAgeFilename();
        return 0;
    } else if (pyPlasma_check<ST::string>(value)) {
        self->fThis->setParentAgeFilename(pyPlasma_get<ST::string>(value));
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "parentAgeFilename must be a string");
        return -1;
    }
}

PY_PROPERTY_GETSET_DECL(AgeLinkStruct, parentAgeFilename)

PyGetSetDef pyAgeLinkStruct_GetSet[] = {
    pyAgeLinkStruct_ageInfo_getset,
    pyAgeLinkStruct_spawnPoint_getset,
    pyAgeLinkStruct_linkingRules_getset,
    pyAgeLinkStruct_parentAgeFilename_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(AgeLinkStruct, plAgeLinkStruct, "plAgeLinkStruct wrapper")

PY_PLASMA_TYPE_INIT(AgeLinkStruct)
{
    pyAgeLinkStruct_Type.tp_new = pyAgeLinkStruct_new;
    pyAgeLinkStruct_Type.tp_getset = pyAgeLinkStruct_GetSet;
    pyAgeLinkStruct_Type.tp_base = &pyCreatable_Type;
    if (PyType_CheckAndReady(&pyAgeLinkStruct_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(AgeLinkStruct, "kBasicLink", plAgeLinkStruct::kBasicLink);
    PY_TYPE_ADD_CONST(AgeLinkStruct, "kOriginalBook", plAgeLinkStruct::kOriginalBook);
    PY_TYPE_ADD_CONST(AgeLinkStruct, "kSubAgeBook", plAgeLinkStruct::kSubAgeBook);
    PY_TYPE_ADD_CONST(AgeLinkStruct, "kOwnedBook", plAgeLinkStruct::kOwnedBook);
    PY_TYPE_ADD_CONST(AgeLinkStruct, "kVisitBook", plAgeLinkStruct::kVisitBook);
    PY_TYPE_ADD_CONST(AgeLinkStruct, "kChildAgeBook", plAgeLinkStruct::kChildAgeBook);

    Py_INCREF(&pyAgeLinkStruct_Type);
    return (PyObject*)&pyAgeLinkStruct_Type;
}

PY_PLASMA_IFC_METHODS(AgeLinkStruct, plAgeLinkStruct)
