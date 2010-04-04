#include "plNetMsgObject.h"

/* plNetMsgObject */
void plNetMsgObject::read(hsStream* S, plResManager* mgr) {
    plNetMessage::read(S, mgr);
    fUoid.read(S);
}

void plNetMsgObject::write(hsStream* S, plResManager* mgr) {
    plNetMessage::write(S, mgr);
    fUoid.write(S);
}

void plNetMsgObject::IPrcWrite(pfPrcHelper* prc) {
    plNetMessage::IPrcWrite(prc);

    prc->writeSimpleTag("Object");
    fUoid.prcWrite(prc);
    prc->closeTag();
}

void plNetMsgObject::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Object") {
        if (tag->hasChildren())
            fUoid.prcParse(tag->getFirstChild());
    } else {
        plNetMessage::IPrcParse(tag, mgr);
    }
}
