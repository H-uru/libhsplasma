#ifndef _PLSITTINGMODIFIER_H
#define _PLSITTINGMODIFIER_H

#include "NucleusLib/pnModifier/plModifier.h"

DllClass plSittingModifier : public plSingleModifier {
public:
    enum {
        kApproachFront = 0x1,
        kApproachLeft = 0x2,
        kApproachRight = 0x4,
        kApproachRear = 0x8,
        kApproachMask = kApproachFront | kApproachLeft |
                        kApproachRight | kApproachRear,
        kDisableForward = 0x10
    };

protected:
    unsigned char fMiscFlags;
    hsTArray<plKey> fNotifyKeys;
    plKey fTriggeredAvatarKey;

public:
    plSittingModifier();
    virtual ~plSittingModifier();

    DECLARE_CREATABLE(plSittingModifier)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
