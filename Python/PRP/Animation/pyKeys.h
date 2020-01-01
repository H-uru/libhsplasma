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

#include <PRP/Animation/hsKeys.h>

#include "PyPlasma.h"

PY_WRAP_PLASMA(KeyFrame, hsKeyFrame);
PY_WRAP_PLASMA(Point3Key, hsPoint3Key);
PY_WRAP_PLASMA(ScalarKey, hsScalarKey);
PY_WRAP_PLASMA(ScaleKey, hsScaleKey);
PY_WRAP_PLASMA(QuatKey, hsQuatKey);
PY_WRAP_PLASMA(CompressedQuatKey32, hsCompressedQuatKey32);
PY_WRAP_PLASMA(CompressedQuatKey64, hsCompressedQuatKey64);
PY_WRAP_PLASMA(G3DSMaxKeyFrame, hsG3DSMaxKeyFrame);
PY_WRAP_PLASMA(Matrix33Key, hsMatrix33Key);
PY_WRAP_PLASMA(Matrix44Key, hsMatrix44Key);

inline PyObject* pyPlasma_convert(hsKeyFrame* key)
{
    switch (key->getType()) {
    case hsKeyFrame::kPoint3KeyFrame:
    case hsKeyFrame::kBezPoint3KeyFrame:
        return pyPoint3Key_FromPoint3Key((hsPoint3Key*)key);
    case hsKeyFrame::kScalarKeyFrame:
    case hsKeyFrame::kBezScalarKeyFrame:
        return pyScalarKey_FromScalarKey((hsScalarKey*)key);
    case hsKeyFrame::kScaleKeyFrame:
    case hsKeyFrame::kBezScaleKeyFrame:
        return pyScaleKey_FromScaleKey((hsScaleKey*)key);
    case hsKeyFrame::kQuatKeyFrame:
        return pyQuatKey_FromQuatKey((hsQuatKey*)key);
    case hsKeyFrame::kCompressedQuatKeyFrame32:
        return pyCompressedQuatKey32_FromCompressedQuatKey32((hsCompressedQuatKey32*)key);
    case hsKeyFrame::kCompressedQuatKeyFrame64:
        return pyCompressedQuatKey64_FromCompressedQuatKey64((hsCompressedQuatKey64*)key);
    case hsKeyFrame::k3dsMaxKeyFrame:
        return pyG3DSMaxKeyFrame_FromG3DSMaxKeyFrame((hsG3DSMaxKeyFrame*)key);
    case hsKeyFrame::kMatrix33KeyFrame:
        return pyMatrix33Key_FromMatrix33Key((hsMatrix33Key*)key);
    case hsKeyFrame::kMatrix44KeyFrame:
        return pyMatrix44Key_FromMatrix44Key((hsMatrix44Key*)key);
    default:
        return pyKeyFrame_FromKeyFrame(key);
    }
}

#endif
