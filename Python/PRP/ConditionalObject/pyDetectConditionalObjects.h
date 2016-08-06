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

#ifndef _PY_DETECTCONDITIONALOBJECT_H
#define _PY_DETECTCONDITIONALOBJECT_H

#include "PyPlasma.h"

PY_WRAP_PLASMA(LocalPlayerInBoxConditionalObject, class plLocalPlayerInBoxConditionalObject);
PY_WRAP_PLASMA(LocalPlayerIntersectPlaneConditionalObject, class plLocalPlayerIntersectPlaneConditionalObject);
PY_WRAP_PLASMA(ObjectInBoxConditionalObject, class plObjectInBoxConditionalObject);
PY_WRAP_PLASMA(ObjectIntersectPlaneConditionalObject, class plObjectIntersectPlaneConditionalObject);

#endif
