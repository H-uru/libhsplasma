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

#include "PRP/Modifier/pyModifier.h"

#include <PRP/Surface/plDistOpacityMod.h>
#include "pyDistOpacityMod.h"

extern "C" {

static PyObject* pyDistOpacityMod_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyDistOpacityMod* self = (pyDistOpacityMod*) type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plDistOpacityMod();
        self->fPyOwned = true;
    }
    return (PyObject*) self;
}

static PyObject* pyDistOpacityMod_getNearTrans(pyDistOpacityMod* self, void*) {
    return PyFloat_FromDouble(self->fThis->getDistance(plDistOpacityMod::kNearTrans));
}

static PyObject* pyDistOpacityMod_getNearOpaq(pyDistOpacityMod* self, void*) {
    return PyFloat_FromDouble(self->fThis->getDistance(plDistOpacityMod::kNearOpaq));
}

static PyObject* pyDistOpacityMod_getFarOpaq(pyDistOpacityMod* self, void*) {
    return PyFloat_FromDouble(self->fThis->getDistance(plDistOpacityMod::kFarOpaq));
}

static PyObject* pyDistOpacityMod_getFarTrans(pyDistOpacityMod* self, void*) {
    return PyFloat_FromDouble(self->fThis->getDistance(plDistOpacityMod::kFarTrans));
}

static int pyDistOpacityMod_setNearTrans(pyDistOpacityMod* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "NearTrans should be a float");
        return -1;
    }
    self->fThis->setDistance(plDistOpacityMod::kNearTrans, PyFloat_AsDouble(value));
    return 0;
}

static int pyDistOpacityMod_setNearOpaq(pyDistOpacityMod* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "NearOpaq should be a float");
        return -1;
    }
    self->fThis->setDistance(plDistOpacityMod::kNearOpaq, PyFloat_AsDouble(value));
    return 0;
}

static int pyDistOpacityMod_setFarOpaq(pyDistOpacityMod* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "FarOpaq should be a float");
        return -1;
    }
    self->fThis->setDistance(plDistOpacityMod::kFarOpaq, PyFloat_AsDouble(value));
    return 0;
}

static int pyDistOpacityMod_setFarTrans(pyDistOpacityMod* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "FarTrans should be a float");
        return -1;
    }
    self->fThis->setDistance(plDistOpacityMod::kFarTrans, PyFloat_AsDouble(value));
    return 0;
}

static PyGetSetDef pyDistOpacityMod_GetSet [] = {
    { _pycs("nearTrans"), (getter) pyDistOpacityMod_getNearTrans, (setter) pyDistOpacityMod_setNearTrans, NULL, NULL },
    { _pycs("nearOpaq"), (getter) pyDistOpacityMod_getNearOpaq, (setter) pyDistOpacityMod_setNearOpaq, NULL, NULL },
    { _pycs("farOpaq"), (getter) pyDistOpacityMod_getFarOpaq, (setter) pyDistOpacityMod_setFarOpaq, NULL, NULL },
    { _pycs("farTrans"), (getter) pyDistOpacityMod_getFarTrans, (setter) pyDistOpacityMod_setFarTrans, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyDistOpacityMod_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plDistOpacityMod",      /* tp_name */
    sizeof(pyDistOpacityMod),           /* tp_basicsize */
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
    "plDistOpacityMod wrapper",         /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyDistOpacityMod_GetSet,            /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyDistOpacityMod_new,              /* tp_new */
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

PyObject* Init_pyDistOpacityMod_Type() {
    pyDistOpacityMod_Type.tp_base = &pySingleModifier_Type;
    if (PyType_Ready(&pyDistOpacityMod_Type) < 0)
        return NULL;

    Py_INCREF(&pyDistOpacityMod_Type);
    return (PyObject*) &pyDistOpacityMod_Type;
}

int pyDistOpacityMod_Check(PyObject* obj) {
    if (obj->ob_type == &pyDistOpacityMod_Type
        || PyType_IsSubtype(obj->ob_type, &pyDistOpacityMod_Type))
        return 1;
    return 0;
}

PyObject* pyDistOpacityMod_FromDistOpacityMod(class plDistOpacityMod* dom) {
    if (dom == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyDistOpacityMod* pydom = PyObject_New(pyDistOpacityMod, &pyDistOpacityMod_Type);
    pydom->fThis = dom;
    pydom->fPyOwned = false;
    return (PyObject*) pydom;
}

}
