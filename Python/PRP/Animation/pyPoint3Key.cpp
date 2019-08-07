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

#include "pyKeys.h"

#include <PRP/Animation/hsKeys.h>
#include "Math/pyGeometry3.h"

PY_PLASMA_EMPTY_INIT(Point3Key)
PY_PLASMA_NEW(Point3Key, hsPoint3Key)

PY_PROPERTY_MEMBER(hsVector3, Point3Key, inTan, fInTan)
PY_PROPERTY_MEMBER(hsVector3, Point3Key, outTan, fOutTan)
PY_PROPERTY_MEMBER(hsVector3, Point3Key, value, fValue)

static PyGetSetDef pyPoint3Key_GetSet[] = {
    pyPoint3Key_inTan_getset,
    pyPoint3Key_outTan_getset,
    pyPoint3Key_value_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(Point3Key, hsPoint3Key, "hsPoint3Key wrapper")

PY_PLASMA_TYPE_INIT(Point3Key)
{
    pyPoint3Key_Type.tp_init = pyPoint3Key___init__;
    pyPoint3Key_Type.tp_new = pyPoint3Key_new;
    pyPoint3Key_Type.tp_getset = pyPoint3Key_GetSet;
    pyPoint3Key_Type.tp_base = &pyKeyFrame_Type;
    if (PyType_CheckAndReady(&pyPoint3Key_Type) < 0)
        return nullptr;

    Py_INCREF(&pyPoint3Key_Type);
    return (PyObject*)&pyPoint3Key_Type;
}

PY_PLASMA_IFC_METHODS(Point3Key, hsPoint3Key)
