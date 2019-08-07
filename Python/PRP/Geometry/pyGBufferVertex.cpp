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

#include "pyGBufferGroup.h"

#include <PRP/Geometry/plGBufferGroup.h>
#include "Math/pyGeometry3.h"

PY_PLASMA_VALUE_DEALLOC(GBufferVertex)
PY_PLASMA_EMPTY_INIT(GBufferVertex)
PY_PLASMA_VALUE_NEW(GBufferVertex, plGBufferVertex)

PY_GETSET_GETTER_DECL(GBufferVertex, skinWeights)
{
    PyObject* list = PyTuple_New(3);
    PyTuple_SET_ITEM(list, 0, pyPlasma_convert(self->fThis->fSkinWeights[0]));
    PyTuple_SET_ITEM(list, 1, pyPlasma_convert(self->fThis->fSkinWeights[1]));
    PyTuple_SET_ITEM(list, 2, pyPlasma_convert(self->fThis->fSkinWeights[2]));
    return list;
}

PY_GETSET_SETTER_DECL(GBufferVertex, skinWeights)
{
    PY_PROPERTY_CHECK_NULL(weights)
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "skinWeights should be a sequence of up to 3 floats");
        return -1;
    }
    Py_ssize_t size = seq.size();
    if (size > 3) {
        PyErr_SetString(PyExc_RuntimeError, "skinWeights should be a sequence of up to 3 floats");
        return -1;
    }
    for (Py_ssize_t i=0; i<size; i++) {
        PyObject* item = seq.get(i);
        if (!pyPlasma_check<float>(item)) {
            PyErr_SetString(PyExc_TypeError, "skinWeights should be a sequence of up to 3 floats");
            return -1;
        }
        self->fThis->fSkinWeights[i] = pyPlasma_get<float>(item);
    }
    for (Py_ssize_t i=size; i<3; i++)
        self->fThis->fSkinWeights[i] = 0.0f;
    return 0;
}

PY_PROPERTY_GETSET_DECL(GBufferVertex, skinWeights)

PY_GETSET_GETTER_DECL(GBufferVertex, UVWs)
{
    PyObject* list = PyTuple_New(10);
    for (size_t i=0; i<10; i++)
        PyTuple_SET_ITEM(list, i, pyVector3_FromVector3(self->fThis->fUVWs[i]));
    return list;
}

PY_GETSET_SETTER_DECL(GBufferVertex, UVWs)
{
    PY_PROPERTY_CHECK_NULL(UVWs)
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "UVWs should be a sequence of up to 10 hsVector3s");
        return -1;
    }
    Py_ssize_t size = seq.size();
    if (size > 10) {
        PyErr_SetString(PyExc_RuntimeError, "UVWs should be a sequence of up to 10 hsVector3s");
        return -1;
    }
    for (Py_ssize_t i=0; i<size; i++) {
        PyObject* item = seq.get(i);
        if (!pyPlasma_check<hsVector3>(item)) {
            PyErr_SetString(PyExc_TypeError, "UVWs should be a sequence of up to 10 hsVector3s");
            return -1;
        }
        self->fThis->fUVWs[i] = pyPlasma_get<hsVector3>(item);
    }
    for (Py_ssize_t i=size; i<10; i++)
        self->fThis->fUVWs[i] = hsVector3(0.0f, 0.0f, 0.0f);
    return 0;
}

PY_PROPERTY_GETSET_DECL(GBufferVertex, UVWs)

PY_PROPERTY_MEMBER(hsVector3, GBufferVertex, pos, fPos)
PY_PROPERTY_MEMBER(hsVector3, GBufferVertex, normal, fNormal)
PY_PROPERTY_MEMBER(int, GBufferVertex, skinIdx, fSkinIdx)
PY_PROPERTY_MEMBER(unsigned int, GBufferVertex, color, fColor)

static PyGetSetDef pyGBufferVertex_GetSet[] = {
    pyGBufferVertex_pos_getset,
    pyGBufferVertex_normal_getset,
    pyGBufferVertex_skinIdx_getset,
    pyGBufferVertex_color_getset,
    pyGBufferVertex_skinWeights_getset,
    pyGBufferVertex_UVWs_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(GBufferVertex, plGBufferVertex, "plGBufferVertex wrapper")

PY_PLASMA_TYPE_INIT(GBufferVertex)
{
    pyGBufferVertex_Type.tp_dealloc = pyGBufferVertex_dealloc;
    pyGBufferVertex_Type.tp_init = pyGBufferVertex___init__;
    pyGBufferVertex_Type.tp_new = pyGBufferVertex_new;
    pyGBufferVertex_Type.tp_getset = pyGBufferVertex_GetSet;
    if (PyType_CheckAndReady(&pyGBufferVertex_Type) < 0)
        return nullptr;

    Py_INCREF(&pyGBufferVertex_Type);
    return (PyObject*)&pyGBufferVertex_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(GBufferVertex, plGBufferVertex)
