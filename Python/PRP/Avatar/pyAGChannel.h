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

#ifndef _PYAGCHANNEL_H
#define _PYAGCHANNEL_H

#include "PyPlasma.h"

PY_WRAP_PLASMA(AGChannel, class plAGChannel);
PY_WRAP_PLASMA(MatrixChannel, class plMatrixChannel);
PY_WRAP_PLASMA(MatrixBlend, class plMatrixBlend);
PY_WRAP_PLASMA(MatrixConstant, class plMatrixConstant);
PY_WRAP_PLASMA(MatrixControllerCacheChannel, class plMatrixControllerCacheChannel);
PY_WRAP_PLASMA(MatrixControllerChannel, class plMatrixControllerChannel);
PY_WRAP_PLASMA(MatrixTimeScale, class plMatrixTimeScale);
PY_WRAP_PLASMA(QuatPointCombine, class plQuatPointCombine);
PY_WRAP_PLASMA(PointChannel, class plPointChannel);
PY_WRAP_PLASMA(PointBlend, class plPointBlend);
PY_WRAP_PLASMA(PointConstant, class plPointConstant);
PY_WRAP_PLASMA(PointControllerCacheChannel, class plPointControllerCacheChannel);
PY_WRAP_PLASMA(PointControllerChannel, class plPointControllerChannel);
PY_WRAP_PLASMA(PointTimeScale, class plPointTimeScale);
PY_WRAP_PLASMA(QuatChannel, class plQuatChannel);
PY_WRAP_PLASMA(QuatBlend, class plQuatBlend);
PY_WRAP_PLASMA(QuatConstant, class plQuatConstant);
PY_WRAP_PLASMA(QuatTimeScale, class plQuatTimeScale);
PY_WRAP_PLASMA(ScalarChannel, class plScalarChannel);
PY_WRAP_PLASMA(ScalarBlend, class plScalarBlend);
PY_WRAP_PLASMA(ScalarConstant, class plScalarConstant);
PY_WRAP_PLASMA(ScalarControllerCacheChannel, class plScalarControllerCacheChannel);
PY_WRAP_PLASMA(ScalarControllerChannel, class plScalarControllerChannel);
PY_WRAP_PLASMA(ScalarTimeScale, class plScalarTimeScale);
PY_WRAP_PLASMA(ScalarSDLChannel, class plScalarSDLChannel);
PY_WRAP_PLASMA(ATCChannel, class plATCChannel);

#endif
