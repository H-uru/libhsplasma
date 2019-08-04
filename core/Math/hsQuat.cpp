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

#include "hsQuat.h"
#include <cmath>

hsQuat::hsQuat(float rad, const hsVector3& axis)
{
    W = cos(rad * 0.5f);
    X = sin(rad * 0.5f) * axis.X;
    Y = sin(rad * 0.5f) * axis.Y;
    Z = sin(rad * 0.5f) * axis.Z;
}

void hsQuat::read(hsStream* S)
{
    X = S->readFloat();
    Y = S->readFloat();
    Z = S->readFloat();
    W = S->readFloat();
}

void hsQuat::write(hsStream* S)
{
    S->writeFloat(X);
    S->writeFloat(Y);
    S->writeFloat(Z);
    S->writeFloat(W);
}

void hsQuat::prcWrite(pfPrcHelper* prc)
{
    prc->startTag("hsQuat");
    prc->writeParam("X", X);
    prc->writeParam("Y", Y);
    prc->writeParam("Z", Z);
    prc->writeParam("W", W);
    prc->endTag(true);
}

void hsQuat::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != "hsQuat")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    X = tag->getParam("X", "0").to_float();
    Y = tag->getParam("Y", "0").to_float();
    Z = tag->getParam("Z", "0").to_float();
    W = tag->getParam("W", "1").to_float();
}
