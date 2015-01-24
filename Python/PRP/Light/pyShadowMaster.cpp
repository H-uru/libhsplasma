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
#include <PRP/Light/plShadowMaster.h>
#include "pyShadowMaster.h"
#include "PRP/Object/pyObjInterface.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyShadowMaster_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyShadowMaster* self = (pyShadowMaster*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plShadowMaster();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyShadowMaster_getAttenDist(pyShadowMaster* self, void*) {
    return PyFloat_FromDouble(plShadowMaster::Convert(IConvert((pyCreatable*)self))->getAttenDist());
}

static PyObject* pyShadowMaster_getMaxDist(pyShadowMaster* self, void*) {
    return PyFloat_FromDouble(plShadowMaster::Convert(IConvert((pyCreatable*)self))->getMaxDist());
}

static PyObject* pyShadowMaster_getMinDist(pyShadowMaster* self, void*) {
    return PyFloat_FromDouble(plShadowMaster::Convert(IConvert((pyCreatable*)self))->getMinDist());
}

static PyObject* pyShadowMaster_getPower(pyShadowMaster* self, void*) {
    return PyFloat_FromDouble(plShadowMaster::Convert(IConvert((pyCreatable*)self))->getPower());
}

static PyObject* pyShadowMaster_getMaxSize(pyShadowMaster* self, void*) {
    return PyInt_FromLong(plShadowMaster::Convert(IConvert((pyCreatable*)self))->getMaxSize());
}

static PyObject* pyShadowMaster_getMinSize(pyShadowMaster* self, void*) {
    return PyInt_FromLong(plShadowMaster::Convert(IConvert((pyCreatable*)self))->getMinSize());
}

static int pyShadowMaster_setAttenDist(pyShadowMaster* self, PyObject* value, void*) {
    if (!PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "attenDist should be a float");
        return -1;
    }
    plShadowMaster::Convert(IConvert((pyCreatable*)self))->setAttenDist(PyFloat_AsDouble(value));
    return 0;
}

static int pyShadowMaster_setMaxDist(pyShadowMaster* self, PyObject* value, void*) {
    if (!PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "maxDist should be a float");
        return -1;
    }
    plShadowMaster::Convert(IConvert((pyCreatable*)self))->setDist(plShadowMaster::Convert(IConvert((pyCreatable*)self))->getMinDist(), PyFloat_AsDouble(value));
    return 0;
}

static int pyShadowMaster_setMinDist(pyShadowMaster* self, PyObject* value, void*) {
    if (!PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "minDist should be a float");
        return -1;
    }
    plShadowMaster::Convert(IConvert((pyCreatable*)self))->setDist(PyFloat_AsDouble(value), plShadowMaster::Convert(IConvert((pyCreatable*)self))->getMaxDist());
    return 0;
}

static int pyShadowMaster_setPower(pyShadowMaster* self, PyObject* value, void*) {
    if (!PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "power should be a float");
        return -1;
    }
    plShadowMaster::Convert(IConvert((pyCreatable*)self))->setPower(PyFloat_AsDouble(value));
    return 0;
}

static int pyShadowMaster_setMaxSize(pyShadowMaster* self, PyObject* value, void*) {
    if (!PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "maxSize should be an int");
        return -1;
    }
    plShadowMaster::Convert(IConvert((pyCreatable*)self))->setSize(plShadowMaster::Convert(IConvert((pyCreatable*)self))->getMinSize(), PyInt_AsLong(value));
    return 0;
}

static int pyShadowMaster_setMinSize(pyShadowMaster* self, PyObject* value, void*) {
    if (!PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "minSize should be an int");
        return -1;
    }
    plShadowMaster::Convert(IConvert((pyCreatable*)self))->setSize(PyInt_AsLong(value), plShadowMaster::Convert(IConvert((pyCreatable*)self))->getMaxSize());
    return 0;
}

static PyMethodDef pyShadowMaster_Methods[] = {
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyShadowMaster_GetSet[] = {
    { _pycs("attenDist"), (getter)pyShadowMaster_getAttenDist,
        (setter)pyShadowMaster_setAttenDist, NULL, NULL },
    { _pycs("maxDist"), (getter)pyShadowMaster_getMaxDist,
        (setter)pyShadowMaster_setMaxDist, NULL, NULL },
    { _pycs("minDist"), (getter)pyShadowMaster_getMinDist,
        (setter)pyShadowMaster_setMinDist, NULL, NULL },
    { _pycs("power"), (getter)pyShadowMaster_getPower,
        (setter)pyShadowMaster_setPower, NULL, NULL },
    { _pycs("maxSize"), (getter)pyShadowMaster_getMaxSize,
        (setter)pyShadowMaster_setMaxSize, NULL, NULL },
    { _pycs("minSize"), (getter)pyShadowMaster_getMinSize,
        (setter)pyShadowMaster_setMinSize, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyShadowMaster_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plShadowMaster",        /* tp_name */
    sizeof(pyShadowMaster),             /* tp_basicsize */
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
    "plShadowMaster wrapper",           /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyShadowMaster_Methods,             /* tp_methods */
    NULL,                               /* tp_members */
    pyShadowMaster_GetSet,              /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyShadowMaster_new,                 /* tp_new */
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

PyObject* Init_pyShadowMaster_Type() {
    pyShadowMaster_Type.tp_base = &pyObjInterface_Type;
    if (PyType_Ready(&pyShadowMaster_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyShadowMaster_Type.tp_dict, "kDisable",
                         PyInt_FromLong(plShadowMaster::kDisable));
    PyDict_SetItemString(pyShadowMaster_Type.tp_dict, "kSelfShadow",
                         PyInt_FromLong(plShadowMaster::kSelfShadow));
    PyDict_SetItemString(pyShadowMaster_Type.tp_dict, "kNumProps",
                         PyInt_FromLong(plShadowMaster::kNumProps));

    Py_INCREF(&pyShadowMaster_Type);
    return (PyObject*)&pyShadowMaster_Type;
}

int pyShadowMaster_Check(PyObject* obj) {
    if (obj->ob_type == &pyShadowMaster_Type
        || PyType_IsSubtype(obj->ob_type, &pyShadowMaster_Type))
        return 1;
    return 0;
}

PyObject* pyShadowMaster_FromShadowMaster(plShadowMaster* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyShadowMaster* pyobj = PyObject_New(pyShadowMaster, &pyShadowMaster_Type);
    pyobj->fThis = obj;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
