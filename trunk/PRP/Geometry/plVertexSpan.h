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
    virtual void IPrcParse(const pfPrcTag* tag);

    unsigned int getGroupIdx() const;
    unsigned int getVBufferIdx() const;
    unsigned int getCellIdx() const;
    unsigned int getCellOffset() const;
    unsigned int getVStartIdx() const;
    unsigned int getVLength() const;
};

#endif
