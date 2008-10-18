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
    fRegions.setSize(count);
    for (i=0; i<count; i++)
        fRegions[i] = mgr->readKey(S);
}

void plDrawInterface::write(hsStream* S, plResManager* mgr) {
    plObjInterface::write(S, mgr);

    S->writeInt(fDrawables.getSize());
    size_t i;
    for (i=0; i<fDrawables.getSize(); i++) {
        S->writeInt(fDrawableKeys[i]);
        mgr->writeKey(S, fDrawables[i]);
    }
    S->writeInt(fRegions.getSize());
    for (i=0; i<fRegions.getSize(); i++)
        mgr->writeKey(S, fRegions[i]);
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
    prc->writeSimpleTag("Regions");
    for (i=0; i<fRegions.getSize(); i++)
        fRegions[i]->prcWrite(prc);
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
    } else if (tag->getName() == "Regions") {
        fRegions.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fRegions.getSize(); i++) {
            fRegions[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plObjInterface::IPrcParse(tag, mgr);
    }
}

size_t plDrawInterface::getNumDrawables() const { return fDrawables.getSize(); }
plKey plDrawInterface::getDrawable(size_t idx) const { return fDrawables[idx]; }
int plDrawInterface::getDrawableKey(size_t idx) const { return fDrawableKeys[idx]; }

void plDrawInterface::clearDrawables() {
    fDrawables.clear();
    fDrawableKeys.clear();
}

void plDrawInterface::addDrawable(plKey draw, int key) {
    fDrawables.append(draw);
    fDrawableKeys.append(key);
}

void plDrawInterface::delDrawable(size_t idx) {
    fDrawables.remove(idx);
    fDrawableKeys.remove(idx);
}

size_t plDrawInterface::getNumRegions() const { return fRegions.getSize(); }
plKey plDrawInterface::getRegion(size_t idx) const { return fRegions[idx]; }
void plDrawInterface::clearRegions() { fRegions.clear(); }
void plDrawInterface::addRegion(plKey obj) { fRegions.append(obj); }
void plDrawInterface::delRegion(size_t idx) { fRegions.remove(idx); }
