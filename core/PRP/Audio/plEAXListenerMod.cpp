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

void plEAXEffect::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);
}

void plEAXEffect::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);
}

void plEAXEffect::IPrcWrite(pfPrcHelper* prc) {
    plSingleModifier::IPrcWrite(prc);
}

void plEAXEffect::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    plSingleModifier::IPrcParse(tag, mgr);
}

void plEAXReverbEffect::read(hsStream* S, plResManager* mgr) {
    plEAXEffect::read(S, mgr);

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

    fApertures.setSize(S->readInt());
    for (size_t i = 0; i < fApertures.getSize(); i++) {
        Aperture a;
        a.fX.read(S);
        a.fY.read(S);
        a.fZ.read(S);
        fApertures[i] = a;
    }
}

void plEAXReverbEffect::write(hsStream* S, plResManager* mgr) {
    plEAXEffect::write(S, mgr);

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

    S->writeInt(fApertures.getSize());
    for (size_t i = 0; i < fApertures.getSize(); i++) {
        fApertures[i].fX.write(S);
        fApertures[i].fY.write(S);
        fApertures[i].fZ.write(S);
    }
}

void plEAXReverbEffect::IPrcWrite(pfPrcHelper* prc) {
    plEAXEffect::IPrcWrite(prc);

    prc->writeSimpleTag("SoftRegion");
    fSoftRegion->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("ReverbProperties");
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

    prc->writeSimpleTag("Apertures");
    for (size_t i = 0; i < fApertures.getSize(); i++) {
        prc->writeSimpleTag("Aperture");
        fApertures[i].fX.prcWrite(prc);
        fApertures[i].fY.prcWrite(prc);
        fApertures[i].fZ.prcWrite(prc);
        prc->closeTag();
    }
    prc->closeTag();
}

void plEAXReverbEffect::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "SoftRegion") {
        if (tag->hasChildren())
            fSoftRegion = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "ReverbProperties") {
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
    } else if (tag->getName() == "Apertures") {
        if (tag->hasChildren()) {
            fApertures.setSize(tag->countChildren());
            const pfPrcTag* child = tag->getFirstChild();
            for (size_t i = 0; i < fApertures.getSize(); i++) {
                if (child->getName() != "Aperture")
                    throw pfPrcTagException(__FILE__, __LINE__, child->getName());
                const pfPrcTag* vector = child->getFirstChild();
                fApertures[i].fX.prcParse(vector);
                vector = vector->getNextSibling();
                fApertures[i].fY.prcParse(vector);
                vector = vector->getNextSibling();
                fApertures[i].fZ.prcParse(vector);
                child = child->getNextSibling();
            }
        }
    } else {
        plEAXEffect::IPrcParse(tag, mgr);
    }
}
