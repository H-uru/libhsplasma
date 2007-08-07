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
    static hsMatrix44 TranslateMat(hsVector3& translate);
    static hsMatrix44 RotateMat(int axis, float angle);
    static hsMatrix44 ScaleMat(hsVector3& scale);

    void Reset();
    bool IsIdentity();
    
    float& operator()(int y, int x);
    //hsMatrix44& operator=(const hsMatrix44& other);
    bool operator==(const hsMatrix44& other);

    hsMatrix44 operator*(const hsMatrix44& right);
    hsPoint3 operator*(const hsPoint3& pt);
    hsVector3 operator*(const hsVector3& vec);
    
    hsMatrix44& translate(hsVector3& translate);
    hsMatrix44& rotate(int axis, float angle);
    hsMatrix44& scale(hsVector3& scale);
    hsMatrix44& setTranslate(hsVector3& translate);
    hsMatrix44& setRotate(int axis, float angle);
    hsMatrix44& setScale(hsVector3& scale);
    
    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);

    const char* toString();
};

#endif
