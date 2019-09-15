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

#include "plLoadCloneMsg.h"

plLoadCloneMsg::~plLoadCloneMsg()
{
    delete fTriggerMsg;
}

void plLoadCloneMsg::read(hsStream* S, plResManager* mgr)
{
    plMessage::read(S, mgr);

    fCloneKey = mgr->readKey(S);
    fRequestorKey = mgr->readKey(S);
    fOriginatingPlayerID = S->readInt();
    fUserData = S->readInt();
    fValidMsg = S->readByte();
    fIsLoading = S->readByte();
    setTriggerMsg(mgr->ReadCreatableC<plMessage>(S));
}

void plLoadCloneMsg::write(hsStream* S, plResManager* mgr)
{
    plMessage::write(S, mgr);

    mgr->writeKey(S, fCloneKey);
    mgr->writeKey(S, fRequestorKey);
    S->writeInt(fOriginatingPlayerID);
    S->writeInt(fUserData);
    S->writeByte(fValidMsg);
    S->writeByte(fIsLoading);
    mgr->WriteCreatable(S, fTriggerMsg);
}

void plLoadCloneMsg::IPrcWrite(pfPrcHelper* prc)
{
    plMessage::IPrcWrite(prc);

    prc->writeSimpleTag("CloneKey");
    plResManager::PrcWriteKey(prc, fCloneKey);
    prc->closeTag();

    prc->writeSimpleTag("RequestorKey");
    plResManager::PrcWriteKey(prc, fRequestorKey);
    prc->closeTag();

    prc->startTag("LoadCloneParams");
    prc->writeParam("OriginatingPlayerID", fOriginatingPlayerID);
    prc->writeParam("UserData", fUserData);
    prc->writeParam("Valid", fValidMsg);
    prc->writeParam("Loading", fIsLoading);
    prc->endTag(true);

    if (fTriggerMsg) {
        prc->writeSimpleTag("TriggerMsg");
        fTriggerMsg->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("TriggerMsg");
        prc->writeParam("NULL", "true");
        prc->endTag(true);
    }
}

void plLoadCloneMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "CloneKey") {
        if (tag->hasChildren())
            fCloneKey = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "RequestorKey") {
        if (tag->hasChildren())
            fRequestorKey = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "LoadCloneParams") {
        fOriginatingPlayerID = tag->getParam("OriginatingPlayerID", "0").to_int();
        fUserData = tag->getParam("UserData", "0").to_int();
        fValidMsg = tag->getParam("Valid", "0").to_bool();
        fIsLoading = tag->getParam("Loading", "0").to_bool();
    } else if (tag->getName() == "TriggerMsg") {
        if (tag->getParam("NULL", "false").to_bool())
            setTriggerMsg(nullptr);
        else if (tag->hasChildren())
            setTriggerMsg(mgr->prcParseCreatableC<plMessage>(tag->getFirstChild()));
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}

void plLoadCloneMsg::setTriggerMsg(plMessage* msg)
{
    delete fTriggerMsg;
    fTriggerMsg = msg;
}
