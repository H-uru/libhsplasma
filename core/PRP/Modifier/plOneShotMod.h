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

#ifndef _PLONESHOTMOD_H
#define _PLONESHOTMOD_H

#include "plModifier.h"

class PLASMA_DLL plOneShotMod : public plMultiModifier
{
    CREATABLE(plOneShotMod, kOneShotMod, plMultiModifier)

protected:
    ST::string fAnimName;
    bool fDrivable, fReversable, fSmartSeek, fNoSeek;
    float fSeekDuration;

public:
    plOneShotMod()
        : fDrivable(), fReversable(), fSmartSeek(), fNoSeek(true),
          fSeekDuration() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    ST::string getAnimName() const { return fAnimName; }
    bool isDrivable() const { return fDrivable; }
    bool isReversable() const { return fReversable; }
    bool getSmartSeek() const { return fSmartSeek; }
    bool getNoSeek() const { return fNoSeek; }
    float getSeekDuration() { return fSeekDuration; }

    void setAnimName(const ST::string& name) { fAnimName = name; }
    void setDrivable(bool drivable) { fDrivable = drivable; }
    void setReversable(bool reversable) { fReversable = reversable; }
    void setSmartSeek(bool smartSeek) { fSmartSeek = smartSeek; }
    void setNoSeek(bool noSeek) { fNoSeek = noSeek; }
    void setSeekDuration(float duration) { fSeekDuration = duration; }
};

#endif
