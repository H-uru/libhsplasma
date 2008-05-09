#ifndef _PLMORPHARRAY_H
#define _PLMORPHARRAY_H

#include "plMorphDelta.h"

DllClass plMorphArray {
protected:
    hsTArray<plMorphDelta> fDeltas;

public:
    plMorphArray();
    ~plMorphArray();

    void read(hsStream* S, plResManager* mgr);
    void write(hsStream* S, plResManager* mgr);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
