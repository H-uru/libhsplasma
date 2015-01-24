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
#include <PRP/Geometry/plSpanTemplate.h>
#include "pySpanTemplate.h"
#include "Math/pyGeometry3.h"

extern "C" {

static void pySpanTemplateVertex_dealloc(pySpanTemplateVertex* self) {
    if (self->fPyOwned)
        delete self->fThis;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static int pySpanTemplateVertex___init__(pySpanTemplateVertex* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pySpanTemplateVertex_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pySpanTemplateVertex* self = (pySpanTemplateVertex*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plSpanTemplate::Vertex();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pySpanTemplateVertex_getPosition(pySpanTemplateVertex* self, void*) {
    return pyVector3_FromVector3(self->fThis->fPosition);
}

static PyObject* pySpanTemplateVertex_getNormal(pySpanTemplateVertex* self, void*) {
    return pyVector3_FromVector3(self->fThis->fNormal);
}

static PyObject* pySpanTemplateVertex_getColor1(pySpanTemplateVertex* self, void*) {
    return PyInt_FromLong(self->fThis->fColor1);
}

static PyObject* pySpanTemplateVertex_getColor2(pySpanTemplateVertex* self, void*) {
    return PyInt_FromLong(self->fThis->fColor2);
}

static PyObject* pySpanTemplateVertex_getWeight(pySpanTemplateVertex* self, void*) {
    return PyInt_FromLong(self->fThis->fWeightIdx);
}

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

static int pySpanTemplateVertex_setPosition(pySpanTemplateVertex* self, PyObject* value, void*) {
    if (value == NULL || !pyVector3_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "position should be an hsVector3");
        return -1;
    }
    self->fThis->fPosition = *((pyVector3*)value)->fThis;
    return 0;
}

static int pySpanTemplateVertex_setNormal(pySpanTemplateVertex* self, PyObject* value, void*) {
    if (value == NULL || !pyVector3_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "normalll should be an hsVector3");
        return -1;
    }
    self->fThis->fNormal = *((pyVector3*)value)->fThis;
    return 0;
}

static int pySpanTemplateVertex_setColor1(pySpanTemplateVertex* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "color1 should be an int");
        return -1;
    }
    self->fThis->fColor1 = PyInt_AsLong(value);
    return 0;
}

static int pySpanTemplateVertex_setColor2(pySpanTemplateVertex* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "color2 should be an int");
        return -1;
    }
    self->fThis->fColor2 = PyInt_AsLong(value);
    return 0;
}

static int pySpanTemplateVertex_setWeight(pySpanTemplateVertex* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "weightIdx should be an int");
        return -1;
    }
    self->fThis->fWeightIdx = PyInt_AsLong(value);
    return 0;
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

static PyGetSetDef pySpanTemplateVertex_GetSet[] = {
    { _pycs("position"), (getter)pySpanTemplateVertex_getPosition,
        (setter)pySpanTemplateVertex_setPosition, NULL, NULL },
    { _pycs("normal"), (getter)pySpanTemplateVertex_getNormal,
        (setter)pySpanTemplateVertex_setNormal, NULL, NULL },
    { _pycs("color1"), (getter)pySpanTemplateVertex_getColor1,
        (setter)pySpanTemplateVertex_setColor1, NULL, NULL },
    { _pycs("color2"), (getter)pySpanTemplateVertex_getColor2,
        (setter)pySpanTemplateVertex_setColor2, NULL, NULL },
    { _pycs("weightIdx"), (getter)pySpanTemplateVertex_getWeight,
        (setter)pySpanTemplateVertex_setWeight, NULL, NULL },
    { _pycs("UVWs"), (getter)pySpanTemplateVertex_getUVWs,
        (setter)pySpanTemplateVertex_setUVWs, NULL, NULL },
    { _pycs("weights"), (getter)pySpanTemplateVertex_getWeights,
        (setter)pySpanTemplateVertex_setWeights, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pySpanTemplateVertex_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plSpanTemplateVertex",  /* tp_name */
    sizeof(pySpanTemplateVertex),       /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pySpanTemplateVertex_dealloc, /* tp_dealloc */
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

    (initproc)pySpanTemplateVertex___init__,  /* tp_init */
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

int pySpanTemplateVertex_Check(PyObject* obj) {
    if (obj->ob_type == &pySpanTemplateVertex_Type
        || PyType_IsSubtype(obj->ob_type, &pySpanTemplateVertex_Type))
        return 1;
    return 0;
}

PyObject* pySpanTemplateVertex_FromVertex(plSpanTemplate::Vertex& vert) {
    pySpanTemplateVertex* obj = PyObject_New(pySpanTemplateVertex, &pySpanTemplateVertex_Type);
    obj->fThis = &vert;
    obj->fPyOwned = false;
    return (PyObject*)obj;
}

}
