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

#ifndef _PYGBUFFERGROUP_H
#define _PYGBUFFERGROUP_H

#include "PyPlasma.h"

#include <PRP/Geometry/plGBufferGroup.h>

PY_WRAP_PLASMA_VALUE(GBufferCell, class plGBufferCell);
PY_WRAP_PLASMA_VALUE(GBufferTriangle, class plGBufferTriangle);
PY_WRAP_PLASMA_VALUE(GBufferVertex, class plGBufferVertex);
PY_WRAP_PLASMA(GBufferGroup, class plGBufferGroup);

inline PyObject* pyPlasma_convert(const plGBufferCell& cell) { return pyGBufferCell_FromGBufferCell(cell); }
inline PyObject* pyPlasma_convert(const plGBufferTriangle& triangle) { return pyGBufferTriangle_FromGBufferTriangle(triangle); }
inline PyObject* pyPlasma_convert(const plGBufferVertex& vertex) { return pyGBufferVertex_FromGBufferVertex(vertex); }

template <> inline int pyPlasma_check<plGBufferCell>(PyObject* obj) { return pyGBufferCell_Check(obj); }
template <> inline int pyPlasma_check<plGBufferTriangle>(PyObject* obj) { return pyGBufferTriangle_Check(obj); }
template <> inline int pyPlasma_check<plGBufferVertex>(PyObject* obj) { return pyGBufferVertex_Check(obj); }

template <> inline plGBufferCell pyPlasma_get(PyObject* obj) { return *((pyGBufferCell*)obj)->fThis; }
template <> inline plGBufferTriangle pyPlasma_get(PyObject* obj) { return *((pyGBufferTriangle*)obj)->fThis; }
template <> inline plGBufferVertex pyPlasma_get(PyObject* obj) { return *((pyGBufferVertex*)obj)->fThis; }

#endif
