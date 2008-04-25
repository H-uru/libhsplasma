#include "plAvatarClothing.h"

/* plClothingOutfit */
const char* const plClothingOutfit::GroupNames[] = {
    "Male", "Female", "(No Options)"
};

const char* const plClothingOutfit::TypeNames[] = {
    "Pants", "Shirt", "LeftHand", "RightHand", "Face", "Hair",
    "LeftFoot", "RightFoot", "Accessory"
};

plClothingOutfit::plClothingOutfit() { }
plClothingOutfit::~plClothingOutfit() { }

IMPLEMENT_CREATABLE(plClothingOutfit, kClothingOutfit, plSynchedObject)

void plClothingOutfit::read(hsStream* S, plResManager* mgr) {
    plSynchedObject::read(S, mgr);

    fGroup = S->readByte();
    fBase = mgr->readKey(S);
    if (fGroup != kClothingGroupNoOptions) {
        fTargetTexture = mgr->readKey(S);
        fMaterial = mgr->readKey(S);
    }
}

void plClothingOutfit::write(hsStream* S, plResManager* mgr) {
    plSynchedObject::write(S, mgr);

    S->writeByte(fGroup);
    mgr->writeKey(S, fBase);
    if (fGroup != kClothingGroupNoOptions) {
        mgr->writeKey(S, fTargetTexture);
        mgr->writeKey(S, fMaterial);
    }
}

void plClothingOutfit::IPrcWrite(pfPrcHelper* prc) {
    plSynchedObject::IPrcWrite(prc);

    prc->startTag("Group");
    prc->writeParam("type", GroupNames[fGroup]);
    prc->endTag(true);

    prc->writeSimpleTag("Base");
    fBase->prcWrite(prc);
    prc->closeTag();

    if (fGroup != kClothingGroupNoOptions) {
        prc->writeSimpleTag("TargetTexture");
        fTargetTexture->prcWrite(prc);
        prc->closeTag();

        prc->writeSimpleTag("Material");
        fMaterial->prcWrite(prc);
        prc->closeTag();
    }
}


/* plClothingBase */
plClothingBase::plClothingBase() { }
plClothingBase::~plClothingBase() { }

IMPLEMENT_CREATABLE(plClothingBase, kClothingBase, hsKeyedObject)

void plClothingBase::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);

    fName = S->readSafeStr();
    if (S->readBool())
        fBaseTexture = mgr->readKey(S);
    fLayoutName = S->readSafeStr();
}

void plClothingBase::write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);

    S->writeSafeStr(fName);
    if (fBaseTexture.Exists())
        mgr->writeKey(S, fBaseTexture);
    S->writeSafeStr(fLayoutName);
}

void plClothingBase::IPrcWrite(pfPrcHelper* prc) {
    hsKeyedObject::IPrcWrite(prc);

    prc->startTag("ClothingBaseParams");
    prc->writeParam("Name", fName);
    prc->writeParam("Layout", fLayoutName);
    prc->endTag(true);

    if (fBaseTexture.Exists()) {
        prc->writeSimpleTag("BaseTexture");
        fBaseTexture->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("BaseTexture");
        prc->writeParam("Exists", false);
        prc->endTag(true);
    }
}
