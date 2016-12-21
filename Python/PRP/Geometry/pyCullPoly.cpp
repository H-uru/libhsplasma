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

#include "pyOccluder.h"

#include <PRP/Geometry/plCullPoly.h>
#include <Math/hsGeometry3.h>
#include "Math/pyGeometry3.h"

extern "C" {

static void pyCullPoly_dealloc(pyCullPoly* self) {
    delete self->fThis;
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static int pyCullPoly___init__(pyCullPoly* self, PyObject* args, PyObject* kwds) {
    if (!PyArg_ParseTuple(args, ""))
        return -1;
    return 0;
}

static PyObject* pyCullPoly_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyCullPoly* self = (pyCullPoly*)type->tp_alloc(type, 0);
    if (self != NULL)
        self->fThis = new plCullPoly();
    return (PyObject*)self;
}

static PyObject* pyCullPoly_getFlags(pyCullPoly* self, void*) {
    return PyInt_FromLong(self->fThis->getFlags());
}

static PyObject* pyCullPoly_getVerts(pyCullPoly* self, void*) {
    std::vector<hsVector3> verts = self->fThis->getVerts();
    PyObject* list = PyList_New(verts.size());
    for (size_t i=0; i<verts.size(); i++)
        PyList_SET_ITEM(list, i, pyVector3_FromVector3(verts[i]));
    return list;
}

static PyObject* pyCullPoly_getNorm(pyCullPoly* self, void*) {
    return pyVector3_FromVector3(self->fThis->getNorm());
}

static PyObject* pyCullPoly_getCenter(pyCullPoly* self, void*) {
    return pyVector3_FromVector3(self->fThis->getCenter());
}

static PyObject* pyCullPoly_getDist(pyCullPoly* self, void*) {
    return PyFloat_FromDouble(self->fThis->getDist());
}

static PyObject* pyCullPoly_getRadius(pyCullPoly* self, void*) {
    return PyFloat_FromDouble(self->fThis->getRadius());
}

static int pyCullPoly_setFlags(pyCullPoly* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "flags should be an int");
        return -1;
    }
    self->fThis->setFlags(PyInt_AsLong(value));
    return 0;
}

static int pyCullPoly_setVerts(pyCullPoly* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setVerts(std::vector<hsVector3>());
        return 0;
    }
    if (!PyList_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "verts should be a list of hsVector3s");
        return -1;
    }
    std::vector<hsVector3> verts(PyList_Size(value));
    for (size_t i=0; i<verts.size(); i++) {
        PyObject* item = PyList_GetItem(value, i);
        if (!pyVector3_Check(item)) {
            PyErr_SetString(PyExc_TypeError, "verts should be a list of hsVector3s");
            return -1;
        }
        verts[i] = *((pyVector3*)item)->fThis;
    }
    self->fThis->setVerts(verts);
    return 0;
}

static int pyCullPoly_setNorm(pyCullPoly* self, PyObject* value, void*) {
    if (value == NULL || !pyVector3_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "norm should be an hsVector3");
        return -1;
    }
    self->fThis->setNorm(*((pyVector3*)value)->fThis);
    return 0;
}

static int pyCullPoly_setCenter(pyCullPoly* self, PyObject* value, void*) {
    if (value == NULL || !pyVector3_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "center should be an hsVector3");
        return -1;
    }
    self->fThis->setCenter(*((pyVector3*)value)->fThis);
    return 0;
}

static int pyCullPoly_setDist(pyCullPoly* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "dist should be a float");
        return -1;
    }
    self->fThis->setDist(PyFloat_AsDouble(value));
    return 0;
}

static int pyCullPoly_setRadius(pyCullPoly* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "radius should be a float");
        return -1;
    }
    self->fThis->setRadius(PyFloat_AsDouble(value));
    return 0;
}

static PyGetSetDef pyCullPoly_GetSet[] = {
    { _pycs("flags"), (getter)pyCullPoly_getFlags, (setter)pyCullPoly_setFlags, NULL, NULL },
    { _pycs("verts"), (getter)pyCullPoly_getVerts, (setter)pyCullPoly_setVerts, NULL, NULL },
    { _pycs("norm"), (getter)pyCullPoly_getNorm, (setter)pyCullPoly_setNorm, NULL, NULL },
    { _pycs("center"), (getter)pyCullPoly_getCenter, (setter)pyCullPoly_setCenter, NULL, NULL },
    { _pycs("dist"), (getter)pyCullPoly_getDist, (setter)pyCullPoly_setDist, NULL, NULL },
    { _pycs("radius"), (getter)pyCullPoly_getRadius, (setter)pyCullPoly_setRadius, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyCullPoly_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plCullPoly",            /* tp_name */
    sizeof(pyCullPoly),                 /* tp_basicsize */
    0,                                  /* tp_itemsize */

    (destructor)pyCullPoly_dealloc,     /* tp_dealloc */
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

    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
    "plCullPoly wrapper",               /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyCullPoly_GetSet,                  /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    (initproc)pyCullPoly___init__,      /* tp_init */
    NULL,                               /* tp_alloc */
    pyCullPoly_new,                     /* tp_new */
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

PyObject* Init_pyCullPoly_Type() {
    if (PyType_Ready(&pyCullPoly_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyCullPoly_Type.tp_dict, "kNone",
                         PyInt_FromLong(plCullPoly::kNone));
    PyDict_SetItemString(pyCullPoly_Type.tp_dict, "kHole",
                         PyInt_FromLong(plCullPoly::kHole));
    PyDict_SetItemString(pyCullPoly_Type.tp_dict, "kTwoSided",
                         PyInt_FromLong(plCullPoly::kTwoSided));

    Py_INCREF(&pyCullPoly_Type);
    return (PyObject*)&pyCullPoly_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(CullPoly, plCullPoly)

}
