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

#include "plSound.h"

/* plSound::plFadeParams */
plSound::plFadeParams::plFadeParams()
       : fLengthInSecs(0), fVolStart(0.0f), fVolEnd(0.0f), fType(kLinear),
         fStopWhenDone(false), fFadeSoftVol(false), fCurrTime(0.0f) { }

void plSound::plFadeParams::read(hsStream* S) {
    fLengthInSecs = S->readFloat();
    fVolStart = S->readFloat();
    fVolEnd = S->readFloat();
    fType = S->readByte();
    fCurrTime = S->readFloat();
    fStopWhenDone = S->readInt() != 0;
    fFadeSoftVol = S->readInt() != 0;
}

void plSound::plFadeParams::write(hsStream* S) {
    S->writeFloat(fLengthInSecs);
    S->writeFloat(fVolStart);
    S->writeFloat(fVolEnd);
    S->writeByte(fType);
    S->writeFloat(fCurrTime);
    S->writeInt(fStopWhenDone ? 1 : 0);
    S->writeInt(fFadeSoftVol ? 1 : 0);
}

void plSound::plFadeParams::prcWrite(pfPrcHelper* prc) {
    prc->startTag("plFadeParams");
    prc->writeParam("Type", fType);
    prc->writeParam("Length", fLengthInSecs);
    prc->writeParam("VolStart", fVolStart);
    prc->writeParam("VolEnd", fVolEnd);
    prc->writeParam("CurrTime", fCurrTime);
    prc->writeParam("StopWhenDone", fStopWhenDone);
    prc->writeParam("FadeSoftVol", fFadeSoftVol);
    prc->endTag(true);
}

void plSound::plFadeParams::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "plFadeParams")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fType = tag->getParam("Type", "0").toUint();
    fLengthInSecs = tag->getParam("Length", "0").toFloat();
    fVolStart = tag->getParam("VolStart", "0").toFloat();
    fVolEnd = tag->getParam("VolEnd", "0").toFloat();
    fCurrTime = tag->getParam("CurrTime", "0").toFloat();
    fStopWhenDone = tag->getParam("StopWhenDone", "false").toBool();
    fFadeSoftVol = tag->getParam("FadeSoftVol", "false").toBool();
}


/* plSound */
plSound::plSound()
       : fType(kStartType), fPriority(0), fPlaying(false), fTime(0.0f),
         fMaxFalloff(0), fMinFalloff(0), fOuterVol(0), fInnerCone(360),
         fOuterCone(360), fCurrVolume(0.0f), fDesiredVol(0.0f),
         fFadedVolume(0.0f), fProperties(0) { }

void plSound::read(hsStream* S, plResManager* mgr) {
    plSynchedObject::read(S, mgr);
    IRead(S, mgr);

    //if (fProperties & kPropLocalOnly)
    //    fSynchFlags |= kLocalOnly;
}

void plSound::write(hsStream* S, plResManager* mgr) {
    plSynchedObject::write(S, mgr);
    IWrite(S, mgr);
}

void plSound::IRead(hsStream* S, plResManager* mgr) {
    fPlaying = S->readBool();
    fTime = S->readDouble();
    fMaxFalloff = S->readInt();
    fMinFalloff = S->readInt();
    fCurrVolume = S->readFloat();
    fDesiredVol = S->readFloat();
    if (fDesiredVol > 1.0f) fDesiredVol = 1.0f;
    if (fCurrVolume > 1.0f) fCurrVolume = 1.0f;
    fOuterVol = S->readInt();
    fInnerCone = S->readInt();
    fOuterCone = S->readInt();
    fFadedVolume = S->readFloat();
    fProperties = S->readInt();
    fType = S->readByte();
    fPriority = S->readByte();

    if (S->getVer().isNewPlasma())
        fSubtitleId = S->readSafeStr();

    if (fPlaying)
        fProperties |= kPropAutoStart;
    fFadeInParams.read(S);
    fFadeOutParams.read(S);

    fSoftRegion = mgr->readKey(S);
    fDataBuffer = mgr->readKey(S);
    fEAXSettings.read(S);
    fSoftOcclusionRegion = mgr->readKey(S);
}

