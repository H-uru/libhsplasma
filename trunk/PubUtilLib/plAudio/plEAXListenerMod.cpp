#include "plEAXListenerMod.h"

plEAXListenerMod::plEAXListenerMod() { }
plEAXListenerMod::~plEAXListenerMod() { }

IMPLEMENT_CREATABLE(plEAXListenerMod, kEAXListenerMod, plSingleModifier)

void plEAXListenerMod::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    fSoftRegion = mgr->readKey(S);
    fListenerProps.ulEnvironment = S->readInt();
    fListenerProps.flEnvironmentSize = S->readFloat();
    fListenerProps.flEnvironmentDiffusion = S->readFloat();
    fListenerProps.lRoom = S->readInt();
    fListenerProps.lRoomHF = S->readInt();
    fListenerProps.lRoomLF = S->readInt();
    fListenerProps.flDecayTime = S->readFloat();
    fListenerProps.flDecayHFRatio = S->readFloat();
    fListenerProps.flDecayLFRatio = S->readFloat();
    fListenerProps.lReflections = S->readInt();
    fListenerProps.flReflectionsDelay = S->readFloat();
    fListenerProps.lReverb = S->readInt();
    fListenerProps.flReverbDelay = S->readFloat();
    fListenerProps.flEchoTime = S->readFloat();
    fListenerProps.flEchoDepth = S->readFloat();
    fListenerProps.flModulationTime = S->readFloat();
    fListenerProps.flModulationDepth = S->readFloat();
    fListenerProps.flAirAbsorptionHF = S->readFloat();
    fListenerProps.flHFReference = S->readFloat();
    fListenerProps.flLFReference = S->readFloat();
    fListenerProps.flRoomRolloffFactor = S->readFloat();
    fListenerProps.ulFlags = S->readInt();
}

void plEAXListenerMod::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);

    mgr->writeKey(S, fSoftRegion);
    S->writeInt(fListenerProps.ulEnvironment);
    S->writeFloat(fListenerProps.flEnvironmentSize);
    S->writeFloat(fListenerProps.flEnvironmentDiffusion);
    S->writeInt(fListenerProps.lRoom);
    S->writeInt(fListenerProps.lRoomHF);
    S->writeInt(fListenerProps.lRoomLF);
    S->writeFloat(fListenerProps.flDecayTime);
    S->writeFloat(fListenerProps.flDecayHFRatio);
    S->writeFloat(fListenerProps.flDecayLFRatio);
    S->writeInt(fListenerProps.lReflections);
    S->writeFloat(fListenerProps.flReflectionsDelay);
    S->writeInt(fListenerProps.lReverb);
    S->writeFloat(fListenerProps.flReverbDelay);
    S->writeFloat(fListenerProps.flEchoTime);
    S->writeFloat(fListenerProps.flEchoDepth);
    S->writeFloat(fListenerProps.flModulationTime);
    S->writeFloat(fListenerProps.flModulationDepth);
    S->writeFloat(fListenerProps.flAirAbsorptionHF);
    S->writeFloat(fListenerProps.flHFReference);
    S->writeFloat(fListenerProps.flLFReference);
    S->writeFloat(fListenerProps.flRoomRolloffFactor);
    S->writeInt(fListenerProps.ulFlags);
}

void plEAXListenerMod::IPrcWrite(pfPrcHelper* prc) {
    plSingleModifier::IPrcWrite(prc);

    prc->writeSimpleTag("SoftRegion");
    fSoftRegion->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("ListenerProperties");
    prc->startTag("EAXREVERBPROPERTIES");
    prc->writeParam("Environment", fListenerProps.ulEnvironment);
    prc->writeParam("EnvironmentSize", fListenerProps.flEnvironmentSize);
    prc->writeParam("EnvironmentDiffusion", fListenerProps.flEnvironmentDiffusion);
    prc->writeParam("Room", fListenerProps.lRoom);
    prc->writeParam("RoomHF", fListenerProps.lRoomHF);
    prc->writeParam("RoomLF", fListenerProps.lRoomLF);
    prc->writeParam("DecayTime", fListenerProps.flDecayTime);
    prc->writeParam("DecayHFRatio", fListenerProps.flDecayHFRatio);
    prc->writeParam("DecayLFRatio", fListenerProps.flDecayLFRatio);
    prc->writeParam("Reflections", fListenerProps.lReflections);
    prc->writeParam("ReflectionsDelay", fListenerProps.flReflectionsDelay);
    prc->writeParam("Reverb", fListenerProps.lReverb);
    prc->writeParam("ReverbDelay", fListenerProps.flReverbDelay);
    prc->writeParam("EchoTime", fListenerProps.flEchoTime);
    prc->writeParam("EchoDepth", fListenerProps.flEchoDepth);
    prc->writeParam("ModulationTime", fListenerProps.flModulationTime);
    prc->writeParam("ModulationDepth", fListenerProps.flModulationDepth);
    prc->writeParam("AirAbsorptionHF", fListenerProps.flAirAbsorptionHF);
    prc->writeParam("HFReference", fListenerProps.flHFReference);
    prc->writeParam("LFReference", fListenerProps.flLFReference);
    prc->writeParam("RoomRolloffFactor", fListenerProps.flRoomRolloffFactor);
    prc->writeParamHex("Flags", fListenerProps.ulFlags);
    prc->endTag(true);
    prc->closeTag();
}
