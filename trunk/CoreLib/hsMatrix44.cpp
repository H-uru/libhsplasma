#include <cstdio>
#include <cmath>
#include "hsMatrix44.h"

/*
hsMatrix44::hsMatrix44() { }
hsMatrix44::hsMatrix44(hsMatrix44& init) {
    memcpy(data, init.data, sizeof(data));
}

hsMatrix44::~hsMatrix44() { }
*/

hsMatrix44 hsMatrix44::IdentityMat() {
    static hsMatrix44 idMat;
    static bool idMatInitialized = false;
    if (!idMatInitialized) {
        idMat.Reset();
        idMatInitialized = true;
    }
    return idMat;
}

hsMatrix44 hsMatrix44::TranslateMat(const hsVector3& translate) {
    hsMatrix44 tMat = IdentityMat();
    tMat.setTranslate(translate);
    return tMat;
}

hsMatrix44 hsMatrix44::RotateMat(int axis, float angle) {
    hsMatrix44 rMat = IdentityMat();
    rMat.setRotate(axis, angle);
    return rMat;
}

hsMatrix44 hsMatrix44::ScaleMat(const hsVector3& scale) {
    hsMatrix44 sMat = IdentityMat();
    sMat.setScale(scale);
    return sMat;
}

void hsMatrix44::Reset() {
    memset(data, 0, sizeof(data));
    data[0][0] = 1.0f;
    data[1][1] = 1.0f;
    data[2][2] = 1.0f;
    data[3][3] = 1.0f;
}

bool hsMatrix44::IsIdentity() const {
    for (int y=0; y<4; y++)
        for (int x=0; x<4; x++)
            if ((x == y && data[y][x] != 1.0) ||
                (x != y && data[y][x] != 0.0))
                return false;
    return true;
}

float& hsMatrix44::operator()(int y, int x) {
    return data[y][x];
}

/*
hsMatrix44& hsMatrix44::operator=(const hsMatrix44& other) {
    for (int y=0; y<4; y++)
        for (int x=0; x<4; x++)
            data[y][x] = other.data[y][x];
    return (*this);
}*/

bool hsMatrix44::operator==(const hsMatrix44& other) const {
    for (int y=0; y<4; y++)
        for (int x=0; x<4; x++)
            if (data[y][x] != other.data[y][x])
                return false;
    return true;
}

hsMatrix44::operator const float*() const {
    static float glmat[16];
    for (int y=0; y<4; y++)
        for (int x=0; x<4; x++)
            glmat[y*4 + x] = data[x][y];
    return glmat;
}

hsMatrix44 hsMatrix44::operator*(const hsMatrix44& right) const {
    hsMatrix44 result;
    for (int y=0; y<4; y++)
        for (int x=0; x<4; x++)
            result.data[y][x] = (data[y][0] * right.data[0][x]) +
                                (data[y][1] * right.data[1][x]) +
                                (data[y][2] * right.data[2][x]) +
                                (data[y][3] * right.data[3][x]);
    return result;
}

hsPoint3 hsMatrix44::operator*(const hsPoint3& pt) const {
    hsPoint3 result;
    result.fX = (data[0][0] * pt.fX) + (data[0][1] * pt.fY) +
                (data[0][2] * pt.fZ) + data[0][3];
    result.fY = (data[1][0] * pt.fX) + (data[1][1] * pt.fY) +
                (data[1][2] * pt.fZ) + data[1][3];
    result.fZ = (data[2][0] * pt.fX) + (data[2][1] * pt.fY) +
                (data[2][2] * pt.fZ) + data[2][3];
    return result;
}

hsVector3 hsMatrix44::operator*(const hsVector3& vec) const {
    hsVector3 result;
    result.fX = (data[0][0] * vec.fX) + (data[0][1] * vec.fY) +
                (data[0][2] * vec.fZ) + data[0][3];
    result.fY = (data[1][0] * vec.fX) + (data[1][1] * vec.fY) +
                (data[1][2] * vec.fZ) + data[1][3];
    result.fZ = (data[2][0] * vec.fX) + (data[2][1] * vec.fY) +
                (data[2][2] * vec.fZ) + data[2][3];
    return result;
}

