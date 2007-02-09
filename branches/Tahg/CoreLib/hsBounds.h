#ifndef _HSBOUNDS_H
#define _HSBOUNDS_H

#include "hsStream.h"
#include "hsGeometry3.h"

class hsBounds {
protected:
    int fType;

public:
    hsBounds();
    virtual ~hsBounds();

    virtual void read(hsStream *S);
    virtual void write(hsStream *S);
};

class hsBounds3 : public hsBounds {
public:
    enum {
        kCenterValid = 0x1,
        kIsSphere = 0x2
    };

protected:
    int fBounds3Flags;
    hsPoint3 fMins, fMaxs, fCenter;

public:
    hsBounds3();
    virtual ~hsBounds3();

    virtual void read(hsStream *S);
    virtual void write(hsStream *S);
};

class hsBounds3Ext : public hsBounds3 {
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
    hsPoint3 fCorner;
    hsVector3 fAxes[3];
    hsFloatPoint2 fDists[3];
    float fRadius;

public:
    hsBounds3Ext();
    hsBounds3Ext(const class hsBounds3Ext &);
    hsBounds3Ext(const class hsBounds3 &);
    virtual ~hsBounds3Ext();
    
    virtual void read(hsStream *S);
    virtual void write(hsStream *S);

#ifdef Tahg
public:
	hsBounds3Ext& operator=(const class hsBounds3 &);
	void Reset(int, const struct hsPoint3 *);
	void Reset(const struct hsPoint3 *){}
	void Reset(const class hsBounds3 *);
	void Reset(const class hsBounds3Ext *);
	void Union(const struct hsVector3 *);
	void Union(const class hsBounds3 *);
	void Union(const struct hsPoint3 *);
	void MakeSymmetric(const struct hsPoint3 *);
	void InscribeSphere();
	void Unalign();
	void Transform(const struct hsMatrix44 *);
	void Translate(const struct hsVector3 &);
	float GetRadius();
	void GetAxes(struct hsVector3 *, hsVector3 *, struct hsVector3 *);
	hsPoint3 *  GetCorner(struct hsPoint3 *);
	void GetCorners(struct hsPoint3 *);
	unsigned long ClosestPoint(const hsPoint3 &, struct hsPoint3 &, struct hsPoint3 &);
	unsigned long IsInside(const struct hsPoint3 *);
	void TestPlane(const struct hsPlane3 *, const hsVector3 &, struct hsFloatPoint2 &);
	void TestPlane(const struct hsVector3 &, const hsVector3 &, struct hsFloatPoint2 &);
	void TestPlane(const struct hsVector3 &, hsFloatPoint2 &);
	long TestPoints(int, const struct hsPoint3 *, const struct hsVector3 &);
	long TestPoints(int, const struct hsPoint3 *);
	long TestBound(const class hsBounds3Ext &);
	unsigned long ISectBB(const class hsBounds3Ext &, const struct hsVector3 &, class hsHitInfoExt *);
	unsigned long ISectBB(const class hsBounds3Ext &, const struct hsVector3 &);
	unsigned long ISectABB(const class hsBounds3Ext &, const struct hsVector3 &);
	unsigned long ISectBS(const class hsBounds3Ext &, const struct hsVector3 &);
	long IClosestISect(const class hsBounds3Ext &, const struct hsVector3 &, float *, float *);
	unsigned long ISectBoxBS(const class hsBounds3Ext &, const struct hsVector3 &);
	unsigned long ISectBoxBS(const class hsBounds3Ext &, const struct hsVector3 &, class hsHitInfoExt *);
	unsigned long ISectBSBox(const class hsBounds3Ext &, const struct hsVector3 &, class hsHitInfoExt *);
	unsigned long ISectBSBS(const class hsBounds3Ext &, const struct hsVector3 &, class hsHitInfoExt *);
	unsigned long ISectLine(const struct hsPoint3 *, const struct hsPoint3 *);
	unsigned long ISectCone(const struct hsPoint3 *, const struct hsPoint3 *, float);
	unsigned long ISectRayBS(const struct hsPoint3 &, const struct hsPoint3 &, struct hsPoint3 &);

protected:
	unsigned long  IAxisIsZero(unsigned long);
	void  IMakeSphere();
	void  IMakeDists();
	void  IMakeMinsMaxs();
#endif
};

class hsHitInfoExt {
  float fDepth; //this+0x0
  struct hsVector3 fNormal; //this+0x4
  struct hsVector3 fDelPos; //this+0x10
  const class hsBounds3Ext * fBoxBnd; //this+0x1c
  const class hsBounds3Ext * fOtherBoxBnd; //this+0x20
  const struct hsPoint3 * fRootCenter; //this+0x24

public:
  hsHitInfoExt(const struct hsPoint3 *, const struct hsVector3 &){}
  void hsHitInfoExt::Set(const class hsBounds3Ext *, const class hsBounds3Ext *, const struct hsVector3 &, float){}
  void Set(const class hsBounds3Ext *, const struct hsVector3 *, float){}
};


class hsBoundsOriented : public hsBounds {
protected:
    unsigned int fCenterValid;
    hsPoint3 fCenter;
    hsPlane3* fPlanes;
    unsigned int fNumPlanes;

public:
    hsBoundsOriented();
    ~hsBoundsOriented();

    void read(hsStream* S);
    void write(hsStream* S);
};

#endif

