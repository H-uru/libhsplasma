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

#include "plUuid.h"
#include <string_theory/format>
#include <cstring>

static const unsigned char nullDat4[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
const plUuid plUuid::Null(0, 0, 0, nullDat4);

plUuid::plUuid(unsigned int data1, unsigned short data2, unsigned short data3,
               const unsigned char* data4)
    : fData1(data1), fData2(data2), fData3(data3)
{
    memcpy(fData4, data4, sizeof(fData4));
}

bool plUuid::operator==(const plUuid& other) const
{
    if (fData1 != other.fData1 || fData2 != other.fData2 || fData3 != other.fData3)
        return false;
    return (memcmp(fData4, other.fData4, sizeof(fData4)) == 0);
}

bool plUuid::operator!=(const plUuid& other) const
{
    if (fData1 == other.fData1 || fData2 == other.fData2 || fData3 == other.fData3)
        return false;
    return (memcmp(fData4, other.fData4, sizeof(fData4)) != 0);
}

void plUuid::read(hsStream* S)
{
    fData1 = S->readInt();
    fData2 = S->readShort();
    fData3 = S->readShort();
    S->read(8, fData4);
}

void plUuid::read(const unsigned char* buffer)
{
    memcpy(&fData1, buffer,     sizeof(fData1));
    memcpy(&fData2, buffer + 4, sizeof(fData2));
    memcpy(&fData3, buffer + 6, sizeof(fData3));
    memcpy(fData4,  buffer + 8, sizeof(fData4));
}

void plUuid::write(hsStream* S) const
{
    S->writeInt(fData1);
    S->writeShort(fData2);
    S->writeShort(fData3);
    S->write(8, fData4);
}

void plUuid::write(unsigned char* buffer) const
{
    memcpy(buffer,     &fData1, sizeof(fData1));
    memcpy(buffer + 4, &fData2, sizeof(fData2));
    memcpy(buffer + 6, &fData3, sizeof(fData3));
    memcpy(buffer + 8, fData4,  sizeof(fData4));
}

void plUuid::prcWrite(pfPrcHelper* prc)
{
    prc->startTag("plUuid");
    prc->writeParam("value", toString());
    prc->endTag(true);
}

void plUuid::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() == "plUuid" || tag->getName() == "plUUID") {
        fromString(tag->getParam("value", "00000000-0000-0000-0000-000000000000"));
        return;
    }
    throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
}

void plUuid::clear()
{
    fData1 = 0;
    fData2 = 0;
    fData3 = 0;
    memset(fData4, 0, sizeof(fData4));
}

ST::string plUuid::toString() const
{
    return ST::format("{_08x}-{_04x}-{_04x}-{_02x}{_02x}-{_02x}{_02x}{_02x}{_02x}{_02x}{_02x}",
                      fData1, fData2, fData3,
                      fData4[0], fData4[1], fData4[2], fData4[3],
                      fData4[4], fData4[5], fData4[6], fData4[7]);
}

void plUuid::fromString(const ST::string& str)
{
    if (str.size() != 36 || str[8] != '-' || str[13] != '-' ||
                            str[18] != '-' || str[23] != '-')
        throw hsBadParamException(__FILE__, __LINE__, "Incorrect Uuid format");

    fData1 = str.substr(0, 8).to_uint(16);
    fData2 = str.substr(9, 4).to_uint(16);
    fData3 = str.substr(14, 4).to_uint(16);
    fData4[0] = str.substr(19, 2).to_uint(16);
    fData4[1] = str.substr(21, 2).to_uint(16);
    fData4[2] = str.substr(24, 2).to_uint(16);
    fData4[3] = str.substr(26, 2).to_uint(16);
    fData4[4] = str.substr(28, 2).to_uint(16);
    fData4[5] = str.substr(30, 2).to_uint(16);
    fData4[6] = str.substr(32, 2).to_uint(16);
    fData4[7] = str.substr(34, 2).to_uint(16);
}
