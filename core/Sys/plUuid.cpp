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

static const unsigned char nullDat4[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
const plUuid NullUuid(0, 0, 0, nullDat4);

plUuid::plUuid() : fData1(0), fData2(0), fData3(0) {
    memset(fData4, 0, sizeof(fData4));
}

plUuid::plUuid(unsigned int data1, unsigned short data2, unsigned short data3,
               const unsigned char* data4)
      : fData1(data1), fData2(data2), fData3(data3) {
    memcpy(fData4, data4, sizeof(fData4));
}

plUuid& plUuid::operator=(const plUuid& init) {
    fData1 = init.fData1;
    fData2 = init.fData2;
    fData3 = init.fData3;
    memcpy(fData4, init.fData4, sizeof(fData4));
    return *this;
}

bool plUuid::operator==(const plUuid& other) const {
    if (fData1 != other.fData1 || fData2 != other.fData2 || fData3 != other.fData3)
        return false;
    return (memcmp(fData4, other.fData4, sizeof(fData4)) == 0);
}

bool plUuid::operator!=(const plUuid& other) const {
    if (fData1 == other.fData1 || fData2 == other.fData2 || fData3 == other.fData3)
        return false;
    return (memcmp(fData4, other.fData4, sizeof(fData4)) != 0);
}

void plUuid::read(hsStream* S) {
    fData1 = S->readInt();
    fData2 = S->readShort();
    fData3 = S->readShort();
    S->read(8, fData4);
}

void plUuid::read(const unsigned char* buffer) {
    fData1 = *(unsigned int*  )(buffer    );
    fData2 = *(unsigned short*)(buffer + 4);
    fData3 = *(unsigned short*)(buffer + 6);
    memcpy(fData4, buffer + 8, 8);
}

void plUuid::write(hsStream* S) {
    S->writeInt(fData1);
    S->writeShort(fData2);
    S->writeShort(fData3);
    S->write(8, fData4);
}

void plUuid::write(unsigned char* buffer) const {
    *(unsigned int*  )(buffer    ) = fData1;
    *(unsigned short*)(buffer + 4) = fData2;
    *(unsigned short*)(buffer + 6) = fData3;
    memcpy(buffer + 8, fData4, 8);
}

void plUuid::prcWrite(pfPrcHelper* prc) {
    prc->startTag("plUuid");
    prc->writeParam("value", toString());
    prc->endTag(true);
}

void plUuid::prcParse(const pfPrcTag* tag) {
    if (tag->getName() == "plUuid" || tag->getName() == "plUUID") {
        fromString(tag->getParam("value", "00000000-0000-0000-0000-000000000000"));
        return;
    }
    throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
}

void plUuid::clear() {
    fData1 = 0;
    fData2 = 0;
    fData3 = 0;
    memset(fData4, 0, sizeof(fData4));
}

bool plUuid::isNull() const {
    return operator==(NullUuid);
}

plString plUuid::toString() const {
    return plString::Format("%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
                            fData1, fData2, fData3,
                            fData4[0], fData4[1], fData4[2], fData4[3],
                            fData4[4], fData4[5], fData4[6], fData4[7]);
}

void plUuid::fromString(const plString& str) {
    if (str.len() != 36 || str[8] != '-' || str[13] != '-' ||
                           str[18] != '-' || str[23] != '-')
        throw hsBadParamException(__FILE__, __LINE__, "Incorrect Uuid format");

    fData1 = str.mid(0, 8).toUint(16);
    fData2 = str.mid(9, 4).toUint(16);
    fData3 = str.mid(14, 4).toUint(16);
    fData4[0] = str.mid(19, 2).toUint(16);
    fData4[1] = str.mid(21, 2).toUint(16);
    fData4[2] = str.mid(24, 2).toUint(16);
    fData4[3] = str.mid(26, 2).toUint(16);
    fData4[4] = str.mid(28, 2).toUint(16);
    fData4[5] = str.mid(30, 2).toUint(16);
    fData4[6] = str.mid(32, 2).toUint(16);
    fData4[7] = str.mid(34, 2).toUint(16);
}
