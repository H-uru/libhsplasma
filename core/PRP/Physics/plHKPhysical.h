#ifndef _PLHKPHYSICAL_H
#define _PLHKPHYSICAL_H

#include "plPhysical.h"
#include "Math/hsGeometry3.h"
#include "Math/hsQuat.h"
#include "Util/hsBitVector.h"

DllClass plHKPhysical : public plPhysical {
protected:
    hsVector3 fPos;
    hsQuat fRot;
    float fMass, fFriction, fRestitution;
    plSimDefs::Bounds fBounds;
    unsigned int fCategory;
    hsBitVector fProps;
    plKey fObjectKey, fSceneNode, fWorldKey, fSndGroup;
    unsigned int fUnk1, fUnk2;
    bool fBool1, fBool2;
    unsigned short fLOSDBs;

    hsVector3 fSphereOffset;
    float fSphereRadius;
    size_t fNumVerts, fNumTris;
    hsVector3* fVerts;
    unsigned short* fIndices;

    void SetFlagNames();

public:
    plHKPhysical();
    plHKPhysical(const plHKPhysical& init);
    virtual ~plHKPhysical();

    DECLARE_CREATABLE(plHKPhysical)

    virtual class plHKPhysical* ConvertToHavok() const;
    virtual class plPXPhysical* ConvertToPhysX() const;
    virtual class plODEPhysical* ConvertToODE() const;

    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

protected:
    virtual void readData(hsStream* S, plResManager* mgr);
    virtual void writeData(hsStream* S, plResManager* mgr);

private:
    friend class plPXPhysical;
    friend class plODEPhysical;
};

#endif
