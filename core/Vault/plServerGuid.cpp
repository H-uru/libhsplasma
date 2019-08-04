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

#include "plServerGuid.h"
#include "Debug/hsExceptions.hpp"
#include <cstring>

plServerGuid::plServerGuid()
{
    fGuid[0] = 0;
    fGuid[1] = 0;
    fGuid[2] = 0;
    fGuid[3] = 0;
    fGuid[4] = 0;
    fGuid[5] = 0;
    fGuid[6] = 0;
    fGuid[7] = 0;
}

bool plServerGuid::operator==(const plServerGuid& other)
{
    return (fGuid[0] == other.fGuid[0]) &&
           (fGuid[1] == other.fGuid[1]) &&
           (fGuid[2] == other.fGuid[2]) &&
           (fGuid[3] == other.fGuid[3]) &&
           (fGuid[4] == other.fGuid[4]) &&
           (fGuid[5] == other.fGuid[5]) &&
           (fGuid[6] == other.fGuid[6]) &&
           (fGuid[7] == other.fGuid[7]);
}

ST::string plServerGuid::toString() const
{
    char buf[17];
    snprintf(buf, 17, "%02X%02X%02X%02X%02X%02X%02X%02X",
             fGuid[0], fGuid[1], fGuid[2], fGuid[3],
             fGuid[4], fGuid[5], fGuid[6], fGuid[7]);
    return ST::string(buf);
}

plServerGuid plServerGuid::FromString(const ST::string& str)
{
    if (str.size() != 16)
        throw hsBadParamException(__FILE__, __LINE__, "Invalid plServerGuid string length");

    plServerGuid guid;
    for (size_t i=0; i<8; i++) {
        char x = str[(2*i)  ];
        char y = str[(2*i)+1];
        if (x >= '0' && x <= '9')
            guid[i] = x - '0';
        else if (x >= 'A' && x <= 'F')
            guid[i] = (x - 'A') + 10;
        else if (x >= 'a' && x <= 'f')
            guid[i] = (x - 'a') + 10;
        else
            throw hsBadParamException(__FILE__, __LINE__, "Bad hex character");

        guid[i] <<= 4;
        if (y >= '0' && y <= '9')
            guid[i] += y - '0';
        else if (y >= 'A' && y <= 'F')
            guid[i] += (y - 'A') + 10;
        else if (y >= 'a' && y <= 'f')
            guid[i] += (y - 'a') + 10;
        else
            throw hsBadParamException(__FILE__, __LINE__, "Bad hex character");
    }
    return guid;
}

void plServerGuid::read(hsStream* S)
{
    S->read(8, fGuid);
}

void plServerGuid::write(hsStream* S)
{
    S->write(8, fGuid);
}
