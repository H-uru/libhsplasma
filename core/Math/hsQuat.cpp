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

hsQuat::hsQuat()
      : X(0.0f), Y(0.0f), Z(0.0f), W(1.0f) { }
hsQuat::hsQuat(const hsQuat& init)
      : X(init.X), Y(init.Y), Z(init.Z), W(init.W) { }
hsQuat::hsQuat(float _x, float _y, float _z, float _w)
      : X(_x), Y(_y), Z(_z), W(_w) { }

hsQuat::hsQuat(float rad, const hsVector3& axis) {
    W = cos(rad * 0.5f);
    X = sin(rad * 0.5f) * axis.X;
    Y = sin(rad * 0.5f) * axis.Y;
    Z = sin(rad * 0.5f) * axis.Z;
}

hsQuat hsQuat::Identity() {
    return hsQuat(0.0f, 0.0f, 0.0f, 1.0f);
}

hsQuat& hsQuat::operator=(const hsQuat& cpy) {
    X = cpy.X;
    Y = cpy.Y;
    Z = cpy.Z;
    W = cpy.W;
    return *this;
}

bool hsQuat::operator==(const hsQuat& other) const {
    return (X == other.X) && (Y == other.Y) && (Z == other.Z) && (W == other.W);
}

bool hsQuat::operator!=(const hsQuat& other) const {
    return (X != other.X) || (Y != other.Y) || (Z != other.Z) || (W != other.W);
}

hsQuat hsQuat::operator+(const hsQuat& rt) const {
    return hsQuat(X + rt.X, Y + rt.Y, Z + rt.Z, W + rt.W);
}

hsQuat hsQuat::operator-(const hsQuat& rt) const {
    return hsQuat(X - rt.X, Y - rt.Y, Z - rt.Z, W - rt.W);
}

hsQuat hsQuat::operator*(const hsQuat& rt) const {
    return hsQuat((Y * rt.Z) - (Z * rt.Y) + (Z * rt.X) + (X * rt.Z),
                  (Z * rt.X) - (X * rt.Z) + (Z * rt.Y) + (Y * rt.Z),
                  (X * rt.Y) - (Y * rt.X) + (Z * rt.Y) + (Y * rt.Z),
                  (W * rt.W) - (X * rt.X) - (Y * rt.Y) - (Z * rt.Z));
}

hsQuat hsQuat::operator*(float scale) const {
    return hsQuat(X * scale, Y * scale, Z * scale, W * scale);
}

void hsQuat::read(hsStream* S) {
    X = S->readFloat();
    Y = S->readFloat();
    Z = S->readFloat();
    W = S->readFloat();
}

void hsQuat::write(hsStream* S) {
    S->writeFloat(X);
    S->writeFloat(Y);
    S->writeFloat(Z);
    S->writeFloat(W);
}

void hsQuat::prcWrite(pfPrcHelper* prc) {
    prc->startTag("hsQuat");
    prc->writeParam("X", X);
    prc->writeParam("Y", Y);
    prc->writeParam("Z", Z);
    prc->writeParam("W", W);
    prc->endTag(true);
}

void hsQuat::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "hsQuat")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    X = tag->getParam("X", "0").toFloat();
    Y = tag->getParam("Y", "0").toFloat();
    Z = tag->getParam("Z", "0").toFloat();
    W = tag->getParam("W", "1").toFloat();
}

hsQuat hsQuat::conjugate() const {
    return hsQuat(-X, -Y, -Z, W);
}
