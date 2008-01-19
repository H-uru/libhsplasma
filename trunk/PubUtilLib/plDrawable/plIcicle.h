#ifndef _PLICICLE_H
#define _PLICICLE_H

#include "PubUtilLib/plPipeline/plGBufferGroup.h"
#include "plVertexSpan.h"

class plIcicle : public plVertexSpan {
public:
    unsigned int fIBufferIdx, fIStartIdx, fILength, fIPackedIdx;
    plGBufferTriangle* fSortData;

public:
    plIcicle();
    virtual ~plIcicle();

    virtual const char* ClassName();
    
    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
};


class plParticleSpan : public plIcicle {
protected:
    //plParticleEmitter* fSource;
    unsigned int fNumParticles, fSortCount, fSrcSpanIdx;
    //plParticleSet* fParentSet;
    
public:
    virtual const char* ClassName();

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);

    void setSrcSpanIdx(unsigned int idx);
};

#endif
