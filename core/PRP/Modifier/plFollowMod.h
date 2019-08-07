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

#ifndef _PLFOLLOWMOD_H
#define _PLFOLLOWMOD_H

#include "PRP/Modifier/plModifier.h"

class PLASMA_DLL plFollowMod : public plSingleModifier
{
    CREATABLE(plFollowMod, kFollowMod, plSingleModifier)

public:
    enum plFMFlags
    {
        kPositionX = 0x1,
        kPositionY = 0x2,
        kPositionZ = 0x4,
        kPosition = (kPositionX | kPositionY | kPositionZ),
        kRotate = 0x8,
        kFullTransform = kPosition | kRotate
    };

    enum FollowLeaderType
    {
        kFollowPlayer, kFollowObject, kFollowCamera, kFollowListener
    };

protected:
    FollowLeaderType    fLeaderType;
    uint8_t             fMode;
    plKey               fLeader;

public:
    plFollowMod() :
        fLeaderType(kFollowPlayer), fMode(kPosition) { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    FollowLeaderType getLeaderType() const { return fLeaderType; }
    uint8_t getMode() const { return fMode; }
    plKey getLeader() const { return fLeader; }

    void setLeaderType(FollowLeaderType leaderType)  { fLeaderType = leaderType; }
    void setMode(uint8_t mode) { fMode = mode; }
    void setLeader(plKey obj) { fLeader = std::move(obj); }

};

#endif
