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

#include "plATCAnim.h"

/* plATCAnim */
void plATCAnim::read(hsStream* S, plResManager* mgr)
{
    plAGAnim::read(S, mgr);

    fInitial = S->readFloat();
    fAutoStart = S->readBool();
    fLoopStart = S->readFloat();
    fLoopEnd = S->readFloat();
    fLoop = S->readBool();

    fEaseInType = S->readByte();
    fEaseInMin = S->readFloat();
    fEaseInMax = S->readFloat();
    fEaseInLength = S->readFloat();

    fEaseOutType = S->readByte();
    fEaseOutMin = S->readFloat();
    fEaseOutMax = S->readFloat();
    fEaseOutLength = S->readFloat();

    size_t numMarkers = S->readInt();
    for (size_t i=0; i<numMarkers; i++) {
        ST::string key = S->readSafeStr();
        fMarkers[key] = S->readFloat();
    }

    size_t numLoops = S->readInt();
    for (size_t i=0; i<numLoops; i++) {
        ST::string key = S->readSafeStr();
        float start = S->readFloat();
        float end = S->readFloat();
        fLoops[key] = std::pair<float, float>(start, end);
    }

    fStopPoints.resize(S->readInt());
    for (size_t i=0; i<fStopPoints.size(); i++)
        fStopPoints[i] = S->readFloat();
}

void plATCAnim::write(hsStream* S, plResManager* mgr)
{
    plAGAnim::write(S, mgr);

    S->writeFloat(fInitial);
    S->writeBool(fAutoStart);
    S->writeFloat(fLoopStart);
    S->writeFloat(fLoopEnd);
    S->writeBool(fLoop);

    S->writeByte(fEaseInType);
    S->writeFloat(fEaseInMin);
    S->writeFloat(fEaseInMax);
    S->writeFloat(fEaseInLength);

    S->writeByte(fEaseOutType);
    S->writeFloat(fEaseOutMin);
    S->writeFloat(fEaseOutMax);
    S->writeFloat(fEaseOutLength);

    S->writeInt(fMarkers.size());
    for (marker_t::iterator i = fMarkers.begin(); i != fMarkers.end(); i++) {
        S->writeSafeStr(i->first);
        S->writeFloat(i->second);
    }

    S->writeInt(fLoops.size());
    for (loop_t::iterator i = fLoops.begin(); i != fLoops.end(); i++) {
        S->writeSafeStr(i->first);
        S->writeFloat(i->second.first);
        S->writeFloat(i->second.second);
    }

    S->writeInt(fStopPoints.size());
    for (size_t i=0; i<fStopPoints.size(); i++)
        S->writeFloat(fStopPoints[i]);
}

void plATCAnim::IPrcWrite(pfPrcHelper* prc)
{
    plAGAnim::IPrcWrite(prc);

    prc->startTag("ATCAnimParams");
    prc->writeParam("Initial", fInitial);
    prc->writeParam("AutoStart", fAutoStart);
    prc->writeParam("LoopStart", fLoopStart);
    prc->writeParam("LoopEnd", fLoopEnd);
    prc->writeParam("Loop", fLoop);
    prc->endTag(true);

    prc->startTag("EaseIn");
    prc->writeParam("Type", fEaseInType);
    prc->writeParam("Min", fEaseInMin);
    prc->writeParam("Max", fEaseInMax);
    prc->writeParam("Length", fEaseInLength);
    prc->endTag(true);

    prc->startTag("EaseOut");
    prc->writeParam("Type", fEaseOutType);
    prc->writeParam("Min", fEaseOutMin);
    prc->writeParam("Max", fEaseOutMax);
    prc->writeParam("Length", fEaseOutLength);
    prc->endTag(true);

    prc->writeSimpleTag("Markers");
    for (marker_t::iterator i = fMarkers.begin(); i != fMarkers.end(); i++) {
        prc->startTag("Marker");
        prc->writeParam("Name", i->first);
        prc->writeParam("Pos", i->second);
        prc->endTag(true);
    }
    prc->closeTag();

    prc->writeSimpleTag("Loops");
    for (loop_t::iterator i = fLoops.begin(); i != fLoops.end(); i++) {
        prc->startTag("Loop");
        prc->writeParam("Name", i->first);
        prc->writeParam("Start", i->second.first);
        prc->writeParam("End", i->second.second);
        prc->endTag(true);
    }
    prc->closeTag();

    prc->writeSimpleTag("StopPoints");
    for (size_t i=0; i<fStopPoints.size(); i++) {
        prc->startTag("StopPoint");
        prc->writeParam("Pos", fStopPoints[i]);
        prc->endTag(true);
    }
    prc->closeTag();
}

