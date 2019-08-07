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

#include "pyTempVertex.h"

#include "Math/pyGeometry3.h"
#include "Sys/pyColor.h"

PY_PLASMA_VALUE_DEALLOC(TempVertex)
PY_PLASMA_VALUE_NEW(TempVertex, plGeometrySpan::TempVertex)

PY_GETSET_GETTER_DECL(TempVertex, uvs)
{
    PyObject* list = PyTuple_New(8);
    for (size_t i = 0; i < 8; ++i)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(self->fThis->fUVs[i]));
    return list;
}

PY_GETSET_SETTER_DECL(TempVertex, uvs)
{
    PY_PROPERTY_CHECK_NULL(uvs)
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "uvs must be a sequence of hsVector3");
        return -1;
    }
    Py_ssize_t size = (seq.size() > 8) ? 8 : seq.size();
    for (Py_ssize_t i = 0; i < size; ++i) {
        PyObject* uv = seq.get(i);
        if (!pyPlasma_check<hsVector3>(uv)) {
            PyErr_SetString(PyExc_TypeError, "uvs must be a sequence of hsVector3");
            return -1;
        }
        self->fThis->fUVs[i] = pyPlasma_get<hsVector3>(uv);
    }
    return 0;
}

PY_PROPERTY_GETSET_DECL(TempVertex, uvs)

PY_GETSET_GETTER_DECL(TempVertex, weights)
{
    PyObject* list = PyTuple_New(3);
    for (size_t i = 0; i < 3; ++i)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(self->fThis->fWeights[i]));
    return list;
}

PY_GETSET_SETTER_DECL(TempVertex, weights)
{
    PY_PROPERTY_CHECK_NULL(weights)
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "weights must be a sequence of floats");
        return -1;
    }
    Py_ssize_t size = (seq.size() > 3) ? 3 : seq.size();
    for (Py_ssize_t i = 0; i < size; ++i) {
        PyObject* weight = seq.get(i);
        if (!pyPlasma_check<float>(weight)) {
            PyErr_SetString(PyExc_TypeError, "weights must be a sequence of floats");
            return -1;
        }
        self->fThis->fWeights[i] = pyPlasma_get<float>(weight);
    }
    return 0;
}

PY_PROPERTY_GETSET_DECL(TempVertex, weights)

PY_GETSET_GETTER_DECL(TempVertex, color)
{
    return pyColor32_FromColor32(hsColor32(self->fThis->fColor));
}

PY_GETSET_SETTER_DECL(TempVertex, color)
{
    PY_PROPERTY_CHECK_NULL(color)
    if (pyColor32_Check(value)) {
        self->fThis->fColor = ((pyColor32*)value)->fThis->color;
        return 0;
    } else if (pyPlasma_check<unsigned int>(value)) {
        self->fThis->fColor = pyPlasma_get<unsigned int>(value);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "color must be an int or an hsColor32");
        return -1;
    }
}

PY_PROPERTY_GETSET_DECL(TempVertex, color)

PY_PROPERTY_MEMBER(unsigned int, TempVertex, indices, fIndices)
PY_PROPERTY_MEMBER(hsVector3, TempVertex, normal, fNormal)
PY_PROPERTY_MEMBER(hsVector3, TempVertex, position, fPosition)

PyGetSetDef pyTempVertex_GetSet[] = {
    pyTempVertex_color_getset,
    pyTempVertex_indices_getset,
    pyTempVertex_normal_getset,
    pyTempVertex_position_getset,
    pyTempVertex_uvs_getset,
    pyTempVertex_weights_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(TempVertex, plGeometrySpan.TempVertex, "plGeometrySpan::TempVertex wrapper")

PY_PLASMA_TYPE_INIT(TempVertex)
{
    pyTempVertex_Type.tp_dealloc = pyTempVertex_dealloc;
    pyTempVertex_Type.tp_new = pyTempVertex_new;
    pyTempVertex_Type.tp_getset = pyTempVertex_GetSet;
    if (PyType_CheckAndReady(&pyTempVertex_Type) < 0)
        return nullptr;

    Py_INCREF(&pyTempVertex_Type);
    return (PyObject*)&pyTempVertex_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(TempVertex, plGeometrySpan::TempVertex)
