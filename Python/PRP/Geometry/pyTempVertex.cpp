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

extern "C" {

static void pyTempVertex_dealloc(pyTempVertex* self) {
    delete self->fThis;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject* pyTempVertex_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyTempVertex* self = (pyTempVertex*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plGeometrySpan::TempVertex();
    }
    return (PyObject*)self;
}

static PyObject* pyTempVertex_getUVs(pyTempVertex* self, void*) {
    PyObject* list = PyList_New(8);
    for (size_t i = 0; i < 8; ++i)
        PyList_SET_ITEM(list, i, pyVector3_FromVector3(self->fThis->fUVs[i]));
    return list;
}

static PyObject* pyTempVertex_getWeights(pyTempVertex* self, void*) {
    PyObject* list = PyList_New(3);
    for (size_t i = 0; i < 3; ++i)
        PyList_SET_ITEM(list, i, PyFloat_FromDouble(self->fThis->fWeights[i]));
    return list;
}

static int pyTempVertex_setUVs(pyTempVertex* self, PyObject* value, void*) {
    if (value == NULL || !PySequence_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "uvs must be a sequence of hsVector3");
        return -1;
    }
    size_t size = (PySequence_Size(value) > 8) ? 8 : PySequence_Size(value);
    for (size_t i = 0; i < size; ++i) {
        if (!pyVector3_Check(PySequence_Fast_GET_ITEM(value, i))) {
            PyErr_SetString(PyExc_TypeError, "uvs must be a sequence of hsVector3");
            return -1;
        }
    }

    for (size_t i = 0; i < size; ++i)
        self->fThis->fUVs[i] = *((pyVector3*)PySequence_Fast_GET_ITEM(value, i))->fThis;
    return 0;
}

static int pyTempVertex_setWeights(pyTempVertex* self, PyObject* value, void*) {
    if (value == NULL || !PySequence_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "weights must be a sequence of floats");
        return -1;
    }
    size_t size = (PySequence_Size(value) > 3) ? 3 : PySequence_Size(value);
    for (size_t i = 0; i < size; ++i) {
        if (!PyFloat_Check(PySequence_Fast_GET_ITEM(value, i))) {
            PyErr_SetString(PyExc_TypeError, "weights must be a sequence of floats");
            return -1;
        }
    }

    for (size_t i = 0; i < size; ++i)
        self->fThis->fWeights[i] = PyFloat_AsDouble(PySequence_Fast_GET_ITEM(value, i));
    return 0;
}

PY_GETSET_GETTER_DECL(TempVertex, color) {
    return pyColor32_FromColor32(hsColor32(self->fThis->fColor));
}

PY_GETSET_SETTER_DECL(TempVertex, color) {
    if (value == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "color cannot be deleted");
        return -1;
    } else if (pyColor32_Check(value)) {
        self->fThis->fColor = ((pyColor32*)value)->fThis->color;
        return 0;
    } else if (PyInt_Check(value)) {
        self->fThis->fColor = PyInt_AsLong(value);
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
    { _pycs("uvs"), (getter)pyTempVertex_getUVs, (setter)pyTempVertex_setUVs, NULL, NULL },
    { _pycs("weights"), (getter)pyTempVertex_getWeights, (setter)pyTempVertex_setWeights, NULL, NULL },
    PY_GETSET_TERMINATOR
};

PyTypeObject pyTempVertex_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plGeometrySpan.TempVertex",/* tp_name */
    sizeof(pyTempVertex),               /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pyTempVertex_dealloc,   /* tp_dealloc */
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
    "TempVertex wrapper",               /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyTempVertex_GetSet,                /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyTempVertex_new,                   /* tp_new */
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

PyObject* Init_pyTempVertex_Type() {
    if (PyType_Ready(&pyTempVertex_Type) < 0)
        return NULL;

    Py_INCREF(&pyTempVertex_Type);
    return (PyObject*)&pyTempVertex_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(TempVertex, plGeometrySpan::TempVertex)

};
