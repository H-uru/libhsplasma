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

#include "plPostEffectMod.h"

void plPostEffectMod::read(hsStream* S, plResManager* mgr)
{
    plSingleModifier::read(S, mgr);

    fState.read(S);
    fHither = S->readFloat();
    fYon = S->readFloat();
    fFovX = S->readFloat();
    fFovY = S->readFloat();

    fNodeKey = mgr->readKey(S);
    fDefaultW2C.read(S);
    fDefaultC2W.read(S);
}

void plPostEffectMod::write(hsStream* S, plResManager* mgr)
{
    plSingleModifier::write(S, mgr);

    fState.write(S);
    S->writeFloat(fHither);
    S->writeFloat(fYon);
    S->writeFloat(fFovX);
    S->writeFloat(fFovY);

    mgr->writeKey(S, fNodeKey);
    fDefaultW2C.write(S);
    fDefaultC2W.write(S);
}

void plPostEffectMod::IPrcWrite(pfPrcHelper* prc)
{
    plSingleModifier::IPrcWrite(prc);

    prc->writeSimpleTag("State");
    fState.prcWrite(prc);
    prc->closeTag();

    prc->startTag("View");
    prc->writeParam("Hither", fHither);
    prc->writeParam("Yon", fYon);
    prc->writeParam("FovX", fFovX);
    prc->writeParam("FovY", fFovY);
    prc->endTag(true);

    prc->writeSimpleTag("SceneNode");
    plResManager::PrcWriteKey(prc, fNodeKey);
    prc->closeTag();

    prc->writeSimpleTag("DefaultW2C");
    fDefaultW2C.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("DefaultC2W");
    fDefaultC2W.prcWrite(prc);
    prc->closeTag();
}

void plPostEffectMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "State") {
        if (tag->hasChildren())
            fState.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "View") {
        fHither = tag->getParam("Hither", "0").to_float();
        fYon = tag->getParam("Yon", "0").to_float();
        fFovX = tag->getParam("FovX", "0").to_float();
        fFovY = tag->getParam("FovY", "0").to_float();
    } else if (tag->getName() == "SceneNode") {
        if (tag->hasChildren())
            fNodeKey = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "DefaultW2C") {
        if (tag->hasChildren())
            fDefaultW2C.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "DefaultC2W") {
        if (tag->hasChildren())
            fDefaultC2W.prcParse(tag->getFirstChild());
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
