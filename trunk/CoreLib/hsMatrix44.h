#ifndef _HSMATRIX44_H
#define _HSMATRIX44_H

#include "hsStream.h"
#include "hsGeometry3.h"
#include "../FeatureLib/pfPRC/pfPrcHelper.h"

struct hsMatrix44 {
public:
    enum { kRight, kUp, kView };  // Axes

private:
    float data[4][4];

public:
    /*
    hsMatrix44();
    hsMatrix44(hsMatrix44& init);
    ~hsMatrix44();
    */
    
    static hsMatrix44 IdentityMat();
    static hsMatrix44 TranslateMat(const hsVector3& translate);
    static hsMatrix44 RotateMat(int axis, float angle);
    static hsMatrix44 ScaleMat(const hsVector3& scale);

    void Reset();
    bool IsIdentity() const;
    
    float& operator()(int y, int x);
    //hsMatrix44& operator=(const hsMatrix44& other);
    bool operator==(const hsMatrix44& other) const;

    hsMatrix44 operator*(const hsMatrix44& right) const;
    hsPoint3 operator*(const hsPoint3& pt) const;
    hsVector3 operator*(const hsVector3& vec) const;
    
    hsMatrix44& translate(const hsVector3& translate);
    hsMatrix44& rotate(int axis, float angle);
    hsMatrix44& scale(const hsVector3& scale);
    hsMatrix44& setTranslate(const hsVector3& translate);
    hsMatrix44& setRotate(int axis, float angle);
    hsMatrix44& setScale(const hsVector3& scale);
    
    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);

    plString toString() const;
};

#endif
