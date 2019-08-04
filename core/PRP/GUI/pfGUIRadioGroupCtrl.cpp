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

#include "pfGUIRadioGroupCtrl.h"
#include "pfGUICheckBoxCtrl.h"

void pfGUIRadioGroupCtrl::read(hsStream* S, plResManager* mgr)
{
    pfGUIControlMod::read(S, mgr);

    fControls.resize(S->readInt());
    for (size_t i=0; i<fControls.size(); i++)
        fControls[i] = mgr->readKey(S);

    fDefaultValue = S->readShort();
}

void pfGUIRadioGroupCtrl::write(hsStream* S, plResManager* mgr)
{
    pfGUIControlMod::write(S, mgr);

    S->writeInt(fControls.size());
    for (size_t i=0; i<fControls.size(); i++)
        mgr->writeKey(S, fControls[i]);

    S->writeShort(fDefaultValue);
}

void pfGUIRadioGroupCtrl::IPrcWrite(pfPrcHelper* prc)
{
    pfGUIControlMod::IPrcWrite(prc);

    prc->startTag("Items");
    prc->writeParam("Default", fDefaultValue);
    prc->endTag();
    for (size_t i=0; i<fControls.size(); i++)
        plResManager::PrcWriteKey(prc, fControls[i]);
    prc->closeTag();
}

void pfGUIRadioGroupCtrl::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Items") {
        fDefaultValue = tag->getParam("Default", "0").to_int();
        fControls.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fControls.size(); i++) {
            fControls[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        pfGUIControlMod::IPrcParse(tag, mgr);
    }
}