hsMatrix44& hsMatrix44::translate(const hsVector3& translate) {
    data[0][3] += translate.fX;
    data[1][3] += translate.fY;
    data[2][3] += translate.fZ;
    return (*this);
}

hsMatrix44& hsMatrix44::rotate(int axis, float angle) {
    hsMatrix44 rMat = RotateMat(axis, angle);
    (*this) = rMat * (*this);
    return (*this);
}

hsMatrix44& hsMatrix44::scale(const hsVector3& scale) {
    data[0][0] *= scale.fX;
    data[0][1] *= scale.fX;
    data[0][2] *= scale.fX;
    data[0][3] *= scale.fX;
    data[1][0] *= scale.fY;
    data[1][1] *= scale.fY;
    data[1][2] *= scale.fY;
    data[1][3] *= scale.fY;
    data[2][0] *= scale.fZ;
    data[2][1] *= scale.fZ;
    data[2][2] *= scale.fZ;
    data[2][3] *= scale.fZ;
    return (*this);
}

hsMatrix44& hsMatrix44::setTranslate(const hsVector3& translate) {
    data[0][3] = translate.fX;
    data[1][3] = translate.fY;
    data[2][3] = translate.fZ;
    return (*this);
}

hsMatrix44& hsMatrix44::setRotate(int axis, float angle) {
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
        // Give something invalid so it'll break:
        c1 = -1;
        c2 = -1;
    }
    data[c1][c1] = cos(angle);
    data[c2][c2] = cos(angle);
    data[c1][c2] = sin(angle);
    data[c2][c1] = -sin(angle);
    return (*this);
}

hsMatrix44& hsMatrix44::setScale(const hsVector3& scale) {
    data[0][0] = scale.fX;
    data[1][1] = scale.fY;
    data[2][2] = scale.fZ;
    return (*this);
}

void hsMatrix44::read(hsStream* S) {
    bool hasData = true;
    if (S->getVer() == pvLive)
        hasData = S->readBool();

    if (hasData) {
        for (int y=0; y<4; y++)
            for (int x=0; x<4; x++)
                data[y][x] = S->readFloat();
    } else {
        Reset();
    }
}

void hsMatrix44::write(hsStream* S) {
    bool hasData = true;
    if (S->getVer() == pvLive) {
        hasData = !IsIdentity();
        S->writeBool(hasData);
    }
    
    if (hasData) {
        for (int y=0; y<4; y++)
            for (int x=0; x<4; x++)
                S->writeFloat(data[y][x]);
    }
}

void hsMatrix44::prcWrite(pfPrcHelper* prc) {
    if (IsIdentity()) {
        prc->startTag("hsMatrix44");
        prc->writeParam("identity", true);
        prc->endTag(true);
    } else {
        prc->writeTagNoBreak("hsMatrix44");
        plString buf = plString::Format("[%f,%f,%f,%f ; %f,%f,%f,%f ; %f,%f,%f,%f ; %f,%f,%f,%f]",
            data[0][0], data[0][1], data[0][2], data[0][3],
            data[1][0], data[1][1], data[1][2], data[1][3],
            data[2][0], data[2][1], data[2][2], data[2][3],
            data[3][0], data[3][1], data[3][2], data[3][3]);
        prc->getStream()->writeStr(buf);
        prc->closeTagNoBreak();
    }
}

plString hsMatrix44::toString() const {
    return plString::Format("[ %5.1f %5.1f %5.1f %5.1f\n  %5.1f %5.1f %5.1f %5.1f\n"
                            "%5.1f %5.1f %5.1f %5.1f\n  %5.1f %5.1f %5.1f %5.1f ]",
        data[0][0], data[0][1], data[0][2], data[0][3],
        data[1][0], data[1][1], data[1][2], data[1][3],
        data[2][0], data[2][1], data[2][2], data[2][3],
        data[3][0], data[3][1], data[3][2], data[3][3]);
}
