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

#include "pyLightInfo.h"

#include <PRP/Light/plDirectionalLightInfo.h>
#include "PRP/pyCreatable.h"

PY_PLASMA_NEW(LimitedDirLightInfo, plLimitedDirLightInfo)

PY_PROPERTY(float, LimitedDirLightInfo, width, getWidth, setWidth)
PY_PROPERTY(float, LimitedDirLightInfo, height, getHeight, setHeight)
PY_PROPERTY(float, LimitedDirLightInfo, depth, getDepth, setDepth)

static PyGetSetDef pyLimitedDirLightInfo_GetSet[] = {
    pyLimitedDirLightInfo_width_getset,
    pyLimitedDirLightInfo_height_getset,
    pyLimitedDirLightInfo_depth_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(LimitedDirLightInfo, plLimitedDirLightInfo,
               "plLimitedDirLightInfo wrapper")

PY_PLASMA_TYPE_INIT(LimitedDirLightInfo)
{
    pyLimitedDirLightInfo_Type.tp_new = pyLimitedDirLightInfo_new;
    pyLimitedDirLightInfo_Type.tp_getset = pyLimitedDirLightInfo_GetSet;
    pyLimitedDirLightInfo_Type.tp_base = &pyDirectionalLightInfo_Type;
    if (PyType_CheckAndReady(&pyLimitedDirLightInfo_Type) < 0)
        return nullptr;

    Py_INCREF(&pyLimitedDirLightInfo_Type);
    return (PyObject*)&pyLimitedDirLightInfo_Type;
}

PY_PLASMA_IFC_METHODS(LimitedDirLightInfo, plLimitedDirLightInfo)
