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

extern "C" {

PY_PLASMA_DEALLOC(SpanTemplateVertex)
PY_PLASMA_EMPTY_INIT(SpanTemplateVertex)
PY_PLASMA_NEW(SpanTemplateVertex, plSpanTemplate::Vertex)

static PyObject* pySpanTemplateVertex_getUVWs(pySpanTemplateVertex* self, void*) {
    PyObject* list = PyList_New(10);
    for (size_t i=0; i<10; i++)
        PyList_SET_ITEM(list, i, pyVector3_FromVector3(self->fThis->fUVWs[i]));
    return list;
}

static PyObject* pySpanTemplateVertex_getWeights(pySpanTemplateVertex* self, void*) {
    PyObject* list = PyList_New(3);
    for (size_t i=0; i<3; i++)
        PyList_SET_ITEM(list, i, PyFloat_FromDouble(self->fThis->fWeights[i]));
    return list;
}

static int pySpanTemplateVertex_setUVWs(pySpanTemplateVertex* self, PyObject* value, void*) {
    std::vector<hsVector3> uvws;
    if (value == NULL || !PyList_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "UVWs should be a list of up to 10 hsVector3 objects");
        return -1;
    }
    uvws.resize(PyList_Size(value));
    if (uvws.size() > 10) {
        PyErr_SetString(PyExc_RuntimeError, "UVWs should be a list of up to 10 hsVector3 objects");
        return -1;
    }
    for (size_t i=0; i<uvws.size(); i++) {
        PyObject* itm = PyList_GetItem(value, i);
        if (!pyVector3_Check(itm)) {
            PyErr_SetString(PyExc_TypeError, "UVWs should be a list of up to 10 hsVector3 objects");
            return -1;
        }
        uvws[i] = *((pyVector3*)itm)->fThis;
    }
    for (size_t i=0; i<uvws.size(); i++)
        self->fThis->fUVWs[i] = uvws[i];
    for (size_t i=uvws.size(); i<10; i++)
        self->fThis->fUVWs[i] = hsVector3(0.0f, 0.0f, 0.0f);
    return 0;
}

static int pySpanTemplateVertex_setWeights(pySpanTemplateVertex* self, PyObject* value, void*) {
    std::vector<float> weights;
    if (value == NULL || !PyList_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "weights should be a list of up to 3 floats");
        return -1;
    }
    weights.resize(PyList_Size(value));
    if (weights.size() > 3) {
        PyErr_SetString(PyExc_RuntimeError, "weights should be a list of up to 3 floats");
        return -1;
    }
    for (size_t i=0; i<weights.size(); i++) {
        PyObject* itm = PyList_GetItem(value, i);
        if (!PyFloat_Check(itm)) {
            PyErr_SetString(PyExc_TypeError, "weights should be a list of up to 3 floats");
            return -1;
        }
        weights[i] = PyFloat_AsDouble(itm);
    }
    for (size_t i=0; i<weights.size(); i++)
        self->fThis->fWeights[i] = weights[i];
    for (size_t i=weights.size(); i<3; i++)
        self->fThis->fWeights[i] = 0.0f;
    return 0;
}

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
    { _pycs("UVWs"), (getter)pySpanTemplateVertex_getUVWs,
        (setter)pySpanTemplateVertex_setUVWs, NULL, NULL },
    { _pycs("weights"), (getter)pySpanTemplateVertex_getWeights,
        (setter)pySpanTemplateVertex_setWeights, NULL, NULL },
    PY_GETSET_TERMINATOR
};

PyTypeObject pySpanTemplateVertex_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plSpanTemplateVertex",  /* tp_name */
    sizeof(pySpanTemplateVertex),       /* tp_basicsize */
    0,                                  /* tp_itemsize */

    pySpanTemplateVertex_dealloc,       /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_compare */
    NULL,                               /* tp_repr */
    NULL,                               /* tp_as_number */
    NULL,                               /* tp_as_sequence */
    NULL,                               /* tp_as_mapping */
    NULL,                               /* tp_hash */
    NULL,                               /* tp_call */
    NULL,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */

    Py_TPFLAGS_DEFAULT,                 /* tp_flags */
    "plSpanTemplate::Vertex wrapper",   /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pySpanTemplateVertex_GetSet,        /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    pySpanTemplateVertex___init__,      /* tp_init */
    NULL,                               /* tp_alloc */
    pySpanTemplateVertex_new,           /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */

    NULL,                               /* tp_del */
    TP_VERSION_TAG_INIT                 /* tp_version_tag */
    TP_FINALIZE_INIT                    /* tp_finalize */
};

PyObject* Init_pySpanTemplateVertex_Type() {
    if (PyType_Ready(&pySpanTemplateVertex_Type) < 0)
        return NULL;

    Py_INCREF(&pySpanTemplateVertex_Type);
    return (PyObject*)&pySpanTemplateVertex_Type;
}

PY_PLASMA_IFC_METHODS(SpanTemplateVertex, plSpanTemplate::Vertex)

}
