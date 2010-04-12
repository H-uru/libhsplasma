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

#ifndef _PLDYNARIPPLEMGR_H
#define _PLDYNARIPPLEMGR_H

#include "plDynaDecalMgr.h"
#include "PRP/Animation/plAnimPath.h"

DllClass plDynaRippleMgr : public plDynaDecalMgr {
    CREATABLE(plDynaRippleMgr, kDynaRippleMgr, plDynaDecalMgr)

protected:
    hsVector3 fInitUVW, fFinalUVW;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plDynaRippleVSMgr : public plDynaRippleMgr {
    CREATABLE(plDynaRippleVSMgr, kDynaRippleVSMgr, plDynaRippleMgr)

protected:
    plKey fWaveSetBase;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plDynaTorpedoMgr : public plDynaRippleMgr {
    CREATABLE(plDynaTorpedoMgr, kDynaTorpedoMgr, plDynaRippleMgr)
};


DllClass plDynaTorpedoVSMgr : public plDynaTorpedoMgr {
    CREATABLE(plDynaTorpedoVSMgr, kDynaTorpedoVSMgr, plDynaTorpedoMgr)

protected:
    plKey fWaveSetBase;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plDynaPuddleMgr : public plDynaRippleMgr {
    CREATABLE(plDynaPuddleMgr, kDynaPuddleMgr, plDynaRippleMgr)
};

DllClass plDynaWakeMgr : public plDynaRippleMgr {
    CREATABLE(plDynaWakeMgr, kDynaWakeMgr, plDynaRippleMgr)

protected:
    hsVector3 fDefaultDir;
    plAnimPath* fAnimPath;
    float fAnimWgt, fVelWgt;

public:
    plDynaWakeMgr();
    virtual ~plDynaWakeMgr();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    void setAnimPath(plAnimPath* path);
};

#endif
