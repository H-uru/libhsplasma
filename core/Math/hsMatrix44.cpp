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

#include <cstdio>
#include <cmath>
#include <cstring>
#include <string_theory/format>
#include "hsMatrix44.h"

#define DATA(y, x) data[y+(x*4)]

hsMatrix44 hsMatrix44::Identity()
{
    static hsMatrix44 idMat;
    static bool idMatInitialized = false;
    if (!idMatInitialized) {
        idMat.Reset();
        idMatInitialized = true;
    }
    return idMat;
}

hsMatrix44 hsMatrix44::TranslateMat(const hsVector3& translate)
{
    hsMatrix44 tMat;
    tMat.setTranslate(translate);
    return tMat;
}

hsMatrix44 hsMatrix44::RotateMat(int axis, float angle)
{
    hsMatrix44 rMat;
    rMat.setRotate(axis, angle);
    return rMat;
}

hsMatrix44 hsMatrix44::ScaleMat(const hsVector3& scale)
{
    hsMatrix44 sMat;
    sMat.setScale(scale);
    return sMat;
}

void hsMatrix44::Reset()
{
    memset(data, 0, sizeof(data));
    DATA(0, 0) = 1.0f;
    DATA(1, 1) = 1.0f;
    DATA(2, 2) = 1.0f;
    DATA(3, 3) = 1.0f;
}

bool hsMatrix44::IsIdentity() const
{
    for (int y=0; y<4; y++)
        for (int x=0; x<4; x++)
            if ((x == y && DATA(y, x) != 1.0) ||
                (x != y && DATA(y, x) != 0.0))
                return false;
    return true;
}

bool hsMatrix44::operator==(const hsMatrix44& other) const
{
    for (int y=0; y<4; y++)
        for (int x=0; x<4; x++)
            if (DATA(y, x) != other.DATA(y, x))
                return false;
    return true;
}

hsMatrix44 hsMatrix44::operator*(const hsMatrix44& right) const
{
    hsMatrix44 result;
    for (int y=0; y<4; y++)
        for (int x=0; x<4; x++)
            result.DATA(y, x) = (DATA(y, 0) * right.DATA(0, x)) +
                                (DATA(y, 1) * right.DATA(1, x)) +
                                (DATA(y, 2) * right.DATA(2, x)) +
                                (DATA(y, 3) * right.DATA(3, x));
    return result;
}

hsVector3 hsMatrix44::multPoint(const hsVector3& point) const
{
    hsVector3 result;
    result.X = (DATA(0, 0) * point.X) + (DATA(0, 1) * point.Y) +
               (DATA(0, 2) * point.Z) +  DATA(0, 3);
    result.Y = (DATA(1, 0) * point.X) + (DATA(1, 1) * point.Y) +
               (DATA(1, 2) * point.Z) +  DATA(1, 3);
    result.Z = (DATA(2, 0) * point.X) + (DATA(2, 1) * point.Y) +
               (DATA(2, 2) * point.Z) +  DATA(2, 3);
    return result;
}

hsVector3 hsMatrix44::multVector(const hsVector3& vec) const
{
    hsVector3 result;
    result.X = (DATA(0, 0) * vec.X) + (DATA(0, 1) * vec.Y) + (DATA(0, 2) * vec.Z);
    result.Y = (DATA(1, 0) * vec.X) + (DATA(1, 1) * vec.Y) + (DATA(1, 2) * vec.Z);
    result.Z = (DATA(2, 0) * vec.X) + (DATA(2, 1) * vec.Y) + (DATA(2, 2) * vec.Z);
    return result;
}

