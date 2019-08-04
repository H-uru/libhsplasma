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

#ifndef _PYAGANIM_H
#define _PYAGANIM_H

#include "PyPlasma.h"
#include <PRP/Avatar/plAGAnim.h>

PY_WRAP_PLASMA(AGAnim, class plAGAnim);
PY_WRAP_PLASMA(AgeGlobalAnim, class plAgeGlobalAnim);

/* Python property helpers */
inline PyObject* pyPlasma_convert(plAGAnim::BodyUsage value)
{
    return PyInt_FromLong((long)value);
}

template <>
inline int pyPlasma_check<plAGAnim::BodyUsage>(PyObject* value)
{
    return PyInt_Check(value);
}

template <>
inline plAGAnim::BodyUsage pyPlasma_get(PyObject* value)
{
    return (plAGAnim::BodyUsage)PyInt_AsLong(value);
}

#endif
