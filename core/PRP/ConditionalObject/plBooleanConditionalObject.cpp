#include "plBooleanConditionalObject.h"

/* plANDConditionalObject */
void plANDConditionalObject::read(hsStream* S, plResManager* mgr) {
    plConditionalObject::read(S, mgr);
    fChildren.setSize(S->readInt());
    for (size_t i=0; i<fChildren.getSize(); i++)
        fChildren[i] = mgr->readKey(S);
}

void plANDConditionalObject::write(hsStream* S, plResManager* mgr) {
    plConditionalObject::write(S, mgr);
    S->writeInt(fChildren.getSize());
    for (size_t i=0; i<fChildren.getSize(); i++)
        mgr->writeKey(S, fChildren[i]);
}

void plANDConditionalObject::IPrcWrite(pfPrcHelper* prc) {
    plConditionalObject::IPrcWrite(prc);
    prc->writeSimpleTag("Children");
    for (size_t i=0; i<fChildren.getSize(); i++)
        fChildren[i]->prcWrite(prc);
    prc->closeTag();
}

void plANDConditionalObject::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Children") {
        fChildren.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fChildren.getSize(); i++) {
            fChildren[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plConditionalObject::IPrcParse(tag, mgr);
    }
}


/* plORConditionalObject */
void plORConditionalObject::read(hsStream* S, plResManager* mgr) {
    plConditionalObject::read(S, mgr);
    fChildren.setSize(S->readInt());
    for (size_t i=0; i<fChildren.getSize(); i++)
        fChildren[i] = mgr->readKey(S);
}

void plORConditionalObject::write(hsStream* S, plResManager* mgr) {
    plConditionalObject::write(S, mgr);
    S->writeInt(fChildren.getSize());
    for (size_t i=0; i<fChildren.getSize(); i++)
        mgr->writeKey(S, fChildren[i]);
}

void plORConditionalObject::IPrcWrite(pfPrcHelper* prc) {
    plConditionalObject::IPrcWrite(prc);
    prc->writeSimpleTag("Children");
    for (size_t i=0; i<fChildren.getSize(); i++)
        fChildren[i]->prcWrite(prc);
    prc->closeTag();
}

void plORConditionalObject::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Children") {
        fChildren.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fChildren.getSize(); i++) {
            fChildren[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plConditionalObject::IPrcParse(tag, mgr);
    }
}