hsMatrix44 hsMatrix44::inverse() const
{
    // This function is intentionally unrolled for performance
    float subDet[4][4];

    subDet[0][0] = DATA(1, 1)*(DATA(2, 2)*DATA(3, 3) - DATA(3, 2)*DATA(2, 3)) -
                   DATA(1, 2)*(DATA(2, 1)*DATA(3, 3) - DATA(3, 1)*DATA(2, 3)) +
                   DATA(1, 3)*(DATA(2, 1)*DATA(3, 2) - DATA(3, 1)*DATA(2, 2));
    subDet[0][1] = DATA(1, 0)*(DATA(2, 2)*DATA(3, 3) - DATA(3, 2)*DATA(2, 3)) -
                   DATA(1, 2)*(DATA(2, 0)*DATA(3, 3) - DATA(3, 0)*DATA(2, 3)) +
                   DATA(1, 3)*(DATA(2, 0)*DATA(3, 2) - DATA(3, 0)*DATA(2, 2));
    subDet[0][2] = DATA(1, 0)*(DATA(2, 1)*DATA(3, 3) - DATA(3, 1)*DATA(2, 3)) -
                   DATA(1, 1)*(DATA(2, 0)*DATA(3, 3) - DATA(3, 0)*DATA(2, 3)) +
                   DATA(1, 3)*(DATA(2, 0)*DATA(3, 1) - DATA(3, 0)*DATA(2, 1));
    subDet[0][3] = DATA(1, 0)*(DATA(2, 1)*DATA(3, 2) - DATA(3, 1)*DATA(2, 2)) -
                   DATA(1, 1)*(DATA(2, 0)*DATA(3, 2) - DATA(3, 0)*DATA(2, 2)) +
                   DATA(1, 2)*(DATA(2, 0)*DATA(3, 1) - DATA(3, 0)*DATA(2, 1));
    subDet[1][0] = DATA(0, 1)*(DATA(2, 2)*DATA(3, 3) - DATA(3, 2)*DATA(2, 3)) -
                   DATA(0, 2)*(DATA(2, 1)*DATA(3, 3) - DATA(3, 1)*DATA(2, 3)) +
                   DATA(0, 3)*(DATA(2, 1)*DATA(3, 2) - DATA(3, 1)*DATA(2, 2));
    subDet[1][1] = DATA(0, 0)*(DATA(2, 2)*DATA(3, 3) - DATA(3, 2)*DATA(2, 3)) -
                   DATA(0, 2)*(DATA(2, 0)*DATA(3, 3) - DATA(3, 0)*DATA(2, 3)) +
                   DATA(0, 3)*(DATA(2, 0)*DATA(3, 2) - DATA(3, 0)*DATA(2, 2));
    subDet[1][2] = DATA(0, 0)*(DATA(2, 1)*DATA(3, 3) - DATA(3, 1)*DATA(2, 3)) -
                   DATA(0, 1)*(DATA(2, 0)*DATA(3, 3) - DATA(3, 0)*DATA(2, 3)) +
                   DATA(0, 3)*(DATA(2, 0)*DATA(3, 1) - DATA(3, 0)*DATA(2, 1));
    subDet[1][3] = DATA(0, 0)*(DATA(2, 1)*DATA(3, 2) - DATA(3, 1)*DATA(2, 2)) -
                   DATA(0, 1)*(DATA(2, 0)*DATA(3, 2) - DATA(3, 0)*DATA(2, 2)) +
                   DATA(0, 2)*(DATA(2, 0)*DATA(3, 1) - DATA(3, 0)*DATA(2, 1));
    subDet[2][0] = DATA(0, 1)*(DATA(1, 2)*DATA(3, 3) - DATA(3, 2)*DATA(1, 3)) -
                   DATA(0, 2)*(DATA(1, 1)*DATA(3, 3) - DATA(3, 1)*DATA(1, 3)) +
                   DATA(0, 3)*(DATA(1, 1)*DATA(3, 2) - DATA(3, 1)*DATA(1, 2));
    subDet[2][1] = DATA(0, 0)*(DATA(1, 2)*DATA(3, 3) - DATA(3, 2)*DATA(1, 3)) -
                   DATA(0, 2)*(DATA(1, 0)*DATA(3, 3) - DATA(3, 0)*DATA(1, 3)) +
                   DATA(0, 3)*(DATA(1, 0)*DATA(3, 2) - DATA(3, 0)*DATA(1, 2));
    subDet[2][2] = DATA(0, 0)*(DATA(1, 1)*DATA(3, 3) - DATA(3, 1)*DATA(1, 3)) -
                   DATA(0, 1)*(DATA(1, 0)*DATA(3, 3) - DATA(3, 0)*DATA(1, 3)) +
                   DATA(0, 3)*(DATA(1, 0)*DATA(3, 1) - DATA(3, 0)*DATA(1, 1));
    subDet[2][3] = DATA(0, 0)*(DATA(1, 1)*DATA(3, 2) - DATA(3, 1)*DATA(1, 2)) -
                   DATA(0, 1)*(DATA(1, 0)*DATA(3, 2) - DATA(3, 0)*DATA(1, 2)) +
                   DATA(0, 2)*(DATA(1, 0)*DATA(3, 1) - DATA(3, 0)*DATA(1, 1));
    subDet[3][0] = DATA(0, 1)*(DATA(1, 2)*DATA(2, 3) - DATA(2, 2)*DATA(1, 3)) -
                   DATA(0, 2)*(DATA(1, 1)*DATA(2, 3) - DATA(2, 1)*DATA(1, 3)) +
                   DATA(0, 3)*(DATA(1, 1)*DATA(2, 2) - DATA(2, 1)*DATA(1, 2));
    subDet[3][1] = DATA(0, 0)*(DATA(1, 2)*DATA(2, 3) - DATA(2, 2)*DATA(1, 3)) -
                   DATA(0, 2)*(DATA(1, 0)*DATA(2, 3) - DATA(2, 0)*DATA(1, 3)) +
                   DATA(0, 3)*(DATA(1, 0)*DATA(2, 2) - DATA(2, 0)*DATA(1, 2));
    subDet[3][2] = DATA(0, 0)*(DATA(1, 1)*DATA(2, 3) - DATA(2, 1)*DATA(1, 3)) -
                   DATA(0, 1)*(DATA(1, 0)*DATA(2, 3) - DATA(2, 0)*DATA(1, 3)) +
                   DATA(0, 3)*(DATA(1, 0)*DATA(2, 1) - DATA(2, 0)*DATA(1, 1));
    subDet[3][3] = DATA(0, 0)*(DATA(1, 1)*DATA(2, 2) - DATA(2, 1)*DATA(1, 2)) -
                   DATA(0, 1)*(DATA(1, 0)*DATA(2, 2) - DATA(2, 0)*DATA(1, 2)) +
                   DATA(0, 2)*(DATA(1, 0)*DATA(2, 1) - DATA(2, 0)*DATA(1, 1));

    float det = DATA(0, 0)*subDet[0][0] - DATA(0, 1)*subDet[0][1] +
                DATA(0, 2)*subDet[0][2] - DATA(0, 3)*subDet[0][3];

    hsMatrix44 result;
    result.DATA(0, 0) = subDet[0][0] / det;
    result.DATA(0, 1) = subDet[1][0] / -det;
    result.DATA(0, 2) = subDet[2][0] / det;
    result.DATA(0, 3) = subDet[3][0] / -det;
    result.DATA(1, 0) = subDet[0][1] / -det;
    result.DATA(1, 1) = subDet[1][1] / det;
    result.DATA(1, 2) = subDet[2][1] / -det;
    result.DATA(1, 3) = subDet[3][1] / det;
    result.DATA(2, 0) = subDet[0][2] / det;
    result.DATA(2, 1) = subDet[1][2] / -det;
    result.DATA(2, 2) = subDet[2][2] / det;
    result.DATA(2, 3) = subDet[3][2] / -det;
    result.DATA(3, 0) = subDet[0][3] / -det;
    result.DATA(3, 1) = subDet[1][3] / det;
    result.DATA(3, 2) = subDet[2][3] / -det;
    result.DATA(3, 3) = subDet[3][3] / det;
    return result;
}

