#ifndef _PLSTEREIZER_H
#define _PLSTEREIZER_H

#include "PRP/Modifier/plModifier.h"
#include "Math/hsGeometry3.h"

DllClass plStereizer : public plSingleModifier {
    CREATABLE(plStereizer, kStereizer, plSingleModifier)

public:
    enum { kLeftChannel, kHasMaster };

protected:
    float fAmbientDist, fTransition, fMaxSepDist, fMinSepDist, fTanAng;
    hsVector3 fInitPos;

public:
    plStereizer();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    float getAmbientDist() const { return fAmbientDist; }
    float getTransition() const { return fTransition; }
    float getMaxSepDist() const { return fMaxSepDist; }
    float getMinSepDist() const { return fMinSepDist; }
    float getTanAng() const { return fTanAng; }
    hsVector3 getInitPos() const { return fInitPos; }

    void setAmbientDist(float dist) { fAmbientDist = dist; }
    void setTransition(float transition) { fTransition = transition; }
    void setSepDist(float min, float max) { fMinSepDist = min; fMaxSepDist = max; }
    void setTanAng(float ang) { fTanAng = ang; }
    void setInitPos(const hsVector3& pos) { fInitPos = pos; }
};

#endif
