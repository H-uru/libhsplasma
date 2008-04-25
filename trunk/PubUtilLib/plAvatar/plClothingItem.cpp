#include "plClothingItem.h"

plClothingItem::plClothingItem()
              : fGroup(0), fType(0), fTileset(0), fSortOrder(0) {
    fDefaultTint1[0] = fDefaultTint2[0] = 255;
    fDefaultTint1[1] = fDefaultTint2[1] = 255;
    fDefaultTint1[2] = fDefaultTint2[2] = 255;
}

plClothingItem::~plClothingItem() { }

IMPLEMENT_CREATABLE(plClothingItem, kClothingItem, hsKeyedObject)

void plClothingItem::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);

    fItemName = S->readSafeStr();
    fGroup = S->readByte();
    fType = S->readByte();
    fTileset = S->readByte();
    fSortOrder = S->readByte();
    fDescription = S->readSafeStr();
    fCustomText = S->readSafeStr();

    if (S->readBool())
        fIcon = mgr->readKey(S);

    int count = S->readInt();
    fElementNames.setSize(count);
    fTextures.setSizeNull(count);
	int i, j, count2;
    for (i=0; i<count; i++) {
        fElementNames[i] = S->readSafeStr();
        fTextures[i] = new plKey[10];
        for (j=0; j<10; j++)
            fTextures[i][j] = NULL;
        count2 = S->readByte();
        for (j=0; j<count2; j++) {
            int idx = S->readByte();
            plKey k = mgr->readKey(S);
            if (idx > 0 && idx < 10)
                fTextures[i][idx] = k;
        }
    }

    for (i=0; i<3; i++) {
        if (S->readBool())
            fMeshes[i] = mgr->readKey(S);
    }

    fAccessory = mgr->readKey(S);

    for (i=0; i<3; i++) {
        fDefaultTint1[i] = S->readByte();
        fDefaultTint2[i] = S->readByte();
    }
}

void plClothingItem::write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);

    S->writeSafeStr(fItemName);
    S->writeByte(fGroup);
    S->writeByte(fType);
    S->writeByte(fTileset);
    S->writeByte(fSortOrder);
    S->writeSafeStr(fDescription);
    S->writeSafeStr(fCustomText);

    S->writeBool(fIcon.Exists());
    if (fIcon.Exists())
        mgr->writeKey(S, fIcon);

    size_t i, j;
    S->writeInt(fTextures.getSize());
    for (i=0; i<fTextures.getSize(); i++) {
        S->writeSafeStr(fElementNames[i]);
        int count2 = 0;
        for (j=0; j<10; j++)
            if (fTextures[i][j] != NULL) count2++;
        S->writeByte(count2);
        for (j=0; j<10; j++) {
            if (fTextures[i][j] != NULL) {
                S->writeByte(j);
                mgr->writeKey(S, fTextures[i][j]);
            }
        }
    }

    for (i=0; i<3; i++) {
        S->writeBool(fMeshes[i] != NULL);
        if (fMeshes[i] != NULL)
            mgr->writeKey(S, fMeshes[i]);
    }

    mgr->writeKey(S, fAccessory);

    for (i=0; i<3; i++) {
        S->writeByte(fDefaultTint1[i]);
        S->writeByte(fDefaultTint2[i]);
    }
}

void plClothingItem::IPrcWrite(pfPrcHelper* prc) {
    hsKeyedObject::IPrcWrite(prc);

    prc->startTag("ClothingName");
    prc->writeParam("value", fItemName);
    prc->endTag(true);
    
    prc->startTag("ClosetOptions");
    prc->writeParam("Group", fGroup);
    prc->writeParam("Type", fType);
    prc->writeParam("Tileset", fTileset);
    prc->writeParam("SortOrder", fSortOrder);
    prc->endTag(true);

    prc->writeTagNoBreak("Description");
    prc->getStream()->writeStr(fDescription);
    prc->closeTagNoBreak();

    prc->startTag("CustomText");
    prc->writeParam("value", fCustomText);
    prc->endTag(true);
}
