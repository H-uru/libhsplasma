#include "plClothingItem.h"
#include "Debug/plDebug.h"

plClothingItem::plClothingItem()
              : fGroup(0), fType(0), fTileset(0), fSortOrder(0) {
    fDefaultTint1[0] = fDefaultTint2[0] = 255;
    fDefaultTint1[1] = fDefaultTint2[1] = 255;
    fDefaultTint1[2] = fDefaultTint2[2] = 255;
}

plClothingItem::~plClothingItem() {
    for (size_t i=0; i<fTextures.getSize(); i++)
        delete[] fTextures[i];
}

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

    fElementNames.setSize(S->readInt());
    fTextures.setSizeNull(fElementNames.getSize());
    for (size_t i=0; i<fElementNames.getSize(); i++) {
        fElementNames[i] = S->readSafeStr();
        fTextures[i] = new plKey[10];
        size_t count = S->readByte();
        for (size_t j=0; j<count; j++) {
            size_t idx = S->readByte();
            plKey k = mgr->readKey(S);
            if (idx < 10)
                fTextures[i][idx] = k;
            else
                plDebug::Warning("Throwing away key %s", k->toString().cstr());
        }
    }

    for (size_t i=0; i<3; i++) {
        if (S->readBool())
            fMeshes[i] = mgr->readKey(S);
    }

    fAccessory = mgr->readKey(S);

    for (size_t i=0; i<3; i++) {
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

    S->writeInt(fTextures.getSize());
    for (size_t i=0; i<fTextures.getSize(); i++) {
        S->writeSafeStr(fElementNames[i]);
        int count = 0;
        for (size_t j=0; j<10; j++)
            if (fTextures[i][j].Exists()) count++;
        S->writeByte(count);
        for (size_t j=0; j<10; j++) {
            if (fTextures[i][j].Exists()) {
                S->writeByte(j);
                mgr->writeKey(S, fTextures[i][j]);
            }
        }
    }

    for (size_t i=0; i<3; i++) {
        S->writeBool(fMeshes[i].Exists());
        if (fMeshes[i].Exists())
            mgr->writeKey(S, fMeshes[i]);
    }

    mgr->writeKey(S, fAccessory);

    for (size_t i=0; i<3; i++) {
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

    prc->writeSimpleTag("Icon");
    fIcon->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Elements");
    for (size_t i=0; i<fTextures.getSize(); i++) {
        prc->startTag("Element");
        prc->writeParam("Name", fElementNames[i]);
        prc->endTag();
        for (size_t j=0; j<10; j++)
            fTextures[i][j]->prcWrite(prc);
        prc->closeTag();
    }
    prc->closeTag();

    prc->writeSimpleTag("Meshes");
    for (size_t i=0; i<3; i++)
        fMeshes[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Accessory");
    fAccessory->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("DefaultTints");
    for (size_t i=0; i<3; i++) {
        prc->startTag("Tint");
        prc->writeParam("color1", fDefaultTint1[i]);
        prc->writeParam("color2", fDefaultTint2[i]);
        prc->endTag(true);
    }
    prc->closeTag();
}

void plClothingItem::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "ClothingName") {
        fItemName = tag->getParam("value", "");
    } else if (tag->getName() == "ClosetOptions") {
        fGroup = tag->getParam("Group", "0").toUint();
        fType = tag->getParam("Type", "0").toUint();
        fTileset = tag->getParam("Tileset", "0").toUint();
        fSortOrder = tag->getParam("SortOrder", "0").toUint();
    } else if (tag->getName() == "Description") {
        fDescription = "";
        hsTList<plString> descTokens = tag->getContents();
        while (!descTokens.empty())
            fDescription += descTokens.pop() + " ";
    } else if (tag->getName() == "CustomText") {
        fCustomText = tag->getParam("value", "");
    } else if (tag->getName() == "Icon") {
        if (tag->hasChildren())
            fIcon = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Elements") {
        fElementNames.setSize(tag->countChildren());
        fTextures.setSizeNull(fElementNames.getSize());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fElementNames.getSize(); i++) {
            if (child->getName() != "Element")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            fElementNames[i] = child->getParam("Name", "");
            fTextures[i] = new plKey[10];
            size_t nSubChildren = child->countChildren();
            const pfPrcTag* subChild = child->getFirstChild();
            for (size_t j=0; j<nSubChildren; j++) {
                plKey k = mgr->prcParseKey(subChild);
                if (j < 10)
                    fTextures[i][j] = k;
                else
                    plDebug::Warning("Throwing away key %s", k->toString().cstr());
                subChild = subChild->getNextSibling();
            }
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Meshes") {
        size_t nMeshes = tag->countChildren();
        if (nMeshes > 3)
            throw hsBadParamException(__FILE__, __LINE__);
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<3; i++) {
            fMeshes[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Accessory") {
        if (tag->hasChildren())
            fAccessory = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "DefaultTints") {
        size_t nTints = tag->countChildren();
        if (nTints > 3)
            throw hsBadParamException(__FILE__, __LINE__);
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<3; i++) {
            fDefaultTint1[i] = child->getParam("color1", "0").toUint();
            fDefaultTint2[i] = child->getParam("color2", "0").toUint();
            child = child->getNextSibling();
        }
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}
