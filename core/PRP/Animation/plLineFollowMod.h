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

#ifndef _PLLINEFOLLOWMOD_H
#define _PLLINEFOLLOWMOD_H

#include "PRP/Modifier/plModifier.h"
#include "plAnimPath.h"

class PLASMA_DLL plLineFollowMod : public plMultiModifier
{
    CREATABLE(plLineFollowMod, kLineFollowMod, plMultiModifier)

public:
    enum FollowMode
    {
        kFollowObject, kFollowListener, kFollowCamera, kFollowLocalAvatar
    };

    enum {
        kNone = 0,
        kFullMatrix = 0x1,
        kOffsetFeet = 0x2,
        kOffsetAng = 0x4,
        kOffset = kOffsetFeet | kOffsetAng,
        kOffsetClamp = 0x8,
        kForceToLine = 0x10,
        kSpeedClamp = 0x20,
        kSearchPopPos = 0x40
    };

protected:
    FollowMode fFollowMode;
    unsigned short fFollowFlags;
    plAnimPath* fPath;
    plKey fPathParent, fRefObj;
    std::vector<plKey> fStereizers;
    float fOffset, fOffsetClamp, fSpeedClamp;

public:
    plLineFollowMod()
        : fFollowMode(kFollowObject), fFollowFlags(), fPath(), fOffset(),
          fOffsetClamp(), fSpeedClamp() { }
    ~plLineFollowMod();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    FollowMode getFollowMode() const { return fFollowMode; }
    unsigned short getFollowFlags() const { return fFollowFlags; }
    plAnimPath* getPath() const { return fPath; }
    plKey getPathParent() const { return fPathParent; }
    plKey getRefObj() const { return fRefObj; }
    float getOffset() const { return fOffset; }
    float getOffsetClamp() const { return fOffsetClamp; }
    float getSpeedClamp() const { return fSpeedClamp; }

    void setFollowMode(FollowMode mode) { fFollowMode = mode; }
    void setFollowFlags(unsigned short flags) { fFollowFlags = flags; }
    void setPathParent(plKey parent) { fPathParent = std::move(parent); }
    void setRefObj(plKey obj) { fRefObj = std::move(obj); }
    void setOffset(float offset) { fOffset = offset; }
    void setOffsetClamp(float clamp) { fOffsetClamp = clamp; }
    void setSpeedClamp(float clamp) { fSpeedClamp = clamp; }
    void setPath(plAnimPath* path);

    const std::vector<plKey>& getStereizers() const { return fStereizers; }
    std::vector<plKey>& getStereizers() { return fStereizers; }
    void addStereizer(plKey stereizer) { fStereizers.emplace_back(std::move(stereizer)); }
    void delStereizer(size_t idx) { fStereizers.erase(fStereizers.begin() + idx); }
    void clearStereizers() { fStereizers.clear(); }
};

class PLASMA_DLL plRailCameraMod : public plLineFollowMod
{
    CREATABLE(plRailCameraMod, kRailCameraMod, plLineFollowMod)
};

#endif
