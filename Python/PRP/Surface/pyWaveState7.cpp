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

#include "pyFixedWaterState7.h"

#include <PRP/Surface/plFixedWaterState7.h>

extern "C" {

static PyObject* pyWaveState7_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyWaveState7* self = (pyWaveState7*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plFixedWaterState7::WaveState();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyWaveState7_getMaxLength(pyWaveState7* self, void*) {
    return PyFloat_FromDouble(self->fThis->fMaxLength);
}

static PyObject* pyWaveState7_getMinLength(pyWaveState7* self, void*) {
    return PyFloat_FromDouble(self->fThis->fMinLength);
}

static PyObject* pyWaveState7_getAmpOverLen(pyWaveState7* self, void*) {
    return PyFloat_FromDouble(self->fThis->fAmpOverLen);
}

static PyObject* pyWaveState7_getChop(pyWaveState7* self, void*) {
    return PyFloat_FromDouble(self->fThis->fChop);
}

static PyObject* pyWaveState7_getAngleDev(pyWaveState7* self, void*) {
    return PyFloat_FromDouble(self->fThis->fAngleDev);
}

static int pyWaveState7_setMaxLength(pyWaveState7* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "maxLength should be a float");
        return -1;
    }
    self->fThis->fMaxLength = (float)PyFloat_AsDouble(value);
    return 0;
}

static int pyWaveState7_setMinLength(pyWaveState7* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "minLength should be a float");
        return -1;
    }
    self->fThis->fMinLength = (float)PyFloat_AsDouble(value);
    return 0;
}

static int pyWaveState7_setAmpOverLen(pyWaveState7* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "ampOverLen should be a float");
        return -1;
    }
    self->fThis->fAmpOverLen = (float)PyFloat_AsDouble(value);
    return 0;
}

static int pyWaveState7_setChop(pyWaveState7* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "chop should be a float");
        return -1;
    }
    self->fThis->fChop = (float)PyFloat_AsDouble(value);
    return 0;
}

static int pyWaveState7_setAngleDev(pyWaveState7* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "angleDev should be a float");
        return -1;
    }
    self->fThis->fAngleDev = (float)PyFloat_AsDouble(value);
    return 0;
}

static PyGetSetDef pyWaveState7_GetSet[] = {
    { _pycs("maxLength"), (getter)pyWaveState7_getMaxLength, (setter)pyWaveState7_setMaxLength, NULL, NULL },
    { _pycs("minLength"), (getter)pyWaveState7_getMinLength, (setter)pyWaveState7_setMinLength, NULL, NULL },
    { _pycs("ampOverLen"), (getter)pyWaveState7_getAmpOverLen, (setter)pyWaveState7_setAmpOverLen, NULL, NULL },
    { _pycs("chop"), (getter)pyWaveState7_getChop, (setter)pyWaveState7_setChop, NULL, NULL },
    { _pycs("angleDev"), (getter)pyWaveState7_getAngleDev, (setter)pyWaveState7_setAngleDev, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyWaveState7_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plWaveState7",          /* tp_name */
    sizeof(pyWaveState7),               /* tp_basicsize */
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
    "plFixedWaterState7 wrapper",             /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyWaveState7_GetSet,                /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyWaveState7_new,                   /* tp_new */
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

PyObject* Init_pyWaveState7_Type() {
    if (PyType_Ready(&pyWaveState7_Type) < 0)
        return NULL;

    Py_INCREF(&pyWaveState7_Type);
    return (PyObject*)&pyWaveState7_Type;
}

PY_PLASMA_IFC_METHODS(WaveState7, plFixedWaterState7::WaveState)

}
