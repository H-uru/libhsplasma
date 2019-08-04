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

#include "plSimulationMsg.h"

/* plSimSuppressMsg */
void plSimSuppressMsg::read(hsStream* S, plResManager* mgr)
{
    plMessage::read(S, mgr);
    fSuppress = S->readBool();
}

void plSimSuppressMsg::write(hsStream* S, plResManager* mgr)
{
    plMessage::write(S, mgr);
    S->writeBool(fSuppress);
}

void plSimSuppressMsg::IPrcWrite(pfPrcHelper* prc)
{
    plMessage::IPrcWrite(prc);

    prc->startTag("SimSuppressParams");
    prc->writeParam("Suppress", fSuppress);
    prc->endTag(true);
}

void plSimSuppressMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "SimSuppressParams") {
        fSuppress = tag->getParam("Suppress", "false").to_bool();
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}


/* plSubWorldMsg */
void plSubWorldMsg::read(hsStream* S, plResManager* mgr)
{
    plMessage::read(S, mgr);
    fWorldKey = mgr->readKey(S);
}

void plSubWorldMsg::write(hsStream* S, plResManager* mgr)
{
    plMessage::write(S, mgr);
    mgr->writeKey(S, fWorldKey);
}

void plSubWorldMsg::IPrcWrite(pfPrcHelper* prc)
{
    plMessage::IPrcWrite(prc);

    prc->writeSimpleTag("WorldKey");
    plResManager::PrcWriteKey(prc, fWorldKey);
    prc->closeTag();
}

void plSubWorldMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "WorldKey") {
        fWorldKey = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
