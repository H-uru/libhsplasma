#include "plLogicModBase.h"

const char* plLogicModBase::FlagNames[] = {
    "kLocalElement", "kReset", "kTriggered", "kOneShot", "kRequestingTrigger",
    "kTypeActivator", "kMultiTrigger"
};

plLogicModBase::plLogicModBase()
              : fCounterLimit(0), fTimer(0.0f), fCounter(0), fNotify(NULL),
                fDisabled(false) {
    fLogicFlags.appendNames(7, FlagNames);
}

plLogicModBase::~plLogicModBase() {
    for (size_t i=0; i<fCommandList.getSize(); i++)
        if (fCommandList[i]) delete fCommandList[i];
    if (fNotify) delete fNotify;
}

IMPLEMENT_CREATABLE(plLogicModBase, kLogicModBase, plSingleModifier)

void plLogicModBase::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    size_t count = S->readInt();
    fCommandList.setSizeNull(count);
    for (size_t i=0; i<count; i++)
        fCommandList[i] = plMessage::Convert(mgr->ReadCreatable(S));

    if (fNotify != NULL)
        delete fNotify;
    fNotify = plNotifyMsg::Convert(mgr->ReadCreatable(S));
    fLogicFlags.read(S);
    fDisabled = S->readBool();
}

void plLogicModBase::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);

    S->writeInt(fCommandList.getSize());
    for (size_t i=0; i<fCommandList.getSize(); i++)
        mgr->WriteCreatable(S, fCommandList[i]);

    mgr->WriteCreatable(S, fNotify);
    fLogicFlags.write(S);
    S->writeBool(fDisabled);
}

void plLogicModBase::prcWrite(pfPrcHelper* prc) {
    plSingleModifier::prcWrite(prc);

    prc->writeSimpleTag("Commands");
    for (size_t i=0; i<fCommandList.getSize(); i++) {
        fCommandList[i]->prcWrite(prc);
        prc->closeTag();
    }
    prc->closeTag();

    fNotify->prcWrite(prc);
    prc->closeTag();

    fLogicFlags.prcWrite(prc);
    prc->startTag("LogicModParams");
    prc->writeParam("Disabled", fDisabled);
    prc->endTag(true);
}
