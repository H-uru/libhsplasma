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

#include "plNetMsgRelevanceRegions.h"

void plNetMsgRelevanceRegions::read(hsStream* S, plResManager* mgr)
{
    plNetMessage::read(S, mgr);

    fRegionsICareAbout.read(S);
    fRegionsImIn.read(S);
}

void plNetMsgRelevanceRegions::write(hsStream* S, plResManager* mgr)
{
    plNetMessage::write(S, mgr);

    fRegionsICareAbout.write(S);
    fRegionsImIn.write(S);
}

void plNetMsgRelevanceRegions::IPrcWrite(pfPrcHelper* prc)
{
    plNetMessage::IPrcWrite(prc);

    prc->writeSimpleTag("RegionsICareAbout");
    fRegionsICareAbout.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("RegionsImIn");
    fRegionsImIn.prcWrite(prc);
    prc->closeTag();
}

void plNetMsgRelevanceRegions::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "RegionsICareAbout") {
        if (tag->hasChildren())
            fRegionsICareAbout.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "RegionsImIn") {
        if (tag->hasChildren())
            fRegionsImIn.prcParse(tag->getFirstChild());
    } else {
        plNetMessage::IPrcParse(tag, mgr);
    }
}

void plNetMsgRelevanceRegions::setRegion(size_t region, bool in, bool careAbout)
{
    fRegionsImIn.set(region, in);
    fRegionsICareAbout.set(region, careAbout);
}
