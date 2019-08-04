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

#ifndef _PYKEY_H
#define _PYKEY_H

#include "PyPlasma.h"
#include <PRP/KeyedObject/plKey.h>

PY_WRAP_PLASMA_VALUE(Key, class plKey);
PY_WRAP_PLASMA_VALUE(Location, class plLocation);

/* Helpers for Python properties */
inline PyObject* pyPlasma_convert(const plLocation& value) { return pyLocation_FromLocation(value); }
template <> inline int pyPlasma_check<plLocation>(PyObject* value) { return pyLocation_Check(value); }
template <> inline plLocation pyPlasma_get(PyObject* value) { return *((pyLocation*)value)->fThis; }

/* Special case for plKey -- accept None as an empty key */
inline PyObject* pyPlasma_convert(const plKey& value) { return pyKey_FromKey(value); }

template <>
inline int pyPlasma_check<plKey>(PyObject* value)
{
    return value == Py_None || pyKey_Check(value);
}

template <> inline plKey pyPlasma_get(PyObject* value)
{
    if (value == Py_None)
        return plKey();
    return *((pyKey*)value)->fThis;
}

#endif
