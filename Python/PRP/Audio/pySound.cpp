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

#include "pySound.h"

#include "PRP/Object/pySynchedObject.h"
#include "PRP/pyCreatable.h"
#include "PRP/KeyedObject/pyKey.h"

extern "C" {

PY_PLASMA_NEW_MSG(Sound, "plSound is abstract")

PY_PROPERTY(unsigned char, Sound, type, getType, setType)
PY_PROPERTY(unsigned char, Sound, priority, getPriority, setPriority)
PY_PROPERTY(bool, Sound, isPlaying, isPlaying, setPlaying)
PY_PROPERTY(double, Sound, time, getTime, setTime)
PY_PROPERTY(int, Sound, maxFalloff, getMaxFalloff, setMaxFalloff)
PY_PROPERTY(int, Sound, minFalloff, getMinFalloff, setMinFalloff)
PY_PROPERTY(int, Sound, outerVol, getOuterVol, setOuterVol)
PY_PROPERTY(int, Sound, innerCone, getInnerCone, setInnerCone)
PY_PROPERTY(int, Sound, outerCone, getOuterCone, setOuterCone)
PY_PROPERTY(float, Sound, currVolume, getCurrVolume, setCurrVolume)
PY_PROPERTY(float, Sound, desiredVolume, getDesiredVolume, setDesiredVolume)
PY_PROPERTY(float, Sound, fadedVolume, getFadedVolume, setFadedVolume)
PY_PROPERTY(unsigned int, Sound, properties, getProperties, setProperties)
PY_PROPERTY_PROXY_RO(plSound::plFadeParams, Sound, fadeInParams, getFadeInParams)
PY_PROPERTY_PROXY_RO(plSound::plFadeParams, Sound, fadeOutParams, getFadeOutParams)
PY_PROPERTY(plKey, Sound, softRegion, getSoftRegion, setSoftRegion)
PY_PROPERTY(plKey, Sound, softOcclusionRegion, getSoftOcclusionRegion, setSoftOcclusionRegion)
PY_PROPERTY(plKey, Sound, dataBuffer, getDataBuffer, setDataBuffer)
PY_PROPERTY(plString, Sound, subtitleId, getSubtitleId, setSubtitleId)

static PyGetSetDef pySound_GetSet[] = {
    pySound_type_getset,
    pySound_priority_getset,
    pySound_isPlaying_getset,
    pySound_time_getset,
    pySound_maxFalloff_getset,
    pySound_minFalloff_getset,
    pySound_outerVol_getset,
    pySound_innerCone_getset,
    pySound_outerCone_getset,
    pySound_currVolume_getset,
    pySound_desiredVolume_getset,
    pySound_fadedVolume_getset,
    pySound_properties_getset,
    pySound_fadeInParams_getset,
    pySound_fadeOutParams_getset,
    pySound_softRegion_getset,
    pySound_softOcclusionRegion_getset,
    pySound_dataBuffer_getset,
    pySound_subtitleId_getset,
    PY_GETSET_TERMINATOR
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

PY_PLASMA_IFC_METHODS(Sound, plSound)

}
