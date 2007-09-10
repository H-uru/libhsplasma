#ifndef _PLCLOTHINGITEM_H
#define _PLCLOTHINGITEM_H

#include "../../NucleusLib/pnKeyedObject/hsKeyedObject.h"
#include "../../NucleusLib/pnKeyedObject/plKey.h"
#include "../../CoreLib/hsTArray.hpp"
#include "../../CoreLib/hsRefCnt.h"

class plClothingItem : public hsKeyedObject {
protected:
    plString ItemName;
    unsigned char Group, Type, Tileset, SortOrder;

    plString Description;
    plString CustomText;

    hsTArray<plString> ElementNames;
    hsTArray<plKey*> Textures;

    plKey Icon;
    plKey Meshes[3];
    plKey Accessory;

    unsigned char DefaultTint1[3];
    unsigned char DefaultTint2[3];

public:
    plClothingItem();
    virtual ~plClothingItem();

    DECLARE_CREATABLE(plClothingItem)

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif

