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
#include "Math/pyGeometry3.h"
#include "Sys/pyColor.h"

extern "C" {

static PyObject* pyFixedWaterState7_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyFixedWaterState7* self = (pyFixedWaterState7*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plFixedWaterState7();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyFixedWaterState7_getGeoState(pyFixedWaterState7* self, void*) {
    return pyWaveState7_FromWaveState7(&self->fThis->getGeoState());
}

static PyObject* pyFixedWaterState7_getTexState(pyFixedWaterState7* self, void*) {
    return pyWaveState7_FromWaveState7(&self->fThis->getTexState());
}

static PyObject* pyFixedWaterState7_getRippleScale(pyFixedWaterState7* self, void*) {
    return PyFloat_FromDouble(self->fThis->getRippleScale());
}

static PyObject* pyFixedWaterState7_getWaterHeight(pyFixedWaterState7* self, void*) {
    return PyFloat_FromDouble(self->fThis->getWaterHeight());
}

static PyObject* pyFixedWaterState7_getWindDir(pyFixedWaterState7* self, void*) {
    return pyVector3_FromVector3(self->fThis->getWindDir());
}

static PyObject* pyFixedWaterState7_getSpecVec(pyFixedWaterState7* self, void*) {
    return pyVector3_FromVector3(self->fThis->getSpecVector());
}

static PyObject* pyFixedWaterState7_getWaterOffset(pyFixedWaterState7* self, void*) {
    return pyVector3_FromVector3(self->fThis->getWaterOffset());
}

static PyObject* pyFixedWaterState7_getMaxAtten(pyFixedWaterState7* self, void*) {
    return pyVector3_FromVector3(self->fThis->getMaxAtten());
}

static PyObject* pyFixedWaterState7_getMinAtten(pyFixedWaterState7* self, void*) {
    return pyVector3_FromVector3(self->fThis->getMinAtten());
}

static PyObject* pyFixedWaterState7_getDepthFalloff(pyFixedWaterState7* self, void*) {
    return pyVector3_FromVector3(self->fThis->getDepthFalloff());
}

static PyObject* pyFixedWaterState7_getWispiness(pyFixedWaterState7* self, void*) {
    return PyFloat_FromDouble(self->fThis->getWispiness());
}

static PyObject* pyFixedWaterState7_getShoreTint(pyFixedWaterState7* self, void*) {
    return pyColorRGBA_FromColorRGBA(self->fThis->getShoreTint());
}

static PyObject* pyFixedWaterState7_getMaxColor(pyFixedWaterState7* self, void*) {
    return pyColorRGBA_FromColorRGBA(self->fThis->getMaxColor());
}

static PyObject* pyFixedWaterState7_getMinColor(pyFixedWaterState7* self, void*) {
    return pyColorRGBA_FromColorRGBA(self->fThis->getMinColor());
}

static PyObject* pyFixedWaterState7_getEdgeOpac(pyFixedWaterState7* self, void*) {
    return PyFloat_FromDouble(self->fThis->getEdgeOpacity());
}

static PyObject* pyFixedWaterState7_getEdgeRadius(pyFixedWaterState7* self, void*) {
    return PyFloat_FromDouble(self->fThis->getEdgeRadius());
}

static PyObject* pyFixedWaterState7_getPeriod(pyFixedWaterState7* self, void*) {
    return PyFloat_FromDouble(self->fThis->getPeriod());
}

static PyObject* pyFixedWaterState7_getFingerLength(pyFixedWaterState7* self, void*) {
    return PyFloat_FromDouble(self->fThis->getFingerLength());
}

static PyObject* pyFixedWaterState7_getWaterTint(pyFixedWaterState7* self, void*) {
    return pyColorRGBA_FromColorRGBA(self->fThis->getWaterTint());
}

static PyObject* pyFixedWaterState7_getSpecularTint(pyFixedWaterState7* self, void*) {
    return pyColorRGBA_FromColorRGBA(self->fThis->getSpecularTint());
}

static PyObject* pyFixedWaterState7_getEnvCenter(pyFixedWaterState7* self, void*) {
    return pyVector3_FromVector3(self->fThis->getEnvCenter());
}

static PyObject* pyFixedWaterState7_getEnvRadius(pyFixedWaterState7* self, void*) {
    return PyFloat_FromDouble(self->fThis->getEnvRadius());
}

static PyObject* pyFixedWaterState7_getEnvRefresh(pyFixedWaterState7* self, void*) {
    return PyFloat_FromDouble(self->fThis->getEnvRefresh());
}

static int pyFixedWaterState7_setGeoState(pyFixedWaterState7* self, PyObject* value, void*) {
    if (value == NULL || !pyWaveState7_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "geoState expects a plFixedWaterState7.WaveState");
        return -1;
    }
    self->fThis->setGeoState(*((pyWaveState7*)value)->fThis);
    return 0;
}

static int pyFixedWaterState7_setTexState(pyFixedWaterState7* self, PyObject* value, void*) {
    if (value == NULL || !pyWaveState7_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "texState expects a plFixedWaterState7.WaveState");
        return -1;
    }
    self->fThis->setTexState(*((pyWaveState7*)value)->fThis);
    return 0;
}

