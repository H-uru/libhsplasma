#ifndef _PLMORPHDATASET_H
#define _PLMORPHDATASET_H

#include "NucleusLib/pnKeyedObject/hsKeyedObject.h"
#include "plMorphArray.h"

DllClass plMorphDataSet : public hsKeyedObject {
protected:
    hsTArray<plMorphArray> fMorphs;

public:
    plMorphDataSet();
    virtual ~plMorphDataSet();

    DECLARE_CREATABLE(plMorphDataSet)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

#endif
