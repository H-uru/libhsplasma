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

#ifndef _PLLIGHTINFO_H
#define _PLLIGHTINFO_H

#include "PRP/Object/plObjInterface.h"
#include "Util/hsBitVector.h"
#include "Sys/hsColor.h"
#include "Math/hsMatrix44.h"

class PLASMA_DLL plLightInfo : public plObjInterface
{
    CREATABLE(plLightInfo, kLightInfo, plObjInterface)

public:
    enum
    {
        kDisable, kLPObsolete, kLPCastShadows, kLPMovable, kLPHasIncludes,
        kLPIncludesChars, kLP_OBSOLECTE_0, kLPOverAll, kLPHasSpecular,
        kLPShadowOnly, kLPShadowLightGroup, kLPForceProj, kNumProps
    };

protected:
    std::vector<plKey> fVisRegions;
    hsColorRGBA fAmbient, fDiffuse, fSpecular;
    hsMatrix44 fLightToLocal, fLocalToLight, fLightToWorld, fWorldToLight;
    plKey fProjection, fSoftVolume;
    plKey fSceneNode;

public:
    plLightInfo();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    hsColorRGBA getAmbient() const { return fAmbient; }
    hsColorRGBA getDiffuse() const { return fDiffuse; }
    hsColorRGBA getSpecular() const { return fSpecular; }
    hsMatrix44 getLightToLocal() const { return fLightToLocal; }
    hsMatrix44 getLocalToLight() const { return fLocalToLight; }
    hsMatrix44 getLightToWorld() const { return fLightToWorld; }
    hsMatrix44 getWorldToLight() const { return fWorldToLight; }
    plKey getProjection() const { return fProjection; }
    plKey getSoftVolume() const { return fSoftVolume; }
    plKey getSceneNode() const { return fSceneNode; }

    void setAmbient(const hsColorRGBA& color) { fAmbient = color; }
    void setDiffuse(const hsColorRGBA& color) { fDiffuse = color; }
    void setSpecular(const hsColorRGBA& color) { fSpecular = color; }
    void setLightToLocal(const hsMatrix44& xform) { fLightToLocal = xform; }
    void setLocalToLight(const hsMatrix44& xform) { fLocalToLight = xform; }
    void setLightToWorld(const hsMatrix44& xform) { fLightToWorld = xform; }
    void setWorldToLight(const hsMatrix44& xform) { fWorldToLight = xform; }
    void setProjection(plKey proj) { fProjection = std::move(proj); }
    void setSoftVolume(plKey vol) { fSoftVolume = std::move(vol); }
    void setSceneNode(plKey node) { fSceneNode = std::move(node); }

    const std::vector<plKey>& getVisRegions() const { return fVisRegions; }
    std::vector<plKey>& getVisRegions() { return fVisRegions; }
    void addVisRegion(plKey region) { fVisRegions.emplace_back(std::move(region)); }
    void delVisRegion(size_t idx) { fVisRegions.erase(fVisRegions.begin() + idx); }
    void clearVisRegions() { fVisRegions.clear(); }
};

#endif
