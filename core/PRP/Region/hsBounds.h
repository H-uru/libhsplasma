#ifndef _HSBOUNDS_H
#define _HSBOUNDS_H

#include "Math/hsGeometry3.h"

DllClass hsBounds {
protected:
    int fType;

public:
    virtual const char* ClassName() const { return "hsBounds"; }

    hsBounds();
    hsBounds(const hsBounds&);
    virtual ~hsBounds() { }

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag);

public:
    int getType() const { return fType; }
    void setType(int type) { fType = type; }
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
    virtual const char* ClassName() const { return "hsBounds3"; }

    hsBounds3() { }
    hsBounds3(const hsBounds3&);

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
    hsVector3 getMins() const { return fMins; }
    hsVector3 getMaxs() const { return fMaxs; }
    hsVector3 getCenter() const { return fCenter; }

    void setMins(const hsVector3& mins) { fMins = mins; }
    void setMaxs(const hsVector3& maxs) { fMaxs = maxs; }
    void setCenter(const hsVector3& center) { fCenter = center; }

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
    virtual const char* ClassName() const { return "hsBounds3Ext"; }

    hsBounds3Ext();
    hsBounds3Ext(const hsBounds3Ext&);

    hsBounds3Ext operator+(const hsBounds3Ext& right) const;

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag);

public:
    unsigned int getFlags() const { return fExtFlags; }
    hsVector3 getCorner() const { return fCorner; }
    hsVector3 getAxis(size_t idx) const { return fAxes[idx]; }
    hsFloatPoint2 getDist(size_t idx) const { return fDists[idx]; }
    float getRadius() const { return fRadius; }

    void setFlags(unsigned int flags) { fExtFlags = flags; }
    void setCorner(const hsVector3& corner) { fCorner = corner; }
    void setAxis(size_t idx, const hsVector3& ax) { fAxes[idx] = ax; }
    void setDist(size_t idx, const hsFloatPoint2& dist) { fDists[idx] = dist; }
    void setRadius(float rad) { fRadius = rad; }
};


DllClass hsBoundsOriented : public hsBounds {
protected:
    unsigned int fCenterValid;
    hsVector3 fCenter;
    hsPlane3* fPlanes;
    unsigned int fNumPlanes;

public:
    virtual const char* ClassName() const { return "hsBoundsOriented"; }

    hsBoundsOriented();
    hsBoundsOriented(const hsBoundsOriented&);
    virtual ~hsBoundsOriented();

    void read(hsStream* S);
    void write(hsStream* S);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag);

public:
    unsigned int getCenterValid() const { return fCenterValid; }
    hsVector3 getCenter() const { return fCenter; }
    unsigned int getNumPlanes() const { return fNumPlanes; }
    const hsPlane3* getPlanes() const { return fPlanes; }

    void setCenterValid(unsigned int valid) { fCenterValid = valid; }
    void setCenter(const hsVector3& center) { fCenter = center; }
    void setPlanes(unsigned int numPlanes, const hsPlane3* planes);
};

#endif

