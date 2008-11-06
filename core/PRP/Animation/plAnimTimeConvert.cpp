#include "plAnimTimeConvert.h"

/* plAnimTimeConvert */
plAnimTimeConvert::plAnimTimeConvert()
                 : fFlags(0), fBegin(0.0f), fEnd(0.0f), fLoopBegin(0.0f),
                   fLoopEnd(0.0f), fSpeed(1.0f), fCurrentAnimTime(0.0f),
                   fLastEvalWorldTime(0.0), fEaseInCurve(NULL),
                   fEaseOutCurve(NULL), fSpeedEaseCurve(NULL) { }

plAnimTimeConvert::~plAnimTimeConvert() {
    if (fEaseInCurve != NULL)
        delete fEaseInCurve;
    if (fEaseOutCurve != NULL)
        delete fEaseOutCurve;
    if (fSpeedEaseCurve != NULL)
        delete fSpeedEaseCurve;

    for (size_t i=0; i<fCallbackMsgs.getSize(); i++)
        delete fCallbackMsgs[i];
}

IMPLEMENT_CREATABLE(plAnimTimeConvert, kAnimTimeConvert, plCreatable)

void plAnimTimeConvert::read(hsStream* S, plResManager* mgr) {
    fFlags = S->readInt();
    fBegin = S->readFloat();
    fEnd = S->readFloat();
    fLoopEnd = S->readFloat();
    fLoopBegin = S->readFloat();
    fSpeed = S->readFloat();

    fEaseInCurve = plATCEaseCurve::Convert(mgr->ReadCreatable(S));
    fEaseOutCurve = plATCEaseCurve::Convert(mgr->ReadCreatable(S));
    fSpeedEaseCurve = plATCEaseCurve::Convert(mgr->ReadCreatable(S));
    fCurrentAnimTime = S->readFloat();
    fLastEvalWorldTime = S->readDouble();

    fCallbackMsgs.setSizeNull(S->readInt());
    for (size_t i=0; i<fCallbackMsgs.getSize(); i++)
        fCallbackMsgs[i] = plEventCallbackMsg::Convert(mgr->ReadCreatable(S));

    fStopPoints.setSizeNull(S->readInt());
    for (size_t i=0; i<fStopPoints.getSize(); i++)
        fStopPoints[i] = S->readFloat();
}

void plAnimTimeConvert::write(hsStream* S, plResManager* mgr) {
    S->writeInt(fFlags);
    S->writeFloat(fBegin);
    S->writeFloat(fEnd);
    S->writeFloat(fLoopEnd);
    S->writeFloat(fLoopBegin);
    S->writeFloat(fSpeed);

    mgr->WriteCreatable(S, fEaseInCurve);
    mgr->WriteCreatable(S, fEaseOutCurve);
    mgr->WriteCreatable(S, fSpeedEaseCurve);
    S->writeFloat(fCurrentAnimTime);
    S->writeDouble(fLastEvalWorldTime);

    S->writeInt(fCallbackMsgs.getSize());
    for (size_t i=0; i<fCallbackMsgs.getSize(); i++)
        mgr->WriteCreatable(S, fCallbackMsgs[i]);

    S->writeInt(fStopPoints.getSize());
    for (size_t i=0; i<fStopPoints.getSize(); i++)
        S->writeFloat(fStopPoints[i]);
}

