#ifndef _PLMORPHDELTA_H
#define _PLMORPHDELTA_H

#include "PRP/plCreatable.h"
#include "Util/hsTArray.hpp"
#include "Math/hsGeometry3.h"

DllClass plVertDelta {
protected:
    unsigned short fIdx, fPadding;
    hsVector3 fPos, fNorm;

public:
    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
};

DllClass plMorphSpan {
protected:
    hsTArray<plVertDelta> fDeltas;
    unsigned short fNumUVWChans;
    hsVector3* fUVWs;

public:
    plMorphSpan();
    ~plMorphSpan();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
};

DllClass plMorphDelta : public plCreatable {
protected:
    hsTArray<plMorphSpan> fSpans;
    float fWeight;

public:
    plMorphDelta();
    virtual ~plMorphDelta();

    DECLARE_CREATABLE(plMorphDelta)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
