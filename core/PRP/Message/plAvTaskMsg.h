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

class PLASMA_DLL plAvTaskMsg : public plAvatarMsg
{
    CREATABLE(plAvTaskMsg, kAvTaskMsg, plAvatarMsg)

private:
    plAvTask* fTask;

public:
    plAvTaskMsg() : fTask() { }
    ~plAvTaskMsg();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plAvTask* getTask() const { return fTask; }
    void setTask(plAvTask* task);
};


class PLASMA_DLL plAvPushBrainMsg : public plAvTaskMsg
{
    CREATABLE(plAvPushBrainMsg, kAvPushBrainMsg, plAvTaskMsg)

private:
    plArmatureBrain* fBrain;

public:
    plAvPushBrainMsg() : fBrain() { }
    ~plAvPushBrainMsg();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plArmatureBrain* getBrain() const { return fBrain; }
    void setBrain(plArmatureBrain* brain);
};


class PLASMA_DLL plAvPopBrainMsg : public plAvTaskMsg
{
    CREATABLE(plAvPopBrainMsg, kAvPopBrainMsg, plAvTaskMsg)
};

#endif
