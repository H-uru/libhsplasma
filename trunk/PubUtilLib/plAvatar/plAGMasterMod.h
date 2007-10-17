#ifndef _PLAGMASTERMOD_H
#define _PLAGMASTERMOD_H

#include "../../NucleusLib/pnModifier/plModifier.h"
#include "../plResMgr/plResManager.h"

DllClass plAGMasterMod : public plModifier {
protected:
    plSceneObject* fTarget;
    //std::map<char*, plAGModifier*> fChannelMods;
    //hsTArray<plAGAnimInstance*> fAnimInstances;
    hsTArray<plKey> fPrivateAnims;
    //hsTArray<plAGAnimInstance*> fATCAnimInstances;
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
