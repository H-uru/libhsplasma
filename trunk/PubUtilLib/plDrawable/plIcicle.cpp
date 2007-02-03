#include "plIcicle.h"

/* plIcicle */
plIcicle::plIcicle() { }
plIcicle::~plIcicle() { }

void plIcicle::read(hsStream* S) {
    plVertexSpan::read(S);
    IBufferIdx = S->readInt();
    IPackedIdx = IStartIdx = S->readInt();
    ILength = S->readInt();
    if (props & kPropFacesSortable) {
        sortData = new plGBufferTriangle[ILength*(2/3)];
        for (unsigned int i=0; i<(ILength*(2/3)); i++)
            sortData[i].read(S);
    } else
        sortData = NULL;
}

void plIcicle::write(hsStream* S) {
    plVertexSpan::write(S);
    S->writeInt(IBufferIdx);
    S->writeInt(IStartIdx);
    S->writeInt(ILength);
    if (props & kPropFacesSortable) {
        for (unsigned int i=0; i<(ILength*(2/3)); i++)
            sortData[i].write(S);
    }
}


/* plParticleSpan */
void plParticleSpan::read(hsStream* S) { }
void plParticleSpan::write(hsStream* S) { }

void plParticleSpan::setSrcSpanIdx(unsigned int idx) { srcSpanIdx = idx; }
