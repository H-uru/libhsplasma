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
#include "pySound.h"

extern "C" {

static PyObject* pyFadeParams_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "Cannot construct plFadeParams objects in Python");
    return NULL;
}

static PyObject* pyFadeParams_getLengthInSecs(pyFadeParams* self, void*) {
    return PyFloat_FromDouble(self->fThis->fLengthInSecs);
}

static PyObject* pyFadeParams_getVolStart(pyFadeParams* self, void*) {
    return PyFloat_FromDouble(self->fThis->fVolStart);
}

static PyObject* pyFadeParams_getVolEnd(pyFadeParams* self, void*) {
    return PyFloat_FromDouble(self->fThis->fVolEnd);
}

static PyObject* pyFadeParams_getType(pyFadeParams* self, void*) {
    return PyInt_FromLong(self->fThis->fType);
}

static PyObject* pyFadeParams_getStopWhenDone(pyFadeParams* self, void*) {
    return PyBool_FromLong(self->fThis->fStopWhenDone ? 1 : 0);
}

static PyObject* pyFadeParams_getFadeSoftVol(pyFadeParams* self, void*) {
    return PyBool_FromLong(self->fThis->fFadeSoftVol ? 1 : 0);
}

static PyObject* pyFadeParams_getCurrTime(pyFadeParams* self, void*) {
    return PyFloat_FromDouble(self->fThis->fCurrTime);
}

static int pyFadeParams_setLengthInSecs(pyFadeParams* self, PyObject* value, void*) {
    if (!PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "lengthInSecs should be a float");
        return -1;
    }
    self->fThis->fLengthInSecs = (float)PyFloat_AsDouble(value);
    return 0;
}

static int pyFadeParams_setVolStart(pyFadeParams* self, PyObject* value, void*) {
    if (!PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "volStart should be a float");
        return -1;
    }
    self->fThis->fVolStart = (float)PyFloat_AsDouble(value);
    return 0;
}

static int pyFadeParams_setVolEnd(pyFadeParams* self, PyObject* value, void*) {
    if (!PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "volEnd should be a float");
        return -1;
    }
    self->fThis->fVolEnd = (float)PyFloat_AsDouble(value);
    return 0;
}

static int pyFadeParams_setType(pyFadeParams* self, PyObject* value, void*) {
    if (!PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "type should be an int");
        return -1;
    }
    self->fThis->fType = (unsigned char)PyInt_AsLong(value);
    return 0;
}

static int pyFadeParams_setStopWhenDone(pyFadeParams* self, PyObject* value, void*) {
    if (!PyBool_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "stopWhenDone should be a boolean");
        return -1;
    }
    self->fThis->fStopWhenDone = PyInt_AsLong(value) != 0;
    return 0;
}

static int pyFadeParams_setFadeSoftVol(pyFadeParams* self, PyObject* value, void*) {
    if (!PyBool_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "fadeSoftVol should be a boolean");
        return -1;
    }
    self->fThis->fFadeSoftVol = PyInt_AsLong(value) != 0;
    return 0;
}

static int pyFadeParams_setCurrTime(pyFadeParams* self, PyObject* value, void*) {
    if (!PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "currTime should be a float");
        return -1;
    }
    self->fThis->fCurrTime = (float)PyFloat_AsDouble(value);
    return 0;
}

static PyGetSetDef pyFadeParams_GetSet[] = {
    { _pycs("lengthInSecs"), (getter)pyFadeParams_getLengthInSecs,
      (setter)pyFadeParams_setLengthInSecs, NULL, NULL },
    { _pycs("volStart"), (getter)pyFadeParams_getVolStart,
      (setter)pyFadeParams_setVolStart, NULL, NULL },
    { _pycs("volEnd"), (getter)pyFadeParams_getVolEnd,
      (setter)pyFadeParams_setVolEnd, NULL, NULL },
    { _pycs("type"), (getter)pyFadeParams_getType,
      (setter)pyFadeParams_setType, NULL, NULL },
    { _pycs("stopWhenDone"), (getter)pyFadeParams_getStopWhenDone,
      (setter)pyFadeParams_setStopWhenDone, NULL, NULL },
    { _pycs("fadeSoftVol"), (getter)pyFadeParams_getFadeSoftVol,
      (setter)pyFadeParams_setFadeSoftVol, NULL, NULL },
    { _pycs("currTime"), (getter)pyFadeParams_getCurrTime,
      (setter)pyFadeParams_setCurrTime, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyFadeParams_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plFadeParams",          /* tp_name */
    sizeof(pyFadeParams),               /* tp_basicsize */
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

    Py_TPFLAGS_DEFAULT,                 /* tp_flags */
    "plFadeParams wrapper",             /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyFadeParams_GetSet,                /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyFadeParams_new,                   /* tp_new */
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

PyObject* Init_pyFadeParams_Type() {
    if (PyType_Ready(&pyFadeParams_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyFadeParams_Type.tp_dict,
                         "kLinear", PyInt_FromLong(plSound::plFadeParams::kLinear));
    PyDict_SetItemString(pyFadeParams_Type.tp_dict,
                         "kLogarithmic", PyInt_FromLong(plSound::plFadeParams::kLogarithmic));
    PyDict_SetItemString(pyFadeParams_Type.tp_dict,
                         "kExponential", PyInt_FromLong(plSound::plFadeParams::kExponential));

    Py_INCREF(&pyFadeParams_Type);
    return (PyObject*)&pyFadeParams_Type;
}

PyObject* pyFadeParams_FromFadeParams(plSound::plFadeParams& params) {
    pyFadeParams* pyObj = PyObject_New(pyFadeParams, &pyFadeParams_Type);
    pyObj->fThis = &params;
    return (PyObject*)pyObj;
}

}
