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

#include "plNetGroupId.h"

void plNetGroupId::read(hsStream* S)
{
    fID.read(S);
    fFlags = S->readByte();
}

void plNetGroupId::write(hsStream* S)
{
    fID.write(S);
    S->writeByte(fFlags);
}

void plNetGroupId::prcWrite(pfPrcHelper* prc)
{
    prc->startTag("plNetGroupId");
    prc->writeParam("Flags", fFlags);
    fID.prcWrite(prc);
    prc->endTag(true);
}

void plNetGroupId::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != "plNetGroupId")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fFlags = tag->getParam("Flags", "0").to_uint();
    if (tag->hasChildren())
        fID.prcParse(tag->getFirstChild());
}
