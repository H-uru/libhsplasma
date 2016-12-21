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

#include "pyATCEaseCurves.h"

#include <PRP/Animation/plATCEaseCurves.h>
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyATCEaseCurve_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyATCEaseCurve* self = (pyATCEaseCurve*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plATCEaseCurve();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyATCEaseCurve_getStartSpeed(pyATCEaseCurve* self, void*) {
    return PyFloat_FromDouble(self->fThis->getStartSpeed());
}

static PyObject* pyATCEaseCurve_getSpeed(pyATCEaseCurve* self, void*) {
    return PyFloat_FromDouble(self->fThis->getSpeed());
}

static PyObject* pyATCEaseCurve_getMinLength(pyATCEaseCurve* self, void*) {
    return PyFloat_FromDouble(self->fThis->getMinLength());
}

static PyObject* pyATCEaseCurve_getMaxLength(pyATCEaseCurve* self, void*) {
    return PyFloat_FromDouble(self->fThis->getMaxLength());
}

static PyObject* pyATCEaseCurve_getLength(pyATCEaseCurve* self, void*) {
    return PyFloat_FromDouble(self->fThis->getLength());
}

static PyObject* pyATCEaseCurve_getBegin(pyATCEaseCurve* self, void*) {
    return PyFloat_FromDouble(self->fThis->getBeginWorldTime());
}

static int pyATCEaseCurve_setStartSpeed(pyATCEaseCurve* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "startSpeed should be a float");
        return -1;
    }
    self->fThis->setStartSpeed(PyFloat_AsDouble(value));
    return 0;
}

static int pyATCEaseCurve_setSpeed(pyATCEaseCurve* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "speed should be a float");
        return -1;
    }
    self->fThis->setSpeed(PyFloat_AsDouble(value));
    return 0;
}

static int pyATCEaseCurve_setMinLength(pyATCEaseCurve* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "minLength should be a float");
        return -1;
    }
    self->fThis->setLengthBounds(PyFloat_AsDouble(value), self->fThis->getMaxLength());
    return 0;
}

static int pyATCEaseCurve_setMaxLength(pyATCEaseCurve* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "maxLength should be a float");
        return -1;
    }
    self->fThis->setLengthBounds(self->fThis->getMinLength(), PyFloat_AsDouble(value));
    return 0;
}

static int pyATCEaseCurve_setLength(pyATCEaseCurve* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "length should be a float");
        return -1;
    }
    self->fThis->setLength(PyFloat_AsDouble(value));
    return 0;
}

static int pyATCEaseCurve_setBegin(pyATCEaseCurve* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "beginWorldTime should be a float");
        return -1;
    }
    self->fThis->setBeginWorldTime(PyFloat_AsDouble(value));
    return 0;
}

static PyGetSetDef pyATCEaseCurve_GetSet[] = {
    { _pycs("startSpeed"), (getter)pyATCEaseCurve_getStartSpeed,
        (setter)pyATCEaseCurve_setStartSpeed, NULL, NULL },
    { _pycs("speed"), (getter)pyATCEaseCurve_getSpeed,
        (setter)pyATCEaseCurve_setSpeed, NULL, NULL },
    { _pycs("minLength"), (getter)pyATCEaseCurve_getMinLength,
        (setter)pyATCEaseCurve_setMinLength, NULL, NULL },
    { _pycs("maxLength"), (getter)pyATCEaseCurve_getMaxLength,
        (setter)pyATCEaseCurve_setMaxLength, NULL, NULL },
    { _pycs("length"), (getter)pyATCEaseCurve_getLength,
        (setter)pyATCEaseCurve_setLength, NULL, NULL },
    { _pycs("beginWorldTime"), (getter)pyATCEaseCurve_getBegin,
        (setter)pyATCEaseCurve_setBegin, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyATCEaseCurve_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plATCEaseCurve",        /* tp_name */
    sizeof(pyATCEaseCurve),             /* tp_basicsize */
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
    "plATCEaseCurve wrapper",           /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyATCEaseCurve_GetSet,              /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyATCEaseCurve_new,                 /* tp_new */
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

PyObject* Init_pyATCEaseCurve_Type() {
    pyATCEaseCurve_Type.tp_base = &pyCreatable_Type;
    if (PyType_Ready(&pyATCEaseCurve_Type) < 0)
        return NULL;

    Py_INCREF(&pyATCEaseCurve_Type);
    return (PyObject*)&pyATCEaseCurve_Type;
}

PY_PLASMA_IFC_METHODS(ATCEaseCurve, plATCEaseCurve)

}
