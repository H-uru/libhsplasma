#include "pfGUIDynDisplayCtrl.h"

pfGUIDynDisplayCtrl::pfGUIDynDisplayCtrl() { }
pfGUIDynDisplayCtrl::~pfGUIDynDisplayCtrl() { }

IMPLEMENT_CREATABLE(pfGUIDynDisplayCtrl, kGUIDynDisplayCtrl, pfGUIControlMod)

void pfGUIDynDisplayCtrl::read(hsStream* S, plResManager* mgr) {
    pfGUIControlMod::read(S, mgr);

    fTextMaps.setSize(S->readInt());
    for (size_t i=0; i<fTextMaps.getSize(); i++)
        fTextMaps[i] = mgr->readKey(S);

    fLayers.setSize(S->readInt());
    for (size_t i=0; i<fLayers.getSize(); i++)
        fLayers[i] = mgr->readKey(S);

    if (S->getVer() >= pvPots) {
        fMaterials.setSize(S->readInt());
        for (size_t i=0; i<fMaterials.getSize(); i++)
            fMaterials[i] = mgr->readKey(S);
    }
}

void pfGUIDynDisplayCtrl::write(hsStream* S, plResManager* mgr) {
    pfGUIControlMod::write(S, mgr);

    S->writeInt(fTextMaps.getSize());
    for (size_t i=0; i<fTextMaps.getSize(); i++)
        mgr->writeKey(S, fTextMaps[i]);

    S->writeInt(fLayers.getSize());
    for (size_t i=0; i<fLayers.getSize(); i++)
        mgr->writeKey(S, fLayers[i]);

    if (S->getVer() >= pvPots) {
        S->writeInt(fMaterials.getSize());
        for (size_t i=0; i<fMaterials.getSize(); i++)
            mgr->writeKey(S, fMaterials[i]);
    }
}

void pfGUIDynDisplayCtrl::IPrcWrite(pfPrcHelper* prc) {
    pfGUIControlMod::IPrcWrite(prc);

    prc->writeSimpleTag("TextMaps");
    for (size_t i=0; i<fTextMaps.getSize(); i++)
        fTextMaps[i]->prcWrite(prc);
    prc->closeTag();
    
    prc->writeSimpleTag("Layers");
    for (size_t i=0; i<fLayers.getSize(); i++)
        fLayers[i]->prcWrite(prc);
    prc->closeTag();
    
    prc->writeSimpleTag("Materials");
    for (size_t i=0; i<fMaterials.getSize(); i++)
        fMaterials[i]->prcWrite(prc);
    prc->closeTag();
}

void pfGUIDynDisplayCtrl::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "TextMaps") {
        fTextMaps.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fTextMaps.getSize(); i++) {
            fTextMaps[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Layers") {
        fLayers.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fLayers.getSize(); i++) {
            fLayers[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Materials") {
        fMaterials.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fMaterials.getSize(); i++) {
            fMaterials[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        pfGUIControlMod::IPrcParse(tag, mgr);
    }
}

size_t pfGUIDynDisplayCtrl::getNumTextMaps() const { return fTextMaps.getSize(); }
plKey pfGUIDynDisplayCtrl::getTextMap(size_t idx) const { return fTextMaps[idx]; }
void pfGUIDynDisplayCtrl::addTextMap(plKey map) { fTextMaps.append(map); }
void pfGUIDynDisplayCtrl::delTextMap(size_t idx) { fTextMaps.remove(idx); }
void pfGUIDynDisplayCtrl::clearTextMaps() { fTextMaps.clear(); }

size_t pfGUIDynDisplayCtrl::getNumLayers() const { return fLayers.getSize(); }
plKey pfGUIDynDisplayCtrl::getLayer(size_t idx) const { return fLayers[idx]; }
void pfGUIDynDisplayCtrl::addLayer(plKey layer) { fLayers.append(layer); }
void pfGUIDynDisplayCtrl::delLayer(size_t idx) { fLayers.remove(idx); }
void pfGUIDynDisplayCtrl::clearLayers() { fLayers.clear(); }

size_t pfGUIDynDisplayCtrl::getNumMaterials() const { return fMaterials.getSize(); }
plKey pfGUIDynDisplayCtrl::getMaterial(size_t idx) const { return fMaterials[idx]; }
void pfGUIDynDisplayCtrl::addMaterial(plKey mat) { fMaterials.append(mat); }
void pfGUIDynDisplayCtrl::delMaterial(size_t idx) { fMaterials.remove(idx); }
void pfGUIDynDisplayCtrl::clearMaterials() { fMaterials.clear(); }
