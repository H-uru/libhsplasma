/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PLOBJECTINVOLUMEDETECTOR_H
#define _PLOBJECTINVOLUMEDETECTOR_H

#include "plCollisionDetector.h"
#include "PRP/Message/plCameraMsg.h"

class PLASMA_DLL plObjectInVolumeDetector : public virtual plCollisionDetector {
    CREATABLE(plObjectInVolumeDetector, kObjectInVolumeDetector,
              plCollisionDetector)
};


class PLASMA_DLL plCameraRegionDetector : public virtual plObjectInVolumeDetector {
    CREATABLE(plCameraRegionDetector, kCameraRegionDetector,
              plObjectInVolumeDetector)

protected:
    std::vector<plCameraMsg*> fMessages;

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


class PLASMA_DLL plObjectInVolumeAndFacingDetector : public virtual plObjectInVolumeDetector {
    CREATABLE(plObjectInVolumeAndFacingDetector,
              kObjectInVolumeAndFacingDetector,
              plObjectInVolumeDetector)

protected:
    float fFacingTolerance;
    bool fNeedWalkingForward;

public:
    plObjectInVolumeAndFacingDetector()
        : fFacingTolerance(0.0f), fNeedWalkingForward(false) { }

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    float getFacingTolerance() const { return fFacingTolerance; }
    bool getNeedWalkingForward() const { return fNeedWalkingForward; }

    void setFacingTolerance(float value) { fFacingTolerance = value; }
    void setNeedWalkingForward(bool value) { fNeedWalkingForward = value; }
};

#endif
