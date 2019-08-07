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

PY_GETSET_GETTER_DECL(Icicle, sortData)
{
    int size = self->fThis->getILength() / 3;
    const plGBufferTriangle* sortData = self->fThis->getSortData();
    if (sortData == nullptr) {
        Py_RETURN_NONE;
    } else {
        PyObject* list = PyTuple_New(size);
        for (int i=0; i<size; i++)
            PyTuple_SET_ITEM(list, i, pyGBufferTriangle_FromGBufferTriangle(sortData[i]));
        return list;
    }
}

PY_GETSET_SETTER_DECL(Icicle, sortData)
{
    PY_PROPERTY_CHECK_NULL(sortData)
    if (value == Py_None) {
        self->fThis->setSortData(nullptr);
        return 0;
    }
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "sortData should be a sequence of plGBufferTriangles");
        return -1;
    }
    Py_ssize_t size = seq.size();
    std::vector<plGBufferTriangle> sortData(size);
    for (Py_ssize_t i=0; i<size; i++) {
        PyObject* item = seq.get(i);
        if (!pyGBufferTriangle_Check(item)) {
            PyErr_SetString(PyExc_TypeError, "sortData should be a sequence of plGBufferTriangles");
            return -1;
        }
        sortData[i] = *((pyGBufferTriangle*)item)->fThis;
    }
    self->fThis->setSortData(&sortData[0]);
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
