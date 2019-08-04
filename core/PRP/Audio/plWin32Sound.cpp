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

#include "plWin32Sound.h"

/* plWin32Sound */
void plWin32Sound::IRead(hsStream* S, plResManager* mgr)
{
    plSound::IRead(S, mgr);
    fChannelSelect = S->readByte();
}

void plWin32Sound::IWrite(hsStream* S, plResManager* mgr)
{
    plSound::IWrite(S, mgr);
    S->writeByte(fChannelSelect);
}

void plWin32Sound::IPrcWrite(pfPrcHelper* prc)
{
    plSound::IPrcWrite(prc);
    prc->startTag("ChannelSelect");
    prc->writeParam("channel", fChannelSelect);
    prc->endTag(true);
}

void plWin32Sound::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "ChannelSelect") {
        fChannelSelect = tag->getParam("channel", "0").to_uint();
    } else {
        plSound::IPrcParse(tag, mgr);
    }
}
