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

#ifndef _PYGEOMETRY3_H
#define _PYGEOMETRY3_H

#include "PyPlasma.h"
#include <Math/hsAffineParts.h>

PY_WRAP_PLASMA_VALUE(Vector3, struct hsVector3);
PY_WRAP_PLASMA_VALUE(Plane3, struct hsPlane3);
PY_WRAP_PLASMA_VALUE(Quat, struct hsQuat);
PY_WRAP_PLASMA_VALUE(AffineParts, class hsAffineParts);

/* Helpers for Python properties */
inline PyObject* pyPlasma_convert(const hsVector3& value) { return pyVector3_FromVector3(value); }
inline PyObject* pyPlasma_convert(const hsPlane3& value) { return pyPlane3_FromPlane3(value); }
inline PyObject* pyPlasma_convert(const hsQuat& value) { return pyQuat_FromQuat(value); }
inline PyObject* pyPlasma_convert(const hsAffineParts& value) { return pyAffineParts_FromAffineParts(value); }

template <> inline int pyPlasma_check<hsVector3>(PyObject *value) { return pyVector3_Check(value); }
template <> inline int pyPlasma_check<hsPlane3>(PyObject *value) { return pyPlane3_Check(value); }
template <> inline int pyPlasma_check<hsQuat>(PyObject *value) { return pyQuat_Check(value); }
template <> inline int pyPlasma_check<hsAffineParts>(PyObject *value) { return pyAffineParts_Check(value); }

template <> inline hsVector3 pyPlasma_get(PyObject* value) { return *((pyVector3*)value)->fThis; }
template <> inline hsPlane3 pyPlasma_get(PyObject* value) { return *((pyPlane3*)value)->fThis; }
template <> inline hsQuat pyPlasma_get(PyObject* value) { return *((pyQuat*)value)->fThis; }
template <> inline hsAffineParts pyPlasma_get(PyObject* value) { return *((pyAffineParts*)value)->fThis; }

#endif
