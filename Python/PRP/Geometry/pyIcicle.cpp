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

#include <PRP/Geometry/plIcicle.h>
#include "pyGBufferGroup.h"

PY_PLASMA_NEW(Icicle, plIcicle)

PY_PROPERTY_READ(Icicle, sortData, getSortDataVec)

PY_GETSET_SETTER_DECL(Icicle, sortData)
{
    if (value == nullptr || value == Py_None) {
        self->fThis->setSortData(nullptr);
        return 0;
    }

    pySequenceFastRef seq(value);
    if (!pyPlasma_check<std::vector<plGBufferTriangle>>(seq)) {
        PyErr_Format(PyExc_TypeError, "sortData expects an iterable of %u plGBufferTriangles",
                     self->fThis->getILength() / 3);
        return -1;
    }

    try {
        self->fThis->setSortData(pyPlasma_get<std::vector<plGBufferTriangle>>(seq));
    } catch (const hsBadParamException& ex) {
        PyErr_SetString(PyExc_ValueError, ex.what());
        return -1;
    }
    return 0;
}

PY_PROPERTY_GETSET_DECL(Icicle, sortData)

PY_PROPERTY(unsigned int, Icicle, IBufferIdx, getIBufferIdx, setIBufferIdx)
PY_PROPERTY(unsigned int, Icicle, IStartIdx, getIStartIdx, setIStartIdx)
PY_PROPERTY(unsigned int, Icicle, ILength, getILength, setILength)

static PyGetSetDef pyIcicle_GetSet[] = {
    pyIcicle_IBufferIdx_getset,
    pyIcicle_IStartIdx_getset,
    pyIcicle_ILength_getset,
    pyIcicle_sortData_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(Icicle, plIcicle, "plIcicle wrapper")

PY_PLASMA_TYPE_INIT(Icicle)
{
    pyIcicle_Type.tp_new = pyIcicle_new;
    pyIcicle_Type.tp_getset = pyIcicle_GetSet;
    pyIcicle_Type.tp_base = &pyVertexSpan_Type;
    if (PyType_CheckAndReady(&pyIcicle_Type) < 0)
        return nullptr;

    Py_INCREF(&pyIcicle_Type);
    return (PyObject*)&pyIcicle_Type;
}

PY_PLASMA_IFC_METHODS(Icicle, plIcicle)
