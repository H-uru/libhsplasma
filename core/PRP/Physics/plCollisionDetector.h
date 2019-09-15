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

#ifndef _PLCOLLISIONDETECTOR_H
#define _PLCOLLISIONDETECTOR_H

#include "plDetectorModifier.h"

class PLASMA_DLL plCollisionDetector : public plDetectorModifier
{
    CREATABLE(plCollisionDetector, kCollisionDetector, plDetectorModifier)

public:
    enum
    {
        kTypeEnter = 0x1,
        kTypeExit = 0x2,
        kTypeAny = 0x4,
        kTypeUnEnter = 0x8,
        kTypeUnExit = 0x10,
        kTypeBump = 0x20
    };

protected:
    unsigned char fType;

public:
    plCollisionDetector() : fType() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    unsigned char getType() const { return fType; }
    void setType(unsigned char type) { fType = type; }
};


class PLASMA_DLL plSubworldRegionDetector : public plCollisionDetector
{
    CREATABLE(plSubworldRegionDetector, kSubworldRegionDetector,
              plCollisionDetector)

protected:
    plKey fSub;
    bool fOnExit;

public:
    plSubworldRegionDetector() : fOnExit() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plKey getSubworld() const { return fSub; }
    bool getOnExit() const { return fOnExit; }

    void setSubworld(plKey subworld) { fSub = std::move(subworld); }
    void setOnExit(bool onExit) { fOnExit = onExit; }
};


class PLASMA_DLL plPanicLinkRegion : public plCollisionDetector
{
    CREATABLE(plPanicLinkRegion, kPanicLinkRegion, plCollisionDetector)

protected:
    bool fPlayLinkOutAnim;

public:
    plPanicLinkRegion() : fPlayLinkOutAnim(true) { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    bool getPlayLinkOutAnim() const { return fPlayLinkOutAnim; }
    void setPlayLinkOutAnim(bool play) { fPlayLinkOutAnim = play; }
};

#endif
