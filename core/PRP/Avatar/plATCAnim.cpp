#include "plATCAnim.h"

/* plATCAnim */
plATCAnim::plATCAnim()
         : fInitial(0.0f), fLoopStart(0.0f), fLoopEnd(0.0f), fAutoStart(false),
           fLoop(false), fEaseInType(0), fEaseOutType(0) { }

plATCAnim::~plATCAnim() { }

IMPLEMENT_CREATABLE(plATCAnim, kATCAnim, plAGAnim)

void plATCAnim::read(hsStream* S, plResManager* mgr) {
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
        plString key = S->readSafeStr();
        fMarkers[key] = S->readFloat();
    }

    size_t numLoops = S->readInt();
    for (size_t i=0; i<numLoops; i++) {
        plString key = S->readSafeStr();
        float start = S->readFloat();
        float end = S->readFloat();
        fLoops[key] = std::pair<float, float>(start, end);
    }

    fStopPoints.setSizeNull(S->readInt());
    for (size_t i=0; i<fStopPoints.getSize(); i++)
        fStopPoints[i] = S->readFloat();
}

void plATCAnim::write(hsStream* S, plResManager* mgr) {
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

    S->writeInt(fStopPoints.getSize());
    for (size_t i=0; i<fStopPoints.getSize(); i++)
        S->writeFloat(fStopPoints[i]);
}

void plATCAnim::IPrcWrite(pfPrcHelper* prc) {
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
    for (size_t i=0; i<fStopPoints.getSize(); i++) {
        prc->startTag("StopPoint");
        prc->writeParam("Pos", fStopPoints[i]);
        prc->endTag(true);
    }
    prc->closeTag();
}

void plATCAnim::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "ATCAnimParams") {
        fInitial = tag->getParam("Initial", "0").toFloat();
        fAutoStart = tag->getParam("AutoStart", "false").toBool();
        fLoopStart = tag->getParam("LoopStart", "0").toFloat();
        fLoopEnd = tag->getParam("LoopEnd", "0").toFloat();
        fLoop = tag->getParam("Loop", "false").toBool();
    } else if (tag->getName() == "EaseIn") {
        fEaseInType = tag->getParam("Type", "0").toUint();
        fEaseInMin = tag->getParam("Min", "0").toFloat();
        fEaseInMax = tag->getParam("Max", "0").toFloat();
        fEaseInLength = tag->getParam("Length", "0").toFloat();
    } else if (tag->getName() == "EaseOut") {
        fEaseOutType = tag->getParam("Type", "0").toUint();
        fEaseOutMin = tag->getParam("Min", "0").toFloat();
        fEaseOutMax = tag->getParam("Max", "0").toFloat();
        fEaseOutLength = tag->getParam("Length", "0").toFloat();
    } else if (tag->getName() == "Markers") {
        const pfPrcTag* child = tag->getFirstChild();
        while (child != NULL) {
            if (child->getName() != "Marker")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            fMarkers[child->getParam("Name", "")] = child->getParam("Pos", "0").toFloat();
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Loops") {
        const pfPrcTag* child = tag->getFirstChild();
        while (child != NULL) {
            if (child->getName() != "Loop")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            plString key = child->getParam("Name", "");
            float start = child->getParam("Start", "0").toFloat();
            float end = child->getParam("End", "0").toFloat();
            fLoops[key] = std::pair<float, float>(start, end);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "StopPoints") {
        fStopPoints.setSizeNull(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fStopPoints.getSize(); i++) {
            if (child->getName() != "StopPoint")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            fStopPoints[i] = child->getParam("Pos", "0").toFloat();
            child = child->getNextSibling();
        }
    } else {
        plAGAnim::IPrcParse(tag, mgr);
    }
}

plATCAnim::marker_t& plATCAnim::getMarkers() { return fMarkers; }
plATCAnim::loop_t& plATCAnim::getLoops() { return fLoops; }

float plATCAnim::getInitial() const { return fInitial; }
float plATCAnim::getLoopStart() const { return fLoopStart; }
float plATCAnim::getLoopEnd() const { return fLoopEnd; }
bool plATCAnim::getAutoStart() const { return fAutoStart; }
bool plATCAnim::getDoLoop() const { return fLoop; }
unsigned char plATCAnim::getEaseInType() const { return fEaseInType; }
unsigned char plATCAnim::getEaseOutType() const { return fEaseOutType; }
float plATCAnim::getEaseInLength() const { return fEaseInLength; }
float plATCAnim::getEaseInMin() const { return fEaseInMin; }
float plATCAnim::getEaseInMax() const { return fEaseInMax; }
float plATCAnim::getEaseOutLength() const { return fEaseOutLength; }
float plATCAnim::getEaseOutMin() const { return fEaseOutMin; }
float plATCAnim::getEaseOutMax() const { return fEaseOutMax; }

float plATCAnim::getMarker(const plString& key) const { return fMarkers.find(key)->second; }
std::pair<float, float> plATCAnim::getLoop(const plString& key) const { return fLoops.find(key)->second; }
const hsTArray<float>& plATCAnim::getStops() const { return fStopPoints; }

void plATCAnim::setInitial(float init) { fInitial = init; }
void plATCAnim::setLoopStart(float start) { fLoopStart = start; }
void plATCAnim::setLoopEnd(float end) { fLoopEnd = end; }
void plATCAnim::setAutoStart(bool autoStart) { fAutoStart = autoStart; }
void plATCAnim::setDoLoop(bool loop) { fLoop = loop; }
void plATCAnim::setEaseInType(unsigned char type) { fEaseInType = type; }
void plATCAnim::setEaseOutType(unsigned char type) { fEaseOutType = type; }

void plATCAnim::setEaseInParams(float length, float min, float max) {
    fEaseInLength = length;
    fEaseInMin = min;
    fEaseInMax = max;
}

void plATCAnim::setEaseOutParams(float length, float min, float max) {
    fEaseOutLength = length;
    fEaseOutMin = min;
    fEaseOutMax = max;
}

void plATCAnim::setMarker(const plString& key, float value) {
    fMarkers[key] = value;
}

void plATCAnim::setLoop(const plString& key, float start, float end) {
    fLoops[key] = std::pair<float, float>(start, end);
}

void plATCAnim::setStops(const hsTArray<float>& stops) { fStopPoints = stops; }


/* plEmoteAnim */
plEmoteAnim::plEmoteAnim() : fBodyUsage(plAGAnim::kBodyUnknown) { }
plEmoteAnim::~plEmoteAnim() { }

IMPLEMENT_CREATABLE(plEmoteAnim, kEmoteAnim, plATCAnim)

void plEmoteAnim::read(hsStream* S, plResManager* mgr) {
    plATCAnim::read(S, mgr);

    fFadeIn = S->readFloat();
    fFadeOut = S->readFloat();
    fBodyUsage = (plAGAnim::BodyUsage)S->readByte();
}

void plEmoteAnim::write(hsStream* S, plResManager* mgr) {
    plATCAnim::write(S, mgr);

    S->writeFloat(fFadeIn);
    S->writeFloat(fFadeOut);
    S->writeByte((hsUbyte)fBodyUsage);
}

void plEmoteAnim::IPrcWrite(pfPrcHelper* prc) {
    plATCAnim::IPrcWrite(prc);

    prc->startTag("EmoteAnimParams");
    prc->writeParam("FadeIn", fFadeIn);
    prc->writeParam("FadeOut", fFadeOut);
    prc->writeParam("BodyUsage", (hsUbyte)fBodyUsage);
    prc->endTag(true);
}

void plEmoteAnim::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "EmoteAnimParams") {
        fFadeIn = tag->getParam("FadeIn", "0").toFloat();
        fFadeOut = tag->getParam("FadeOut", "0").toFloat();
        fBodyUsage = (plAGAnim::BodyUsage)tag->getParam("BodyUsage", "0").toInt();
    } else {
        plATCAnim::IPrcParse(tag, mgr);
    }
}

