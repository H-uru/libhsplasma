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

#include "plEAXEffects.h"

/* plEAXSourceSoftSettings */
void plEAXSourceSoftSettings::reset()
{
    fOcclusion = 0;
    fOcclusionLFRatio = 0.25f;
    fOcclusionRoomRatio = 1.5f;
    fOcclusionDirectRatio = 1.0f;
}

void plEAXSourceSoftSettings::read(hsStream* S)
{
    fOcclusion = S->readShort();
    fOcclusionLFRatio = S->readFloat();
    fOcclusionRoomRatio = S->readFloat();
    fOcclusionDirectRatio = S->readFloat();
}

void plEAXSourceSoftSettings::write(hsStream* S)
{
    S->writeShort(fOcclusion);
    S->writeFloat(fOcclusionLFRatio);
    S->writeFloat(fOcclusionRoomRatio);
    S->writeFloat(fOcclusionDirectRatio);
}

void plEAXSourceSoftSettings::prcWrite(pfPrcHelper* prc)
{
    prc->startTag("plEAXSourceSoftSettings");
      prc->writeParam("Occlusion", fOcclusion);
      prc->writeParam("LFRatio", fOcclusionLFRatio);
      prc->writeParam("RoomRatio", fOcclusionRoomRatio);
      prc->writeParam("DirectRatio", fOcclusionDirectRatio);
    prc->endTag(true);
}

void plEAXSourceSoftSettings::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != "plEAXSourceSoftSettings")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fOcclusion = tag->getParam("Occlusion", "0").to_int();
    fOcclusionLFRatio = tag->getParam("LFRatio", "0").to_float();
    fOcclusionRoomRatio = tag->getParam("RoomRatio", "0").to_float();
    fOcclusionDirectRatio = tag->getParam("DirectRatio", "0").to_float();
}


/* plEAXSourceSettings */
void plEAXSourceSettings::enable(bool en)
{
    fEnabled = en;
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
        fOcclusionSoftValue = 0.0f;
        fSoftStarts.reset();
        fSoftEnds.reset();
    }
}

void plEAXSourceSettings::read(hsStream* S)
{
    enable(S->readBool());
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
        if (!S->getVer().isNewPlasma() || S->getVer().isUniversal()) {
            fSoftStarts.read(S);
            fSoftEnds.read(S);
            fOcclusionSoftValue = S->readFloat();
        } else {
            fOcclusionSoftValue = S->readFloat();
            fSoftStarts.read(S);
            fSoftEnds.reset();
        }
    }
}

void plEAXSourceSettings::write(hsStream* S)
{
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
        if (!S->getVer().isNewPlasma() || S->getVer().isUniversal()) {
            fSoftStarts.write(S);
            fSoftEnds.write(S);
            S->writeFloat(fOcclusionSoftValue);
        } else {
            S->writeFloat(fOcclusionSoftValue);
            fSoftStarts.write(S);
        }
    }
}

void plEAXSourceSettings::prcWrite(pfPrcHelper* prc)
{
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

void plEAXSourceSettings::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != "plEAXSourceSettings")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fEnabled = tag->getParam("enabled", "true").to_bool();
    if (fEnabled) {
        fRoom = tag->getParam("Room", "0").to_int();
        fRoomHF = tag->getParam("RoomHF", "0").to_int();
        fRoomAuto = tag->getParam("RoomAuto", "false").to_bool();
        fRoomHFAuto = tag->getParam("RoomHFAuto", "false").to_bool();
        fOutsideVolHF = tag->getParam("OutsideHF", "0").to_int();

        const pfPrcTag* child = tag->getFirstChild();
        while (child) {
            if (child->getName() == "Effects") {
                fAirAbsorptionFactor = child->getParam("AirAbsorption", "0").to_float();
                fRoomRolloffFactor = child->getParam("RoomRolloff", "0").to_float();
                fDopplerFactor = child->getParam("Doppler", "0").to_float();
                fRolloffFactor = child->getParam("Rolloff", "0").to_float();
                fOcclusionSoftValue = tag->getParam("SoftOcclusion", "0").to_float();
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
        enable(false);
    }
}
