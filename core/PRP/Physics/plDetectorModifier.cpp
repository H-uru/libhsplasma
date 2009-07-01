#include "plDetectorModifier.h"

/* plDetectorModifier */
plDetectorModifier::plDetectorModifier() { }
plDetectorModifier::~plDetectorModifier() { }

IMPLEMENT_CREATABLE(plDetectorModifier, kDetectorModifier, plSingleModifier)

void plDetectorModifier::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    fReceivers.setSize(S->readInt());
    for (size_t i=0; i<fReceivers.getSize(); i++)
        fReceivers[i] = mgr->readKey(S);
    fRemoteMod = mgr->readKey(S);
    fProxyKey = mgr->readKey(S);
}

void plDetectorModifier::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);

    S->writeInt(fReceivers.getSize());
    for (size_t i=0; i<fReceivers.getSize(); i++)
        mgr->writeKey(S, fReceivers[i]);
    mgr->writeKey(S, fRemoteMod);
    mgr->writeKey(S, fProxyKey);
}

void plDetectorModifier::IPrcWrite(pfPrcHelper* prc) {
    plSingleModifier::IPrcWrite(prc);

    prc->writeSimpleTag("Receivers");
    for (size_t i=0; i<fReceivers.getSize(); i++)
        fReceivers[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("RemoteMod");
    fRemoteMod->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Proxy");
    fProxyKey->prcWrite(prc);
    prc->closeTag();
}

void plDetectorModifier::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Receivers") {
        fReceivers.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fReceivers.getSize(); i++) {
            fReceivers[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "RemoteMod") {
        if (tag->hasChildren())
            fRemoteMod = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Proxy") {
        if (tag->hasChildren())
            fProxyKey = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}

size_t plDetectorModifier::getNumReceivers() const { return fReceivers.getSize(); }
plKey plDetectorModifier::getReceiver(size_t idx) const { return fReceivers[idx]; }
void plDetectorModifier::addReceiver(plKey rcvr) { fReceivers.append(rcvr); }
void plDetectorModifier::delReceiver(size_t idx) { fReceivers.remove(idx); }
void plDetectorModifier::clearReceivers() { fReceivers.clear(); }

plKey plDetectorModifier::getRemoteMod() const { return fRemoteMod; }
plKey plDetectorModifier::getProxy() const { return fProxyKey; }

void plDetectorModifier::setRemoteMod(plKey mod) { fRemoteMod = mod; }
void plDetectorModifier::setProxy(plKey proxy) { fProxyKey = proxy; }


/* plPickingDetector */
IMPLEMENT_CREATABLE(plPickingDetector, kPickingDetector, plDetectorModifier)
