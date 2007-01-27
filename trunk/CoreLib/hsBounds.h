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
//    hsBounds3Ext();
//    virtual ~hsBounds3Ext();
public:
    virtual void read(hsStream *S);
    virtual void write(hsStream *S);
protected:
	unsigned long fExtFlags; //this+0x30
	struct hsPoint3 fCorner; //this+0x34
	struct hsVector3 fAxes[3]; //this+0x40
	struct hsFloatPoint2 fDists[3]; //this+0x64
	float fRadius; //this+0x7c

public:
	hsBounds3Ext(const class hsBounds3Ext &);
	hsBounds3Ext(const class hsBounds3 &);
	hsBounds3Ext();
	 hsBounds3Ext & operator=(const class hsBounds3 &);
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
	void Read(class hsStream *);
	void Write(class hsStream *);

private:

protected:
	unsigned long  IAxisIsZero(unsigned long);
	void  IMakeSphere();
	void  IMakeDists();
	void  IMakeMinsMaxs();

};

#endif

