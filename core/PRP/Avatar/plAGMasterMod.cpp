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

#include "plAGMasterMod.h"

plAGMasterMod::plAGMasterMod() : fIsGrouped(false), fIsGroupMaster(false) { }

void plAGMasterMod::read(hsStream* S, plResManager* mgr) {
    plSynchedObject::read(S, mgr);

    if (S->getVer() == pvUniversal) {
        fGroupName = S->readSafeStr();
    } else if (S->getVer() < pvEoa) {
        int len = S->readInt();
        fGroupName = S->readStr(len);
    }

    fPrivateAnims.setSize(S->readInt());
    for (size_t i=0; i<fPrivateAnims.getSize(); i++)
        fPrivateAnims[i] = mgr->readKey(S);

    if (S->getVer() == pvLive || S->getVer() == pvUniversal) {
        fIsGrouped = S->readBool();
        fIsGroupMaster = S->readBool();
        if (fIsGroupMaster)
            fMsgForwarder = mgr->readKey(S);
    }

    if (S->getVer() >= pvEoa) {
        fEoaKeys2.setSize(S->readInt());
        for (size_t i=0; i<fEoaKeys2.getSize(); i++)
            fEoaKeys2[i] = mgr->readKey(S);
    }
}

void plAGMasterMod::write(hsStream* S, plResManager* mgr) {
    plSynchedObject::write(S, mgr);

    if (S->getVer() == pvUniversal) {
        S->writeSafeStr(fGroupName);
    } else if (S->getVer() != pvPrime) {
        S->writeInt(0);
    } else if (S->getVer() < pvEoa) {
        S->writeInt(fGroupName.len());
        S->writeStr(fGroupName);
    }

    S->writeInt(fPrivateAnims.getSize());
    for (size_t i=0; i<fPrivateAnims.getSize(); i++)
        mgr->writeKey(S, fPrivateAnims[i]);

    if (S->getVer() == pvLive || S->getVer() == pvUniversal) {
        S->writeBool(fIsGrouped);
        S->writeBool(fIsGroupMaster);
        if (fIsGroupMaster)
            mgr->writeKey(S, fMsgForwarder);
    }

    if (S->getVer() >= pvEoa) {
        S->writeInt(fEoaKeys2.getSize());
        for (size_t i=0; i<fEoaKeys2.getSize(); i++)
            mgr->writeKey(S, fEoaKeys2[i]);
    }
}

void plAGMasterMod::IPrcWrite(pfPrcHelper* prc) {
    plSynchedObject::IPrcWrite(prc);

    prc->startTag("Group");
    prc->writeParam("Name", fGroupName);
    prc->writeParam("IsGrouped", fIsGrouped);
    prc->writeParam("IsGroupMaster", fIsGroupMaster);
    prc->endTag();
    prc->writeSimpleTag("MsgForwarder");
    fMsgForwarder->prcWrite(prc);
    prc->closeTag();
    prc->closeTag();

    prc->writeSimpleTag("PrivateAnims");
    for (size_t i=0; i<fPrivateAnims.getSize(); i++)
        fPrivateAnims[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeComment("Unknown EoA/HexIsle Keys");
    prc->writeSimpleTag("EoaKeys");
    for (size_t i=0; i<fEoaKeys2.getSize(); i++)
        fEoaKeys2[i]->prcWrite(prc);
    prc->closeTag();
}

void plAGMasterMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Group") {
        fGroupName = tag->getParam("Name", "");
        fIsGrouped = tag->getParam("IsGrouped", "False").toBool();
        fIsGroupMaster = tag->getParam("IsGroupMaster", "False").toBool();
        if (tag->hasChildren()) {
            const pfPrcTag* child = tag->getFirstChild();
            if (child->getName() != "MsgForwarder")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            if (child->hasChildren())
                fMsgForwarder = mgr->prcParseKey(child->getFirstChild());;;;;;;
        }
    } else if (tag->getName() == "PrivateAnims") {
        fPrivateAnims.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fPrivateAnims.getSize(); i++) {
            fPrivateAnims[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "EoaKeys") {
        fEoaKeys2.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fEoaKeys2.getSize(); i++) {
            fEoaKeys2[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plSynchedObject::IPrcParse(tag, mgr);
    }
}
