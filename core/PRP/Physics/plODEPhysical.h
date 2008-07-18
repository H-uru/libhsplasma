#ifndef _PLODEPHYSICAL_H
#define _PLODEPHYSICAL_H

#include "plPhysical.h"
#include "Math/hsGeometry3.h"

DllClass plODEPhysical : public plPhysical {
protected:
    plSimDefs::Bounds fBounds;
    unsigned int fCategory;
    unsigned short fLOSDBs;
    plKey fObjectKey, fSceneNode;
    unsigned int fUnk1, fUnk2;
    unsigned int fFlags;
    
    hsVector3 fBoxDimensions;
    float fMass, fRadius, fLength;
    size_t fNumVerts, fNumTris, fTMDSize;
    hsVector3* fVerts;
    unsigned int* fIndices;
    unsigned char* fTMDBuffer;

public:
    plODEPhysical();
    plODEPhysical(const plODEPhysical& init);
    virtual ~plODEPhysical();

    DECLARE_CREATABLE(plODEPhysical)

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
    friend class plPXPhysical;
};

#endif
