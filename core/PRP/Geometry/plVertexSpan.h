#ifndef _PLVERTEXSPAN_H
#define _PLVERTEXSPAN_H

#include "plSpan.h"

DllClass plVertexSpan : public plSpan {
public:
    unsigned int fGroupIdx, fVBufferIdx, fCellIdx,
                 fCellOffset, fVStartIdx, fVLength;

public:
    virtual const char* ClassName() const { return "plVertexSpan"; }

    plVertexSpan();
    plVertexSpan(const plVertexSpan& init);

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag);

public:
    unsigned int getGroupIdx() const { return fGroupIdx; }
    unsigned int getVBufferIdx() const { return fVBufferIdx; }
    unsigned int getCellIdx() const { return fCellIdx; }
    unsigned int getCellOffset() const { return fCellOffset; }
    unsigned int getVStartIdx() const { return fVStartIdx; }
    unsigned int getVLength() const { return fVLength; }

    void setGroupIdx(unsigned int idx) { fGroupIdx = idx; }
    void setVBufferIdx(unsigned int idx) { fVBufferIdx = idx; }
    void setCellIdx(unsigned int idx) { fCellIdx = idx; }
    void setCellOffset(unsigned int off) { fCellOffset = off; }
    void setVStartIdx(unsigned int idx) { fVStartIdx = idx; }
    void setVLength(unsigned int len) { fVLength = len; }
};

#endif
