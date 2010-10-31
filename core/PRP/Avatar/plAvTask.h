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

#ifndef _PLAVTASK_H
#define _PLAVTASK_H

#include "PRP/plCreatable.h"
#include "plArmatureBrain.h"

DllClass plAvTask : public plCreatable {
    CREATABLE(plAvTask, kAvTask, plCreatable)

public:
    virtual void read(hsStream* S, plResManager* mgr) { }
    virtual void write(hsStream* S, plResManager* mgr) { }

protected:
    virtual void IPrcWrite(pfPrcHelper* prc) { }
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plAvAnimTask : public plAvTask {
    CREATABLE(plAvAnimTask, kAvAnimTask, plAvTask)

private:
    plString fAnimName;
    float fInitialBlend, fTargetBlend;
    float fFadeSpeed, fSetTime;
    bool fStart, fLoop, fAttach;

public:
    plAvAnimTask();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plAvOneShotTask : public plAvTask {
    CREATABLE(plAvOneShotTask, kAvOneShotTask, plAvTask)
};


DllClass plAvOneShotLinkTask : public plAvOneShotTask {
    CREATABLE(plAvOneShotLinkTask, kAvOneShotLinkTask, plAvOneShotTask)

private:
    plString fAnimName, fMarkerName;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plAvSeekTask : public plAvTask {
    CREATABLE(plAvSeekTask, kAvSeekTask, plAvTask)
};


DllClass plAvTaskBrain : public plAvTask {
    CREATABLE(plAvTaskBrain, kAvTaskBrain, plAvTask)

private:
    plArmatureBrain* fBrain;

public:
    plAvTaskBrain();
    virtual ~plAvTaskBrain();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plArmatureBrain* getBrain() const { return fBrain; }
    void setBrain(plArmatureBrain* brain);
};


// Yay redundancy
DllClass plAvTaskSeek : public plAvTask {
    CREATABLE(plAvTaskSeek, kAvTaskSeek, plAvTask)
};

#endif
