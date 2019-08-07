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

#include "pyFacingConditionalObject.h"

#include <PRP/ConditionalObject/plFacingConditionalObject.h>
#include "pyConditionalObject.h"

PY_PLASMA_NEW(FacingConditionalObject, plFacingConditionalObject)

PY_PROPERTY(float, FacingConditionalObject, tolerance, getTolerance, setTolerance)
PY_PROPERTY(bool, FacingConditionalObject, directional, getDirectional, setDirectional)

static PyGetSetDef pyFacingConditionalObject_GetSet[] = {
    pyFacingConditionalObject_tolerance_getset,
    pyFacingConditionalObject_directional_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(FacingConditionalObject, plFacingConditionalObject,
               "plFacingConditionalObject wrapper")

PY_PLASMA_TYPE_INIT(FacingConditionalObject)
{
    pyFacingConditionalObject_Type.tp_new = pyFacingConditionalObject_new;
    pyFacingConditionalObject_Type.tp_getset = pyFacingConditionalObject_GetSet;
    pyFacingConditionalObject_Type.tp_base = &pyConditionalObject_Type;
    if (PyType_CheckAndReady(&pyFacingConditionalObject_Type) < 0)
        return nullptr;

    Py_INCREF(&pyFacingConditionalObject_Type);
    return (PyObject*)&pyFacingConditionalObject_Type;
}

PY_PLASMA_IFC_METHODS(FacingConditionalObject, plFacingConditionalObject)
