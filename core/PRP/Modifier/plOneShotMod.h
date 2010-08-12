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

DllClass plOneShotMod : public virtual plMultiModifier {
    CREATABLE(plOneShotMod, kOneShotMod, plMultiModifier)

protected:
    plString fAnimName;
    bool fDrivable, fReversable, fSmartSeek, fNoSeek;
    float fSeekDuration;

public:
    plOneShotMod();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plString getAnimName() const { return fAnimName; }
    bool isDrivable() const { return fDrivable; }
    bool isReversable() const { return fReversable; }
    bool getSmartSeek() const { return fSmartSeek; }
    bool getNoSeek() const { return fNoSeek; }
    float getSeekDuration() { return fSeekDuration; }

    void setAnimName(const plString& name) { fAnimName = name; }
    void setDrivable(bool drivable) { fDrivable = drivable; }
    void setReversable(bool reversable) { fReversable = reversable; }
    void setSmartSeek(bool smartSeek) { fSmartSeek = smartSeek; }
    void setNoSeek(bool noSeek) { fNoSeek = noSeek; }
    void setSeekDuration(float duration) { fSeekDuration = duration; }
};

#endif
