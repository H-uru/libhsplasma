#ifndef _PLAGMODIFIER_H
#define _PLAGMODIFIER_H

#include "NucleusLib/pnModifier/plModifier.h"

DllClass plAGModifier : public plSingleModifier {
protected:
    //hsTArray<plAGApplicator*> fApps;
    plString fChannelName;
    bool fAutoApply, fEnabled;

public:
    plAGModifier();
    virtual ~plAGModifier();

    DECLARE_CREATABLE(plAGModifier)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
