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
#include <PRP/Light/plOmniLightInfo.h>
#include "pyLightInfo.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyOmniLightInfo_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyOmniLightInfo* self = (pyOmniLightInfo*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plOmniLightInfo();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyOmniLightInfo_getAttenConst(pyOmniLightInfo* self, void*) {
    return PyFloat_FromDouble(self->fThis->getAttenConst());
}

static PyObject* pyOmniLightInfo_getAttenLinear(pyOmniLightInfo* self, void*) {
    return PyFloat_FromDouble(self->fThis->getAttenLinear());
}

static PyObject* pyOmniLightInfo_getAttenQuadratic(pyOmniLightInfo* self, void*) {
    return PyFloat_FromDouble(self->fThis->getAttenQuadratic());
}

static PyObject* pyOmniLightInfo_getAttenCutoff(pyOmniLightInfo* self, void*) {
    return PyFloat_FromDouble(self->fThis->getAttenCutoff());
}

static int pyOmniLightInfo_setAttenConst(pyOmniLightInfo* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "attenConst should be a float");
        return -1;
    }
    self->fThis->setAttenConst(PyFloat_AsDouble(value));
    return 0;
}

static int pyOmniLightInfo_setAttenLinear(pyOmniLightInfo* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "attenLinear should be a float");
        return -1;
    }
    self->fThis->setAttenLinear(PyFloat_AsDouble(value));
    return 0;
}

static int pyOmniLightInfo_setAttenQuadratic(pyOmniLightInfo* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "attenQuadratic should be a float");
        return -1;
    }
    self->fThis->setAttenQuadratic(PyFloat_AsDouble(value));
    return 0;
}

static int pyOmniLightInfo_setAttenCutoff(pyOmniLightInfo* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "attenCutoff should be a float");
        return -1;
    }
    self->fThis->setAttenCutoff(PyFloat_AsDouble(value));
    return 0;
}

static PyMethodDef pyOmniLightInfo_Methods[] = {
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyOmniLightInfo_GetSet[] = {
    { "attenConst", (getter)pyOmniLightInfo_getAttenConst, (setter)pyOmniLightInfo_setAttenConst, NULL, NULL },
    { "attenLinear", (getter)pyOmniLightInfo_getAttenLinear, (setter)pyOmniLightInfo_setAttenLinear, NULL, NULL },
    { "attenQuadratic", (getter)pyOmniLightInfo_getAttenQuadratic, (setter)pyOmniLightInfo_setAttenQuadratic, NULL, NULL },
    { "attenCutoff", (getter)pyOmniLightInfo_getAttenCutoff, (setter)pyOmniLightInfo_setAttenCutoff, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyOmniLightInfo_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyPlasma.plOmniLightInfo",         /* tp_name */
    sizeof(pyOmniLightInfo),            /* tp_basicsize */
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
    "plOmniLightInfo wrapper",          /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyOmniLightInfo_Methods,            /* tp_methods */
    NULL,                               /* tp_members */
    pyOmniLightInfo_GetSet,             /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyOmniLightInfo_new,                /* tp_new */
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

PyObject* Init_pyOmniLightInfo_Type() {
    pyOmniLightInfo_Type.tp_base = &pyLightInfo_Type;
    if (PyType_Ready(&pyOmniLightInfo_Type) < 0)
        return NULL;

    Py_INCREF(&pyOmniLightInfo_Type);
    return (PyObject*)&pyOmniLightInfo_Type;
}

int pyOmniLightInfo_Check(PyObject* obj) {
    if (obj->ob_type == &pyOmniLightInfo_Type
        || PyType_IsSubtype(obj->ob_type, &pyOmniLightInfo_Type))
        return 1;
    return 0;
}

PyObject* pyOmniLightInfo_FromOmniLightInfo(class plOmniLightInfo* light) {
    if (light == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyOmniLightInfo* pyLight = PyObject_New(pyOmniLightInfo, &pyOmniLightInfo_Type);
    pyLight->fThis = light;
    pyLight->fPyOwned = false;
    return (PyObject*)pyLight;
}

}
