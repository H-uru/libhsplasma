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

PY_PLASMA_NEW(LocalPlayerIntersectPlaneConditionalObject,
              plLocalPlayerIntersectPlaneConditionalObject)

PY_PLASMA_TYPE(LocalPlayerIntersectPlaneConditionalObject,
               plLocalPlayerIntersectPlaneConditionalObject,
               "plLocalPlayerIntersectPlaneConditionalObject wrapper")

PY_PLASMA_TYPE_INIT(LocalPlayerIntersectPlaneConditionalObject)
{
    pyLocalPlayerIntersectPlaneConditionalObject_Type.tp_new = pyLocalPlayerIntersectPlaneConditionalObject_new;
    pyLocalPlayerIntersectPlaneConditionalObject_Type.tp_base = &pyConditionalObject_Type;
    if (PyType_CheckAndReady(&pyLocalPlayerIntersectPlaneConditionalObject_Type) < 0)
        return nullptr;

    Py_INCREF(&pyLocalPlayerIntersectPlaneConditionalObject_Type);
    return (PyObject*)&pyLocalPlayerIntersectPlaneConditionalObject_Type;
}

PY_PLASMA_IFC_METHODS(LocalPlayerIntersectPlaneConditionalObject,
                      plLocalPlayerIntersectPlaneConditionalObject)
