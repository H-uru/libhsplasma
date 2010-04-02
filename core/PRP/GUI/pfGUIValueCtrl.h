#ifndef _PFGUIVALUECTRL_H
#define _PFGUIVALUECTRL_H

#include "pfGUIControlMod.h"

DllClass pfGUIValueCtrl : public pfGUIControlMod {
    CREATABLE(pfGUIValueCtrl, kGUIValueCtrl, pfGUIControlMod)

protected:
    float fMin, fMax, fStep;

public:
    pfGUIValueCtrl();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    float getMin() const { return fMin; }
    float getMax() const { return fMax; }
    float getStep() const { return fStep; }

    void setMin(float min) { fMin = min; }
    void setMax(float max) { fMax = max; }
    void setStep(float step) { fStep = step; }
    void setRange(float min, float max) { fMin = min; fMax = max; }
};

#endif
