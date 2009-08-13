#include "plNetMsgMembersList.h"

/* plNetMsgMemberInfoHelper */
plNetMsgMemberInfoHelper::plNetMsgMemberInfoHelper() : fFlags(0) { }
plNetMsgMemberInfoHelper::~plNetMsgMemberInfoHelper() { }

IMPLEMENT_CREATABLE(plNetMsgMemberInfoHelper, kNetMsgMemberInfoHelper,
                    plCreatable)

void plNetMsgMemberInfoHelper::read(hsStream* S, plResManager* mgr) {
    fFlags = S->readInt();
    fClientGuid.read(S, mgr);
    fAvatarUoid.read(S);
}

void plNetMsgMemberInfoHelper::write(hsStream* S, plResManager* mgr) {
    S->writeInt(fFlags);
    fClientGuid.write(S, mgr);
    fAvatarUoid.write(S);
}

void plNetMsgMemberInfoHelper::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("MemberInfo");
    prc->writeParamHex("Flags", fFlags);
    prc->endTag();

    prc->writeSimpleTag("ClientGuid");
    fClientGuid.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("AvatarUoid");
    fAvatarUoid.prcWrite(prc);
    prc->closeTag();

    prc->closeTag();
}

void plNetMsgMemberInfoHelper::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "MemberInfo") {
        fFlags = tag->getParam("Flags", "0").toUint();
        const pfPrcTag* child = tag->getFirstChild();
        while (child != NULL) {
            if (child->getName() == "ClientGuid") {
                if (child->hasChildren())
                    fClientGuid.prcParse(child->getFirstChild(), mgr);
            } else if (child->getName() == "AvatarUoid") {
                if (child->hasChildren())
                    fAvatarUoid.prcParse(child->getFirstChild());
            } else {
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            }
            child = child->getNextSibling();
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}


/* plNetMsgMemberListHelper */
plNetMsgMemberListHelper::plNetMsgMemberListHelper() { }
plNetMsgMemberListHelper::~plNetMsgMemberListHelper() { }

IMPLEMENT_CREATABLE(plNetMsgMemberListHelper, kNetMsgMemberListHelper,
                    plCreatable)

void plNetMsgMemberListHelper::read(hsStream* S, plResManager* mgr) {
    fMembers.setSize(S->readShort());
    for (size_t i=0; i<fMembers.getSize(); i++)
        fMembers[i].read(S, mgr);
}

void plNetMsgMemberListHelper::write(hsStream* S, plResManager* mgr) {
    S->writeShort(fMembers.getSize());
    for (size_t i=0; i<fMembers.getSize(); i++)
        fMembers[i].write(S, mgr);
}

void plNetMsgMemberListHelper::IPrcWrite(pfPrcHelper* prc) {
    prc->writeSimpleTag("Members");
    for (size_t i=0; i<fMembers.getSize(); i++)
        fMembers[i].prcWrite(prc);
    prc->closeTag();
}

void plNetMsgMemberListHelper::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Members") {
        fMembers.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fMembers.getSize(); i++) {
            fMembers[i].prcParse(child, mgr);
            child = child->getNextSibling();
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}


/* plNetMsgMembersList */
plNetMsgMembersList::plNetMsgMembersList() { }
plNetMsgMembersList::~plNetMsgMembersList() { }

IMPLEMENT_CREATABLE(plNetMsgMembersList, kNetMsgMembersList,
                    plNetMsgServerToClient)

void plNetMsgMembersList::read(hsStream* S, plResManager* mgr) {
    plNetMessage::read(S, mgr);
    fHelper.read(S, mgr);
}

void plNetMsgMembersList::write(hsStream* S, plResManager* mgr) {
    plNetMessage::write(S, mgr);
    fHelper.write(S, mgr);
}

void plNetMsgMembersList::IPrcWrite(pfPrcHelper* prc) {
    plNetMessage::IPrcWrite(prc);
    fHelper.prcWrite(prc);
}

void plNetMsgMembersList::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "plNetMsgMemberListHelper") {
        fHelper.prcParse(tag, mgr);
    } else {
        plNetMessage::IPrcParse(tag, mgr);
    }
}


/* plNetMsgMembersListReq */
IMPLEMENT_CREATABLE(plNetMsgMembersListReq, kNetMsgMembersListReq, plNetMessage)
