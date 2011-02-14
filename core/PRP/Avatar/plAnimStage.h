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

#ifndef _PLANIMSTAGE_H
#define _PLANIMSTAGE_H

#include "PRP/plCreatable.h"

class PLASMA_DLL plAnimStage : public plCreatable {
    CREATABLE(plAnimStage, kAnimStage, plCreatable)

public:
    enum NotifyType {
        kNotifyEnter = 0x1,
        kNotifyLoop = 0x2,
        kNotifyAdvance = 0x4,
        kNotifyRegress = 0x8
    };

    enum PlayType { kPlayNone, kPlayKey, kPlayAuto, kPlayMax };

    enum AdvanceType {
        kAdvanceNone, kAdvanceOnMove, kAdvanceAuto, kAdvanceOnAnyKey,
        kAdvanceMax
    };

private:
    PlayType fForwardType, fBackType;
    AdvanceType fAdvanceType, fRegressType;
    plString fAnimName;
    unsigned char fNotify;
    int fLoops;
    bool fDoAdvanceTo, fDoRegressTo;
    unsigned int fAdvanceTo, fRegressTo;

    // Aux Params
    float fLocalTime, fLength;
    int fCurLoop;
    bool fAttached;

public:
    plAnimStage();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

    void readAux(hsStream* S);
    void writeAux(hsStream* S);
    void prcWriteAux(pfPrcHelper* prc);
    void prcParseAux(const pfPrcTag* tag);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    PlayType getForwardType() const { return fForwardType; }
    PlayType getBackType() const { return fBackType; }
    AdvanceType getAdvanceType() const { return fAdvanceType; }
    AdvanceType getRegressType() const { return fRegressType; }
    plString getAnimName() const { return fAnimName; }
    unsigned char getNotify() const { return fNotify; }
    int getLoops() const { return fLoops; }
    bool doAdvanceTo() const { return fDoAdvanceTo; }
    bool doRegressTo() const { return fDoRegressTo; }
    unsigned int getAdvanceTo() const { return fAdvanceTo; }
    unsigned int getRegressTo() const { return fRegressTo; }

    void setForwardType(PlayType fwd) { fForwardType = fwd; }
    void setBackType(PlayType back) { fBackType = back; }
    void setAdvanceType(AdvanceType adv) { fAdvanceType = adv; }
    void setRegressType(AdvanceType reg) { fRegressType = reg; }
    void setAnimName(const plString& name) { fAnimName = name; }
    void setNotify(unsigned char notify) { fNotify = notify; }
    void setLoops(int loops) { fLoops = loops; }

    void setAdvanceTo(bool doAdvance, unsigned int advance = 0)
    { fDoAdvanceTo = doAdvance; fAdvanceTo = advance; }

    void setRegressTo(bool doRegress, unsigned int regress = 0)
    { fDoRegressTo = doRegress; fRegressTo = regress; }

    float getLocalTime() const { return fLocalTime; }
    float getLength() const { return fLength; }
    int getCurLoop() const { return fCurLoop; }
    bool isAttached() const { return fAttached; }

    void setLocalTime(float time) { fLocalTime = time; }
    void setLength(float length) { fLength = length; }
    void setCurLoop(int loop) { fCurLoop = loop; }
    void setAttached(bool att) { fAttached = att; }
};

#endif
