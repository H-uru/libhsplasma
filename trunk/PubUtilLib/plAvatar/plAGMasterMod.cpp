#include "plAGMasterMod.h"
#include "../plResMgr/plResManager.h"

plAGMasterMod::plAGMasterMod() : fTarget(NULL), fGroupName(NULL) { }
plAGMasterMod::~plAGMasterMod() {
    if (fGroupName != NULL) delete[] fGroupName;
}

IMPLEMENT_CREATABLE(plAGMasterMod, kAGMasterMod, plModifier)

void plAGMasterMod::read(hsStream* S) {
    plSynchedObject::read(S);

    int len = S->readInt();
    fGroupName = new char[len+1];
    S->read(len, fGroupName);
    fGroupName[len] = 0;

    len = S->readInt();
    fPrivateAnims.resize(len);
    for (int i=0; i<len; i++)
        fPrivateAnims[i] = plResManager::inst->readKey(S);
}

void plAGMasterMod::write(hsStream* S) {
    plSynchedObject::write(S);
    
    if (S->getVer() != pvPrime || fGroupName == NULL) {
        S->writeInt(0);
    } else {
        S->writeInt(strlen(fGroupName));
        S->writeStr(fGroupName);
    }

    S->writeInt(fPrivateAnims.size());
    for (int i=0; i<fPrivateAnims.size(); i++)
        plResManager::inst->writeKey(S, fPrivateAnims[i]);
}

void plAGMasterMod::prcWrite(pfPrcHelper* prc) {
    plSynchedObject::prcWrite(prc);

    if (fGroupName != NULL) {
        prc->startTag("Group");
        prc->writeParam("Name", fGroupName);
        prc->endTag(true);
    }
    prc->writeSimpleTag("PrivateAnims");
    for (int i=0; i<fPrivateAnims.size(); i++)
        fPrivateAnims[i]->prcWrite(prc);
    prc->closeTag();
}
