#ifndef _PLVERTEXSPAN_H
#define _PLVERTEXSPAN_H

#include "plSpan.h"

DllClass plVertexSpan : public plSpan {
public:
    unsigned int fGroupIdx, fVBufferIdx, fCellIdx,
                 fCellOffset, fVStartIdx, fVLength;

public:
    plVertexSpan();
    virtual ~plVertexSpan();

    virtual const char* ClassName();

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

#endif
