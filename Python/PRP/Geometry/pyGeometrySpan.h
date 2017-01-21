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

#ifndef _PYGEOMETRYSPAN_H
#define _PYGEOMETRYSPAN_H

#include "PyPlasma.h"
#include <memory>

typedef struct {
    PyObject_HEAD
    std::shared_ptr<class plGeometrySpan> fThis;
} pyGeometrySpan;

extern PyTypeObject pyGeometrySpan_Type;
PyObject* Init_pyGeometrySpan_Type();
int pyGeometrySpan_Check(PyObject* obj);
PyObject* pyGeometrySpan_FromGeometrySpan(const std::shared_ptr<class plGeometrySpan>& span);

#endif
