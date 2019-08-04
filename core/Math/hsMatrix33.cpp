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

#include <cstring>
#include <string_theory/format>

#define DATA(y, x) data[y+(x*3)]

void hsMatrix33::Reset()
{
    memset(data, 0, sizeof(data));
    DATA(0, 0) = 1.0f;
    DATA(1, 1) = 1.0f;
    DATA(2, 2) = 1.0f;
}

void hsMatrix33::read(hsStream* S)
{
    for (int y=0; y<3; y++)
        for (int x=0; x<3; x++)
            DATA(y, x) = S->readFloat();
}

void hsMatrix33::write(hsStream* S)
{
    for (int y=0; y<3; y++)
        for (int x=0; x<3; x++)
            S->writeFloat(DATA(y, x));
}

void hsMatrix33::prcWrite(pfPrcHelper* prc)
{
    prc->writeTagNoBreak("hsMatrix33");
    ST::string buf = ST::format("[{f},{f},{f} ; {f},{f},{f} ; {f},{f},{f}]",
        DATA(0, 0), DATA(0, 1), DATA(0, 2),
        DATA(1, 0), DATA(1, 1), DATA(1, 2),
        DATA(2, 0), DATA(2, 1), DATA(2, 2));
    prc->directWrite(buf);
    prc->closeTagNoBreak();
}

void hsMatrix33::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != "hsMatrix33")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    std::list<ST::string> contents = tag->getContents();
    auto iter = contents.begin();
    if (*iter++ != "[")
        throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix33 Format error");
    DATA(0, 0) = (*iter++).to_float();
    if (*iter++ != ",")
        throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix33 Format error");
    DATA(0, 1) = (*iter++).to_float();
    if (*iter++ != ",")
        throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix33 Format error");
    DATA(0, 2) = (*iter++).to_float();
    if (*iter++ != ";")
        throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix33 Format error");
    DATA(1, 0) = (*iter++).to_float();
    if (*iter++ != ",")
        throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix33 Format error");
    DATA(1, 1) = (*iter++).to_float();
    if (*iter++ != ",")
        throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix33 Format error");
    DATA(1, 2) = (*iter++).to_float();
    if (*iter++ != ";")
        throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix33 Format error");
    DATA(2, 0) = (*iter++).to_float();
    if (*iter++ != ",")
        throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix33 Format error");
    DATA(2, 1) = (*iter++).to_float();
    if (*iter++ != ",")
        throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix33 Format error");
    DATA(2, 2) = (*iter++).to_float();
    if (*iter++ != "]")
        throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix33 Format error");
}
