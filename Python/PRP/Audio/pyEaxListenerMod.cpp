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

#include "pyEAXListenerMod.h"

#include <PRP/Audio/plEAXListenerMod.h>
#include "PRP/Modifier/pyModifier.h"
#include "PRP/KeyedObject/pyKey.h"

PY_PLASMA_NEW(EAXListenerMod, plEAXListenerMod)

PY_PROPERTY(plKey, EAXListenerMod, softRegion, getSoftRegion, setSoftRegion)

PY_GETSET_GETTER_DECL(EAXListenerMod, listenerProps)
{
    // This cannot be a subclass, since it's an inline member
    return pyEAXReverbProperties_FromEAXReverbProperties(self->fThis->getListenerProps());
}

PY_GETSET_SETTER_DECL(EAXListenerMod, listenerProps)
{
    PY_PROPERTY_CHECK_NULL(listenerProps)

    EAXREVERBPROPERTIES& eaxrp = self->fThis->getListenerProps();
    if (value == Py_None) {
        eaxrp = EAXREVERBPROPERTIES();
        self->fThis->setListenerProps(eaxrp);
        return 0;
    }
    else if (pyEAXReverbProperties_Check(value)) {
        eaxrp = *((pyEAXReverbProperties*)value)->fThis;
        self->fThis->setListenerProps(eaxrp);
        return 0;
    }
    else {
        PyErr_SetString(PyExc_TypeError, "listenerProps must be a EAXReverbProperties");
        return -1;
    }
}

PY_PROPERTY_GETSET_DECL(EAXListenerMod, listenerProps)

