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

#include "plImageLibMod.h"

void plImageLibMod::read(hsStream* S, plResManager* mgr)
{
    plSingleModifier::read(S, mgr);

    fImages.resize(S->readInt());
    for (size_t i=0; i<fImages.size(); i++)
        fImages[i] = mgr->readKey(S);
}

void plImageLibMod::write(hsStream* S, plResManager* mgr)
{
    plSingleModifier::write(S, mgr);

    S->writeInt(fImages.size());
    for (size_t i=0; i<fImages.size(); i++)
        mgr->writeKey(S, fImages[i]);
}

void plImageLibMod::IPrcWrite(pfPrcHelper* prc)
{
    plSingleModifier::IPrcWrite(prc);

    prc->writeSimpleTag("Images");
    for (size_t i=0; i<fImages.size(); i++)
        plResManager::PrcWriteKey(prc, fImages[i]);
    prc->closeTag();
}

void plImageLibMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Images") {
        fImages.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fImages.size(); i++) {
            fImages[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
