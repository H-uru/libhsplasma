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

#include "pfGUICheckBoxCtrl.h"

void pfGUICheckBoxCtrl::read(hsStream* S, plResManager* mgr)
{
    pfGUIControlMod::read(S, mgr);

    fAnimKeys.resize(S->readInt());
    for (size_t i=0; i<fAnimKeys.size(); i++)
        fAnimKeys[i] = mgr->readKey(S);
    fAnimName = S->readSafeStr();
    fChecked = S->readBool();
}

void pfGUICheckBoxCtrl::write(hsStream* S, plResManager* mgr)
{
    pfGUIControlMod::write(S, mgr);

    S->writeInt(fAnimKeys.size());
    for (size_t i=0; i<fAnimKeys.size(); i++)
        mgr->writeKey(S, fAnimKeys[i]);
    S->writeSafeStr(fAnimName);
    S->writeBool(fChecked);
}

void pfGUICheckBoxCtrl::IPrcWrite(pfPrcHelper* prc)
{
    pfGUIControlMod::IPrcWrite(prc);

    prc->startTag("CheckBoxParams");
    prc->writeParam("AnimName", fAnimName);
    prc->writeParam("Checked", fChecked);
    prc->endTag(true);

    prc->writeSimpleTag("AnimKeys");
    for (size_t i=0; i<fAnimKeys.size(); i++)
        plResManager::PrcWriteKey(prc, fAnimKeys[i]);
    prc->closeTag();
}

void pfGUICheckBoxCtrl::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "CheckBoxParams") {
        fAnimName = tag->getParam("AnimName", "");
        fChecked = tag->getParam("Checked", "false").to_bool();
    } else if (tag->getName() == "AnimKeys") {
        fAnimKeys.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fAnimKeys.size(); i++) {
            fAnimKeys[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        pfGUIControlMod::IPrcParse(tag, mgr);
    }
}
