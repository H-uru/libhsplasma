#include "plSpawnModifier.h"

/* plSpawnMod */
plSpawnMod::plSpawnMod() : fBool1(false), fDisableDraw(false) { }

void plSpawnMod::read(hsStream* S, plResManager* mgr) {
    plModifier::read(S, mgr);

    fAge = S->readSafeStr();
    fPage = S->readSafeStr();
    fObjName = S->readSafeStr();
    fBool1 = S->readBool();
    fDisableDraw = S->readBool();
}

void plSpawnMod::write(hsStream* S, plResManager* mgr) {
    plModifier::write(S, mgr);

    S->writeSafeStr(fAge);
    S->writeSafeStr(fPage);
    S->writeSafeStr(fObjName);
    S->writeBool(fBool1);
    S->writeBool(fDisableDraw);
}

void plSpawnMod::IPrcWrite(pfPrcHelper* prc) {
    plModifier::IPrcWrite(prc);

    prc->startTag("SpawnParams");
    prc->writeParam("Age", fAge);
    prc->writeParam("Page", fPage);
    prc->writeParam("ObjName", fObjName);
    prc->writeParam("Bool1", fBool1);
    prc->writeParam("DisableDraw", fDisableDraw);
    prc->endTag(true);
}

void plSpawnMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "SpawnParams") {
        fAge = tag->getParam("Age", "");
        fPage = tag->getParam("Page", "");
        fObjName = tag->getParam("ObjName", "");
        fBool1 = tag->getParam("Bool1", "false").toBool();
        fDisableDraw = tag->getParam("DisableDraw", "false").toBool();
    } else {
        plModifier::IPrcParse(tag, mgr);
    }
}
