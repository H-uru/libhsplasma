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
PY_PROPERTY(ST::string, Sound, subtitleId, getSubtitleId, setSubtitleId)

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

PY_PLASMA_TYPE(Sound, plSound, "plSound wrapper")

PY_PLASMA_TYPE_INIT(Sound)
{
    pySound_Type.tp_new = pySound_new;
    pySound_Type.tp_getset = pySound_GetSet;
    pySound_Type.tp_base = &pySynchedObject_Type;
    if (PyType_CheckAndReady(&pySound_Type) < 0)
        return nullptr;

    /* Konstants */
    PY_TYPE_ADD_CONST(Sound, "kPropIs3DSound", plSound::kPropIs3DSound);
    PY_TYPE_ADD_CONST(Sound, "kPropDisableLOD", plSound::kPropDisableLOD);
    PY_TYPE_ADD_CONST(Sound, "kPropLooping", plSound::kPropLooping);
    PY_TYPE_ADD_CONST(Sound, "kPropAutoStart", plSound::kPropAutoStart);
    PY_TYPE_ADD_CONST(Sound, "kPropLocalOnly", plSound::kPropLocalOnly);
    PY_TYPE_ADD_CONST(Sound, "kPropLoadOnlyOnCall", plSound::kPropLoadOnlyOnCall);
    PY_TYPE_ADD_CONST(Sound, "kPropFullyDisabled", plSound::kPropFullyDisabled);
    PY_TYPE_ADD_CONST(Sound, "kPropDontFade", plSound::kPropDontFade);
    PY_TYPE_ADD_CONST(Sound, "kPropIncidental", plSound::kPropIncidental);

    PY_TYPE_ADD_CONST(Sound, "kSoundFX", plSound::kSoundFX);
    PY_TYPE_ADD_CONST(Sound, "kAmbience", plSound::kAmbience);
    PY_TYPE_ADD_CONST(Sound, "kBackgroundMusic", plSound::kBackgroundMusic);
    PY_TYPE_ADD_CONST(Sound, "kGUISound", plSound::kGUISound);
    PY_TYPE_ADD_CONST(Sound, "kNPCVoices", plSound::kNPCVoices);

    /* Nested class */
    PyDict_SetItemString(pySound_Type.tp_dict,
                         "plFadeParams", Init_pyFadeParams_Type());

    Py_INCREF(&pySound_Type);
    return (PyObject*)&pySound_Type;
}

PY_PLASMA_IFC_METHODS(Sound, plSound)
