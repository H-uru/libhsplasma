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

#include "pyRenderTarget.h"

#include <PRP/Surface/plRenderTarget.h>
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW(CubicRenderTarget, plCubicRenderTarget)

/* These are proxies to render target objects in the CRT, so they cannot be set */
#define CRT_FACE(propName, faceName)                                    \
    PY_GETSET_GETTER_DECL(CubicRenderTarget, propName)                  \
    {                                                                   \
        return ICreate(self->fThis->getFace(plCubicRenderTarget::k##faceName##Face)); \
    }                                                                   \
    PY_PROPERTY_GETSET_RO_DECL(CubicRenderTarget, propName)

CRT_FACE(leftFace, Left)
CRT_FACE(rightFace, Right)
CRT_FACE(frontFace, Front)
CRT_FACE(backFace, Back)
CRT_FACE(topFace, Top)
CRT_FACE(bottomFace, Bottom)

PY_GETSET_GETTER_DECL(CubicRenderTarget, faces)
{
    PyObject* facesTuple = PyTuple_New(plCubicRenderTarget::kNumFaces);
    for (size_t i = 0; i < plCubicRenderTarget::kNumFaces; ++i) {
        plRenderTarget* rt = self->fThis->getFace(i);
        PyTuple_SET_ITEM(facesTuple, i, ICreate(rt));
    }
    return facesTuple;
}

PY_PROPERTY_GETSET_RO_DECL(CubicRenderTarget, faces)

static PyGetSetDef pyCubicRenderTarget_GetSet[] = {
    pyCubicRenderTarget_leftFace_getset,
    pyCubicRenderTarget_rightFace_getset,
    pyCubicRenderTarget_frontFace_getset,
    pyCubicRenderTarget_backFace_getset,
    pyCubicRenderTarget_topFace_getset,
    pyCubicRenderTarget_bottomFace_getset,
    pyCubicRenderTarget_faces_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(CubicRenderTarget, plCubicRenderTarget, "plCubicRenderTarget wrapper")

PY_PLASMA_TYPE_INIT(CubicRenderTarget)
{
    pyCubicRenderTarget_Type.tp_new = pyCubicRenderTarget_new;
    pyCubicRenderTarget_Type.tp_getset = pyCubicRenderTarget_GetSet;
    pyCubicRenderTarget_Type.tp_base = &pyRenderTarget_Type;
    if (PyType_CheckAndReady(&pyCubicRenderTarget_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(CubicRenderTarget, "kLeftFace", plCubicRenderTarget::kLeftFace);
    PY_TYPE_ADD_CONST(CubicRenderTarget, "kRightFace", plCubicRenderTarget::kRightFace);
    PY_TYPE_ADD_CONST(CubicRenderTarget, "kFrontFace", plCubicRenderTarget::kFrontFace);
    PY_TYPE_ADD_CONST(CubicRenderTarget, "kBackFace", plCubicRenderTarget::kBackFace);
    PY_TYPE_ADD_CONST(CubicRenderTarget, "kTopFace", plCubicRenderTarget::kTopFace);
    PY_TYPE_ADD_CONST(CubicRenderTarget, "kBottomFace", plCubicRenderTarget::kBottomFace);

    Py_INCREF(&pyCubicRenderTarget_Type);
    return (PyObject*)&pyCubicRenderTarget_Type;
}

PY_PLASMA_IFC_METHODS(CubicRenderTarget, plCubicRenderTarget)
