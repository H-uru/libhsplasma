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

#include "plCullPoly.h"

void plCullPoly::read(hsStream* S)
{
    fFlags = S->readInt();
    fNorm.read(S);
    fDist = S->readFloat();
    fCenter.read(S);
    fRadius = S->readFloat();

    fVerts.resize(S->readInt());
    for (size_t i=0; i<fVerts.size(); i++)
        fVerts[i].read(S);
}

void plCullPoly::write(hsStream* S)
{
    S->writeInt(fFlags);
    fNorm.write(S);
    S->writeFloat(fDist);
    fCenter.write(S);
    S->writeFloat(fRadius);

    S->writeInt(fVerts.size());
    for (size_t i=0; i<fVerts.size(); i++)
        fVerts[i].write(S);
}

void plCullPoly::prcWrite(pfPrcHelper* prc)
{
    prc->startTag("plCullPoly");
    prc->writeParamHex("Flags", fFlags);
    prc->endTag();

    prc->startTag("Normal");
    prc->writeParam("Dist", fDist);
    prc->endTag();
    fNorm.prcWrite(prc);
    prc->closeTag();

    prc->startTag("Center");
    prc->writeParam("Radius", fRadius);
    prc->endTag();
    fCenter.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Verts");
    for (size_t i=0; i<fVerts.size(); i++)
        fVerts[i].prcWrite(prc);
    prc->closeTag();

    prc->closeTag(); // plCullPoly
}

void plCullPoly::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != "plCullPoly")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    fFlags = tag->getParam("Flags", "0").to_uint();

    const pfPrcTag* child = tag->getFirstChild();
    while (child) {
        if (child->getName() == "Normal") {
            fDist = child->getParam("Dist", "0").to_float();
            if (child->hasChildren())
                fNorm.prcParse(child->getFirstChild());
        } else if (child->getName() == "Center") {
            fRadius = child->getParam("Radius", "0").to_float();
            if (child->hasChildren())
                fCenter.prcParse(child->getFirstChild());
        } else if (child->getName() == "Verts") {
            fVerts.resize(child->countChildren());
            const pfPrcTag* vertChild = child->getFirstChild();
            for (size_t i=0; i<fVerts.size(); i++) {
                fVerts[i].prcParse(vertChild);
                vertChild = vertChild->getNextSibling();
            }
        } else {
            throw pfPrcTagException(__FILE__, __LINE__, child->getName());
        }
        child = child->getNextSibling();
    }
}
