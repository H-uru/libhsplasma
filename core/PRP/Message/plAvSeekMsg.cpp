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

#include "plAvSeekMsg.h"

/* plAvSeekMsg */
void plAvSeekMsg::read(hsStream* S, plResManager* mgr)
{
    plAvTaskMsg::read(S, mgr);

    fSeekPoint = mgr->readKey(S);
    if (fSeekPoint.Exists()) {
        fTargetPos.read(S);
        fTargetLookAt.read(S);
    }
    fDuration = S->readFloat();
    fSmartSeek = S->readBool();
    fAnimName = S->readSafeStr();
    fAlignType = S->readShort();
    fNoSeek = S->readBool();
    fFlags = S->readByte();
    fFinishKey = mgr->readKey(S);
}

void plAvSeekMsg::write(hsStream* S, plResManager* mgr)
{
    plAvTaskMsg::write(S, mgr);

    mgr->writeKey(S, fSeekPoint);
    if (fSeekPoint.Exists()) {
        fTargetPos.write(S);
        fTargetLookAt.write(S);
    }
    S->writeFloat(fDuration);
    S->writeBool(fSmartSeek);
    S->writeSafeStr(fAnimName);
    S->writeShort(fAlignType);
    S->writeBool(fNoSeek);
    S->writeByte(fFlags);
    mgr->writeKey(S, fFinishKey);
}

void plAvSeekMsg::IPrcWrite(pfPrcHelper* prc)
{
    plAvTaskMsg::IPrcWrite(prc);

    prc->startTag("SeekParams");
    prc->writeParam("Duration", fDuration);
    prc->writeParam("SmartSeek", fSmartSeek);
    prc->writeParam("AnimName", fAnimName);
    prc->writeParam("AlignType", fAlignType);
    prc->writeParam("NoSeek", fNoSeek);
    prc->writeParam("Flags", fFlags);
    prc->endTag(true);

    prc->writeSimpleTag("SeekPoint");
    plResManager::PrcWriteKey(prc, fSeekPoint);
    if (fSeekPoint.Exists()) {
        prc->writeSimpleTag("TargetPos");
        fTargetPos.prcWrite(prc);
        prc->closeTag();
        prc->writeSimpleTag("TargetLook");
        fTargetLookAt.prcWrite(prc);
        prc->closeTag();
    }
    prc->closeTag();

    prc->writeSimpleTag("FinishKey");
    plResManager::PrcWriteKey(prc, fFinishKey);
    prc->closeTag();
}

void plAvSeekMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "SeekParams") {
        fDuration = tag->getParam("Duration", "0").to_float();
        fSmartSeek = tag->getParam("SmartSeek", "true").to_bool();
        fAnimName = tag->getParam("AnimName", "");
        fAlignType = tag->getParam("AlignType", "0").to_uint();
        fNoSeek = tag->getParam("NoSeek", "false").to_bool();
        fFlags = tag->getParam("Flags", "0").to_uint();
    } else if (tag->getName() == "SeekPoint") {
        const pfPrcTag* child = tag->getFirstChild();
        while (child) {
            if (child->getName() == "plKey") {
                fSeekPoint = mgr->prcParseKey(child);
            } else if (child->getName() == "TargetPos") {
                if (child->hasChildren())
                    fTargetPos.prcParse(child->getFirstChild());
            } else if (child->getName() == "TargetLook") {
                if (child->hasChildren())
                    fTargetLookAt.prcParse(child->getFirstChild());
            } else {
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            }
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "FinishKey") {
        if (tag->hasChildren())
            fFinishKey = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plAvTaskMsg::IPrcParse(tag, mgr);
    }
}


/* plAvOneShotMsg */
void plAvOneShotMsg::read(hsStream* S, plResManager* mgr)
{
    plAvSeekMsg::read(S, mgr);

    fAnimName = S->readSafeStr();
    fDrivable = S->readBool();
    fReversible = S->readBool();
}

void plAvOneShotMsg::write(hsStream* S, plResManager* mgr)
{
    plAvSeekMsg::write(S, mgr);

    S->writeSafeStr(fAnimName);
    S->writeBool(fDrivable);
    S->writeBool(fReversible);
}

void plAvOneShotMsg::IPrcWrite(pfPrcHelper* prc)
{
    plAvSeekMsg::IPrcWrite(prc);

    prc->startTag("OneShotParams");
    prc->writeParam("AnimName", fAnimName);
    prc->writeParam("Drivable", fDrivable);
    prc->writeParam("Reversible", fReversible);
    prc->endTag(true);
}

void plAvOneShotMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "OneShotParams") {
        fAnimName = tag->getParam("AnimName", "");
        fDrivable = tag->getParam("Drivable", "false").to_bool();
        fReversible = tag->getParam("Reversible", "false").to_bool();
    } else {
        plAvSeekMsg::IPrcParse(tag, mgr);
    }
}
