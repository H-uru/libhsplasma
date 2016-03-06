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
#include "PRP/Object/pySynchedObject.h"
#include "PRP/pyCreatable.h"
#include "PRP/KeyedObject/pyKey.h"

static inline plSound* IConvertSound(pySound* sound) {
    return plSound::Convert(IConvert((pyCreatable*)sound));
}

extern "C" {

static PyObject* pySound_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "plSound is abstract");
    return NULL;
}

static PyObject* pySound_getType(pySound* self, void*) {
    return PyInt_FromLong(IConvertSound(self)->getType());
}

static PyObject* pySound_getPriority(pySound* self, void*) {
    return PyInt_FromLong(IConvertSound(self)->getPriority());
}

static PyObject* pySound_getIsPlaying(pySound* self, void*) {
    return PyBool_FromLong(IConvertSound(self)->isPlaying() ? 1 : 0);
}

static PyObject* pySound_getTime(pySound* self, void*) {
    return PyFloat_FromDouble(IConvertSound(self)->getTime());
}

static PyObject* pySound_getMaxFalloff(pySound* self, void*) {
    return PyInt_FromLong(IConvertSound(self)->getMaxFalloff());
}

static PyObject* pySound_getMinFalloff(pySound* self, void*) {
    return PyInt_FromLong(IConvertSound(self)->getMinFalloff());
}

static PyObject* pySound_getOuterVol(pySound* self, void*) {
    return PyInt_FromLong(IConvertSound(self)->getOuterVol());
}

static PyObject* pySound_getInnerCone(pySound* self, void*) {
    return PyInt_FromLong(IConvertSound(self)->getInnerCone());
}

static PyObject* pySound_getOuterCone(pySound* self, void*) {
    return PyInt_FromLong(IConvertSound(self)->getOuterCone());
}

static PyObject* pySound_getCurrVolume(pySound* self, void*) {
    return PyFloat_FromDouble(IConvertSound(self)->getCurrVolume());
}

static PyObject* pySound_getDesiredVolume(pySound* self, void*) {
    return PyFloat_FromDouble(IConvertSound(self)->getDesiredVolume());
}

static PyObject* pySound_getFadedVolume(pySound* self, void*) {
    return PyFloat_FromDouble(IConvertSound(self)->getFadedVolume());
}

static PyObject* pySound_getProperties(pySound* self, void*) {
    return PyInt_FromLong(IConvertSound(self)->getProperties());
}

static PyObject* pySound_getFadeInParams(pySound* self, void*) {
    return pyFadeParams_FromFadeParams(IConvertSound(self)->getFadeInParams());
}

static PyObject* pySound_getFadeOutParams(pySound* self, void*) {
    return pyFadeParams_FromFadeParams(IConvertSound(self)->getFadeOutParams());
}

static PyObject* pySound_getSoftRegion(pySound* self, void*) {
    return pyKey_FromKey(IConvertSound(self)->getSoftRegion());
}

static PyObject* pySound_getSoftOcclusionRegion(pySound* self, void*) {
    return pyKey_FromKey(IConvertSound(self)->getSoftOcclusionRegion());
}

static PyObject* pySound_getDataBuffer(pySound* self, void*) {
    return pyKey_FromKey(IConvertSound(self)->getDataBuffer());
}

static PyObject* pySound_getSubtitleId(pySound* self, void*) {
    return PlStr_To_PyStr(IConvertSound(self)->getSubtitleId());
}

static int pySound_setType(pySound* self, PyObject* value, void*) {
    if (!PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "type should be an int");
        return -1;
    }
    IConvertSound(self)->setType((unsigned char)PyInt_AsLong(value));
    return 0;
}

static int pySound_setPriority(pySound* self, PyObject* value, void*) {
    if (!PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "priority should be an int");
        return -1;
    }
    IConvertSound(self)->setPriority((unsigned char)PyInt_AsLong(value));
    return 0;
}

static int pySound_setIsPlaying(pySound* self, PyObject* value, void*) {
    if (!PyBool_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "isPlaying should be a boolean");
        return -1;
    }
    IConvertSound(self)->setPlaying(PyInt_AsLong(value) != 0);
    return 0;
}

static int pySound_setTime(pySound* self, PyObject* value, void*) {
    if (!PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "time should be a float");
        return -1;
    }
    IConvertSound(self)->setTime((float)PyFloat_AsDouble(value));
    return 0;
}

static int pySound_setMaxFalloff(pySound* self, PyObject* value, void*) {
    if (!PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "maxFalloff should be an int");
        return -1;
    }
    IConvertSound(self)->setMaxFalloff(PyInt_AsLong(value));
    return 0;
}

