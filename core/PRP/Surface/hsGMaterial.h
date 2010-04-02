#ifndef _HSGMATERIAL_H
#define _HSGMATERIAL_H

#include "PRP/Object/plSynchedObject.h"
#include "Util/hsTArray.hpp"

DllClass hsGMaterial : public plSynchedObject {
    CREATABLE(hsGMaterial, kGMaterial, plSynchedObject)

public:
    enum hsGCompFlags {
        kCompShaded = 0x1,
        kCompEnvironMap = 0x2,
        kCompProjectOnto = 0x4,
        kCompSoftShadow = 0x8,
        kCompSpecular = 0x10,
        kCompTwoSided = 0x20,
        kCompDrawAsSplats = 0x40,
        kCompAdjusted = 0x80,
        kCompNoSoftShadow = 0x100,
        kCompDynamic = 0x200,
        kCompDecal = 0x400,
        kCompIsEmissive = 0x800,    // OBSOLETE
        kCompIsLightMapped = 0x1000,
        kCompNeedsBlendChannel = 0x2000
    };

private:
    hsTArray<plKey> fLayers, fPiggyBacks;
    unsigned int fCompFlags, fLoadFlags;

public:
    hsGMaterial();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const hsTArray<plKey>& getLayers() const { return fLayers; }
    hsTArray<plKey>& getLayers() { return fLayers; }
    void addLayer(plKey layer) { fLayers.append(layer); }
    void delLayer(size_t idx) { fLayers.remove(idx); }
    void clearLayers() { fLayers.clear(); }

    const hsTArray<plKey>& getPiggyBacks() const { return fPiggyBacks; }
    hsTArray<plKey>& getPiggyBacks() { return fPiggyBacks; }
    void addPiggyBack(plKey layer) { fPiggyBacks.append(layer); }
    void delPiggyBack(size_t idx) { fPiggyBacks.remove(idx); }
    void clearPiggyBacks() { fPiggyBacks.clear(); }

    unsigned int getCompFlags() const { return fCompFlags; }
    unsigned int getLoadFlags() const { return fLoadFlags; }
    void setCompFlags(unsigned int flags) { fCompFlags = flags; }
    void setLoadFlags(unsigned int flags) { fLoadFlags = flags; }
};

#endif
