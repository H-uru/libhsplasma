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

#include "plNetMsgGroupOwner.h"

void plNetMsgGroupOwner::read(hsStream* S, plResManager* mgr)
{
    plNetMessage::read(S, mgr);

    fGroups.resize(S->readInt());
    for (size_t i=0; i<fGroups.size(); i++) {
        fGroups[i].fGroupID.read(S);
        fGroups[i].fOwnIt = S->readBool();
    }
}

void plNetMsgGroupOwner::write(hsStream* S, plResManager* mgr)
{
    plNetMessage::write(S, mgr);

    S->writeInt(fGroups.size());
    for (size_t i=0; i<fGroups.size(); i++) {
        fGroups[i].fGroupID.write(S);
        S->writeBool(fGroups[i].fOwnIt);
    }
}

void plNetMsgGroupOwner::IPrcWrite(pfPrcHelper* prc)
{
    plNetMessage::IPrcWrite(prc);

    prc->writeSimpleTag("Groups");
    for (size_t i=0; i<fGroups.size(); i++) {
        prc->startTag("Group");
        prc->writeParam("OwnIt", fGroups[i].fOwnIt);
        prc->endTag();
        fGroups[i].fGroupID.prcWrite(prc);
        prc->closeTag();
    }
    prc->closeTag();
}

void plNetMsgGroupOwner::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Groups") {
        fGroups.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fGroups.size(); i++) {
            if (child->getName() != "Group")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            fGroups[i].fOwnIt = child->getParam("OwnIt", "False").to_bool();
            if (child->hasChildren())
                fGroups[i].fGroupID.prcParse(child->getFirstChild());
            child = child->getNextSibling();
        }
    } else {
        plNetMessage::IPrcParse(tag, mgr);
    }
}
