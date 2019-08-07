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

#include "pyViewFaceModifier.h"

#include <PRP/Animation/plViewFaceModifier.h>
#include "PRP/Modifier/pyModifier.h"
#include "PRP/Region/pyBounds.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/pyCreatable.h"
#include "Math/pyGeometry3.h"
#include "Math/pyMatrix.h"

PY_PLASMA_NEW(ViewFaceModifier, plViewFaceModifier)

PY_PROPERTY(hsVector3, ViewFaceModifier, scale, getScale, setScale)
PY_PROPERTY(hsVector3, ViewFaceModifier, offset, getOffset, setOffset)
PY_PROPERTY(hsMatrix44, ViewFaceModifier, localToParent, getLocalToParent, setLocalToParent)
PY_PROPERTY(hsMatrix44, ViewFaceModifier, parentToLocal, getParentToLocal, setParentToLocal)
PY_PROPERTY(plKey, ViewFaceModifier, faceObj, getFaceObj, setFaceObj)
PY_PROPERTY_BOUNDS(Bounds3Ext, ViewFaceModifier, maxBounds, getMaxBounds, setMaxBounds)

static PyGetSetDef pyViewFaceModifier_GetSet[] = {
    pyViewFaceModifier_scale_getset,
    pyViewFaceModifier_offset_getset,
    pyViewFaceModifier_localToParent_getset,
    pyViewFaceModifier_parentToLocal_getset,
    pyViewFaceModifier_faceObj_getset,
    pyViewFaceModifier_maxBounds_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ViewFaceModifier, plViewFaceModifier, "plViewFaceModifier wrapper")

PY_PLASMA_TYPE_INIT(ViewFaceModifier)
{
    pyViewFaceModifier_Type.tp_new = pyViewFaceModifier_new;
    pyViewFaceModifier_Type.tp_getset = pyViewFaceModifier_GetSet;
    pyViewFaceModifier_Type.tp_base = &pySingleModifier_Type;
    if (PyType_CheckAndReady(&pyViewFaceModifier_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(ViewFaceModifier, "kPivotFace", plViewFaceModifier::kPivotFace);
    PY_TYPE_ADD_CONST(ViewFaceModifier, "kPivotFavorY", plViewFaceModifier::kPivotFavorY);
    PY_TYPE_ADD_CONST(ViewFaceModifier, "kPivotY", plViewFaceModifier::kPivotY);
    PY_TYPE_ADD_CONST(ViewFaceModifier, "kPivotTumple", plViewFaceModifier::kPivotTumple);
    PY_TYPE_ADD_CONST(ViewFaceModifier, "kScale", plViewFaceModifier::kScale);
    PY_TYPE_ADD_CONST(ViewFaceModifier, "kFaceCam", plViewFaceModifier::kFaceCam);
    PY_TYPE_ADD_CONST(ViewFaceModifier, "kFaceList", plViewFaceModifier::kFaceList);
    PY_TYPE_ADD_CONST(ViewFaceModifier, "kFacePlay", plViewFaceModifier::kFacePlay);
    PY_TYPE_ADD_CONST(ViewFaceModifier, "kFaceObj", plViewFaceModifier::kFaceObj);
    PY_TYPE_ADD_CONST(ViewFaceModifier, "kOffset", plViewFaceModifier::kOffset);
    PY_TYPE_ADD_CONST(ViewFaceModifier, "kOffsetLocal", plViewFaceModifier::kOffsetLocal);
    PY_TYPE_ADD_CONST(ViewFaceModifier, "kMaxBounds", plViewFaceModifier::kMaxBounds);

    Py_INCREF(&pyViewFaceModifier_Type);
    return (PyObject*)&pyViewFaceModifier_Type;
}

PY_PLASMA_IFC_METHODS(ViewFaceModifier, plViewFaceModifier)
