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

#include "hsMatrix33.h"

void hsMatrix33::Reset() {
    for (int y=0; y<3; y++)
        for (int x=0; x<3; x++)
            data[y][x] = (x == y) ? 1.0f : 0.0f;
}

void hsMatrix33::read(hsStream* S) {
    for (int y=0; y<3; y++)
        for (int x=0; x<3; x++)
            data[y][x] = S->readFloat();
}

void hsMatrix33::write(hsStream* S) {
    for (int y=0; y<3; y++)
        for (int x=0; x<3; x++)
            S->writeFloat(data[y][x]);
}

void hsMatrix33::prcWrite(pfPrcHelper* prc) {
    prc->writeTagNoBreak("hsMatrix33");
    plString buf = plString::Format("[%f,%f,%f ; %f,%f,%f ; %f,%f,%f]",
        data[0][0], data[0][1], data[0][2],
        data[1][0], data[1][1], data[1][2],
        data[2][0], data[2][1], data[2][2]);
    prc->directWrite(buf);
    prc->closeTagNoBreak();
}

void hsMatrix33::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "hsMatrix33")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    std::list<plString> contents = tag->getContents();
    auto iter = contents.begin();
    if (*iter++ != "[")
        throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix33 Format error");
    data[0][0] = (*iter++).toFloat();
    if (*iter++ != ",")
        throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix33 Format error");
    data[0][1] = (*iter++).toFloat();
    if (*iter++ != ",")
        throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix33 Format error");
    data[0][2] = (*iter++).toFloat();
    if (*iter++ != ";")
        throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix33 Format error");
    data[1][0] = (*iter++).toFloat();
    if (*iter++ != ",")
        throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix33 Format error");
    data[1][1] = (*iter++).toFloat();
    if (*iter++ != ",")
        throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix33 Format error");
    data[1][2] = (*iter++).toFloat();
    if (*iter++ != ";")
        throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix33 Format error");
    data[2][0] = (*iter++).toFloat();
    if (*iter++ != ",")
        throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix33 Format error");
    data[2][1] = (*iter++).toFloat();
    if (*iter++ != ",")
        throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix33 Format error");
    data[2][2] = (*iter++).toFloat();
    if (*iter++ != "]")
        throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix33 Format error");
}
