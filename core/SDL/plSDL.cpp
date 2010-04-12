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

#include "plSDL.h"

unsigned int plSDL::VariableLengthRead(hsStream* S, size_t size) {
    if (size < 0x100)
        return S->readByte();
    else if (size < 0x10000)
        return S->readShort();
    else
        return S->readInt();
}

void plSDL::VariableLengthWrite(hsStream* S, size_t size, unsigned int value) {
    if (size < 0x100)
        S->writeByte(value);
    else if (size < 0x10000)
        S->writeShort(value);
    else
        S->writeInt(value);
}
