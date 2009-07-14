#ifndef _PLCLOTHINGITEM_H
#define _PLCLOTHINGITEM_H

#include "Util/hsTArray.hpp"
#include "PRP/KeyedObject/hsKeyedObject.h"

DllClass plClothingItem : public hsKeyedObject {
protected:
    plString fItemName, fDescription, fCustomText;
    unsigned char fGroup, fType, fTileset, fSortOrder;

    hsTArray<plString> fElementNames;
    hsTArray<plKey*> fTextures;
    plKey fIcon, fAccessory, fMeshes[3];

    unsigned char fDefaultTint1[3];
    unsigned char fDefaultTint2[3];

public:
    plClothingItem();
    virtual ~plClothingItem();

    DECLARE_CREATABLE(plClothingItem)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    void clearTextures();
};

#endif
