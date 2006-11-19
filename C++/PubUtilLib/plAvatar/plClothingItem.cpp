#include "plClothingItem.h"

/* Clothing_FeatureSet */
Clothing_FeatureSet::Clothing_FeatureSet() : FeatureName(""), TexCount(0) {
    Textures = new Clothing_Texture[0];
}

Clothing_FeatureSet::~Clothing_FeatureSet() {
    delete [] Textures;
    delete FeatureName;
}

void Clothing_FeatureSet::read(hsStream *S) {
    delete FeatureName;
    FeatureName = S->readSafeStr();
    TexCount = S->readByte();
    delete [] Textures;
    Textures = new Clothing_Texture[TexCount];
    for (unsigned char i=0; i<TexCount; i++) {
        Textures[i].TexID = S->readByte();
        Textures[i].Texture.read(S);
    }
}

void Clothing_FeatureSet::write(hsStream *S) {
    S->writeSafeStr(FeatureName);
    S->writeByte(TexCount);
    for (unsigned char i=0; i<TexCount; i++) {
        S->writeByte(Textures[i].TexID);
        Textures[i].Texture.write(S);
    }
}

const char* Clothing_FeatureSet::getFeatureName() {
    return FeatureName;
}

const char Clothing_FeatureSet::getTexCount() {
    return TexCount;
}

/*
plMipMap* Clothing_FeatureSet::getTexture(int id) {
    //
}*/


/* plClothingItem */
plClothingItem::plClothingItem() : ItemName(""), ClothingGroup(0),
                  ClothingType(0), ClosetCategory(0), Unknown(false),
                  AttrList(""), FriendlyName(""), Icon(NULL), HQMesh(NULL),
                  MQMesh(NULL), LQMesh(NULL) {
    ClothingItem = new plKey();
    Extra[0] = 0;
    Extra[1] = 0;
    Extra[2] = 0;
}

plClothingItem::~plClothingItem() {
    if (Icon) delete Icon;
    if (HQMesh) delete HQMesh;
    if (MQMesh) delete MQMesh;
    if (LQMesh) delete LQMesh;
    delete ClothingItem;
    delete ItemName;
    delete AttrList;
    delete FriendlyName;
}

void plClothingItem::read(hsStream *S) {
    hsKeyedObject::read(S);

    delete ItemName;
    ItemName = S->readSafeStr();
    ClothingGroup = S->readByte();
    ClothingType = S->readByte();
    ClosetCategory = S->readByte();
    Unknown = S->readBool();

    delete AttrList;
    AttrList = S->readSafeStr();
    delete FriendlyName;
    FriendlyName = S->readSafeStr();

    if (Icon) {
        delete Icon;
        Icon = NULL;
    }
    if (S->readBool()) {
        Icon = new plKey();
        Icon->readRef(S);
    }

    Features.read(S);

    if (HQMesh) {
        delete HQMesh;
        HQMesh = NULL;
    }
    if (S->readBool()) {
        HQMesh = new plKey();
        HQMesh->readRef(S);
    }
    if (MQMesh) {
        delete MQMesh;
        MQMesh = NULL;
    }
    if (S->readBool()) {
        MQMesh = new plKey();
        MQMesh->readRef(S);
    }
    if (LQMesh) {
        delete LQMesh;
        LQMesh = NULL;
    }
    if (S->readBool()) {
        LQMesh = new plKey();
        LQMesh->readRef(S);
    }

    delete ClothingItem;
    ClothingItem = new plKey();
    ClothingItem->readRef(S);

    for (int i=0; i<3; i++)
        Extra[i] = S->readShort();
}

void plClothingItem::write(hsStream *S) {
    hsKeyedObject::write(S);

    S->writeSafeStr(ItemName);
    S->writeByte(ClothingGroup);
    S->writeByte(ClothingType);
    S->writeByte(ClosetCategory);
    S->writeBool(Unknown);

    S->writeSafeStr(AttrList);
    S->writeSafeStr(FriendlyName);

    if (Icon) {
        S->writeBool(true);
        Icon->writeRef(S);
    } else
        S->writeBool(false);

    Features.write(S);

    if (HQMesh) {
        S->writeBool(true);
        HQMesh->writeRef(S);
    } else
        S->writeBool(false);
    if (MQMesh) {
        S->writeBool(true);
        MQMesh->writeRef(S);
    } else
        S->writeBool(false);
    if (LQMesh) {
        S->writeBool(true);
        LQMesh->writeRef(S);
    } else
        S->writeBool(false);

    ClothingItem->writeRef(S);

    for (int i=0; i<3; i++)
        S->writeShort(Extra[i]);
}

