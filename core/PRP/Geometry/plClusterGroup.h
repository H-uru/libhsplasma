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

#ifndef _PLCLUSTERGROUP_H
#define _PLCLUSTERGROUP_H

#include "PRP/KeyedObject/hsKeyedObject.h"
#include "PRP/Misc/plRenderLevel.h"
#include "plCluster.h"
#include "plSpanTemplate.h"

class PLASMA_DLL plLODDist
{
protected:
    float fMinDist, fMaxDist;

public:
    plLODDist() : fMinDist(), fMaxDist() { }

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

public:
    float getMin() const { return fMinDist; }
    float getMax() const { return fMaxDist; }
    void setMin(float dist) { fMinDist = dist; }
    void setMax(float dist) { fMaxDist = dist; }
};

class PLASMA_DLL plClusterGroup : public hsKeyedObject
{
    CREATABLE(plClusterGroup, kClusterGroup, hsKeyedObject)

protected:
    plSpanTemplate fTemplate;
    plKey fMaterial;
    std::vector<plCluster*> fClusters;
    std::vector<plKey> fRegions, fLights;
    plLODDist fLOD;
    plKey fSceneNode, fDrawable;
    unsigned int fRenderLevel;

public:
    plClusterGroup() : fRenderLevel() { }
    ~plClusterGroup();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    const plLODDist& getLOD() const { return fLOD; }
    plLODDist& getLOD() { return fLOD; }
    const plSpanTemplate& getTemplate() const { return fTemplate; }
    plSpanTemplate& getTemplate() { return fTemplate; }

    plKey getMaterial() const { return fMaterial; }
    plKey getSceneNode() const { return fSceneNode; }
    plKey getDrawable() const { return fDrawable; }
    unsigned int getRenderLevel() const { return fRenderLevel; }

    void setMaterial(plKey mat) { fMaterial = std::move(mat); }
    void setSceneNode(plKey node) { fSceneNode = std::move(node); }
    void setDrawable(plKey draw) { fDrawable = std::move(draw); }
    void setRenderLevel(unsigned int level) { fRenderLevel = level; }

    const std::vector<plCluster*>& getClusters() const { return fClusters; }
    std::vector<plCluster*>& getClusters() { return fClusters; }
    void addCluster(plCluster* cluster) { fClusters.push_back(cluster); }
    void delCluster(size_t idx);
    void clearClusters();

    const std::vector<plKey>& getRegions() const { return fRegions; }
    std::vector<plKey>& getRegions() { return fRegions; }
    void addRegion(plKey region) { fRegions.emplace_back(std::move(region)); }
    void delRegion(size_t idx) { fRegions.erase(fRegions.begin() + idx); }
    void clearRegions() { fRegions.clear(); }

    const std::vector<plKey>& getLights() const { return fLights; }
    std::vector<plKey>& getLights() { return fLights; }
    void addLight(plKey light) { fLights.emplace_back(std::move(light)); }
    void delLight(size_t idx) { fLights.erase(fLights.begin() + idx); }
    void clearLights() { fLights.clear(); }
};

#endif