hsMatrix44& hsMatrix44::translate(const hsVector3& translate)
{
    DATA(0, 3) += translate.X;
    DATA(1, 3) += translate.Y;
    DATA(2, 3) += translate.Z;
    return (*this);
}

hsMatrix44& hsMatrix44::rotate(int axis, float angle)
{
    hsMatrix44 rMat = RotateMat(axis, angle);
    (*this) = rMat * (*this);
    return (*this);
}

hsMatrix44& hsMatrix44::scale(const hsVector3& scale)
{
    DATA(0, 0) *= scale.X;
    DATA(0, 1) *= scale.X;
    DATA(0, 2) *= scale.X;
    DATA(0, 3) *= scale.X;
    DATA(1, 0) *= scale.Y;
    DATA(1, 1) *= scale.Y;
    DATA(1, 2) *= scale.Y;
    DATA(1, 3) *= scale.Y;
    DATA(2, 0) *= scale.Z;
    DATA(2, 1) *= scale.Z;
    DATA(2, 2) *= scale.Z;
    DATA(2, 3) *= scale.Z;
    return (*this);
}

hsMatrix44& hsMatrix44::setTranslate(const hsVector3& translate)
{
    DATA(0, 3) = translate.X;
    DATA(1, 3) = translate.Y;
    DATA(2, 3) = translate.Z;
    return (*this);
}

hsMatrix44& hsMatrix44::setRotate(int axis, float angle)
{
    // Note: This is only for rotation around the global axes.
    //   You should get Local-To-World coordinates first before using this
    //   function if you want a local axis rotation.
    int c1, c2;
    switch(axis) {
    case kRight:
        c1 = 1;
        c2 = 2;
        break;
    case kUp:
        c1 = 0;
        c2 = 2;
        break;
    case kView:
        c1 = 0;
        c2 = 1;
        break;
    default:
        throw hsBadParamException(__FILE__, __LINE__);
    }
    DATA(c1, c1) = cos(angle);
    DATA(c2, c2) = cos(angle);
    DATA(c1, c2) = sin(angle);
    DATA(c2, c1) = -sin(angle);
    return (*this);
}

hsMatrix44& hsMatrix44::setScale(const hsVector3& scale)
{
    DATA(0, 0) = scale.X;
    DATA(1, 1) = scale.Y;
    DATA(2, 2) = scale.Z;
    return (*this);
}

