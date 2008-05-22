#ifndef _PLSTEREIZER_H
#define _PLSTEREIZER_H

#include "PRP/Modifier/plModifier.h"
#include "Math/hsGeometry3.h"

DllClass plStereizer : public plSingleModifier {
public:
    enum { kLeftChannel, kHasMaster };

protected:
    float fAmbientDist, fTransition, fMaxSepDist, fMinSepDist, fTanAng;
    hsVector3 fInitPos;

public:
    plStereizer();
    virtual ~plStereizer();

    DECLARE_CREATABLE(plStereizer)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
