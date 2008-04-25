#include "plAGAnim.h"

// plAGAnim //
plAGAnim::plAGAnim() : fBlend(0.0f), fStart(0.0f), fEnd(0.0f) { }

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
}

void plAGAnim::IPrcWrite(pfPrcHelper* prc) {
    plSynchedObject::IPrcWrite(prc);

    prc->startTag("AGAnimParams");
    prc->writeParam("Name", fName);
    prc->writeParam("Start", fStart);
    prc->writeParam("End", fEnd);
    prc->endTag(true);

    prc->writeSimpleTag("Applicators");
    for (size_t i=0; i<fApps.getSize(); i++) {
        fApps[i]->prcWrite(prc);
        fApps[i]->getChannel()->prcWrite(prc);
    }
    prc->closeTag();
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
        fMarkers[i].key = S->readSafeStr();
        fMarkers[i].value = S->readFloat();
    }

    fLoops.setSize(S->readInt());
    for (size_t i=0; i<fLoops.getSize(); i++) {
        fLoops[i].key = S->readSafeStr();
        fLoops[i].start = S->readFloat();
        fLoops[i].end = S->readFloat();
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
        S->writeSafeStr(fMarkers[i].key);
        S->writeFloat(fMarkers[i].value);
    }

    S->writeInt(fLoops.getSize());
    for (size_t i=0; i<fLoops.getSize(); i++) {
        S->writeSafeStr(fLoops[i].key);
        S->writeFloat(fLoops[i].start);
        S->writeFloat(fLoops[i].end);
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
        prc->writeParam("name", fMarkers[i].key);
        prc->writeParam("pos", fMarkers[i].value);
        prc->endTag(true);
    }
    prc->closeTag();

    prc->writeSimpleTag("Loops");
    for (size_t i=0; i<fLoops.getSize(); i++) {
        prc->startTag("Loop");
        prc->writeParam("name", fLoops[i].key);
        prc->writeParam("start", fLoops[i].start);
        prc->writeParam("end", fLoops[i].end);
        prc->endTag(true);
    }
    prc->closeTag();

    prc->writeSimpleTag("StopPoints");
    for (size_t i=0; i<fStopPoints.getSize(); i++) {
        prc->startTag("StopPoint");
        prc->writeParam("pos", fStopPoints[i]);
        prc->endTag(true);
    }
    prc->closeTag();
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
