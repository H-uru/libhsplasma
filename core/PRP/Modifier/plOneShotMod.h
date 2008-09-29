#ifndef _PLONESHOTMOD_H
#define _PLONESHOTMOD_H

#include "plModifier.h"

DllClass plOneShotMod : public plMultiModifier {
protected:
    plString fAnimName;
    bool fDrivable, fReversible, fSmartSeek, fNoSeek;
    float fSeekDuration;

public:
    plOneShotMod();
    virtual ~plOneShotMod();

    DECLARE_CREATABLE(plOneShotMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
