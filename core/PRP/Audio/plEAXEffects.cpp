#include "plEAXEffects.h"

/* plEAXSourceSoftSettings */
void plEAXSourceSoftSettings::Reset() {
    fOcclusion = 0;
    fOcclusionLFRatio = 0.25f;
    fOcclusionRoomRatio = 1.5f;
    fOcclusionDirectRatio = 1.0f;
}

void plEAXSourceSoftSettings::read(hsStream* S) {
    fOcclusion = S->readShort();
    fOcclusionLFRatio = S->readFloat();
    fOcclusionRoomRatio = S->readFloat();
    fOcclusionDirectRatio = S->readFloat();
}

void plEAXSourceSoftSettings::write(hsStream* S) {
    S->writeShort(fOcclusion);
    S->writeFloat(fOcclusionLFRatio);
    S->writeFloat(fOcclusionRoomRatio);
    S->writeFloat(fOcclusionDirectRatio);
}

void plEAXSourceSoftSettings::prcWrite(pfPrcHelper* prc) {
    prc->startTag("plEAXSourceSoftSettings");
      prc->writeParam("Occlusion", fOcclusion);
      prc->writeParam("LFRatio", fOcclusionLFRatio);
      prc->writeParam("RoomRatio", fOcclusionRoomRatio);
      prc->writeParam("DirectRatio", fOcclusionDirectRatio);
    prc->endTag(true);
}

void plEAXSourceSoftSettings::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "plEAXSourceSoftSettings")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fOcclusion = tag->getParam("Occlusion", "0").toInt();
    fOcclusionLFRatio = tag->getParam("LFRatio", "0").toFloat();
    fOcclusionRoomRatio = tag->getParam("RoomRatio", "0").toFloat();
    fOcclusionDirectRatio = tag->getParam("DirectRatio", "0").toFloat();
}


/* plEAXSourceSettings */
plEAXSourceSettings::plEAXSourceSettings() : fDirtyParams(kAll) {
    Enable(false);
}

void plEAXSourceSettings::Enable(bool enable) {
    fEnabled = enable;
    if (!fEnabled) {
        fRoom = -1;
        fRoomHF = -1;
        fRoomAuto = true;
        fRoomHFAuto = true;
        fOutsideVolHF = 0;
        fAirAbsorptionFactor = 1.0f;
        fRoomRolloffFactor = 0.0f;
        fDopplerFactor = 0.0f;
        fRolloffFactor = 0.0f;
        fSoftStarts.Reset();
        fSoftEnds.Reset();
        fDirtyParams = kAll;
    }
}

void plEAXSourceSettings::read(hsStream* S) {
    Enable(S->readBool());
    if (fEnabled) {
        fRoom = S->readShort();
        fRoomHF = S->readShort();
        fRoomAuto = S->readBool();
        fRoomHFAuto = S->readBool();
        fOutsideVolHF = S->readShort();
        fAirAbsorptionFactor = S->readFloat();
        fRoomRolloffFactor = S->readFloat();
        fDopplerFactor = S->readFloat();
        fRolloffFactor = S->readFloat();
        if (S->getVer() < pvEoa) {
            fSoftStarts.read(S);
            fSoftEnds.read(S);
        }
        fOcclusionSoftValue = S->readFloat();
        if (S->getVer() >= pvEoa) {
            fSoftStarts.read(S);
            fSoftEnds.Reset();
        }
        fDirtyParams = kAll;
    }
}

void plEAXSourceSettings::write(hsStream* S) {
    S->writeBool(fEnabled);
    if (fEnabled) {
        S->writeShort(fRoom);
        S->writeShort(fRoomHF);
        S->writeBool(fRoomAuto);
        S->writeBool(fRoomHFAuto);
        S->writeShort(fOutsideVolHF);
        S->writeFloat(fAirAbsorptionFactor);
        S->writeFloat(fRoomRolloffFactor);
        S->writeFloat(fDopplerFactor);
        S->writeFloat(fRolloffFactor);
        if (S->getVer() < pvEoa) {
            fSoftStarts.write(S);
            fSoftEnds.write(S);
        }
        S->writeFloat(fOcclusionSoftValue);
        if (S->getVer() >= pvEoa) {
            fSoftStarts.write(S);
        }
    }
}

void plEAXSourceSettings::prcWrite(pfPrcHelper* prc) {
    prc->startTag("plEAXSourceSettings");
    if (fEnabled) {
        prc->writeParam("Room", fRoom);
        prc->writeParam("RoomHF", fRoomHF);
        prc->writeParam("RoomAuto", fRoomAuto);
        prc->writeParam("RoomHFAuto", fRoomHFAuto);
        prc->writeParam("OutsideHF", fOutsideVolHF);
        prc->endTag();
        prc->startTag("Effects");
        prc->writeParam("AirAbsorption", fAirAbsorptionFactor);
        prc->writeParam("RoomRolloff", fRoomRolloffFactor);
        prc->writeParam("Doppler", fDopplerFactor);
        prc->writeParam("Rolloff", fRolloffFactor);
        prc->writeParam("SoftOcclusion", fOcclusionSoftValue);
        prc->endTag(true);
        prc->writeSimpleTag("Starts");
        fSoftStarts.prcWrite(prc);
        prc->closeTag();
        prc->writeSimpleTag("Ends");
        fSoftEnds.prcWrite(prc);
        prc->closeTag();
        
        prc->closeTag();  // plEAXSourceSettings
    } else {
        prc->writeParam("enabled", false);
        prc->endTag(true);
    }
}

void plEAXSourceSettings::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "plEAXSourceSettings")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fEnabled = tag->getParam("enabled", "true").toBool();
    if (fEnabled) {
        fRoom = tag->getParam("Room", "0").toInt();
        fRoomHF = tag->getParam("RoomHF", "0").toInt();
        fRoomAuto = tag->getParam("RoomAuto", "false").toBool();
        fRoomHFAuto = tag->getParam("RoomHFAuto", "false").toBool();
        fOutsideVolHF = tag->getParam("OutsideHF", "0").toInt();

        const pfPrcTag* child = tag->getFirstChild();
        while (child != NULL) {
            if (child->getName() == "Effects") {
                fAirAbsorptionFactor = child->getParam("AirAbsorption", "0").toFloat();
                fRoomRolloffFactor = child->getParam("RoomRolloff", "0").toFloat();
                fDopplerFactor = child->getParam("Doppler", "0").toFloat();
                fRolloffFactor = child->getParam("Rolloff", "0").toFloat();
                fOcclusionSoftValue = tag->getParam("SoftOcclusion", "0").toFloat();
            } else if (child->getName() == "Starts") {
                if (tag->hasChildren())
                    fSoftStarts.prcParse(child->getFirstChild());
            } else if (child->getName() == "Ends") {
                if (tag->hasChildren())
                    fSoftEnds.prcParse(child->getFirstChild());
            } else {
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            }
            child = child->getNextSibling();
        }
    } else {
        Enable(false);
    }
}
