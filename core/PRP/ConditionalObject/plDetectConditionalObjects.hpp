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

#ifndef _PLDETECTCONDITIONALOBJECTS_H
#define _PLDETECTCONDITIONALOBJECTS_H

#include "plConditionalObject.h"

class PLASMA_DLL plLocalPlayerInBoxConditionalObject : public plConditionalObject
{
    CREATABLE(plLocalPlayerInBoxConditionalObject,
              kLocalPlayerInBoxConditionalObject,
              plConditionalObject)
};

class PLASMA_DLL plLocalPlayerIntersectPlaneConditionalObject : public plConditionalObject
{
    CREATABLE(plLocalPlayerIntersectPlaneConditionalObject,
              kLocalPlayerIntersectPlaneConditionalObject,
              plConditionalObject)
};

class PLASMA_DLL plObjectInBoxConditionalObject : public plConditionalObject
{
    CREATABLE(plObjectInBoxConditionalObject,
              kObjectInBoxConditionalObject,
              plConditionalObject)
};

class PLASMA_DLL plObjectIntersectPlaneConditionalObject : public plConditionalObject
{
    CREATABLE(plObjectIntersectPlaneConditionalObject,
              kObjectIntersectPlaneConditionalObject,
              plConditionalObject)
};

#endif
