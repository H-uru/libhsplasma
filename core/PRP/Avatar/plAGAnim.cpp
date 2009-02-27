#include "plAGAnim.h"

/* plAGAnim */
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

    clearApplicators();
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
        clearApplicators();
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

size_t plAGAnim::getNumApplicators() const { return fApps.getSize(); }
plAGApplicator* plAGAnim::getApplicator(size_t idx) const { return fApps[idx]; }
void plAGAnim::addApplicator(plAGApplicator* app) { fApps.append(app); }

void plAGAnim::clearApplicators() {
    for (size_t i=0; i<fApps.getSize(); i++)
        delete fApps[i];
    fApps.clear();
}

void plAGAnim::delApplicator(size_t idx) {
    delete fApps[idx];
    fApps.remove(idx);
}

float plAGAnim::getBlend() const { return fBlend; }
float plAGAnim::getStart() const { return fStart; }
float plAGAnim::getEnd() const { return fEnd; }
plString plAGAnim::getName() const { return fName; }

void plAGAnim::setBlend(float blend) { fBlend = blend; }
void plAGAnim::setStart(float start) { fStart = start; }
void plAGAnim::setEnd(float end) { fEnd = end; }
void plAGAnim::setName(const plString& name) { fName = name; }


/* plAgeGlobalAnim */
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

plString plAgeGlobalAnim::getVarName() const { return fGlobalVarName; }
void plAgeGlobalAnim::setVarName(const plString& name) { fGlobalVarName = name; }
