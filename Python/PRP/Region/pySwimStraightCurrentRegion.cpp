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

static PyObject* pySwimStraightCurrentRegion_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pySwimStraightCurrentRegion* self = (pySwimStraightCurrentRegion*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plSwimStraightCurrentRegion();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pySwimStraightCurrentRegion_getNearDist(pySwimStraightCurrentRegion* self, void*) {
    return PyFloat_FromDouble(self->fThis->getNearDist());
}

static PyObject* pySwimStraightCurrentRegion_getFarDist(pySwimStraightCurrentRegion* self, void*) {
    return PyFloat_FromDouble(self->fThis->getFarDist());
}

static PyObject* pySwimStraightCurrentRegion_getNearVel(pySwimStraightCurrentRegion* self, void*) {
    return PyFloat_FromDouble(self->fThis->getNearVel());
}

static PyObject* pySwimStraightCurrentRegion_getFarVel(pySwimStraightCurrentRegion* self, void*) {
    return PyFloat_FromDouble(self->fThis->getFarVel());
}

static PyObject* pySwimStraightCurrentRegion_getCurrentObj(pySwimStraightCurrentRegion* self, void*) {
    return pyKey_FromKey(self->fThis->getCurrentObj());
}

static int pySwimStraightCurrentRegion_setNearDist(pySwimStraightCurrentRegion* self, PyObject* value, void*) {
    if (PyFloat_Check(value)) {
        self->fThis->setNearDist((float)PyFloat_AsDouble(value));
        return 0;
    }
    PyErr_SetString(PyExc_TypeError, "nearDist should be a float");
    return -1;
}

static int pySwimStraightCurrentRegion_setFarDist(pySwimStraightCurrentRegion* self, PyObject* value, void*) {
    if (PyFloat_Check(value)) {
        self->fThis->setFarDist((float)PyFloat_AsDouble(value));
        return 0;
    }
    PyErr_SetString(PyExc_TypeError, "farDist should be a float");
    return -1;
}

static int pySwimStraightCurrentRegion_setNearVel(pySwimStraightCurrentRegion* self, PyObject* value, void*) {
    if (PyFloat_Check(value)) {
        self->fThis->setNearVel((float)PyFloat_AsDouble(value));
        return 0;
    }
    PyErr_SetString(PyExc_TypeError, "nearVel should be a float");
    return -1;
}

static int pySwimStraightCurrentRegion_setFarVel(pySwimStraightCurrentRegion* self, PyObject* value, void*) {
    if (PyFloat_Check(value)) {
        self->fThis->setFarVel((float)PyFloat_AsDouble(value));
        return 0;
    }
    PyErr_SetString(PyExc_TypeError, "farVel should be a float");
    return -1;
}

static int pySwimStraightCurrentRegion_setCurrentObj(pySwimStraightCurrentRegion* self, PyObject* value, void*) {
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

PyGetSetDef pySwimStraightCurrentRegion_GetSet[] = {
    { _pycs("nearDist"), (getter)pySwimStraightCurrentRegion_getNearDist,
     (setter)pySwimStraightCurrentRegion_setNearDist, NULL, NULL },
    { _pycs("farDist"), (getter)pySwimStraightCurrentRegion_getFarDist,
     (setter)pySwimStraightCurrentRegion_setFarDist, NULL, NULL },
    { _pycs("nearVel"), (getter)pySwimStraightCurrentRegion_getNearVel,
     (setter)pySwimStraightCurrentRegion_setNearVel, NULL, NULL },
    { _pycs("farVel"), (getter)pySwimStraightCurrentRegion_getFarVel,
     (setter)pySwimStraightCurrentRegion_setFarVel, NULL, NULL },
    { _pycs("currentObj"), (getter)pySwimStraightCurrentRegion_getCurrentObj,
     (setter)pySwimStraightCurrentRegion_setCurrentObj, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pySwimStraightCurrentRegion_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plSwimStraightCurrentRegion", /* tp_name */
    sizeof(pySwimStraightCurrentRegion),      /* tp_basicsize */
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
    "plSwimStraightCurrentRegion wrapper",    /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pySwimStraightCurrentRegion_GetSet, /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pySwimStraightCurrentRegion_new,    /* tp_new */
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

PyObject* Init_pySwimStraightCurrentRegion_Type() {
    pySwimStraightCurrentRegion_Type.tp_base = &pySwimRegionInterface_Type;
    if (PyType_Ready(&pySwimStraightCurrentRegion_Type) < 0)
        return NULL;

    Py_INCREF(&pySwimStraightCurrentRegion_Type);
    return (PyObject*)&pySwimStraightCurrentRegion_Type;
}

PY_PLASMA_IFC_METHODS(SwimStraightCurrentRegion, plSwimStraightCurrentRegion);

}
