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
        delete fCommandList[i];
    if (fNotify != NULL)
        delete fNotify;
}

IMPLEMENT_CREATABLE(plLogicModBase, kLogicModBase, plSingleModifier)

void plLogicModBase::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    clearCommands();
    fCommandList.setSizeNull(S->readInt());
    for (size_t i=0; i<fCommandList.getSize(); i++)
        fCommandList[i] = plMessage::Convert(mgr->ReadCreatable(S));

    setNotify(plNotifyMsg::Convert(mgr->ReadCreatable(S)));
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
        clearCommands();
        fCommandList.setSizeNull(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fCommandList.getSize(); i++) {
            fCommandList[i] = plMessage::Convert(mgr->prcParseCreatable(child));
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Notify") {
        if (tag->hasChildren())
            setNotify(plNotifyMsg::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else if (tag->getName() == "LogicFlags") {
        if (tag->hasChildren())
            fLogicFlags.prcParse(tag->getFirstChild());
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}

size_t plLogicModBase::getNumCommands() const { return fCommandList.getSize(); }
plMessage* plLogicModBase::getCommand(size_t idx) const { return fCommandList[idx]; }
void plLogicModBase::addCommand(plMessage* cmd) { fCommandList.append(cmd); }

void plLogicModBase::delCommand(size_t idx) {
    delete fCommandList[idx];
    fCommandList.remove(idx);
}

void plLogicModBase::clearCommands() {
    for (size_t i=0; i<fCommandList.getSize(); i++)
        delete fCommandList[i];
    fCommandList.clear();
}

plNotifyMsg* plLogicModBase::getNotify() const { return fNotify; }
bool plLogicModBase::isDisabled() const { return fDisabled; }

void plLogicModBase::setNotify(plNotifyMsg* notify) {
    if (fNotify != NULL)
        delete fNotify;
    fNotify = notify;
}

void plLogicModBase::setDisabled(bool disabled) { fDisabled = disabled; }
hsBitVector& plLogicModBase::getLogicFlags() { return fLogicFlags; }
