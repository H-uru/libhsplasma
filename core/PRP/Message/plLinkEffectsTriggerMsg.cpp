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

#include "plLinkEffectsTriggerMsg.h"

void plLinkEffectsTriggerMsg::read(hsStream* S, plResManager* mgr)
{
    plMessage::read(S, mgr);

    fInvisLevel = S->readInt();
    fLeavingAge = S->readBool();
    fLinkKey = mgr->readKey(S);
    fEffects = S->readInt();
    fLinkInAnimKey = mgr->readKey(S);
}

void plLinkEffectsTriggerMsg::write(hsStream* S, plResManager* mgr)
{
    plMessage::write(S, mgr);

    S->writeInt(fInvisLevel);
    S->writeBool(fLeavingAge);
    mgr->writeKey(S, fLinkKey);
    S->writeInt(fEffects);
    mgr->writeKey(S, fLinkInAnimKey);
}

void plLinkEffectsTriggerMsg::IPrcWrite(pfPrcHelper* prc)
{
    plMessage::IPrcWrite(prc);

    prc->startTag("LinkEffectsTriggerParams");
    prc->writeParam("InvisLevel", fInvisLevel);
    prc->writeParam("Effects", fEffects);
    prc->writeParam("LeavingAge", fLeavingAge);
    prc->endTag(true);

    prc->writeSimpleTag("LinkKey");
    plResManager::PrcWriteKey(prc, fLinkKey);
    prc->closeTag();

    prc->writeSimpleTag("LinkInAnimKey");
    plResManager::PrcWriteKey(prc, fLinkInAnimKey);
    prc->closeTag();
}

void plLinkEffectsTriggerMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "LinkEffectsTriggerParams") {
        fInvisLevel = tag->getParam("InvisLevel", "0").to_uint();
        fEffects = tag->getParam("Effects", "0").to_uint();
        fLeavingAge = tag->getParam("LeavingAge", "False").to_bool();
    } else if (tag->getName() == "LinkKey") {
        if (tag->hasChildren())
            fLinkKey = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "LinkInAnimKey") {
        if (tag->hasChildren())
            fLinkInAnimKey = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
