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

PY_PLASMA_EMPTY_INIT(G3DSMaxKeyFrame)
PY_PLASMA_NEW(G3DSMaxKeyFrame, hsG3DSMaxKeyFrame)

PY_PROPERTY_MEMBER(hsAffineParts, G3DSMaxKeyFrame, value, fValue)

static PyGetSetDef pyG3DSMaxKeyFrame_GetSet[] = {
    pyG3DSMaxKeyFrame_value_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(G3DSMaxKeyFrame, hsG3DSMaxKeyFrame, "hsG3DSMaxKeyFrame wrapper")

PY_PLASMA_TYPE_INIT(G3DSMaxKeyFrame)
{
    pyG3DSMaxKeyFrame_Type.tp_init = pyG3DSMaxKeyFrame___init__;
    pyG3DSMaxKeyFrame_Type.tp_new = pyG3DSMaxKeyFrame_new;
    pyG3DSMaxKeyFrame_Type.tp_getset = pyG3DSMaxKeyFrame_GetSet;
    pyG3DSMaxKeyFrame_Type.tp_base = &pyKeyFrame_Type;
    if (PyType_CheckAndReady(&pyG3DSMaxKeyFrame_Type) < 0)
        return nullptr;

    Py_INCREF(&pyG3DSMaxKeyFrame_Type);
    return (PyObject*)&pyG3DSMaxKeyFrame_Type;
}

PY_PLASMA_IFC_METHODS(G3DSMaxKeyFrame, hsG3DSMaxKeyFrame)
