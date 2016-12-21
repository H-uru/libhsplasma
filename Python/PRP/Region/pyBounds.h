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

#ifndef _PYBOUNDS_H
#define _PYBOUNDS_H

#include "PyPlasma.h"

PY_WRAP_PLASMA_VALUE(Bounds, class hsBounds);
PY_WRAP_PLASMA_VALUE(Bounds3, class hsBounds3);
PY_WRAP_PLASMA_VALUE(Bounds3Ext, class hsBounds3Ext);
PY_WRAP_PLASMA_VALUE(BoundsOriented, class hsBoundsOriented);

PyObject* ICreateBounds(const class hsBounds&);

#endif
