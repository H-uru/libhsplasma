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

#include "pySpanTemplate.h"

#include <PRP/Geometry/plSpanTemplate.h>
#include "Math/pyGeometry3.h"

PY_PLASMA_DEALLOC(SpanTemplateVertex)
PY_PLASMA_EMPTY_INIT(SpanTemplateVertex)
PY_PLASMA_NEW(SpanTemplateVertex, plSpanTemplate::Vertex)

PY_GETSET_GETTER_DECL(SpanTemplateVertex, UVWs)
{
    PyObject* list = PyTuple_New(10);
    for (size_t i=0; i<10; i++)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(self->fThis->fUVWs[i]));
    return list;
}

PY_GETSET_SETTER_DECL(SpanTemplateVertex, UVWs)
{
    PY_PROPERTY_CHECK_NULL(UVWs)
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "UVWs should be a sequence of up to 10 hsVector3 objects");
        return -1;
    }
    Py_ssize_t size = seq.size();
    if (size > 10) {
        PyErr_SetString(PyExc_RuntimeError, "UVWs should be a sequence of up to 10 hsVector3 objects");
        return -1;
    }
    for (Py_ssize_t i=0; i<size; i++) {
        PyObject* itm = seq.get(i);
        if (!pyPlasma_check<hsVector3>(itm)) {
            PyErr_SetString(PyExc_TypeError, "UVWs should be a sequence of up to 10 hsVector3 objects");
            return -1;
        }
        self->fThis->fUVWs[i] = pyPlasma_get<hsVector3>(itm);
    }
    for (Py_ssize_t i=size; i<10; i++)
        self->fThis->fUVWs[i] = hsVector3(0.0f, 0.0f, 0.0f);
    return 0;
}

PY_PROPERTY_GETSET_DECL(SpanTemplateVertex, UVWs)

PY_GETSET_GETTER_DECL(SpanTemplateVertex, weights)
{
    PyObject* list = PyTuple_New(3);
    for (size_t i=0; i<3; i++)
        PyTuple_SET_ITEM(list, i, pyPlasma_convert(self->fThis->fWeights[i]));
    return list;
}

PY_GETSET_SETTER_DECL(SpanTemplateVertex, weights)
{
    PY_PROPERTY_CHECK_NULL(weights)
    pySequenceFastRef seq(value);
    if (!seq.isSequence()) {
        PyErr_SetString(PyExc_TypeError, "weights should be a sequence of up to 3 floats");
        return -1;
    }
    Py_ssize_t size = seq.size();
    if (size > 3) {
        PyErr_SetString(PyExc_RuntimeError, "weights should be a sequence of up to 3 floats");
        return -1;
    }
    for (Py_ssize_t i=0; i<size; i++) {
        PyObject* itm = seq.get(i);
        if (!pyPlasma_check<float>(itm)) {
            PyErr_SetString(PyExc_TypeError, "weights should be a sequence of up to 3 floats");
            return -1;
        }
        self->fThis->fWeights[i] = pyPlasma_get<float>(itm);
    }
    for (Py_ssize_t i=size; i<3; i++)
        self->fThis->fWeights[i] = 0.0f;
    return 0;
}

PY_PROPERTY_GETSET_DECL(SpanTemplateVertex, weights)

PY_PROPERTY_MEMBER(hsVector3, SpanTemplateVertex, position, fPosition)
PY_PROPERTY_MEMBER(hsVector3, SpanTemplateVertex, normal, fNormal)
PY_PROPERTY_MEMBER(unsigned int, SpanTemplateVertex, color1, fColor1)
PY_PROPERTY_MEMBER(unsigned int, SpanTemplateVertex, color2, fColor2)
PY_PROPERTY_MEMBER(int, SpanTemplateVertex, weightIdx, fWeightIdx)

static PyGetSetDef pySpanTemplateVertex_GetSet[] = {
    pySpanTemplateVertex_position_getset,
    pySpanTemplateVertex_normal_getset,
    pySpanTemplateVertex_color1_getset,
    pySpanTemplateVertex_color2_getset,
    pySpanTemplateVertex_weightIdx_getset,
    pySpanTemplateVertex_UVWs_getset,
    pySpanTemplateVertex_weights_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(SpanTemplateVertex, plSpanTemplateVertex, "plSpanTemplate::Vertex wrapper")

PY_PLASMA_TYPE_INIT(SpanTemplateVertex)
{
    pySpanTemplateVertex_Type.tp_dealloc = pySpanTemplateVertex_dealloc;
    pySpanTemplateVertex_Type.tp_init = pySpanTemplateVertex___init__;
    pySpanTemplateVertex_Type.tp_new = pySpanTemplateVertex_new;
    pySpanTemplateVertex_Type.tp_getset = pySpanTemplateVertex_GetSet;
    if (PyType_CheckAndReady(&pySpanTemplateVertex_Type) < 0)
        return nullptr;

    Py_INCREF(&pySpanTemplateVertex_Type);
    return (PyObject*)&pySpanTemplateVertex_Type;
}

PY_PLASMA_IFC_METHODS(SpanTemplateVertex, plSpanTemplate::Vertex)