static int pySound_setMinFalloff(pySound* self, PyObject* value, void*) {
    if (!PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "minFalloff should be an int");
        return -1;
    }
    IConvertSound(self)->setMinFalloff(PyInt_AsLong(value));
    return 0;
}

static int pySound_setOuterVol(pySound* self, PyObject* value, void*) {
    if (!PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "outerVol should be an int");
        return -1;
    }
    IConvertSound(self)->setOuterVol(PyInt_AsLong(value));
    return 0;
}

static int pySound_setInnerCone(pySound* self, PyObject* value, void*) {
    if (!PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "innerCone should be an int");
        return -1;
    }
    IConvertSound(self)->setInnerCone(PyInt_AsLong(value));
    return 0;
}

static int pySound_setOuterCone(pySound* self, PyObject* value, void*) {
    if (!PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "outerCone should be an int");
        return -1;
    }
    IConvertSound(self)->setOuterCone(PyInt_AsLong(value));
    return 0;
}

static int pySound_setCurrVolume(pySound* self, PyObject* value, void*) {
    if (!PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "currVolume should be a float");
        return -1;
    }
    IConvertSound(self)->setCurrVolume((float)PyFloat_AsDouble(value));
    return 0;
}

static int pySound_setDesiredVolume(pySound* self, PyObject* value, void*) {
    if (!PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "desiredVolume should be a float");
        return -1;
    }
    IConvertSound(self)->setDesiredVolume((float)PyFloat_AsDouble(value));
    return 0;
}

static int pySound_setFadedVolume(pySound* self, PyObject* value, void*) {
    if (!PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "fadedVolume should be a float");
        return -1;
    }
    IConvertSound(self)->setFadedVolume((float)PyFloat_AsDouble(value));
    return 0;
}

static int pySound_setProperties(pySound* self, PyObject* value, void*) {
    if (!PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "properties should be an int");
        return -1;
    }
    IConvertSound(self)->setProperties(PyInt_AsLong(value));
    return 0;
}

static int pySound_setFadeInParams(pySound* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "fadeInParams cannot be assigned");
    return -1;
}

static int pySound_setFadeOutParams(pySound* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "fadeOutParams cannot be assigned");
    return -1;
}

static int pySound_setSoftRegion(pySound* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        IConvertSound(self)->setSoftRegion(plKey());
        return 0;
    } else if (pyKey_Check(value)) {
        IConvertSound(self)->setSoftRegion(*((pyKey*)value)->fThis);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "softRegion should be a plKey");
        return -1;
    }
}

static int pySound_setSoftOcclusionRegion(pySound* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        IConvertSound(self)->setSoftOcclusionRegion(plKey());
        return 0;
    } else if (pyKey_Check(value)) {
        IConvertSound(self)->setSoftOcclusionRegion(*((pyKey*)value)->fThis);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "softOcclusionRegion should be a plKey");
        return -1;
    }
}

static int pySound_setDataBuffer(pySound* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        IConvertSound(self)->setDataBuffer(plKey());
        return 0;
    } else if (pyKey_Check(value)) {
        IConvertSound(self)->setDataBuffer(*((pyKey*)value)->fThis);
        return 0;
    } else {
        PyErr_SetString(PyExc_TypeError, "dataBuffer should be a plKey");
        return -1;
    }
}

static int pySound_setSubtitleId(pySound* self, PyObject* value, void*) {
    if (!PyAnyStr_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "subtitleId should be a string");
        return -1;
    }
    IConvertSound(self)->setSubtitleId(PyStr_To_PlStr(value));
    return 0;
}

