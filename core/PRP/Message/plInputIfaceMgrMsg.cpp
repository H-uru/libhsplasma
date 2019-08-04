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

#include "plInputIfaceMgrMsg.h"

void plInputIfaceMgrMsg::read(hsStream* S, plResManager* mgr)
{
    plMessage::read(S, mgr);

    fCommand = S->readByte();
    fPageID = S->readInt();
    fAgeName = S->readSafeStr();
    fAgeFilename = S->readSafeStr();
    fSpawnPoint = S->readSafeStr();
    fAvKey = mgr->readKey(S);
}

void plInputIfaceMgrMsg::write(hsStream* S, plResManager* mgr)
{
    plMessage::write(S, mgr);

    S->writeByte(fCommand);
    S->writeInt(fPageID);
    S->writeSafeStr(fAgeName);
    S->writeSafeStr(fAgeFilename);
    S->writeSafeStr(fSpawnPoint);
    mgr->writeKey(S, fAvKey);
}

void plInputIfaceMgrMsg::IPrcWrite(pfPrcHelper* prc)
{
    plMessage::IPrcWrite(prc);

    prc->startTag("InputIfaceMgrParams");
    prc->writeParam("Command", fCommand);
    prc->writeParam("PageID", fPageID);
    prc->writeParam("AgeName", fAgeName);
    prc->writeParam("AgeFilename", fAgeFilename);
    prc->writeParam("SpawnPoint", fSpawnPoint);
    prc->endTag(true);

    prc->writeSimpleTag("AvatarKey");
    plResManager::PrcWriteKey(prc, fAvKey);
    prc->closeTag();
}

void plInputIfaceMgrMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "InputIfaceMgrParams") {
        fCommand = tag->getParam("Command", "0").to_uint();
        fPageID = tag->getParam("PageID", "0").to_uint();
        fAgeName = tag->getParam("AgeName", "");
        fAgeFilename = tag->getParam("AgeFilename", "");
        fSpawnPoint = tag->getParam("SpawnPoint", "");
    } else if (tag->getName() == "AvKey") {
        if (tag->hasChildren())
            fAvKey = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
