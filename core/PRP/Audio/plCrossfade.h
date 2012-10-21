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

#ifndef _PLCROSSFADE_H
#define _PLCROSSFADE_H

#include "PRP/Modifier/plModifier.h"
#include "PRP/Message/plMessage.h"

class PLASMA_DLL plCrossfade : public virtual plSingleModifier {
    CREATABLE(plCrossfade, kCrossfade, plSingleModifier)

protected:
    unsigned short fFirstIdx, fSecondIdx;
    unsigned int fStartType, fEndType, fFlags;
    bool fRegistered;

public:
    plCrossfade() : fFirstIdx(0), fSecondIdx(0), fStartType(0), fEndType(0),
                    fFlags(0), fRegistered(false) { }
    virtual ~plCrossfade() { }

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    unsigned short getFirstIdx() const { return fFirstIdx; }
    unsigned short getSecondIdx() const { return fSecondIdx; }
    unsigned int getStartType() const { return fStartType; }
    unsigned int getEndType() const { return fEndType; }
    unsigned int getFlags() const { return fFlags; }
    bool isRegistered() const { return fRegistered; }

    void setFirstIdx(unsigned short idx) { fFirstIdx = idx; }
    void setSecondIdx(unsigned short idx) { fSecondIdx = idx; }
    void setStartType(unsigned int type) { fStartType = type; }
    void setEndType(unsigned int type) { fEndType = type; }
    void setFlags(unsigned int flags) { fFlags = flags; }
    void setRegistered(bool registered) { fRegistered = registered; }
};

class PLASMA_DLL plCrossfadeMsg : public plMessage {
    CREATABLE(plCrossfadeMsg, kCrossfadeMsg, plMessage)
};

#endif
