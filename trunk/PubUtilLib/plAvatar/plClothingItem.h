#ifndef _PLCLOTHINGITEM_H
#define _PLCLOTHINGITEM_H

#include "CoreLib/hsTArray.hpp"
#include "NucleusLib/pnKeyedObject/hsKeyedObject.h"

class plClothingItem : public hsKeyedObject {
protected:
    plString fItemName;
    unsigned char fGroup, fType, fTileset, fSortOrder;

    plString fDescription;
    plString fCustomText;

    hsTArray<plString> fElementNames;
    hsTArray<plKey*> fTextures;

    plKey fIcon;
    plKey fMeshes[3];
    plKey fAccessory;

    unsigned char fDefaultTint1[3];
    unsigned char fDefaultTint2[3];

public:
    plClothingItem();
    virtual ~plClothingItem();

    DECLARE_CREATABLE(plClothingItem)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

#endif

