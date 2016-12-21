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

#ifndef _PYKEYS_H
#define _PYKEYS_H

#include "PyPlasma.h"

PY_WRAP_PLASMA(KeyFrame, struct hsKeyFrame);
PY_WRAP_PLASMA(Point3Key, struct hsPoint3Key);
PY_WRAP_PLASMA(ScalarKey, struct hsScalarKey);
PY_WRAP_PLASMA(ScaleKey, struct hsScaleKey);
PY_WRAP_PLASMA(QuatKey, struct hsQuatKey);
PY_WRAP_PLASMA(CompressedQuatKey32, struct hsCompressedQuatKey32);
PY_WRAP_PLASMA(CompressedQuatKey64, struct hsCompressedQuatKey64);
PY_WRAP_PLASMA(G3DSMaxKeyFrame, struct hsG3DSMaxKeyFrame);
PY_WRAP_PLASMA(Matrix33Key, struct hsMatrix33Key);
PY_WRAP_PLASMA(Matrix44Key, struct hsMatrix44Key);

#endif
