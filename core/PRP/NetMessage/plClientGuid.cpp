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

#include "plClientGuid.h"

void plClientGuid::read(hsStream* S, plResManager* mgr)
{
    fFlags = S->readShort();
    if ((fFlags & kAcctUuid) != 0)
        fAcctUuid.read(S);
    if ((fFlags & kPlayerID) != 0 || (fFlags & kTempPlayerID) != 0)
        fPlayerID = S->readInt();
    if ((fFlags & kPlayerName) != 0) {
        unsigned short sz = S->readShort();
        fPlayerName = S->readStr(sz);
    }
    if ((fFlags & kCCRLevel) != 0)
        fCCRLevel = S->readByte();
    if ((fFlags & kProtectedLogin) != 0)
        fProtectedLogin = S->readByte();
    if ((fFlags & kBuildType) != 0)
        fBuildType = S->readByte();
    if ((fFlags & kSrcAddr) != 0)
        fSrcAddr = S->readInt();
    if ((fFlags & kSrcPort) != 0)
        fSrcPort = S->readShort();
    if ((fFlags & kReserved) != 0)
        fReserved = S->readShort();
    if ((fFlags & kClientKey) != 0) {
        unsigned short sz = S->readShort();
        fClientKey = S->readStr(sz);
    }
}

void plClientGuid::write(hsStream* S, plResManager* mgr)
{
    S->writeShort(fFlags);
    if ((fFlags & kAcctUuid) != 0)
        fAcctUuid.write(S);
    if ((fFlags & kPlayerID) != 0 || (fFlags & kTempPlayerID) != 0)
        S->writeInt(fPlayerID);
    if ((fFlags & kPlayerName) != 0) {
        S->writeShort(fPlayerName.size());
        S->writeStr(fPlayerName);
    }
    if ((fFlags & kCCRLevel) != 0)
        S->writeByte(fCCRLevel);
    if ((fFlags & kProtectedLogin) != 0)
        S->writeByte(fProtectedLogin);
    if ((fFlags & kBuildType) != 0)
        S->writeByte(fBuildType);
    if ((fFlags & kSrcAddr) != 0)
        S->writeInt(fSrcAddr);
    if ((fFlags & kSrcPort) != 0)
        S->writeShort(fSrcPort);
    if ((fFlags & kReserved) != 0)
        S->writeShort(fReserved);
    if ((fFlags & kClientKey) != 0) {
        S->writeShort(fClientKey.size());
        S->writeStr(fClientKey);
    }
}

void plClientGuid::IPrcWrite(pfPrcHelper* prc)
{
    prc->startTag("ClientParams");
    prc->writeParamHex("Flags", fFlags);
    prc->endTag();

    if ((fFlags & kAcctUuid) != 0) {
        prc->writeSimpleTag("AccountUuid");
        fAcctUuid.prcWrite(prc);
        prc->closeTag();
    }
    if ((fFlags & kPlayerID) != 0 || (fFlags & kTempPlayerID) != 0 ||
        (fFlags & kPlayerName) != 0) {
        prc->startTag("Player");
        if ((fFlags & kPlayerID) != 0 || (fFlags & kTempPlayerID) != 0)
            prc->writeParam("ID", fPlayerID);
        if ((fFlags & kPlayerName) != 0)
            prc->writeParam("Name", fPlayerName);
        prc->endTag(true);
    }
    if ((fFlags & kCCRLevel) != 0) {
        prc->startTag("CCR");
        prc->writeParam("Level", fCCRLevel);
        prc->endTag(true);
    }
    if ((fFlags & kProtectedLogin) != 0) {
        prc->startTag("ProtectedLogin");
        prc->writeParam("value", fProtectedLogin);
        prc->endTag(true);
    }
    if ((fFlags & kBuildType) != 0) {
        prc->startTag("BuildType");
        prc->writeParam("value", fBuildType);
        prc->endTag(true);
    }
    if ((fFlags & kSrcAddr) != 0 || ((fFlags & kSrcPort) != 0)) {
        prc->startTag("SourceAddress");
        if ((fFlags & kSrcAddr) != 0)
            prc->writeParamHex("IP", fSrcAddr);
        if ((fFlags & kSrcPort) != 0)
            prc->writeParam("Port", fSrcPort);
        prc->endTag(true);
    }
    if ((fFlags & kReserved) != 0) {
        prc->startTag("Reserved");
        prc->writeParam("value", fReserved);
        prc->endTag(true);
    }
    if ((fFlags & kClientKey) != 0) {
        prc->startTag("ClientKey");
        prc->writeParam("value", fClientKey);
        prc->endTag(true);
    }

    prc->closeTag();
}

void plClientGuid::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "NetMsgParams") {
        fFlags = tag->getParam("Flags", "0").to_uint();
        const pfPrcTag* child = tag->getFirstChild();
        while (child) {
            if (child->getName() == "AccountUuid") {
                if (child->hasChildren())
                    fAcctUuid.prcParse(child->getFirstChild());
            } else if (child->getName() == "Player") {
                fPlayerID = child->getParam("ID", "0").to_uint();
                fPlayerName = child->getParam("Name", "");
            } else if (child->getName() == "CCR") {
                fCCRLevel = child->getParam("Level", "0").to_uint();
            } else if (child->getName() == "ProtectedLogin") {
                fProtectedLogin = child->getParam("value", "0").to_uint();
            } else if (child->getName() == "BuildType") {
                fBuildType = child->getParam("value", "0").to_uint();
            } else if (child->getName() == "SourceAddress") {
                fSrcAddr = child->getParam("IP", "0").to_uint();
                fSrcPort = child->getParam("Port", "0").to_uint();
            } else if (child->getName() == "Reserved") {
                fReserved = child->getParam("value", "0").to_uint();
            } else if (child->getName() == "ClientKey") {
                fClientKey = child->getParam("value", "");
            } else {
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            }
            child = child->getNextSibling();
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}
