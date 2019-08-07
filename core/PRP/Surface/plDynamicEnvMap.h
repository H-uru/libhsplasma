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

#ifndef _PLDYNAMICENVMAP_H
#define _PLDYNAMICENVMAP_H

#include "plRenderTarget.h"

class PLASMA_DLL plDynamicEnvMap : public plCubicRenderTarget
{
    CREATABLE(plDynamicEnvMap, kDynamicEnvMap, plCubicRenderTarget)

protected:
    plKey fRootNode;
    hsVector3 fPos;
    float fHither, fYon, fFogStart;
    hsColorRGBA fColor;
    float fRefreshRate;
    std::vector<plKey> fVisRegions;
    std::vector<ST::string> fVisRegionNames;
    bool fIncCharacters;

public:
    plDynamicEnvMap()
        : fHither(), fYon(), fFogStart(), fRefreshRate(), fIncCharacters() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    /** Returns the root node */
    plKey getRootNode() const { return fRootNode; }

    /** Returns the position */
    hsVector3 getPosition() const { return fPos; }

    /** Returns the hither distance */
    float getHither() const { return fHither; }

    /** Returns the yon distance */
    float getYon() const { return fYon; }

    /** Returns the fog start distance */
    float getFogStart() const { return fFogStart; }

    /** Returns the fog color */
    hsColorRGBA getColor() const { return fColor; }

    /** Returns the refresh rate */
    float getRefreshRate() const { return fRefreshRate; }

    /** Returns a list of visregions */
    const std::vector<plKey>& getVisRegions() const { return fVisRegions; }

    /** Returns a list of visregions by name (from other pages) */
    const std::vector<ST::string>& getVisRegionNames() const { return fVisRegionNames; }

    /** Returns whether to include avatars in the render */
    bool getIncludeCharacters() const { return fIncCharacters; }

    /** Set the root node */
    void setRootNode(plKey rootNode) { fRootNode = std::move(rootNode); }

    /** Set the position  */
    void setPosition(hsVector3 pos) { fPos = pos; }

    /** Set the hither distance */
    void setHither(float hither) { fHither = hither; }

    /** Set the yon distance */
    void setYon(float yon) { fYon = yon; }

    /** Set the fog start distance */
    void setFogStart(float fogstart) { fFogStart = fogstart; }

    /** Set the fog color */
    void setColor(hsColorRGBA color) { fColor = color; }

    /** Set the refresh rate */
    void setRefreshRate(float refreshRate) { fRefreshRate = refreshRate; }

    /** Set the list of visregions */
    void setVisRegions(const std::vector<plKey>& visRegions) { fVisRegions = visRegions; }

    /** Set the list of visregion names (for other pages) */
    void setVisRegionNames(const std::vector<ST::string>& visRegionNames) { fVisRegionNames = visRegionNames; }

    /** Set whether to include avatars in the render */
    void setIncludeCharacters(bool incCharacters) { fIncCharacters = incCharacters; }
};


class PLASMA_DLL plDynamicCamMap : public plRenderTarget
{
    CREATABLE(plDynamicCamMap, kDynamicCamMap, plRenderTarget)

public:
    enum
    {
        kReflectionCapable = 0x1,
        kReflectionEnabled = 0x2,
        kReflectionMask = kReflectionCapable | kReflectionEnabled
    };

protected:
    float fHither, fYon, fFogStart;
    hsColorRGBA fColor;
    float fRefreshRate;
    std::vector<plKey> fVisRegions, fTargetNodes, fMatLayers;
    std::vector<ST::string> fVisRegionNames;
    bool fIncCharacters;
    plKey fCamera, fRootNode, fDisableTexture;

public:
    plDynamicCamMap()
        : fHither(), fYon(), fFogStart(), fRefreshRate(), fIncCharacters() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    /** Returns the hither distance */
    float getHither() const { return fHither; }

    /** Returns the yon distance */
    float getYon() const { return fYon; }

    /** Returns the fog start distance */
    float getFogStart() const { return fFogStart; }

    /** Returns the fog color */
    hsColorRGBA getColor() const { return fColor; }

    /** Returns the refresh rate */
    float getRefreshRate() const { return fRefreshRate; }

    /** Returns the list of visregions */
    const std::vector<plKey>& getVisRegions() const { return fVisRegions; }