static PyGetSetDef pyEAXListenerMod_GetSet[] = {
    pyEAXListenerMod_softRegion_getset,
    pyEAXListenerMod_listenerProps_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(EAXListenerMod, plEAXListenerMod,
               "plEAXListenerMod wrapper")

PY_PLASMA_TYPE_INIT(EAXListenerMod)
{
    pyEAXListenerMod_Type.tp_new = pyEAXListenerMod_new;
    pyEAXListenerMod_Type.tp_getset = pyEAXListenerMod_GetSet;
    pyEAXListenerMod_Type.tp_base = &pySingleModifier_Type;
    if (PyType_CheckAndReady(&pyEAXListenerMod_Type) < 0)
        return nullptr;

    Py_INCREF(&pyEAXListenerMod_Type);
    return (PyObject*)&pyEAXListenerMod_Type;
}

PY_PLASMA_IFC_METHODS(EAXListenerMod, plEAXListenerMod)

/* EAXReverbProperties */

PY_PLASMA_VALUE_DEALLOC(EAXReverbProperties)
PY_PLASMA_EMPTY_INIT(EAXReverbProperties)
PY_PLASMA_VALUE_NEW(EAXReverbProperties, EAXREVERBPROPERTIES)

PY_PROPERTY_MEMBER(unsigned long, EAXReverbProperties, environment, ulEnvironment)
PY_PROPERTY_MEMBER(float, EAXReverbProperties, environmentSize, flEnvironmentSize)
PY_PROPERTY_MEMBER(float, EAXReverbProperties, environmentDiffusion, flEnvironmentDiffusion)
PY_PROPERTY_MEMBER(long, EAXReverbProperties, room, lRoom)
PY_PROPERTY_MEMBER(long, EAXReverbProperties, roomHF, lRoomHF)
PY_PROPERTY_MEMBER(long, EAXReverbProperties, roomLF, lRoomLF)
PY_PROPERTY_MEMBER(float, EAXReverbProperties, decayTime, flDecayTime)
PY_PROPERTY_MEMBER(float, EAXReverbProperties, decayHFRatio, flDecayHFRatio)
PY_PROPERTY_MEMBER(float, EAXReverbProperties, decayLFRatio, flDecayLFRatio)
PY_PROPERTY_MEMBER(long, EAXReverbProperties, reflections, lReflections)
PY_PROPERTY_MEMBER(float, EAXReverbProperties, reflectionsDelay, flReflectionsDelay)
PY_PROPERTY_MEMBER(long, EAXReverbProperties, reverb, lReverb)
PY_PROPERTY_MEMBER(float, EAXReverbProperties, reverbDelay, flReverbDelay)
PY_PROPERTY_MEMBER(float, EAXReverbProperties, echoTime, flEchoTime)
PY_PROPERTY_MEMBER(float, EAXReverbProperties, echoDepth, flEchoDepth)
PY_PROPERTY_MEMBER(float, EAXReverbProperties, modulationTime, flModulationTime)
PY_PROPERTY_MEMBER(float, EAXReverbProperties, modulationDepth, flModulationDepth)
PY_PROPERTY_MEMBER(float, EAXReverbProperties, airAbsorptionHF, flAirAbsorptionHF)
PY_PROPERTY_MEMBER(float, EAXReverbProperties, hfReference, flHFReference)
PY_PROPERTY_MEMBER(float, EAXReverbProperties, lfReference, flLFReference)
PY_PROPERTY_MEMBER(float, EAXReverbProperties, roomRolloffFactor, flRoomRolloffFactor)
PY_PROPERTY_MEMBER(unsigned long, EAXReverbProperties, flags, ulFlags)

static PyGetSetDef pyEAXReverbProperties_GetSet[] = {
    pyEAXReverbProperties_environment_getset,
    pyEAXReverbProperties_environmentSize_getset,
    pyEAXReverbProperties_environmentDiffusion_getset,
    pyEAXReverbProperties_room_getset,
    pyEAXReverbProperties_roomHF_getset,
    pyEAXReverbProperties_roomLF_getset,
    pyEAXReverbProperties_decayTime_getset,
    pyEAXReverbProperties_decayHFRatio_getset,
    pyEAXReverbProperties_decayLFRatio_getset,
    pyEAXReverbProperties_reflections_getset,
    pyEAXReverbProperties_reflectionsDelay_getset,
    pyEAXReverbProperties_reverb_getset,
    pyEAXReverbProperties_reverbDelay_getset,
    pyEAXReverbProperties_echoTime_getset,
    pyEAXReverbProperties_echoDepth_getset,
    pyEAXReverbProperties_modulationTime_getset,
    pyEAXReverbProperties_modulationDepth_getset,
    pyEAXReverbProperties_airAbsorptionHF_getset,
    pyEAXReverbProperties_hfReference_getset,
    pyEAXReverbProperties_lfReference_getset,
    pyEAXReverbProperties_roomRolloffFactor_getset,
    pyEAXReverbProperties_flags_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(EAXReverbProperties, EAXREVERBPROPERTIES, "EAXREVERBPROPERTIES wrapper")

#define PY_TYPE_ADD_PRESET(preset) \
    PyDict_SetItemString(pyEAXReverbProperties_Type.tp_dict, #preset, \
        pyEAXReverbProperties_FromEAXReverbProperties(EAXREVERBPROPERTIES(##preset##)));

PY_PLASMA_TYPE_INIT(EAXReverbProperties)
{
    pyEAXReverbProperties_Type.tp_dealloc = pyEAXReverbProperties_dealloc;
    pyEAXReverbProperties_Type.tp_init = pyEAXReverbProperties___init__;
    pyEAXReverbProperties_Type.tp_new = pyEAXReverbProperties_new;
    pyEAXReverbProperties_Type.tp_getset = pyEAXReverbProperties_GetSet;
    if (PyType_CheckAndReady(&pyEAXReverbProperties_Type) < 0)
        return nullptr;

    /* EAX reverb presets */
    PY_TYPE_ADD_PRESET(REVERB_PRESET_GENERIC)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_PADDEDCELL)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_ROOM)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_BATHROOM)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_LIVINGROOM)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_STONEROOM)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_AUDITORIUM)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_CONCERTHALL)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_CAVE)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_ARENA)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_HANGAR)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_CARPETTEDHALLWAY)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_HALLWAY)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_STONECORRIDOR)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_ALLEY)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_FOREST)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_CITY)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_MOUNTAINS)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_QUARRY)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_PLAIN)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_PARKINGLOT)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_SEWERPIPE)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_UNDERWATER)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_DRUGGED)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_DIZZY)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_PSYCHOTIC)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_CASTLE_SMALLROOM)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_CASTLE_SHORTPASSAGE)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_CASTLE_MEDIUMROOM)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_CASTLE_LONGPASSAGE)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_CASTLE_LARGEROOM)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_CASTLE_HALL)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_CASTLE_CUPBOARD)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_CASTLE_COURTYARD)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_CASTLE_ALCOVE)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_FACTORY_ALCOVE)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_FACTORY_SHORTPASSAGE)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_FACTORY_MEDIUMROOM)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_FACTORY_LONGPASSAGE)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_FACTORY_LARGEROOM)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_FACTORY_HALL)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_FACTORY_CUPBOARD)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_FACTORY_COURTYARD)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_FACTORY_SMALLROOM)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_ICEPALACE_ALCOVE)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_ICEPALACE_SHORTPASSAGE)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_ICEPALACE_MEDIUMROOM)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_ICEPALACE_LONGPASSAGE)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_ICEPALACE_LARGEROOM)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_ICEPALACE_HALL)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_ICEPALACE_CUPBOARD)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_ICEPALACE_COURTYARD)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_ICEPALACE_SMALLROOM)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_SPACESTATION_ALCOVE)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_SPACESTATION_MEDIUMROOM)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_SPACESTATION_SHORTPASSAGE)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_SPACESTATION_LONGPASSAGE)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_SPACESTATION_LARGEROOM)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_SPACESTATION_HALL)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_SPACESTATION_CUPBOARD)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_SPACESTATION_SMALLROOM)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_WOODEN_ALCOVE)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_WOODEN_SHORTPASSAGE)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_WOODEN_MEDIUMROOM)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_WOODEN_LONGPASSAGE)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_WOODEN_LARGEROOM)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_WOODEN_HALL)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_WOODEN_CUPBOARD)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_WOODEN_SMALLROOM)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_WOODEN_COURTYARD)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_SPORT_EMPTYSTADIUM)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_SPORT_SQUASHCOURT)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_SPORT_SMALLSWIMMINGPOOL)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_SPORT_LARGESWIMMINGPOOL)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_SPORT_GYMNASIUM)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_SPORT_FULLSTADIUM)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_SPORT_STADIUMTANNOY)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_PREFAB_WORKSHOP)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_PREFAB_SCHOOLROOM)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_PREFAB_PRACTISEROOM)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_PREFAB_OUTHOUSE)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_PREFAB_CARAVAN)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_DOME_TOMB)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_PIPE_SMALL)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_DOME_SAINTPAULS)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_PIPE_LONGTHIN)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_PIPE_LARGE)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_PIPE_RESONANT)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_OUTDOORS_BACKYARD)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_OUTDOORS_ROLLINGPLAINS)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_OUTDOORS_DEEPCANYON)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_OUTDOORS_CREEK)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_OUTDOORS_VALLEY)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_MOOD_HEAVEN)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_MOOD_HELL)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_MOOD_MEMORY)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_DRIVING_COMMENTATOR)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_DRIVING_PITGARAGE)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_DRIVING_INCAR_RACER)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_DRIVING_INCAR_SPORTS)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_DRIVING_INCAR_LUXURY)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_DRIVING_FULLGRANDSTAND)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_DRIVING_EMPTYGRANDSTAND)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_DRIVING_TUNNEL)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_CITY_STREETS)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_CITY_SUBWAY)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_CITY_MUSEUM)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_CITY_LIBRARY)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_CITY_UNDERPASS)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_CITY_ABANDONED)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_DUSTYROOM)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_CHAPEL)
    PY_TYPE_ADD_PRESET(REVERB_PRESET_SMALLWATERROOM)

    /* EAX reverb flags */
    PY_TYPE_ADD_CONST(EAXReverbProperties, "kFlagDecayTimeScale", 0x1);
    PY_TYPE_ADD_CONST(EAXReverbProperties, "kFlagReflectionsScale", 0x2);
    PY_TYPE_ADD_CONST(EAXReverbProperties, "kFlagReflectionsDelayScale", 0x4);
    PY_TYPE_ADD_CONST(EAXReverbProperties, "kFlagReverbScale", 0x8);
    PY_TYPE_ADD_CONST(EAXReverbProperties, "kFlagReverbDelayScale", 0x10);
    PY_TYPE_ADD_CONST(EAXReverbProperties, "kFlagEchoTimeScale", 0x40);
    PY_TYPE_ADD_CONST(EAXReverbProperties, "kFlagModulationTimeScale", 0x80);
    PY_TYPE_ADD_CONST(EAXReverbProperties, "kFlagDecayHFLimit", 0x20);

    Py_INCREF(&pyEAXReverbProperties_Type);
    return (PyObject*)&pyEAXReverbProperties_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(EAXReverbProperties, EAXREVERBPROPERTIES)
