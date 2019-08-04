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

#include "plFilterCoordInterface.h"

void plFilterCoordInterface::read(hsStream* S, plResManager* mgr)
{
    plCoordinateInterface::read(S, mgr);
    fFilterMask = S->readInt();
    fRefParentLocalToWorld.read(S);
}

void plFilterCoordInterface::write(hsStream* S, plResManager* mgr)
{
    plCoordinateInterface::write(S, mgr);
    S->writeInt(fFilterMask);
    fRefParentLocalToWorld.write(S);
}

void plFilterCoordInterface::IPrcWrite(pfPrcHelper* prc)
{
    plCoordinateInterface::IPrcWrite(prc);

    prc->startTag("FilterParams");
    prc->writeParamHex("Mask", fFilterMask);
    prc->endTag(true);

    prc->writeSimpleTag("RefParentLocalToWorld");
    fRefParentLocalToWorld.prcWrite(prc);
    prc->closeTag();
}

void plFilterCoordInterface::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "FilterParams") {
        fFilterMask = tag->getParam("Mask", "0").to_uint();
    } else if (tag->getName() == "RefParentLocalToWorld") {
        if (tag->hasChildren())
            fRefParentLocalToWorld.prcParse(tag->getFirstChild());
    } else {
        plCoordinateInterface::IPrcParse(tag, mgr);
    }
}
