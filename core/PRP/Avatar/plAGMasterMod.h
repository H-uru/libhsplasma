#ifndef _PLAGMASTERMOD_H
#define _PLAGMASTERMOD_H

#include "PRP/Modifier/plModifier.h"

DllClass plAGMasterMod : public plModifier {
protected:
    hsTArray<plKey> fPrivateAnims, fEoaKeys2;
    bool fFirstEval, fNeedEval, fNeedCompile;
    plString fGroupName; // Only used in UU, auto-deleted in PotS and newer
    bool fLiveA5, fLiveA6;
    plKey fLiveA8;

public:
    plAGMasterMod();
    virtual ~plAGMasterMod();

    DECLARE_CREATABLE(plAGMasterMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
