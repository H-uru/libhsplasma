#ifndef _HSMATRIX44_H
#define _HSMATRIX44_H

#include "hsGeometry3.h"
#include "Stream/pfPrcHelper.h"
#include "Stream/pfPrcParser.h"

// Just remember: http://xkcd.org/184/

DllStruct hsMatrix44 {
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
    const float* glMatrix() const;

    hsMatrix44 operator*(const hsMatrix44& right) const;
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
    void prcParse(const pfPrcTag* tag);

    plString toString() const;

private:
    friend hsVector3 DllExport operator*(const hsVector3& left, const hsMatrix44& right);
};

hsVector3 DllExport operator*(const hsVector3& left, const hsMatrix44& right);

#endif
