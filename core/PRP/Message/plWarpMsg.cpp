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

#include "plWarpMsg.h"

void plWarpMsg::read(hsStream* S, plResManager* mgr)
{
    plMessage::read(S, mgr);

    fTransform.read(S);
    fWarpFlags = S->readInt();
}

void plWarpMsg::write(hsStream* S, plResManager* mgr)
{
    plMessage::write(S, mgr);

    fTransform.write(S);
    S->writeInt(fWarpFlags);
}

void plWarpMsg::IPrcWrite(pfPrcHelper* prc)
{
    plMessage::IPrcWrite(prc);

    prc->startTag("WarpParams");
    prc->writeParamHex("Flags", fWarpFlags);
    prc->endTag(true);
    prc->writeSimpleTag("WarpTo");
    fTransform.prcWrite(prc);
    prc->closeTag();
}

void plWarpMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "WarpParams") {
        fWarpFlags = tag->getParam("Flags", "0").to_uint();
    } else if (tag->getName() == "WarpTo") {
        fTransform.prcParse(tag->getFirstChild());
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
