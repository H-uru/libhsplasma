#ifndef _PLICICLE_H
#define _PLICICLE_H

#include "../plPipeline/plGBufferGroup.h"
#include "plVertexSpan.h"

class plIcicle : public plVertexSpan {
public:
    unsigned int IBufferIdx, IStartIdx, ILength, IPackedIdx;
    plGBufferTriangle* sortData;

public:
    plIcicle();
    virtual ~plIcicle();

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
};


class plParticleSpan : public plIcicle {
protected:
    //plParticleEmitter* source;
    unsigned int numParticles, sortCount, srcSpanIdx;
    //plParticleSet* parentSet;
    
public:
    virtual void read(hsStream* S);
    virtual void write(hsStream* S);

    void setSrcSpanIdx(unsigned int idx);
};

#endif
