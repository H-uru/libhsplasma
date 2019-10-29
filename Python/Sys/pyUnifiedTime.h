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

#ifndef _PYUNIFIEDTIME_H
#define _PYUNIFIEDTIME_H

#include "PyPlasma.h"
#include <Sys/plUnifiedTime.h>

PY_WRAP_PLASMA_VALUE(UnifiedTime, plUnifiedTime);

/* Helpers for Python properties */
inline PyObject* pyPlasma_convert(const plUnifiedTime& value) { return pyUnifiedTime_FromUnifiedTime(value); }
template <> inline int pyPlasma_check<plUnifiedTime>(PyObject* value) { return pyUnifiedTime_Check(value); }
template <> inline plUnifiedTime pyPlasma_get(PyObject* value) { return *((pyUnifiedTime*)value)->fThis; }

#endif
