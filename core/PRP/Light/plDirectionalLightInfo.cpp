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

#include "plDirectionalLightInfo.h"

/* plLimitedDirLightInfo */
void plLimitedDirLightInfo::read(hsStream* S, plResManager* mgr)
{
    plLightInfo::read(S, mgr);
    fWidth = S->readFloat();
    fHeight = S->readFloat();
    fDepth = S->readFloat();
}

void plLimitedDirLightInfo::write(hsStream* S, plResManager* mgr)
{
    plLightInfo::write(S, mgr);
    S->writeFloat(fWidth);
    S->writeFloat(fHeight);
    S->writeFloat(fDepth);
}

void plLimitedDirLightInfo::IPrcWrite(pfPrcHelper* prc)
{
    plLightInfo::IPrcWrite(prc);
    prc->startTag("Limits");
    prc->writeParam("Width", fWidth);
    prc->writeParam("Height", fHeight);
    prc->writeParam("Depth", fDepth);
    prc->endTag(true);
}

void plLimitedDirLightInfo::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Limits") {
        fWidth = tag->getParam("Width", "0").to_float();
        fHeight = tag->getParam("Height", "0").to_float();
        fDepth = tag->getParam("Depth", "0").to_float();
    } else {
        plLightInfo::IPrcParse(tag, mgr);
    }
}
