#ifndef _PLICICLE_H
#define _PLICICLE_H

#include "plGBufferGroup.h"
#include "plVertexSpan.h"

DllClass plIcicle : public plVertexSpan {
protected:
    unsigned int fIBufferIdx, fIStartIdx, fILength;
    plGBufferTriangle* fSortData;

public:
    virtual const char* ClassName() const { return "plIcicle"; }

    plIcicle();
    plIcicle(const plIcicle& init);
    virtual ~plIcicle();

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag);

public:
    unsigned int getIBufferIdx() const { return fIBufferIdx; }
    unsigned int getIStartIdx() const { return fIStartIdx; }
    unsigned int getILength() const { return fILength; }
    const plGBufferTriangle* getSortData() const { return fSortData; }

    void setIBufferIdx(unsigned int idx) { fIBufferIdx = idx; }
    void setIStartIdx(unsigned int idx) { fIStartIdx = idx; }
    void setILength(unsigned int len) { fILength = len; }
    void setSortData(const plGBufferTriangle* data);
};

DllClass plParticleSpan : public plIcicle {
public:
    virtual const char* ClassName() const { return "plParticleSpan"; }

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag);
};

#endif
