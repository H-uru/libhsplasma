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

#ifndef _PYSERVERGUID_H
#define _PYSERVERGUID_H

#include "PyPlasma.h"
#include <Vault/plServerGuid.h>

PY_WRAP_PLASMA_VALUE(ServerGuid, plServerGuid)

/* Helpers for Python properties */
inline PyObject* pyPlasma_convert(const plServerGuid& value) { return pyServerGuid_FromServerGuid(value); }
template <> inline int pyPlasma_check<plServerGuid>(PyObject* value) { return pyServerGuid_Check(value); }
template <> inline plServerGuid pyPlasma_get(PyObject* value) { return *((pyServerGuid*)value)->fThis; }

#endif