plAGAnim::BodyUsage plEmoteAnim::getBodyUsage() const { return fBodyUsage; }
float plEmoteAnim::getFadeIn() const { return fFadeIn; }
float plEmoteAnim::getFadeOut() const { return fFadeOut; }

void plEmoteAnim::setBodyUsage(plAGAnim::BodyUsage usage) { fBodyUsage = usage; }
void plEmoteAnim::setFadeIn(float fade) { fFadeIn = fade; }
void plEmoteAnim::setFadeOut(float fade) { fFadeOut = fade; }


/* plAGAnimBink */
plAGAnimBink::plAGAnimBink() { }
plAGAnimBink::~plAGAnimBink() { }

IMPLEMENT_CREATABLE(plAGAnimBink, kAGAnimBink, plATCAnim)

void plAGAnimBink::read(hsStream* S, plResManager* mgr) {
    plATCAnim::read(S, mgr);

    fBinkFilename = S->readSafeStr();
    fSgtFilename = S->readSafeStr();
    fSubtitleId = S->readSafeStr();
}

void plAGAnimBink::write(hsStream* S, plResManager* mgr) {
    plATCAnim::write(S, mgr);

    S->writeSafeStr(fBinkFilename);
    S->writeSafeStr(fSgtFilename);
    S->writeSafeStr(fSubtitleId);
}

void plAGAnimBink::IPrcWrite(pfPrcHelper* prc) {
    plATCAnim::IPrcWrite(prc);

    prc->startTag("BinkParams");
    prc->writeParam("BinkFile", fBinkFilename);
    prc->writeParam("SgtFile", fSgtFilename);
    prc->writeParam("SubtitleId", fSubtitleId);
    prc->endTag(true);
}

void plAGAnimBink::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "BinkParams") {
        fBinkFilename = tag->getParam("BinkFile", "");
        fSgtFilename = tag->getParam("SgtFile", "");
        fSubtitleId = tag->getParam("SubtitleId", "");
    } else {
        plATCAnim::IPrcParse(tag, mgr);
    }
}

plString plAGAnimBink::getBinkFilename() const { return fBinkFilename; }
plString plAGAnimBink::getSgtFilename() const { return fSgtFilename; }
plString plAGAnimBink::getSubtitleId() const { return fSubtitleId; }

void plAGAnimBink::setBinkFilename(const plString& filename) { fBinkFilename = filename; }
void plAGAnimBink::setSgtFilename(const plString& filename) { fSgtFilename = filename; }
void plAGAnimBink::setSubtitleId(const plString& id) { fSubtitleId = id; }
