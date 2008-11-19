#ifndef _PLLADDERMODIFIER_H
#define _PLLADDERMODIFIER_H

#include "PRP/Modifier/plModifier.h"
#include "Math/hsGeometry3.h"

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

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plLadderModifier : public plSingleModifier {
protected:
    plKey fTopLogic, fBottomLogic, fMainLogic;
    plKey fExitTop, fExitBottom, fTopPos, fBottomPos;

public:
    plLadderModifier();
    virtual ~plLadderModifier();

    DECLARE_CREATABLE(plLadderModifier)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
