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

#ifndef _PYMATRIX_H
#define _PYMATRIX_H

#include "PyPlasma.h"
#include <Math/hsMatrix33.h>
#include <Math/hsMatrix44.h>

PY_WRAP_PLASMA_VALUE(Matrix33, struct hsMatrix33);
PY_WRAP_PLASMA_VALUE(Matrix44, struct hsMatrix44);

/* Helpers for Python properties */
inline PyObject* pyPlasma_convert(const hsMatrix33& value) { return pyMatrix33_FromMatrix33(value); }
inline PyObject* pyPlasma_convert(const hsMatrix44& value) { return pyMatrix44_FromMatrix44(value); }

template <> inline int pyPlasma_check<hsMatrix33>(PyObject *value) { return pyMatrix33_Check(value); }
template <> inline int pyPlasma_check<hsMatrix44>(PyObject *value) { return pyMatrix44_Check(value); }

template <> inline hsMatrix33 pyPlasma_get(PyObject* value) { return *((pyMatrix33*)value)->fThis; }
template <> inline hsMatrix44 pyPlasma_get(PyObject* value) { return *((pyMatrix44*)value)->fThis; }

#endif
