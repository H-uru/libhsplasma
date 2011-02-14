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

#ifndef _PLAVATARMSG_H
#define _PLAVATARMSG_H

#include "plMessage.h"

class PLASMA_DLL plAvatarMsg : public plMessage {
    CREATABLE(plAvatarMsg, kAvatarMsg, plMessage)
};


class PLASMA_DLL plArmatureUpdateMsg : public plAvatarMsg {
    CREATABLE(plArmatureUpdateMsg, kArmatureUpdateMsg, plAvatarMsg)

public:
    plArmatureUpdateMsg();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


class PLASMA_DLL plAvatarSetTypeMsg : public plAvatarMsg {
    CREATABLE(plAvatarSetTypeMsg, kAvatarSetTypeMsg, plAvatarMsg)

private:
    bool fIsPlayer;

public:
    plAvatarSetTypeMsg();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


class PLASMA_DLL plAvatarStealthModeMsg : public plAvatarMsg {
    CREATABLE(plAvatarStealthModeMsg, kAvatarStealthModeMsg, plAvatarMsg)

public:
    plAvatarStealthModeMsg();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


class PLASMA_DLL plAvBrainGenericMsg : public plAvatarMsg {
    CREATABLE(plAvBrainGenericMsg, kAvBrainGenericMsg, plAvatarMsg)

public:
    enum Type {
        kNextStage, kPrevStage, kGotoStage, kSetLoopCount
    };

private:
    unsigned int fType, fWhichStage;
    bool fSetTime, fSetDirection, fNewDirection;
    float fNewTime, fTransitionTime;

public:
    plAvBrainGenericMsg();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


class PLASMA_DLL plAvTaskSeekDoneMsg : public plAvatarMsg {
    CREATABLE(plAvTaskSeekDoneMsg, kAvTaskSeekDoneMsg, plAvatarMsg)

private:
    bool fAborted;

public:
    plAvTaskSeekDoneMsg();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
