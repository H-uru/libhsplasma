#ifndef _PLATCEASECURVES_H
#define _PLATCEASECURVES_H

#include "PRP/plCreatable.h"

DllClass plATCEaseCurve : public plCreatable {
protected:
    float fStartSpeed, fMinLength, fMaxLength, fNormLength;
    double fBeginWorldTime;
    float fLength, fSpeed;

public:
    plATCEaseCurve();
    virtual ~plATCEaseCurve();

    DECLARE_CREATABLE(plATCEaseCurve)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plSplineEaseCurve : public plATCEaseCurve {
protected:
    float fCoef[4];

public:
    plSplineEaseCurve();
    virtual ~plSplineEaseCurve();

    DECLARE_CREATABLE(plSplineEaseCurve)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plConstAccelEaseCurve : public plATCEaseCurve {
public:
    plConstAccelEaseCurve();
    virtual ~plConstAccelEaseCurve();

    DECLARE_CREATABLE(plConstAccelEaseCurve)
};

#endif
