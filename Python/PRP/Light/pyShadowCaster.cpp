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

#include "pyShadowCaster.h"

#include <PRP/Light/plShadowCaster.h>
#include "PRP/Modifier/pyModifier.h"

extern "C" {

static PyObject* pyShadowCaster_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyShadowCaster* self = (pyShadowCaster*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plShadowCaster();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyShadowCaster_getCastFlags(pyShadowCaster* self, void*) {
    return PyInt_FromLong(self->fThis->getCastFlags());
}

static PyObject* pyShadowCaster_getBoost(pyShadowCaster* self, void*) {
    return PyFloat_FromDouble(self->fThis->getBoost());
}

static PyObject* pyShadowCaster_getAttenScale(pyShadowCaster* self, void*) {
    return PyFloat_FromDouble(self->fThis->getAttenScale());
}

static PyObject* pyShadowCaster_getBlurScale(pyShadowCaster* self, void*) {
    return PyFloat_FromDouble(self->fThis->getBlurScale());
}

static PyObject* pyShadowCaster_getMaxOpacity(pyShadowCaster* self, void*) {
    return PyFloat_FromDouble(self->fThis->getMaxOpacity());
}

static int pyShadowCaster_setCastFlags(pyShadowCaster* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "castFlags should be an int");
        return -1;
    }
    self->fThis->setCastFlags((unsigned char)PyInt_AsLong(value));
    return 0;
}

static int pyShadowCaster_setBoost(pyShadowCaster* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "boost should be a float");
        return -1;
    }
    self->fThis->setBoost((float)PyFloat_AsDouble(value));
    return 0;
}

static int pyShadowCaster_setAttenScale(pyShadowCaster* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "attenScale should be a float");
        return -1;
    }
    self->fThis->setAttenScale((float)PyFloat_AsDouble(value));
    return 0;
}

static int pyShadowCaster_setBlurScale(pyShadowCaster* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "blurScale should be a float");
        return -1;
    }
    self->fThis->setBlurScale((float)PyFloat_AsDouble(value));
    return 0;
}

static int pyShadowCaster_setMaxOpacity(pyShadowCaster* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "maxOpacity should be a float");
        return -1;
    }
    self->fThis->setMaxOpacity((float)PyFloat_AsDouble(value));
    return 0;
}

static PyGetSetDef pyShadowCaster_GetSet[] = {
    { _pycs("castFlags"), (getter)pyShadowCaster_getCastFlags,
      (setter)pyShadowCaster_setCastFlags, NULL, NULL },
    { _pycs("boost"), (getter)pyShadowCaster_getBoost,
      (setter)pyShadowCaster_setBoost, NULL, NULL },
    { _pycs("attenScale"), (getter)pyShadowCaster_getAttenScale,
      (setter)pyShadowCaster_setAttenScale, NULL, NULL },
    { _pycs("blurScale"), (getter)pyShadowCaster_getBlurScale,
      (setter)pyShadowCaster_setBlurScale , NULL, NULL },
    { _pycs("maxOpacity"), (getter)pyShadowCaster_getMaxOpacity,
      (setter)pyShadowCaster_setMaxOpacity, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyShadowCaster_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plShadowCaster",        /* tp_name */
    sizeof(pyShadowCaster),             /* tp_basicsize */
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
    "plShadowCaster wrapper",                 /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyShadowCaster_GetSet,              /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyShadowCaster_new,                 /* tp_new */
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

PyObject* Init_pyShadowCaster_Type() {
    pyShadowCaster_Type.tp_base = &pyMultiModifier_Type;
    if (PyType_Ready(&pyShadowCaster_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyShadowCaster_Type.tp_dict, "kNone",
                         PyInt_FromLong(plShadowCaster::kNone));
    PyDict_SetItemString(pyShadowCaster_Type.tp_dict, "kSelfShadow",
                         PyInt_FromLong(plShadowCaster::kSelfShadow));
    PyDict_SetItemString(pyShadowCaster_Type.tp_dict, "kPerspective",
                         PyInt_FromLong(plShadowCaster::kPerspective));
    PyDict_SetItemString(pyShadowCaster_Type.tp_dict, "kLimitRes",
                         PyInt_FromLong(plShadowCaster::kLimitRes));

    Py_INCREF(&pyShadowCaster_Type);
    return (PyObject*)&pyShadowCaster_Type;
}

int pyShadowCaster_Check(PyObject* obj) {
    if (obj->ob_type == &pyShadowCaster_Type
        || PyType_IsSubtype(obj->ob_type, &pyShadowCaster_Type))
        return 1;
    return 0;
}

PyObject* pyShadowCaster_FromShadowCaster(plShadowCaster* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyShadowCaster* pyobj = PyObject_New(pyShadowCaster, &pyShadowCaster_Type);
    pyobj->fThis = obj;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