static PyGetSetDef pySound_GetSet[] = {
    { _pycs("type"), (getter)pySound_getType,
      (setter)pySound_setType, NULL, NULL },
    { _pycs("priority"), (getter)pySound_getPriority,
      (setter)pySound_setPriority, NULL, NULL },
    { _pycs("isPlaying"), (getter)pySound_getIsPlaying,
      (setter)pySound_setIsPlaying, NULL, NULL },
    { _pycs("time"), (getter)pySound_getTime,
      (setter)pySound_setTime, NULL, NULL },
    { _pycs("maxFalloff"), (getter)pySound_getMaxFalloff,
      (setter)pySound_setMaxFalloff, NULL, NULL },
    { _pycs("minFalloff"), (getter)pySound_getMinFalloff,
      (setter)pySound_setMinFalloff, NULL, NULL },
    { _pycs("outerVol"), (getter)pySound_getOuterVol,
      (setter)pySound_setOuterVol, NULL, NULL },
    { _pycs("innerCone"), (getter)pySound_getInnerCone,
      (setter)pySound_setInnerCone, NULL, NULL },
    { _pycs("outerCone"), (getter)pySound_getOuterCone,
      (setter)pySound_setOuterCone, NULL, NULL },
    { _pycs("currVolume"), (getter)pySound_getCurrVolume,
      (setter)pySound_setCurrVolume, NULL, NULL },
    { _pycs("desiredVolume"), (getter)pySound_getDesiredVolume,
      (setter)pySound_setDesiredVolume, NULL, NULL },
    { _pycs("fadedVolume"), (getter)pySound_getFadedVolume,
      (setter)pySound_setFadedVolume, NULL, NULL },
    { _pycs("properties"), (getter)pySound_getProperties,
      (setter)pySound_setProperties, NULL, NULL },
    { _pycs("fadeInParams"), (getter)pySound_getFadeInParams,
      (setter)pySound_setFadeInParams, NULL, NULL },
    { _pycs("fadeOutParams"), (getter)pySound_getFadeOutParams,
      (setter)pySound_setFadeOutParams, NULL, NULL },
    { _pycs("softRegion"), (getter)pySound_getSoftRegion,
      (setter)pySound_setSoftRegion, NULL, NULL },
    { _pycs("softOcclusionRegion"), (getter)pySound_getSoftOcclusionRegion,
      (setter)pySound_setSoftOcclusionRegion, NULL, NULL },
    { _pycs("dataBuffer"), (getter)pySound_getDataBuffer,
      (setter)pySound_setDataBuffer, NULL, NULL },
    { _pycs("subtitleId"), (getter)pySound_getSubtitleId,
      (setter)pySound_setSubtitleId, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pySound_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plSound",               /* tp_name */
    sizeof(pySound),                    /* tp_basicsize */
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
    "plSound wrapper",           /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pySound_GetSet,                     /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pySound_new,                        /* tp_new */
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

PyObject* Init_pySound_Type() {
    pySound_Type.tp_base = &pySynchedObject_Type;
    if (PyType_Ready(&pySound_Type) < 0)
        return NULL;

    /* Konstants */
    PyDict_SetItemString(pySound_Type.tp_dict,
                         "kPropIs3DSound", PyInt_FromLong(plSound::kPropIs3DSound));
    PyDict_SetItemString(pySound_Type.tp_dict,
                         "kPropDisableLOD", PyInt_FromLong(plSound::kPropDisableLOD));
    PyDict_SetItemString(pySound_Type.tp_dict,
                         "kPropLooping", PyInt_FromLong(plSound::kPropLooping));
    PyDict_SetItemString(pySound_Type.tp_dict,
                         "kPropAutoStart", PyInt_FromLong(plSound::kPropAutoStart));
    PyDict_SetItemString(pySound_Type.tp_dict,
                         "kPropLocalOnly", PyInt_FromLong(plSound::kPropLocalOnly));
    PyDict_SetItemString(pySound_Type.tp_dict,
                         "kPropLoadOnlyOnCall", PyInt_FromLong(plSound::kPropLoadOnlyOnCall));
    PyDict_SetItemString(pySound_Type.tp_dict,
                         "kPropFullyDisabled", PyInt_FromLong(plSound::kPropFullyDisabled));
    PyDict_SetItemString(pySound_Type.tp_dict,
                         "kPropDontFade", PyInt_FromLong(plSound::kPropDontFade));
    PyDict_SetItemString(pySound_Type.tp_dict,
                         "kPropIncidental", PyInt_FromLong(plSound::kPropIncidental));

    PyDict_SetItemString(pySound_Type.tp_dict,
                         "kSoundFX", PyInt_FromLong(plSound::kSoundFX));
    PyDict_SetItemString(pySound_Type.tp_dict,
                         "kAmbience", PyInt_FromLong(plSound::kAmbience));
    PyDict_SetItemString(pySound_Type.tp_dict,
                         "kBackgroundMusic", PyInt_FromLong(plSound::kBackgroundMusic));
    PyDict_SetItemString(pySound_Type.tp_dict,
                         "kGUISound", PyInt_FromLong(plSound::kGUISound));
    PyDict_SetItemString(pySound_Type.tp_dict,
                         "kNPCVoices", PyInt_FromLong(plSound::kNPCVoices));

    /* Subclass */
    PyDict_SetItemString(pySound_Type.tp_dict,
                         "plFadeParams", Init_pyFadeParams_Type());

    Py_INCREF(&pySound_Type);
    return (PyObject*)&pySound_Type;
}

int pySound_Check(PyObject* obj) {
    if (obj->ob_type == &pySound_Type
        || PyType_IsSubtype(obj->ob_type, &pySound_Type))
        return 1;
    return 0;
}

PyObject* pySound_FromSound(class plSound* sound) {
    if (sound == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pySound* intf = PyObject_New(pySound, &pySound_Type);
    intf->fThis = sound;
    intf->fPyOwned = false;
    return (PyObject*)intf;
}

}
