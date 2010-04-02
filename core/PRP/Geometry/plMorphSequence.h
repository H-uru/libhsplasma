#ifndef _PLMORPHSEQUENCE_H
#define _PLMORPHSEQUENCE_H

#include "PRP/Modifier/plModifier.h"
#include "plMorphArray.h"
#include "plSharedMesh.h"

DllClass plMorphSequence : public plSingleModifier {
    CREATABLE(plMorphSequence, kMorphSequence, plSingleModifier)

private:
    hsTArray<plMorphArray> fMorphs;
    hsTArray<plKey> fSharedMeshes;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
