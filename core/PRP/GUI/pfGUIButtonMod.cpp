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

#include "pfGUIButtonMod.h"

/* pfGUIButtonMod */
void pfGUIButtonMod::read(hsStream* S, plResManager* mgr)
{
    pfGUIControlMod::read(S, mgr);

    fAnimationKeys.resize(S->readInt());
    for (size_t i=0; i<fAnimationKeys.size(); i++)
        fAnimationKeys[i] = mgr->readKey(S);
    fAnimName = S->readSafeStr();

    fMouseOverAnimKeys.resize(S->readInt());
    for (size_t i=0; i<fMouseOverAnimKeys.size(); i++)
        fMouseOverAnimKeys[i] = mgr->readKey(S);
    fMouseOverAnimName = S->readSafeStr();

    fNotifyType = S->readInt();
    if (S->getVer().isNewPlasma()) {
        fEoaUnknown1 = S->readInt();
        fEoaUnknown2 = S->readInt();
    }
    fDraggable = mgr->readKey(S);
}

void pfGUIButtonMod::write(hsStream* S, plResManager* mgr)
{
    pfGUIControlMod::write(S, mgr);

    S->writeInt(fAnimationKeys.size());
    for (size_t i=0; i<fAnimationKeys.size(); i++)
        mgr->writeKey(S, fAnimationKeys[i]);
    S->writeSafeStr(fAnimName);

    S->writeInt(fMouseOverAnimKeys.size());
    for (size_t i=0; i<fMouseOverAnimKeys.size(); i++)
        mgr->writeKey(S, fMouseOverAnimKeys[i]);
    S->writeSafeStr(fMouseOverAnimName);

    S->writeInt(fNotifyType);
    if (S->getVer().isNewPlasma()) {
        S->writeInt(fEoaUnknown1);
        S->writeInt(fEoaUnknown2);
    }
    mgr->writeKey(S, fDraggable);
}

void pfGUIButtonMod::IPrcWrite(pfPrcHelper* prc)
{
    pfGUIControlMod::IPrcWrite(prc);

    prc->startTag("Animation");
    prc->writeParam("Name", fAnimName);
    prc->endTag();
    for (size_t i=0; i<fAnimationKeys.size(); i++)
        plResManager::PrcWriteKey(prc, fAnimationKeys[i]);
    prc->closeTag();

    prc->startTag("MouseOverAnimation");
    prc->writeParam("Name", fMouseOverAnimName);
    prc->endTag();
    for (size_t i=0; i<fMouseOverAnimKeys.size(); i++)
        plResManager::PrcWriteKey(prc, fMouseOverAnimKeys[i]);
    prc->closeTag();

    prc->startTag("NotifyType");
    prc->writeParam("value", fNotifyType);
    prc->endTag(true);

    prc->writeSimpleTag("Draggable");
    plResManager::PrcWriteKey(prc, fDraggable);
    prc->closeTag();
}

void pfGUIButtonMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Animation") {
        fAnimName = tag->getParam("Name", "");
        fAnimationKeys.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fAnimationKeys.size(); i++) {
            fAnimationKeys[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "MouseOverAnimation") {
        fMouseOverAnimName = tag->getParam("Name", "");
        fMouseOverAnimKeys.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fMouseOverAnimKeys.size(); i++) {
            fMouseOverAnimKeys[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "NotifyType") {
        fNotifyType = tag->getParam("value", "0").to_int();
    } else if (tag->getName() == "Draggable") {
        if (tag->hasChildren())
            fDraggable = mgr->prcParseKey(tag->getFirstChild());
    } else {
        pfGUIControlMod::IPrcParse(tag, mgr);
    }
}
