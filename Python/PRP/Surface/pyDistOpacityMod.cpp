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

#include "PRP/Modifier/pyModifier.h"

#include <PRP/Surface/plDistOpacityMod.h>
#include "pyDistOpacityMod.h"

PY_PLASMA_NEW(DistOpacityMod, plDistOpacityMod)

#define DOM_DISTANCE(propName, distEnum)                                \
    PY_GETSET_GETTER_DECL(DistOpacityMod, propName)                     \
    {                                                                   \
        return pyPlasma_convert(self->fThis->getDistance(plDistOpacityMod::distEnum)); \
    }                                                                   \
    PY_GETSET_SETTER_DECL(DistOpacityMod, propName)                     \
    {                                                                   \
        PY_PROPERTY_CHECK_NULL(propName)                                \
        if (!pyPlasma_check<float>(value)) {                            \
            PyErr_SetString(PyExc_TypeError, #propName " expected type float"); \
            return -1;                                                  \
        }                                                               \
        self->fThis->setDistance(plDistOpacityMod::distEnum, pyPlasma_get<float>(value)); \
        return 0;                                                       \
    }                                                                   \
    PY_PROPERTY_GETSET_DECL(DistOpacityMod, propName)

DOM_DISTANCE(nearTrans, kNearTrans)
DOM_DISTANCE(nearOpaq, kNearOpaq)
DOM_DISTANCE(farOpaq, kFarOpaq)
DOM_DISTANCE(farTrans, kFarTrans)

static PyGetSetDef pyDistOpacityMod_GetSet [] = {
    pyDistOpacityMod_nearTrans_getset,
    pyDistOpacityMod_nearOpaq_getset,
    pyDistOpacityMod_farOpaq_getset,
    pyDistOpacityMod_farTrans_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(DistOpacityMod, plDistOpacityMod, "plDistOpacityMod wrapper")

PY_PLASMA_TYPE_INIT(DistOpacityMod)
{
    pyDistOpacityMod_Type.tp_new = pyDistOpacityMod_new;
    pyDistOpacityMod_Type.tp_getset = pyDistOpacityMod_GetSet;
    pyDistOpacityMod_Type.tp_base = &pySingleModifier_Type;
    if (PyType_CheckAndReady(&pyDistOpacityMod_Type) < 0)
        return nullptr;

    Py_INCREF(&pyDistOpacityMod_Type);
    return (PyObject*) &pyDistOpacityMod_Type;
}

PY_PLASMA_IFC_METHODS(DistOpacityMod, plDistOpacityMod)
