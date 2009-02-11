#ifndef _HSBOUNDS_H
#define _HSBOUNDS_H

#include "Math/hsGeometry3.h"

DllClass hsBounds {
protected:
    int fType;

public:
    hsBounds();
    hsBounds(const hsBounds&);
    virtual ~hsBounds();
    
    virtual const char* ClassName();

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag);

public:
    int getType() const;
    void setType(int type);
};

DllClass hsBounds3 : public hsBounds {
public:
    enum {
        kCenterValid = 0x1,
        kIsSphere = 0x2
    };

protected:
    hsVector3 fMins, fMaxs, fCenter;

public:
    hsBounds3();
    hsBounds3(const hsBounds3&);
    virtual ~hsBounds3();

    virtual const char* ClassName();

    void init(const hsVector3& right);
    hsBounds3 operator+(const hsBounds3& right) const;
    hsBounds3& operator+=(const hsBounds3& right);
    hsBounds3& operator+=(const hsVector3& point);

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag);

public:
    hsVector3 getMins() const;
    hsVector3 getMaxs() const;
    hsVector3 getCenter() const;
    void setMins(const hsVector3& mins);
    void setMaxs(const hsVector3& maxs);
    void setCenter(const hsVector3& center);

    const hsVector3& updateCenter();
};

DllClass hsBounds3Ext : public hsBounds3 {
public:
    enum {
        kAxisAligned = 0x1,
        kSphereSet = 0x2,
        kDistsSet = 0x4,
        kAxisZeroZero = 0x100000,
        kAxisOneZero = 0x200000,
        kAxisTwoZero = 0x400000
    };

protected:
    unsigned int fExtFlags;
    hsVector3 fCorner;
    hsVector3 fAxes[3];
    hsFloatPoint2 fDists[3];
    float fRadius;

public:
    hsBounds3Ext();
    hsBounds3Ext(const hsBounds3Ext&);
    virtual ~hsBounds3Ext();

    virtual const char* ClassName();

    hsBounds3Ext operator+(const hsBounds3Ext& right) const;

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag);

public:
    unsigned int getFlags() const;
    hsVector3 getCorner() const;
    hsVector3 getAxis(size_t idx) const;
    hsFloatPoint2 getDist(size_t idx) const;
    float getRadius() const;

    void setFlags(unsigned int flags);
    void setCorner(const hsVector3& corner);
    void setAxis(size_t idx, const hsVector3& ax);
    void setDist(size_t idx, const hsFloatPoint2& dist);
    void setRadius(float rad);
};

DllClass hsBoundsOriented : public hsBounds {
protected:
    unsigned int fCenterValid;
    hsVector3 fCenter;
    hsPlane3* fPlanes;
    unsigned int fNumPlanes;

public:
    hsBoundsOriented();
    hsBoundsOriented(const hsBoundsOriented&);
    virtual ~hsBoundsOriented();
    
    virtual const char* ClassName();

    void read(hsStream* S);
    void write(hsStream* S);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag);

public:
    unsigned int getCenterValid() const;
    hsVector3 getCenter() const;
    const hsPlane3* getPlanes() const;
    unsigned int getNumPlanes() const;

    void setCenterValid(unsigned int valid);
    void setCenter(const hsVector3& center);
    void setPlanes(unsigned int numPlanes, const hsPlane3* planes);
};

#endif

