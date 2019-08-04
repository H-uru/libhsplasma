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

#include "pySpan.h"

#include <PRP/Geometry/plVertexSpan.h>
#include <PRP/Geometry/plIcicle.h>
#include <typeinfo>

PyObject* ICreateSpan(plSpan* span)
{
    if (typeid(*span) == typeid(plIcicle))
        return pyIcicle_FromIcicle((plIcicle*)span);
    else if (typeid(*span) == typeid(plVertexSpan))
        return pyVertexSpan_FromVertexSpan((plVertexSpan*)span);
    else if (typeid(*span) == typeid(plParticleSpan))
        return pyParticleSpan_FromParticleSpan((plParticleSpan*)span);
    return pySpan_FromSpan(span);
}
