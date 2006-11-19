#ifndef _PLCLOTHINGITEM_H
#define _PLCLOTHINGITEM_H

#include "../../NucleusLib/pnKeyedObject/hsKeyedObject.h"
#include "../../NucleusLib/pnKeyedObject/plKey.h"
#include "../../CoreLib/hsTArray.hpp"

typedef struct Clothing_Texture {
    char TexID;
    plKey Texture;
};

class Clothing_FeatureSet {
private:
    char* FeatureName;
    unsigned char TexCount;

public:
    Clothing_Texture* Textures;

    Clothing_FeatureSet();
    ~Clothing_FeatureSet();

    void read(hsStream *S);
    void write(hsStream *S);

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

    short Extra[3];

public:
    plClothingItem();
    ~plClothingItem();

    void read(hsStream *S);
    void write(hsStream *S);
};

#endif

