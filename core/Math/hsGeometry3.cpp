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

#include "hsGeometry3.h"
#include <cmath>

/* hsVector3 */
float hsVector3::magnitude() const
{
    return sqrt(X*X + Y*Y + Z*Z);
}

void hsVector3::read(hsStream* S)
{
    X = S->readFloat();
    Y = S->readFloat();
    Z = S->readFloat();
}

void hsVector3::write(hsStream* S)
{
    S->writeFloat(X);
    S->writeFloat(Y);
    S->writeFloat(Z);
}

void hsVector3::prcWrite(pfPrcHelper* prc)
{
    prc->startTag("hsVector3");
    prc->writeParam("X", X);
    prc->writeParam("Y", Y);
    prc->writeParam("Z", Z);
    prc->endTag(true);
}

void hsVector3::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != "hsVector3")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    X = tag->getParam("X", "0").to_float();
    Y = tag->getParam("Y", "0").to_float();
    Z = tag->getParam("Z", "0").to_float();
}

void hsVector3::normalize()
{
    float length = magnitude();
    if (length == 0.f || std::fabs(length - 1.f) < .0001f)
        return;
    X /= length;
    Y /= length;
    Z /= length;
}


/* hsPlane3 */
void hsPlane3::read(hsStream* S)
{
    N.read(S);
    W = S->readFloat();
}

void hsPlane3::write(hsStream* S)
{
    N.write(S);
    S->writeFloat(W);
}

void hsPlane3::prcWrite(pfPrcHelper* prc)
{
    prc->startTag("hsPlane3");
    prc->writeParam("X", N.X);
    prc->writeParam("Y", N.Y);
    prc->writeParam("Z", N.Z);
    prc->writeParam("W", W);
    prc->endTag(true);
}

void hsPlane3::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != "hsPlane3")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    N.X = tag->getParam("X", "0").to_float();
    N.Y = tag->getParam("Y", "0").to_float();
    N.Z = tag->getParam("Z", "0").to_float();
    W = tag->getParam("W", "0").to_float();
}
