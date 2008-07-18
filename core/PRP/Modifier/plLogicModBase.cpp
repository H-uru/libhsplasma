#include "plLogicModBase.h"

plLogicModBase::plLogicModBase()
              : fNotify(NULL), fDisabled(false) {
    fLogicFlags.setName(kLocalElement, "kLocalElement");
    fLogicFlags.setName(kReset, "kReset");
    fLogicFlags.setName(kTriggered, "kTriggered");
    fLogicFlags.setName(kOneShot, "kOneShot");
    fLogicFlags.setName(kRequestingTrigger, "kRequestingTrigger");
    fLogicFlags.setName(kTypeActivator, "kTypeActivator");
    fLogicFlags.setName(kMultiTrigger, "kMultiTrigger");
}

plLogicModBase::~plLogicModBase() {
    for (size_t i=0; i<fCommandList.getSize(); i++)
        if (fCommandList[i]) delete fCommandList[i];
    if (fNotify) delete fNotify;
}

IMPLEMENT_CREATABLE(plLogicModBase, kLogicModBase, plSingleModifier)

void plLogicModBase::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    fCommandList.setSizeNull(S->readInt());
    for (size_t i=0; i<fCommandList.getSize(); i++)
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

void plLogicModBase::IPrcWrite(pfPrcHelper* prc) {
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("LogicModParams");
    prc->writeParam("Disabled", fDisabled);
    prc->endTag(true);
    
    prc->writeSimpleTag("Commands");
    for (size_t i=0; i<fCommandList.getSize(); i++)
        fCommandList[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Notify");
    fNotify->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("LogicFlags");
    fLogicFlags.prcWrite(prc);
    prc->closeTag();
}

void plLogicModBase::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "LogicModParams") {
        fDisabled = tag->getParam("Disabled", "false").toBool();
    } else if (tag->getName() == "Commands") {
        fCommandList.setSizeNull(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fCommandList.getSize(); i++) {
            fCommandList[i] = plMessage::Convert(mgr->prcParseCreatable(child));
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Notify") {
        if (tag->hasChildren())
            fNotify = plNotifyMsg::Convert(mgr->prcParseCreatable(tag->getFirstChild()));
    } else if (tag->getName() == "LogicFlags") {
        if (tag->hasChildren())
            fLogicFlags.prcParse(tag->getFirstChild());
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
