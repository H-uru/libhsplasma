#ifndef _PLICICLE_H
#define _PLICICLE_H

#include "plGBufferGroup.h"
#include "plVertexSpan.h"

class plIcicle : public plVertexSpan {
protected:
    unsigned int fIBufferIdx, fIStartIdx, fILength;
    plGBufferTriangle* fSortData;

public:
    plIcicle();
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


class plParticleSpan : public plIcicle {
protected:
    unsigned int fNumParticles, fSortCount, fSrcSpanIdx;
    
public:
    virtual const char* ClassName();

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag);

    void setSrcSpanIdx(unsigned int idx);
};

#endif
