#include "plLeafController.h"
#include "plKeyControllers.h"

/* plLeafController */
plLeafController::plLeafController() { }

plLeafController::~plLeafController() {
    DeallocKeys();
    DeallocControllers();
}

IMPLEMENT_CREATABLE(plLeafController, kLeafController, plController)

void plLeafController::read(hsStream* S, plResManager* mgr) {
    if (S->getVer() == pvPrime || S->getVer() == pvPots) {
        fType = S->readInt();
        if (S->getVer() == pvEoa && fType >= hsKeyFrame::kCompressedQuatKeyFrame64)
            fType++;    // Myst V doesn't have hsCompressedQuatKeyFrame64
        unsigned int numControllers = S->readInt();
        AllocControllers(numControllers);

        for (size_t i=0; i<fControllers.getSize(); i++)
            fControllers[i]->read(S, mgr);

        S->readInt();
    } else {
        fType = S->readByte();
        unsigned int numKeys = S->readInt();
        AllocKeys(numKeys, fType);

        for (size_t i=0; i<fKeys.getSize(); i++)
            fKeys[i]->read(S);
    }
}

void plLeafController::write(hsStream* S, plResManager* mgr) {
    //TODO: Convert Keys to Controllers and vice versa

    if (S->getVer() == pvPrime || S->getVer() == pvPots) {
        if (S->getVer() == pvEoa && fType >= hsKeyFrame::kCompressedQuatKeyFrame64)
            S->writeInt(fType - 1);
        else
            S->writeInt(fType);
        S->writeInt(fControllers.getSize());

        for (size_t i=0; i<fControllers.getSize(); i++)
            fControllers[i]->write(S, mgr);

        S->writeInt(0);
    } else {
        S->writeByte(fType);
        S->writeInt(fKeys.getSize());

        for (size_t i=0; i<fKeys.getSize(); i++)
            fKeys[i]->write(S);
    }
}

void plLeafController::prcWrite(pfPrcHelper* prc) {
    plCreatable::prcWrite(prc);

    prc->startTag("Parameters");
    prc->writeParam("Type", fType);
    prc->endTag(true);
    
    prc->writeSimpleTag("Keys");
    for (size_t i=0; i<fKeys.getSize(); i++)
        fKeys[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Controllers");
    for (size_t i=0; i<fControllers.getSize(); i++)
        fControllers[i]->prcWrite(prc);
    prc->closeTag();
}

void plLeafController::AllocKeys(unsigned int numKeys, unsigned char type) {
    DeallocKeys();
    fType = type;
    fKeys.setSizeNull(numKeys);

    switch (fType) {
    case hsKeyFrame::kPoint3KeyFrame:
        for (size_t i=0; i<numKeys; i++)
            fKeys[i] = new hsPoint3Key();
        break;
    case hsKeyFrame::kBezPoint3KeyFrame:
        for (size_t i=0; i<numKeys; i++)
            fKeys[i] = new hsBezPoint3Key();
        break;
    case hsKeyFrame::kScalarKeyFrame:
        for (size_t i=0; i<numKeys; i++)
            fKeys[i] = new hsScalarKey();
        break;
    case hsKeyFrame::kBezScalarKeyFrame:
        for (size_t i=0; i<numKeys; i++)
            fKeys[i] = new hsBezScalarKey();
        break;
    case hsKeyFrame::kScaleKeyFrame:
        for (size_t i=0; i<numKeys; i++)
            fKeys[i] = new hsScaleKey();
        break;
    case hsKeyFrame::kBezScaleKeyFrame:
        for (size_t i=0; i<numKeys; i++)
            fKeys[i] = new hsBezScaleKey();
        break;
    case hsKeyFrame::kQuatKeyFrame:
        for (size_t i=0; i<numKeys; i++)
            fKeys[i] = new hsQuatKey();
        break;
    case hsKeyFrame::kCompressedQuatKeyFrame32:
        for (size_t i=0; i<numKeys; i++)
            fKeys[i] = new hsCompressedQuatKey32();
        break;
    case hsKeyFrame::kCompressedQuatKeyFrame64:
        for (size_t i=0; i<numKeys; i++)
            fKeys[i] = new hsCompressedQuatKey64();
        break;
    case hsKeyFrame::k3dsMaxKeyFrame:
        for (size_t i=0; i<numKeys; i++)
            fKeys[i] = new hsG3DSMaxKeyFrame();
        break;
    case hsKeyFrame::kMatrix33KeyFrame:
        for (size_t i=0; i<numKeys; i++)
            fKeys[i] = new hsMatrix33Key();
        break;
    case hsKeyFrame::kMatrix44KeyFrame:
        for (size_t i=0; i<numKeys; i++)
            fKeys[i] = new hsMatrix44Key();
        break;
    default:
        break;
    }
}

void plLeafController::DeallocKeys() {
    for (size_t i=0; i<fKeys.getSize(); i++)
        delete fKeys[i];
    fKeys.setSize(0);
}

void plLeafController::AllocControllers(unsigned int numControllers) {
    DeallocControllers();
    fControllers.setSizeNull(numControllers);
    for (size_t i=0; i<fControllers.getSize(); i++)
        fControllers[i] = new plEaseController();
}

void plLeafController::DeallocControllers() {
    for (size_t i=0; i<fControllers.getSize(); i++)
        delete fControllers[i];
    fControllers.setSize(0);
}
