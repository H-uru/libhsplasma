/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "plNetMsgMembersList.h"

/* plNetMsgMemberInfoHelper */
void plNetMsgMemberInfoHelper::read(hsStream* S, plResManager* mgr)
{
    fFlags = S->readInt();
    fClientGuid.read(S, mgr);
    fAvatarUoid.read(S);
}

void plNetMsgMemberInfoHelper::write(hsStream* S, plResManager* mgr)
{
    S->writeInt(fFlags);
    fClientGuid.write(S, mgr);
    fAvatarUoid.write(S);
}

void plNetMsgMemberInfoHelper::IPrcWrite(pfPrcHelper* prc)
{
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

void plNetMsgMemberInfoHelper::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "MemberInfo") {
        fFlags = tag->getParam("Flags", "0").to_uint();
        const pfPrcTag* child = tag->getFirstChild();
        while (child) {
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


/* plNetMsgMembersList */
void plNetMsgMembersList::read(hsStream* S, plResManager* mgr)
{
    plNetMessage::read(S, mgr);

    fMembers.resize(S->readShort());
    for (size_t i=0; i<fMembers.size(); i++)
        fMembers[i].read(S, mgr);
}

void plNetMsgMembersList::write(hsStream* S, plResManager* mgr)
{
    plNetMessage::write(S, mgr);

    S->writeShort(fMembers.size());
    for (size_t i=0; i<fMembers.size(); i++)
        fMembers[i].write(S, mgr);
}

void plNetMsgMembersList::IPrcWrite(pfPrcHelper* prc)
{
    plNetMessage::IPrcWrite(prc);

    prc->writeSimpleTag("Members");
    for (size_t i=0; i<fMembers.size(); i++)
        fMembers[i].prcWrite(prc);
    prc->closeTag();
}

void plNetMsgMembersList::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Members") {
        fMembers.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fMembers.size(); i++) {
            fMembers[i].prcParse(child, mgr);
            child = child->getNextSibling();
        }
    } else {
        plNetMessage::IPrcParse(tag, mgr);
    }
}

/* plNetMsgMemberUpdate */
void plNetMsgMemberUpdate::read(hsStream* S, plResManager* mgr)
{
    plNetMessage::read(S, mgr);

    fMemberInfo.read(S, mgr);
    fAddMember = S->readBool();
}

void plNetMsgMemberUpdate::write(hsStream* S, plResManager* mgr)
{
    plNetMessage::write(S, mgr);

    fMemberInfo.write(S, mgr);
    S->writeBool(fAddMember);
}

void plNetMsgMemberUpdate::IPrcWrite(pfPrcHelper* prc)
{
    plNetMessage::IPrcWrite(prc);

    prc->startTag("MemberUpdate");
    prc->writeParam("AddMember", fAddMember);
    prc->endTag(false);
    fMemberInfo.prcWrite(prc);
    prc->closeTag();
}

void plNetMsgMemberUpdate::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "MemberUpdate") {
        fAddMember = tag->getParam("AddMember", "false").to_bool();
        const pfPrcTag* child = tag->getFirstChild();
        fMemberInfo.prcParse(child, mgr);
    } else {
        plNetMessage::IPrcParse(tag, mgr);
    }
}
