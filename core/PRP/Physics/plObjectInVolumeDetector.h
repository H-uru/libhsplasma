#ifndef _PLOBJECTINVOLUMEDETECTOR_H
#define _PLOBJECTINVOLUMEDETECTOR_H

#include "plCollisionDetector.h"
#include "PRP/Message/plCameraMsg.h"

DllClass plObjectInVolumeDetector : public plCollisionDetector {
public:
    plObjectInVolumeDetector();
    virtual ~plObjectInVolumeDetector();

    DECLARE_CREATABLE(plObjectInVolumeDetector)
};

DllClass plCameraRegionDetector : public plObjectInVolumeDetector {
protected:
    hsTArray<plCameraMsg*> fMessages;

public:
    plCameraRegionDetector();
    virtual ~plCameraRegionDetector();

    DECLARE_CREATABLE(plCameraRegionDetector)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    void clearMessages();
};

DllClass plObjectInVolumeAndFacingDetector : public plObjectInVolumeDetector {
protected:
    float fFacingTolerance;
    bool fNeedWalkingForward;

public:
    plObjectInVolumeAndFacingDetector();
    virtual ~plObjectInVolumeAndFacingDetector();

    DECLARE_CREATABLE(plObjectInVolumeAndFacingDetector)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
