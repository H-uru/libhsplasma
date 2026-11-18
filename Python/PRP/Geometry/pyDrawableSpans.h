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

#ifndef _PYDRAWABLESPANS_H
#define _PYDRAWABLESPANS_H

#include "PyPlasma.h"

#include <PRP/Geometry/plDrawableSpans.h>

PY_WRAP_PLASMA_VALUE(DISpanIndex, class plDISpanIndex);
PY_WRAP_PLASMA(Drawable, class plDrawable);
PY_WRAP_PLASMA(DrawableSpans, class plDrawableSpans);

inline PyObject* pyPlasma_convert(const plDISpanIndex& value) { return pyDISpanIndex_FromDISpanIndex(value); }

template <> inline int pyPlasma_check<plDISpanIndex>(PyObject* obj) { return pyDISpanIndex_Check(obj); }

template <> inline plDISpanIndex pyPlasma_get(PyObject* obj) { return *((pyDISpanIndex*)obj)->fThis; }

#endif
