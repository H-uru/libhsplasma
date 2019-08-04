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

#ifndef _PYFOLLOWMOD_H
#define _PYFOLLOWMOD_H

#include "PyPlasma.h"
#include <PRP/Modifier/plFollowMod.h>

PY_WRAP_PLASMA(FollowMod, class plFollowMod);

/* Python property helpers */
inline PyObject* pyPlasma_convert(plFollowMod::FollowLeaderType value)
{
    return PyInt_FromLong((long)value);
}

template <>
inline int pyPlasma_check<plFollowMod::FollowLeaderType>(PyObject* value)
{
    return PyInt_Check(value);
}

template <>
inline plFollowMod::FollowLeaderType pyPlasma_get(PyObject* value)
{
    return (plFollowMod::FollowLeaderType)PyInt_AsLong(value);
}

#endif
