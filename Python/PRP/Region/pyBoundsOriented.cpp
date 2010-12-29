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

static PyObject* pyBoundsOriented_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyBoundsOriented* self = (pyBoundsOriented*)type->tp_alloc(type, 0);
    if (self != NULL)
        self->fThis = new hsBoundsOriented();
    return (PyObject*)self;
}

static PyObject* pyBoundsOriented_getCenter(pyBoundsOriented* self, void*) {
    return pyVector3_FromVector3(self->fThis->getCenter());
}

static PyObject* pyBoundsOriented_getCenterValid(pyBoundsOriented* self, void*) {
    return PyInt_FromLong(self->fThis->getCenterValid());
}

static PyObject* pyBoundsOriented_getPlanes(pyBoundsOriented* self, void*) {
    PyObject* list = PyList_New(self->fThis->getNumPlanes());
    for (size_t i=0; i<self->fThis->getNumPlanes(); i++)
        PyList_SET_ITEM(list, i, pyPlane3_FromPlane3(self->fThis->getPlanes()[i]));
    return list;
}

static int pyBoundsOriented_setCenter(pyBoundsOriented* self, PyObject* value, void*) {
    if (value == NULL || !pyVector3_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "center should be an hsVector3");
        return -1;
    }
    self->fThis->setCenter(*((pyVector3*)value)->fThis);
    return 0;
}

static int pyBoundsOriented_setCenterValid(pyBoundsOriented* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "centerValid should be an int");
        return -1;
    }
    self->fThis->setCenterValid(PyInt_AsLong(value));
    return 0;
}

static int pyBoundsOriented_setPlanes(pyBoundsOriented* self, PyObject* value, void*) {
    if (value == NULL) {
        self->fThis->setPlanes(0, NULL);
        return 0;
    } else if (PyList_Check(value)) {
        size_t numPlanes = PyList_Size(value);
        hsPlane3* planes = new hsPlane3[numPlanes];
        for (size_t i=0; i<numPlanes; i++) {
            if (!pyPlane3_Check(PyList_GetItem(value, i))) {
                PyErr_SetString(PyExc_TypeError, "planes should be a list of hsPlane3 objects");
                return -1;
            }
            planes[i] = *((pyPlane3*)PyList_GetItem(value, i))->fThis;
        }
        self->fThis->setPlanes(numPlanes, planes);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "planes should be a list of hsPlane3 objects");
        return -1;
    }
}

static PyGetSetDef pyBoundsOriented_GetSet[] = {
    { "center", (getter)pyBoundsOriented_getCenter, (setter)pyBoundsOriented_setCenter, NULL, NULL },
    { "centerValid", (getter)pyBoundsOriented_getCenterValid, (setter)pyBoundsOriented_setCenterValid, NULL, NULL },
    { "planes", (getter)pyBoundsOriented_getPlanes, (setter)pyBoundsOriented_setPlanes, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyBoundsOriented_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.hsBoundsOriented",        /* tp_name */
    sizeof(pyBoundsOriented),           /* tp_basicsize */
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
    "hsBoundsOriented wrapper",             /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyBoundsOriented_GetSet,                /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyBoundsOriented_new,                   /* tp_new */
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

PyObject* Init_pyBoundsOriented_Type() {
    pyBoundsOriented_Type.tp_base = &pyBounds_Type;
    if (PyType_Ready(&pyBoundsOriented_Type) < 0)
        return NULL;

    Py_INCREF(&pyBoundsOriented_Type);
    return (PyObject*)&pyBoundsOriented_Type;
}

int pyBoundsOriented_Check(PyObject* obj) {
    if (obj->ob_type == &pyBoundsOriented_Type
        || PyType_IsSubtype(obj->ob_type, &pyBoundsOriented_Type))
        return 1;
    return 0;
}

PyObject* pyBoundsOriented_FromBoundsOriented(const hsBoundsOriented& bounds) {
    pyBoundsOriented* obj = PyObject_New(pyBoundsOriented, &pyBoundsOriented_Type);
    delete obj->fThis;
    obj->fThis = new hsBoundsOriented(bounds);
    return (PyObject*)obj;
}

}
