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

static PyObject* pyBounds3_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyBounds3* self = (pyBounds3*)type->tp_alloc(type, 0);
    if (self != NULL)
        self->fThis = new hsBounds3();
    return (PyObject*)self;
}

static PyObject* pyBounds3_getMins(pyBounds3* self, void*) {
    return pyVector3_FromVector3(self->fThis->getMins());
}

static PyObject* pyBounds3_getMaxs(pyBounds3* self, void*) {
    return pyVector3_FromVector3(self->fThis->getMaxs());
}

static PyObject* pyBounds3_getCenter(pyBounds3* self, void*) {
    return pyVector3_FromVector3(self->fThis->getCenter());
}

static int pyBounds3_setMins(pyBounds3* self, PyObject* value, void*) {
    if (value == NULL || !pyVector3_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "mins should be an hsVector3");
        return -1;
    }
    self->fThis->setMins(*((pyVector3*)value)->fThis);
    return 0;
}

static int pyBounds3_setMaxs(pyBounds3* self, PyObject* value, void*) {
    if (value == NULL || !pyVector3_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "maxs should be an hsVector3");
        return -1;
    }
    self->fThis->setMaxs(*((pyVector3*)value)->fThis);
    return 0;
}

static int pyBounds3_setCenter(pyBounds3* self, PyObject* value, void*) {
    if (value == NULL || !pyVector3_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "center should be an hsVector3");
        return -1;
    }
    self->fThis->setCenter(*((pyVector3*)value)->fThis);
    return 0;
}

static PyGetSetDef pyBounds3_GetSet[] = {
    { "mins", (getter)pyBounds3_getMins, (setter)pyBounds3_setMins, NULL, NULL },
    { "maxs", (getter)pyBounds3_getMaxs, (setter)pyBounds3_setMaxs, NULL, NULL },
    { "center", (getter)pyBounds3_getCenter, (setter)pyBounds3_setCenter, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyBounds3_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.hsBounds3",               /* tp_name */
    sizeof(pyBounds3),                  /* tp_basicsize */
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
    "hsBounds3 wrapper",                /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyBounds3_GetSet,                   /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyBounds3_new,                      /* tp_new */
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

PyObject* Init_pyBounds3_Type() {
    pyBounds3_Type.tp_base = &pyBounds_Type;
    if (PyType_Ready(&pyBounds3_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyBounds3_Type.tp_dict, "kCenterValid",
                         PyInt_FromLong(hsBounds3::kCenterValid));
    PyDict_SetItemString(pyBounds3_Type.tp_dict, "kIsSphere",
                         PyInt_FromLong(hsBounds3::kIsSphere));

    Py_INCREF(&pyBounds3_Type);
    return (PyObject*)&pyBounds3_Type;
}

int pyBounds3_Check(PyObject* obj) {
    if (obj->ob_type == &pyBounds3_Type
        || PyType_IsSubtype(obj->ob_type, &pyBounds3_Type))
        return 1;
    return 0;
}

PyObject* pyBounds3_FromBounds3(const hsBounds3& bounds) {
    pyBounds3* obj = PyObject_New(pyBounds3, &pyBounds3_Type);
    obj->fThis = new hsBounds3(bounds);
    return (PyObject*)obj;
}

}
