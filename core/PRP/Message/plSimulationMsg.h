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

#ifndef _PLSIMULATIONMSG_H
#define _PLSIMULATIONMSG_H

#include "plMessage.h"

DllClass plSimulationMsg : public plMessage {
    CREATABLE(plSimulationMsg, kSimulationMsg, plMessage)
};


DllClass plSimStateMsg : public plSimulationMsg {
    CREATABLE(plSimStateMsg, kSimStateMsg, plSimulationMsg)
};


DllClass plSimSuppressMsg : public plSimStateMsg {
    CREATABLE(plSimSuppressMsg, kSimSuppressMsg, plSimStateMsg)

protected:
    bool fSuppress;

public:
    plSimSuppressMsg();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plSubWorldMsg : public plSimulationMsg {
    CREATABLE(plSubWorldMsg, kSubWorldMsg, plSimulationMsg)

protected:
    plKey fWorldKey;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
