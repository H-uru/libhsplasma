#ifndef _PLIMAGELIBMOD_H

#include "PRP/Modifier/plModifier.h"

DllClass plImageLibMod : public plSingleModifier {
    CREATABLE(plImageLibMod, kImageLibMod, plSingleModifier)

protected:
    hsTArray<plKey> fImages;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const hsTArray<plKey>& getImages() const { return fImages; }
    hsTArray<plKey>& getImages() { return fImages; }
    void addImage(plKey img) { fImages.append(img); }
    void delImage(size_t idx) { fImages.remove(idx); }
    void clearImages() { fImages.clear(); }
};

#endif
