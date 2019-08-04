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

#include "plPrintShape.h"

/* plPrintShape */
void plPrintShape::read(hsStream* S, plResManager* mgr)
{
    plObjInterface::read(S, mgr);
    fWidth = S->readFloat();
    fLength = S->readFloat();
    fHeight = S->readFloat();
}

void plPrintShape::write(hsStream* S, plResManager* mgr)
{
    plObjInterface::write(S, mgr);
    S->writeFloat(fWidth);
    S->writeFloat(fLength);
    S->writeFloat(fHeight);
}

void plPrintShape::IPrcWrite(pfPrcHelper* prc)
{
    plObjInterface::IPrcWrite(prc);

    prc->startTag("Dimensions");
    prc->writeParam("Width", fWidth);
    prc->writeParam("Length", fLength);
    prc->writeParam("Height", fHeight);
    prc->endTag(true);
}

void plPrintShape::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Dimensions") {
        fWidth = tag->getParam("Width", "0").to_float();
        fLength = tag->getParam("Length", "0").to_float();
        fHeight = tag->getParam("Height", "0").to_float();
    } else {
        plObjInterface::IPrcParse(tag, mgr);
    }
}


/* plActivePrintShape */
void plActivePrintShape::read(hsStream* S, plResManager* mgr)
{
    plPrintShape::read(S, mgr);

    fDecalMgrs.resize(S->readInt());
    for (size_t i=0; i<fDecalMgrs.size(); i++)
        fDecalMgrs[i] = mgr->readKey(S);
}

void plActivePrintShape::write(hsStream* S, plResManager* mgr)
{
    plPrintShape::write(S, mgr);

    S->writeInt(fDecalMgrs.size());
    for (size_t i=0; i<fDecalMgrs.size(); i++)
        mgr->writeKey(S, fDecalMgrs[i]);
}

void plActivePrintShape::IPrcWrite(pfPrcHelper* prc)
{
    plPrintShape::IPrcWrite(prc);

    prc->writeSimpleTag("DecalMgrs");
    for (size_t i=0; i<fDecalMgrs.size(); i++)
        plResManager::PrcWriteKey(prc, fDecalMgrs[i]);
    prc->closeTag();
}

void plActivePrintShape::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "DecalMgrs") {
        fDecalMgrs.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fDecalMgrs.size(); i++) {
            fDecalMgrs[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plPrintShape::IPrcParse(tag, mgr);
    }
}
