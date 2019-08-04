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

#include "hsColor.h"

/* hsColorRGBA */
const hsColorRGBA hsColorRGBA::kBlack   = hsColorRGBA(0.0f, 0.0f, 0.0f, 1.0f);
const hsColorRGBA hsColorRGBA::kWhite   = hsColorRGBA(1.0f, 1.0f, 1.0f, 1.0f);
const hsColorRGBA hsColorRGBA::kRed     = hsColorRGBA(1.0f, 0.0f, 0.0f, 1.0f);
const hsColorRGBA hsColorRGBA::kGreen   = hsColorRGBA(0.0f, 1.0f, 0.0f, 1.0f);
const hsColorRGBA hsColorRGBA::kBlue    = hsColorRGBA(0.0f, 0.0f, 1.0f, 1.0f);
const hsColorRGBA hsColorRGBA::kYellow  = hsColorRGBA(1.0f, 1.0f, 0.0f, 1.0f);
const hsColorRGBA hsColorRGBA::kMagenta = hsColorRGBA(1.0f, 0.0f, 1.0f, 1.0f);
const hsColorRGBA hsColorRGBA::kCyan    = hsColorRGBA(0.0f, 1.0f, 1.0f, 1.0f);
const hsColorRGBA hsColorRGBA::kGray    = hsColorRGBA(0.5f, 0.5f, 0.5f, 1.0f);
const hsColorRGBA hsColorRGBA::kNone    = hsColorRGBA(0.0f, 0.0f, 0.0f, 0.0f);

void hsColorRGBA::set(float red, float green, float blue, float alpha)
{
    r = red;
    g = green;
    b = blue;
    a = alpha;
}

void hsColorRGBA::set(const hsColorRGBA& init)
{
    r = init.r;
    g = init.g;
    b = init.b;
    a = init.a;
}

bool hsColorRGBA::operator==(const hsColorRGBA& other) const
{
    return (r == other.r) && (g == other.g) && (b == other.b) && (a == other.a);
}

bool hsColorRGBA::operator!=(const hsColorRGBA& other) const
{
    return (r != other.r) || (g != other.g) || (b != other.b) || (a != other.a);
}

void hsColorRGBA::read(hsStream* S)
{
    r = S->readFloat();
    g = S->readFloat();
    b = S->readFloat();
    a = S->readFloat();
}

void hsColorRGBA::write(hsStream* S)
{
    S->writeFloat(r);
    S->writeFloat(g);
    S->writeFloat(b);
    S->writeFloat(a);
}

void hsColorRGBA::readRGB(hsStream* S)
{
    r = S->readFloat();
    g = S->readFloat();
    b = S->readFloat();
    a = 1.0f;
}

void hsColorRGBA::writeRGB(hsStream* S)
{
    S->writeFloat(r);
    S->writeFloat(g);
    S->writeFloat(b);
}

void hsColorRGBA::prcWrite(pfPrcHelper* prc)
{
    prc->startTag("hsColorRGBA");
    prc->writeParam("red", r);
    prc->writeParam("green", g);
    prc->writeParam("blue", b);
    prc->writeParam("alpha", a);
    prc->endTag(true);
}

void hsColorRGBA::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != "hsColorRGBA")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    r = tag->getParam("red", "0").to_float();
    g = tag->getParam("green", "0").to_float();
    b = tag->getParam("blue", "0").to_float();
    a = tag->getParam("alpha", "1").to_float();
}


/* hsColor32 */
bool hsColor32::operator==(const hsColor32& other) const
{
    return (color == other.color);
}

bool hsColor32::operator!=(const hsColor32& other) const
{
    return (color != other.color);
}

void hsColor32::read32(hsStream* S)
{
    color = S->readInt();
}

void hsColor32::write32(hsStream* S)
{
    S->writeInt(color);
}

void hsColor32::readRGB8(hsStream* S)
{
    r = S->readByte();
    g = S->readByte();
    b = S->readByte();
}

void hsColor32::writeRGB8(hsStream* S)
{
    S->writeByte(r);
    S->writeByte(g);
    S->writeByte(b);
}

void hsColor32::readRGBA8(hsStream* S)
{
    r = S->readByte();
    g = S->readByte();
    b = S->readByte();
    a = S->readByte();
}

void hsColor32::writeRGBA8(hsStream* S)
{
    S->writeByte(r);
    S->writeByte(g);
    S->writeByte(b);
    S->writeByte(a);
}

void hsColor32::prcWrite(pfPrcHelper* prc)
{
    prc->startTag("hsColor32");
    prc->writeParamHex("value", color);
    prc->endTag(true);
}

void hsColor32::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != "hsColor32")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    color = tag->getParam("value", "0").to_uint();
}
