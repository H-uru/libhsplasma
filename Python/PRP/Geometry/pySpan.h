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

#ifndef _PYSPAN_H
#define _PYSPAN_H

#include "PyPlasma.h"

PY_WRAP_PLASMA(Span, class plSpan);
PY_WRAP_PLASMA(VertexSpan, class plVertexSpan);
PY_WRAP_PLASMA(Icicle, class plIcicle);
PY_WRAP_PLASMA(ParticleSpan, class plParticleSpan);

#endif
