#ifndef _PFGUIDYNDISPLAYCTRL_H
#define _PFGUIDYNDISPLAYCTRL_H

#include "pfGUIControlMod.h"

DllClass pfGUIDynDisplayCtrl : public pfGUIControlMod {
    CREATABLE(pfGUIDynDisplayCtrl, kGUIDynDisplayCtrl, pfGUIControlMod)

protected:
    hsTArray<plKey> fTextMaps, fLayers, fMaterials;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const hsTArray<plKey>& getTextMaps() const { return fTextMaps; }
    hsTArray<plKey>& getTextMaps() { return fTextMaps; }
    void addTextMap(plKey map) { fTextMaps.append(map); }
    void delTextMap(size_t idx) { fTextMaps.remove(idx); }
    void clearTextMaps() { fTextMaps.clear(); }

    const hsTArray<plKey>& getLayers() const { return fLayers; }
    hsTArray<plKey>& getLayers() { return fLayers; }
    void addLayer(plKey map) { fLayers.append(map); }
    void delLayer(size_t idx) { fLayers.remove(idx); }
    void clearLayers() { fLayers.clear(); }

    const hsTArray<plKey>& getMaterials() const { return fMaterials; }
    hsTArray<plKey>& getMaterials() { return fMaterials; }
    void addMaterial(plKey map) { fMaterials.append(map); }
    void delMaterial(size_t idx) { fMaterials.remove(idx); }
    void clearMaterials() { fMaterials.clear(); }
};

#endif