void hsMatrix44::read(hsStream* S)
{
    bool hasData = true;
    if (S->getVer().isLive() || S->getVer().isHexIsle())
        hasData = S->readBool();

    if (hasData) {
        for (int y=0; y<4; y++)
            for (int x=0; x<4; x++)
                DATA(y, x) = S->readFloat();
    } else {
        Reset();
    }
}

void hsMatrix44::write(hsStream* S)
{
    bool hasData = true;
    if (S->getVer().isLive() || S->getVer().isHexIsle()) {
        hasData = !IsIdentity();
        S->writeBool(hasData);
    }

    if (hasData) {
        for (int y=0; y<4; y++)
            for (int x=0; x<4; x++)
                S->writeFloat(DATA(y, x));
    }
}

void hsMatrix44::prcWrite(pfPrcHelper* prc)
{
    if (IsIdentity()) {
        prc->startTag("hsMatrix44");
        prc->writeParam("identity", true);
        prc->endTag(true);
    } else {
        prc->writeTagNoBreak("hsMatrix44");
        ST::string buf = ST::format("[{f},{f},{f},{f} ; {f},{f},{f},{f} ; {f},{f},{f},{f} ; {f},{f},{f},{f}]",
            DATA(0, 0), DATA(0, 1), DATA(0, 2), DATA(0, 3),
            DATA(1, 0), DATA(1, 1), DATA(1, 2), DATA(1, 3),
            DATA(2, 0), DATA(2, 1), DATA(2, 2), DATA(2, 3),
            DATA(3, 0), DATA(3, 1), DATA(3, 2), DATA(3, 3));
        prc->directWrite(buf);
        prc->closeTagNoBreak();
    }
}

void hsMatrix44::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != "hsMatrix44")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    if (tag->getParam("identity", "false").to_bool()) {
        Reset();
    } else {
        std::list<ST::string> contents = tag->getContents();
        auto iter = contents.begin();
        if (*iter++ != "[")
            throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix44 Format error");
        DATA(0, 0) = (*iter++).to_float();
        if (*iter++ != ",")
            throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix44 Format error");
        DATA(0, 1) = (*iter++).to_float();
        if (*iter++ != ",")
            throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix44 Format error");
        DATA(0, 2) = (*iter++).to_float();
        if (*iter++ != ",")
            throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix44 Format error");
        DATA(0, 3) = (*iter++).to_float();
        if (*iter++ != ";")
            throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix44 Format error");
        DATA(1, 0) = (*iter++).to_float();
        if (*iter++ != ",")
            throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix44 Format error");
        DATA(1, 1) = (*iter++).to_float();
        if (*iter++ != ",")
            throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix44 Format error");
        DATA(1, 2) = (*iter++).to_float();
        if (*iter++ != ",")
            throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix44 Format error");
        DATA(1, 3) = (*iter++).to_float();
        if (*iter++ != ";")
            throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix44 Format error");
        DATA(2, 0) = (*iter++).to_float();
        if (*iter++ != ",")
            throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix44 Format error");
        DATA(2, 1) = (*iter++).to_float();
        if (*iter++ != ",")
            throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix44 Format error");
        DATA(2, 2) = (*iter++).to_float();
        if (*iter++ != ",")
            throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix44 Format error");
        DATA(2, 3) = (*iter++).to_float();
        if (*iter++ != ";")
            throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix44 Format error");
        DATA(3, 0) = (*iter++).to_float();
        if (*iter++ != ",")
            throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix44 Format error");
        DATA(3, 1) = (*iter++).to_float();
        if (*iter++ != ",")
            throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix44 Format error");
        DATA(3, 2) = (*iter++).to_float();
        if (*iter++ != ",")
            throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix44 Format error");
        DATA(3, 3) = (*iter++).to_float();
        if (*iter++ != "]")
            throw pfPrcParseException(__FILE__, __LINE__, "hsMatrix44 Format error");
    }
}

ST::string hsMatrix44::toString() const
{
    return ST::format("[ {5.1f} {5.1f} {5.1f} {5.1f}\n  {5.1f} {5.1f} {5.1f} {5.1f}\n"
                      "  {5.1f} {5.1f} {5.1f} {5.1f}\n  {5.1f} {5.1f} {5.1f} {5.1f} ]",
        DATA(0, 0), DATA(0, 1), DATA(0, 2), DATA(0, 3),
        DATA(1, 0), DATA(1, 1), DATA(1, 2), DATA(1, 3),
        DATA(2, 0), DATA(2, 1), DATA(2, 2), DATA(2, 3),
        DATA(3, 0), DATA(3, 1), DATA(3, 2), DATA(3, 3));
}
