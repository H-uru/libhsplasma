#ifndef _PLBLOWER_H
#define _PLBLOWER_H

#include "PRP/Modifier/plModifier.h"

DllClass plBlower : public plSingleModifier {
    CREATABLE(plBlower, kBlower, plSingleModifier)

protected:
    float fMasterPower, fDirectRate, fImpulseRate, fSpringKonst;

public:
    plBlower();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    float getMasterPower() const { return fMasterPower; }
    float getDirectRate() const { return fDirectRate; }
    float getImpulseRate() const { return fImpulseRate; }
    float getSpringKonst() const { return fSpringKonst; }

    void setMasterPower(float power) { fMasterPower = power; }
    void setDirectRate(float rate) { fDirectRate = rate; }
    void setImpulseRate(float rate) { fImpulseRate = rate; }
    void setSpringKonst(float konst) { fSpringKonst = konst; }
};

#endif
