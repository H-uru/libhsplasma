#ifndef _PLCLOTHINGITEM_H
#define _PLCLOTHINGITEM_H

#include "../../NucleusLib/pnKeyedObject/hsKeyedObject.h"
#include "../../NucleusLib/pnKeyedObject/plKey.h"
#include "../../CoreLib/hsTArray.hpp"
#include "../../CoreLib/hsRefCnt.h"

class plClothingItem : public hsKeyedObject {
protected:
    char* ItemName;
    unsigned char Group, Type, Tileset, SortOrder;

    char* Description;
    char* CustomText;

    hsTArray<char*> ElementNames;
    hsTArray<plKey**> Textures;

    plKey* Icon;
    plKey* Meshes[3];
    plKey* Accessory;

    unsigned char DefaultTint1[3];
    unsigned char DefaultTint2[3];

public:
    plClothingItem(PlasmaVer pv = pvUnknown);
    virtual ~plClothingItem();

    virtual short ClassIndex();
    virtual const char* ClassName();

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(hsStream* S, pfPrcHelper* prc);
};

#endif

