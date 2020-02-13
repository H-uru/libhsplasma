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

class PLASMA_DLL plSimulationMsg : public plMessage
{
    CREATABLE(plSimulationMsg, kSimulationMsg, plMessage)
};


class PLASMA_DLL plSimStateMsg : public plSimulationMsg
{
    CREATABLE(plSimStateMsg, kSimStateMsg, plSimulationMsg)
};


class PLASMA_DLL plSimSuppressMsg : public plSimStateMsg
{
    CREATABLE(plSimSuppressMsg, kSimSuppressMsg, plSimStateMsg)

protected:
    bool fSuppress;

public:
    plSimSuppressMsg() : fSuppress() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    bool getSuppress() const { return fSuppress; }
    void setSuppress(bool value) { fSuppress = value; }
};


class PLASMA_DLL plSubWorldMsg : public plSimulationMsg
{
    CREATABLE(plSubWorldMsg, kSubWorldMsg, plSimulationMsg)

protected:
    plKey fWorldKey;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plKey getWorldKey() const { return fWorldKey; }
    void setWorldKey(plKey worldKey) { fWorldKey = std::move(worldKey); }
};

#endif
