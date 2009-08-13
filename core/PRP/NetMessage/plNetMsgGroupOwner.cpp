#include "plNetMsgGroupOwner.h"

plNetMsgGroupOwner::GroupInfo::GroupInfo() : fOwnIt(false) { }

plNetMsgGroupOwner::plNetMsgGroupOwner() { }
plNetMsgGroupOwner::~plNetMsgGroupOwner() { }

IMPLEMENT_CREATABLE(plNetMsgGroupOwner, kNetMsgGroupOwner, plNetMsgServerToClient)

void plNetMsgGroupOwner::read(hsStream* S, plResManager* mgr) {
    plNetMessage::read(S, mgr);

    fGroups.setSize(S->readInt());
    for (size_t i=0; i<fGroups.getSize(); i++) {
        fGroups[i].fGroupID.read(S);
        fGroups[i].fOwnIt = S->readBool();
    }
}

void plNetMsgGroupOwner::write(hsStream* S, plResManager* mgr) {
    plNetMessage::write(S, mgr);

    S->writeInt(fGroups.getSize());
    for (size_t i=0; i<fGroups.getSize(); i++) {
        fGroups[i].fGroupID.write(S);
        S->writeBool(fGroups[i].fOwnIt);
    }
}

void plNetMsgGroupOwner::IPrcWrite(pfPrcHelper* prc) {
    plNetMessage::IPrcWrite(prc);

    prc->writeSimpleTag("Groups");
    for (size_t i=0; i<fGroups.getSize(); i++) {
        prc->startTag("Group");
        prc->writeParam("OwnIt", fGroups[i].fOwnIt);
        prc->endTag();
        fGroups[i].fGroupID.prcWrite(prc);
        prc->closeTag();
    }
    prc->closeTag();
}

void plNetMsgGroupOwner::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Groups") {
        fGroups.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fGroups.getSize(); i++) {
            if (child->getName() != "Group")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            fGroups[i].fOwnIt = child->getParam("OwnIt", "False").toBool();
            if (child->hasChildren())
                fGroups[i].fGroupID.prcParse(child->getFirstChild());
            child = child->getNextSibling();
        }
    } else {
        plNetMessage::IPrcParse(tag, mgr);
    }
}
