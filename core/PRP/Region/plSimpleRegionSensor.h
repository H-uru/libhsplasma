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

#ifndef _PLSIMPLEREGIONSENSOR_H
#define _PLSIMPLEREGIONSENSOR_H

#include "PRP/Modifier/plModifier.h"
#include "PRP/Message/plMessage.h"

DllClass plSimpleRegionSensor : public plSingleModifier {
    CREATABLE(plSimpleRegionSensor, kSimpleRegionSensor, plSingleModifier)

protected:
    plMessage* fEnterMsg;
    plMessage* fExitMsg;

public:
    plSimpleRegionSensor();
    virtual ~plSimpleRegionSensor();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    void setEnterMsg(plMessage* msg);
    void setExitMsg(plMessage* msg);
};


DllClass plSwimDetector : public plSimpleRegionSensor {
    CREATABLE(plSwimDetector, kSwimDetector, plSimpleRegionSensor)

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
};


DllClass plAutoWalkRegion : public plSimpleRegionSensor {
    CREATABLE(plAutoWalkRegion, kAutoWalkRegion, plSimpleRegionSensor)

protected:
    unsigned int fUnknown;

public:
    plAutoWalkRegion();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plRidingAnimatedPhysicalDetector : public plSimpleRegionSensor {
    CREATABLE(plRidingAnimatedPhysicalDetector,
              kRidingAnimatedPhysicalDetector,
              plSimpleRegionSensor)
};

#endif
