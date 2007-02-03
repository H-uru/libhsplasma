#ifndef _PLVERTEXSPAN_H
#define _PLVERTEXSPAN_H

#include "plSpan.h"

class plVertexSpan : public plSpan {
public:
    unsigned int groupIdx, VBufferIdx, cellIdx, cellOffset, VStartIdx, VLength;

public:
    plVertexSpan();
    virtual ~plVertexSpan();

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
};

#endif
