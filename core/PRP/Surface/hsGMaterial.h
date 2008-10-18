#ifndef _HSGMATERIAL_H
#define _HSGMATERIAL_H

#include "PRP/Object/plSynchedObject.h"
#include "Util/hsTArray.hpp"

DllClass hsGMaterial : public plSynchedObject {
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
    virtual ~hsGMaterial();

    DECLARE_CREATABLE(hsGMaterial)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    size_t getNumLayers() const;
    plKey getLayer(size_t idx) const;
    void clearLayers();
    void addLayer(plKey layer);
    void delLayer(size_t idx);

    size_t getNumPiggyBacks() const;
    plKey getPiggyBack(size_t idx) const;
    void clearPiggyBacks();
    void addPiggyBack(plKey pb);
    void delPiggyBack(size_t idx);

    unsigned int getCompFlags() const;
    unsigned int getLoadFlags() const;
    void setCompFlags(unsigned int flags);
    void setLoadFlags(unsigned int flags);
};

#endif
