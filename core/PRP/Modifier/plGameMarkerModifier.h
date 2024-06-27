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

#ifndef _PLGAMEMARKERMODIFIER_H
#define _PLGAMEMARKERMODIFIER_H

#include "plModifier.h"

class HSPLASMA_EXPORT plGameMarkerModifier : public plSingleModifier
{
    CREATABLE(plGameMarkerModifier, kGameMarkerModifier, plSingleModifier)

private:
    plKey fGreenAnimKey, fRedAnimKey, fOpenAnimKey, fBounceAnimKey;
    unsigned short fPlaceSoundIdx, fHitSoundIdx;

public:
    plGameMarkerModifier() : fPlaceSoundIdx(), fHitSoundIdx() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plKey getGreenAnimKey() const { return fGreenAnimKey; }
    plKey getRedAnimKey() const { return fRedAnimKey; }
    plKey getOpenAnimKey() const { return fOpenAnimKey; }
    plKey getBounceAnimKey() const { return fBounceAnimKey; }
    unsigned short getPlaceSoundIdx() const { return fPlaceSoundIdx; }
    unsigned short getHitSoundIdx() const { return fHitSoundIdx; }

    void setGreenAnimKey(plKey greenAnimKey) { fGreenAnimKey = std::move(greenAnimKey); }
    void setRedAnimKey(plKey redAnimKey) { fRedAnimKey = std::move(redAnimKey); }
    void setOpenAnimKey(plKey openAnimKey) { fOpenAnimKey = std::move(openAnimKey); }
    void setBounceAnimKey(plKey bounceAnimKey) { fBounceAnimKey = std::move(bounceAnimKey); }
    void setPlaceSoundIdx(unsigned short placeSoundIdx) { fPlaceSoundIdx = placeSoundIdx; }
    void setHitSoundIdx(unsigned short hitSoundIdx) { fHitSoundIdx = hitSoundIdx; }
};

#endif