void plSound::IWrite(hsStream* S, plResManager* mgr) {
    S->writeBool(fPlaying);
    S->writeDouble(fTime);
    S->writeInt(fMaxFalloff);
    S->writeInt(fMinFalloff);
    S->writeFloat(fCurrVolume);
    S->writeFloat(fDesiredVol);
    S->writeInt(fOuterVol);
    S->writeInt(fInnerCone);
    S->writeInt(fOuterCone);
    S->writeFloat(fFadedVolume);
    S->writeInt(fProperties);
    S->writeByte(fType);
    S->writeByte(fPriority);

    if (S->getVer().isNewPlasma())
        S->writeSafeStr(fSubtitleId);

    fFadeInParams.write(S);
    fFadeOutParams.write(S);
    mgr->writeKey(S, fSoftRegion);
    mgr->writeKey(S, fDataBuffer);
    fEAXSettings.write(S);
    mgr->writeKey(S, fSoftOcclusionRegion);
}

void plSound::IPrcWrite(pfPrcHelper* prc) {
    plSynchedObject::IPrcWrite(prc);

    prc->startTag("SoundParams");
      prc->writeParam("Playing", fPlaying);
      prc->writeParam("Time", fTime);
      prc->writeParam("MaxFalloff", fMaxFalloff);
      prc->writeParam("MinFalloff", fMinFalloff);
      prc->writeParamHex("Properties", fProperties);
      prc->writeParam("Type", fType);
      prc->writeParam("Priority", fPriority);
    prc->endTag(true);
    prc->startTag("Volumes");
      prc->writeParam("Current", fCurrVolume);
      prc->writeParam("Desired", fDesiredVol);
      prc->writeParam("Fade", fFadedVolume);
    prc->endTag(true);
    prc->startTag("Cone");
      prc->writeParam("OuterVol", fOuterVol);
      prc->writeParam("InnerCone", fInnerCone);
      prc->writeParam("OuterCone", fOuterCone);
    prc->endTag(true);

    prc->startTag("Localization");
    prc->writeParam("SubtitleId", fSubtitleId);
    prc->endTag(true);

    prc->writeSimpleTag("FadeInParams");
      fFadeInParams.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("FadeOutParams");
      fFadeOutParams.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("SoftRegion");
      fSoftRegion->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("DataBuffer");
      fDataBuffer->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("SoftOcclusionRegion");
      fSoftOcclusionRegion->prcWrite(prc);
    prc->closeTag();

    fEAXSettings.prcWrite(prc);
}

void plSound::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "SoundParams") {
        fPlaying = tag->getParam("Playing", "false").toBool();
        fTime = tag->getParam("Time", "0").toFloat();
        fMaxFalloff = tag->getParam("MaxFalloff", "0").toInt();
        fMinFalloff = tag->getParam("MinFalloff", "0").toInt();
        fProperties = tag->getParam("Properties", "0").toUint();
        fType = tag->getParam("Type", "0").toUint();
        fPriority = tag->getParam("Priority", "0").toUint();
    } else if (tag->getName() == "Volumes") {
        fCurrVolume = tag->getParam("Current", "0").toFloat();
        fDesiredVol = tag->getParam("Desired", "0").toFloat();
        fFadedVolume = tag->getParam("Fade", "0").toFloat();
    } else if (tag->getName() == "Cone") {
        fOuterVol = tag->getParam("OuterVol", "0").toInt();
        fInnerCone = tag->getParam("InnerCone", "360").toInt();
        fOuterCone = tag->getParam("OuterCone", "360").toInt();
    } else if (tag->getName() == "Localization") {
        fSubtitleId = tag->getParam("SubtitleId", "");
    } else if (tag->getName() == "FadeInParams") {
        if (tag->hasChildren())
            fFadeInParams.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "FadeOutParams") {
        if (tag->hasChildren())
            fFadeOutParams.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "SoftRegion") {
        if (tag->hasChildren())
            fSoftRegion = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "DataBuffer") {
        if (tag->hasChildren())
            fDataBuffer = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "SoftOcclusionRegion") {
        if (tag->hasChildren())
            fSoftOcclusionRegion = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "plEAXSourceSettings") {
        fEAXSettings.prcParse(tag);
    } else {
        plSynchedObject::IPrcParse(tag, mgr);
    }
}
