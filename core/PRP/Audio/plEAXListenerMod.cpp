#include "plEAXListenerMod.h"

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

void plEAXListenerMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "SoftRegion") {
        if (tag->hasChildren())
            fSoftRegion = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "ListenerProperties") {
        const pfPrcTag* eax = tag->getFirstChild();
        if (eax != NULL) {
            if (eax->getName() != "EAXREVERBPROPERTIES")
                throw pfPrcTagException(__FILE__, __LINE__, eax->getName());
            fListenerProps.ulEnvironment = eax->getParam("Environment", "0").toUint();
            fListenerProps.flEnvironmentSize = eax->getParam("EnvironmentSize", "0").toFloat();
            fListenerProps.flEnvironmentDiffusion = eax->getParam("EnvironmentDiffusion", "0").toFloat();
            fListenerProps.lRoom = eax->getParam("Room", "0").toInt();
            fListenerProps.lRoomHF = eax->getParam("RoomHF", "0").toInt();
            fListenerProps.lRoomLF = eax->getParam("RoomLF", "0").toInt();
            fListenerProps.flDecayTime = eax->getParam("DecayTime", "0").toFloat();
            fListenerProps.flDecayHFRatio = eax->getParam("DecayHFRatio", "0").toFloat();
            fListenerProps.flDecayLFRatio = eax->getParam("DecayLFRatio", "0").toFloat();
            fListenerProps.lReflections = eax->getParam("Reflections", "0").toInt();
            fListenerProps.flReflectionsDelay = eax->getParam("ReflectionsDelay", "0").toFloat();
            fListenerProps.lReverb = eax->getParam("Reverb", "0").toInt();
            fListenerProps.flReverbDelay = eax->getParam("ReverbDelay", "0").toFloat();
            fListenerProps.flEchoTime = eax->getParam("EchoTime", "0").toFloat();
            fListenerProps.flEchoDepth = eax->getParam("EchoDepth", "0").toFloat();
            fListenerProps.flModulationTime = eax->getParam("ModulationTime", "0").toFloat();
            fListenerProps.flModulationDepth = eax->getParam("ModulationDepth", "0").toFloat();
            fListenerProps.flAirAbsorptionHF = eax->getParam("AirAbsorptionHF", "0").toFloat();
            fListenerProps.flHFReference = eax->getParam("HFReference", "0").toFloat();
            fListenerProps.flLFReference = eax->getParam("LFReference", "0").toFloat();
            fListenerProps.flRoomRolloffFactor = eax->getParam("RoomRolloffFactor", "0").toFloat();
            fListenerProps.ulFlags = eax->getParam("Flags", "0").toUint();
        }
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
