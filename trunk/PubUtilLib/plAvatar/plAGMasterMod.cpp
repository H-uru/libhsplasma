#include "plAGMasterMod.h"

plAGMasterMod::plAGMasterMod() : fTarget(NULL), fLiveA5(false), fLiveA6(false) { }
plAGMasterMod::~plAGMasterMod() { }

IMPLEMENT_CREATABLE(plAGMasterMod, kAGMasterMod, plModifier)

void plAGMasterMod::read(hsStream* S, plResManager* mgr) {
    plSynchedObject::read(S, mgr);

    int len = S->readInt();
    fGroupName = S->readStr(len);

    fPrivateAnims.setSize(S->readInt());
    for (size_t i=0; i<fPrivateAnims.getSize(); i++)
        fPrivateAnims[i] = mgr->readKey(S);

    if (S->getVer() == pvLive) {
        fLiveA5 = S->readBool();
        fLiveA6 = S->readBool();
        if (fLiveA6)
            fLiveA8 = mgr->readKey(S);
    }
}

void plAGMasterMod::write(hsStream* S, plResManager* mgr) {
    plSynchedObject::write(S, mgr);
    
    if (S->getVer() != pvPrime) {
        S->writeInt(0);
    } else {
        S->writeInt(fGroupName.len());
        S->writeStr(fGroupName);
    }

    S->writeInt(fPrivateAnims.getSize());
    for (size_t i=0; i<fPrivateAnims.getSize(); i++)
        mgr->writeKey(S, fPrivateAnims[i]);

    if (S->getVer() == pvLive) {
        S->writeBool(fLiveA5);
        S->writeBool(fLiveA6);
        if (fLiveA6)
            mgr->writeKey(S, fLiveA8);
    }
}

void plAGMasterMod::prcWrite(pfPrcHelper* prc) {
    plSynchedObject::prcWrite(prc);

    if (!fGroupName.empty()) {
        prc->startTag("Group");
        prc->writeParam("Name", fGroupName);
        prc->endTag(true);
    }
    prc->writeSimpleTag("PrivateAnims");
    for (size_t i=0; i<fPrivateAnims.getSize(); i++)
        fPrivateAnims[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeComment("Unknown Live Params");
    prc->startTag("LiveParams");
    prc->writeParam("thisA5", fLiveA5);
    prc->writeParam("thisA6", fLiveA6);
    prc->endTag();
    if (fLiveA6)
        fLiveA8->prcWrite(prc);
    prc->closeTag();
}
