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

#include "pyAnimPath.h"

#include "pyController.h"
#include "Math/pyGeometry3.h"
#include "Math/pyMatrix.h"
#include "PRP/pyCreatable.h"
#include <PRP/Animation/plAnimPath.h>

PY_PLASMA_NEW(AnimPath, plAnimPath)

PY_PROPERTY(unsigned int, AnimPath, flags, getFlags, setFlags)
PY_PROPERTY(float, AnimPath, minDistSq, getMinDistSq, setMinDistSq)
PY_PROPERTY(float, AnimPath, length, getLength, setLength)
PY_PROPERTY(hsMatrix44, AnimPath, localToWorld, getLocalToWorld, setLocalToWorld)
PY_PROPERTY(hsMatrix44, AnimPath, worldToLocal, getWorldToLocal, setWorldToLocal)
PY_PROPERTY(hsAffineParts, AnimPath, affineParts, getAffineParts, setAffineParts)

PY_GETSET_GETTER_DECL(AnimPath, controller)
{
    if (self->fThis->getController()) {
        return ICreate(self->fThis->getController());
    }
    if (self->fThis->getTMController()) {
        return ICreate(self->fThis->getTMController());
    }
    Py_RETURN_NONE;
}
PY_GETSET_SETTER_DECL(AnimPath, controller)
{
    if (value == nullptr || value == Py_None) {
        self->fThis->setController(nullptr);
        return 0;
    } else if (pyCompoundController_Check(value)) {
        ((pyCompoundController*)value)->fPyOwned = false;
        self->fThis->setController(((pyCompoundController*)value)->fThis);
        return 0;
    } else if (pyTMController_Check(value)) {
        ((pyTMController*)value)->fPyOwned = false;
        self->fThis->setTMController(((pyTMController*)value)->fThis);
        return 0;
    }
    PyErr_SetString(PyExc_TypeError, "controller should be a plCompoundController or a plTMController");
    return -1;
}
PY_PROPERTY_GETSET_DECL(AnimPath, controller)

static PyGetSetDef pyAnimPath_GetSet[] = {
    pyAnimPath_flags_getset,
    pyAnimPath_minDistSq_getset,
    pyAnimPath_length_getset,
    pyAnimPath_localToWorld_getset,
    pyAnimPath_worldToLocal_getset,
    pyAnimPath_controller_getset,
    pyAnimPath_affineParts_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(AnimPath, plAnimPath, "plAnimPath wrapper")

PY_PLASMA_TYPE_INIT(AnimPath)
{
    pyAnimPath_Type.tp_new = pyAnimPath_new;
    pyAnimPath_Type.tp_getset = pyAnimPath_GetSet;
    pyAnimPath_Type.tp_base = &pyCreatable_Type;
    if (PyType_CheckAndReady(&pyAnimPath_Type) < 0)
        return nullptr;

    /* Konstants */
    PY_TYPE_ADD_CONST(AnimPath, "kNone", plAnimPath::kNone);
    PY_TYPE_ADD_CONST(AnimPath, "kFavorFwdSearch", plAnimPath::kFavorFwdSearch);
    PY_TYPE_ADD_CONST(AnimPath, "kFavorBwdSearch", plAnimPath::kFavorBwdSearch);
    PY_TYPE_ADD_CONST(AnimPath, "kCalcPosOnly", plAnimPath::kCalcPosOnly);
    PY_TYPE_ADD_CONST(AnimPath, "kFarthest", plAnimPath::kFarthest);
    PY_TYPE_ADD_CONST(AnimPath, "kWrap", plAnimPath::kWrap);
    PY_TYPE_ADD_CONST(AnimPath, "kIncrement", plAnimPath::kIncrement);

    Py_INCREF(&pyAnimPath_Type);
    return (PyObject*)&pyAnimPath_Type;
}

PY_PLASMA_IFC_METHODS(AnimPath, plAnimPath)
