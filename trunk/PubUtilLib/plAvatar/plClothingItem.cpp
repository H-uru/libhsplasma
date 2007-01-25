#include "plClothingItem.h"
#include "../plResMgr/plResManager.h"

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
    for (unsigned char j=0; j<TexCount; j++) {
        Textures[j].TexID = S->readByte();
        Textures[j].Texture = new plKey();
        Textures[j].Texture = plResManager::inst->readKey(S);
    }
}

void Clothing_FeatureSet::write(hsStream *S) {
    S->writeSafeStr(FeatureName);
    S->writeByte(TexCount);
    for (unsigned char i=0; i<TexCount; i++) {
        S->writeByte(Textures[i].TexID);
        plResManager::inst->writeKey(S, Textures[i].Texture);
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
    DefaultTint1[0] = DefaultTint2[0] = 255;
    DefaultTint1[1] = DefaultTint2[1] = 255;
    DefaultTint1[2] = DefaultTint2[2] = 255;
}

plClothingItem::~plClothingItem() {
    if (Icon) Icon->UnRef();
    if (HQMesh) HQMesh->UnRef();
    if (MQMesh) MQMesh->UnRef();
    if (LQMesh) LQMesh->UnRef();
    ClothingItem->UnRef();
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
    Unknown = S->readByte();

    delete AttrList;
    AttrList = S->readSafeStr();
    delete FriendlyName;
    FriendlyName = S->readSafeStr();

    if (Icon) {
        Icon->UnRef();
        Icon = NULL;
    }
    if (S->readBool()) {
        Icon = plResManager::inst->readKey(S);
        Icon->Ref();
    }

    Features.clear();
    Features.setSize(S->readInt());
	int i;
    for (i=0; i<Features.getSize(); i++)
        Features[i].read(S);

    if (HQMesh) {
        HQMesh->UnRef();
        HQMesh = NULL;
    }
    if (S->readBool()) {
        HQMesh = plResManager::inst->readKey(S);
        HQMesh->Ref();
    }
    if (MQMesh) {
        MQMesh->UnRef();
        MQMesh = NULL;
    }
    if (S->readBool()) {
        MQMesh = plResManager::inst->readKey(S);
        MQMesh->Ref();
    }
    if (LQMesh) {
        LQMesh->UnRef();
        LQMesh = NULL;
    }
    if (S->readBool()) {
        LQMesh = plResManager::inst->readKey(S);
        LQMesh->Ref();
    }

    ClothingItem->UnRef();
    ClothingItem = plResManager::inst->readKey(S);
    ClothingItem->Ref();

    for (i=0; i<3; i++) {
        DefaultTint1[i] = S->readByte();
        DefaultTint2[i] = S->readByte();
    }
}

void plClothingItem::write(hsStream *S) {
    hsKeyedObject::write(S);

    S->writeSafeStr(ItemName);
    S->writeByte(ClothingGroup);
    S->writeByte(ClothingType);
    S->writeByte(ClosetCategory);
    S->writeByte(Unknown);

    S->writeSafeStr(AttrList);
    S->writeSafeStr(FriendlyName);

    if (Icon) {
        S->writeBool(true);
        plResManager::inst->writeKey(S, Icon);
    } else
        S->writeBool(false);

    S->writeInt(Features.getSize());
	int i;
    for (i=0; i<Features.getSize(); i++)
        Features[i].write(S);

    if (HQMesh) {
        S->writeBool(true);
        plResManager::inst->writeKey(S, HQMesh);
    } else
        S->writeBool(false);
    if (MQMesh) {
        S->writeBool(true);
        plResManager::inst->writeKey(S, MQMesh);
    } else
        S->writeBool(false);
    if (LQMesh) {
        S->writeBool(true);
        plResManager::inst->writeKey(S, LQMesh);
    } else
        S->writeBool(false);

    plResManager::inst->writeKey(S, ClothingItem);

    for (i=0; i<3; i++) {
        S->writeByte(DefaultTint1[i]);
        S->writeByte(DefaultTint2[i]);
    }
}

