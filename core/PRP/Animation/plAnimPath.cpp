#include "plAnimPath.h"

/* plAnimPath */
plAnimPath::plAnimPath() : fController(NULL), fTMController(NULL) { }

plAnimPath::~plAnimPath() {
    if (fController != NULL)
        delete fController;
    if (fTMController != NULL)
        delete fTMController;
}

void plAnimPath::read(hsStream* S, plResManager* mgr) {
    fAnimPathFlags = S->readInt();

    if (fController != NULL)
        delete fController;
    if (fTMController != NULL)
        delete fTMController;

    bool useTM = (S->getVer() <= pvPots);
    if (S->getVer() == pvUniversal)
        useTM = S->readBool();

    if (useTM) {
        fTMController = new plTMController();
        fTMController->read(S, mgr);
        fController = NULL;
    } else {
        fController = plCompoundController::Convert(mgr->ReadCreatable(S));
        fTMController = NULL;
    }

    fParts.read(S);
    fLocalToWorld.read(S);
    fWorldToLocal.read(S);
    fLength = S->readFloat();
    fMinDistSq = S->readFloat();
}

void plAnimPath::write(hsStream* S, plResManager* mgr) {
    S->writeInt(fAnimPathFlags);

    bool useTM = (S->getVer() <= pvPots);
    if (S->getVer() == pvUniversal) {
        useTM = (fTMController != NULL);
        S->writeBool(useTM);
    }

    if (useTM) {
        plTMController* controller = fTMController;
        if (controller == NULL && fController != NULL)
            controller = fController->convertToTMController();
        if (controller == NULL) {
            controller = new plTMController();
            controller->write(S, mgr);
            delete controller;
        } else {
            controller->write(S, mgr);
        }
    } else {
        plCompoundController* controller = fController;
        if (controller == NULL && fTMController != NULL)
            controller = fTMController->convertToCompoundController();
        mgr->WriteCreatable(S, controller);
    }

    fParts.write(S);
    fLocalToWorld.write(S);
    fWorldToLocal.write(S);
    S->writeFloat(fLength);
    S->writeFloat(fMinDistSq);
}

void plAnimPath::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("AnimPathParams");
      prc->writeParamHex("Flags", fAnimPathFlags);
      prc->writeParam("Length", fLength);
      prc->writeParam("MinDistSq", fMinDistSq);
    prc->endTag(true);

    prc->writeSimpleTag("Controller");
    if (fController != NULL)
        fController->prcWrite(prc);
    if (fTMController != NULL)
        fTMController->prcWrite(prc);
    prc->closeTag();
    fParts.prcWrite(prc);

    prc->writeSimpleTag("LocalToWorld");
      fLocalToWorld.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("WorldToLocal");
      fWorldToLocal.prcWrite(prc);
    prc->closeTag();
}

void plAnimPath::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "AnimPathParams") {
        fAnimPathFlags = tag->getParam("Flags", "0").toUint();
        fLength = tag->getParam("Length", "0").toFloat();
        fMinDistSq = tag->getParam("MinDistSq", "0").toFloat();
    } else if (tag->getName() == "Controller") {
        if (tag->hasChildren()) {
            if (fController != NULL)
                delete fController;
            if (fTMController != NULL)
                delete fTMController;
            if (tag->getFirstChild()->getName() == "plTMController") {
                fTMController = new plTMController();
                fTMController->prcParse(tag->getFirstChild(), mgr);
                fController = NULL;
            } else {
                fController = plCompoundController::Convert(mgr->prcParseCreatable(tag->getFirstChild()));
                fTMController = NULL;
            }
        }
    } else if (tag->getName() == "hsAffineParts") {
        fParts.prcParse(tag);
    } else if (tag->getName() == "LocalToWorld") {
        if (tag->hasChildren())
            fLocalToWorld.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "WorldToLocal") {
        if (tag->hasChildren())
            fWorldToLocal.prcParse(tag->getFirstChild());
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

void plAnimPath::setController(plCompoundController* controller) {
    if (fController != NULL)
        delete fController;
    if (fTMController != NULL)
        delete fTMController;
    fController = controller;
    fTMController = NULL;
}

void plAnimPath::setTMController(plTMController* controller) {
    if (fController != NULL)
        delete fController;
    if (fTMController != NULL)
        delete fTMController;
    fTMController = controller;
    fController = NULL;
}
