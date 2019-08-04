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

#ifndef _PYCOLOR_H

#include "PyPlasma.h"
#include <Sys/hsColor.h>

PY_WRAP_PLASMA_VALUE(ColorRGBA, struct hsColorRGBA);
PY_WRAP_PLASMA_VALUE(Color32, struct hsColor32);

/* Python property helpers */
inline PyObject* pyPlasma_convert(const hsColorRGBA& value)
{
    return pyColorRGBA_FromColorRGBA(value);
}

template <>
inline int pyPlasma_check<hsColorRGBA>(PyObject* value)
{
    return pyColorRGBA_Check(value);
}

template <>
inline hsColorRGBA pyPlasma_get(PyObject* value)
{
    return *((pyColorRGBA*)value)->fThis;
}

#endif
