#include "plAnimTimeConvert.h"

/* plAnimTimeConvert */
plAnimTimeConvert::plAnimTimeConvert()
                 : fFlags(0), fBegin(0.0f), fEnd(0.0f), fLoopBegin(0.0f),
                   fLoopEnd(0.0f), fSpeed(1.0f), fCurrentAnimTime(0.0f),
                   fWrapTime(0.0f), fLastEvalWorldTime(0.0),
                   fEaseInCurve(NULL), fEaseOutCurve(NULL),
                   fSpeedEaseCurve(NULL), fCurrentEaseCurve(NULL),
                   fInitialBegin(0.0f), fInitialEnd(0.0f) { }

plAnimTimeConvert::~plAnimTimeConvert() {
    if (fEaseInCurve) delete fEaseInCurve;
    if (fEaseOutCurve) delete fEaseOutCurve;
    if (fSpeedEaseCurve) delete fSpeedEaseCurve;
}

IMPLEMENT_CREATABLE(plAnimTimeConvert, kAnimTimeConvert, plCreatable)

void plAnimTimeConvert::read(hsStream* S, plResManager* mgr) {
    fFlags = S->readInt();
    fBegin = fInitialBegin = S->readFloat();
    fEnd = fInitialEnd = S->readFloat();
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
    //IProcessStateChange(0.0f, fBegin);
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
