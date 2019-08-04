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

#include "plSeekPointMod.h"

void plSeekPointMod::read(hsStream* S, plResManager* mgr)
{
    plMultiModifier::read(S, mgr);
    size_t len = S->readInt();
    fName = S->readStr(len);
}

void plSeekPointMod::write(hsStream* S, plResManager* mgr)
{
    plMultiModifier::write(S, mgr);
    S->writeInt(fName.size());
    S->writeStr(fName);
}

void plSeekPointMod::IPrcWrite(pfPrcHelper* prc)
{
    plMultiModifier::IPrcWrite(prc);

    prc->startTag("SeekPoint");
    prc->writeParam("Name", fName);
    prc->endTag(true);
}

void plSeekPointMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "SeekPoint") {
        fName = tag->getParam("Name", "");
    } else {
        plMultiModifier::IPrcParse(tag, mgr);
    }
}
