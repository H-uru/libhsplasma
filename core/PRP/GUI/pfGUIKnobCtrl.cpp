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

#include "pfGUIKnobCtrl.h"

pfGUIKnobCtrl::pfGUIKnobCtrl()
    : fEoaInt1(), fEoaInt2(), fEoaInt3(), fEoaInt4(),
      fEoaFl1(), fEoaFl2(), fEoaFl3(), fEoaFl4()
{
    fFlags.setName(kReverseValues, "kReverseValues");
    fFlags.setName(kLeftRightOrientation, "kLeftRightOrientation");
    fFlags.setName(kMapToScreenRange, "kMapToScreenRange");
    fFlags.setName(kTriggerOnlyOnMouseUp, "kTriggerOnlyOnMouseUp");
    fFlags.setName(kMapToAnimationRange, "kMapToAnimationRange");
}

void pfGUIKnobCtrl::read(hsStream* S, plResManager* mgr)
{
    pfGUIValueCtrl::read(S, mgr);

    fAnimationKeys.resize(S->readInt());
    for (size_t i=0; i<fAnimationKeys.size(); i++)
        fAnimationKeys[i] = mgr->readKey(S);

    fAnimName = S->readSafeStr();
    fAnimStartPos.read(S);
    fAnimEndPos.read(S);

    if (S->getVer().isNewPlasma()) {
        fEoaInt1 = S->readInt();
        fEoaInt2 = S->readInt();
        fEoaInt3 = S->readInt();
        fEoaInt4 = S->readInt();
        fEoaFl1 = S->readFloat();
        fEoaFl2 = S->readFloat();
        fEoaFl3 = S->readFloat();
        fEoaFl4 = S->readFloat();
    }
}

void pfGUIKnobCtrl::write(hsStream* S, plResManager* mgr)
{
    pfGUIValueCtrl::write(S, mgr);

    S->writeInt(fAnimationKeys.size());
    for (size_t i=0; i<fAnimationKeys.size(); i++)
        mgr->writeKey(S, fAnimationKeys[i]);

    S->writeSafeStr(fAnimName);
    fAnimStartPos.write(S);
    fAnimEndPos.write(S);

    if (S->getVer().isNewPlasma()) {
        S->writeInt(fEoaInt1);
        S->writeInt(fEoaInt2);
        S->writeInt(fEoaInt3);
        S->writeInt(fEoaInt4);
        S->writeFloat(fEoaFl1);
        S->writeFloat(fEoaFl2);
        S->writeFloat(fEoaFl3);
        S->writeFloat(fEoaFl4);
    }
}

void pfGUIKnobCtrl::IPrcWrite(pfPrcHelper* prc)
{
    pfGUIValueCtrl::IPrcWrite(prc);

    prc->startTag("Animation");
    prc->writeParam("Name", fAnimName);
    prc->endTag();
    for (size_t i=0; i<fAnimationKeys.size(); i++)
        plResManager::PrcWriteKey(prc, fAnimationKeys[i]);
    prc->closeTag();

    prc->writeSimpleTag("AnimStartPos");
    fAnimStartPos.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("AnimEndPos");
    fAnimEndPos.prcWrite(prc);
    prc->closeTag();

    prc->startTag("EoaInts");
    prc->writeParam("Int1", fEoaInt1);
    prc->writeParam("Int2", fEoaInt2);
    prc->writeParam("Int3", fEoaInt3);
    prc->writeParam("Int4", fEoaInt4);
    prc->endTag();

    prc->startTag("EoaFloats");
    prc->writeParam("Float1", fEoaFl1);
    prc->writeParam("Float2", fEoaFl2);
    prc->writeParam("Float3", fEoaFl3);
    prc->writeParam("Float4", fEoaFl4);
    prc->endTag();
}

void pfGUIKnobCtrl::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Animation") {
        fAnimName = tag->getParam("Name", "");
        fAnimationKeys.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fAnimationKeys.size(); i++) {
            fAnimationKeys[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "AnimStartPos") {
        if (tag->hasChildren())
            fAnimStartPos.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "AnimEndPos") {
        if (tag->hasChildren())
            fAnimEndPos.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "EoaInts") {
        fEoaInt1 = tag->getParam("Int1", "0").to_uint();
        fEoaInt2 = tag->getParam("Int2", "0").to_uint();
        fEoaInt3 = tag->getParam("Int3", "0").to_uint();
        fEoaInt4 = tag->getParam("Int4", "0").to_uint();
    } else if (tag->getName() == "EoaFloats") {
        fEoaFl1 = tag->getParam("Float1", "0").to_float();
        fEoaFl2 = tag->getParam("Float2", "0").to_float();
        fEoaFl3 = tag->getParam("Float3", "0").to_float();
        fEoaFl4 = tag->getParam("Float4", "0").to_float();
    } else {
        pfGUIValueCtrl::IPrcParse(tag, mgr);
    }
}
