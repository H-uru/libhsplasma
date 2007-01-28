#ifndef _PLCLOTHINGITEM_H
#define _PLCLOTHINGITEM_H

#include "../../NucleusLib/pnKeyedObject/hsKeyedObject.h"
#include "../../NucleusLib/pnKeyedObject/plKey.h"
#include "../../CoreLib/hsTArray.hpp"
#include "../../CoreLib/hsRefCnt.h"

struct Clothing_Texture {
    char TexID;
    plKey * Texture;
};

class Clothing_FeatureSet : public hsRefCnt {
private:
    char* FeatureName;
    unsigned char TexCount;

public:
    Clothing_Texture* Textures;

    Clothing_FeatureSet();
    virtual ~Clothing_FeatureSet();

    virtual void read(hsStream *S);
    virtual void write(hsStream *S);

    const char* getFeatureName();
    const char getTexCount();
    //plMipMap* getTexture(int id);
};

class plClothingItem : public hsKeyedObject {
protected:
    char* ItemName;
    char ClothingGroup, ClothingType, ClosetCategory;
    bool Unknown;

    char* AttrList;
    char* FriendlyName;

    hsTArray<Clothing_FeatureSet> Features;

    plKey * Icon;
    plKey * HQMesh;
    plKey * MQMesh;
    plKey * LQMesh;
    plKey * ClothingItem;

    unsigned char DefaultTint1[3];
    unsigned char DefaultTint2[3];

public:
    plClothingItem(PlasmaVer pv = pvUnknown);
    virtual ~plClothingItem();

    virtual short ClassIndex();

    virtual void read(hsStream *S);
    virtual void write(hsStream *S);
};

#endif

