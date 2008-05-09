#include "plMultistageBehMod.h"

plMultistageBehMod::plMultistageBehMod()
                  : fFreezePhys(false), fSmartSeek(false),
                    fReverseFBControlsOnRelease(false) { }

plMultistageBehMod::~plMultistageBehMod() {
    for (size_t i=0; i<fStages.getSize(); i++)
        delete fStages[i];
}

IMPLEMENT_CREATABLE(plMultistageBehMod, kMultistageBehMod, plSingleModifier)

void plMultistageBehMod::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    fFreezePhys = S->readBool();
    fSmartSeek = S->readBool();
    fReverseFBControlsOnRelease = S->readBool();
    
    fStages.setSizeNull(S->readInt());
    for (size_t i=0; i<fStages.getSize(); i++) {
        fStages[i] = new plAnimStage();
        fStages[i]->read(S, mgr);
    }

    fReceivers.setSize(S->readInt());
    for (size_t i=0; i<fReceivers.getSize(); i++)
        fReceivers[i] = mgr->readKey(S);
}

void plMultistageBehMod::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);

    S->writeBool(fFreezePhys);
    S->writeBool(fSmartSeek);
    S->writeBool(fReverseFBControlsOnRelease);

    S->writeInt(fStages.getSize());
    for (size_t i=0; i<fStages.getSize(); i++)
        fStages[i]->write(S, mgr);

    S->writeInt(fReceivers.getSize());
    for (size_t i=0; i<fReceivers.getSize(); i++)
        mgr->writeKey(S, fReceivers[i]);
}

void plMultistageBehMod::IPrcWrite(pfPrcHelper* prc) {
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("MultistageBehParams");
    prc->writeParam("FreezePhys", fFreezePhys);
    prc->writeParam("SmartSeek", fSmartSeek);
    prc->writeParam("ReverseFBControlsOnRelease", fReverseFBControlsOnRelease);
    prc->endTag(true);

    prc->writeSimpleTag("Stages");
    for (size_t i=0; i<fStages.getSize(); i++)
        fStages[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Receivers");
    for (size_t i=0; i<fReceivers.getSize(); i++)
        fReceivers[i]->prcWrite(prc);
    prc->closeTag();
}

void plMultistageBehMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "MultistageBehParams") {
        fFreezePhys = tag->getParam("FreezePhys", "false").toBool();
        fSmartSeek = tag->getParam("SmartSeek", "false").toBool();
        fReverseFBControlsOnRelease = tag->getParam("ReverseFBControlsOnRelease", "false").toBool();
    } else if (tag->getName() == "Stages") {
        fStages.setSizeNull(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fStages.getSize(); i++) {
            fStages[i] = new plAnimStage();
            fStages[i]->prcParse(child, mgr);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Receivers") {
        fReceivers.setSizeNull(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fReceivers.getSize(); i++) {
            fReceivers[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
