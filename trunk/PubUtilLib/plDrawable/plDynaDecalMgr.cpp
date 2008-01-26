#include "plDynaDecalMgr.h"

// plDynaDecalMgr //
plDynaDecalMgr::plDynaDecalMgr()
              : fPartyTime(0.0f), fMaxNumVerts(0), fMaxNumIdx(0),
                fWaitOnEnable(0), fWetLength(0.0f), fRampEnd(0.0f),
                fDecayStart(0.0f), fLifeSpan(0.0f), fIntensity(0.0f),
                fGridSizeU(0.0f), fGridSizeV(0.0f), fInitAtten(0.0f),
                fMinDepth(0.0f), fMaxDepth(0.0f), fMinDepthRange(0.0f),
                fMaxDepthRange(0.0f) { }

plDynaDecalMgr::~plDynaDecalMgr() { }

IMPLEMENT_CREATABLE(plDynaDecalMgr, kDynaDecalMgr, plSynchedObject)

void plDynaDecalMgr::read(hsStream* S, plResManager* mgr) {
    plSynchedObject::read(S, mgr);

    fMatPreShade = mgr->readKey(S);
    fMatRTShade = mgr->readKey(S);

    fTargets.setSize(S->readInt());
    for (size_t i=0; i<fTargets.getSize(); i++)
        fTargets[i] = mgr->readKey(S);
    fPartyObjects.setSize(S->readInt());
    for (size_t i=0; i<fPartyObjects.getSize(); i++)
        fPartyObjects[i] = mgr->readKey(S);

    fMaxNumVerts = S->readInt();
    fMaxNumIdx = S->readInt();
    fWaitOnEnable = S->readInt();
    fIntensity = S->readFloat();
    fWetLength = S->readFloat();
    fRampEnd = S->readFloat();
    fDecayStart = S->readFloat();
    fLifeSpan = S->readFloat();
    fGridSizeU = S->readFloat();
    fGridSizeV = S->readFloat();
    fScale.read(S);
    fPartyTime = S->readFloat();

    fNotifies.setSize(S->readInt());
    for (size_t i=0; i<fNotifies.getSize(); i++)
        fNotifies[i] = mgr->readKey(S);
}

void plDynaDecalMgr::write(hsStream* S, plResManager* mgr) {
    plSynchedObject::write(S, mgr);

    mgr->writeKey(S, fMatPreShade);
    mgr->writeKey(S, fMatRTShade);

    S->writeInt(fTargets.getSize());
    for (size_t i=0; i<fTargets.getSize(); i++)
        mgr->writeKey(S, fTargets[i]);
    S->writeInt(fPartyObjects.getSize());
    for (size_t i=0; i<fPartyObjects.getSize(); i++)
        mgr->writeKey(S, fPartyObjects[i]);

    S->writeInt(fMaxNumVerts);
    S->writeInt(fMaxNumIdx);
    S->writeInt(fWaitOnEnable);
    S->writeFloat(fIntensity);
    S->writeFloat(fWetLength);
    S->writeFloat(fRampEnd);
    S->writeFloat(fDecayStart);
    S->writeFloat(fLifeSpan);
    S->writeFloat(fGridSizeU);
    S->writeFloat(fGridSizeV);
    fScale.write(S);
    S->writeFloat(fPartyTime);

    S->writeInt(fNotifies.getSize());
    for (size_t i=0; i<fNotifies.getSize(); i++)
        mgr->writeKey(S, fNotifies[i]);
}

void plDynaDecalMgr::prcWrite(pfPrcHelper* prc) {
    plSynchedObject::prcWrite(prc);

    prc->writeSimpleTag("PreShade");
    fMatPreShade->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("RTShade");
    fMatRTShade->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Targets");
    for (size_t i=0; i<fTargets.getSize(); i++)
        fTargets[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("PartyObjects");
    for (size_t i=0; i<fPartyObjects.getSize(); i++)
        fPartyObjects[i]->prcWrite(prc);
    prc->closeTag();

    prc->startTag("DynaDecalParams");
    prc->writeParam("MaxNumVerts", fMaxNumVerts);
    prc->writeParam("MaxNumIndices", fMaxNumIdx);
    prc->writeParam("WaitOnEnable", fWaitOnEnable);
    prc->writeParam("PartyTime", fPartyTime);
    prc->endTag(true);

    prc->startTag("DynaDecalMetrics");
    prc->writeParam("Intensity", fIntensity);
    prc->writeParam("WetLength", fWetLength);
    prc->writeParam("RampEnd", fRampEnd);
    prc->writeParam("DecayStart", fDecayStart);
    prc->writeParam("LifeSpan", fLifeSpan);
    prc->endTag();
      prc->startTag("GridSize");
      prc->writeParam("U", fGridSizeU);
      prc->writeParam("V", fGridSizeV);
      prc->endTag(true);
      prc->writeSimpleTag("Scale");
      fScale.prcWrite(prc);
      prc->closeTag();
    prc->closeTag();

    prc->writeSimpleTag("Notifies");
    for (size_t i=0; i<fNotifies.getSize(); i++)
        fNotifies[i]->prcWrite(prc);
    prc->closeTag();
}


// plDynaBulletMgr //
plDynaBulletMgr::plDynaBulletMgr() { }
plDynaBulletMgr::~plDynaBulletMgr() { }

IMPLEMENT_CREATABLE(plDynaBulletMgr, kDynaBulletMgr, plDynaDecalMgr)


// plDynaFootMgr //
plDynaFootMgr::plDynaFootMgr() { }
plDynaFootMgr::~plDynaFootMgr() { }

IMPLEMENT_CREATABLE(plDynaFootMgr, kDynaFootMgr, plDynaDecalMgr)
