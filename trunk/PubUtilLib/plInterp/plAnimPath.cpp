#include "plAnimPath.h"

/* ArcLenDeltaInfo */
plAnimPath::ArcLenDeltaInfo::ArcLenDeltaInfo()
          : fT(0.0f), fArcLenDelta(0.0f) { }
plAnimPath::ArcLenDeltaInfo::ArcLenDeltaInfo(float T, float arcLenDelta)
          : fT(T), fArcLenDelta(arcLenDelta) { }


/* plAnimPath */
plAnimPath::plAnimPath() : fController(NULL), fTMController(NULL) { }

plAnimPath::~plAnimPath() {
    if (fController) delete fController;
    if (fTMController) delete fTMController;
}

IMPLEMENT_CREATABLE(plAnimPath, kAnimPath, plCreatable)

void plAnimPath::read(hsStream* S, plResManager* mgr) {
    fAnimPathFlags = S->readInt();

    if (fController != NULL) delete fController;
    if (fTMController != NULL) delete fTMController;

    if (S->getVer() == pvPrime || S->getVer() == pvPots) {
        fTMController = new plTMController();
        fTMController->read(S, mgr);
        fController = NULL;
    } else {
        fController = plCompoundController::Convert(mgr->ReadCreatable(S));
        fTMController = NULL;
    }

    //ICalcBounds();
    fParts.read(S);
    fLocalToWorld.read(S);
    fWorldToLocal.read(S);
    fLength = S->readFloat();
    fMinDistSq = S->readFloat();
    //SetCurTime(0.0f, 0);
}

void plAnimPath::write(hsStream* S, plResManager* mgr) {
    S->writeInt(fAnimPathFlags);

    if (S->getVer() == pvPrime || S->getVer() == pvPots) {
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

void plAnimPath::prcWrite(pfPrcHelper* prc) {
    plCreatable::prcWrite(prc);

    prc->startTag("Parameters");
      prc->writeParam("Flags", fAnimPathFlags);
      prc->writeParam("Length", fLength);
      prc->writeParam("MinDistSq", fMinDistSq);
    prc->endTag(true);
    if (fController != NULL) {
        fController->prcWrite(prc);
        prc->closeTag();
    }
    if (fTMController != NULL) {
        fTMController->prcWrite(prc);
        prc->closeTag();
    }
    fParts.prcWrite(prc);

    prc->writeSimpleTag("LocalToWorld");
      fLocalToWorld.prcWrite(prc);
      fWorldToLocal.prcWrite(prc);
    prc->closeTag();
}
