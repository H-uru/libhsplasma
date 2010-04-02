#include "plATCEaseCurves.h"

/* plATCEaseCurve */
plATCEaseCurve::plATCEaseCurve()
              : fStartSpeed(0.0f), fMinLength(0.0f), fMaxLength(0.0f),
                fBeginWorldTime(0.0), fLength(0.0f), fSpeed(0.0f) { }

void plATCEaseCurve::read(hsStream* S, plResManager* mgr) {
    fMinLength = S->readFloat();
    fMaxLength = S->readFloat();
    fLength = S->readFloat();
    fStartSpeed = S->readFloat();
    fSpeed = S->readFloat();
    fBeginWorldTime = S->readDouble();
}

void plATCEaseCurve::write(hsStream* S, plResManager* mgr) {
    S->writeFloat(fMinLength);
    S->writeFloat(fMaxLength);
    S->writeFloat(fLength);
    S->writeFloat(fStartSpeed);
    S->writeFloat(fSpeed);
    S->writeDouble(fBeginWorldTime);
}

void plATCEaseCurve::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("Lengths");
    prc->writeParam("Min", fMinLength);
    prc->writeParam("Max", fMaxLength);
    prc->writeParam("Norm", fLength);
    prc->endTag(true);

    prc->startTag("Timing");
    prc->writeParam("StartSpeed", fStartSpeed);
    prc->writeParam("Speed", fSpeed);
    prc->writeParam("BeginWorldTime", fBeginWorldTime);
    prc->endTag(true);
}

void plATCEaseCurve::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Lengths") {
        fMinLength = tag->getParam("Min", "0").toFloat();
        fMaxLength = tag->getParam("Max", "0").toFloat();
        fLength = tag->getParam("Norm", "0").toFloat();
    } else if (tag->getName() == "Timing") {
        fStartSpeed = tag->getParam("StartSpeed", "0").toFloat();
        fSpeed = tag->getParam("Speed", "0").toFloat();
        fBeginWorldTime = tag->getParam("BeginWorldTime", "0").toFloat();
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}


/* plSplineEaseCurve */
plSplineEaseCurve::plSplineEaseCurve() {
    fCoef[0] = 0.0f;
    fCoef[1] = 0.0f;
    fCoef[2] = 0.0f;
    fCoef[3] = 0.0f;
}

void plSplineEaseCurve::read(hsStream* S, plResManager* mgr) {
    plATCEaseCurve::read(S, mgr);

    fCoef[0] = S->readFloat();
    fCoef[1] = S->readFloat();
    fCoef[2] = S->readFloat();
    fCoef[3] = S->readFloat();
}

void plSplineEaseCurve::write(hsStream* S, plResManager* mgr) {
    plATCEaseCurve::write(S, mgr);

    S->writeFloat(fCoef[0]);
    S->writeFloat(fCoef[1]);
    S->writeFloat(fCoef[2]);
    S->writeFloat(fCoef[3]);
}

void plSplineEaseCurve::IPrcWrite(pfPrcHelper* prc) {
    plATCEaseCurve::IPrcWrite(prc);

    prc->writeTagNoBreak("SplineCoefficients");
    prc->getStream()->writeStr(plString::Format("%f %f %f %f",
                               fCoef[0], fCoef[1], fCoef[2], fCoef[3]));
    prc->closeTagNoBreak();
}

void plSplineEaseCurve::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "SplineCoefficients") {
        hsTList<plString> coefList = tag->getContents();
        if (coefList.getSize() != 4)
            throw pfPrcParseException(__FILE__, __LINE__, "plSplineEaseCurve expects exactly 4 coefficients");
        for (size_t i=0; i<4; i++)
            fCoef[i] = coefList.pop().toFloat();
    } else {
        plATCEaseCurve::IPrcParse(tag, mgr);
    }
}
