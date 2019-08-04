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

#include "plAliasModifier.h"

void plAliasModifier::read(hsStream* S, plResManager* mgr)
{
    plSingleModifier::read(S, mgr);

    size_t len = S->readInt();
    fAlias = S->readStr(len);
}

void plAliasModifier::write(hsStream* S, plResManager* mgr)
{
    plSingleModifier::write(S, mgr);

    S->writeInt(fAlias.size());
    S->writeStr(fAlias);
}

void plAliasModifier::IPrcWrite(pfPrcHelper* prc)
{
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("Alias");
    prc->writeParam("value", fAlias);
    prc->endTag(true);
}

void plAliasModifier::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Alias") {
        fAlias = tag->getParam("value", "");
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
