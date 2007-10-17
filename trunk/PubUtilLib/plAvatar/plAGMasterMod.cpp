#include "plAGMasterMod.h"

plAGMasterMod::plAGMasterMod() : fTarget(NULL) { }
plAGMasterMod::~plAGMasterMod() { }

IMPLEMENT_CREATABLE(plAGMasterMod, kAGMasterMod, plModifier)

void plAGMasterMod::read(hsStream* S, plResManager* mgr) {
    plSynchedObject::read(S, mgr);

    int len = S->readInt();
    fGroupName = S->readStr(len);

    len = S->readInt();
    fPrivateAnims.setSize(len);
    for (int i=0; i<len; i++)
        fPrivateAnims[i] = mgr->readKey(S);
}

void plAGMasterMod::write(hsStream* S, plResManager* mgr) {
    plSynchedObject::write(S, mgr);
    
    if (S->getVer() != pvPrime || fGroupName == NULL) {
        S->writeInt(0);
    } else {
        S->writeInt(strlen(fGroupName));
        S->writeStr(fGroupName);
    }

    S->writeInt(fPrivateAnims.getSize());
    for (size_t i=0; i<fPrivateAnims.getSize(); i++)
        mgr->writeKey(S, fPrivateAnims[i]);
}

void plAGMasterMod::prcWrite(pfPrcHelper* prc) {
    plSynchedObject::prcWrite(prc);

    if (fGroupName != NULL) {
        prc->startTag("Group");
        prc->writeParam("Name", fGroupName);
        prc->endTag(true);
    }
    prc->writeSimpleTag("PrivateAnims");
    for (size_t i=0; i<fPrivateAnims.getSize(); i++)
        fPrivateAnims[i]->prcWrite(prc);
    prc->closeTag();
}
