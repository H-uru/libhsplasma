#include "plAnimPath.h"
#include "../plResMgr/plResManager.h"

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
        if (fController != NULL)
            mgr->WriteCreatable(S, fController);
        else
            mgr->WriteCreatable(S, fTMController->convertToCompoundController());
    } else {
        if (fTMController != NULL)
            fTMController->write(S, mgr);
        else
            fController->convertToTMController()->write(S, mgr);
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
    fController->prcWrite(prc);
    fParts.prcWrite(prc);

    prc->writeSimpleTag("LocalToWorld");
      fLocalToWorld.prcWrite(prc);
      fWorldToLocal.prcWrite(prc);
    prc->closeTag();
}
