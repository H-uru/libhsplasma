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

#include "pyDrawableSpans.h"

#include <PRP/Geometry/plDrawableSpans.h>

PY_PLASMA_VALUE_DEALLOC(DISpanIndex)
PY_PLASMA_EMPTY_INIT(DISpanIndex)
PY_PLASMA_VALUE_NEW(DISpanIndex, plDISpanIndex)

PY_PROPERTY_MEMBER(uint8_t, DISpanIndex, flags, fFlags)
PY_PROPERTY_MEMBER_VECTOR(unsigned int, DISpanIndex, indices, fIndices)

static PyGetSetDef pyDISpanIndex_GetSet[] = {
    pyDISpanIndex_flags_getset,
    pyDISpanIndex_indices_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(DISpanIndex, plDISpanIndex, "plDISpanIndex wrapper")

PY_PLASMA_TYPE_INIT(DISpanIndex)
{
    pyDISpanIndex_Type.tp_dealloc = pyDISpanIndex_dealloc;
    pyDISpanIndex_Type.tp_init = pyDISpanIndex___init__;
    pyDISpanIndex_Type.tp_new = pyDISpanIndex_new;
    pyDISpanIndex_Type.tp_getset = pyDISpanIndex_GetSet;
    if (PyType_CheckAndReady(&pyDISpanIndex_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(DISpanIndex, "kNone", plDISpanIndex::kNone);
    PY_TYPE_ADD_CONST(DISpanIndex, "kMatrixOnly", plDISpanIndex::kMatrixOnly);
    PY_TYPE_ADD_CONST(DISpanIndex, "kDontTransformSpans", plDISpanIndex::kDontTransformSpans);

    Py_INCREF(&pyDISpanIndex_Type);
    return (PyObject*)&pyDISpanIndex_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(DISpanIndex, plDISpanIndex)
