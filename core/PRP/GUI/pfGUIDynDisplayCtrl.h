#ifndef _PFGUIDYNDISPLAYCTRL_H
#define _PFGUIDYNDISPLAYCTRL_H

#include "pfGUIControlMod.h"

DllClass pfGUIDynDisplayCtrl : public pfGUIControlMod {
protected:
    hsTArray<plKey> fTextMaps, fLayers, fMaterials;

public:
    pfGUIDynDisplayCtrl();
    virtual ~pfGUIDynDisplayCtrl();

    DECLARE_CREATABLE(pfGUIDynDisplayCtrl)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    size_t getNumTextMaps() const;
    plKey getTextMap(size_t idx) const;
    void addTextMap(plKey map);
    void delTextMap(size_t idx);
    void clearTextMaps();

    size_t getNumLayers() const;
    plKey getLayer(size_t idx) const;
    void addLayer(plKey layer);
    void delLayer(size_t idx);
    void clearLayers();

    size_t getNumMaterials() const;
    plKey getMaterial(size_t idx) const;
    void addMaterial(plKey mat);
    void delMaterial(size_t idx);
    void clearMaterials();
};

#endif
