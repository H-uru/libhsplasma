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

#include "hsAffineParts.h"

void hsAffineParts::read(hsStream* S)
{
    fI = (!S->getVer().isMoul()) ? S->readInt() : 0;
    fT.read(S);
    fQ.read(S);
    fU.read(S);
    fK.read(S);
    fF = S->readFloat();
}

void hsAffineParts::write(hsStream* S)
{
    if (!S->getVer().isMoul())
        S->writeInt(fI);
    fT.write(S);
    fQ.write(S);
    fU.write(S);
    fK.write(S);
    S->writeFloat(fF);
}

void hsAffineParts::prcWrite(pfPrcHelper* prc)
{
    prc->writeSimpleTag("hsAffineParts");
      prc->startTag("I");
      prc->writeParam("value", fI);
      prc->endTag(true);
      prc->writeSimpleTag("T");
        fT.prcWrite(prc);
      prc->closeTag();
      prc->writeSimpleTag("Q");
        fQ.prcWrite(prc);
      prc->closeTag();
      prc->writeSimpleTag("U");
        fU.prcWrite(prc);
      prc->closeTag();
      prc->writeSimpleTag("K");
        fK.prcWrite(prc);
      prc->closeTag();
      prc->startTag("F");
      prc->writeParam("value", fF);
      prc->endTag(true);
    prc->closeTag();
}

void hsAffineParts::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != "hsAffineParts")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    const pfPrcTag* child = tag->getFirstChild();
    while (child) {
        if (child->getName() == "I") {
            fI = child->getParam("value", "0").to_int();
        } else if (child->getName() == "T") {
            if (child->hasChildren())
                fT.prcParse(child->getFirstChild());
        } else if (child->getName() == "Q") {
            if (child->hasChildren())
                fQ.prcParse(child->getFirstChild());
        } else if (child->getName() == "U") {
            if (child->hasChildren())
                fU.prcParse(child->getFirstChild());
        } else if (child->getName() == "K") {
            if (child->hasChildren())
                fK.prcParse(child->getFirstChild());
        } else if (child->getName() == "F") {
            fF = child->getParam("value", "0").to_float();
        } else {
            throw pfPrcTagException(__FILE__, __LINE__, child->getName());
        }
        child = child->getNextSibling();
    }
}

void hsAffineParts::reset()
{
    fI = 0;
    fT = hsVector3(0.0f, 0.0f, 0.0f);
    fQ = hsQuat(0.0f, 0.0f, 0.0f, 1.0f);
    fU = hsQuat(0.0f, 0.0f, 0.0f, 1.0f);
    fK = hsVector3(1.0f, 1.0f, 1.0f);
    fF = 1.0f;
}
