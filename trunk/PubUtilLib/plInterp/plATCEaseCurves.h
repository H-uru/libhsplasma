#ifndef _PLATCEASECURVES_H
#define _PLATCEASECURVES_H

#include "NucleusLib/pnFactory/plCreatable.h"

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
    virtual void prcWrite(pfPrcHelper* prc);
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
    virtual void prcWrite(pfPrcHelper* prc);
};

DllClass plConstAccelEaseCurve : public plATCEaseCurve {
public:
    plConstAccelEaseCurve();
    virtual ~plConstAccelEaseCurve();

    DECLARE_CREATABLE(plConstAccelEaseCurve)
};

#endif
