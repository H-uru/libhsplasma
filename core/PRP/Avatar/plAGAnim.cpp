#include "plAGAnim.h"

// plAGAnim //
plAGAnim::plAGAnim() : fBlend(0.0f), fStart(0.0f), fEnd(0.0f), fEoaFlag(0) { }

plAGAnim::~plAGAnim() {
    for (size_t i=0; i<fApps.getSize(); i++)
        delete fApps[i];
}

IMPLEMENT_CREATABLE(plAGAnim, kAGAnim, plSynchedObject)

void plAGAnim::read(hsStream* S, plResManager* mgr) {
    plSynchedObject::read(S, mgr);
    
    fName = S->readSafeStr();
    fStart = S->readFloat();
    fEnd = S->readFloat();

    fApps.setSizeNull(S->readInt());
    for (size_t i=0; i<fApps.getSize(); i++) {
        plAGApplicator* agApp = plAGApplicator::Convert(mgr->ReadCreatable(S));
        plAGChannel* agChan = plAGChannel::Convert(mgr->ReadCreatable(S));
        agApp->setChannel(agChan);
        fApps[i] = agApp;
    }

    if (S->getVer() >= pvEoa)
        fEoaFlag = S->readByte();
}

void plAGAnim::write(hsStream* S, plResManager* mgr) {
    plSynchedObject::write(S, mgr);

    S->writeSafeStr(fName);
    S->writeFloat(fStart);
    S->writeFloat(fEnd);

    S->writeInt(fApps.getSize());
    for (size_t i=0; i<fApps.getSize(); i++) {
        mgr->WriteCreatable(S, fApps[i]);
        mgr->WriteCreatable(S, fApps[i]->getChannel());
    }

    if (S->getVer() >= pvEoa)
        S->writeByte(fEoaFlag);
}

void plAGAnim::IPrcWrite(pfPrcHelper* prc) {
    plSynchedObject::IPrcWrite(prc);

    prc->startTag("AGAnimParams");
    prc->writeParam("Name", fName);
    prc->writeParam("Start", fStart);
    prc->writeParam("End", fEnd);
    prc->writeParam("EoaFlag", fEoaFlag);
    prc->endTag(true);

    prc->writeSimpleTag("Applicators");
    for (size_t i=0; i<fApps.getSize(); i++) {
        prc->writeSimpleTag("AppSet");
          prc->writeSimpleTag("Applicator");
          fApps[i]->prcWrite(prc);
          prc->closeTag();
          prc->writeSimpleTag("Channel");
          fApps[i]->getChannel()->prcWrite(prc);
          prc->closeTag();
        prc->closeTag();
    }
    prc->closeTag();
}

void plAGAnim::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "AGAnimParams") {
        fName = tag->getParam("Name", "");
        fStart = tag->getParam("Start", "0").toFloat();
        fEnd = tag->getParam("End", "0").toFloat();
        fEoaFlag = tag->getParam("EoaFlag", "0").toUint();
    } else if (tag->getName() == "Applicators") {
        fApps.setSizeNull(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fApps.getSize(); i++) {
            if (child->getName() != "AppSet")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());

            const pfPrcTag* subChild = child->getFirstChild();
            plAGApplicator* agApp;
            plAGChannel* agChan;
            while (subChild != NULL) {
                if (subChild->getName() == "Applicator") {
                    if (subChild->hasChildren())
                        agApp = plAGApplicator::Convert(mgr->prcParseCreatable(subChild->getFirstChild()));
                } else if (subChild->getName() == "Channel") {
                    if (subChild->hasChildren())
                        agChan = plAGChannel::Convert(mgr->prcParseCreatable(subChild->getFirstChild()));
                } else {
                    throw pfPrcTagException(__FILE__, __LINE__, subChild->getName());
                }
                subChild = subChild->getNextSibling();
            }
            if (agApp == NULL)
                throw pfPrcParseException(__FILE__, __LINE__, "Missing Applicator");
            agApp->setChannel(agChan);
            fApps[i] = agApp;
            child = child->getNextSibling();
        }
    } else {
        plSynchedObject::IPrcParse(tag, mgr);
    }
}


// plAgeGlobalAnim //
plAgeGlobalAnim::plAgeGlobalAnim() { }
plAgeGlobalAnim::~plAgeGlobalAnim() { }

IMPLEMENT_CREATABLE(plAgeGlobalAnim, kAgeGlobalAnim, plAGAnim)

void plAgeGlobalAnim::read(hsStream* S, plResManager* mgr) {
    plAGAnim::read(S, mgr);
    fGlobalVarName = S->readSafeStr();
}

void plAgeGlobalAnim::write(hsStream* S, plResManager* mgr) {
    plAGAnim::write(S, mgr);
    S->writeSafeStr(fGlobalVarName);
}

void plAgeGlobalAnim::IPrcWrite(pfPrcHelper* prc) {
    plAGAnim::IPrcWrite(prc);

    prc->startTag("AgeGlobalAnimParams");
    prc->writeParam("GlobalVarName", fGlobalVarName);
    prc->endTag(true);
}

void plAgeGlobalAnim::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "AgeGlobalAnimParams") {
        fGlobalVarName = tag->getParam("GlobalVarName", "");
    } else {
        plAGAnim::IPrcParse(tag, mgr);
    }
}


// plATCAnim //
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
    
    fMarkers.setSize(S->readInt());
    for (size_t i=0; i<fMarkers.getSize(); i++) {
        fMarkers[i].fKey = S->readSafeStr();
        fMarkers[i].fValue = S->readFloat();
    }

    fLoops.setSize(S->readInt());
    for (size_t i=0; i<fLoops.getSize(); i++) {
        fLoops[i].fKey = S->readSafeStr();
        fLoops[i].fStart = S->readFloat();
        fLoops[i].fEnd = S->readFloat();
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

    S->writeInt(fMarkers.getSize());
    for (size_t i=0; i<fMarkers.getSize(); i++) {
        S->writeSafeStr(fMarkers[i].fKey);
        S->writeFloat(fMarkers[i].fValue);
    }

    S->writeInt(fLoops.getSize());
    for (size_t i=0; i<fLoops.getSize(); i++) {
        S->writeSafeStr(fLoops[i].fKey);
        S->writeFloat(fLoops[i].fStart);
        S->writeFloat(fLoops[i].fEnd);
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
    for (size_t i=0; i<fMarkers.getSize(); i++) {
        prc->startTag("Marker");
        prc->writeParam("Name", fMarkers[i].fKey);
        prc->writeParam("Pos", fMarkers[i].fValue);
        prc->endTag(true);
    }
    prc->closeTag();

    prc->writeSimpleTag("Loops");
    for (size_t i=0; i<fLoops.getSize(); i++) {
        prc->startTag("Loop");
        prc->writeParam("Name", fLoops[i].fKey);
        prc->writeParam("Start", fLoops[i].fStart);
        prc->writeParam("End", fLoops[i].fEnd);
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
        fMarkers.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fMarkers.getSize(); i++) {
            if (child->getName() != "Marker")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            fMarkers[i].fKey = child->getParam("Name", "");
            fMarkers[i].fValue = child->getParam("Pos", "0").toFloat();
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Loops") {
        fLoops.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fLoops.getSize(); i++) {
            if (child->getName() != "Loop")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            fLoops[i].fKey = child->getParam("Name", "");
            fLoops[i].fStart = child->getParam("Start", "0").toFloat();
            fLoops[i].fEnd = child->getParam("End", "0").toFloat();
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


// plEmoteAnim //
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
