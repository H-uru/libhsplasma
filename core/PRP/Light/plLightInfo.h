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
#include "PRP/Geometry/hsGDeviceRef.hpp"

class PLASMA_DLL plLightInfo : public virtual plObjInterface {
    CREATABLE(plLightInfo, kLightInfo, plObjInterface)

public:
    enum {
        kDisable, kLPObsolete, kLPCastShadows, kLPMovable, kLPHasIncludes,
        kLPIncludesChars, kLP_OBSOLECTE_0, kLPOverAll, kLPHasSpecular,
        kLPShadowOnly, kLPShadowLightGroup, kLPForceProj, kNumProps
    };

protected:
    hsTArray<plKey> fVisRegions;
    hsColorRGBA fAmbient, fDiffuse, fSpecular;
    hsMatrix44 fLightToLocal, fLocalToLight, fLightToWorld, fWorldToLight;
    plKey fProjection, fSoftVolume;
    plKey fSceneNode;

public:
    plLightInfo();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

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
    void setProjection(plKey proj) { fProjection = proj; }
    void setSoftVolume(plKey vol) { fSoftVolume = vol; }
    void setSceneNode(plKey node) { fSceneNode = node; }

    const hsTArray<plKey>& getVisRegions() const { return fVisRegions; }
    hsTArray<plKey>& getVisRegions() { return fVisRegions; }
    void addVisRegion(plKey region) { fVisRegions.append(region); }
    void delVisRegion(size_t idx) { fVisRegions.remove(idx); }
    void clearVisRegions() { fVisRegions.clear(); }
};

#endif
