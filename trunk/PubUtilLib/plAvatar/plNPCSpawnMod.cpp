#include "plNPCSpawnMod.h"

plNPCSpawnMod::plNPCSpawnMod() : fAutoSpawn(false), fNotify(NULL) { }

plNPCSpawnMod::~plNPCSpawnMod() {
    if (fNotify) delete fNotify;
}

IMPLEMENT_CREATABLE(plNPCSpawnMod, kNPCSpawnMod, plSingleModifier)

void plNPCSpawnMod::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    fModelName = S->readSafeStr();
    fAccountName = S->readSafeStr();
    fAutoSpawn = S->readBool();

    if (S->readBool())
        fNotify = plNotifyMsg::Convert(mgr->ReadCreatable(S));
}

void plNPCSpawnMod::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);

    S->writeSafeStr(fModelName);
    S->writeSafeStr(fAccountName);
    S->writeBool(fAutoSpawn);

    S->writeBool(fNotify != NULL);
    if (fNotify != NULL)
        mgr->WriteCreatable(S, fNotify);
}

void plNPCSpawnMod::prcWrite(pfPrcHelper* prc) {
    plSingleModifier::prcWrite(prc);

    prc->startTag("NPCSpawnParams");
    prc->writeParam("ModelName", fModelName);
    prc->writeParam("AccountName", fAccountName);
    prc->writeParam("AutoSpawn", fAutoSpawn);
    prc->endTag(true);

    if (fNotify != NULL) {
        fNotify->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("Notify");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
}