    /** Returns the list of visregions */
    std::vector<plKey>& getVisRegions() { return fVisRegions; }

    /** Adds a visregion to the list */
    void addVisRegion(plKey key) { fVisRegions.emplace_back(std::move(key)); }

    /** Removes a visregion from the list */
    void delVisRegion(size_t idx) { fVisRegions.erase(fVisRegions.begin() + idx); }

    /** Clears the visregion list */
    void clearVisRegions() { fVisRegions.clear(); }

    /** Returns the list of target node SceneObject keys */
    const std::vector<plKey>& getTargetNodes() const { return fTargetNodes; }

    /** Returns the list of target node SceneObject keys */
    std::vector<plKey>& getTargetNodes() { return fTargetNodes; }

    /** Adds a target node to the list */
    void addTargetNode(plKey key) { fTargetNodes.emplace_back(std::move(key)); }

    /** Removes a target node from the list */
    void delTargetNode(size_t idx) { fTargetNodes.erase(fTargetNodes.begin() + idx); }

    /** Clears the target node list */
    void clearTargetNodes() { fTargetNodes.clear(); }

    /** Returns the list of material layers */
    const std::vector<plKey>& getMatLayers() const { return fMatLayers; }

    /** Returns the list of material layers */
    std::vector<plKey>& getMatLayers() { return fMatLayers; }

    /** Adds a material layer to the list */
    void addMatLayer(plKey key) { fMatLayers.emplace_back(std::move(key)); }

    /** Removes a material layer from the list */
    void delMatLayer(size_t idx) { fMatLayers.erase(fMatLayers.begin() + idx); }

    /** Clears the material layer list */
    void clearMatLayers() { fMatLayers.clear(); }

    /** Returns a list of visregions by name (from other pages)  */
    const std::vector<ST::string>& getVisRegionNames() const { return fVisRegionNames; }

    /** Returns the list of material layers */
    std::vector<ST::string>& getVisRegionNames() { return fVisRegionNames; }

    /** Adds a material layer to the list */
    void addVisRegionName(const ST::string& name) { fVisRegionNames.push_back(name); }

    /** Removes a material layer from the list */
    void delVisRegionName(size_t idx) { fVisRegionNames.erase(fVisRegionNames.begin() + idx); }

    /** Clears the material layer list */
    void clearVisRegionNames() { fVisRegionNames.clear(); }

    /** Returns whether to include avatars in the render  */
    bool getIncludeCharacters() const { return fIncCharacters; }

    /** Returns the camera */
    plKey getCamera() const { return fCamera; }

    /** Returns the root node */
    plKey getRootNode() const { return fRootNode; }

    /** Returns the texture to display when disabled */
    plKey getDisableTexture() const { return fDisableTexture; }

    /** Set the hither distance */
    void setHither(float hither) { fHither = hither; }

    /** Set the yon distance */
    void setYon(float yon) { fYon = yon; }

    /** Set the fog start distance */
    void setFogStart(float fogstart) { fFogStart = fogstart; }

    /** Set the fog color */
    void setColor(hsColorRGBA color) { fColor = color; }

    /** Set the refresh rate */
    void setRefreshRate(float refreshRate) { fRefreshRate = refreshRate; }

    /** Set the list of visregions */
    void setVisRegions(const std::vector<plKey>& visRegions) { fVisRegions = visRegions; }

    /** Set the list of target nodes */
    void setTargetNodes(const std::vector<plKey>& targetNodes) { fTargetNodes = targetNodes; }

    /** Set the list of material layers */
    void setMatLayers(const std::vector<plKey>& matLayers) { fMatLayers = matLayers; }

    /** Set the list of visregion names (for other pages) */
    void setVisRegionNames(const std::vector<ST::string>& visRegionNames) { fVisRegionNames = visRegionNames; }

    /** Set whether to include avatars in the render */
    void setIncludeCharacters(bool incCharacters) { fIncCharacters = incCharacters; }

    /** Set the camera */
    void setCamera(plKey camera) { fCamera = std::move(camera); }

    /** Set the root node */
    void setRootNode(plKey rootNode) { fRootNode = std::move(rootNode); }

    /** Set the texture to display when disabled */
    void setDisableTexture(plKey texture) { fDisableTexture = std::move(texture); }
};

#endif
