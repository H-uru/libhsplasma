#include "plNetMsgObject.h"

/* plNetMsgObjectHelper */
void plNetMsgObjectHelper::read(hsStream* S, plResManager* mgr) {
    fUoid.read(S);
}

void plNetMsgObjectHelper::write(hsStream* S, plResManager* mgr) {
    fUoid.write(S);
}

void plNetMsgObjectHelper::IPrcWrite(pfPrcHelper* prc) {
    fUoid.prcWrite(prc);
}

void plNetMsgObjectHelper::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "plKey") {
        fUoid.prcParse(tag);
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}


/* plNetMsgObject */
void plNetMsgObject::read(hsStream* S, plResManager* mgr) {
    plNetMessage::read(S, mgr);
    fHelper.read(S, mgr);
}

void plNetMsgObject::write(hsStream* S, plResManager* mgr) {
    plNetMessage::write(S, mgr);
    fHelper.write(S, mgr);
}

void plNetMsgObject::IPrcWrite(pfPrcHelper* prc) {
    plNetMessage::IPrcWrite(prc);
    fHelper.prcWrite(prc);
}

void plNetMsgObject::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "plNetMsgObjectHelper") {
        fHelper.prcParse(tag, mgr);
    } else {
        plNetMessage::IPrcParse(tag, mgr);
    }
}
