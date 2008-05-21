#ifndef _PLAVLADDERMOD_H
#define _PLAVLADDERMOD_H

#include "NucleusLib/pnModifier/plModifier.h"
#include "CoreLib/hsGeometry3.h"

DllClass plAvLadderMod : public plSingleModifier {
public:
    enum TypeField { kBig, kFourFeet, kTwoFeet, kNumTypeFields };

protected:
    bool fGoingUp, fEnabled, fAvatarInBox, fAvatarMounting;
    int fType, fLoops;
    hsVector3 fLadderView;

public:
    plAvLadderMod();
    virtual ~plAvLadderMod();

    DECLARE_CREATABLE(plAvLadderMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
