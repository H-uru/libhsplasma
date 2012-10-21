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

#include <PyPlasma.h>
#include "pyTempVertex.h"
#include "Math/pyGeometry3.h"

extern "C" {

static PyObject* pyTempVertex_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyTempVertex* self = (pyTempVertex*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plGeometrySpan::TempVertex();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyTempVertex_getColor(pyTempVertex* self, void*) {
    return PyInt_FromLong(self->fThis->fColor);
}

static PyObject* pyTempVertex_getIndices(pyTempVertex* self, void*) {
    return PyInt_FromLong(self->fThis->fIndices);
}

static PyObject* pyTempVertex_getNormal(pyTempVertex* self, void*) {
    return pyVector3_FromVector3(self->fThis->fNormal);
}

static PyObject* pyTempVertex_getPosition(pyTempVertex* self, void*) {
    return pyVector3_FromVector3(self->fThis->fPosition);
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

static int pyTempVertex_setColor(pyTempVertex* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "weights must be an int");
        return -1;
    }
    self->fThis->fColor = PyInt_AsLong(value);
    return 0;
}

static int pyTempVertex_setIndices(pyTempVertex* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "indices must be an int");
        return -1;
    }
    self->fThis->fIndices = PyInt_AsLong(value);
    return 0;
}

static int pyTempVertex_setNormal(pyTempVertex* self, PyObject* value, void*) {
    if (value == NULL || !pyVector3_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "normal must be an hsVector3");
        return -1;
    }
    self->fThis->fNormal = *((pyVector3*)self)->fThis;
    return 0;
}

static int pyTempVertex_setPosition(pyTempVertex* self, PyObject* value, void*) {
    if (value == NULL || !pyVector3_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "position must be an hsVector3");
        return -1;
    }
    self->fThis->fPosition = *((pyVector3*)self)->fThis;
    return 0;
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

PyGetSetDef pyTempVertex_GetSet[] = {
    { _pycs("color"), (getter)pyTempVertex_getColor, (setter)pyTempVertex_setColor, NULL, NULL },
    { _pycs("indices"), (getter)pyTempVertex_getIndices, (setter)pyTempVertex_setIndices, NULL, NULL },
    { _pycs("normal"), (getter)pyTempVertex_getNormal, (setter)pyTempVertex_setNormal, NULL, NULL },
    { _pycs("position"), (getter)pyTempVertex_getPosition, (setter)pyTempVertex_setPosition, NULL, NULL },
    { _pycs("uvs"), (getter)pyTempVertex_getUVs, (setter)pyTempVertex_setUVs, NULL, NULL },
    { _pycs("weights"), (getter)pyTempVertex_getWeights, (setter)pyTempVertex_setWeights, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyTempVertex_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plGeometrySpan.TempVertex",/* tp_name */
    sizeof(pyTempVertex),                /* tp_basicsize */
    0,                                   /* tp_itemsize */

    NULL,                                /* tp_dealloc */
    NULL,                                /* tp_print */
    NULL,                                /* tp_getattr */
    NULL,                                /* tp_setattr */
    NULL,                                /* tp_compare */
    NULL,                                /* tp_repr */
    NULL,                                /* tp_as_number */
    NULL,                                /* tp_as_sequence */
    NULL,                                /* tp_as_mapping */
    NULL,                                /* tp_hash */
    NULL,                                /* tp_call */
    NULL,                                /* tp_str */
    NULL,                                /* tp_getattro */
    NULL,                                /* tp_setattro */
    NULL,                                /* tp_as_buffer */

    Py_TPFLAGS_DEFAULT,                  /* tp_flags */
    "TempVertex wrapper",                /* tp_doc */

    NULL,                                /* tp_traverse */
    NULL,                                /* tp_clear */
    NULL,                                /* tp_richcompare */
    0,                                   /* tp_weaklistoffset */
    NULL,                                /* tp_iter */
    NULL,                                /* tp_iternext */

    NULL,                                /* tp_methods */
    NULL,                                /* tp_members */
    pyTempVertex_GetSet,                 /* tp_getset */
    NULL,                                /* tp_base */
    NULL,                                /* tp_dict */
    NULL,                                /* tp_descr_get */
    NULL,                                /* tp_descr_set */
    0,                                   /* tp_dictoffset */

    NULL,                                /* tp_init */
    NULL,                                /* tp_alloc */
    pyTempVertex_new,                    /* tp_new */
    NULL,                                /* tp_free */
    NULL,                                /* tp_is_gc */

    NULL,                                /* tp_bases */
    NULL,                                /* tp_mro */
    NULL,                                /* tp_cache */
    NULL,                                /* tp_subclasses */
    NULL,                                /* tp_weaklist */

    NULL,                                /* tp_del */
    TP_VERSION_TAG_INIT                  /* tp_version_tag */
};

PyObject* Init_pyTempVertex_Type() {
    if (PyType_Ready(&pyTempVertex_Type) < 0)
        return NULL;

    Py_INCREF(&pyTempVertex_Type);
    return (PyObject*)&pyTempVertex_Type;
}


int pyTempVertex_Check(PyObject* obj) {
    if (obj->ob_type == &pyTempVertex_Type
        || PyType_IsSubtype(obj->ob_type, &pyTempVertex_Type))
        return 1;
    return 0;
}

PyObject* pyTempVertex_FromTempVertex(const struct plGeometrySpan::TempVertex& vertex) {
    pyTempVertex* pspan = PyObject_New(pyTempVertex, &pyTempVertex_Type);
    pspan->fThis = new plGeometrySpan::TempVertex(vertex);
    return (PyObject*)pspan;
}

};
