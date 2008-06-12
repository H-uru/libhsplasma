#ifndef _PLPXPHYSICAL_H
#define _PLPXPHYSICAL_H

#include "plPhysical.h"
#include "Math/hsGeometry3.h"
#include "Math/hsQuat.h"
#include "Util/hsBitVector.h"

DllClass plPXPhysical : public plPhysical {
protected:
    float fMass, fFriction, fRestitution;
    plSimDefs::Bounds fBounds;
    plSimDefs::Group fGroup;
    unsigned int fReportsOn;
    plKey fObjectKey, fSceneNode, fWorldKey;
    float fSphereRadius;
    hsVector3 fSphereOffset;
    hsVector3 fBoxDimensions, fBoxOffset;
    
    unsigned short fLOSDBs;
    hsVector3 fPos;
    hsQuat fRot;
    hsBitVector fProps;
    plKey fSndGroup;
    size_t fNumVerts, fNumTris;
    hsVector3* fVerts;
    unsigned int* fIndices;
    unsigned int* fTMDBuffer;

    void SetFlagNames();

public:
    plPXPhysical();
    plPXPhysical(const plPXPhysical& init);
    virtual ~plPXPhysical();

    DECLARE_CREATABLE(plPXPhysical)

    virtual class plHKPhysical* ConvertToHavok() const;
    virtual class plPXPhysical* ConvertToPhysX() const;
    virtual class plODEPhysical* ConvertToODE() const;

    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

protected:
    virtual void readData(hsStream* S, plResManager* mgr);
    virtual void writeData(hsStream* S, plResManager* mgr);

private:
    friend class plHKPhysical;
    friend class plODEPhysical;
};

#endif
