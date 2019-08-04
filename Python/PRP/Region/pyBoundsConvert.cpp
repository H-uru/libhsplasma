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

#include "pyBounds.h"

#include <PRP/Region/hsBounds.h>
#include <typeinfo>

PyObject* ICreateBounds(const hsBounds& bounds)
{
    if (typeid(bounds) == typeid(hsBounds3))
        return pyBounds3_FromBounds3((const hsBounds3&)bounds);
    else if (typeid(bounds) == typeid(hsBounds3Ext))
        return pyBounds3Ext_FromBounds3Ext((const hsBounds3Ext&)bounds);
    else if (typeid(bounds) == typeid(hsBoundsOriented))
        return pyBoundsOriented_FromBoundsOriented((const hsBoundsOriented&)bounds);
    return pyBounds_FromBounds(bounds);
}
