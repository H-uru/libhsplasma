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

#ifndef _PLAVTASKMSG_H
#define _PLAVTASKMSG_H

#include "plAvatarMsg.h"
#include "PRP/Avatar/plAvTask.h"

DllClass plAvTaskMsg : public plAvatarMsg {
    CREATABLE(plAvTaskMsg, kAvTaskMsg, plAvatarMsg)

private:
    plAvTask* fTask;

public:
    plAvTaskMsg();
    virtual ~plAvTaskMsg();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plAvTask* getTask() const { return fTask; }
    void setTask(plAvTask* task);
};


DllClass plAvPushBrainMsg : public plAvTaskMsg {
    CREATABLE(plAvPushBrainMsg, kAvPushBrainMsg, plAvTaskMsg)

private:
    plArmatureBrain* fBrain;

public:
    plAvPushBrainMsg();
    virtual ~plAvPushBrainMsg();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plArmatureBrain* getBrain() const { return fBrain; }
    void setBrain(plArmatureBrain* brain);
};


DllClass plAvPopBrainMsg : public plAvTaskMsg {
    CREATABLE(plAvPopBrainMsg, kAvPopBrainMsg, plAvTaskMsg)
};

#endif
