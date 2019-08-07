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

#include "pyDetectConditionalObjects.h"

#include <PRP/ConditionalObject/plDetectConditionalObjects.hpp>
#include "pyConditionalObject.h"

PY_PLASMA_NEW(ObjectIntersectPlaneConditionalObject, plObjectIntersectPlaneConditionalObject)

PY_PLASMA_TYPE(ObjectIntersectPlaneConditionalObject, plObjectIntersectPlaneConditionalObject,
               "plObjectIntersectPlaneConditionalObject wrapper")

PY_PLASMA_TYPE_INIT(ObjectIntersectPlaneConditionalObject)
{
    pyObjectIntersectPlaneConditionalObject_Type.tp_new = pyObjectIntersectPlaneConditionalObject_new;
    pyObjectIntersectPlaneConditionalObject_Type.tp_base = &pyConditionalObject_Type;
    if (PyType_CheckAndReady(&pyObjectIntersectPlaneConditionalObject_Type) < 0)
        return nullptr;

    Py_INCREF(&pyObjectIntersectPlaneConditionalObject_Type);
    return (PyObject*)&pyObjectIntersectPlaneConditionalObject_Type;
}

PY_PLASMA_IFC_METHODS(ObjectIntersectPlaneConditionalObject, plObjectIntersectPlaneConditionalObject)
