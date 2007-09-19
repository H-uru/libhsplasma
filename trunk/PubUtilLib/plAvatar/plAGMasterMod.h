#ifndef _PLAGMASTERMOD_H
#define _PLAGMASTERMOD_H

#include "../../NucleusLib/pnModifier/plModifier.h"

DllClass plAGMasterMod : public plModifier {
protected:
    plSceneObject* fTarget;
    //std::map<char*, plAGModifier*> fChannelMods;
    //std::vector<plAGAnimInstance*> fAnimInstances;
    std::vector<plKey> fPrivateAnims;
    //std::vector<plAGAnimInstance*> fATCAnimInstances;
    bool fFirstEval, fNeedEval, fNeedCompile;
    //plAGMasterSDLModifier* fAGMasterSDLMod;
    plString fGroupName; // Only used in UU, auto-deleted in PotS and newer

public:
    plAGMasterMod();
    virtual ~plAGMasterMod();

    DECLARE_CREATABLE(plAGMasterMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
