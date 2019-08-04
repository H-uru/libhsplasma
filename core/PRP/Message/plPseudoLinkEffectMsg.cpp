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

#include "plPseudoLinkEffectMsg.h"

void plPseudoLinkEffectMsg::read(hsStream* S, plResManager* mgr)
{
    plMessage::read(S, mgr);
    fLinkObjKey = mgr->readKey(S);
    fAvatarKey = mgr->readKey(S);
}

void plPseudoLinkEffectMsg::write(hsStream* S, plResManager* mgr)
{
    plMessage::write(S, mgr);
    mgr->writeKey(S, fLinkObjKey);
    mgr->writeKey(S, fAvatarKey);
}

void plPseudoLinkEffectMsg::IPrcWrite(pfPrcHelper* prc)
{
    plMessage::IPrcWrite(prc);

    prc->writeSimpleTag("LinkObject");
    plResManager::PrcWriteKey(prc, fLinkObjKey);
    prc->closeTag();

    prc->writeSimpleTag("Avatar");
    plResManager::PrcWriteKey(prc, fAvatarKey);
    prc->closeTag();
}

void plPseudoLinkEffectMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "LinkObject") {
        if (tag->hasChildren())
            fLinkObjKey = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Avatar") {
        if (tag->hasChildren())
            fAvatarKey = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
