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

PY_GETSET_GETTER_DECL(DISpanIndex, indices)
{
    PyObject* list = PyTuple_New(self->fThis->fIndices.size());
    for (size_t i=0; i<self->fThis->fIndices.size(); i++)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(self->fThis->fIndices[i]));
    return list;
}

PY_GETSET_SETTER_DECL(DISpanIndex, indices)
{
    PY_PROPERTY_CHECK_NULL(indices)
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "indices should be a list of ints");
        return -1;
    }
    self->fThis->fIndices.resize(seq.size());
    for (size_t i=0; i<self->fThis->fIndices.size(); i++) {
        PyObject* item = seq.get(i);
        if (!pyPlasma_check<unsigned int>(item)) {
            PyErr_SetString(PyExc_TypeError, "indices should be a list of ints");
            return -1;
        }
        self->fThis->fIndices[i] = pyPlasma_get<unsigned int>(item);
    }
    return 0;
}

PY_PROPERTY_GETSET_DECL(DISpanIndex, indices)

PY_PROPERTY_MEMBER(uint8_t, DISpanIndex, flags, fFlags)

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
