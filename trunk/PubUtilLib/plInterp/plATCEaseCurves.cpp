#include "plATCEaseCurves.h"

// plATCEaseCurve //
plATCEaseCurve::plATCEaseCurve() { }
plATCEaseCurve::~plATCEaseCurve() { }

IMPLEMENT_CREATABLE(plATCEaseCurve, kATCEaseCurve, plCreatable)

void plATCEaseCurve::read(hsStream* S, plResManager* mgr) {
    fMinLength = S->readFloat();
    fMaxLength = S->readFloat();
    fNormLength = S->readFloat();
    fStartSpeed = S->readFloat();
    fSpeed = S->readFloat();
    fBeginWorldTime = S->readDouble();

    fLength = fNormLength;
}

void plATCEaseCurve::write(hsStream* S, plResManager* mgr) {
    S->writeFloat(fMinLength);
    S->writeFloat(fMaxLength);
    S->writeFloat(fNormLength);
    S->writeFloat(fStartSpeed);
    S->writeFloat(fSpeed);
    S->writeDouble(fBeginWorldTime);
}

void plATCEaseCurve::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("Lengths");
    prc->writeParam("MinLength", fMinLength);
    prc->writeParam("MaxLength", fMaxLength);
    prc->writeParam("NormLength", fNormLength);
    prc->endTag(true);

    prc->startTag("Timing");
    prc->writeParam("StartSpeed", fStartSpeed);
    prc->writeParam("Speed", fSpeed);
    prc->writeParam("BeginWorldTime", fBeginWorldTime);
    prc->endTag(true);
}


// plSplineEaseCurve //
plSplineEaseCurve::plSplineEaseCurve() { }
plSplineEaseCurve::~plSplineEaseCurve() { }

IMPLEMENT_CREATABLE(plSplineEaseCurve, kSplineEaseCurve, plATCEaseCurve)

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


// plConstAccelEaseCurve //
plConstAccelEaseCurve::plConstAccelEaseCurve() { }
plConstAccelEaseCurve::~plConstAccelEaseCurve() { }

IMPLEMENT_CREATABLE(plConstAccelEaseCurve, kConstAccelEaseCurve, plATCEaseCurve)