void plAnimTimeConvert::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("Params");
    prc->writeParamHex("Flags", fFlags);
    prc->writeParam("Begin", fBegin);
    prc->writeParam("End", fEnd);
    prc->writeParam("LoopBegin", fLoopBegin);
    prc->writeParam("LoopEnd", fLoopEnd);
    prc->writeParam("Speed", fSpeed);
    prc->endTag(true);

    if (fEaseInCurve != NULL) {
        prc->writeSimpleTag("EaseInCurve");
        fEaseInCurve->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("EaseInCurve");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
    if (fEaseOutCurve != NULL) {
        prc->writeSimpleTag("EaseOutCurve");
        fEaseOutCurve->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("EaseOutCurve");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
    if (fSpeedEaseCurve != NULL) {
        prc->writeSimpleTag("SpeedEaseCurve");
        fSpeedEaseCurve->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("SpeedEaseCurve");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }

    prc->startTag("Times");
    prc->writeParam("CurrentAnimTime", fCurrentAnimTime);
    prc->writeParam("LastEvalWorldTime", fLastEvalWorldTime);
    prc->endTag(true);

    prc->writeSimpleTag("Callbacks");
    for (size_t i=0; i<fCallbackMsgs.getSize(); i++)
        fCallbackMsgs[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("StopPoints");
    for (size_t i=0; i<fStopPoints.getSize(); i++) {
        prc->startTag("StopPoint");
        prc->writeParam("value", fStopPoints[i]);
        prc->endTag(true);
    }
    prc->closeTag();
}

void plAnimTimeConvert::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Params") {
        fFlags = tag->getParam("Flags", "0").toUint();
        fBegin = tag->getParam("Begin", "0").toFloat();
        fEnd = tag->getParam("End", "0").toFloat();
        fLoopBegin = tag->getParam("LoopBegin", "0").toFloat();
        fLoopEnd = tag->getParam("LoopEnd", "0").toFloat();
        fSpeed = tag->getParam("Speed", "0").toFloat();
    } else if (tag->getName() == "EaseInCurve") {
        if (!tag->getParam("NULL", "false").toBool() && tag->hasChildren())
            fSpeedEaseCurve = plATCEaseCurve::Convert(mgr->prcParseCreatable(tag->getFirstChild()));
    } else if (tag->getName() == "EaseOutCurve") {
        if (!tag->getParam("NULL", "false").toBool() && tag->hasChildren())
            fSpeedEaseCurve = plATCEaseCurve::Convert(mgr->prcParseCreatable(tag->getFirstChild()));
    } else if (tag->getName() == "SpeedEaseCurve") {
        if (!tag->getParam("NULL", "false").toBool() && tag->hasChildren())
            fSpeedEaseCurve = plATCEaseCurve::Convert(mgr->prcParseCreatable(tag->getFirstChild()));
    } else if (tag->getName() == "Times") {
        fCurrentAnimTime = tag->getParam("CurrentAnimTime", "0").toFloat();
        fLastEvalWorldTime = tag->getParam("LastEvalWorldTime", "0").toFloat();
    } else if (tag->getName() == "Callbacks") {
        fCallbackMsgs.setSizeNull(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fCallbackMsgs.getSize(); i++) {
            fCallbackMsgs[i] = plEventCallbackMsg::Convert(mgr->prcParseCreatable(child));
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "StopPoints") {
        fStopPoints.setSizeNull(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fStopPoints.getSize(); i++) {
            if (child->getName() != "StopPoint")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            fStopPoints[i] = child->getParam("value", "0").toFloat();
            child = child->getNextSibling();
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

unsigned int plAnimTimeConvert::getFlags() const { return fFlags; }
float plAnimTimeConvert::getBegin() const { return fBegin; }
float plAnimTimeConvert::getEnd() const { return fEnd; }
float plAnimTimeConvert::getLoopBegin() const { return fLoopBegin; }
float plAnimTimeConvert::getLoopEnd() const { return fLoopEnd; }
float plAnimTimeConvert::getSpeed() const { return fSpeed; }
float plAnimTimeConvert::getCurrentAnimTime() const { return fCurrentAnimTime; }
double plAnimTimeConvert::getLastEvalWorldTime() const { return fLastEvalWorldTime; }
plATCEaseCurve* plAnimTimeConvert::getEaseInCurve() const { return fEaseInCurve; }
plATCEaseCurve* plAnimTimeConvert::getEaseOutCurve() const { return fEaseOutCurve; }
plATCEaseCurve* plAnimTimeConvert::getSpeedEaseCurve() const { return fSpeedEaseCurve; }
const hsTArray<float>& plAnimTimeConvert::getStopPoints() const { return fStopPoints; }

void plAnimTimeConvert::setFlags(unsigned int flags) { fFlags = flags; }

void plAnimTimeConvert::setRange(float begin, float end) {
    fBegin = begin;
    fEnd = end;
}

void plAnimTimeConvert::setLoop(float begin, float end) {
    fLoopBegin = begin;
    fLoopEnd = end;
}

void plAnimTimeConvert::setSpeed(float speed) { fSpeed = speed; }
void plAnimTimeConvert::setCurrentAnimTime(float time) { fCurrentAnimTime = time; }
void plAnimTimeConvert::setLastEvalWorldTime(double time) { fLastEvalWorldTime = time; }

void plAnimTimeConvert::setEaseInCurve(plATCEaseCurve* curve) {
    if (fEaseInCurve != NULL)
        delete fEaseInCurve;
    fEaseInCurve = curve;
}

void plAnimTimeConvert::setEaseOutCurve(plATCEaseCurve* curve) {
    if (fEaseOutCurve != NULL)
        delete fEaseOutCurve;
    fEaseOutCurve = curve;
}

void plAnimTimeConvert::setSpeedEaseCurve(plATCEaseCurve* curve) {
    if (fSpeedEaseCurve != NULL)
        delete fSpeedEaseCurve;
    fSpeedEaseCurve = curve;
}

void plAnimTimeConvert::setStopPoints(const hsTArray<float>& stops) {
    fStopPoints = stops;
}

size_t plAnimTimeConvert::getNumCallbacks() const { return fCallbackMsgs.getSize(); }
plEventCallbackMsg* plAnimTimeConvert::getCallback(size_t idx) const { return fCallbackMsgs[idx]; }
void plAnimTimeConvert::addCallback(plEventCallbackMsg* callback) { fCallbackMsgs.append(callback); }

void plAnimTimeConvert::delCallback(size_t idx) {
    delete fCallbackMsgs[idx];
    fCallbackMsgs.remove(idx);
}

void plAnimTimeConvert::clearCallbacks() {
    for (size_t i=0; i<fCallbackMsgs.getSize(); i++)
        delete fCallbackMsgs[i];
    fCallbackMsgs.clear();
}
