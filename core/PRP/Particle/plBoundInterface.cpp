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

#include "plBoundInterface.h"

plBoundInterface::~plBoundInterface()
{
    delete fBounds;
}

void plBoundInterface::read(hsStream* S, plResManager* mgr)
{
    plObjInterface::read(S, mgr);
    setBounds(mgr->ReadCreatableC<plConvexVolume>(S));
}

void plBoundInterface::write(hsStream* S, plResManager* mgr)
{
    plObjInterface::write(S, mgr);
    mgr->WriteCreatable(S, fBounds);
}

void plBoundInterface::IPrcWrite(pfPrcHelper* prc)
{
    plObjInterface::IPrcWrite(prc);

    prc->writeSimpleTag("Bounds");
    fBounds->prcWrite(prc);
    prc->closeTag();
}

void plBoundInterface::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Bounds") {
        if (tag->hasChildren())
            setBounds(mgr->prcParseCreatableC<plConvexVolume>(tag->getFirstChild()));
    } else {
        plObjInterface::IPrcParse(tag, mgr);
    }
}

void plBoundInterface::setBounds(plConvexVolume* bounds)
{
    delete fBounds;
    fBounds = bounds;
}
