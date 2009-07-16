#ifndef _PLIMAGELIBMOD_H

#include "PRP/Modifier/plModifier.h"

DllClass plImageLibMod : public plSingleModifier {
protected:
    hsTArray<plKey> fImages;

public:
    plImageLibMod();
    virtual ~plImageLibMod();
    
    DECLARE_CREATABLE(plImageLibMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    size_t getNumImages() const;
    plKey getImage(size_t idx) const;
    void addImage(plKey img);
    void delImage(size_t idx);
    void clearImages();
};

#endif