static int pyFixedWaterState7_setRippleScale(pyFixedWaterState7* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "rippleScale should be a float");
        return -1;
    }
    self->fThis->setRippleScale((float)PyFloat_AsDouble(value));
    return 0;
}

static int pyFixedWaterState7_setWaterHeight(pyFixedWaterState7* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "waterHeight should be a float");
        return -1;
    }
    self->fThis->setWaterHeight((float)PyFloat_AsDouble(value));
    return 0;
}

static int pyFixedWaterState7_setWindDir(pyFixedWaterState7* self, PyObject* value, void*) {
    if (value == NULL || !pyVector3_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "windDir should be an hsVector3");
        return -1;
    }
    self->fThis->setWindDir(*((pyVector3*)value)->fThis);
    return 0;
}

static int pyFixedWaterState7_setSpecVec(pyFixedWaterState7* self, PyObject* value, void*) {
    if (value == NULL || !pyVector3_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "specVector should be an hsVector3");
        return -1;
    }
    self->fThis->setSpecVector(*((pyVector3*)value)->fThis);
    return 0;
}

static int pyFixedWaterState7_setWaterOffset(pyFixedWaterState7* self, PyObject* value, void*) {
    if (value == NULL || !pyVector3_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "waterOffset should be an hsVector3");
        return -1;
    }
    self->fThis->setWaterOffset(*((pyVector3*)value)->fThis);
    return 0;
}

static int pyFixedWaterState7_setMaxAtten(pyFixedWaterState7* self, PyObject* value, void*) {
    if (value == NULL || !pyVector3_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "maxAtten should be an hsVector3");
        return -1;
    }
    self->fThis->setMaxAtten(*((pyVector3*)value)->fThis);
    return 0;
}

static int pyFixedWaterState7_setMinAtten(pyFixedWaterState7* self, PyObject* value, void*) {
    if (value == NULL || !pyVector3_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "minAtten should be an hsVector3");
        return -1;
    }
    self->fThis->setMinAtten(*((pyVector3*)value)->fThis);
    return 0;
}

static int pyFixedWaterState7_setDepthFalloff(pyFixedWaterState7* self, PyObject* value, void*) {
    if (value == NULL || !pyVector3_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "depthFalloff should be an hsVector3");
        return -1;
    }
    self->fThis->setDepthFalloff(*((pyVector3*)value)->fThis);
    return 0;
}

static int pyFixedWaterState7_setWispiness(pyFixedWaterState7* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "wispiness should be a float");
        return -1;
    }
    self->fThis->setWispiness((float)PyFloat_AsDouble(value));
    return 0;
}

static int pyFixedWaterState7_setShoreTint(pyFixedWaterState7* self, PyObject* value, void*) {
    if (value == NULL || !pyColorRGBA_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "shoreTint should be an hsColorRGBA");
        return -1;
    }
    self->fThis->setShoreTint(*((pyColorRGBA*)value)->fThis);
    return 0;
}

