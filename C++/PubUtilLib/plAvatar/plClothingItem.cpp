#include "plClothingItem.h"

/* Clothing_FeatureSet */
Clothing_FeatureSet::Clothing_FeatureSet() : FeatureName(""), TexCount(0) {
    Textures = new Clothing_Texture[0];
}

Clothing_FeatureSet::~Clothing_FeatureSet() {
    for (int i=0; i<TexCount; i++)
        Textures[i].Texture->UnRef();
    delete [] Textures;
    delete FeatureName;
}

void Clothing_FeatureSet::read(hsStream *S) {
    delete FeatureName;
    FeatureName = S->readSafeStr();
    for (int i=0; i<TexCount; i++)
        Textures[i].Texture->UnRef();
    delete [] Textures;
    TexCount = S->readByte();
    Textures = new Clothing_Texture[TexCount];
    for (unsigned char i=0; i<TexCount; i++) {
        Textures[i].TexID = S->readByte();
        Textures[i].Texture = new plKey();
        Textures[i].Texture->read(S);
    }
}

void Clothing_FeatureSet::write(hsStream *S) {
    S->writeSafeStr(FeatureName);
    S->writeByte(TexCount);
    for (unsigned char i=0; i<TexCount; i++) {
        S->writeByte(Textures[i].TexID);
        Textures[i].Texture->write(S);
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
plClothingItem::plClothingItem(PlasmaVer pv) : ItemName(""), ClothingGroup(0),
                  ClothingType(0), ClosetCategory(0), Unknown(false),
                  AttrList(""), FriendlyName(""), Icon(NULL), HQMesh(NULL),
                  MQMesh(NULL), LQMesh(NULL) {
    ClothingItem = new plKey();
    Extra[0] = 0;
    Extra[1] = 0;
    Extra[2] = 0;
}

plClothingItem::~plClothingItem() {
    if (Icon) Icon->UnRef();
    if (HQMesh) HQMesh->UnRef();
    if (MQMesh) MQMesh->UnRef();
    if (LQMesh) LQMesh->UnRef();
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
        Icon->UnRef();
        Icon = NULL;
    }
    if (S->readBool()) {
        Icon = new plKey();
        Icon->readRef(S);
    }

    Features.clear();
    Features.setSize(S->readInt());
    for (int i=0; i<Features.getSize(); i++)
        Features[i].read(S);

    if (HQMesh) {
        HQMesh->UnRef();
        HQMesh = NULL;
    }
    if (S->readBool()) {
        HQMesh = new plKey();
        HQMesh->readRef(S);
    }
    if (MQMesh) {
        MQMesh->UnRef();
        MQMesh = NULL;
    }
    if (S->readBool()) {
        MQMesh = new plKey();
        MQMesh->readRef(S);
    }
    if (LQMesh) {
        LQMesh->UnRef();
        LQMesh = NULL;
    }
    if (S->readBool()) {
        LQMesh = new plKey();
        LQMesh->readRef(S);
    }

    ClothingItem->UnRef();
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

    S->writeInt(Features.getSize());
    for (int i=0; i<Features.getSize(); i++)
        Features[i].write(S);

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

