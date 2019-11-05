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

class PLASMA_DLL plDynaRippleMgr : public plDynaDecalMgr
{
    CREATABLE(plDynaRippleMgr, kDynaRippleMgr, plDynaDecalMgr)

protected:
    hsVector3 fInitUVW, fFinalUVW;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    hsVector3 getInitUVW() const { return fInitUVW; }
    hsVector3 getFinalUVW() const { return fFinalUVW; }

    void setInitUVW(const hsVector3& value) { fInitUVW = value; }
    void setFinalUVW(const hsVector3& value) { fFinalUVW = value; }
};


class PLASMA_DLL plDynaRippleVSMgr : public plDynaRippleMgr
{
    CREATABLE(plDynaRippleVSMgr, kDynaRippleVSMgr, plDynaRippleMgr)

protected:
    plKey fWaveSetBase;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plKey getWaveSet() const { return fWaveSetBase; }
    void setWaveSet(plKey value) { fWaveSetBase = std::move(value); }
};


class PLASMA_DLL plDynaTorpedoMgr : public plDynaRippleMgr
{
    CREATABLE(plDynaTorpedoMgr, kDynaTorpedoMgr, plDynaRippleMgr)
};


class PLASMA_DLL plDynaTorpedoVSMgr : public plDynaTorpedoMgr
{
    CREATABLE(plDynaTorpedoVSMgr, kDynaTorpedoVSMgr, plDynaTorpedoMgr)

protected:
    plKey fWaveSetBase;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plKey getWaveSet() const { return fWaveSetBase; }
    void setWaveSet(plKey value) { fWaveSetBase = std::move(value); }
};


class PLASMA_DLL plDynaPuddleMgr : public plDynaRippleMgr
{
    CREATABLE(plDynaPuddleMgr, kDynaPuddleMgr, plDynaRippleMgr)
};

class PLASMA_DLL plDynaWakeMgr : public plDynaRippleMgr
{
    CREATABLE(plDynaWakeMgr, kDynaWakeMgr, plDynaRippleMgr)

protected:
    hsVector3 fDefaultDir;
    plAnimPath* fAnimPath;
    float fAnimWgt, fVelWgt;

public:
    plDynaWakeMgr() : fAnimPath(), fAnimWgt(), fVelWgt() { }
    ~plDynaWakeMgr();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    hsVector3 getDefaultDir() const { return fDefaultDir; }
    plAnimPath* getAnimPath() const { return fAnimPath; }
    float getAnimWgt() const { return fAnimWgt; }
    float getVelWgt() const { return fVelWgt; }

    void setDefaultDir(const hsVector3& value) { fDefaultDir = value; }
    void setAnimPath(plAnimPath* path);
    void setAnimWgt(float value) { fAnimWgt = value; }
    void setVelWgt(float value) { fVelWgt = value; }
};

#endif