static int pyFixedWaterState7_setMaxColor(pyFixedWaterState7* self, PyObject* value, void*) {
    if (value == NULL || !pyColorRGBA_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "maxColor should be an hsColorRGBA");
        return -1;
    }
    self->fThis->setMaxColor(*((pyColorRGBA*)value)->fThis);
    return 0;
}

static int pyFixedWaterState7_setMinColor(pyFixedWaterState7* self, PyObject* value, void*) {
    if (value == NULL || !pyColorRGBA_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "minColor should be an hsColorRGBA");
        return -1;
    }
    self->fThis->setMinColor(*((pyColorRGBA*)value)->fThis);
    return 0;
}

static int pyFixedWaterState7_setEdgeOpac(pyFixedWaterState7* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "edgeOpacity should be a float");
        return -1;
    }
    self->fThis->setEdgeOpacity((float)PyFloat_AsDouble(value));
    return 0;
}

static int pyFixedWaterState7_setEdgeRadius(pyFixedWaterState7* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "edgeRadius should be a float");
        return -1;
    }
    self->fThis->setEdgeRadius((float)PyFloat_AsDouble(value));
    return 0;
}

static int pyFixedWaterState7_setPeriod(pyFixedWaterState7* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "period should be a float");
        return -1;
    }
    self->fThis->setPeriod((float)PyFloat_AsDouble(value));
    return 0;
}

static int pyFixedWaterState7_setFingerLength(pyFixedWaterState7* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "fingerLength should be a float");
        return -1;
    }
    self->fThis->setFingerLength((float)PyFloat_AsDouble(value));
    return 0;
}

static int pyFixedWaterState7_setWaterTint(pyFixedWaterState7* self, PyObject* value, void*) {
    if (value == NULL || !pyColorRGBA_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "waterTint should be an hsColorRGBA");
        return -1;
    }
    self->fThis->setWaterTint(*((pyColorRGBA*)value)->fThis);
    return 0;
}

static int pyFixedWaterState7_setSpecularTint(pyFixedWaterState7* self, PyObject* value, void*) {
    if (value == NULL || !pyColorRGBA_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "specularTine should be an hsColorRGBA");
        return -1;
    }
    self->fThis->setSpecularTint(*((pyColorRGBA*)value)->fThis);
    return 0;
}

static int pyFixedWaterState7_setEnvCenter(pyFixedWaterState7* self, PyObject* value, void*) {
    if (value == NULL || !pyVector3_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "envCenter should be an hsVector3");
        return -1;
    }
    self->fThis->setEnvCenter(*((pyVector3*)value)->fThis);
    return 0;
}

static int pyFixedWaterState7_setEnvRadius(pyFixedWaterState7* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "envRadius should be a float");
        return -1;
    }
    self->fThis->setEnvRadius((float)PyFloat_AsDouble(value));
    return 0;
}

static int pyFixedWaterState7_setEnvRefresh(pyFixedWaterState7* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "envRefresh should be a float");
        return -1;
    }
    self->fThis->setFingerLength((float)PyFloat_AsDouble(value));
    return 0;
}

