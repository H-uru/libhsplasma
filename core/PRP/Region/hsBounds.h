#ifndef _HSBOUNDS_H
#define _HSBOUNDS_H

#include "Math/hsGeometry3.h"

DllClass hsBounds {
protected:
    int fType;

public:
    hsBounds();
    virtual ~hsBounds();
    
    virtual const char* ClassName();

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    virtual void IPrcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
    virtual void IPrcParse(const pfPrcTag* tag);

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
    virtual ~hsBounds3();

    virtual const char* ClassName();
    
    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag);

    hsVector3 getMins() const;
    hsVector3 getMaxs() const;
    hsVector3 getCenter() const;
    void setMins(const hsVector3& mins);
    void setMaxs(const hsVector3& maxs);
    void setCenter(const hsVector3& center);
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
    hsBounds3Ext(const hsBounds3&);
    virtual ~hsBounds3Ext();

    virtual const char* ClassName();
    
    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag);

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
    ~hsBoundsOriented();
    
    virtual const char* ClassName();

    void read(hsStream* S);
    void write(hsStream* S);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag);

    unsigned int getCenterValid() const;
    hsVector3 getCenter() const;
    const hsPlane3* getPlanes() const;
    unsigned int getNumPlanes() const;

    void setCenterValid(unsigned int valid);
    void setCenter(const hsVector3& center);
    void setPlanes(unsigned int numPlanes, const hsPlane3* planes);
};

#endif

