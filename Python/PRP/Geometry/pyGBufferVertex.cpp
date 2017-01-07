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

extern "C" {

PY_PLASMA_VALUE_DEALLOC(GBufferVertex)
PY_PLASMA_EMPTY_INIT(GBufferVertex)
PY_PLASMA_VALUE_NEW(GBufferVertex, plGBufferVertex)

static PyObject* pyGBufferVertex_getWeights(pyGBufferVertex* self, void*) {
    PyObject* list = PyList_New(3);
    PyList_SET_ITEM(list, 0, pyPlasma_convert(self->fThis->fSkinWeights[0]));
    PyList_SET_ITEM(list, 1, pyPlasma_convert(self->fThis->fSkinWeights[1]));
    PyList_SET_ITEM(list, 2, pyPlasma_convert(self->fThis->fSkinWeights[2]));
    return list;
}

static PyObject* pyGBufferVertex_getUVWs(pyGBufferVertex* self, void*) {
    PyObject* list = PyList_New(10);
    for (size_t i=0; i<10; i++)
        PyList_SET_ITEM(list, i, pyVector3_FromVector3(self->fThis->fUVWs[i]));
    return list;
}

static int pyGBufferVertex_setWeights(pyGBufferVertex* self, PyObject* value, void*) {
    if (value != NULL && !PyList_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "weights should be a list of up to 3 floats");
        return -1;
    }
    int size = (value == NULL) ? 0 : PyList_Size(value);
    if (size > 3) {
        PyErr_SetString(PyExc_RuntimeError, "weights should be a list of up to 3 floats");
        return -1;
    }
    for (int i=0; i<size; i++) {
        if (!PyFloat_Check(PyList_GetItem(value, i))) {
            PyErr_SetString(PyExc_TypeError, "weights should be a list of up to 3 floats");
            return -1;
        }
        self->fThis->fSkinWeights[i] = PyFloat_AsDouble(PyList_GetItem(value, i));
    }
    for (int i=size; i<3; i++)
        self->fThis->fSkinWeights[i] = 0.0f;
    return 0;
}

static int pyGBufferVertex_setUVWs(pyGBufferVertex* self, PyObject* value, void*) {
    if (value != NULL && !PyList_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "UVWs should be a list of up to 10 hsVector3s");
        return -1;
    }
    int size = (value == NULL) ? 0 : PyList_Size(value);
    if (size > 10) {
        PyErr_SetString(PyExc_RuntimeError, "UVWs should be a list of up to 10 hsVector3s");
        return -1;
    }
    for (int i=0; i<size; i++) {
        if (!pyVector3_Check(PyList_GetItem(value, i))) {
            PyErr_SetString(PyExc_TypeError, "UVWs should be a list of up to 10 hsVector3s");
            return -1;
        }
        self->fThis->fUVWs[i] = *((pyVector3*)PyList_GetItem(value, i))->fThis;
    }
    for (int i=size; i<10; i++)
        self->fThis->fUVWs[i] = hsVector3(0.0f, 0.0f, 0.0f);
    return 0;
}

PY_PROPERTY_MEMBER(hsVector3, GBufferVertex, pos, fPos)
PY_PROPERTY_MEMBER(hsVector3, GBufferVertex, normal, fNormal)
PY_PROPERTY_MEMBER(int, GBufferVertex, skinIdx, fSkinIdx)
PY_PROPERTY_MEMBER(unsigned int, GBufferVertex, color, fColor)

static PyGetSetDef pyGBufferVertex_GetSet[] = {
    pyGBufferVertex_pos_getset,
    pyGBufferVertex_normal_getset,
    pyGBufferVertex_skinIdx_getset,
    pyGBufferVertex_color_getset,
    { _pycs("skinWeights"), (getter)pyGBufferVertex_getWeights,
        (setter)pyGBufferVertex_setWeights, NULL, NULL },
    { _pycs("UVWs"), (getter)pyGBufferVertex_getUVWs,
        (setter)pyGBufferVertex_setUVWs, NULL, NULL },
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(GBufferVertex, plGBufferVertex, "plGBufferVertex wrapper")

PY_PLASMA_TYPE_INIT(GBufferVertex) {
    pyGBufferVertex_Type.tp_dealloc = pyGBufferVertex_dealloc;
    pyGBufferVertex_Type.tp_init = pyGBufferVertex___init__;
    pyGBufferVertex_Type.tp_new = pyGBufferVertex_new;
    pyGBufferVertex_Type.tp_getset = pyGBufferVertex_GetSet;
    if (PyType_Ready(&pyGBufferVertex_Type) < 0)
        return NULL;

    Py_INCREF(&pyGBufferVertex_Type);
    return (PyObject*)&pyGBufferVertex_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(GBufferVertex, plGBufferVertex)

}
