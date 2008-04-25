#ifndef _PLMORPHDELTA_H
#define _PLMORPHDELTA_H

#include "NucleusLib/pnFactory/plCreatable.h"
#include "CoreLib/hsTArray.hpp"
#include "CoreLib/hsGeometry3.h"

DllClass plVertDelta {
public:
    unsigned short fIdx, fPadding;
    hsVector3 fPos, fNorm;

public:
    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
};

DllClass plMorphSpan {
public:
    hsTArray<plVertDelta> fDeltas;
    unsigned short fNumUVWChans;
    hsVector3* fUVWs;

public:
    plMorphSpan();
    ~plMorphSpan();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
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

private:
    void allocDeltas(int iSpan, int nDel, int nUVW);
};

#endif
