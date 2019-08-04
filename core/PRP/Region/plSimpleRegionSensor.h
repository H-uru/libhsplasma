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

class PLASMA_DLL plSimpleRegionSensor : public plSingleModifier
{
    CREATABLE(plSimpleRegionSensor, kSimpleRegionSensor, plSingleModifier)

protected:
    plMessage* fEnterMsg;
    plMessage* fExitMsg;

public:
    plSimpleRegionSensor() : fEnterMsg(), fExitMsg() { }
    ~plSimpleRegionSensor();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plMessage* getEnterMsg() const { return fEnterMsg; }
    plMessage* getExitMsg() const { return fExitMsg; }

    void setEnterMsg(plMessage* msg);
    void setExitMsg(plMessage* msg);
};


class PLASMA_DLL plSwimDetector : public plSimpleRegionSensor
{
    CREATABLE(plSwimDetector, kSwimDetector, plSimpleRegionSensor)

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;
};


class PLASMA_DLL plAutoWalkRegion : public plSimpleRegionSensor
{
    CREATABLE(plAutoWalkRegion, kAutoWalkRegion, plSimpleRegionSensor)

protected:
    unsigned int fUnknown;

public:
    plAutoWalkRegion() : fUnknown() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;
};


class PLASMA_DLL plRidingAnimatedPhysicalDetector : public plSimpleRegionSensor
{
    CREATABLE(plRidingAnimatedPhysicalDetector,
              kRidingAnimatedPhysicalDetector,
              plSimpleRegionSensor)
};

#endif
