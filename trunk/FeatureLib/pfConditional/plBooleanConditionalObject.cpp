#include "plBooleanConditionalObject.h"
#include "../../PubUtilLib/plResMgr/plResManager.h"

/* plANDConditionalObject */
plANDConditionalObject::plANDConditionalObject() { }
plANDConditionalObject::~plANDConditionalObject() { }

IMPLEMENT_CREATABLE(plANDConditionalObject, kANDConditionalObject,
                    plConditionalObject)

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

void plANDConditionalObject::prcWrite(pfPrcHelper* prc) {
    plConditionalObject::prcWrite(prc);
    prc->writeSimpleTag("Children");
    for (size_t i=0; i<fChildren.getSize(); i++)
        fChildren[i]->prcWrite(prc);
    prc->closeTag();
}


/* plORConditionalObject */
plORConditionalObject::plORConditionalObject() { }
plORConditionalObject::~plORConditionalObject() { }

IMPLEMENT_CREATABLE(plORConditionalObject, kORConditionalObject,
                    plConditionalObject)

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

void plORConditionalObject::prcWrite(pfPrcHelper* prc) {
    plConditionalObject::prcWrite(prc);
    prc->writeSimpleTag("Children");
    for (size_t i=0; i<fChildren.getSize(); i++)
        fChildren[i]->prcWrite(prc);
    prc->closeTag();
}
