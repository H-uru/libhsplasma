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

#include "plAGModifier.h"

void plAGModifier::read(hsStream* S, plResManager* mgr)
{
    plSingleModifier::read(S, mgr);
    fChannelName = S->readSafeStr();
}

void plAGModifier::write(hsStream* S, plResManager* mgr)
{
    plSingleModifier::write(S, mgr);
    S->writeSafeStr(fChannelName);
}

void plAGModifier::IPrcWrite(pfPrcHelper* prc)
{
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("AGModifierParams");
    prc->writeParam("ChannelName", fChannelName);
    prc->endTag(true);
}

void plAGModifier::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "AGModifierParams") {
        fChannelName = tag->getParam("ChannelName", "");
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
