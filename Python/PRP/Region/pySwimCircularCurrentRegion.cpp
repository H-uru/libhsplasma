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

#include "pySwimRegion.h"

#include "PRP/KeyedObject/pyKey.h"
#include <PRP/Region/plSwimRegion.h>

extern "C" {

static PyObject* pySwimCircularCurrentRegion_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pySwimCircularCurrentRegion* self = (pySwimCircularCurrentRegion*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plSwimCircularCurrentRegion();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pySwimCircularCurrentRegion_getRotation(pySwimCircularCurrentRegion* self, void*) {
    return PyFloat_FromDouble(self->fThis->getRotation());
}

static PyObject* pySwimCircularCurrentRegion_getPullNearDistSq(pySwimCircularCurrentRegion* self, void*) {
    return PyFloat_FromDouble(self->fThis->getPullNearDistSq());
}

static PyObject* pySwimCircularCurrentRegion_getPullFarDistSq(pySwimCircularCurrentRegion* self, void*) {
    return PyFloat_FromDouble(self->fThis->getPullFarDistSq());
}

static PyObject* pySwimCircularCurrentRegion_getPullNearVel(pySwimCircularCurrentRegion* self, void*) {
    return PyFloat_FromDouble(self->fThis->getPullNearVel());
}

static PyObject* pySwimCircularCurrentRegion_getPullFarVel(pySwimCircularCurrentRegion* self, void*) {
    return PyFloat_FromDouble(self->fThis->getPullFarVel());
}

static PyObject* pySwimCircularCurrentRegion_getCurrentObj(pySwimCircularCurrentRegion* self, void*) {
    return pyKey_FromKey(self->fThis->getCurrentObj());
}

static int pySwimCircularCurrentRegion_setRotation(pySwimCircularCurrentRegion* self, PyObject* value, void*) {
    if (PyFloat_Check(value)) {
        self->fThis->setRotation((float)PyFloat_AsDouble(value));
        return 0;
    }
    PyErr_SetString(PyExc_TypeError, "rotation should be a float");
    return -1;
}

static int pySwimCircularCurrentRegion_setPullNearDistSq(pySwimCircularCurrentRegion* self, PyObject* value, void*) {
    if (PyFloat_Check(value)) {
        self->fThis->setPullNearDistSq((float)PyFloat_AsDouble(value));
        return 0;
    }
    PyErr_SetString(PyExc_TypeError, "pullNearDistSq should be a float");
    return -1;
}

static int pySwimCircularCurrentRegion_setPullFarDistSq(pySwimCircularCurrentRegion* self, PyObject* value, void*) {
    if (PyFloat_Check(value)) {
        self->fThis->setPullFarDistSq((float)PyFloat_AsDouble(value));
        return 0;
    }
    PyErr_SetString(PyExc_TypeError, "pullFarDistSq should be a float");
    return -1;
}

static int pySwimCircularCurrentRegion_setPullNearVel(pySwimCircularCurrentRegion* self, PyObject* value, void*) {
    if (PyFloat_Check(value)) {
        self->fThis->setPullNearVel((float)PyFloat_AsDouble(value));
        return 0;
    }
    PyErr_SetString(PyExc_TypeError, "pullNearVel should be a float");
    return -1;
}

static int pySwimCircularCurrentRegion_setPullFarVel(pySwimCircularCurrentRegion* self, PyObject* value, void*) {
    if (PyFloat_Check(value)) {
        self->fThis->setPullFarVel((float)PyFloat_AsDouble(value));
        return 0;
    }
    PyErr_SetString(PyExc_TypeError, "pullFarVel should be a float");
    return -1;
}

static int pySwimCircularCurrentRegion_setCurrentObj(pySwimCircularCurrentRegion* self, PyObject* value, void*) {
    if (value == Py_None || value == NULL) {
        self->fThis->setCurrentObj(plKey());
        return 0;
    } else if (pyKey_Check(value)) {
        self->fThis->setCurrentObj(*((pyKey*)value)->fThis);
        return 0;
    }
    PyErr_SetString(PyExc_TypeError, "currentObj should be a plKey");
    return -1;
}

PyGetSetDef pySwimCircularCurrentRegion_GetSet[] = {
    { _pycs("rotation"), (getter)pySwimCircularCurrentRegion_getRotation,
     (setter)pySwimCircularCurrentRegion_setRotation, NULL, NULL },
    { _pycs("pullNearDistSq"), (getter)pySwimCircularCurrentRegion_getPullNearDistSq,
     (setter)pySwimCircularCurrentRegion_setPullNearDistSq, NULL, NULL },
    { _pycs("pullFarDistSq"), (getter)pySwimCircularCurrentRegion_getPullFarDistSq,
     (setter)pySwimCircularCurrentRegion_setPullFarDistSq, NULL, NULL },
    { _pycs("pullNearVel"), (getter)pySwimCircularCurrentRegion_getPullNearVel,
     (setter)pySwimCircularCurrentRegion_setPullNearVel, NULL, NULL },
    { _pycs("pullFarVel"), (getter)pySwimCircularCurrentRegion_getPullFarVel,
     (setter)pySwimCircularCurrentRegion_setPullFarVel, NULL, NULL },
    { _pycs("currentObj"), (getter)pySwimCircularCurrentRegion_getCurrentObj,
     (setter)pySwimCircularCurrentRegion_setCurrentObj, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pySwimCircularCurrentRegion_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plSwimCircularCurrentRegion", /* tp_name */
    sizeof(pySwimCircularCurrentRegion),      /* tp_basicsize */
    0,                                        /* tp_itemsize */

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
    "plSwimCircularCurrentRegion wrapper",    /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pySwimCircularCurrentRegion_GetSet, /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pySwimCircularCurrentRegion_new,    /* tp_new */
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

PyObject* Init_pySwimCircularCurrentRegion_Type() {
    pySwimCircularCurrentRegion_Type.tp_base = &pySwimRegionInterface_Type;
    if (PyType_Ready(&pySwimCircularCurrentRegion_Type) < 0)
        return NULL;

    Py_INCREF(&pySwimCircularCurrentRegion_Type);
    return (PyObject*)&pySwimCircularCurrentRegion_Type;
}

PY_PLASMA_IFC_METHODS(SwimCircularCurrentRegion, plSwimCircularCurrentRegion);

}
