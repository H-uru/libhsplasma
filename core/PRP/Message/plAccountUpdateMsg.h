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

#ifndef _PLACCOUNTUPDATEMSG_H
#define _PLACCOUNTUPDATEMSG_H

#include "plMessage.h"

class PLASMA_DLL plAccountUpdateMsg : public plMessage
{
    CREATABLE(plAccountUpdateMsg, kAccountUpdateMsg, plMessage)

public:
    enum
    {
        kCreatePlayer = 1, kDeletePlayer, kUpgradePlayer, kActivePlayer,
        kChangePassword
    };

protected:
    unsigned int fUpdateType;
    unsigned int fResult;
    unsigned int fPlayer;

public:
    plAccountUpdateMsg() : fUpdateType(), fResult(), fPlayer() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    unsigned int getUpdateType() { return fUpdateType; }
    unsigned int getResult() { return fResult; }
    unsigned int getPlayer() { return fPlayer; }

    void setUpdateType(unsigned int updateType) { fUpdateType = updateType; }
    void setResult(unsigned int result) { fResult = result; }
    void setPlayer(unsigned int player) { fPlayer = player; }
};

#endif
