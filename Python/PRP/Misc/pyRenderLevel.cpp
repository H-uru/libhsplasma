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

#include "pyRenderLevel.h"

#include <PRP/Misc/plRenderLevel.h>

PY_PLASMA_NEW_MSG(RenderLevel, "Cannot construct plRenderLevel objects")

typedef PyObject pyRenderLevel;
PY_PLASMA_TYPE(RenderLevel, plRenderLevel, "plRenderLevel constants")

PY_PLASMA_TYPE_INIT(RenderLevel)
{
    pyRenderLevel_Type.tp_new = pyRenderLevel_new;
    if (PyType_CheckAndReady(&pyRenderLevel_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(RenderLevel, "kOpaqueMajorLevel", plRenderLevel::kOpaqueMajorLevel);
    PY_TYPE_ADD_CONST(RenderLevel, "kFBMajorLevel", plRenderLevel::kFBMajorLevel);
    PY_TYPE_ADD_CONST(RenderLevel, "kDefRendMajorLevel", plRenderLevel::kDefRendMajorLevel);
    PY_TYPE_ADD_CONST(RenderLevel, "kBlendRendMajorLevel", plRenderLevel::kBlendRendMajorLevel);
    PY_TYPE_ADD_CONST(RenderLevel, "kLateRendMajorLevel", plRenderLevel::kLateRendMajorLevel);
    PY_TYPE_ADD_CONST(RenderLevel, "kMajorShift", plRenderLevel::kMajorShift);
    PY_TYPE_ADD_CONST(RenderLevel, "kDefRendMinorLevel", plRenderLevel::kDefRendMinorLevel);
    PY_TYPE_ADD_CONST(RenderLevel, "kOpaqueMinorLevel", plRenderLevel::kOpaqueMinorLevel);
    PY_TYPE_ADD_CONST(RenderLevel, "kMinorLevelMask", plRenderLevel::kMinorLevelMask);
    PY_TYPE_ADD_CONST(RenderLevel, "kAvatarRendMinorLevel", plRenderLevel::kAvatarRendMinorLevel);

    Py_INCREF(&pyRenderLevel_Type);
    return (PyObject*)&pyRenderLevel_Type;
}