static PyGetSetDef pyFixedWaterState7_GetSet[] = {
    { _pycs("geoState"), (getter)pyFixedWaterState7_getGeoState, (setter)pyFixedWaterState7_setGeoState, NULL, NULL },
    { _pycs("texState"), (getter)pyFixedWaterState7_getTexState, (setter)pyFixedWaterState7_setTexState, NULL, NULL },
    { _pycs("rippleScale"), (getter)pyFixedWaterState7_getRippleScale, (setter)pyFixedWaterState7_setRippleScale, NULL, NULL },
    { _pycs("waterHeight"), (getter)pyFixedWaterState7_getWaterHeight, (setter)pyFixedWaterState7_setWaterHeight, NULL, NULL },
    { _pycs("windDir"), (getter)pyFixedWaterState7_getWindDir, (setter)pyFixedWaterState7_setWindDir, NULL, NULL },
    { _pycs("specVector"), (getter)pyFixedWaterState7_getSpecVec, (setter)pyFixedWaterState7_setSpecVec, NULL, NULL },
    { _pycs("waterOffset"), (getter)pyFixedWaterState7_getWaterOffset, (setter)pyFixedWaterState7_setWaterOffset, NULL, NULL },
    { _pycs("maxAtten"), (getter)pyFixedWaterState7_getMaxAtten, (setter)pyFixedWaterState7_setMaxAtten, NULL, NULL },
    { _pycs("minAtten"), (getter)pyFixedWaterState7_getMinAtten, (setter)pyFixedWaterState7_setMinAtten, NULL, NULL },
    { _pycs("depthFalloff"), (getter)pyFixedWaterState7_getDepthFalloff, (setter)pyFixedWaterState7_setDepthFalloff, NULL, NULL },
    { _pycs("wispiness"), (getter)pyFixedWaterState7_getWispiness, (setter)pyFixedWaterState7_setWispiness, NULL, NULL },
    { _pycs("shoreTint"), (getter)pyFixedWaterState7_getShoreTint, (setter)pyFixedWaterState7_setShoreTint, NULL, NULL },
    { _pycs("maxColor"), (getter)pyFixedWaterState7_getMaxColor, (setter)pyFixedWaterState7_setMaxColor, NULL, NULL },
    { _pycs("minColor"), (getter)pyFixedWaterState7_getMinColor, (setter)pyFixedWaterState7_setMinColor, NULL, NULL },
    { _pycs("edgeOpacity"), (getter)pyFixedWaterState7_getEdgeOpac, (setter)pyFixedWaterState7_setEdgeOpac, NULL, NULL },
    { _pycs("edgeRadius"), (getter)pyFixedWaterState7_getEdgeRadius, (setter)pyFixedWaterState7_setEdgeRadius, NULL, NULL },
    { _pycs("period"), (getter)pyFixedWaterState7_getPeriod, (setter)pyFixedWaterState7_setPeriod, NULL, NULL },
    { _pycs("fingerLength"), (getter)pyFixedWaterState7_getFingerLength, (setter)pyFixedWaterState7_setFingerLength, NULL, NULL },
    { _pycs("waterTint"), (getter)pyFixedWaterState7_getWaterTint, (setter)pyFixedWaterState7_setWaterTint, NULL, NULL },
    { _pycs("specularTint"), (getter)pyFixedWaterState7_getSpecularTint, (setter)pyFixedWaterState7_setSpecularTint, NULL, NULL },
    { _pycs("envCenter"), (getter)pyFixedWaterState7_getEnvCenter, (setter)pyFixedWaterState7_setEnvCenter, NULL, NULL },
    { _pycs("envRadius"), (getter)pyFixedWaterState7_getEnvRadius, (setter)pyFixedWaterState7_setEnvRadius, NULL, NULL },
    { _pycs("envRefresh"), (getter)pyFixedWaterState7_getEnvRefresh, (setter)pyFixedWaterState7_setEnvRefresh, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyFixedWaterState7_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plFixedWaterState7",    /* tp_name */
    sizeof(pyFixedWaterState7),         /* tp_basicsize */
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
    pyFixedWaterState7_GetSet,          /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyFixedWaterState7_new,             /* tp_new */
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

PyObject* Init_pyFixedWaterState7_Type() {
    if (PyType_Ready(&pyFixedWaterState7_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyFixedWaterState7_Type.tp_dict, "WaveState", Init_pyWaveState7_Type());

    Py_INCREF(&pyFixedWaterState7_Type);
    return (PyObject*)&pyFixedWaterState7_Type;
}

int pyFixedWaterState7_Check(PyObject* obj) {
    if (obj->ob_type == &pyFixedWaterState7_Type
        || PyType_IsSubtype(obj->ob_type, &pyFixedWaterState7_Type))
        return 1;
    return 0;
}

PyObject* pyFixedWaterState7_FromFixedWaterState7(plFixedWaterState7* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyFixedWaterState7* pyobj = PyObject_New(pyFixedWaterState7, &pyFixedWaterState7_Type);
    pyobj->fThis = obj;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
