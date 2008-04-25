#ifndef _PLONESHOTMOD_H
#define _PLONESHOTMOD_H

#include "NucleusLib/pnModifier/plModifier.h"

DllClass plOneShotMod : public plMultiModifier {
protected:
    plString fAnimName;
    bool fDrivable, fReversible;
    float fSeekDuration, fSmartSeek;
    bool fNoSeek;

public:
    plOneShotMod();
    virtual ~plOneShotMod();

    DECLARE_CREATABLE(plOneShotMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper *prc);
};

#endif
