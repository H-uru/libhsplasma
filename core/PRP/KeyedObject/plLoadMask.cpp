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

#include "plLoadMask.h"

void plLoadMask::read(hsStream* S)
{
    unsigned char m = S->readByte();
    fQuality[0] = (m >> 4) | 0xF0;
    fQuality[1] = m | 0xF0;
}

void plLoadMask::write(hsStream* S)
{
    unsigned char m = (fQuality[1] & 0x0F) | (fQuality[0] << 4);
    S->writeByte(m);
}

void plLoadMask::prcWrite(pfPrcHelper* prc)
{
    prc->writeParamHex("LoadMask", fMask);
}

void plLoadMask::prcParse(const pfPrcTag* tag)
{
    fMask = tag->getParam("LoadMask", "0xFFFF").to_uint();
}

void plLoadMask::setQuality(unsigned char low, unsigned char high)
{
    fQuality[0] = low;
    fQuality[1] = high;
}
