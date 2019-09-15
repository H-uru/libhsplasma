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
#include "ResManager/plResManager.h"
#include "plArmatureBrain.h"

class PLASMA_DLL plAvTask : public plCreatable
{
    CREATABLE(plAvTask, kAvTask, plCreatable)

public:
    void read(hsStream* /*S*/, plResManager* /*mgr*/) HS_OVERRIDE { }
    void write(hsStream* /*S*/, plResManager* /*mgr*/) HS_OVERRIDE { }

protected:
    void IPrcWrite(pfPrcHelper* /*prc*/) HS_OVERRIDE { }
};


class PLASMA_DLL plAvAnimTask : public plAvTask
{
    CREATABLE(plAvAnimTask, kAvAnimTask, plAvTask)

private:
    ST::string fAnimName;
    float fInitialBlend, fTargetBlend;
    float fFadeSpeed, fSetTime;
    bool fStart, fLoop, fAttach;

public:
    plAvAnimTask()
        : fInitialBlend(), fTargetBlend(), fFadeSpeed(), fSetTime(),
          fStart(), fLoop(), fAttach() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;
};


class PLASMA_DLL plAvOneShotTask : public plAvTask
{
    CREATABLE(plAvOneShotTask, kAvOneShotTask, plAvTask)
};


class PLASMA_DLL plAvOneShotLinkTask : public plAvOneShotTask
{
    CREATABLE(plAvOneShotLinkTask, kAvOneShotLinkTask, plAvOneShotTask)

private:
    ST::string fAnimName, fMarkerName;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;
};


class PLASMA_DLL plAvSeekTask : public plAvTask
{
    CREATABLE(plAvSeekTask, kAvSeekTask, plAvTask)
};


class PLASMA_DLL plAvTaskBrain : public plAvTask
{
    CREATABLE(plAvTaskBrain, kAvTaskBrain, plAvTask)

private:
    plArmatureBrain* fBrain;

public:
    plAvTaskBrain() : fBrain() { }
    ~plAvTaskBrain();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plArmatureBrain* getBrain() const { return fBrain; }
    void setBrain(plArmatureBrain* brain);
};


// Yay redundancy
class PLASMA_DLL plAvTaskSeek : public plAvTask
{
    CREATABLE(plAvTaskSeek, kAvTaskSeek, plAvTask)
};

#endif
