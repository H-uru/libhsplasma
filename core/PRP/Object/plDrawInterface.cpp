#include "plDrawInterface.h"

plDrawInterface::plDrawInterface() { }
plDrawInterface::~plDrawInterface() { }

IMPLEMENT_CREATABLE(plDrawInterface, kDrawInterface, plObjInterface)

void plDrawInterface::read(hsStream* S, plResManager* mgr) {
    plObjInterface::read(S, mgr);

    size_t count = S->readInt();
    fDrawables.setSize(count);
    fDrawableKeys.setSize(count);
    size_t i;
    for (i=0; i<count; i++) {
        fDrawableKeys[i] = S->readInt();
        fDrawables[i] = mgr->readKey(S);
    }
    count = S->readInt();
    fObjects.setSize(count);
    for (i=0; i<count; i++)
        fObjects[i] = mgr->readKey(S);
}

void plDrawInterface::write(hsStream* S, plResManager* mgr) {
    plObjInterface::write(S, mgr);

    S->writeInt(fDrawables.getSize());
    size_t i;
    for (i=0; i<fDrawables.getSize(); i++) {
        S->writeInt(fDrawableKeys[i]);
        mgr->writeKey(S, fDrawables[i]);
    }
    S->writeInt(fObjects.getSize());
    for (i=0; i<fObjects.getSize(); i++)
        mgr->writeKey(S, fObjects[i]);
}

void plDrawInterface::IPrcWrite(pfPrcHelper* prc) {
    plObjInterface::IPrcWrite(prc);

    size_t i;
    prc->writeSimpleTag("Drawables");
    for (i=0; i<fDrawables.getSize(); i++) {
        prc->startTag("Drawable");
        prc->writeParam("key", fDrawableKeys[i]);
        prc->endTag();
        fDrawables[i]->prcWrite(prc);
        prc->closeTag();
    }
    prc->closeTag();
    prc->writeSimpleTag("Objects");
    for (i=0; i<fObjects.getSize(); i++)
        fObjects[i]->prcWrite(prc);
    prc->closeTag();
}

void plDrawInterface::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Drawables") {
        fDrawables.setSize(tag->countChildren());
        fDrawableKeys.setSizeNull(fDrawables.getSize());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fDrawables.getSize(); i++) {
            if (child->getName() != "Drawable")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            fDrawableKeys[i] = child->getParam("key", "0").toInt();
            if (child->hasChildren())
                fDrawables[i] = mgr->prcParseKey(child->getFirstChild());
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Objects") {
        fObjects.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fObjects.getSize(); i++) {
            fObjects[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plObjInterface::IPrcParse(tag, mgr);
    }
}

size_t plDrawInterface::getNumDrawables() const {
    return fDrawables.getSize();
}

plKey plDrawInterface::getDrawable(size_t idx) const {
    return fDrawables[idx];
}

int plDrawInterface::getDrawableKey(size_t idx) const {
    return fDrawableKeys[idx];
}

size_t plDrawInterface::getNumObjects() const {
    return fObjects.getSize();
}

plKey plDrawInterface::getObject(size_t idx) const {
    return fObjects[idx];
}
