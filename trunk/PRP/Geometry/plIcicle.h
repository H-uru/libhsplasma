#ifndef _PLICICLE_H
#define _PLICICLE_H

#include "plGBufferGroup.h"
#include "plVertexSpan.h"

DllClass plIcicle : public plVertexSpan {
protected:
    unsigned int fIBufferIdx, fIStartIdx, fILength;
    plGBufferTriangle* fSortData;

public:
    plIcicle();
    plIcicle(const plIcicle& init);
    virtual ~plIcicle();

    virtual const char* ClassName();
    
    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag);

    unsigned int getIBufferIdx() const;
    unsigned int getIStartIdx() const;
    unsigned int getILength() const;
};


DllClass plParticleSpan : public plIcicle {
public:
    virtual const char* ClassName();

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag);
};

#endif
