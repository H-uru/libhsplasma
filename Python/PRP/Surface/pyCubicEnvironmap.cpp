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

#include "pyCubicEnvironmap.h"

#include <PRP/Surface/plCubicEnvironmap.h>
#include "PRP/pyCreatable.h"
#include "pyBitmap.h"

PY_PLASMA_NEW(CubicEnvironmap, plCubicEnvironmap)

#define CEM_FACE(propName, faceName)                                    \
    PY_GETSET_GETTER_DECL(CubicEnvironmap, propName)                    \
    {                                                                   \
        return ICreate(self->fThis->getFace(plCubicEnvironmap::Faces::k##faceName##Face)); \
    }                                                                   \
    PY_GETSET_SETTER_DECL(CubicEnvironmap, propName)                    \
    {                                                                   \
        PY_PROPERTY_CHECK_NULL(propName)                                \
        if (!pyMipmap_Check(value)) {                                   \
            PyErr_SetString(PyExc_TypeError, #propName " expected type plMipmap"); \
            return -1;                                                  \
        }                                                               \
        self->fThis->setFace(plCubicEnvironmap::Faces::k##faceName##Face, \
                             ((pyMipmap*)value)->fThis);                \
        return 0;                                                       \
    }                                                                   \
    PY_PROPERTY_GETSET_DECL(CubicEnvironmap, propName)

CEM_FACE(leftFace, Left)
CEM_FACE(rightFace, Right)
CEM_FACE(frontFace, Front)
CEM_FACE(backFace, Back)
CEM_FACE(topFace, Top)
CEM_FACE(bottomFace, Bottom)

static PyGetSetDef pyCubicEnvironmap_GetSet[] = {
    pyCubicEnvironmap_leftFace_getset,
    pyCubicEnvironmap_rightFace_getset,
    pyCubicEnvironmap_frontFace_getset,
    pyCubicEnvironmap_backFace_getset,
    pyCubicEnvironmap_topFace_getset,
    pyCubicEnvironmap_bottomFace_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(CubicEnvironmap, plCubicEnvironmap, "plCubicEnvironmap wrapper")

PY_PLASMA_TYPE_INIT(CubicEnvironmap)
{
    pyCubicEnvironmap_Type.tp_new = pyCubicEnvironmap_new;
    pyCubicEnvironmap_Type.tp_getset = pyCubicEnvironmap_GetSet;
    pyCubicEnvironmap_Type.tp_base = &pyBitmap_Type;
    if (PyType_CheckAndReady(&pyCubicEnvironmap_Type) < 0)
        return nullptr;

    Py_INCREF(&pyCubicEnvironmap_Type);
    return (PyObject*)&pyCubicEnvironmap_Type;
}

PY_PLASMA_IFC_METHODS(CubicEnvironmap, plCubicEnvironmap)
