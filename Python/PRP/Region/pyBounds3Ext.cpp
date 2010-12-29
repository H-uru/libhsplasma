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
#include <PRP/Region/hsBounds.h>
#include "pyBounds.h"
#include "Math/pyGeometry3.h"

extern "C" {

static PyObject* pyBounds3Ext_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyBounds3Ext* self = (pyBounds3Ext*)type->tp_alloc(type, 0);
    if (self != NULL)
        self->fThis = new hsBounds3Ext();
    return (PyObject*)self;
}

static PyObject* pyBounds3Ext_getFlags(pyBounds3Ext* self, void*) {
    return PyInt_FromLong(self->fThis->getFlags());
}

static PyObject* pyBounds3Ext_getCorner(pyBounds3Ext* self, void*) {
    return pyVector3_FromVector3(self->fThis->getCorner());
}

static PyObject* pyBounds3Ext_getAxis(pyBounds3Ext* self, void* idx) {
    return pyVector3_FromVector3(self->fThis->getAxis((long)idx));
}

static PyObject* pyBounds3Ext_getDist(pyBounds3Ext* self, void* idx) {
    hsFloatPoint2 dist = self->fThis->getDist((long)idx);
    return Py_BuildValue("ff", dist.X, dist.Y);
}

static PyObject* pyBounds3Ext_getRadius(pyBounds3Ext* self, void*) {
    return PyFloat_FromDouble(self->fThis->getRadius());
}

static int pyBounds3Ext_setFlags(pyBounds3Ext* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "flags should be an int");
        return -1;
    }
    self->fThis->setFlags(PyInt_AsLong(value));
    return 0;
}

static int pyBounds3Ext_setCorner(pyBounds3Ext* self, PyObject* value, void*) {
    if (value == NULL || !pyVector3_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "corner should be an hsVector3");
        return -1;
    }
    self->fThis->setCorner(*((pyVector3*)value)->fThis);
    return 0;
}

static int pyBounds3Ext_setAxis(pyBounds3Ext* self, PyObject* value, void* idx) {
    if (value == NULL || !pyVector3_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "axes should be an hsVector3");
        return -1;
    }
    self->fThis->setAxis((long)idx, *((pyVector3*)value)->fThis);
    return 0;
}

static int pyBounds3Ext_setDist(pyBounds3Ext* self, PyObject* value, void* idx) {
    if (value == NULL || !PyTuple_Check(value) || (PyTuple_Size(value) != 2)) {
        PyErr_SetString(PyExc_TypeError, "dists should be a tuple (float, float)");
        return -1;
    }
    hsFloatPoint2 dist;
    PyObject* itmX = PyTuple_GET_ITEM(value, 0);
    PyObject* itmY = PyTuple_GET_ITEM(value, 1);
    if (!PyFloat_Check(itmX) || !PyFloat_Check(itmY)) {
        PyErr_SetString(PyExc_TypeError, "dists should be a tuple (float, float)");
        return -1;
    }
    dist.X = PyFloat_AsDouble(itmX);
    dist.Y = PyFloat_AsDouble(itmY);
    self->fThis->setDist((long)idx, dist);
    return 0;
}

static int pyBounds3Ext_setRadius(pyBounds3Ext* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "radius should be a float");
        return -1;
    }
    self->fThis->setRadius(PyFloat_AsDouble(value));
    return 0;
}

static PyGetSetDef pyBounds3Ext_GetSet[] = {
    { "flags", (getter)pyBounds3Ext_getFlags, (setter)pyBounds3Ext_setFlags, NULL, NULL },
    { "corner", (getter)pyBounds3Ext_getCorner, (setter)pyBounds3Ext_setCorner, NULL, NULL },
    { "axis0", (getter)pyBounds3Ext_getAxis, (setter)pyBounds3Ext_setAxis, NULL, (void*)0 },
    { "axis1", (getter)pyBounds3Ext_getAxis, (setter)pyBounds3Ext_setAxis, NULL, (void*)1 },
    { "axis2", (getter)pyBounds3Ext_getAxis, (setter)pyBounds3Ext_setAxis, NULL, (void*)2 },
    { "dist0", (getter)pyBounds3Ext_getDist, (setter)pyBounds3Ext_setDist, NULL, (void*)0 },
    { "dist1", (getter)pyBounds3Ext_getDist, (setter)pyBounds3Ext_setDist, NULL, (void*)1 },
    { "dist2", (getter)pyBounds3Ext_getDist, (setter)pyBounds3Ext_setDist, NULL, (void*)2 },
    { "radius", (getter)pyBounds3Ext_getRadius, (setter)pyBounds3Ext_setRadius, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyBounds3Ext_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.hsBounds3Ext",            /* tp_name */
    sizeof(pyBounds3Ext),               /* tp_basicsize */
    0,                                  /* tp_itemsize */

    NULL,                               /* tp_dealloc */
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
    "hsBounds3Ext wrapper",             /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyBounds3Ext_GetSet,                /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyBounds3Ext_new,                   /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */

    NULL,                               /* tp_del */
    TP_VERSION_TAG_INIT                 /* tp_version_tag */
};

PyObject* Init_pyBounds3Ext_Type() {
    pyBounds3Ext_Type.tp_base = &pyBounds3_Type;
    if (PyType_Ready(&pyBounds3Ext_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyBounds3Ext_Type.tp_dict, "kAxisAligned",
                         PyInt_FromLong(hsBounds3Ext::kAxisAligned));
    PyDict_SetItemString(pyBounds3Ext_Type.tp_dict, "kSphereSet",
                         PyInt_FromLong(hsBounds3Ext::kSphereSet));
    PyDict_SetItemString(pyBounds3Ext_Type.tp_dict, "kDistsSet",
                         PyInt_FromLong(hsBounds3Ext::kDistsSet));
    PyDict_SetItemString(pyBounds3Ext_Type.tp_dict, "kAxisZeroZero",
                         PyInt_FromLong(hsBounds3Ext::kAxisZeroZero));
    PyDict_SetItemString(pyBounds3Ext_Type.tp_dict, "kAxisOneZero",
                         PyInt_FromLong(hsBounds3Ext::kAxisOneZero));
    PyDict_SetItemString(pyBounds3Ext_Type.tp_dict, "kAxisTwoZero",
                         PyInt_FromLong(hsBounds3Ext::kAxisTwoZero));

    Py_INCREF(&pyBounds3Ext_Type);
    return (PyObject*)&pyBounds3Ext_Type;
}

int pyBounds3Ext_Check(PyObject* obj) {
    if (obj->ob_type == &pyBounds3Ext_Type
        || PyType_IsSubtype(obj->ob_type, &pyBounds3Ext_Type))
        return 1;
    return 0;
}

PyObject* pyBounds3Ext_FromBounds3Ext(const hsBounds3Ext& bounds) {
    pyBounds3Ext* obj = PyObject_New(pyBounds3Ext, &pyBounds3Ext_Type);
    delete obj->fThis;
    obj->fThis = new hsBounds3Ext(bounds);
    return (PyObject*)obj;
}

}
