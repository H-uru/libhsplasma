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

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    float getAmbientDist() const;
    float getTransition() const;
    float getMaxSepDist() const;
    float getMinSepDist() const;
    float getTanAng() const;
    hsVector3 getInitPos() const;

    void setAmbientDist(float dist);
    void setTransition(float transition);
    void setSepDist(float min, float max);
    void setTanAng(float ang);
    void setInitPos(const hsVector3& pos);
};

#endif
