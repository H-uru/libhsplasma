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

#include "plAGChannel.h"

void plAGChannel::read(hsStream* S, plResManager* mgr)
{
    fName = S->readSafeStr();
}

void plAGChannel::write(hsStream* S, plResManager* mgr)
{
    S->writeSafeStr(fName);
}

void plAGChannel::IPrcWrite(pfPrcHelper* prc)
{
    prc->startTag("Channel");
    prc->writeParam("Name", fName);
    prc->endTag(true);
}

void plAGChannel::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Channel") {
        fName = tag->getParam("Name", "");
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}