void plATCAnim::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "ATCAnimParams") {
        fInitial = tag->getParam("Initial", "0").to_float();
        fAutoStart = tag->getParam("AutoStart", "false").to_bool();
        fLoopStart = tag->getParam("LoopStart", "0").to_float();
        fLoopEnd = tag->getParam("LoopEnd", "0").to_float();
        fLoop = tag->getParam("Loop", "false").to_bool();
    } else if (tag->getName() == "EaseIn") {
        fEaseInType = tag->getParam("Type", "0").to_uint();
        fEaseInMin = tag->getParam("Min", "0").to_float();
        fEaseInMax = tag->getParam("Max", "0").to_float();
        fEaseInLength = tag->getParam("Length", "0").to_float();
    } else if (tag->getName() == "EaseOut") {
        fEaseOutType = tag->getParam("Type", "0").to_uint();
        fEaseOutMin = tag->getParam("Min", "0").to_float();
        fEaseOutMax = tag->getParam("Max", "0").to_float();
        fEaseOutLength = tag->getParam("Length", "0").to_float();
    } else if (tag->getName() == "Markers") {
        const pfPrcTag* child = tag->getFirstChild();
        while (child) {
            if (child->getName() != "Marker")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            fMarkers[child->getParam("Name", "")] = child->getParam("Pos", "0").to_float();
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Loops") {
        const pfPrcTag* child = tag->getFirstChild();
        while (child) {
            if (child->getName() != "Loop")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            ST::string key = child->getParam("Name", "");
            float start = child->getParam("Start", "0").to_float();
            float end = child->getParam("End", "0").to_float();
            fLoops[key] = std::pair<float, float>(start, end);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "StopPoints") {
        fStopPoints.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fStopPoints.size(); i++) {
            if (child->getName() != "StopPoint")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            fStopPoints[i] = child->getParam("Pos", "0").to_float();
            child = child->getNextSibling();
        }
    } else {
        plAGAnim::IPrcParse(tag, mgr);
    }
}

float plATCAnim::getMarker(const ST::string& key) const
{
    marker_t::const_iterator f = fMarkers.find(key);
    if (f == fMarkers.end())
        throw hsOutOfBoundsException(__FILE__, __LINE__);
    return f->second;
}

std::pair<float, float> plATCAnim::getLoop(const ST::string& key) const
{
    loop_t::const_iterator f = fLoops.find(key);
    if (f == fLoops.end())
        throw hsOutOfBoundsException(__FILE__, __LINE__);
    return f->second;
}


/* plEmoteAnim */
void plEmoteAnim::read(hsStream* S, plResManager* mgr)
{
    plATCAnim::read(S, mgr);

    fFadeIn = S->readFloat();
    fFadeOut = S->readFloat();
    fBodyUsage = (plAGAnim::BodyUsage)S->readByte();
}

void plEmoteAnim::write(hsStream* S, plResManager* mgr)
{
    plATCAnim::write(S, mgr);

    S->writeFloat(fFadeIn);
    S->writeFloat(fFadeOut);
    S->writeByte((uint8_t)fBodyUsage);
}

void plEmoteAnim::IPrcWrite(pfPrcHelper* prc)
{
    plATCAnim::IPrcWrite(prc);

    prc->startTag("EmoteAnimParams");
    prc->writeParam("FadeIn", fFadeIn);
    prc->writeParam("FadeOut", fFadeOut);
    prc->writeParam("BodyUsage", (uint8_t)fBodyUsage);
    prc->endTag(true);
}

void plEmoteAnim::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "EmoteAnimParams") {
        fFadeIn = tag->getParam("FadeIn", "0").to_float();
        fFadeOut = tag->getParam("FadeOut", "0").to_float();
        fBodyUsage = (plAGAnim::BodyUsage)tag->getParam("BodyUsage", "0").to_int();
    } else {
        plATCAnim::IPrcParse(tag, mgr);
    }
}


/* plAGAnimBink */
void plAGAnimBink::read(hsStream* S, plResManager* mgr)
{
    plATCAnim::read(S, mgr);

    fBinkFilename = S->readSafeStr();
    fSgtFilename = S->readSafeStr();
    fSubtitleId = S->readSafeStr();
}

void plAGAnimBink::write(hsStream* S, plResManager* mgr)
{
    plATCAnim::write(S, mgr);

    S->writeSafeStr(fBinkFilename);
    S->writeSafeStr(fSgtFilename);
    S->writeSafeStr(fSubtitleId);
}

void plAGAnimBink::IPrcWrite(pfPrcHelper* prc)
{
    plATCAnim::IPrcWrite(prc);

    prc->startTag("BinkParams");
    prc->writeParam("BinkFile", fBinkFilename);
    prc->writeParam("SgtFile", fSgtFilename);
    prc->writeParam("SubtitleId", fSubtitleId);
    prc->endTag(true);
}

void plAGAnimBink::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "BinkParams") {
        fBinkFilename = tag->getParam("BinkFile", "");
        fSgtFilename = tag->getParam("SgtFile", "");
        fSubtitleId = tag->getParam("SubtitleId", "");
    } else {
        plATCAnim::IPrcParse(tag, mgr);
    }
}
