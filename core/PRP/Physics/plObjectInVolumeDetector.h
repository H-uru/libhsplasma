#ifndef _PLOBJECTINVOLUMEDETECTOR_H
#define _PLOBJECTINVOLUMEDETECTOR_H

#include "plCollisionDetector.h"
#include "PRP/Message/plCameraMsg.h"

DllClass plObjectInVolumeDetector : public plCollisionDetector {
    CREATABLE(plObjectInVolumeDetector, kObjectInVolumeDetector,
              plCollisionDetector)
};


DllClass plCameraRegionDetector : public plObjectInVolumeDetector {
    CREATABLE(plCameraRegionDetector, kCameraRegionDetector,
              plObjectInVolumeDetector)

protected:
    hsTArray<plCameraMsg*> fMessages;

public:
    plCameraRegionDetector() { }
    virtual ~plCameraRegionDetector();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    void clearMessages();
};


DllClass plObjectInVolumeAndFacingDetector : public plObjectInVolumeDetector {
    CREATABLE(plObjectInVolumeAndFacingDetector,
              kObjectInVolumeAndFacingDetector,
              plObjectInVolumeDetector)

protected:
    float fFacingTolerance;
    bool fNeedWalkingForward;

public:
    plObjectInVolumeAndFacingDetector();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
