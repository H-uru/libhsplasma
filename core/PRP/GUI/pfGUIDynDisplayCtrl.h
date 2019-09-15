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

#ifndef _PFGUIDYNDISPLAYCTRL_H
#define _PFGUIDYNDISPLAYCTRL_H

#include "pfGUIControlMod.h"

class PLASMA_DLL pfGUIDynDisplayCtrl : public pfGUIControlMod
{
    CREATABLE(pfGUIDynDisplayCtrl, kGUIDynDisplayCtrl, pfGUIControlMod)

protected:
    std::vector<plKey> fTextMaps, fLayers, fMaterials;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    const std::vector<plKey>& getTextMaps() const { return fTextMaps; }
    std::vector<plKey>& getTextMaps() { return fTextMaps; }
    void addTextMap(plKey map) { fTextMaps.emplace_back(std::move(map)); }
    void delTextMap(size_t idx) { fTextMaps.erase(fTextMaps.begin() + idx); }
    void clearTextMaps() { fTextMaps.clear(); }

    const std::vector<plKey>& getLayers() const { return fLayers; }
    std::vector<plKey>& getLayers() { return fLayers; }
    void addLayer(plKey map) { fLayers.emplace_back(std::move(map)); }
    void delLayer(size_t idx) { fLayers.erase(fLayers.begin() + idx); }
    void clearLayers() { fLayers.clear(); }

    const std::vector<plKey>& getMaterials() const { return fMaterials; }
    std::vector<plKey>& getMaterials() { return fMaterials; }
    void addMaterial(plKey map) { fMaterials.emplace_back(std::move(map)); }
    void delMaterial(size_t idx) { fMaterials.erase(fMaterials.begin() + idx); }
    void clearMaterials() { fMaterials.clear(); }
};

#endif
