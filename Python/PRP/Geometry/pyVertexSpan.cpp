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

#include "pySpan.h"

#include <PRP/Geometry/plVertexSpan.h>

PY_PLASMA_NEW(VertexSpan, plVertexSpan)

PY_PROPERTY(unsigned int, VertexSpan, groupIdx, getGroupIdx, setGroupIdx)
PY_PROPERTY(unsigned int, VertexSpan, VBufferIdx, getVBufferIdx, setVBufferIdx)
PY_PROPERTY(unsigned int, VertexSpan, cellIdx, getCellIdx, setCellIdx)
PY_PROPERTY(unsigned int, VertexSpan, cellOffset, getCellOffset, setCellOffset)
PY_PROPERTY(unsigned int, VertexSpan, VStartIdx, getVStartIdx, setVStartIdx)
PY_PROPERTY(unsigned int, VertexSpan, VLength, getVLength, setVLength)

static PyGetSetDef pyVertexSpan_GetSet[] = {
    pyVertexSpan_groupIdx_getset,
    pyVertexSpan_VBufferIdx_getset,
    pyVertexSpan_cellIdx_getset,
    pyVertexSpan_cellOffset_getset,
    pyVertexSpan_VStartIdx_getset,
    pyVertexSpan_VLength_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(VertexSpan, plVertexSpan, "plVertexSpan wrapper")

PY_PLASMA_TYPE_INIT(VertexSpan)
{
    pyVertexSpan_Type.tp_new = pyVertexSpan_new;
    pyVertexSpan_Type.tp_getset = pyVertexSpan_GetSet;
    pyVertexSpan_Type.tp_base = &pySpan_Type;
    if (PyType_CheckAndReady(&pyVertexSpan_Type) < 0)
        return nullptr;

    Py_INCREF(&pyVertexSpan_Type);
    return (PyObject*)&pyVertexSpan_Type;
}

PY_PLASMA_IFC_METHODS(VertexSpan, plVertexSpan)
